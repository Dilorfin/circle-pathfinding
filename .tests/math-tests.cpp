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
		const Point a(-2.3, 5.99);
		const Point b(-60.3, -8.3);
		const double result = dot(a, b);
		CHECK(88.973 == doctest::Approx(result).epsilon(max_error));
	}

	SUBCASE("angle between vectors ~76.8317deg")
	{
		const Point a(-2.3, 5.99);
		const Point b(-60.3, -8.3);
		const double result = angleBetweenVectors(a, b);
		CHECK(1.34096754 == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("angle between vectors 90deg")
	{
		const Point a(10, 0);
		const Point b(0, 10);
		const double result = angleBetweenVectors(a, b);
		CHECK(1.57079633 == doctest::Approx(result).epsilon(max_error));
	}
}

TEST_CASE("general math tests")
{
	SUBCASE("distance 5")
	{
		const Point a(1, 1);
		const Point b(4, 5);
		const double result = distance(a, b);
		CHECK(5 == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("distance 59.734446511205")
	{
		const Point a(-2.3, 5.99);
		const Point b(-60.3, -8.3);
		const double result = distance(a, b);
		CHECK(59.734446511205 == doctest::Approx(result).epsilon(max_error));
	}
	SUBCASE("distance 1.4142135623731")
	{
		const Point a(1, 1);
		const Point b(0, 0);
		const double result = distance(a, b);
		CHECK(1.4142135623731 == doctest::Approx(result).epsilon(max_error));
	}

	SUBCASE("equal points true")
	{
		const Point b(4, 5);
		CHECK(equal(b, b));
	}
	SUBCASE("equal points false")
	{
		const Point a(4.0001, 5);
		const Point b(4, 5);
		CHECK_FALSE(equal(a, b));
	}

	SUBCASE("arc length")
	{
		const Circle circle(0, 0, 5);
		const Point a(1, 1);
		const Point b(2, 2);
		const double angle = angleBetweenVectors(a, b);

		const double result = arcLength(circle, a, b);

		CHECK(angle * circle.r == doctest::Approx(result).epsilon(max_error));
	}
}

TEST_CASE("line exists tests")
{
	SUBCASE("line not exist one circle")
	{
		const std::vector<Circle> circles{ {0, 0, 5} };

		const Point a(-10, 0);
		const Point b(10, 0);

		CHECK_FALSE(lineExists(a, b, circles));
	}
	SUBCASE("line exist one circle")
	{
		const std::vector<Circle> circles{ {0, 10, 5} };

		const Point a(-10, 0);
		const Point b(10, 0);

		CHECK(lineExists(a, b, circles));
	}
	SUBCASE("line exist one circle border case")
	{
		const std::vector<Circle> circles{ { 25, 20, 5 } };

		const Point a(10, 20);
		const Point b(20, 20);

		CHECK(lineExists(a, b, circles));
	}
	SUBCASE("line not exist one circle border case")
	{
		const std::vector<Circle> circles{ { 25, 20, 5.000001 } };

		const Point a(10, 20);
		const Point b(20, 20);

		CHECK_FALSE(lineExists(a, b, circles));
	}

	const auto circlesGenerator = [](const size_t number)->std::vector<Circle>
	{
		std::vector<Circle> circles;
		circles.reserve(number);
		for (size_t i = 0; i < number; i++)
		{
			circles.emplace_back(10 * i, 10 * i, 3 * i);
		}
		return circles;
	};

	SUBCASE("line exist muliple circles")
	{
		const std::vector<Circle> circles = circlesGenerator(500);

		const Point a(-10, -20);
		const Point b(-20, -20);

		CHECK(lineExists(a, b, circles));
	}
	SUBCASE("line not exist muliple circles")
	{
		const std::vector<Circle> circles = circlesGenerator(500);

		const Point a = circles.back().ctr;
		const Point b(circles.back().ctr.x + 20, circles.back().ctr.y - 20);

		CHECK_FALSE(lineExists(a, b, circles));
	}
}

TEST_CASE("tangent line and circle")
{
	SUBCASE("test 1")
	{
		const Point a(0, 0);
		const Circle circle(10, 10, 10);

		const std::vector<Point> res = tangentLines(a, circle);

		REQUIRE(res.size() == 2);
		CHECK(10 == doctest::Approx(res[0].x).epsilon(max_error));
		CHECK(0 == doctest::Approx(res[0].y).epsilon(max_error));
		CHECK(0 == doctest::Approx(res[1].x).epsilon(max_error));
		CHECK(10 == doctest::Approx(res[1].y).epsilon(max_error));
	}

	SUBCASE("test 2")
	{
		const Point a(31.25, 0);
		const Circle circle(0, 0, 25);

		const std::vector<Point> res = tangentLines(a, circle);

		REQUIRE(res.size() == 2);
		CHECK(20 == doctest::Approx(res[0].x).epsilon(max_error));
		CHECK(15 == doctest::Approx(res[0].y).epsilon(max_error));
		CHECK(20 == doctest::Approx(res[1].x).epsilon(max_error));
		CHECK(-15 == doctest::Approx(res[1].y).epsilon(max_error));
	}

	SUBCASE("test 3")
	{
		const Point a(0, 31.25);
		const Circle circle(0, 0, 25);

		const std::vector<Point> res = tangentLines(a, circle);

		REQUIRE(res.size() == 2);
		CHECK(-15 == doctest::Approx(res[0].x).epsilon(max_error));
		CHECK(20 == doctest::Approx(res[0].y).epsilon(max_error));
		CHECK(15 == doctest::Approx(res[1].x).epsilon(max_error));
		CHECK(20 == doctest::Approx(res[1].y).epsilon(max_error));
	}

	SUBCASE("test 4")
	{
		const Point a(10, 10);
		const Circle circle(50, 50, 10);

		const std::vector<Point> res = tangentLines(a, circle);

		REQUIRE(res.size() == 2);
		CHECK(55.7097054535375 == doctest::Approx(res[0].x).epsilon(max_error));
		CHECK(41.7902945464625 == doctest::Approx(res[0].y).epsilon(max_error));
		CHECK(41.7902945464625 == doctest::Approx(res[1].x).epsilon(max_error));
		CHECK(55.7097054535375 == doctest::Approx(res[1].y).epsilon(max_error));
	}

	SUBCASE("test 5")
	{
		const Point a(10, 10);
		const Circle circle(-50, 50, 10);

		const std::vector<Point> res = tangentLines(a, circle);

		REQUIRE(res.size() == 2);
		CHECK(-43.3527473626593 == doctest::Approx(res[0].x).epsilon(max_error));
		CHECK(57.470878956011 == doctest::Approx(res[0].y).epsilon(max_error));
		CHECK(-54.3395603296484 == doctest::Approx(res[1].x).epsilon(max_error));
		CHECK(40.9906595055275 == doctest::Approx(res[1].y).epsilon(max_error));
	}

	SUBCASE("test 6")
	{
		const Point a(-113, 17);
		const Circle circle(1024, -2500, 5);

		const std::vector<Point> res = tangentLines(a, circle);

		REQUIRE(res.size() == 2);
		CHECK(1019.439625266714 == doctest::Approx(res[0].x).epsilon(max_error));
		CHECK(-2502.0501176288226 == doctest::Approx(res[0].y).epsilon(max_error));
		CHECK(1028.5529219844996 == doctest::Approx(res[1].x).epsilon(max_error));
		CHECK(-2497.933384069775 == doctest::Approx(res[1].y).epsilon(max_error));
	}
}

TEST_CASE("tangent circle and circle")
{
	SUBCASE("test 1")
	{
		const Circle A(6.6125714285714,1.306380952381, 1);
		const Circle B(-7.9765714285714,-3.4183809523809, 5.6);

		const std::vector<std::pair<Point, Point>> res = tangentLines(A, B);

		const std::vector<std::pair<Point, Point>> expected = {
			{ Point(-4.126273966625, -7.4847318293358), Point(5.9250183103665, 2.0325150375517) },
			{ Point(-7.2410558456096, 2.1331068506506), Point(6.4812293601853, 0.3150438446966) },
			{ Point(-8.0243947890834, 2.1814148408748), Point(6.6040315427657, 2.3063444868914) },
			{ Point(-4.7325753397895, -7.9830813123108), Point(7.1918564444255, 0.4912558881075) }
		};

		REQUIRE(res.size() == expected.size());

		for (const auto& expectedPair : expected)
		{
			CHECK(std::any_of(res.begin(), res.end(), [&](const std::pair<Point, Point>& p)->bool {
				return (equal(p.first, expectedPair.first) && equal(p.second, expectedPair.second))
					|| (equal(p.first, expectedPair.second) && equal(p.second, expectedPair.first));
			}));
		}
	}

	SUBCASE("test 2")
	{
		const Circle A(6.6125714285714,1.306380952381, 1.6);
		const Circle B(-7.9765714285714,-3.4183809523809, 40.6);

		const std::vector<std::pair<Point, Point>> res = tangentLines(A, B);
		
		REQUIRE(0 == res.size());
	}

	SUBCASE("test 3")
	{
		const Circle A(0, -25, 7);
		const Circle B(25, 0, 7);

		const std::vector<std::pair<Point, Point>> res = tangentLines(A, B);

		const std::vector<std::pair<Point, Point>> expected = {
			{ Point(27.5851512626079, -6.5051512626072), Point(-2.5851512626088, -18.4948487373905) },
			{ Point(18.494848737393, 2.5851512626078), Point(6.5051512626096, -27.5851512626088) },
			{ Point(20.0502525316964, 4.9497474683026), Point(-4.9497474683063, -20.0502525316948) },
			{ Point(29.9497474683024, -4.9497474683035), Point(4.9497474683051, -29.9497474683063) }
		};

		REQUIRE(res.size() == expected.size());

		for (const auto& expectedPair : expected)
		{
			CHECK(std::any_of(res.begin(), res.end(), [&](const std::pair<Point, Point>& p)->bool {
				return (equal(p.first, expectedPair.first) && equal(p.second, expectedPair.second))
					|| (equal(p.first, expectedPair.second) && equal(p.second, expectedPair.first));
			}));
		}
	}

	SUBCASE("test 4")
	{
		const Circle A(-23.788981056404,-12.286414432, 1.6);
		const Circle B(9.3681447619048,6.1178019047619, 42);

		const std::vector<std::pair<Point, Point>> res = tangentLines(A, B);

		REQUIRE(res.size() == 0);
	}

	SUBCASE("test 5")
	{
		const Circle A(0, 0, 0.3);
		const Circle B(19, 0, 0.3);

		const std::vector<std::pair<Point, Point>> res = tangentLines(A, B);

		const std::vector<std::pair<Point, Point>> expected = {
			{ Point(18.9905263157841, -0.2998503784958), Point(0.0094736842052, 0.2998503781581) },
			{ Point(18.9905263157841, 0.2998503784958), Point(0.0094736842052, -0.2998503781581) },
			{ Point(19.0000000000053, 0.2999999999209), Point(0.0000000000053, 0.2999999995825) },
			{ Point(19.0000000000053, -0.2999999999209), Point(0.0000000000053, -0.2999999995825) }
		};

		REQUIRE(res.size() == expected.size());

		for (const auto& expectedPair : expected)
		{
			CHECK(std::any_of(res.begin(), res.end(), [&](const std::pair<Point, Point>& p)->bool {
				return (equal(p.first, expectedPair.first) && equal(p.second, expectedPair.second))
					|| (equal(p.first, expectedPair.second) && equal(p.second, expectedPair.first));
			}));
		}
	}

	SUBCASE("test 6")
	{
		const Circle A(18.9990994611522,-13.2036074219616, 1);
		const Circle B(0.4065104827304,-0.4580090951249, 2);

		const std::vector<std::pair<Point, Point>> res = tangentLines(A, B);

		const std::vector<std::pair<Point, Point>> expected = {
			{ Point(18.3289399254399, -13.9458245038818), Point(1.7468295541569, 1.0264250687176) },
			{ Point(18.4708264328064, -14.0526819814218), Point(-0.6500355739629, -2.1561582140481) },
			{ Point(19.6005522629483, -12.4046990872875), Point(1.6094160863248, 1.1398075742264) },
			{ Point(19.449719676513, -12.3108916656829), Point(-0.4947299479927, -2.2434406076855) }
		};

		REQUIRE(res.size() == expected.size());

		for (const auto& expectedPair : expected)
		{
			CHECK(std::any_of(res.begin(), res.end(), [&](const std::pair<Point, Point>& p)->bool {
				return (equal(p.first, expectedPair.first) && equal(p.second, expectedPair.second))
					|| (equal(p.first, expectedPair.second) && equal(p.second, expectedPair.first));
			}));
		}
	}
}
