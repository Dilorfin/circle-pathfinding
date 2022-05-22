#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../a-star/graph.hpp"
#include "../a-star/math.hpp"

TEST_CASE("graph tests")
{
	const std::vector<Point> points = { {10, 10},{0, 1},{10.5, 10} };
	SUBCASE("graph size should be equal to number of inserted points (in constructor)")
	{
		Graph graph(points);

		REQUIRE(graph.size() == points.size());
	}

	SUBCASE("graph ctr throws when has points duplications")
	{
		const std::vector<Point> tempPoints = { {10, 10},{0, 1},{10.5, 10}, {10, 10} };
		auto func = [&]{ Graph graph(tempPoints);};
		REQUIRE_THROWS(func());
	}

	SUBCASE("graph size should be equal to number of inserted points (per point)")
	{
		Graph graph;
		for (const auto& point : points)
		{
			graph.addVertex(point);
		}
		REQUIRE(graph.size() == points.size());
	}

	SUBCASE("vertexes vector should be equal to inserted vector")
	{
		const Graph graph(points);
		const auto& vertexes = graph.getVertexes();

		CHECK(vertexes.size() == points.size());

		for (int i = 0; i < vertexes.size(); i++)
		{
			REQUIRE(points[i].x == doctest::Approx(vertexes[i].x).epsilon(max_error));
			REQUIRE(points[i].y == doctest::Approx(vertexes[i].y).epsilon(max_error));
		}
	}

	SUBCASE("vertexes should be equal to inserted vector (by getter)")
	{
		const Graph graph(points);

		for (int i = 0; i < graph.size(); i++)
		{
			REQUIRE(points[i].x == doctest::Approx(graph.getVertex(i).x).epsilon(max_error));
			REQUIRE(points[i].y == doctest::Approx(graph.getVertex(i).y).epsilon(max_error));
		}
	}

	SUBCASE("initial weights should be zeros")
	{
		const Graph graph(points);

		for (int x = 0; x < graph.size(); x++)
		{
			for (int y = 0; y < graph.size(); y++)
			{
				REQUIRE(graph.getWeight(x, y) == doctest::Approx(0).epsilon(max_error));
			}
		}
	}

	SUBCASE("weights should be setted")
	{
		Graph graph(points);
		constexpr double weight = 0.42;

		graph.setWeight(0, 1, weight);
		REQUIRE(graph.getWeight(0, 1) == doctest::Approx(weight).epsilon(max_error));
	}

	SUBCASE("weights should be setted symetrycaly")
	{
		Graph graph(points);
		constexpr double weight = 0.42;
		constexpr size_t x = 0;
		constexpr size_t y = 2;
		graph.setWeight(x, y, weight);

		REQUIRE(graph.getWeight(x, y) == doctest::Approx(weight).epsilon(max_error));
		REQUIRE(graph.getWeight(y, x) == doctest::Approx(weight).epsilon(max_error));
	}

	SUBCASE("setting weight should affect only two cells")
	{
		Graph graph(points);
		constexpr double weight = 0.42;
		constexpr size_t x = 0;
		constexpr size_t y = 2;
		graph.setWeight(x, y, weight);

		for (int i = 0; i < graph.size(); i++)
		{
			for (int j = 0; j < graph.size(); j++)
			{
				if ((i == x && j == y) || (i == y && j == x))
					continue;

				INFO("i: ", i);
				INFO("j: ", j);
				REQUIRE(graph.getWeight(i, j) != doctest::Approx(weight).epsilon(max_error));
			}
		}
	}
}