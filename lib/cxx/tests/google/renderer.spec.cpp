#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/pipeline/pipelinelibrary.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/rendermodule.hpp>

#include <google/plugfixture.hpp>
#include <google/stubs/capabilitystubcreator.hpp>
#include <google/stubs/drawcallstubcreator.hpp>
#include <google/stubs/viewportstubcreator.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

class RendererTestFixture : public PlugTestFixture {};

TEST_F(RendererTestFixture, setup) {
  const auto fwd = core::toBase(RendererType::Enum::IDX_FWD);
  const auto def = core::toBase(RendererType::Enum::IDX_DEF);

  auto mod = std::make_unique<RenderModule>();
  // RenderModule::getInternalContext()->capability = CapabilityStubCreator::create(globalGapiPlug);
  RenderModule::getInternalContext()->drawCall = DrawCallStubCreator::create(globalGapiPlug);
  RenderModule::getInternalContext()->viewport = ViewportStubCreator::create(globalGapiPlug);
  mod->prepare();

  ASSERT_EQ(mod->getState().activeRenderer->getType(), fwd);
  ASSERT_EQ(mod->getState().activeRendererIdx, fwd);

  mod->setActiveRenderer(def);
  ASSERT_EQ(mod->getState().activeRenderer->getType(), def);
  ASSERT_EQ(mod->getState().activeRendererIdx, def);

  mod->setActiveRenderer(fwd);
  ASSERT_EQ(mod->getState().activeRenderer->getType(), fwd);
  ASSERT_EQ(mod->getState().activeRendererIdx, fwd);

  auto tech = std::make_shared<Technique>("main");
  auto pass = Pass::get(tech.get(), (struct PassDescriptor){.format = 0});

  mod->getState().activeRenderer->render();

  RenderModule::getInternalContext()->disponse();
}
