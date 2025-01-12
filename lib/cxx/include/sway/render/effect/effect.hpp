#ifndef SWAY_RENDER_EFFECT_HPP
#define SWAY_RENDER_EFFECT_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/_typedefs.hpp>
#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/effect/effectresourceimmutable.hpp>
#include <sway/render/global.hpp>

namespace sway::render {

class Effect {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto create(global::GapiPluginFunctionSet *plug, const gapi::ShaderCreateInfoSet &infoSet)
      -> EffectTypedefs::Ptr_t;

  /** @} */

#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  /**
   * \~english
   * @brief Constructor class. Performs initialization of a new instance of the class.
   * @param[in] plug Pointer to the plugin function set.
   *
   * \~russian
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   * @param[in] infoSet Первоначальная информация о шейдере.
   */
  Effect(global::GapiPluginFunctionSet *plug, const gapi::ShaderCreateInfoSet &infoSet);

  ~Effect();

  /** @} */
#pragma endregion

  void reload(const std::string &name) {
    if (!immutable_) {
      immutable_ = std::make_shared<EffectResourceImmutable>();
    }

    immutable_->resource.name = std::move(name);
    immutable_->resource.hash = core::hashValue(immutable_->resource.name);
    immutable_->timestamp = 0;
  }

#pragma region "Binding/Unbinding"

  /**
   * @brief \~english Performs binding of shader resources to corresponding slots. \~russian Выполняет привязку ресурсов
   * шейдера к соответствующим слотам.
   *
   * @sa unbind()
   */
  void bind();

  /**
   * \~english
   * @brief Performs unbinding of shader resources.
   * @note If the shader resource is already unbound, then this method has no effect.
   *
   * \~russian
   * @brief Выполняет отвязку ресурсов шейдера.
   * @note Если ресурс шейдера уже отвязан, то данный метод не имеет эффекта.
   *
   * \~
   * @sa bind()
   */
  void unbind();

#pragma endregion

#pragma region "Getters/Setters"

  auto getShaderProgram() -> gapi::typedefs::ShaderProgramPtr_t { return program_; }

  auto getNumMacros() const noexcept -> u32_t { return static_cast<u32_t>(immutable_->macros.size()); }

#pragma endregion

protected:
  global::GapiPluginFunctionSet *gapiPlugin_;

private:
  gapi::typedefs::ShaderProgramPtr_t program_; /*!< \~english Pointer to shader program.
    \~russian Указатель на шейдерную программу. */
  EffectResourceImmutableTypedefs::SharedPtr_t immutable_;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_EFFECT_HPP
