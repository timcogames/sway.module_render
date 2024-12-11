#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>

#include <google/plugfixture.hpp>
#include <google/stubs/capabilitystub.hpp>
#include <google/stubs/drawcallstub.hpp>
#include <google/stubs/framebufferidgeneratorstub.hpp>
#include <google/stubs/idgeneratorstub.hpp>
#include <google/stubs/rasterizerstatestub.hpp>
#include <google/stubs/textureidgeneratorstub.hpp>
#include <google/stubs/viewportstub.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

NS_SHORT_SWAY()

class SpriteTestFixture : public PlugTestFixture {};

class RenderSubsystemContext : public core::foundation::Context {
public:
  RenderSubsystemContext() {
    subsys = std::make_shared<render::RenderSubsystem>(nullptr, this);
    subsys->setGraphicsApiContext(globalGapiPlug);
    subsys->initialize();
  }

public:
  render::RenderSubsystem::SharedPtr_t subsys;
};

TEST_F(SpriteTestFixture, test) {
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

  RenderSubsystemContext context;

  render::Sprite sprite;
  // sprite.initialize(context.subsys, nullptr, math::size2f_t(32, 32), math::size2i_one);
  // sprite.setRenderQueue(nullptr);

  // SAFE_DELETE_OBJECT(drawCallStub);
  // SAFE_DELETE_OBJECT(capabilityStub);
  SAFE_DELETE_OBJECT(viewportStub);
  // SAFE_DELETE_OBJECT(rasterizerStateStub);
  // SAFE_DELETE_OBJECT(textureIdGeneratorStub);
  // SAFE_DELETE_OBJECT(frameBufferIdGeneratorStub);
  // SAFE_DELETE_OBJECT(geometryIdGeneratorStub);
}
