#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pass/passcache.hpp>
#include <sway/render/experience/pass/specs/graphicspass.hpp>

#include <google/plugfixture.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

TEST(GraphicsPassTest, render) {
  auto queue = std::make_unique<CommandQueue>();
  auto bufOpt = queue->createBuffer((struct CommandBufferDescriptor){.group = 0, .priority = 0});
  if (!bufOpt.has_value()) {
    // ERR
  }

  auto &buf = bufOpt->get();
  buf.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::BEGIN_PASS}));
  buf.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::DRAW}));
  buf.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::END_PASS}));

  auto passCache = std::make_unique<PassCache>();
  auto pass = passCache->getOrCreate<GraphicsPass>((struct PassDescriptor){.format = 0});
  pass->setQueue(std::move(queue));
  pass->render();
}
