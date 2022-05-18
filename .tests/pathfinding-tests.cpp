#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <vector>

#include "../a-star/graph.hpp"
#include "../a-star/pathfinding.hpp"

TEST_CASE("pathfinding tests")
{
	constexpr double max_error = 1e-8;

    Point a,b;
    std::vector<Circle> c;
    Graph graph;

    SUBCASE("Example in the picture")
    {
        a = {-3, 1};   b = {4.25, 0};
        c = { {0.0, 0.0, 2.5}, {1.5, 2.0, 0.5}, {3.5, 1.0, 1.0}, {3.5, -1.7, 1.2} };
        CHECK(std::abs(shortest_path_length(a, b, c, graph) - 9.11821650244) < max_error);
    }
    
    SUBCASE("Long way round")
    {
        a = {0, 1};  b = {0, -1};
        c = { {0.0, 0.0, 0.8}, {3.8, 0.0, 3.2}, {-3.5, 0.0, 3.0}, {-7.0, 0.0, 1.0} };
        CHECK(std::abs(shortest_path_length(a, b, c, graph) - 19.0575347577) < max_error);
    }
    
    SUBCASE("Straight line")
    {
        a = { 3, 0 };   b = { 0, 4 };
        c = { {0, 0, 1} };
        CHECK(std::abs(shortest_path_length(a, b, c, graph) - 5.0) < max_error);
    }
  
     SUBCASE("No way through")
     {
       a = {0, 0};  b = {20, 20};
       c = { {4, 0, 3}, {-4, 0, 3}, {0, 4, 3}, {0, -4, 3} };
       CHECK(std::abs(shortest_path_length(a, b, c, graph) - (-1.0)) < max_error);
     }
 
     SUBCASE("Simple test #0")
     {
         a = { 0, 1 };  b = { 0, -1 };
         c = { {0.0, 0.0, 0.8}, {-3.8, 0.0, 3.2}, {3.5, 0.0, 3.0}, {7.0, 0.0, 1.0} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - 19.0575347577) < max_error);
     }
     SUBCASE("Simple test #1")
     {
         a = { 0, -7 };  b = { 8, 8 };
         c = { };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - 17.0) < max_error);
     }
     SUBCASE("Simple test #2")
     {
         a = { -3.5, 0.1 };  b = { 3.5, 0.0 };
         double r = 2.01;
         c = { {0,0,1}, {r, 0.0, 1.0}, {r * 0.5, r * sqrt(3) / 2, 1.0}, {-r * 0.5, r * sqrt(3) / 2, 1.0},
                       {-r, 0.0, 1.0}, {r * 0.5, -r * sqrt(3) / 2, 1.0}, {-r * 0.5, -r * sqrt(3) / 2, 1.0} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - 7.80758072818) < max_error);
     }
     SUBCASE("Start in forbidden zone")
     {
         a = { 0.5, 0.5 };  b = { 2, 2 };
         c = { {0, 0, 1} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - (-1.0)) < max_error);
     }
   
     SUBCASE("End in forbidden zone")
     {
         a = { 2, 2 };  b = { 0.5, 0.5 };
         c = { {0, 0, 1} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - (-1.0)) < max_error);
     }
}