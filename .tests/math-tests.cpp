#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../a-star/math.hpp"

TEST_CASE("vector math tests")
{
	SUBCASE("vector func test 0")
	{
		const Point a(3, 4);
		const Point b(3, 4);
		const Point result = vector(a, b);
		CHECK(0 == doctest::Approx(result.x).epsilon(max_error));
		CHECK(0 == doctest::Approx(result.y).epsilon(max_error));
	}
	SUBCASE("vector func test 1")
	{
		const Point a(3, 4);
		const Point b(4, 3);
		const Point result = vector(a, b);
		CHECK(1 == doctest::Approx(result.x).epsilon(max_error));
		CHECK(-1 == doctest::Approx(result.y).epsilon(max_error));
	}

	SUBCASE("vector length 5")
	{
		const Point a(3, 4);
		const double result = length(a);
		CHECK(5 == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("vector length 17.029386365926403")
	{
		const Point a(11, 13);
		const double result = length(a);
		CHECK(17.029386365926403 == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("vector length 42.11721263331656")
	{
		const Point a(3.14, 42);
		const double result = length(a);
		CHECK(42.11721263331656 == doctest::Approx(result).epsilon(max_error));
	}

	SUBCASE("dot product 58")
	{
		const Point a(3, 5);
		const Point b(6, 8);
		const double result = dot(a, b);
		CHECK(58. == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("dot product -53.8")
	{
		const Point a(-2.3, 5);
		const Point b(6, -8);
		const double result = dot(a, b);
		CHECK(-53.8 == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("dot product 88.973")
	{
		const Point a(-2.3,5.99);
		const Point b(-60.3,-8.3);
		const double result = dot(a, b);
		CHECK(88.973 == doctest::Approx(result).epsilon(max_error));
	}
}

TEST_CASE("general math tests")
{
	SUBCASE("distance 5")
	{
		const Point a(1,1);
		const Point b(4,5);
		const double result = distance(a, b);
		CHECK(5 == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("distance 59.734446511205")
	{
		const Point a(-2.3,5.99);
		const Point b(-60.3,-8.3);
		const double result = distance(a, b);
		CHECK(59.734446511205 == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("distance 1.4142135623731")
	{
		const Point a(1,1);
		const Point b(0,0);
		const double result = distance(a, b);
		CHECK(1.4142135623731 == doctest::Approx(result).epsilon(max_error));
	}

	SUBCASE("equal points true")
	{
		const Point b(4,5);
		CHECK(equal(b, b));
	}
	SUBCASE("equal points false")
	{
		const Point a(4.0001,5);
		const Point b(4,5);
		CHECK_FALSE(equal(a, b));
	}
}

TEST_CASE("check line tests")
{
	SUBCASE("")
	{
		//REQUIRE();
	}
}
