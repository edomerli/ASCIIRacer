#include "Engine/System.hpp"
#include "windows.h"

#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::getline;
using std::runtime_error;

HANDLE hStdout, hStdin;

void System::initialise() {
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("Code 850: Road Madness");

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hStdout, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hStdout, &cursorInfo);
}

bool System::keyIsDown(int key) {
	return GetKeyState(key) & 0x8000;
}

void System::clearScreen() {
	system("cls");
}

Size System::getConsoleSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(hStdout, &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return Size(columns, rows);
}

void System::moveCursor(int x, int y) {
	COORD windowsCoord;
	windowsCoord.X = x;
	windowsCoord.Y = y;
	SetConsoleCursorPosition(hStdout, windowsCoord);
}

void System::setTextColor(Color foreground, Color background)
{
	Color trueForeground, trueBackground;
	if (foreground == Color::No_Color) {
		trueForeground = Color::Bright_White;
	}
	else {
		trueForeground = foreground;
	}

	if (background == Color::No_Color) {
		trueBackground = Color::Black;
	}
	else {
		trueBackground = background;
	}

	SetConsoleTextAttribute(hStdout, (int)trueForeground + 16 * (int)trueBackground);
	return;
}

float System::randomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

std::string System::getExecutableDirectory()
{
	char result[MAX_PATH];
	string executablePath = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
	//return executablePath.substr(0, executablePath.find_last_of("\\/")-9)+"ASCIIRacer";	//questa funziona per Filip
	return executablePath.substr(0, executablePath.find_last_of("\\/"));				//questa funziona per Sam ed Edo
}

vector<string> System::loadFile(string path) {
	ifstream file;
	vector<string> content;

	file.open(path);

	if (!file.is_open()) {
		throw runtime_error("Impossibile aprire il file. " + path);
	}

	string str;
	while (std::getline(file, str))
	{
		content.push_back(str);
	}

	file.close();

	return content;
}