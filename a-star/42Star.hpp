#pragma once

#include <vector>
#include <optional>
#include <algorithm>
#include <list>

#include "../a-star/math.hpp"
#include "../a-star/graph.hpp"
#include "../codewars_structs.hpp"

class _42Star
{
private:
	Graph graph;
	const std::vector<Circle>& circles;

	Point start; 
	Point end;

	struct Node {
		size_t ind;
		double g;
		double h;
		int prev;
		int circle_index;
	};
	std::list<Node> open;
	std::list<Node> closed;
	std::vector<size_t> closedCirclesIndicies;

	std::optional<std::vector<Point>> path = std::nullopt;
public:
	_42Star(Graph graph, const std::vector<Circle>& circles, const Point& start, const Point& end) :
		graph(graph),
		circles(circles), 
		start(start), 
		end(end)
	{}

	std::vector<Point> getPath()
	{
		if (path.has_value())
			return path.value();

		if(checkLine(circles, start, end))
			return std::vector<Point>({ start, end });

		//initialization
		graph.addVertex(start);

		//0: find points from start
		for (int i = 0; i < circles.size(); i++)
		{
			auto points = tangentLines(start, circles[i]);
			for (size_t j = 0; j < points.size(); j++)
			{
				graph.addVertex(points[j]);
				double distance_from_start = distance(start, points[j]);
				open.push_back({
					j + 1,
					distance_from_start,
					distance(end, points[j]),
					0,
					i
					});
				graph.setWeight(0, j + 1, distance_from_start);
			}
		}
		//1: put start in closed list
		closed.push_back({
			0,
			0,
			distance(start, end),
			-1,
			-1
			});

		while (open.size() != 0)
		{
			//2: select point with min heuristic
			auto point = *std::min_element(
				open.begin(), 
				open.end(), 
				[](Node a, Node b) {
					return a.g + a.h < b.g + b.h; 
				});
			//3: if circle with point is not checked, check it
			if (find(closedCirclesIndicies.begin(), closedCirclesIndicies.end(), point.circle_index) == closedCirclesIndicies.end())
			{
				//5: build edges for tangents
				//
				for (int i = 0; i < circles.size(); i++)
				{
					
					//TODO: check if tangentLines() will not die if pass equal circles
				}
				//4: build edges for points on circle
				auto vertexes = graph.getVertexes();
				for (int i = 0; i < vertexes.size(); i++)
				{
					for (int j = i + 1; j < vertexes.size(); j++)
					{
						//if circle contains both points
						if ((circles[point.circle_index].r == distance(circles[point.circle_index].ctr, graph.getVertex(i))) &&
							(circles[point.circle_index].r == distance(circles[point.circle_index].ctr, graph.getVertex(j))))
						{
							//add length of arc between points to graph
							graph.setWeight(i, j, arcLength(circles[point.circle_index], graph.getVertex(i), graph.getVertex(j)));
						}
					}
				}
				//6: set weights and heuristics for points
				//7: add new points to open list
			}
			//try to set better g for point neighbors
			
			//8: remove point from open, add to close
			//9: if open does not contain points which is possibly better than curent
			if (false)
			{
				//return path
			}
		}

		path = std::vector<Point>();
		return path.value();
	}
};