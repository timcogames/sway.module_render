#ifndef SWAY_GRAPHICS_MATERIAL_HPP
#define SWAY_GRAPHICS_MATERIAL_HPP

#include <sway/graphics/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Material {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] infoSet Первоначальная информация о материале.
   */
  Material(const gapi::ShaderCreateInfoSet &infoSet);

  ~Material() = default;

  void loadFromXml();

  /**
   * @brief Привязывает.
   */
  void bind();

  /**
   * @brief Отвязывает.
   */
  void unbind();

  auto getShaderProgram() -> gapi::ShaderProgramRef_t { return shaderProgram_; }

private:
  gapi::ShaderProgramRef_t shaderProgram_;  // Указатель на шейдерную программу.
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_MATERIAL_HPP
