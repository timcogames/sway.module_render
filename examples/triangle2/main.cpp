#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/glx11/canvas.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/graphics.hpp>
#include <sway/math.hpp>
#include <sway/math/extensions/projection.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

class RenderSubsystemContext : public core::foundation::Context {
public:
  RenderSubsystemContext() {
    char path[PATH_MAX + 1];
    strncpy(path, "/Users/apriori85/Documents/Projects/sway.module_graphics/bin", PATH_MAX);
    std::string plugname = core::misc::format("%s/module_gapi_gl.dylib.0.16.34", path);
    // std::string plugpath = core::generic::io::Path(plugname).toString();

    subsystem_ = std::make_shared<graphics::RenderSubsystem>(plugname, this);

    gapi::ShaderCreateInfoSet shaderCreateInfoSet;
    shaderCreateInfoSet.vs.type = gapi::ShaderType::VERTEX;
    shaderCreateInfoSet.vs.code = "attribute vec3 attr_position;"
                                  "attribute vec4 attr_color;"
                                  "uniform mat4 projection_mat4f;"
                                  "varying vec4 color;"
                                  "void main() {"
                                  "	gl_Position = projection_mat4f * vec4(attr_position, 1.0);"
                                  "	color = attr_color;"
                                  "}";
    shaderCreateInfoSet.fs.type = gapi::ShaderType::FRAGMENT;
    shaderCreateInfoSet.fs.code = "varying vec4 color;"
                                  "void main() {"
                                  "	gl_FragColor = color;"
                                  "}";

    subqueue_ = std::make_shared<graphics::RenderSubqueue>();
    material_ = std::make_shared<graphics::Material>(shaderCreateInfoSet);
    auto staticMesh = std::make_shared<graphics::StaticMesh>(
        subqueue_, std::make_shared<graphics::primitives::Quad>(0.5, 0.5), material_);
    auto queue = subsystem_->createQueue();
    queue->setPriority(core::intrusive::Priority_High);
    queue->addSubqueue(subqueue_);
  }

  virtual ~RenderSubsystemContext() = default;

  void drawFrame() { subsystem_->render(); }

  std::shared_ptr<graphics::Material> getMaterial() { return material_; }

private:
  std::shared_ptr<graphics::RenderSubsystem> subsystem_;
  std::shared_ptr<graphics::RenderSubqueue> subqueue_;
  std::shared_ptr<graphics::Material> material_;
};

enum { WindowSize_WD = 800, WindowSize_HT = 600 };

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  glx11::WindowInitialInfo windowInitialInfo;
  windowInitialInfo.title = "examples";
  windowInitialInfo.size.normal = math::size2i_t(WindowSize_WD, WindowSize_HT);
  windowInitialInfo.fullscreen = false;
  windowInitialInfo.resizable = false;

  auto connection = std::make_shared<glx11::XScreenConnection>();
  auto canvas = std::make_shared<glx11::Canvas>(connection, windowInitialInfo);

  canvas->show();
  canvas->getContext()->makeCurrent();

  auto rendersystemContext = std::make_shared<RenderSubsystemContext>();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    float const aspectRatio = 1.0;

    math::Projection projection;
    math::mat4f_t projmat = projection.ortho(1.0 * aspectRatio, -1.0, -1.0 * aspectRatio, 1.0, 0.0, 100.0);

    rendersystemContext->getMaterial()->getShaderProgram()->setUniformMat4f("projection_mat4f", projmat);

    rendersystemContext->drawFrame();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
