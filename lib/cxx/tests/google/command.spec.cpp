#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandbufferexecutor.hpp>
#include <sway/render/experience/command/commandqueue.hpp>
#include <sway/render/experience/command/commandqueuesorter.hpp>
#include <sway/render/experience/command/specs/beginpasscommand.hpp>
#include <sway/render/experience/command/specs/beginpasscommandhandler.hpp>
#include <sway/render/experience/command/specs/bindpipelinecommand.hpp>
#include <sway/render/experience/command/specs/bindpipelinecommandhandler.hpp>
#include <sway/render/experience/command/specs/clearcommand.hpp>
#include <sway/render/experience/command/specs/clearcommandhandler.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/drawcommandhandler.hpp>
#include <sway/render/experience/command/specs/endpasscommand.hpp>
#include <sway/render/experience/command/specs/endpasscommandhandler.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/global.hpp>

#include <google/plugfixture.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

class CommandBufferTestFixture : public PlugTestFixture {};

TEST_F(CommandBufferTestFixture, submit) {
  auto *viewportStub = createViewportStub(globalGapiPlug);

  auto passCache = std::make_unique<Cache>();
  auto pass = passCache->getOrCreate<GraphicsPass>((struct PassDescriptor){.format = 0});

  CommandBufferExecutor executor;
  executor.registerHandler(std::make_unique<experience::BeginPassCommandHandler>());
  executor.registerHandler(std::make_unique<experience::EndPassCommandHandler>());
  executor.registerHandler(std::make_unique<experience::DrawCommandHandler>());
  executor.registerHandler(std::make_unique<experience::ClearCommandHandler>(viewportStub));

  CommandBuffer buf((struct CommandBufferDescriptor){});
  buf.enqueue(std::make_unique<BeginPassCommand>(*pass));
  buf.enqueue(std::make_unique<ClearCommand>(math::col4f_t(0.0F, 0.0F, 0.0F, 255.0F), gapi::ClearFlag::COLOR));
  buf.enqueue(std::make_unique<DrawCommand>(gapi::TopologyType::Enum::TRIANGLE_STRIP));
  buf.enqueue(std::make_unique<EndPassCommand>());
  ASSERT_EQ(buf.getSize(), 4);

  CommandBufferTypedefs::RefArray_t refs = {buf};
  executor.submit(refs);

  SAFE_DELETE_OBJECT(viewportStub);
}

TEST(CommandQueueTest, sort) {
  const u32_t MAIN_GROUP = 0;
  CommandQueue queue;

  auto passCache = std::make_unique<Cache>();
  auto pass = passCache->getOrCreate<GraphicsPass>((struct PassDescriptor){.format = 0});

  auto buf1 = new CommandBuffer((struct CommandBufferDescriptor){.group = MAIN_GROUP, .priority = 0});
  ASSERT_EQ(buf1->getGroup(), MAIN_GROUP);
  ASSERT_EQ(buf1->getPriority(), 0);

  buf1->enqueue(std::make_unique<BeginPassCommand>(*pass));
  buf1->enqueue(std::make_unique<DrawCommand>(gapi::TopologyType::Enum::TRIANGLE_STRIP));
  buf1->enqueue(std::make_unique<EndPassCommand>());
  queue.add(buf1);

  auto buf2Opt = queue.createBuffer((struct CommandBufferDescriptor){.group = MAIN_GROUP, .priority = 1});
  if (!buf2Opt.has_value()) {
    // ERR
  }

  auto &buf2 = buf2Opt->get();
  ASSERT_EQ(buf2.getGroup(), MAIN_GROUP);
  ASSERT_EQ(buf2.getPriority(), 1);

  buf2.enqueue(std::make_unique<BeginPassCommand>(*pass));
  buf2.enqueue(std::make_unique<DrawCommand>(gapi::TopologyType::Enum::TRIANGLE_STRIP));
  buf2.enqueue(std::make_unique<EndPassCommand>());

  CommandQueueSorter::sort(queue.getSubqueue(MAIN_GROUP), SortOrder::Enum::ASCENDING);

  queue.process(MAIN_GROUP);
}
