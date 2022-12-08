#ifndef SWAY_GRAPHICS_VERTEXCHANNEL_HPP
#define SWAY_GRAPHICS_VERTEXCHANNEL_HPP

#include <sway/core.hpp>
#include <sway/graphics/prereqs.hpp>
#include <sway/keywords.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class IVertexChannelBase {
public:
  /**
   * @brief Виртуальный деструктор класса.
   */
  virtual ~IVertexChannelBase() = default;

  PURE_VIRTUAL(void addAnyData(f32_t *data, int &capacity));

  // clang-format off
  PURE_VIRTUAL(auto getData(u32_t idx) const -> f32_t);  // clang-format on

  // clang-format off
  PURE_VIRTUAL(auto getVertCount() const -> s32_t);  // clang-format on

  // clang-format off
  PURE_VIRTUAL(auto getVertexAttribDescriptor() -> gapi::VertexAttributeDescriptor);  // clang-format on
};

template <typename TAttributeFormatType>
class TVertexChannel : public IVertexChannelBase {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  TVertexChannel(gapi::VertexSemantic_t semantic, std::size_t reserve = 8);

  /**
   * @brief Деструктор класса.
   */
  virtual ~TVertexChannel() = default;

  MTHD_OVERRIDE(void addAnyData(f32_t *data, int &capacity));

  // clang-format off
  MTHD_OVERRIDE(auto getData(u32_t idx) const -> f32_t);  // clang-format on

  // clang-format off
  MTHD_OVERRIDE(auto getVertCount() const -> s32_t) {  // clang-format on
    return vertexCount_;
  }
  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttribDescriptor() -> gapi::VertexAttributeDescriptor) {  // clang-format on
    return descriptor_;
  }

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
  f32_t *vertexData_;  // Набор данных.
  s32_t vertexCount_;
};

#include <sway/graphics/vertexchannel.inl>

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_VERTEXCHANNEL_HPP
