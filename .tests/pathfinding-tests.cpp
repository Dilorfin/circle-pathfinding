#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <vector>

#include "../a-star/graph.hpp"
#include "../a-star/pathfinding.hpp"

TEST_CASE("pathfinding tests")
{

    SUBCASE("Example in the picture")
    {
        Graph graph;
        Point a = {-3, 1}; 
        Point b = {4.25, 0};
        std::vector<Circle> c = { {0.0, 0.0, 2.5}, {1.5, 2.0, 0.5}, {3.5, 1.0, 1.0}, {3.5, -1.7, 1.2} };
        CHECK(std::abs(shortest_path_length(a, b, c, graph) - 9.11821650244) < max_error);
    }
    
    SUBCASE("Long way round")
    {
        Graph graph;
        Point a = {0, 1};
        Point b = {0, -1};
        std::vector<Circle> c = { {0.0, 0.0, 0.8}, {3.8, 0.0, 3.2}, {-3.5, 0.0, 3.0}, {-7.0, 0.0, 1.0} };
        CHECK(std::abs(shortest_path_length(a, b, c, graph) - 19.0575347577) < max_error);
    }
    
    SUBCASE("Straight line")
    {
        Graph graph;
        Point a = { 3, 0 };   
        Point b = { 0, 4 };
        std::vector<Circle> c = { {0, 0, 1} };
        CHECK(std::abs(shortest_path_length(a, b, c, graph) - 5.0) < max_error);
    }
  
     SUBCASE("No way through")
     {
         Graph graph;
         Point a = {0, 0}; 
         Point b = {20, 20};
         std::vector<Circle> c = { {4, 0, 3}, {-4, 0, 3}, {0, 4, 3}, {0, -4, 3} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - (-1.0)) < max_error);
     }
 
     SUBCASE("Simple test #0")
     {
         Graph graph;
         Point a = { 0, 1 }; 
         Point b = { 0, -1 };
         std::vector<Circle> c = { {0.0, 0.0, 0.8}, {-3.8, 0.0, 3.2}, {3.5, 0.0, 3.0}, {7.0, 0.0, 1.0} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - 19.0575347577) < max_error);
     }
     SUBCASE("Simple test #1")
     {
         Graph graph;
         Point a = { 0, -7 };  
         Point b = { 8, 8 };
         std::vector<Circle> c = { };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - 17.0) < max_error);
     }
     SUBCASE("Simple test #2")
     {
         Graph graph;
         Point a = { -3.5, 0.1 }; 
         Point b = { 3.5, 0.0 };
         double r = 2.01;
         std::vector<Circle> c = { {0,0,1}, {r, 0.0, 1.0}, {r * 0.5, r * sqrt(3) / 2, 1.0}, {-r * 0.5, r * sqrt(3) / 2, 1.0},
                       {-r, 0.0, 1.0}, {r * 0.5, -r * sqrt(3) / 2, 1.0}, {-r * 0.5, -r * sqrt(3) / 2, 1.0} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - 7.80758072818) < max_error);
     }
     SUBCASE("Start in forbidden zone")
     {
         Graph graph;
         Point a = { 0.5, 0.5 };  
         Point b = { 2, 2 };
         std::vector<Circle> c = { {0, 0, 1} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - (-1.0)) < max_error);
     }
   
     SUBCASE("End in forbidden zone")
     {
         Graph graph;
         Point a = { 2, 2 };  
         Point b = { 0.5, 0.5 };
         std::vector<Circle> c = { {0, 0, 1} };
         CHECK(std::abs(shortest_path_length(a, b, c, graph) - (-1.0)) < max_error);
     }
}