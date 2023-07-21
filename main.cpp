#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

struct carsInfo
{
    int row, col, squareRow, squareCol;
    char direction;
    bool aroundSquare = false;
};
char direc[5] = {'u', 'r', 'd', 'l', 'u'};

#define width 20
#define height 20

void mapInitializer(char **, int, int, int, struct carsInfo *c);
void gameLogic(char **, int, struct carsInfo *c);
void boardDraw(char **, int, struct carsInfo *c);
void isAroundSquare(char **, int, struct carsInfo *c);
void carsDirection(int, struct carsInfo *c);

int main()
{
    srand(time(0));
    int carNum, squares, fourWays, duration;
    cout << "How many cars are in the city? \n";
    cin >> carNum;
    cout << "How many squares are in the city? \n";
    cin >> squares;
    cout << "How many four-ways are in the city? \n";
    cin >> fourWays;
    bool isNotOk = (fourWays >= 50 && squares != 0) || (squares >= 50 && fourWays != 0) || (carNum >= 100);
    while (isNotOk)
    {
        try
        {
            if (isNotOk)
                throw("Not Possible!");
            else
                isNotOk = false;
        }
        catch (...)
        {
            cout << "\nNot Possible! enter again:\n\n";
            cout << "How many cars are in the city? \n";
            cin >> carNum;
            cout << "How many squares are in the city? \n";
            cin >> squares;
            cout << "How many four-ways are in the city? \n";
            cin >> fourWays;
            isNotOk = (fourWays >= 50 && squares != 0) || (squares >= 50 && fourWays != 0) || (carNum >= 100);
        }
    }
    cout << "Ok, Now: \nHow many seconds do you want to see the movement of cars? \n";
    cin >> duration;
    carsInfo c[carNum];
    char **map;
    map = new char *[height];
    for (int i = 0; i < height; i++)
    {
        map[i] = new char[width];
        for (int j = 0; j < width; j++)
            map[i][j] = ' ';
    }
    mapInitializer(map, carNum, squares, fourWays, c);
    auto end_time = chrono::steady_clock::now() + chrono::seconds(duration);
    while (chrono::steady_clock::now() < end_time)
    {
        gameLogic(map, carNum, c);
        boardDraw(map, carNum, c);
        this_thread::sleep_for(chrono::milliseconds(450));
    }
    cout << "The End!\n\n";
    return 0;
}

void mapInitializer(char **map, int carNum, int squares, int fourWays, struct carsInfo *c)
{
    for (int i = 1; i <= squares; i++)
    {
        int tempX = (rand() % 18) + 1;
        int tempY = (rand() % 18) + 1;
        if (map[tempX][tempY] == ' ')
        {
            bool freeAround = true;
            for (int x = tempX - 1; x <= tempX + 1; x++)
                for (int y = tempY - 1; y <= tempY + 1; y++)
                    if (map[x][y] == '@')
                    {
                        freeAround = false;
                        break;
                    }
            if (freeAround)
                map[tempX][tempY] = '@';
            else
                i--;
        }
        else
            i--;
    }
    for (int i = 1; i <= fourWays; i++)
    {
        int tempX = (rand() % 18) + 1;
        int tempY = (rand() % 18) + 1;
        if (map[tempX][tempY] == ' ')
        {
            bool freeAround = true;
            for (int x = tempX - 1; x <= tempX + 1; x++)
                for (int y = tempY - 1; y <= tempY + 1; y++)
                    if (map[x][y] == '@')
                    {
                        freeAround = false;
                        break;
                    }
            if (freeAround)
                map[tempX][tempY] = '#';
            else
                i--;
        }
        else
            i--;
    }
    for (int i = 0; i < carNum; i++)
    {
        int tempX = (rand() % 20);
        int tempY = (rand() % 20);
        if (map[tempX][tempY] == ' ')
        {
            c[i].row = tempX;
            c[i].col = tempY;
            carsDirection(i, c);
        }
        else
            i--;
    }
    boardDraw(map, carNum, c);
}

void boardDraw(char **map, int carNum, struct carsInfo *c)
{

    system("clear");
    cout << "    ";
    for (int i = 1; i <= 20; i += 2)
        cout << "^   ";
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        string sign;
        if (i % 2 == 0)
            sign = "-> ";
        else
            sign = "<- ";
        cout << sign << "|";
        for (int j = 0; j < width; j++)
        {
            int m = 0;
            bool isCar = false;
            for (m = 0; m < carNum; m++)
                if (i == c[m].row && j == c[m].col)
                {
                    isCar = true;
                    break;
                }
            if (isCar)
                // cout << c[m].direction << ' ';
                cout << "* ";
            else
                cout << map[i][j] << ' ';
        }
        cout << "| " << sign << endl;
    }
    cout << "    ";
    for (int i = 1; i <= 20; i += 2)
        cout << "^   ";
    cout << endl;
}

void gameLogic(char **map, int carNum, struct carsInfo *c)
{
    for (int i = 0; i < carNum; i++)
    {
        bool isFree = true;
        char d = c[i].direction;
        bool condition = map[c[i].row][c[i].col] == '#' || c[i].row == 19 || c[i].row == 0 || c[i].col == 19 || c[i].col == 0;
        if (!c[i].aroundSquare && condition)
            carsDirection(i, c);
        d = c[i].direction;
        if (d == 'u' && c[i].row == 0)
            c[i].direction = 'r';
        else if (d == 'd' && c[i].row == 19)
            c[i].direction = 'l';
        else if (d == 'l' && c[i].col == 0)
            c[i].direction = 'u';
        else if (d == 'r' && c[i].col == 19)
            c[i].direction = 'd';
        if (!c[i].aroundSquare)
            isAroundSquare(map, i, c);
        if (c[i].aroundSquare)
        {
            if (c[i].row + 1 == c[i].squareRow && c[i].col + 1 == c[i].squareCol)
                c[i].direction = 'r';
            else if (c[i].row + 1 == c[i].squareRow && c[i].col == c[i].squareCol && c[i].col % 2 == 0)
            {
                c[i].direction = direc[rand() % 2];
                if (c[i].direction == 'u')
                    c[i].aroundSquare = false;
            }
            else if (c[i].row + 1 == c[i].squareRow && c[i].col - 1 == c[i].squareCol)
                c[i].direction = 'd';
            else if (c[i].row == c[i].squareRow && c[i].col - 1 == c[i].squareCol && c[i].row % 2 == 0)
            {
                c[i].direction = direc[(rand() % 2) + 1];
                if (c[i].direction == 'r')
                    c[i].aroundSquare = false;
            }
            else if (c[i].row - 1 == c[i].squareRow && c[i].col - 1 == c[i].squareCol)
                c[i].direction = 'l';
            else if (c[i].row - 1 == c[i].squareRow && c[i].col == c[i].squareCol && c[i].col % 2 == 1)
            {
                c[i].direction = direc[(rand() % 2) + 2];
                if (c[i].direction == 'd')
                    c[i].aroundSquare = false;
            }
            else if (c[i].row - 1 == c[i].squareRow && c[i].col + 1 == c[i].squareCol)
                c[i].direction = 'u';
            else if (c[i].row == c[i].squareRow && c[i].col + 1 == c[i].squareCol && c[i].row % 2 == 1)
            {
                c[i].direction = direc[(rand() % 2) + 3];
                if (c[i].direction == 'l')
                    c[i].aroundSquare = false;
            }
        }
        if (!c[i].aroundSquare && !condition)
            isAroundSquare(map, i, c);
        switch (c[i].direction)
        {
        case 'u':
            for (int j = 0; j < carNum; j++)
                if (c[i].row - 1 == c[j].row && c[i].col == c[j].col)
                    isFree = false;
            if (c[i].row == 0)
            {
                c[i].direction = 'r';
                c[i].col++;
            }
            else if (isFree || c[i].aroundSquare)
                c[i].row--;
            break;
        case 'd':
            for (int j = 0; j < carNum; j++)
                if (c[i].row + 1 == c[j].row && c[i].col == c[j].col)
                    isFree = false;
            if (c[i].row == 19)
            {
                c[i].direction = 'l';
                c[i].col--;
            }
            else if (isFree || c[i].aroundSquare)
                c[i].row++;
            break;
        case 'l':
            for (int j = 0; j < carNum; j++)
                if (c[i].row == c[j].row && c[i].col - 1 == c[j].col)
                    isFree = false;
            if (c[i].col == 0)
            {
                c[i].direction = 'u';
                c[i].row--;
            }
            else if (isFree || c[i].aroundSquare)
                c[i].col--;
            break;
        case 'r':
            for (int j = 0; j < carNum; j++)
                if (c[i].row == c[j].row && c[i].col + 1 == c[j].col)
                    isFree = false;
            if (c[i].col == 19)
            {
                c[i].direction = 'd';
                c[i].row++;
            }
            else if (isFree || c[i].aroundSquare)
                c[i].col++;
        }
    }
}

void isAroundSquare(char **map, int i, struct carsInfo *c)
{
    char d = c[i].direction;
    bool condition = map[c[i].row][c[i].col] == '#' || c[i].row == 19 || c[i].row == 0 || c[i].col == 19 || c[i].col == 0;
    switch (d)
    {
    case 'u':
        if (map[c[i].row - 1][c[i].col] == '@')
        {
            c[i].squareRow = c[i].row - 1;
            c[i].squareCol = c[i].col;
            c[i].aroundSquare = true;
            c[i].direction = 'l';
        }
        break;
    case 'd':
        if (map[c[i].row + 1][c[i].col] == '@')
        {
            c[i].squareRow = c[i].row + 1;
            c[i].squareCol = c[i].col;
            c[i].aroundSquare = true;
            c[i].direction = 'r';
        }
        break;
    case 'l':
        if (map[c[i].row][c[i].col - 1] == '@')
        {
            c[i].squareRow = c[i].row;
            c[i].squareCol = c[i].col - 1;
            c[i].aroundSquare = true;
            c[i].direction = 'd';
        }
        break;
    case 'r':
        if (map[c[i].row][c[i].col + 1] == '@')
        {
            c[i].squareRow = c[i].row;
            c[i].squareCol = c[i].col + 1;
            c[i].aroundSquare = true;
            c[i].direction = 'u';
        }
        break;
    default:
        c[i].aroundSquare = false;
    }
}

void carsDirection(int i, struct carsInfo *c)
{
    if (c[i].row % 2 == 0)
    {
        if (c[i].col % 2 == 0)
            c[i].direction = direc[rand() % 2];
        else
            c[i].direction = direc[(rand() % 2) + 1];
    }
    else if (c[i].col % 2 == 0)
        c[i].direction = direc[(rand() % 2) + 3];
    else
        c[i].direction = direc[(rand() % 2) + 2];
}