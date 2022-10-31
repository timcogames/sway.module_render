#ifndef SWAY_GRAPHICS_VERTEXCHANNEL_HPP
#define SWAY_GRAPHICS_VERTEXCHANNEL_HPP

#include <sway/core.hpp>
#include <sway/graphics/prereqs.hpp>
#include <sway/keywords.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class IVertexChannelBase {
public:
  /*!
   * \brief
   *    Виртуальный деструктор класса.
   */
  virtual ~IVertexChannelBase() = default;

  PURE_VIRTUAL(void addAnyData(f32_t *data, int &capacity));

  PURE_VIRTUAL(f32_t getData(u32_t idx) const);

  PURE_VIRTUAL(s32_t getVertCount() const);

  PURE_VIRTUAL(gapi::VertexAttributeDescriptor getVertexAttribDescriptor());
};

template <typename TYPE>
class TVertexChannel : public IVertexChannelBase {
public:
  /*!
   * \brief
   *    Конструктор класса.
   *    Выполняет инициализацию нового экземпляра класса.
   */
  TVertexChannel(gapi::VertexSemantic_t semantic, std::size_t reserve = 8);

  /*!
   * \brief
   *    Деструктор класса.
   */
  virtual ~TVertexChannel() = default;

  MTHD_OVERRIDE(void addAnyData(f32_t *data, int &capacity));

  MTHD_OVERRIDE(f32_t getData(u32_t idx) const);

  MTHD_OVERRIDE(s32_t getVertCount() const);

  MTHD_OVERRIDE(gapi::VertexAttributeDescriptor getVertexAttribDescriptor());

private:
  void reallocate_(s32_t &capacity) {
    capacity = !capacity ? vertexReserve_ : capacity * 2;

    f32_t *tmp = new f32_t[capacity * descriptor_.numComponents];
    if (vertexCount_) {
      memcpy(tmp, vertexData_, vertexCount_ * descriptor_.stride);
    }

    SAFE_DELETE_ARRAY(vertexData_);

    vertexData_ = tmp;
  }

  gapi::VertexAttributeDescriptor descriptor_;
  std::size_t vertexReserve_;
  f32_t *vertexData_; /*!< Набор данных. */
  s32_t vertexCount_;
};

#include <sway/graphics/vertexchannel.inl>

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif
