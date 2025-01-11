#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>
#include <sway/render/typedefs.hpp>

#include <google/plugfixture.hpp>
#include <google/stubs/bufferstub.hpp>
#include <google/stubs/capabilitystub.hpp>
#include <google/stubs/drawcallstub.hpp>
#include <google/stubs/framebufferidgeneratorstub.hpp>
#include <google/stubs/idgeneratorstub.hpp>
#include <google/stubs/rasterizerstatestub.hpp>
#include <google/stubs/shaderpreprocessorstubcreator.hpp>
#include <google/stubs/shaderprogramstubcreator.hpp>
#include <google/stubs/shaderstubcreator.hpp>
#include <google/stubs/textureidgeneratorstub.hpp>
#include <google/stubs/vertexarraystub.hpp>
#include <google/stubs/vertexattriblayoutstub.hpp>
#include <google/stubs/viewportstub.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

NS_SHORT_SWAY()

class SpriteTestFixture : public PlugTestFixture {};

class RenderSubsystemContext : public core::Context {
public:
  RenderSubsystemContext() {
    subsys = std::make_shared<render::RenderSubsystem>(nullptr, this);
    subsys->setGraphicsApiContext(globalGapiPlug);
    subsys->initialize();
  }

public:
  render::typedefs::RenderSubsystemSharedPtr_t subsys;
};

TEST_F(SpriteTestFixture, test) {
  auto *shaderStub = render::ShaderStubCreator::create(globalGapiPlug);
  auto *shaderProgStub = render::ShaderProgramStubCreator::create2(globalGapiPlug, shaderStub);

  auto *preprocessorStub = render::ShaderPreprocessorStubCreator::create(globalGapiPlug);
  EXPECT_CALL(*globalGapiPlug, createShaderPreprocessor(testing::_, testing::_))
      .WillRepeatedly(testing::Return(preprocessorStub));

  auto *geometryIdGeneratorStub = new render::IdGeneratorStub();
  EXPECT_CALL(*globalGapiPlug, createBufferIdGenerator()).WillRepeatedly(testing::Return(geometryIdGeneratorStub));

  auto *frameBufferIdGeneratorStub = new render::FrameBufferIdGeneratorStub();
  EXPECT_CALL(*globalGapiPlug, createFrameBufferIdGenerator())
      .WillRepeatedly(testing::Return(frameBufferIdGeneratorStub));

  auto *textureIdGeneratorStub = new render::TextureIdGeneratorStub();
  EXPECT_CALL(*globalGapiPlug, createTextureIdGenerator()).WillRepeatedly(testing::Return(textureIdGeneratorStub));

  auto *rasterizerStateStub = new render::RasterizerStateStub();
  EXPECT_CALL(*globalGapiPlug, createRasterizerState()).WillRepeatedly(testing::Return(rasterizerStateStub));

  auto *viewportStub = new render::ViewportStub();
  EXPECT_CALL(*globalGapiPlug, createViewport()).WillRepeatedly(testing::Return(viewportStub));
  EXPECT_CALL(*viewportStub, set(testing::_, testing::_));

  auto *capabilityStub = new render::CapabilityStub();
  EXPECT_CALL(*globalGapiPlug, createCapability()).WillRepeatedly(testing::Return(capabilityStub));

  auto *drawCallStub = new render::DrawCallStub();
  EXPECT_CALL(*globalGapiPlug, createDrawCall()).WillRepeatedly(testing::Return(drawCallStub));

  auto *vertexAttribLayoutStub = new render::VertexAttribLayoutStub();
  EXPECT_CALL(*globalGapiPlug, createVertexAttribLayout(shaderProgStub))
      .WillRepeatedly(testing::Return(vertexAttribLayoutStub));
  EXPECT_CALL(*vertexAttribLayoutStub, addAttribute(testing::_)).Times(testing::AnyNumber());

  auto *vertexArrayStub = new render::VertexArrayStub();
  EXPECT_CALL(*globalGapiPlug, createVertexArray()).WillRepeatedly(testing::Return(vertexArrayStub));

  auto *bufferStub = new render::BufferStub();
  EXPECT_CALL(*globalGapiPlug, createBuffer(geometryIdGeneratorStub, testing::_))
      .WillRepeatedly(testing::Return(bufferStub));

  RenderSubsystemContext context;

  render::ShaderTypedefs::SourcePair_t sources;
  sources[core::toBase(gapi::ShaderType::Enum::VERT)] = "layout (location = 0) in vec3 vtx_pos_attrib;"
                                                        "layout (location = 1) in vec4 vtx_col_attrib;"
                                                        "out vec4 vtx_col;"
                                                        "void main() {"
                                                        "    gl_Pos = vec4(vtx_pos_attrib, 1.0);"
                                                        "    vtx_col = vtx_col_attrib;"
                                                        "}";
  sources[core::toBase(gapi::ShaderType::Enum::FRAG)] = "in vec4 vtx_col;"
                                                        "out vec4 out_col;"
                                                        "void main() {"
                                                        "    out_col = vtx_col;"
                                                        "}";

  auto mtrl = std::make_shared<render::Material>(globalGapiPlug, "test_1");
  mtrl->addEffectSource(sources);

  auto sprite = std::make_unique<render::Sprite>();
  sprite->initialize(context.subsys, mtrl, math::size2f_t(32, 32), math::size2i_one);
  // sprite->setTexture(mtrl->getImage(0 /* ALBEDO */), false);
  // sprite->setRenderQueue(nullptr);

  sprite->destroy();

  SAFE_DELETE_OBJECT(preprocessorStub);
  SAFE_DELETE_OBJECT(shaderProgStub);
  SAFE_DELETE_OBJECT(shaderStub);
}
