#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/glx11/canvas.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/graphics.hpp>
#include <sway/math.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

class RenderSubsystemContext : public core::foundation::Context {
public:
  RenderSubsystemContext() {
    char path[PATH_MAX + 1];
    strncpy(path, "/home/bonus85/Projects/sway.modules/sway.module_graphics/bin", PATH_MAX);
    std::string plugname = core::misc::format("%s/module_gapi_gl.so.0.16.34", path);
    // std::string plugpath = core::generic::io::Path(plugname).toString();

    _subsystem = std::make_shared<graphics::RenderSubsystem>(plugname, this);

    gapi::ShaderCreateInfoSet shaderCreateInfoSet;
    shaderCreateInfoSet.vs.type = gapi::ShaderType_t::kVertex;
    shaderCreateInfoSet.vs.code = "attribute vec3 attr_position;"
                                  "attribute vec4 attr_color;"
                                  "varying vec4 color;"
                                  "void main() {"
                                  "	gl_Position = vec4(attr_position, 1.0);"
                                  "	color = attr_color;"
                                  "}";
    shaderCreateInfoSet.fs.type = gapi::ShaderType_t::kFragment;
    shaderCreateInfoSet.fs.code = "varying vec4 color;"
                                  "void main() {"
                                  "	gl_FragColor = color;"
                                  "}";

    auto subqueue = std::make_shared<graphics::RenderSubqueue>();
    auto material = std::make_shared<graphics::Material>(shaderCreateInfoSet);
    auto staticMesh = std::make_shared<graphics::StaticMesh>(subqueue, material);
    auto queue = _subsystem->createQueue();
    queue->setPriority(core::intrusive::kPriority_High);
    queue->addSubqueue(subqueue);
  }

  virtual ~RenderSubsystemContext() {
    // Empty
  }

  void drawFrame() { _subsystem->render(); }

private:
  std::shared_ptr<graphics::RenderSubsystem> _subsystem;
};

int main(int argc, char *argv[]) {
  glx11::WindowInitialInfo windowInitialInfo;
  windowInitialInfo.title = "examples";
  windowInitialInfo.size.normal = math::size2i_t(800, 600);
  windowInitialInfo.fullscreen = false;
  windowInitialInfo.resizable = false;

  auto connection = std::make_shared<glx11::XScreenConnection>();
  auto canvas = std::make_shared<glx11::Canvas>(connection, windowInitialInfo);

  canvas->show();
  canvas->getContext()->makeCurrent();

  auto rendersystemContext = std::make_shared<RenderSubsystemContext>();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    rendersystemContext->drawFrame();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
