#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/mtrl/material.hpp>
#include <sway/render/mtrl/materialdeserializer.hpp>

#include <google/pass.jdata.hpp>
#include <google/plugfixture.hpp>
#include <google/stubs/shaderpreprocessorstubcreator.hpp>
#include <google/stubs/shaderprogramstubcreator.hpp>
#include <google/stubs/shaderstubcreator.hpp>

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

NS_SHORT_SWAY()

class MaterialTestFixture : public PlugTestFixture {};

TEST_F(MaterialTestFixture, add_effect) {
  auto *shaderStub = render::ShaderStubCreator::create(globalGapiPlug);
  auto *shaderProgStub = render::ShaderProgramStubCreator::create2(globalGapiPlug, shaderStub);

  auto *preprocessorStub = render::ShaderPreprocessorStubCreator::create(globalGapiPlug);
  EXPECT_CALL(*globalGapiPlug, createShaderPreprocessor(testing::_, testing::_))
      .WillRepeatedly(testing::Return(preprocessorStub));

  render::ShaderTypedefs::SourcePair_t sources;
  sources[core::detail::toBase(gapi::ShaderType::Enum::VERT)] = "layout (location = 0) in vec3 vtx_pos_attrib;"
                                                                "layout (location = 1) in vec4 vtx_col_attrib;"
                                                                "out vec4 vtx_col;"
                                                                "void main() {"
                                                                "    gl_Pos = vec4(vtx_pos_attrib, 1.0);"
                                                                "    vtx_col = vtx_col_attrib;"
                                                                "}";
  sources[core::detail::toBase(gapi::ShaderType::Enum::FRAG)] = "in vec4 vtx_col;"
                                                                "out vec4 out_col;"
                                                                "void main() {"
                                                                "    out_col = vtx_col;"
                                                                "}";

  auto mtrl = std::make_shared<render::Material>(globalGapiPlug, "test_1");
  mtrl->addEffectSource(sources);

  SAFE_DELETE_OBJECT(preprocessorStub);
  SAFE_DELETE_OBJECT(shaderProgStub);
  SAFE_DELETE_OBJECT(shaderStub);
}

TEST(Material, deserialize) {
  auto jraw = std::string(R"({
    "techniques": [{
      "name": "main",
      "viewport": {
        "offset": [0.0, 0.0],
        "extent": [1.0, 1.0]
      },
      "impl": {
        "passes": [<PASSES_1>]
      }
    }, {
      "name": "next",
      "impl": {
        "passes": [<PASSES_2>]
      }
    }]
  })");

  jraw = toRawString(jraw, "<PASSES_1>", PassJsonTest);
  jraw = toRawString(jraw, "<PASSES_2>", "");
  auto jdata = nlohmann::json::parse(jraw);

  auto mtrl = render::experience::MaterialDeserializer::deserialize(jdata);
}
