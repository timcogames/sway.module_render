#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandbufferexecutor.hpp>
#include <sway/render/experience/command/commandqueue.hpp>
#include <sway/render/experience/command/commandqueuesorter.hpp>
#include <sway/render/experience/command/specs/beginpasscommand.hpp>
#include <sway/render/experience/command/specs/beginpasscommandhandler.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/drawcommandhandler.hpp>
#include <sway/render/experience/command/specs/endpasscommand.hpp>
#include <sway/render/experience/command/specs/endpasscommandhandler.hpp>
#include <sway/render/experience/pass/pass.hpp>

#include <google/plugfixture.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

TEST(CommandBufferTest, submit) {
  auto passCache = std::make_unique<Cache<Pass>>();
  auto pass = passCache->getOrCreate<PassDescriptor, Pass>((struct PassDescriptor){.format = 0});

  CommandBuffer buf((struct CommandBufferDescriptor){});
  buf.enqueue(std::make_unique<BeginPassCommand>(*pass));
  buf.enqueue(std::make_unique<DrawCommand>());
  buf.enqueue(std::make_unique<EndPassCommand>());

  ASSERT_EQ(buf.size(), 3);

  CommandBufferExecutor executor;
  executor.registerHandler(std::make_unique<experience::BeginPassCommandHandler>());
  executor.registerHandler(std::make_unique<experience::EndPassCommandHandler>());
  executor.registerHandler(std::make_unique<experience::DrawCommandHandler>());

  CommandBufferTypedefs::RefArray_t refs = {buf};
  executor.submit(refs);
}

TEST(CommandQueueTest, sort) {
  const u32_t MAIN_GROUP = 0;
  CommandQueue queue;

  auto passCache = std::make_unique<Cache<Pass>>();
  auto pass = passCache->getOrCreate<PassDescriptor, Pass>((struct PassDescriptor){.format = 0});

  auto buf1 = new CommandBuffer((struct CommandBufferDescriptor){.group = MAIN_GROUP, .priority = 0});
  ASSERT_EQ(buf1->group(), MAIN_GROUP);
  ASSERT_EQ(buf1->priority(), 0);

  buf1->enqueue(std::make_unique<BeginPassCommand>(*pass));
  buf1->enqueue(std::make_unique<DrawCommand>());
  buf1->enqueue(std::make_unique<EndPassCommand>());
  queue.add(buf1);

  auto buf2Opt = queue.createBuffer((struct CommandBufferDescriptor){.group = MAIN_GROUP, .priority = 1});
  if (!buf2Opt.has_value()) {
    // ERR
  }

  auto &buf2 = buf2Opt->get();
  ASSERT_EQ(buf2.group(), MAIN_GROUP);
  ASSERT_EQ(buf2.priority(), 1);

  buf2.enqueue(std::make_unique<BeginPassCommand>(*pass));
  buf2.enqueue(std::make_unique<DrawCommand>());
  buf2.enqueue(std::make_unique<EndPassCommand>());

  CommandQueueSorter::sort(queue.subqueue(MAIN_GROUP), SortOrder::Enum::ASCENDING);

  queue.process(MAIN_GROUP);
}
