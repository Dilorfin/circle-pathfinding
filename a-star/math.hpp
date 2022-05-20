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

// lineExists_resharper_v4
inline bool lineExists(const Point& a, const Point& b, const std::vector<Circle>& circles)
{
	const Point v = vector(a, b);
	return std::all_of(circles.begin(), circles.end(), [&](const Circle& circle) {
		const double u = ((circle.ctr.x - a.x) * v.x + (circle.ctr.y - a.y) * v.y) / (v.x * v.x + v.y * v.y);
		const double temp = std::clamp(u, 0., 1.);
		const Point E(a.x + temp * v.x, a.y + temp * v.y);
		const double d = length(vector(circle.ctr, E));
		return d >= circle.r;
	});
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

//https://stackoverflow.com/a/69433855/8885358
std::vector<Point> tangentLines(const Point& A, const Circle& circle)
{
	const Point C = circle.ctr;
	const double R = circle.r;

	const double t = R * R - C.x * C.x - A.x * C.x;
	const double p = C.y - A.y;

	const double a = std::pow(C.x - A.x, 2) + p * p;
	const double b = 2 * t * (C.x - A.x) - 2 * p * p * C.x;
	const double c = t * t - p * p * R * R + p * p * C.x * C.x;

	const double D = b * b - 4 * a * c;

	const double x1 = (-b + std::sqrt(D)) / (2 * a);
	const double x2 = (-b - std::sqrt(D)) / (2 * a);

	double y1 = C.y - std::sqrt(R * R - std::pow(C.x - x1, 2));
	double y2 = C.y - std::sqrt(R * R - std::pow(C.x - x2, 2));

	y2 = std::abs(C.y - A.y) <= max_error ? -y2 : y2;

	return { {x1,y1}, {x2, y2} };
}
