#pragma once
#include <SFML/Graphics.hpp>

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
