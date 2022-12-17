#include <sway/core.hpp>
#include <sway/graphics.hpp>

#include <boost/test/unit_test.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

#pragma region "Auto test suite"

BOOST_AUTO_TEST_SUITE(RenderQueue_AutoTestSuite)

/*!
 * \brief
 *    Убеждаемся, что конструктор устанавливает все значения свойств в те,
 *    которые были заданы.
 */
BOOST_AUTO_TEST_CASE(RenderQueue_TestCase_ComponentConstructor) {
  graphics::RenderQueue queue(core::intrusive::kPriority_High);
  BOOST_CHECK_EQUAL(queue.getPriority(), core::intrusive::kPriority_High);
}

BOOST_AUTO_TEST_SUITE_END()

#pragma endregion

#pragma region "Fixture test suite"

BOOST_FIXTURE_TEST_SUITE(RenderQueue_FixtureTestSuite, graphics::RenderQueue)

/*!
 * \brief
 *    Убеждаемся, что конструктор приводит свойства к значению по умолчанию.
 */
BOOST_AUTO_TEST_CASE(RenderQueue_TestCase_DefaultConstructor) {
  BOOST_CHECK_EQUAL(getPriority(), core::intrusive::kPriority_Normal);
}

/*!
 * \brief
 *    Убеждаемся, что установка всех свойств очереди проходит правильно.
 */
BOOST_AUTO_TEST_CASE(RenderQueue_TestCase_Setters) {
  setPriority(core::intrusive::kPriority_VeryLow);
  BOOST_CHECK_EQUAL(getPriority(), core::intrusive::kPriority_VeryLow);
}

/*!
 * \brief
 *    Убеждаемся, что добавление и удаление подочередей проходит правильно.
 */
BOOST_AUTO_TEST_CASE(RenderQueue_TestCase_Subqueues) {
  graphics::RenderSubqueueRefVec_t opaqueGroup, transparentGroup;

  BOOST_CHECK(getSubqueues(graphics::RenderSubqueueGroup::OPAQUE).empty());

  addSubqueue(std::make_shared<graphics::RenderSubqueue>());
  addSubqueue(std::make_shared<graphics::RenderSubqueue>());
  opaqueGroup = getSubqueues(graphics::RenderSubqueueGroup::OPAQUE);
  BOOST_CHECK_EQUAL(opaqueGroup.size(), 2);

  removeSubqueue(opaqueGroup[0]);
  opaqueGroup = getSubqueues(graphics::RenderSubqueueGroup::OPAQUE);
  BOOST_CHECK_EQUAL(opaqueGroup.size(), 1);

  BOOST_CHECK(getSubqueues(graphics::RenderSubqueueGroup::TRANSPARENT).empty());

  addSubqueue(std::make_shared<graphics::RenderSubqueue>(graphics::RenderSubqueueGroup::TRANSPARENT));
  transparentGroup = getSubqueues(graphics::RenderSubqueueGroup::TRANSPARENT);
  BOOST_CHECK_EQUAL(transparentGroup.size(), 1);

  removeSubqueue(transparentGroup[0]);
  transparentGroup = getSubqueues(graphics::RenderSubqueueGroup::TRANSPARENT);
  BOOST_CHECK_EQUAL(transparentGroup.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

#pragma endregion
