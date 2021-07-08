#include "Snake.h"
#include <string>
// 0 up
// 1 down
// 2 left
// 3 right

template <typename T>
void PrintList(const std::vector<T>& list)
{
	if (list.size() == 0) { std::cout << "length list 0" << std::endl; }
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << list[i];

		if (i + 1 < list.size()) { std::cout << " ,"; }
		else { std::cout << std::endl; }

	}

}


void updateDirection(Action& action)
{

	int direction = action.getDirection();
	int deltaX = 0;
	int deltaY = 0;

	if (direction == 0) { deltaX = 0; deltaY = -1;}
	else if (direction == 1) { deltaX = 0; deltaY = 1; }
	else if (direction == 2) { deltaX = -1; deltaY = 0; }
	else if (direction == 3) { deltaX = 1; deltaY = 0; }

	// check limit board and the body snake ???

	//action.setPoint(Point(1, 2));


	action.getPoint().setX(action.getPoint().getX() + deltaX);
	action.getPoint().setY(action.getPoint().getY() + deltaY);


	//std::cout << "action: " << action << std::endl;

	

}

void changeDirection(Action& action, int newDirection)
{
	action.setDirection(newDirection);
}


int getDirectionFromList(Point& point, std::vector<Action>& listActions)
{
	
	for (int i = 0; i < listActions.size(); i++)
	{
		Point pointTemp = listActions[i].getPoint();
		//std::cout << i << std::endl;

		if (pointTemp.getX() == point.getX() && pointTemp.getY() == point.getY())
		{
			listActions[i].incSumTTL();
			//std::cout << "listActions[i].getDirection()" << listActions[i].getDirection() << std::endl;
			return listActions[i].getDirection();
		}
	}

	return -1;


}


void updatePoints(std::vector<Action>& listActionsPoints, std::vector<Action>& listActions)
{
	for (int i = 0; i < listActionsPoints.size(); i++)
	{
		int isChangeDirection = getDirectionFromList(listActionsPoints[i].getPoint(), listActions);
		if (isChangeDirection != -1)
		{
			changeDirection(listActionsPoints[i], isChangeDirection);
		}
		updateDirection(listActionsPoints[i]);
	}

}


Snake::Snake(int x, int y, int direction)
{
	length = 1;
	sumGames = 0;
	sumWins = 0;
	recordUser = 0;
	head = '0';
	body = 'o';

	listActions.push_back({ x, y, direction });
	listActionsPoints.push_back({ x, y, direction });

}

Snake::Snake(const Snake& snake)
{
	length = snake.length;
	sumGames = snake.sumGames;
	sumWins = snake.sumWins;
	recordUser = snake.recordUser;
	head = snake.head;
	body = snake.body;

	for (int i = 0; i < snake.listActions.size(); i++)
	{
		listActions.push_back(snake.listActions[i]);// ???
	}

	for (int i = 0; i < snake.listActionsPoints.size(); i++)
	{
		listActionsPoints.push_back(snake.listActionsPoints[i]);// ???
	}
}

Snake::~Snake()
{
	listActions.clear();
	listActionsPoints.clear();
}

void Snake::addAction(int x, int y, int direction)
{
	listActions.push_back({ x, y, direction });
}
// 0 up
// 1 down
// 2 left
// 3 right

void Snake::addActionPoint(int x, int y, int direction)
{
	int deltaX = 0;
	int deltaY = 0;

	/*if (direction == 0) { deltaX = 0; deltaY = 1; }
	else if (direction == 1) { deltaX = 0; deltaY = -1; }
	else if (direction == 2) { deltaX = 1; deltaY = 0; }
	else if (direction == 3) { deltaX = -1; deltaY = 0; }*/

	listActionsPoints.push_back({ x+ deltaX, y + deltaY, direction });
	(this->length)++;
}

int Snake::getLength()
{
	return length;
}
int Snake::getSumGames()
{
	return sumGames;
}
int Snake::getSumWins()
{
	return sumWins;
}
int Snake::getRrecordUser()
{
	return recordUser;
}
 
std::vector<Action> Snake::getListActionsPoints()
{
	return listActionsPoints;
}

std::vector<Action> Snake::getListActions()
{
	return listActions;
}
//bool Snake::isLose();


void deleteAction(std::vector<Action>& listActions ,int length)
{
	int sumDelete = 0;
	for (int i = 0; i < listActions.size(); i++)
	{
		if (listActions.size() > 1 && listActions[i - sumDelete].getSumTTL() >= length)
		{
			listActions[i - sumDelete].setDirection(-1);
		}
	}
}


void Snake::updateSnake()
{
	deleteAction(listActions, length);
	updatePoints(listActionsPoints, listActions);

}

std::ostream& operator<<(std::ostream& stream, const Snake& snake)
{
	for (int i = 0; i < snake.listActionsPoints.size(); i++)
	{
		stream << snake.listActionsPoints[i];
	}
	return stream;
}

bool Snake::isLose(int x, int y)
{
	Point pointHead = listActionsPoints[0].getPoint();
	if (pointHead.getX() <= 0 || pointHead.getY() <= 0)
	{
		return true;
	}
	else if (pointHead.getX() >= x || pointHead.getY() >= y)
	{
		return true;
	}

	else 
	{
		for (int i = 1; i < listActionsPoints.size(); i++)
		{
			Point pointNow = listActionsPoints[i].getPoint();
			if (pointNow.getX() == pointHead.getX() && pointNow.getY() == pointHead.getY())
			{
				return true;
			}
		}
	}
	return false;
}

char Snake::getHead()
{
	return head;
}

char Snake::getBody()
{
	return body;
}