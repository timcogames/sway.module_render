#ifndef SWAY_GRAPHICS_VERTEXDATA_HPP
#define SWAY_GRAPHICS_VERTEXDATA_HPP

#include <sway/core.hpp>
#include <sway/graphics/prereqs.hpp>
#include <sway/graphics/vertexchannel.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class VertexData {
public:
  /*!
   * \brief
   *    Конструктор класса.
   *    Выполняет инициализацию нового экземпляра класса.
   */
  VertexData();

  /*!
   * \brief
   *    Конструктор класса.
   *    Выполняет инициализацию нового экземпляра класса.
   *
   * \param[in] count
   *    Количество вершин.
   */
  VertexData(u32_t count);

  /*!
   * \brief
   *    Деструктор класса.
   *    Освобождает захваченные ресурсы.
   */
  virtual ~VertexData();

  template <typename TYPE>
  VertexChannelRef_t createChannel(gapi::VertexSemantic_t semantic, u32_t count);

  VertexChannelRefMap_t getChannels();
  VertexChannelRef_t getChannel(gapi::VertexSemantic_t semantic);

  u32_t getVertexCount() const;

  void *getRaw();

  void addTriIndices(u32_t a, u32_t b, u32_t c);

  void addIndex(u32_t index);

  IndexVec_t &getIndices();

  u32_t getIndexCount() const;

private:
  VertexChannelRefMap_t _channels;
  u32_t _vertexCount;

  IndexVec_t _indices;
};

#include <sway/graphics/vertexdata.inl>

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif
