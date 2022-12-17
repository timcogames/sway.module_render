#ifndef SWAY_GRAPHICS_VERTEXDATA_HPP
#define SWAY_GRAPHICS_VERTEXDATA_HPP

#include <sway/core.hpp>
#include <sway/graphics/prereqs.hpp>
#include <sway/graphics/vertexchannel.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class VertexData {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  VertexData();

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] count Количество вершин.
   */
  VertexData(s32_t count);

  ~VertexData() = default;

  template <typename TAttributeFormatType>
  auto createChannel(gapi::VertexSemantic_t semantic, u32_t count) -> VertexChannelRef_t;

  auto getChannels() -> VertexChannelRefMap_t { return channels_; }

  auto getChannel(gapi::VertexSemantic_t semantic) -> VertexChannelRef_t { return channels_[semantic]; }

  [[nodiscard]] auto getVertexCount() const -> s32_t { return vertexCount_; }

  auto getRaw() -> void *;

  void addTriIndices(u32_t a, u32_t b, u32_t c);

  void addIndex(u32_t index);

  auto getIndices() -> std::vector<u32_t> & { return indices_; }

  [[nodiscard]] auto getIndexCount() const -> u32_t { return indices_.size(); }

private:
  VertexChannelRefMap_t channels_;
  s32_t vertexCount_;
  std::vector<u32_t> indices_;
};

#include <sway/graphics/vertexdata.inl>

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_VERTEXDATA_HPP
