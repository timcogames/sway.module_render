#ifndef SWAY_RENDER_EFFECT_HPP
#define SWAY_RENDER_EFFECT_HPP

#include <sway/render/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class Effect {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] infoSet Первоначальная информация о материале.
   */
  Effect(const gapi::ShaderCreateInfoSet &infoSet);

  ~Effect() = default;

  /**
   * @brief Привязывает.
   */
  void bind();

  /**
   * @brief Отвязывает.
   */
  void unbind();

  auto getShaderProgram() -> gapi::ShaderProgramRef_t { return program_; }

private:
  gapi::ShaderProgramRef_t program_;  // Указатель на шейдерную программу.
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_EFFECT_HPP
