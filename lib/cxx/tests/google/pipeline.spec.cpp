#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/rendermodule.hpp>

#include <google/plugfixture.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

TEST(PipelineTest, setup) {
  const auto fwd = core::detail::toBase(RendererType::Enum::IDX_FWD);
  const auto def = core::detail::toBase(RendererType::Enum::IDX_DEF);

  auto mod = std::make_unique<RenderModule>();
  mod->prepare();

  ASSERT_EQ(mod->state().activeRenderer->type(), fwd);
  ASSERT_EQ(mod->state().activeRendererIdx, fwd);

  mod->setActiveRenderer(def);
  ASSERT_EQ(mod->state().activeRenderer->type(), def);
  ASSERT_EQ(mod->state().activeRendererIdx, def);

  mod->setActiveRenderer(fwd);
  ASSERT_EQ(mod->state().activeRenderer->type(), fwd);
  ASSERT_EQ(mod->state().activeRendererIdx, fwd);

  auto ctx = RenderModule::getInternalContext();

  auto tech = std::make_shared<Technique>();
  auto pass = Pass::get(tech.get(), (struct PassDescriptor){.format = 0});
}
