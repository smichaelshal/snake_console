#include "Action.h"
#include "Point.h"
#include <string>

Action::Action(int x, int y, int directionUser): direction(directionUser)
{
	this->point = new Point(x, y);
	this->sumTTL = 0;
}

//Action::Action(const Point& pointUser, int directionUser): direction(directionUser)
//{
//	this->point =;
//	this->sumTTL = 0;
//}
Action::Action(const Action& action): direction(action.direction)
{

	this->sumTTL = action.sumTTL;
	this->point = new Point(action.point->getX(), action.point->getY());

}

Action::~Action()
{
	delete this->point;
	//std::cout << "delete action" << std::endl;
}

int Action::getDirection()
{
	return direction;
}
int Action::getSumTTL()
{
	return sumTTL;
}
Point& Action::getPoint()
{
	return *point;
}

void Action::incSumTTL()
{
	//std::cout << "incs" << std::endl;
	(this->sumTTL)++;
}

void Action::setDirection(int newDirection)
{
	//std::cout << "ff" << std::endl;
	this->direction = newDirection;
}
void Action::setPoint(Point newPoint)
{
	point->setX(newPoint.getX());
	point->setY(newPoint.getY());
}

std::ostream& operator<<(std::ostream& stream, const Action& action)
{
	stream << "(" << *(action.point) << "," << action.sumTTL << "," << action.direction << ")";
	return stream;
}
