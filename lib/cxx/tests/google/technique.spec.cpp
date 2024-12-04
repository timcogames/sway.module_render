#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/techniquedeserializer.hpp>

#include <google/pass.jdata.hpp>
#include <google/plugfixture.hpp>
#include <google/technique.jdata.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

TEST(TechniqueTest, deserialize) {
  auto jraw = toRawString(TechniqueJsonTest, "<PASSES_1>", PassJsonTest);
  auto tech = TechniqueDeserializer::deserialize(nlohmann::json::parse(jraw));
  ASSERT_NE(nullptr, tech);
}
