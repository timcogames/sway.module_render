#ifndef SWAY_RENDER_UPDATABLE_HPP
#define SWAY_RENDER_UPDATABLE_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

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

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_UPDATABLE_HPP
