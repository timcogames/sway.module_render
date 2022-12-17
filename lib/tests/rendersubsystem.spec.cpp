#include <sway/core.hpp>
#include <sway/core/intrusive/priorities.hpp>
#include <sway/graphics.hpp>

#include <boost/test/unit_test.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

class RenderSubsystemFixture : public core::foundation::Context {
public:
  RenderSubsystemFixture() {
    char path[PATH_MAX + 1];
    strncpy(path, "/home/bonus85/Projects/sway.modules/sway.module_graphics/bin", PATH_MAX);
    std::string plugname = core::misc::format("%s/module_gapi_dummy.so.0.1.0", path);

    _subsystem = std::make_shared<graphics::RenderSubsystem>(plugname, this);
    BOOST_CHECK_NO_THROW(registerObject(_subsystem.get()));
  }

  virtual ~RenderSubsystemFixture() {
    // Empty
  }

private:
  std::shared_ptr<graphics::RenderSubsystem> _subsystem;
};

BOOST_FIXTURE_TEST_SUITE(RenderSubsystem_FixtureTestSuite, RenderSubsystemFixture);

BOOST_AUTO_TEST_CASE(RenderSubsystemFixture_TestCase) {
  auto queue_h = static_cast<graphics::RenderSubsystem *>(getObject("RenderSubsystem"))->createQueue();
  queue_h->setPriority(core::intrusive::kPriority_High);
  queue_h->addSubqueue(std::make_shared<graphics::RenderSubqueue>());
  auto subqueueGroup_h = queue_h->getSubqueues(graphics::RenderSubqueueGroup::TRANSPARENT);

  auto queue_l = static_cast<graphics::RenderSubsystem *>(getObject("RenderSubsystem"))->createQueue();
  queue_l->setPriority(core::intrusive::kPriority_Low);
  queue_l->addSubqueue(std::make_shared<graphics::RenderSubqueue>());
  auto subqueueGroup_l = queue_l->getSubqueues(graphics::RenderSubqueueGroup::TRANSPARENT);

  auto queue_n = static_cast<graphics::RenderSubsystem *>(getObject("RenderSubsystem"))->createQueue();
  queue_n->setPriority(core::intrusive::kPriority_Normal);
  queue_n->addSubqueue(std::make_shared<graphics::RenderSubqueue>());
  auto subqueueGroup_n = queue_n->getSubqueues(graphics::RenderSubqueueGroup::TRANSPARENT);

  auto unsortedQueues = static_cast<graphics::RenderSubsystem *>(getObject("RenderSubsystem"))->getQueues();
  BOOST_CHECK_EQUAL(unsortedQueues.size(), size_t(3));

  static_cast<graphics::RenderSubsystem *>(getObject("RenderSubsystem"))->sortQueues();

  auto sortedQueues = static_cast<graphics::RenderSubsystem *>(getObject("RenderSubsystem"))->getQueues();
  BOOST_CHECK(std::is_sorted(sortedQueues.begin(), sortedQueues.end(),
                  graphics::RenderQueue::PriorityInDescendingOrder()) == true);
}

BOOST_AUTO_TEST_SUITE_END();
