#ifndef SWAY_RENDER_UPDATABLE_HPP
#define SWAY_RENDER_UPDATABLE_HPP

namespace sway::render {

class Updatable {
public:
  virtual void update() = 0;
};

class BeforeUpdatable {
public:
  virtual void beforeUpdate() = 0;
};

class AfterUpdatable {
public:
  virtual void afterUpdate() = 0;
};

class FinalUpdatable {
public:
  virtual void finalUpdate() = 0;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_UPDATABLE_HPP
