//#include<iostream>
//#include<conio.h>
//#include<Windows.h>
//#include<string>
//using namespace std;
//
//class UI
//{
//private:
//	int width, height;
//	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
//	DWORD dwWritten;
//	SMALL_RECT windowSize;
//	BOOL ForceDraw = true;
//	COORD CursorCurrentPos;
//	BOOL StartSelected = true;
//	CONSOLE_CURSOR_INFO ConCurInfo;
//
//public:
//	//Shows Start menu of the Snake Game
//	void StartMenu()
//	{
//		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
//		GetConsoleCursorInfo(hOutput, &ConCurInfo);
//		ConCurInfo.bVisible = false;
//		SetConsoleCursorInfo(hOutput, &ConCurInfo);
//
//		this->width = ConsoleScreenBufferInfo.dwSize.X;
//		this->height = ConsoleScreenBufferInfo.srWindow.Bottom;
//		windowSize = ConsoleScreenBufferInfo.srWindow;
//		CONSOLE_FONT_INFOEX cfi;
//		cfi.cbSize = sizeof cfi;
//		cfi.nFont = 0;
//		cfi.dwFontSize.X = 15;
//		cfi.dwFontSize.Y = 15;
//		cfi.FontFamily = FF_DONTCARE;
//		cfi.FontWeight = FW_NORMAL;
//		SetCurrentConsoleFontEx(hOutput, false, &cfi);
//		system("cls");
//		while (true)
//		{
//			if (WindowSizeChanged() || ForceDraw)
//			{
//				SetConsoleCursorInfo(hOutput, &ConCurInfo);
//				SetConsoleCursorPosition(hOutput, GetMiddleOfTheScreen(width, height, "START"));
//				GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
//				CursorCurrentPos = ConsoleScreenBufferInfo.dwCursorPosition;
//				cout << "START";
//				if (StartSelected)
//					FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_BLUE, 5, GetMiddleOfTheScreen(width, height, "START"), &dwWritten);
//				else
//					FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN, 5, GetMiddleOfTheScreen(width, height, "START"), &dwWritten);
//
//				SetConsoleCursorPosition(hOutput, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 });
//				cout << "EXIT";
//				if (StartSelected)
//					FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN, 4, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 }, &dwWritten);
//				else
//					FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_BLUE, 4, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 }, &dwWritten);
//				ForceDraw = false;
//			}
//			if (_kbhit())
//			{
//				int key = _getch();
//				if (key == 'w' || key == 'W')
//				{
//					StartSelected = true;
//					ForceDraw = true;
//				}
//				if (key == 's' || key == 'S')
//				{
//					StartSelected = false;
//					ForceDraw = true;
//				}
//				if (key == '\x0D')
//				{
//					if (StartSelected)
//					{
//						SetConsoleCursorPosition(hOutput, GetMiddleOfTheScreen(width, height, "START"));
//						cout << "START";
//						FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_RED, 5, GetMiddleOfTheScreen(width, height, "START"), &dwWritten);
//					}
//					else
//					{
//						SetConsoleCursorPosition(hOutput, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 });
//						cout << "EXIT";
//						FillConsoleOutputAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_RED, 4, COORD{ CursorCurrentPos.X, CursorCurrentPos.Y + 1 }, &dwWritten);
//						cout << endl << "Exitted Game";
//						cfi.dwFontSize.X = 0;
//						cfi.dwFontSize.Y = 20;
//						SetCurrentConsoleFontEx(hOutput, false, &cfi);
//						break;
//					}
//
//				}
//			}
//		}
//	}
//	//Reurns true if Window size changed.
//	BOOL WindowSizeChanged()
//	{
//		GetConsoleScreenBufferInfo(hOutput, &ConsoleScreenBufferInfo);
//		if (windowSize.Bottom == ConsoleScreenBufferInfo.srWindow.Bottom && windowSize.Left == ConsoleScreenBufferInfo.srWindow.Left && windowSize.Right == ConsoleScreenBufferInfo.srWindow.Right && this->windowSize.Top == ConsoleScreenBufferInfo.srWindow.Top)
//			return false;
//		else
//		{
//			this->width = ConsoleScreenBufferInfo.dwSize.X;
//			this->height = ConsoleScreenBufferInfo.srWindow.Bottom;
//			windowSize = ConsoleScreenBufferInfo.srWindow;
//			system("cls");
//			return true;
//		}
//	}
//	//Returns COORD for the middle of the screen for a string str
//	COORD GetMiddleOfTheScreen(int winWidth, int winHeight, string str)
//	{
//		COORD returnCOORD;
//		returnCOORD.X = (SHORT)winWidth / 2 - str.length();
//		returnCOORD.Y = (SHORT)winHeight / 2 - 1;
//		return returnCOORD;
//	}
//};
//int main()
//{
//	UI ui = UI();
//	ui.StartMenu();
//}
