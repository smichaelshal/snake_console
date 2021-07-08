#pragma once
#include "Point.h"
#include <string>

class Action
{
private:
	Point* point;
	int direction;
	int sumTTL;
	
public:
	Action(int x, int y, int directionUser);
	Action(const Action& action);
	~Action();

	int getDirection();
	int getSumTTL();
	Point& getPoint();

	void incSumTTL();
	void setDirection(int newDirection);
	void setPoint(Point newPoint);

	friend std::ostream& operator<<(std::ostream& stream, const Action& action);

};

