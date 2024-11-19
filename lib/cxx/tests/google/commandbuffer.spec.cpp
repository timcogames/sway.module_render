#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandbufferexecutor.hpp>

#include <google/plugfixture.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

TEST(CommandBufferTest, submit) {
  CommandBuffer buf((struct CommandBufferCreateInfo){});
  buf.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::BEGIN_PASS}));
  buf.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::DRAW}));
  buf.enqueue(std::make_unique<Command>((struct Command){.type = CommandType::Enum::END_PASS}));

  CommandBufferExecutor executor;
  CommandBufferTypedefs::RefArray_t refs = {buf};
  executor.submit(refs);
}
