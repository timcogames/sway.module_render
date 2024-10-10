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

struct VertexPosition2D {
  f32_t x, y;
  f32_t u, v;
};

class ScreenQuad {
  DECLARE_CLASS_POINTER_ALIASES(ScreenQuad)

public:
#pragma region "Ctors/Dtor"

  ScreenQuad() { drawCall_ = global::getGapiPluginFunctionSet()->createDrawCall(); }

  ~ScreenQuad() { geomBuilder_->remove(geomIdx_); }

#pragma endregion

  void createEffect() {
    std::unordered_map<gapi::ShaderType::Enum, std::string> sources = {
        {gapi::ShaderType::Enum::VERT, "layout (location = 0) in vec2 attrib_pos;"
                                       "layout (location = 1) in vec2 attrib_texcoord_0;"
                                       "out vec2 vtx_uv;"
                                       "void main() {"
                                       "    gl_Position = vec4(attrib_pos, 0.0, 1.0);"
                                       "    vtx_uv = attrib_texcoord_0;"
                                       "}"},
        {gapi::ShaderType::Enum::FRAG, "in vec2 vtx_uv;"
                                       "uniform sampler2D tex_color;"
                                       "out vec4 frag_color;"
                                       "void main() {"
                                       //  "    frag_color = vec4(vec3(1.0 - texture(tex_color, vtx_uv)), 1.0);"
                                       "    frag_color = texture(tex_color, vtx_uv);"
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

    createEffect();

    auto shape =
        new procedurals::prims::Quad<VertexPosition2D>({gapi::VertexSemantic::POS, gapi::VertexSemantic::TEXCOORD_0});

    shape->setPosDataAttrib();
    shape->setTexDataAttrib();

    GeometryCreateInfo geomCreateInfo;
    geomCreateInfo.indexed = false;
    geomCreateInfo.topology = gapi::TopologyType::Enum::TRIANGLE_STRIP;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::Enum::STATIC;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(VertexPosition2D);
    geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = 4;
    auto data = new f32_t[4 * sizeof(VertexPosition2D)];
    shape->data()->getVertices(data, 0, 4);
    // std::cout << math::vec2f_t(data[0], data[1]) << std::endl;
    // std::cout << math::vec2f_t(data[2], data[3]) << std::endl;
    // std::cout << math::vec2f_t(data[4], data[5]) << std::endl;
    // std::cout << math::vec2f_t(data[6], data[7]) << std::endl;
    geomCreateInfo.bo[Constants::IDX_VBO].data = data;

    geomIdx_ = geomBuilder_->create<procedurals::prims::Quad<VertexPosition2D>>(
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

    drawCall_->execute(gapi::TopologyType::Enum::TRIANGLE_STRIP, bufset, core::ValueDataType::Enum::UINT);

    geom->unbind();
    effect_->unbind();
  }

  auto getShader() -> gapi::ShaderProgram::Ptr_t { return effect_->getShaderProgram(); }

private:
  gapi::DrawCallPtr_t drawCall_;
  Effect::Ptr_t effect_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  Geom::Ptr_t geom_;
  u32_t geomIdx_;

  f32_t screenWdt_;
  f32_t screenHgt_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PPE_SCREENQUAD_HPP
