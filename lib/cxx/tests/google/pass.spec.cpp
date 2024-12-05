#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/experience/command/specs/beginpasscommand.hpp>
#include <sway/render/experience/command/specs/beginpasscommandhandler.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/drawcommandhandler.hpp>
#include <sway/render/experience/command/specs/endpasscommand.hpp>
#include <sway/render/experience/command/specs/endpasscommandhandler.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pass/passdeserializer.hpp>
#include <sway/render/experience/pass/specs/graphicspass.hpp>

#include <google/pass.jdata.hpp>
#include <google/plugfixture.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

TEST(GraphicsPassTest, render) {
  auto context = std::make_shared<OperationContext>();
  auto queue = std::make_unique<CommandQueue>();

  auto bufOpt = CommandBuffer::create(queue, (struct CommandBufferDescriptor){.priority = 0});
  if (!bufOpt.has_value()) {
    // ERR
  }

  auto passCache = std::make_unique<Cache>();
  auto pass = passCache->getOrCreate<GraphicsPass>((struct PassDescriptor){.format = 0});
  pass->setQueue(std::move(queue));

  auto &buf = bufOpt->get();
  buf.enqueue(std::make_unique<BeginPassCommand>(*pass));
  buf.enqueue(std::make_unique<DrawCommand>(gapi::TopologyType::Enum::TRIANGLE_STRIP));
  buf.enqueue(std::make_unique<EndPassCommand>());

  pass->execute(context.get());
}

TEST(GraphicsPassTest, deserializer) {
  auto pass = PassDeserializer::deserialize_depricated<GraphicsPass>(nlohmann::json::parse(PassJsonTest));
  ASSERT_NE(nullptr, pass);
}
