#pragma once

#include <iostream>
#include "Point.h"
#include "Action.h"
#include <string>
#include <vector>

class Snake
{
private:
	std::vector<Action> listActionsPoints;
	std::vector<Action> listActions;

	int length;
	int sumGames;
	int sumWins;
	int recordUser;
	char head;
	char body;

public:
	Snake(int x, int y, int direction);
	Snake(const Snake& snake);
	~Snake();

	void addAction(int x, int y, int direction);
	void addActionPoint(int x, int y, int direction);

	int getLength();
	int getSumGames();
	int getSumWins();
	int getRrecordUser();

	void updateSnake();
	
	std::vector<Action> getListActionsPoints();
	std::vector<Action> getListActions();

	bool isLose(int x, int y);
	char getHead();
	char getBody();


	friend std::ostream& operator<<(std::ostream& stream, const Snake& snake);

};

//void updateDirection(Action& action);
//void changeDirection(Action& action, int newDirection);

