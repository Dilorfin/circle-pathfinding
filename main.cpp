#include <iostream>

#include <SFML/Graphics.hpp>

#include "codewars_structs.hpp"

int main() try
{
	Point startPoint { 10, 10 };
	startPoint.color = sf::Color::Red;
	Point endPoint { 100, 100 };
	endPoint.color = sf::Color::Green;

	const std::vector circles = {
		Circle(50, 50, 10)
	};

	sf::RenderWindow window(sf::VideoMode(864, 724), "Circle Path-finding", sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	sf::Clock frameClock;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		for (const auto & circle : circles)
		{
			window.draw(circle);
		}

		window.draw(startPoint);
		window.draw(endPoint);

		window.display();
	}
	return 0;
}
catch (std::exception& exception)
{
	std::cerr << "An error has occurred: ";
	std::cerr << exception.what() << std::endl;
	system("pause");
	return -1;
}
