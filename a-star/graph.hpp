#pragma once
#include <iostream>
#include <vector>

#include "../codewars_structs.hpp"
#include "math.hpp"

class Graph final
{
private:
	std::vector<std::vector<double>> matrix;

	std::vector<Point> vertexes;
public:

	Graph() = default;

	explicit Graph(std::vector<Point> points)
		: vertexes(std::move(points))
	{
		for (int i = 0; i < this->vertexes.size(); i++)
		{
			for (int j = i + 1; j < this->vertexes.size(); j++)
			{
				if (equal(this->vertexes[i], this->vertexes[j]))
					throw std::exception("fuck this boolshit");
			}
			matrix.emplace_back(this->vertexes.size());
		}
	}

	void setWeight(const size_t x, const size_t y, const double weight)
	{
		assert(x != y);
		assert(x < matrix.size());
		assert(y < matrix[x].size());

		matrix[x][y] = weight;
		matrix[y][x] = weight;
	}

	[[nodiscard]] double getWeight(const size_t x, const size_t y) const
	{
		assert(x < matrix.size());
		assert(y < matrix[x].size());

		return matrix[x][y];
	}

	[[nodiscard]] size_t size() const
	{
		return matrix.size();
	}

	bool addVertex(const Point& point)
	{
		for (const auto& value : vertexes)
		{
			if (equal(point, value))
				return false;
		}
		vertexes.push_back(point);
		this->addVertex();
		return true;
	}

	[[nodiscard]] Point getVertex(const size_t ind) const
	{
		assert(ind < vertexes.size());

		return vertexes[ind];
	}

	[[nodiscard]] const std::vector<Point>& getVertexes() const
	{
		return vertexes;
	}

	void debugDisplay() const
	{
		for (const auto& row : matrix)
		{
			for (const double j : row)
			{
				std::cout << j << "\t";
			}
			std::cout << std::endl;
		}
	}

private:
	static bool noEdge(const double weight)
	{
		constexpr double none_weight = 0.0;
		return weight <= none_weight;
	}
	void addVertex()
	{
		for (auto& row : matrix)
		{
			row.emplace_back();
		}
		matrix.emplace_back(vertexes.size());
	}
};
