#ifndef SWAY_RENDER_EFFECT_HPP
#define SWAY_RENDER_EFFECT_HPP

#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/effect/effectresourceimmutable.hpp>
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

  void reload(const std::string &name) {
    if (!immutable_) {
      immutable_ = std::make_shared<EffectResourceImmutable>();
    }

    immutable_->resource.name = std::move(name);
    immutable_->resource.hash = core::misc::hashValue(immutable_->resource.name);
    immutable_->timestamp = 0;
  }

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

  auto getNumMacros() const noexcept -> u32_t { return static_cast<u32_t>(immutable_->macros.size()); }

#pragma endregion

protected:
  global::GapiPluginFunctionSet *gapiPlugin_;

private:
  gapi::ShaderProgramPtr_t program_;  ///< Указатель на шейдерную программу.
  EffectResourceImmutableTypedefs::SharedPtr_t immutable_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EFFECT_HPP
