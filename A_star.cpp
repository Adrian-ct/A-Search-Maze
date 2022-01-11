#include "A_star.h"

bool A_star::valid(std::pair<int, int> curr)
{
	return curr.first >= 0 && curr.second >= 0 && curr.second <= size - 1 && curr.first <= size - 1 && matrix[curr.first][curr.second] == 0
		&& (curr.first != finish.first || curr.second != finish.second) && (curr.first != start.first || curr.second != start.second);
}

std::pair<int, int> A_star::a_star_search()
{
	std::pair<int, int> _fin = finish;
	auto lambda = [_fin](std::pair<int, int> curr, std::pair<int, int> curr2) {
		return (abs(curr.first - _fin.first) + abs(curr.second - _fin.second)) > (abs(curr2.first - _fin.first) + abs(curr2.second - _fin.second));
	};

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(lambda)> q(lambda);
	int row[] = { 0,0,-1,+1 },
		col[] = { -1,+1,0,0 };

	q.push(start);

	while (!q.empty())
	{
		int i = q.top().first,
			j = q.top().second;
		q.pop();
		for (size_t k = 0; k < 4; k++)
		{
			int linie = i + row[k],
				coloana = col[k] + j;
			if (valid(std::make_pair(linie, coloana)))
			{
				q.push(std::make_pair(linie, coloana));
				matrix[(linie)][coloana] = matrix[i][j] + 1;
			}
			else if (linie == finish.first && coloana == finish.second)
			{
				matrix[(linie)][coloana] = matrix[i][j] + 1;
				return std::make_pair(i + row[k], col[k] + j);
			}
		}
	}
	return std::make_pair(-1, -1);
}

A_star::~A_star()
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

A_star::A_star(const A_star& a_star)
{
	this->size = a_star.size;
	this->matrix = new int* [size];

	for (size_t i = 0; i < size; i++)
	{
		this->matrix[i] = new int[size];
	}

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			this->matrix[i][j] = a_star.matrix[i][j];
		}
	}
}

void A_star::search()
{
	std::pair<int, int> result = a_star_search();
	std::stack< std::pair<int, int>> stack;
	int row[] = { 0,0,-1,+1 },
		col[] = { -1,+1,0,0 };
	int i = result.first, j = result.second;
	auto startTime = high_resolution_clock::now();
	if (i != -1)
	{

		while (i != start.first || j != start.second)
		{
			for (size_t k = 0; k < 4; k++)
			{
				if (matrix[i + row[k]][j + col[k]] == matrix[i][j] - 1)
				{
					stack.push(std::make_pair(i + row[k], j + col[k]));
					i = i + row[k];
					j = col[k] + j;
					break;
				}
			}
		}

		auto end = high_resolution_clock::now();
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds> (end - startTime).count() << " microseconds\n\n";
		while (!stack.empty())
		{
			std::cout << "Line: "<<stack.top().first << ", Column: " << stack.top().second << "\n";
			stack.pop();
		}
	}
}

std::istream& operator>>(std::istream& in, A_star& obj)
{
	in >> obj.start.first;
	in >> obj.start.second;

	in >> obj.finish.first;
	in >> obj.finish.second;

	in >> obj.size;
	obj.matrix = new int* [obj.size];

	for (size_t i = 0; i < obj.size; i++)
	{
		obj.matrix[i] = new int[obj.size];
	}

	for (size_t i = 0; i < obj.size; i++)
	{
		for (size_t j = 0; j < obj.size; j++)
		{
			in >> obj.matrix[i][j];
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, A_star& obj)
{
	out << "Start: ";
	out << obj.start.first << " " << obj.start.second << "\n";

	out << "Final: ";
	out << obj.finish.first << " " << obj.finish.second << "\n";
	for (size_t i = 0; i < obj.size; i++)
	{
		for (size_t j = 0; j < obj.size; j++)
		{
			if (obj.matrix[i][j] >= 0)
				out << "  " << obj.matrix[i][j];
			else
				out << " -" << obj.matrix[i][j] * (-1);
		}
		out << "\n";
	}
	return out;
}
