#ifndef PASS_JDATA_H
#define PASS_JDATA_H

#include <sway/core.hpp>

NS_SHORT_SWAY()

inline auto toRawString(std::string const &in, std::string const marker, std::string const &content) -> std::string {
  auto ret = in;
  auto pos = ret.find(marker);
  if (pos != ret.npos) {
    ret.replace(pos, marker.length(), content);
  }

  return ret;
}

constexpr lpcstr_t PassJsonTest = R"({
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
  })";

#endif  // PASS_JDATA_H
