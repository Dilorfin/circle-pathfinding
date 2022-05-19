#include <nanobench.h>
#include "../a-star/math.hpp"

std::vector<Circle> circlesGenerator(const size_t number);

inline bool lineExists_v1(const Point& a, const Point& b, const std::vector<Circle>& circles);
inline bool lineExists_v3(const Point& a, const Point& b, const std::vector<Circle>& circles);
inline bool lineExists_v4(const Point& a, const Point& b, const std::vector<Circle>& circles);

inline bool lineExists_resharper_v1(const Point& a, const Point& b, const std::vector<Circle>& circles);
inline bool lineExists_resharper_v2(const Point& a, const Point& b, const std::vector<Circle>& circles);
inline bool lineExists_resharper_v3(const Point& a, const Point& b, const std::vector<Circle>& circles);
inline bool lineExists_resharper_v4(const Point& a, const Point& b, const std::vector<Circle>& circles);

int main()
{
	const std::vector<Circle> circles = circlesGenerator(15000);
	const Point a = circles.back().ctr;
	const Point b(circles.back().ctr.x + 20, circles.back().ctr.y - 20);

	ankerl::nanobench::Bench().run("mainstream", [&]() {
		return lineExists(a, b, circles);
	});

	ankerl::nanobench::Bench().run("lineExists_v1", [&]() {
		return lineExists_v1(a, b, circles);
	});

	ankerl::nanobench::Bench().run("lineExists_v3", [&]() {
		return lineExists_v3(a, b, circles);
	});
	ankerl::nanobench::Bench().run("lineExists_v4", [&]() {
		return lineExists_v4(a, b, circles);
	});

	ankerl::nanobench::Bench().run("lineExists_resharper_v1", [&]() {
		return lineExists_resharper_v1(a, b, circles);
	});

	ankerl::nanobench::Bench().run("lineExists_resharper_v2", [&]() {
		return lineExists_resharper_v2(a, b, circles);
	});

	ankerl::nanobench::Bench().run("lineExists_resharper_v3", [&]() {
		return lineExists_resharper_v3(a, b, circles);
	});

	ankerl::nanobench::Bench().run("lineExists_resharper_v4", [&]() {
		return lineExists_resharper_v4(a, b, circles);
	});

	return 0;
}

inline bool lineExists_v1(const Point& a, const Point& b, const std::vector<Circle>& circles)
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

inline bool lineExists_v3(const Point& a, const Point& b, const std::vector<Circle>& circles)
{
	const Point v = vector(a, b);
	
	for (const auto& circle : circles)
	{
		const double u = ((circle.ctr.x - a.x) * v.x + (circle.ctr.y - a.y) * v.y) / (v.x * v.x + v.y * v.y);
		const double temp = std::clamp(u, 0., 1.);
		const Point E(a.x + temp * v.x, a.y + temp * v.y);
		const double d = length({E.x - circle.ctr.x, E.y- circle.ctr.y});
		if(d < circle.r)
		{
			return false;
		}
	}
	return true;
}
inline bool lineExists_v4(const Point& a, const Point& b, const std::vector<Circle>& circles)
{
	const Point v = vector(a, b);
	
	for (const auto& circle : circles)
	{
		const double u = ((circle.ctr.x - a.x) * v.x + (circle.ctr.y - a.y) * v.y) / (v.x * v.x + v.y * v.y);
		const double temp = std::clamp(u, 0., 1.);
		const Point E(a.x + temp * v.x, a.y + temp * v.y);
		const double d = length(vector(circle.ctr, E));
		if(d < circle.r)
		{
			return false;
		}
	}
	return true;
}

inline bool lineExists_resharper_v1(const Point& a, const Point& b, const std::vector<Circle>& circles)
{
	return std::all_of(circles.begin(), circles.end(), [&a, &b](const Circle& circle) {
		const Point v = vector(a, b);
		const double u = ((circle.ctr.x - a.x) * (b.x - a.x) + (circle.ctr.y - a.y) * (b.y - a.y)) / (v.x * v.x + v.y * v.y);
		const double temp = std::clamp(u, 0., 1.);
		const Point E(a.x + temp * (b.x - a.x), a.y + temp * (b.y - a.y));
		const double d = length({E.x - circle.ctr.x, E.y- circle.ctr.y});
		return d >= circle.r;
	});
}
inline bool lineExists_resharper_v2(const Point& a, const Point& b, const std::vector<Circle>& circles)
{
	const Point v = vector(a, b);
	return std::all_of(circles.begin(), circles.end(), [&](const Circle& circle) {
		const double u = ((circle.ctr.x - a.x) * (b.x - a.x) + (circle.ctr.y - a.y) * (b.y - a.y)) / (v.x * v.x + v.y * v.y);
		const double temp = std::clamp(u, 0., 1.);
		const Point E(a.x + temp * (b.x - a.x), a.y + temp * (b.y - a.y));
		const double d = length({E.x - circle.ctr.x, E.y- circle.ctr.y});
		return d >= circle.r;
	});
}
inline bool lineExists_resharper_v3(const Point& a, const Point& b, const std::vector<Circle>& circles)
{
	const Point v = vector(a, b);
	return std::all_of(circles.begin(), circles.end(), [&](const Circle& circle) {
		const double u = ((circle.ctr.x - a.x) * v.x + (circle.ctr.y - a.y) * v.y) / (v.x * v.x + v.y * v.y);
		const double temp = std::clamp(u, 0., 1.);
		const Point E(a.x + temp * v.x, a.y + temp * v.y);
		const double d = length({E.x - circle.ctr.x, E.y- circle.ctr.y});
		return d >= circle.r;
	});
}
inline bool lineExists_resharper_v4(const Point& a, const Point& b, const std::vector<Circle>& circles)
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

std::vector<Circle> circlesGenerator(const size_t number)
{
	std::vector<Circle> circles;
	circles.reserve(number);
	for(size_t i = 0; i < number; i++)
	{
		circles.emplace_back(10*i, 10*i, 3*i);
	}
	return circles;
}
