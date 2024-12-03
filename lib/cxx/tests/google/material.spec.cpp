#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/mtrl/material.hpp>
#include <sway/render/mtrl/materialdeserializer.hpp>

#include <google/pass.jdata.hpp>

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

NS_SHORT_SWAY()

TEST(Material, add_effect) {
  const std::unordered_map<gapi::ShaderType::Enum, std::string> sources = {
      {gapi::ShaderType::Enum::VERT, "layout (location = 0) in vec3 vtx_pos_attrib;"
                                     "layout (location = 1) in vec4 vtx_col_attrib;"
                                     "out vec4 vtx_col;"
                                     "void main() {"
                                     "    gl_Pos = vec4(vtx_pos_attrib, 1.0);"
                                     "    vtx_col = vtx_col_attrib;"
                                     "}"},
      {gapi::ShaderType::Enum::FRAG, "in vec4 vtx_col;"
                                     "out vec4 out_col;"
                                     "void main() {"
                                     "    out_col = vtx_col;"
                                     "}"}};

  auto mtrl = std::make_shared<render::Material>("test_1", nullptr, nullptr);
  // mtrl->addEffect(sources);
}

auto toRawString(std::string const &in, std::string const marker, std::string const &content) -> std::string {
  auto ret = in;
  auto pos = ret.find(marker);
  if (pos != ret.npos) {
    ret.replace(pos, marker.length(), content);
  }

  return ret;
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
        "passes": <PASSES_1>
      }
    }, {
      "name": "next",
      "impl": {
        "passes": <PASSES_2>
      }
    }]
  })");

  jraw = toRawString(jraw, "<PASSES_1>", PassJsonTest);
  jraw = toRawString(jraw, "<PASSES_2>", "[]");
  auto jdata = nlohmann::json::parse(jraw);

  auto mtrl = render::experience::MaterialDeserializer::deserialize(jdata);
}
