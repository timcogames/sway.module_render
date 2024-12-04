
#ifndef TECHNIQUE_JDATA_H
#define TECHNIQUE_JDATA_H

#include <sway/core.hpp>

NS_SHORT_SWAY()

constexpr lpcstr_t TechniqueJsonTest = R"({
      "name": "main",
      "viewport": {
        "offset": [0.0, 0.0],
        "extent": [1.0, 1.0]
      },
      "impl": {
        "passes": [<PASSES_1>]
      }
    })";

#endif  // TECHNIQUE_JDATA_H
