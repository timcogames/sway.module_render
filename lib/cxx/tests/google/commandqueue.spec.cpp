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
  auto group = 0;
  CommandQueue queue;

  auto buf1 = new CommandBuffer((struct CommandBufferCreateInfo){.group = group, .priority = 0});
  buf1->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::BEGIN_PASS}));
  buf1->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::DRAW}));
  buf1->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::END_PASS}));
  queue.add(buf1);

  auto buf2 = new CommandBuffer((struct CommandBufferCreateInfo){.group = group, .priority = 1});
  buf2->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::BEGIN_PASS}));
  buf2->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::DRAW}));
  buf2->enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::END_PASS}));
  queue.add(buf2);

  CommandQueueSorter::sort(queue.subqueue(group), SortOrder::Enum::ASCENDING);

  queue.process(group);
}
