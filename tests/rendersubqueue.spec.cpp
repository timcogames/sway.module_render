#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>

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
	graphics::RenderSubqueue subqueue(graphics::kRenderSubqueueGroup_Transparent);
	BOOST_CHECK_EQUAL(subqueue.getGroupIdx(), graphics::kRenderSubqueueGroup_Transparent);
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
	BOOST_CHECK_EQUAL(getGroupIdx(), graphics::kRenderSubqueueGroup_Opaque);
}

/*!
 * \brief
 *    Убеждаемся, что установка всех свойств подочереди проходит правильно.
 */
BOOST_AUTO_TEST_CASE(RenderSubqueue_TestCase_Setters) {
	BOOST_CHECK_NO_THROW(setGroupIdx(graphics::kRenderSubqueueGroup_Transparent));
	BOOST_CHECK_EQUAL(getGroupIdx(), graphics::kRenderSubqueueGroup_Transparent);
}

BOOST_AUTO_TEST_SUITE_END()

#pragma endregion
