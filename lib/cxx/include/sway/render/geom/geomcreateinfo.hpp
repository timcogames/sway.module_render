#ifndef SWAY_RENDER_GEOMCREATEINFO_HPP
#define SWAY_RENDER_GEOMCREATEINFO_HPP

#include <sway/gapi/buffercreateinfo.hpp>
#include <sway/gapi/topologytypes.hpp>
#include <sway/namespacemacros.hpp>

namespace sway::render {

struct Constants {
  static constexpr std::size_t MAX_VERTEX_ATTRIBS{16};
  static constexpr std::size_t MAX_BUFFER_OBJECTS{80};

  static constexpr std::size_t MAX_IDX_BUFFERS{2};
  static constexpr int IDX_VBO{0};
  static constexpr int IDX_EBO{1};

  static constexpr std::size_t MAX_NUM_INSTANCES{120};
};

struct GeomCreateInfo {
  bool indexed;
  gapi::TopologyType::Enum topology;
  std::array<gapi::BufferCreateInfo, Constants::MAX_IDX_BUFFERS> bo{};

  GeomCreateInfo()
      : indexed(false)
      , topology(gapi::TopologyType::Enum::NONE) {
    bo[Constants::IDX_VBO].desc.target = gapi::BufferTarget::Enum::ARRAY;
    bo[Constants::IDX_EBO].desc.target = gapi::BufferTarget::Enum::ELEMENT_ARRAY;
  }
};

}  // namespace sway::render

#endif  // SWAY_RENDER_GEOMCREATEINFO_HPP
