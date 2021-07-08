#include "Point.h"
#include <iostream>
#include <string>


Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point& point)
{
	//std::cout << "copy point" << std::endl;

	this->x = point.x;
	this->y = point.y;
}

Point::~Point()
{
	//std::cout << "deleted point" << std::endl;
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

void Point::setX(const int x)
{
	this->x = x;
}


void Point::setY(const int y)
{
	this->y = y;
}

std::ostream& operator<<(std::ostream& stream, const Point& point)
{
	stream << "(" << point.x << "," << point.y << ")";
	return stream;
}