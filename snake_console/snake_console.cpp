#include <iostream>
#include <vector>

#include <chrono>
#include <thread>

#include <conio.h>

#include "Point.h"
#include "Action.h"
#include "Snake.h"

#define X_BOARD 30
#define Y_BOARD 20

#define X_START 5
#define Y_START 15

bool static isApple = false;
static Point* applePoint;

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

void eatApple(Snake& snake)
{
   
    int sizeList = snake.getListActionsPoints().size();
    Point point = snake.getListActionsPoints()[sizeList - 1].getPoint();
    int direction = snake.getListActionsPoints()[sizeList - 1].getDirection();
    int deltaX = 0;
    int deltaY = 0;

    if (direction == 0) { deltaX = 0; deltaY = 1; }
    else if (direction == 1) { deltaX = 0; deltaY = -1; }
    else if (direction == 2) { deltaX = 1; deltaY = 0; }
    else if (direction == 3) { deltaX = -1; deltaY = 0; }

    snake.addActionPoint(point.getX() + deltaX, point.getY() + deltaY, direction);
}

bool checkApple(int x, int y, std::vector<Snake>& listSnakes)
{
    for (int i = 0; i < listSnakes.size(); i++)
    {
        std::vector<Action> listAction = listSnakes[i].getListActionsPoints();

        if (x == 0 || y == 0 || x >= X_BOARD -1 || y >= Y_BOARD -1) { return false; }

        for (int i = 0; i < listAction.size(); i++)
        {
            if (listAction[i].getPoint().getX() == x && listAction[i].getPoint().getY() == y) { return false; }
        }

    }

    return true;
}




Point* createApple(std::vector<Snake>& listSnakes)
{
    int xApple;
    int yApple;
    bool isOkApple = false;

    do
    {
        xApple = rand() % X_BOARD;
        yApple = rand() % Y_BOARD;

        isOkApple = checkApple(xApple, yApple, listSnakes);
    } while (!isOkApple);

    Point* tempPoint = new Point(xApple, yApple);

    return tempPoint;
}

void printSnake(int x, int y, std::vector<Snake> listSnakes)
{
    int sumLoops = 0;

    for (int index_Y = 0; index_Y < y; index_Y++)
    {
        for (int index_X = 0; index_X < x; index_X++)
        {

            bool isHead = false;
            bool isBody = false;

            for (int indexSnake = 0; indexSnake < listSnakes.size(); indexSnake++)
            {
                std::vector<Action> listActions = listSnakes[indexSnake].getListActionsPoints();
                for (int indexPointSnake = 0; indexPointSnake < listActions.size(); indexPointSnake++)
                {
                    Point point = listActions[indexPointSnake].getPoint();
                    if (point.getX() == index_X && point.getY() == index_Y)
                    {
                        if(indexPointSnake == 0){ isHead = true;}
                        else { isBody = true; }
                    }
                }


                if(isHead){ std::cout << listSnakes[indexSnake].getHead(); }
                else if(isApple && index_X == applePoint->getX() && index_Y == applePoint->getY()){ std::cout << 'A'; }
                else if(isBody){ std::cout << listSnakes[indexSnake].getBody(); }
                else if (index_X == 0 || index_X == x - 1 || index_Y == 0 || index_Y == y - 1) { std::cout << '#'; }
                else { std::cout << ' '; }
            }
        }

        std::cout << std::endl;
    }

}



void update(std::vector<Snake>& listSnakes)
{
    if (!isApple)
    {
        applePoint = createApple(listSnakes);
        isApple = true;

    }
    else {

    }

    for (int i = 0; i < listSnakes.size(); i++)
    {
        listSnakes[i].updateSnake();

        Point tempPoint = listSnakes[i].getListActionsPoints()[0].getPoint();
        if (tempPoint.getX() == applePoint->getX() && tempPoint.getY() == applePoint->getY())
        {
            eatApple(listSnakes[i]);
            isApple = false;
            std::cout << "rrrr";
            applePoint = nullptr;
        }
        
    }

}

bool isLoseSnakes(int x, int y, std::vector<Snake> listSnakes)
{
    for (int i = 0; i < listSnakes.size(); i++)
    {
        if (listSnakes[i].isLose(x, y)) { return true; }
    }
    return false;
}


void input(Snake& snake)
{
    if (_kbhit())
    //if(true)
    {
        char inputChar = _getch();
        int direction = -1;

        if (inputChar == 'w') { direction = 0; }
        else if (inputChar == 's') { direction = 1; }
        else if (inputChar == 'a') { direction = 2; }
        else if (inputChar == 'd') { direction = 3; }

        else {
            return;
        }
        int oldDirection = snake.getListActionsPoints()[0].getDirection();

        if (oldDirection == 0 && direction == 1 && snake.getLength() > 1) { return; }
        else if (oldDirection == 1 && direction == 0 && snake.getLength() > 1) { return; }
        else if (oldDirection == 2 && direction == 3 && snake.getLength() > 1) { return; }
        else if (oldDirection == 3 && direction == 2 && snake.getLength() > 1) { return; }

        Point tempPoint = snake.getListActionsPoints()[0].getPoint();
        snake.addAction(tempPoint.getX(), tempPoint.getY(), direction);
        
    }
}

int main()
{
    bool gameOver = false;

    std::vector<Snake> listSnakes;
    Snake snake = Snake(X_START, Y_START, 0);
    //snake.addActionPoint(5, 16, 0);
    //snake.addActionPoint(5, 17, 0);
    //snake.addActionPoint(5, 18, 0);

    listSnakes.push_back(snake);



    while (!gameOver)
    {
        printSnake(X_BOARD, Y_BOARD, listSnakes);

        input(listSnakes[0]);

        update(listSnakes);

        if (isLoseSnakes(X_BOARD, Y_BOARD, listSnakes)) { std::cout << "GAME OVER!!!" << std::endl; break; }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");


    }

    std::cin.get();

}
