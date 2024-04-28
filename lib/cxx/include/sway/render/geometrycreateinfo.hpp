#ifndef SWAY_RENDER_GEOMETRYCREATEINFO_HPP
#define SWAY_RENDER_GEOMETRYCREATEINFO_HPP

#include <sway/gapi/buffercreateinfo.hpp>
#include <sway/gapi/topologytypes.hpp>
#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct Constants {
  static constexpr std::size_t MAX_VERTEX_ATTRIBS{16};
  static constexpr std::size_t MAX_BUFFER_OBJECTS{80};

  static constexpr std::size_t MAX_IDX_BUFFERS{2};
  static constexpr int IDX_VBO{0};
  static constexpr int IDX_EBO{1};

  static constexpr std::size_t MAX_NUM_INSTANCES{120};
};

struct GeometryCreateInfo {
  bool indexed;
  gapi::TopologyType topology;
  std::array<gapi::BufferCreateInfo, Constants::MAX_IDX_BUFFERS> bo{};

  GeometryCreateInfo()
      : indexed(false)
      , topology(gapi::TopologyType::UNDEF) {
    bo[Constants::IDX_VBO].desc.target = gapi::BufferTarget::ARRAY;
    bo[Constants::IDX_EBO].desc.target = gapi::BufferTarget::ELEMENT_ARRAY;
  }
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRYCREATEINFO_HPP
