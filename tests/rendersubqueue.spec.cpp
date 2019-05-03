#include <boost/test/unit_test.hpp>
#include <memory> // std::shared_ptr, std::make_shared

#include <sway/core.h>
#include <sway/graphics.h>

using namespace sway;

#pragma region "Auto test suite"

BOOST_AUTO_TEST_SUITE(RenderSubqueue_TestSuite)

/*!
 * \brief
 *    Убеждаемся, что конструктор устанавливает все значения свойств в те, 
 *    которые были заданы.
 */
BOOST_AUTO_TEST_CASE(RenderSubqueue_TestCase_ComponentConstructor) {
	graphics::RenderSubqueue subqueue(graphics::RenderSubqueueGroup_t::kTransparent);
	BOOST_CHECK(subqueue.getGroup() == graphics::RenderSubqueueGroup_t::kTransparent);
}

BOOST_AUTO_TEST_SUITE_END()

#pragma endregion

#pragma region "Fixture test suite"

BOOST_FIXTURE_TEST_SUITE(RenderSubqueue_FixtureTestSuite, graphics::RenderSubqueue)

/*!
 * \brief
 *    Убеждаемся, что конструктор приводит свойства к значению по умолчанию.
 */
BOOST_AUTO_TEST_CASE(RenderSubqueue_TestCase_DefaultConstructor) {
	BOOST_CHECK(getGroup() == graphics::RenderSubqueueGroup_t::kOpaque);
}

/*!
 * \brief
 *    Убеждаемся, что установка всех свойств подочереди проходит правильно.
 */
BOOST_AUTO_TEST_CASE(RenderSubqueue_TestCase_Setters) {
	setGroup(graphics::RenderSubqueueGroup_t::kTransparent);
	BOOST_CHECK(getGroup() == graphics::RenderSubqueueGroup_t::kTransparent);
}

BOOST_AUTO_TEST_SUITE_END()

#pragma endregion
