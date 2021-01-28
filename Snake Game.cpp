#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;
// The width and height of the game board. These settings are set and can not be changed later on. Only here.
const int width = 20;
const int height = 20;
// Global variables that are used later on for knowing the coordinates of things.
int x, y, fruitX, fruitY, score;
// Used to keep track of the tails X and Y coordinate.
int tailX[100], tailY[100];
int nTail;

// Setting up an enum because we can't move any other direction than up, down, left and right. So we should restrict it to only be these.
// + a stop for when the game is starting/resetting.
enum eDirection { Stop = 0, Left, Right, Up, Down }dir;
void Setup() {
    gameOver = false;
    dir = Stop;

    // Makes it so that the player starts in the middle of the map.
    x = width / 2;
    y = height / 2;

    // Randomizes the fruit location.
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw() {
    // "cls" clears the console window.
    system("cls");
    for (int i = 0; i < width+2; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int p = 0; p < width; p++) {
            if (p == 0) {
                cout << "#";
            }
            if (i == y && p == x) {
                cout << "O";
            }
            else if (i == fruitY && p == fruitX) {
                cout << "F";
            }
            else {
                // Checks if we should print out a tail or if we should print out a blank space. If the coordinates for our tail lign up
                // we print out the "o" else if we didn't print out the tail, we print out a blank space.
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == p && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
            if (p == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < height+2; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}
void Input() {
    // This makes us able to controll the snake. _kbhit() and _getch() are used for checking if a key has been pressed and
    // then which key has been pressed respectively.
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = Left;
            break;
        case 'd':
            dir = Right;
            break;
        case 'w':
            dir = Up;
            break;
        case 's':
            dir = Down;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic() {
    // Logic for making sure that the tail follows where the player has moved.
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    // This tells the computer what to do when we have pressed the keys. So if we press 'a' then we move Left because it constantly
    // reduces our snakes x axies by 1. And it will keep on doing this till another key is pressed.
    switch (dir) {
    case Left:
        x--;
        break;
    case Right:
        x++;
        break;
    case Up:
        y--;
        break;
    case Down:
        y++;
        break;
    }
    // If we hit a wall, the game should end.
    if (x > width || x < 0 || y > height || y < 0) {
        gameOver = true;
    }
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
    // If we move over a fruit, we should add score and make the snake longer. Then we need to move the fruit to a new random location within
    // the game borders.
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
int main()
{
    Setup();
    while (!gameOver) {
        Draw();
        Sleep(100);
        Input();
        Logic();
    }
    return 0;
}
