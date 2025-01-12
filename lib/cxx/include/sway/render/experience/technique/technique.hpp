#ifndef SWAY_RENDER_EXPERIENCE_TECHNIQUE_HPP
#define SWAY_RENDER_EXPERIENCE_TECHNIQUE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>

namespace sway::render {
NS_BEGIN(experience)

class Technique {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Technique(const std::string &name);

  DTOR_DEFAULT(Technique);

  /** @} */
#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] auto getPasses() const -> const PassCacheTypedefs::UniquePtr_t & { return passes_; }

#pragma endregion

private:
  PassCacheTypedefs::UniquePtr_t passes_;
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_TECHNIQUE_HPP
