#ifndef SWAY_GRAPHICS_VERTEXDATACHANNEL_HPP
#define SWAY_GRAPHICS_VERTEXDATACHANNEL_HPP

#include <sway/core.hpp>
#include <sway/graphics/prereqs.hpp>
#include <sway/keywords.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

template <typename TValueData>
class VertexDataChannel {
public:
  VertexDataChannel(gapi::VertexSemantic_t semantic)
      : descriptor_(gapi::VertexAttribute::merge<TValueData>(semantic, false, true)) {}

  ~VertexDataChannel() = default;

private:
  gapi::VertexAttributeDescriptor descriptor_;
  void *data_;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_VERTEXDATACHANNEL_HPP
