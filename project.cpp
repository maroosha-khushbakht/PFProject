#include <iostream>
#include <conio.h>
#include <windows.h> 
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(h, &info);
}


void clearScreen()
{
    system("cls");
}

void gridF(char grid[3][3])
{
    cout << endl;
    setColor(14);
    cout << "+---+---+---+" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "|";
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == 'X')
                setColor(12);
            else if (grid[i][j] == 'O')
                setColor(11);
            else
                setColor(7);

            cout << " " << grid[i][j] << " ";
            setColor(14);
            cout << "|";
        }
        cout << endl;
        cout << "+---+---+---+" << endl;
    }
    setColor(7);
}


bool check(char grid[3][3], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][0] == player &&
            grid[i][1] == player &&
            grid[i][2] == player)
            return true;
    }

    for (int j = 0; j < 3; j++)
    {
        if (grid[0][j] == player &&
            grid[1][j] == player &&
            grid[2][j] == player)
            return true;
    }

    if (grid[0][0] == player &&
        grid[1][1] == player &&
        grid[2][2] == player)
        return true;

    if (grid[0][2] == player &&
        grid[1][1] == player &&
        grid[2][0] == player)
        return true;

    return false;
}

bool draw(char grid[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == ' ')
                return false;

    return true;
}

void playTicTacToe()
{
    char grid[3][3] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char turn = 'X';

    while (true)
    {
        clearScreen();
        cout << "TIC TAC TOE" << endl;
        gridF(grid);

        cout << "Player " << turn << endl;
        cout << "Press 1-9 to place, Q to quit" << endl;

        char key = _getch();

        if (key == 'q' || key == 'Q')
            break;

        int pos = key - '0';

        if (pos < 1 || pos > 9)
            continue;

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;

        if (grid[r][c] != ' ')
            continue;
         
        grid[r][c] = turn;

        if (check(grid, turn))
        {
            clearScreen();
            gridF(grid);
            cout << "Player " << turn << " wins!";
            _getch();
            break;
        }

        if (draw(grid))
        {
            clearScreen();
            gridF(grid);
            cout << "It's a draw!";
            _getch();
            break;
        }

        if (turn == 'X')
            turn = 'O';
        else
            turn = 'X';
    }
}

void playNumberGuessing()
{
    clearScreen();
    srand((unsigned)time(0));

    int secret = rand() % 100 + 1;
    int guess = 0;
    int attempts = 0;

    setColor(11);
    cout << "===============================" << endl;
    cout << "      NUMBER GUESSING GAME     " << endl;
    cout << "===============================" << endl << endl;
    setColor(7);

    cout << "Guess a number between ";
    setColor(14);
    cout << "1 and 100" << endl;
    setColor(7);

    cout << "Press ";
    setColor(12);
    cout << "0";
    setColor(7);
    cout << " to quit" << endl;

    while (true)
    {
        setColor(14);
        cout << endl << "Enter guess: ";
        setColor(7);
        cin >> guess;

        if (guess == 0)
            break;

        attempts++;

        int diff = guess - secret;
        if (diff < 0)
            diff = -diff;

        if (guess == secret)
        {
            setColor(10);
            cout << endl << "Correct!" << endl;
            setColor(11);
            cout << "Attempts: " << attempts << endl;
            setColor(7);
            _getch();
            break;
        }
        else if (guess < secret)
        {
            if (diff <= 10)
            {
                setColor(12);
                cout << "Low" << endl;
            }
            else
            {
                setColor(12);
                cout << "Too low" << endl;
            }
        }
        else
        {
            if (diff <= 10)
            {
                setColor(12);
                cout << "High" << endl;
            }
            else
            {
                setColor(14);
                cout << "Too high" << endl;
            }
        }
    }
}


void setCursorPosition(int x, int y)
{
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

const int MAX_LEN = 50;

void drawSnake(int x[], int y[], int len, int fx, int fy)
{
    setCursorPosition(0, 0);

    setColor(14);
    for (int i = 0; i < 64; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < 22; i++)
    {
        setColor(14);
        cout << "#";   

        for (int j = 0; j < 62; j++)
        {
            bool printed = false;

            if (i == fy && j == fx)
            {
                setColor(12);
                cout << "@";
                printed = true;
            }

            for (int k = 0; k < len; k++)
            {
                if (x[k] == j && y[k] == i)
                {
                    if (k == 0)
                        setColor(10), cout << "O";
                    else
                        setColor(2), cout << "o";
                    printed = true;
                    break;
                }
            }

            if (!printed)
            {
                setColor(7);
                cout << " ";
            }
        }

        setColor(14);
        cout << "#";   
        cout << endl;
    }


    setColor(14);
    for (int i = 0; i < 64; i++) cout << "#";
    setColor(7);
}

void spawnFood(int& fx, int& fy)
{
    fx = rand() % 60 + 1;
    fy = rand() % 20 + 1;
}

void moveSnake(char input, int x[], int y[], int len)
{
    for (int i = len - 1; i > 0; i--)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    if (input == 'w') y[0]--;
    else if (input == 's') y[0]++;
    else if (input == 'a') x[0]--;
    else if (input == 'd') x[0]++;
}

bool hitWall(int x, int y)
{
    return (x < 0 || y < 0 || x >= 62 || y >= 22);
}


bool hitSelf(int x[], int y[], int len)
{
    for (int i = 1; i < len; i++)
    {
        if (x[0] == x[i] && y[0] == y[i])
            return true;
    }
    return false;
}

void printMsg(const char* msg)
{
    setColor(11);
    cout << msg << endl;
    setColor(7);
}

void printMsg(const char* msg, int value)
{
    setColor(10);
    cout << msg << value << endl;
    setColor(7);
}

int loadSnakeHighScore()
{
    int high = 0;
    ifstream fin("snake_score.txt");
    if (fin)
        fin >> high;
    fin.close();
    return high;
}

void saveSnakeHighScore(int score)
{
    ofstream fout("snake_score.txt");
    fout << score;
    fout.close();
}


void playSnake()
{

    hideCursor();

    int highScore = loadSnakeHighScore();
    

    int x[50], y[50];
    int len = 5;

    for (int i = 0; i < len; i++)
    {
        x[i] = 30 - i;
        y[i] = 10;
    }

    int fx, fy;
    spawnFood(fx, fy);

    char input = 'd';

    cout << "SNAKE GAME" << endl;
    cout << "W A S D to move | X to exit" << endl;
    printMsg("High Score: ", highScore);
    _getch();

    while (true)
    {
        drawSnake(x, y, len, fx, fy);

        if (_kbhit())
            input = _getch();

        if (input == 'x' || input == 'X')
            break;

        moveSnake(input, x, y, len);

        if (x[0] == fx && y[0] == fy)
        {
            if (len < 50)
                len++;
            spawnFood(fx, fy);
        }

        if (hitWall(x[0], y[0]) || hitSelf(x, y, len))
        {
            clearScreen();

            int score = len - 5;
            int highScore = loadSnakeHighScore();

            cout << "Game Over!" << endl;
            cout << "Score: " << score << endl;

            if (score > highScore)
            {
                saveSnakeHighScore(score);
                cout << "New High Score!" << endl;
            }
            else
            {
                cout << "High Score: " << highScore << endl;
            }

            _getch();
            break;
        }


        Sleep(120);
    }
}

const int s = 4;
void draw2048(int board[s][s])
{
    clearScreen();
    cout << "===== 2048 =====" << endl;

    setColor(14);
    cout << "+----+----+----+----+" << endl;

    for (int i = 0; i < s; i++)
    {
        cout << "|";
        for (int j = 0; j < s; j++)
        {
            if (board[i][j] == 0)
                setColor(7);
            else if (board[i][j] == 2)
                setColor(10);
            else if (board[i][j] == 4)
                setColor(11);
            else
                setColor(12);

            if (board[i][j] == 0)
                cout << "    ";
            else
                cout << board[i][j] << "   ";

            setColor(14);
            cout << "|";
        }
        cout << endl;
        cout << "+----+----+----+----+" << endl;
    }

    setColor(7);
    cout << "W A S D to move | Q to quit";
}


void spawnTile(int board[s][s])
{
    int r, c;
    do
    {
        r = rand() % s;
        c = rand() % s;
    } while (board[r][c] != 0);

    board[r][c] = 2;
}

void shiftLeft(int row[])
{
    int temp[s] = { 0 };
    int idx = 0;

    for (int i = 0; i < s; i++)
        if (row[i] != 0)
            temp[idx++] = row[i];

    for (int i = 0; i < s - 1; i++)
    {
        if (temp[i] == temp[i + 1])
        {
            temp[i] *= 2;
            temp[i + 1] = 0;
        }
    }

    int finalRow[s] = { 0 };
    idx = 0;
    for (int i = 0; i < s; i++)
        if (temp[i] != 0)
            finalRow[idx++] = temp[i];

    for (int i = 0; i < s; i++)
        row[i] = finalRow[i];
}

void moveLeft(int board[s][s])
{
    for (int i = 0; i < s; i++)
        shiftLeft(board[i]);
}

void rotateBoard(int board[s][s])
{
    int temp[s][s];

    for (int i = 0; i < s; i++)
        for (int j = 0; j < s; j++)
            temp[j][s - 1 - i] = board[i][j];

    for (int i = 0; i < s; i++)
        for (int j = 0; j < s; j++)
            board[i][j] = temp[i][j];
}

int load2048Best()
{
    int best = 0;
    ifstream fin("2048_score.txt");
    if (fin)
        fin >> best;
    fin.close();
    return best;
}

void save2048Best(int best)
{
    ofstream fout("2048_score.txt");
    fout << best;
    fout.close();
}

int getMaxTile(int board[s][s])
{
    int mx = 0;
    for (int i = 0; i < s; i++)
        for (int j = 0; j < s; j++)
            if (board[i][j] > mx)
                mx = board[i][j];
    return mx;
}

void play2048()
{
    hideCursor();
    int bestTile = load2048Best();
    int board[s][s] = { 0 };
    srand(time(0));

    spawnTile(board);
    spawnTile(board);
    printMsg("Best Tile: ", bestTile);

    while (true)
    {
        draw2048(board);
        char key = _getch();

        if (key == 'q' || key == 'Q')
            break;

        if (key == 'a')
            moveLeft(board);
        else if (key == 'd')
        {
            rotateBoard(board);
            rotateBoard(board);
            moveLeft(board);
            rotateBoard(board);
            rotateBoard(board);
        }
        else if (key == 'w')
        {
            rotateBoard(board);
            rotateBoard(board);
            rotateBoard(board);
            moveLeft(board);
            rotateBoard(board);
        }
        else if (key == 's')
        {
            rotateBoard(board);
            moveLeft(board);
            rotateBoard(board);
            rotateBoard(board);
            rotateBoard(board);
        }
        else
            continue;
        int currentMax = getMaxTile(board);

        if (currentMax > bestTile)
        {
            bestTile = currentMax;
            save2048Best(bestTile);
        }

        spawnTile(board);
    }
}


void showMenu()
{
    clearScreen();

    setColor(11);
    cout << "=============================" << endl;
    cout << "       MINI GAME HUB         " << endl;
    cout << "=============================" << endl << endl;

    setColor(10); cout << "1. ";
    setColor(7);  cout << "Tic Tac Toe" << endl;

    setColor(10); cout << "2. ";
    setColor(7);  cout << "Number Guessing" << endl;

    setColor(10); cout << "3. ";
    setColor(7);  cout << "Snake" << endl;

    setColor(10); cout << "4. ";
    setColor(7);  cout << "2048" << endl;

    setColor(12); cout << "5. ";
    setColor(7);  cout << "Exit" << endl << endl;

    setColor(14);
    cout << "Enter Choice: ";
    setColor(7);
}


int main()
{
    int choice = 0;

    while (choice != 5)
    {
        showMenu();
        cin >> choice;

        if (choice == 1)
            playTicTacToe();
        else if (choice == 2)
            playNumberGuessing();
        else if (choice == 3)
            playSnake();
        else if (choice == 4)
            play2048();
        else if (choice == 5)
            break;
        else
        {
            cout << "Invalid choice";
            _getch();
        }
    }

    return 0;
}
