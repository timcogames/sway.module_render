#ifndef SWAY_RENDER_UPDATABLE_HPP
#define SWAY_RENDER_UPDATABLE_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Updatable {
public:
  PURE_VIRTUAL(void update());
};

class BeforeUpdatable {
public:
  PURE_VIRTUAL(void beforeUpdate());
};

class AfterUpdatable {
public:
  PURE_VIRTUAL(void afterUpdate());
};

class FinalUpdatable {
public:
  PURE_VIRTUAL(void finalUpdate());
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_UPDATABLE_HPP
