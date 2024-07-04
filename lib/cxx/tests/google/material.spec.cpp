#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/material.hpp>

#include <gtest/gtest.h>

using namespace sway;

TEST(Material, addEffect) {
  const std::unordered_map<gapi::ShaderType, std::string> sources = {
      {gapi::ShaderType::VERT, "layout (location = 0) in vec3 vtx_pos_attrib;"
                               "layout (location = 1) in vec4 vtx_col_attrib;"
                               "out vec4 vtx_col;"
                               "void main() {"
                               "    gl_Position = vec4(vtx_pos_attrib, 1.0);"
                               "    vtx_col = vtx_col_attrib;"
                               "}"},
      {gapi::ShaderType::FRAG, "in vec4 vtx_col;"
                               "out vec4 out_col;"
                               "void main() {"
                               "    out_col = vtx_col;"
                               "}"}};

  auto mtrl = std::make_shared<render::Material>("test_1", nullptr, nullptr);
  // mtrl->addEffect(sources);
}
