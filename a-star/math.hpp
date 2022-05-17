#pragma once
#include "../codewars_structs.hpp"

constexpr double max_error = 1e-8;

inline double distance(const Point& a, const Point& b)
{
	return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

double arcLength(Circle circle, Point a, Point b)
{
	return 0;
}

inline bool equal(const Point& a, const Point& b)
{
	return distance(a, b) <= max_error;
}

bool checkLine(const std::vector<Circle>& circles, Point  a, Point b)
{
	return false;
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
