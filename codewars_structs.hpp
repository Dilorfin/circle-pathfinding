#pragma once
#include <vector>

struct Point final : sf::Drawable
{
	// shouldn't be modified... or finally replaced with undef in codewars
	double x, y;

	Point() : x(0.0), y(0.0) {}
	Point(double x, double y) : x(x), y(y) {}

	// for testing purpose only (can be modified)
	sf::Color color = sf::Color::Magenta;
protected:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override
	{
		sf::CircleShape circle(3);
		circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
		circle.setPosition(sf::Vector2f(x, y));
		circle.setFillColor(color);
		target.draw(circle);
	}
};

struct Circle final : sf::Drawable
{
	// shouldn't be modified... or finally replaced with undef in codewars
	Point ctr;
	double r;

	Circle() : ctr(), r(1.0) {}
	Circle(Point c, double r) : ctr(c), r(r) {}
	Circle(double cx, double cy, double r) : ctr(cx, cy), r(r) {}

	// for testing purpose only (can be modified)
	sf::Color color = sf::Color::Yellow;
protected:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override
	{
		sf::CircleShape circle(r);
		circle.setOrigin(sf::Vector2f(r, r));
		circle.setPosition(sf::Vector2f(ctr.x, ctr.y));
		circle.setFillColor(color);
		target.draw(circle);
	}
};

inline double distance(const Point& a, const Point& b)
{
	return std::sqrt(std::pow(a.x-b.x, 2)+std::pow(a.y-b.y, 2));
}
inline bool equal(const Point& a, const Point& b)
{
	constexpr double max_error = 1e-8;
	return distance(a, b) <= max_error;
}

double shortest_path_length(const Point& startPoint, const Point& endPoint, const std::vector<Circle>& circles)
{
	// return length of shortest route from a to b, avoiding the interiors of the circles in c
	return 0;
}
