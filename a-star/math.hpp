#pragma once
#include "../codewars_structs.hpp"

constexpr double max_error = 1e-8;

inline double distance(const Point& a, const Point& b)
{
	return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

inline bool equal(const Point& a, const Point& b)
{
	return distance(a, b) <= max_error;
}

inline Point vector(const Point& start, const Point& end)
{
	return { end.x - start.x, end.y - start.y };
}

inline double length(const Point& a)
{
	return std::sqrt(a.x * a.x + a.y * a.y);
}

inline double dot(const Point& a, const Point& b)
{
	return a.x*b.x + a.y*b.y;
}

inline double angleBetweenVectors(const Point& a, const Point& b)
{
	return std::acos(dot(a, b) / (length(a) * length(b)));
}

inline double arcLength(const Circle& circle, const Point& a, const Point& b)
{
	const Point ca = vector(circle.ctr, a);
	const Point cb = vector(circle.ctr, b);
	
	const double angle = angleBetweenVectors(ca, cb);
	
	return angle * circle.r;
}

inline bool lineExists(const Point& a, const Point& b, const std::vector<Circle>& circles)
{
	const Point v = vector(a, b);

	for (const auto& circle : circles)
	{
		const double u = ((circle.ctr.x - a.x) * (b.x - a.x) + (circle.ctr.y - a.y) * (b.y - a.y)) / (v.x * v.x + v.y * v.y);
		const double temp = std::clamp(u, 0., 1.);
		const Point E(a.x + temp * (b.x - a.x), a.y + temp * (b.y - a.y));
		const double d = length({E.x - circle.ctr.x, E.y- circle.ctr.y});
		if(d < circle.r)
		{
			return false;
		}
	}

	return true;
}

std::vector<std::pair<Point, Point>> tangentLines(Circle a, Circle b)
{
	std::vector<std::pair<Point, Point>> result;

	// straight

	if (distance(a.ctr, b.ctr) - (a.r+b.r) <= max_error)
		return result;

	// diagonal

	return result;
}

std::vector<Point> tangentLines(Point a, Circle b)
{
	return {};
}
