#ifndef SWAY_RENDER_EFFECT_HPP
#define SWAY_RENDER_EFFECT_HPP

#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Effect {
public:
#pragma region "Static methods"

  static auto create(const gapi::ShaderCreateInfoSet &infoSet) -> EffectTypedefs::Ptr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] infoSet Первоначальная информация о шейдере.
   */
  Effect(global::GapiPluginFunctionSet *plug, const gapi::ShaderCreateInfoSet &infoSet);

  DTOR(Effect);

#pragma endregion

#pragma region "Binding/Unbinding"

  /**
   * @brief Привязывает.
   */
  void bind();

  /**
   * @brief Отвязывает.
   */
  void unbind();

#pragma endregion

#pragma region "Getters/Setters"

  auto getShaderProgram() -> gapi::ShaderProgramPtr_t { return program_; }

#pragma endregion

protected:
  global::GapiPluginFunctionSet *gapiPlugin_;

private:
  gapi::ShaderProgramPtr_t program_;  // Указатель на шейдерную программу.
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EFFECT_HPP
