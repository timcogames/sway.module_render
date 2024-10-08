#ifndef SWAY_RENDER_PPE_SCREENQUAD_HPP
#define SWAY_RENDER_PPE_SCREENQUAD_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/flippable.hpp>
#include <sway/render/flipper.hpp>
#include <sway/render/geom/geombuilder.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/prims/quad.hpp>
#include <sway/render/rendercomponent.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/renderstages.hpp>
#include <sway/render/rendersubqueue.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class ScreenQuad {
  DECLARE_CLASS_POINTER_ALIASES(ScreenQuad)

public:
#pragma region "Ctors/Dtor"

  ScreenQuad() { drawCall_ = global::getGapiPluginFunctionSet()->createDrawCall(); }

  ~ScreenQuad() { geomBuilder_->remove(geomIdx_); }

#pragma endregion

  void createEffect() {
    std::unordered_map<gapi::ShaderType::Enum, std::string> sources = {
        {gapi::ShaderType::Enum::VERT, "layout (location = 0) in vec3 attrib_position;"
                                       "layout (location = 1) in vec4 attrib_color;"
                                       "layout (location = 2) in vec2 attrib_texcoord_0;"
                                       "out vec2 uv;"
                                       "void main() {"
                                       "    gl_Position = vec4(attrib_position, 1.0);"
                                       //  "    uv = attrib_position.xy * 0.5 + 0.5;"
                                       "    uv = attrib_texcoord_0;"
                                       "}"},
        {gapi::ShaderType::Enum::FRAG, "in vec2 uv;"
                                       "uniform sampler2D tex_color;"
                                       "out vec4 frag_color;"
                                       "void main() {"
                                       //  "    frag_color = texture(tex_color, uv);"
                                       "    frag_color = vec4(1.0, 0.0, 0.0, 1.0);"
                                       //  "    frag_color = vec4(vec3(1.0 - texture(tex_color, uv)), 1.0);"
                                       "}"}};

    gapi::ShaderCreateInfoSet createInfoSet;
    createInfoSet.vs.type = gapi::ShaderType::Enum::VERT;
    createInfoSet.vs.code = sources[gapi::ShaderType::Enum::VERT];
    createInfoSet.vs.preprocessor = global::getGapiPluginFunctionSet()->createShaderPreprocessor(300, "es");

    createInfoSet.fs.type = gapi::ShaderType::Enum::FRAG;
    createInfoSet.fs.code = sources[gapi::ShaderType::Enum::FRAG];
    createInfoSet.fs.preprocessor = global::getGapiPluginFunctionSet()->createShaderPreprocessor(300, "es");
    effect_ = Effect::create(createInfoSet);
  }

  void initialize(core::misc::Dictionary glob, GeomBuilder::SharedPtr_t geomBuilder) {
    geomBuilder_ = geomBuilder;

    screenWdt_ = (f32_t)glob.getIntegerOrDefault("screen_wdt", 800);
    screenHgt_ = (f32_t)glob.getIntegerOrDefault("screen_hgt", 600);

    createEffect();

    auto shape = new procedurals::prims::Quad<math::VertexTexCoord>(
        {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});

    shape->setPosDataAttrib(0.0f);
    shape->setColDataAttrib();
    shape->setTexDataAttrib();

    GeometryCreateInfo geomCreateInfo;
    geomCreateInfo.indexed = false;
    geomCreateInfo.topology = gapi::TopologyType::Enum::TRIANGLE_LIST;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::Enum::STATIC;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexTexCoord);
    geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = 6;
    auto data = new f32_t[6 * sizeof(math::VertexTexCoord)];
    shape->data()->getVertices(data, 0, 6);
    geomCreateInfo.bo[Constants::IDX_VBO].data = data;

    geomIdx_ = geomBuilder_->create<procedurals::prims::Quad<math::VertexTexCoord>>(
        geomCreateInfo, shape->getVertexAttribs(), effect_);
  }

  void draw() {
    auto geom = geomBuilder_->getGeometry(geomIdx_);
    if (!geom) {
      return;
    }

    effect_->bind();
    geom->bind();

    gapi::BufferSet bufset;
    bufset.vbo = geom->getBuffer(Constants::IDX_VBO).value();
    bufset.ebo = nullptr;

    drawCall_->execute(gapi::TopologyType::Enum::TRIANGLE_LIST, bufset, core::ValueDataType::Enum::UINT);

    geom->unbind();
    effect_->unbind();
  }

  auto getShader() -> gapi::ShaderProgram::Ptr_t { return effect_->getShaderProgram(); }

private:
  gapi::DrawCallPtr_t drawCall_;
  Effect::Ptr_t effect_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  u32_t geomIdx_;

  f32_t screenWdt_;
  f32_t screenHgt_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PPE_SCREENQUAD_HPP
