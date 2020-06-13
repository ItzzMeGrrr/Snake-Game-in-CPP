#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<string>
#include "UserInterface.cpp"
using namespace std;
enum Direction { Up, Down, Right, Left };
class MainClass
{
private:
	int width, height, score = 0, oldScore = 0, snakeLength = 0, snakePartPosX[50], snakePartPosY[50];
	int playerCharCount;
	char playerChar, fruitChar, borderChar, bodyChar;
	bool start = false, printDebug = false, pauseGame = false, isGameOver = false;

	
	Direction PlayerDir = Right;
	COORD CursorCurrentPos, CursorDefaultPos, PlayerPos, FruitPos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
	SMALL_RECT windowSize;
	CONSOLE_FONT_INFOEX fonts;
	DWORD dwWritten;
	CONSOLE_CURSOR_INFO ConCurInfo;

public:
	//MainClass Constructor
	MainClass(int width, int height, char borChar, char PlChar, char fChar, char body)
	{
		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
		this->width = ConsoleScreenBufferInfo.dwSize.X;
		this->height = ConsoleScreenBufferInfo.srWindow.Bottom;
		PlayerPos.X = 10;
		PlayerPos.Y = 10;
		borderChar = borChar;
		playerChar = PlChar;
		fruitChar = fChar;
		bodyChar = body;
		windowSize = ConsoleScreenBufferInfo.srWindow;

		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof cfi;
		cfi.nFont = 0;
		cfi.dwFontSize.X = 13;
		cfi.dwFontSize.Y = 13;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;//
		SetCurrentConsoleFontEx(hOutput, false, &cfi);

		GetConsoleCursorInfo(hOutput, &ConCurInfo);
		ConCurInfo.bVisible = false;
		SetConsoleCursorInfo(hOutput, &ConCurInfo);	
	}
	//Starts Game
	void StartGame()
	{
		DrawMap();
		while (!isGameOver)
		{
			if (WindowSizeChanged())
				DrawMap();
			SpawnFruit(false);
			if (_kbhit())
			{
				int key = _getch();
				if (key == 'W' || key == 'w')// && (!PlayerDir == Down))
					PlayerDir = Up;
				else if (key == 'S' || key == 's')// && (!PlayerDir == Up))
					PlayerDir = Down;
				else if (key == 'D' || key == 'd')// && (!PlayerDir == Left))
					PlayerDir = Right;
				else if (key == 'A' || key == 'a')// && (!PlayerDir == Right))
					PlayerDir = Left;
				else if (key == 'e')
					score += 10;
				else if (key == char(27))
				{
					GameOver("", true);
				}
				else if (key == char(32))
				{
					PauseGame();
				}
			}
			MovePlayer();
			MoveSnakeBody();
			CheckFruitSnakeCollid();
			CheckGameOver();
			if (ScoreChanged())
				DrawScore();
			Sleep(100);
		}
	}
	//Draws Map of the Game
	void DrawMap()
	{
		this->width = ConsoleScreenBufferInfo.dwSize.X - 1;
		this->height = ConsoleScreenBufferInfo.srWindow.Bottom - 5;
		system("cls");
		for (int H = 0; H < height; H++)
		{
			for (int W = 0; W < width; W++)
			{
				if (H == 0 || H == height - 1)
				{
					cout << "#";
				}
				else if (W == 0 || W == width - 1)
				{
					cout << "#";
				}
				else
					cout << " ";
			}
			cout << endl;
		}
		DrawScore();
		SpawnFruit(true);
	}
	//Draws snake according to COORD PlayerPos
	void DrawPlayer()
	{
		PrintAtXY(PlayerPos.X, PlayerPos.Y, string(1, playerChar));
		FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY, 1, PlayerPos, &dwWritten);
	}
	//Moves snake according to player input
	void MovePlayer()
	{
		DrawBlank(PlayerPos.X, PlayerPos.Y);
		if (PlayerDir == Up) {
			PlayerPos.Y--;
		}
		if (PlayerDir == Down) {
			PlayerPos.Y++;
		}
		if (PlayerDir == Left) {
			PlayerPos.X--;
		}
		if (PlayerDir == Right) {
			PlayerPos.X++;
		}
		DrawPlayer();

	}
	//Draws Fruit(Coin) according to COORD FruitPos
	void DrawFruit() {
		PrintAtXY(FruitPos.X, FruitPos.Y, string(1, fruitChar));
		FillConsoleOutputAttribute(hOutput, FOREGROUND_RED, 1, FruitPos, &dwWritten);
	}
	//Spawns a fruit, randomly on the screen
	void SpawnFruit(BOOL ForceDraw)
	{
		if (ScoreChanged() || ForceDraw)
		{
			int a = (int)malloc(sizeof(int));
			srand(a);
			FruitPos.X = abs(rand() % ConsoleScreenBufferInfo.dwSize.X - 1);
			FruitPos.Y = abs(rand() % ConsoleScreenBufferInfo.srWindow.Bottom - 5);
			if (FruitPos.X == 0 || FruitPos.Y == 0 || FruitPos.X >= ConsoleScreenBufferInfo.dwSize.X - 1 || FruitPos.Y >= ConsoleScreenBufferInfo.srWindow.Bottom - 5)
				SpawnFruit(false);
			else
				DrawFruit();

		}
	}
	//Sets Cursor Position
	void SetCursorPos(int X, int Y)
	{
		InitOldCursorPos();
		CursorCurrentPos.X = X;
		CursorCurrentPos.Y = Y;
		SetConsoleCursorPosition(hOutput, CursorCurrentPos);
	}
	//Sets cursor poition at the end of the drawing
	void SetCursorDefaultPos()
	{
		SetConsoleCursorPosition(hOutput, CursorDefaultPos);
	}
	//Stores Cursor's Default Position in COORD CursorDefaultPos
	void InitOldCursorPos()
	{
		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
		CursorDefaultPos.X = ConsoleScreenBufferInfo.dwCursorPosition.X;
		CursorDefaultPos.Y = ConsoleScreenBufferInfo.dwCursorPosition.Y;
	}
	//Checks if player took the Fruit(Coin)
	void CheckFruitSnakeCollid()
	{
		if (FruitPos.X == PlayerPos.X && FruitPos.Y == PlayerPos.Y)
		{
			score += 10;
			snakeLength++;
			DrawScore();
			SpawnFruit(true);
		}
	}
	//Draws a space(blank) on X, Y coordinates
	void DrawBlank(int X, int Y)
	{
		SetCursorPos(X, Y);
		cout << " ";
		SetCursorDefaultPos();
	}
	//Draws Score
	void DrawScore()
	{
		cout << '\r' << "Score: " << score;
	}
	//Checks if game is over
	void CheckGameOver()
	{
		if (PlayerPos.X <= 0 || PlayerPos.X >= width - 1 || PlayerPos.Y <= 0 || PlayerPos.Y >= height - 1)
		{
			GameOver("Hit the walls", false);
		}
	}
	//Stops Game
	void GameOver(string reason, BOOL userExited)
	{
		if (!userExited)
		{
			cout << endl << "GAME OVER!!" << endl << "Reason: " << reason << endl;
		}
		else
		{
			cout << endl << "Exited" << endl;
		}
		isGameOver = true;
	}
	//Prints str to X, Y Coordinates
	void PrintAtXY(int X, int Y, string str)
	{
		SetCursorPos(X, Y);
		cout << str;
		SetCursorDefaultPos();
	}
	//Moves snake's body begind its head
	void MoveSnakeBody()
	{
		int tempX = 1, tempY = 1, tempX1 = 1, tempY1 = 1;
		for (int i = 0; i < snakeLength; i++)
		{
			if (i == 0) {
				tempX = snakePartPosX[i];
				tempY = snakePartPosY[i];
				if (PlayerDir == Left)
				{
					snakePartPosX[i] = PlayerPos.X + 1;
					snakePartPosY[i] = PlayerPos.Y;
				}
				else if (PlayerDir == Right)
				{
					snakePartPosX[i] = PlayerPos.X - 1;
					snakePartPosY[i] = PlayerPos.Y;
				}
				else if (PlayerDir == Up)
				{
					snakePartPosX[i] = PlayerPos.X;
					snakePartPosY[i] = PlayerPos.Y + 1;
				}
				else if (PlayerDir == Down)
				{
					snakePartPosX[i] = PlayerPos.X;
					snakePartPosY[i] = PlayerPos.Y - 1;
				}
			}
			else {
				tempX1 = snakePartPosX[i];
				tempY1 = snakePartPosY[i];

				snakePartPosX[i] = tempX;
				snakePartPosY[i] = tempY;

				tempX = tempX1;
				tempY = tempY1;
			}
		}
		DrawSnakeBody();
	}
	//Draws snake's body
	void DrawSnakeBody()
	{
		for (int i = 0; i < snakeLength; i++)
		{
			FillConsoleOutputAttribute(hOutput, BACKGROUND_BLUE, 1, COORD{ (SHORT)snakePartPosX[i], (SHORT)snakePartPosY[i] }, &dwWritten);
		}
	}
	//Pauses Game
	void PauseGame()
	{
		cout << "GAME PAUSED!! Press any key to continue.";
		if (_getch())
		{
			/*for (int i = 0; i <= 40; i++)
			{
				PrintAtXY(CursorDefaultPos.X - i, CursorDefaultPos.Y, " ");
				FillConsoleOutputAttribute(hOutput, COLOR_BACKGROUND, 1, COORD{ (SHORT)i, CursorDefaultPos.Y}, &dwWritten);
				PrintAtXY(CursorDefaultPos.X - i, CursorDefaultPos.Y, string(1, '\b'));
			}*/
		}
	}
	//Returns true if window size changed, false otherwise
	BOOL WindowSizeChanged()
	{
		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
		if (windowSize.Bottom == ConsoleScreenBufferInfo.srWindow.Bottom && windowSize.Left == ConsoleScreenBufferInfo.srWindow.Left && windowSize.Right == ConsoleScreenBufferInfo.srWindow.Right && this->windowSize.Top == ConsoleScreenBufferInfo.srWindow.Top)
			return false;
		else
		{
			this->width = ConsoleScreenBufferInfo.dwSize.X - 1;
			this->height = ConsoleScreenBufferInfo.srWindow.Bottom - 5;
			windowSize = ConsoleScreenBufferInfo.srWindow;
			return true;
		}
	}
	//Returns true if score changed false otherwise
	BOOL ScoreChanged()
	{
		if (score == oldScore)
			return false;
		else
		{
			oldScore = score;
			return true;
		}
	}
};
int main()
{
	LPCSTR ConsoleTitle = "Snake Game";
	SetConsoleTitle(ConsoleTitle);
	MainClass MC = MainClass(50, 20, '#', 'O', 'Q', char(153));
	//UI ui = UI();
	MC.StartGame();
	//ui.StartMenu();
	_getch();
	return 0;
}

