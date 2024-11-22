#ifndef SWAY_RENDER_EXPERIENCE_PIPELINE_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINE_HPP

#include <sway/render/experience/base/disposable.hpp>
#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Pipeline : public Disposable {
public:
#pragma region "Ctors/Dtor"

  Pipeline();

  DTOR_VIRTUAL_DEFAULT(Pipeline);

#pragma endregion

  void initialize();

#pragma region "Override Disposable methods"

  MTHD_OVERRIDE(void dispose());

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] inline auto passes() const -> const PassCacheTypedefs::UniquePtr_t & { return passes_; }

#pragma endregion

private:
  PassCacheTypedefs::UniquePtr_t passes_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINE_HPP
