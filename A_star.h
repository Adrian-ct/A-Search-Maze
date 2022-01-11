#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <chrono>
using namespace std::chrono;

class A_star
{
public:
	A_star() = default;
	~A_star();
	A_star(const A_star& a_star);

	friend std::istream& operator>>(std::istream& in, A_star& obj);
	friend std::ostream& operator <<(std::ostream& out, A_star& obj);
	void search();

private:
	int** matrix;
	int size;
	std::pair<int, int> start;
	std::pair<int, int> finish;
	bool valid(std::pair<int, int> curr);
	std::pair<int, int> a_star_search();
};

