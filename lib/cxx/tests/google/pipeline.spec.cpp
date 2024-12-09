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
#include <google/stubs/viewportstubcreator.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

NS_SHORT_SWAY()
NS_SHORT(render)
NS_SHORT(render::experience)

class PipelineTestFixture : public PlugTestFixture {};

TEST_F(PipelineTestFixture, library) {
  auto lib = std::make_unique<PipelineLibrary>();

  GraphicsPipelineDescriptor pipelineDesc;
  pipelineDesc.shaders[0] = "vert";
  pipelineDesc.shaders[1] = "frag";

  auto pipelineFuture = lib->getGraphicsPipeline(pipelineDesc);
  ASSERT_NO_THROW(pipelineFuture.get());
}