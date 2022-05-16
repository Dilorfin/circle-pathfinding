#include <vector>

struct Point
{
	double x, y;

	Point() : x(0.0), y(0.0) {}
	Point(double x, double y) : x(x), y(y) {}
};

struct Circle
{
	Point ctr;
	double r;

	Circle() : ctr(), r(1.0) {}
	Circle(Point c, double r) : ctr(c), r(r) {}
	Circle(double cx, double cy, double r) : ctr(cx, cy), r(r) {}
};

double shortest_path_length(Point a, Point b, const std::vector<Circle>& circles)
{
	// return length of shortest route from a to b, avoiding the interiors of the circles in c
	return 0;
}
