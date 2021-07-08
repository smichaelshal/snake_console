#pragma once
#include <iostream>

class Point
{
private:
	int x;
	int y;

public:
	Point(int x, int y);
	Point(const Point& point);
	~Point();

	int getX();
	int getY();
	void setX(const int x);
	void setY(const int x);

	friend std::ostream& operator<<(std::ostream& stream, const Point& point);
};