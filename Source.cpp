#include <windows.h>
#include <iostream>

using namespace std;


bool CheckString(char* string1, const char* string2)
{
	int size = 0;
	while (*(string2 + size) != '\0')
	{
		size++;
	}
	bool check = true;
	for (int i = 1; i < size; i++)
	{
		if (*(string1 + i - 1) != *(string2 + i))
		{
			check = false;
		}
	}
	return check;
}
struct Card
{
	char* suits;
	char* numbers;
	char symbol;
};
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
int main()
{
	enum class Color
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Aqua = 3,
		Red = 4,
		Purple = 5,
		Yellow = 6,
		White = 7,
		Gray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightAqua = 11,
		LightRed = 12,
		LightPurple = 13,
		LightYellow = 14,
		BrightWhite = 15
	};
	SetConsoleOutputCP(CP_UTF8);
	
	cout << "\u2660";  // ♠ Пика (Spades)
	cout << "\u2665";  // ♥ Купа (Hearts)
	cout << "\u2666";  // ♦ Каро (Diamonds)
	cout << "\u2663";  // ♣ Спатия (Clubs)
	return 0;
}
