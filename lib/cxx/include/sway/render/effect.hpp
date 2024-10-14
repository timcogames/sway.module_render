#ifndef SWAY_RENDER_EFFECT_HPP
#define SWAY_RENDER_EFFECT_HPP

#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Effect {
  DECLARE_PTR_ALIASES(Effect)

public:
  static auto create(const gapi::ShaderCreateInfoSet &infoSet) -> Effect::Ptr_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] infoSet Первоначальная информация о материале.
   */
  Effect(global::GapiPluginFunctionSet *plug, const gapi::ShaderCreateInfoSet &infoSet);

  ~Effect();

  /**
   * @brief Привязывает.
   */
  void bind();

  /**
   * @brief Отвязывает.
   */
  void unbind();

  auto getShaderProgram() -> gapi::ShaderProgramPtr_t { return program_; }

protected:
  global::GapiPluginFunctionSet *gapiPlugin_;

private:
  gapi::ShaderProgramPtr_t program_;  // Указатель на шейдерную программу.
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EFFECT_HPP
