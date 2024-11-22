#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/experience/command/commandqueue.hpp>
#include <sway/render/experience/command/commandqueuesorter.hpp>

#include <google/plugfixture.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

TEST(CommandQueueTest, sort) {
  const u32_t MAIN_GROUP = 0;
  CommandQueue queue;

  auto buf1 = new CommandBuffer((struct CommandBufferDescriptor){.group = MAIN_GROUP, .priority = 0});
  ASSERT_EQ(buf1->group(), MAIN_GROUP);
  ASSERT_EQ(buf1->priority(), 0);

  buf1->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::BEGIN_PASS}));
  buf1->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::DRAW}));
  buf1->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::END_PASS}));
  queue.add(buf1);

  auto buf2Opt = queue.createBuffer((struct CommandBufferDescriptor){.group = MAIN_GROUP, .priority = 1});
  if (!buf2Opt.has_value()) {
    // ERR
  }

  auto &buf2 = buf2Opt->get();
  ASSERT_EQ(buf2.group(), MAIN_GROUP);
  ASSERT_EQ(buf2.priority(), 1);

  buf2.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::BEGIN_PASS}));
  buf2.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::DRAW}));
  buf2.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::END_PASS}));

  CommandQueueSorter::sort(queue.subqueue(MAIN_GROUP), SortOrder::Enum::ASCENDING);

  queue.process(MAIN_GROUP);
}
