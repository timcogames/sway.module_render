#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/mtrl/material.hpp>
#include <sway/render/mtrl/materialdeserializer.hpp>

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

NS_SHORT_SWAY()

TEST(Material, add_effect) {
  const std::unordered_map<gapi::ShaderType::Enum, std::string> sources = {
      {gapi::ShaderType::Enum::VERT, "layout (location = 0) in vec3 vtx_pos_attrib;"
                                     "layout (location = 1) in vec4 vtx_col_attrib;"
                                     "out vec4 vtx_col;"
                                     "void main() {"
                                     "    gl_Position = vec4(vtx_pos_attrib, 1.0);"
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

TEST(Material, json) {
  auto data = nlohmann::json::parse(R"({
    "techniques": [{
      "name": "main",
      "viewport": {
        "offset": [0.0, 0.0],
        "extent": [1.0, 1.0]
      },
      "impl": {
        "passes": [{
          "id": 0,
          "clear_color" : [0.0, 0.0, 0.0, 1.0],
          "clear_flags" : ["CLEAR_COLOR", "CLEAR_DEPTH"],
          "shader": {
            "path": "file_path",
            "name": "file_name",
            "test": [".vert", ".frag"],
            "defs": ["TEST_1", "TEST_2", "TEST_3"],
            "samplers": [{
              "path": "file_path",
              "name": "file_name",
              "test": ".png"
            }]
          },
          "target_layer" : 0,
          "target": {}
        }]
      }
    }, {
      "name": "next",
      "impl": {
        "passes": []
      }
    }]
  })");

  auto mtrl = render::experience::MaterialDeserializer::deserialize(data);
}
