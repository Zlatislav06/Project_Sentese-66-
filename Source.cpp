#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
const int DECK = 24;
const int MAX_SUITS = 9;
const int ELEMENT = 3;
const int SIZE = 100;
const int HAND_COUNT = 6;


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
struct Card
{
	char suits[MAX_SUITS];
	char numbers[ELEMENT];
};
void setColor(Color color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		static_cast<int>(color)
	);
}
bool CheckCardsWhichIsNotNull(Card a)
{
	
	bool check = false;
	if (a.suits != "")
	{
		check = true;
	}
	if (a.numbers != "")
	{
		check = true;
	}
	return check;
	
}
bool RandomRepeat(int *repaete, int random)
{
	bool check = true;
	for (int i = 0; i < DECK; i++)
	{
		if (*(repaete + i) == random)
		{
			check = false;
		}
	}
	return check;
}
void Shuffle(Card* deck)
{
	srand(time(nullptr));
	
	Card new_deck[DECK];
	
	int repeat[DECK];
	for (int i = 0; i < DECK; i++)
	{
		repeat[i] = -1;
	}
	for (int i = 0; i < DECK; i++)
	{
		int random = rand() % DECK;
		if (RandomRepeat(repeat, random))
		{
			new_deck[random] = *(deck + i);
			repeat[i] = random;
		}
		else
		{
			i--;
		}
		
	};
	for (int i = 0; i < DECK; i++)
	{
		*(deck + i)=*(new_deck+i);
	};
}
bool Cleaving(Card* deck,int index)
{
	bool check = true;
	Card new_deck[DECK];
	if (index < 1 && index>24)
	{
		check = false;
		return check;
	}
	for (int i = 0; i < DECK- (index - 1); i++)
	{
		*(new_deck + i) = *(deck + i + (index - 1));
	}
	for (int i = DECK - (index - 1); i < DECK; i++)
	{
		*(new_deck + i) = *(deck + i-(DECK - (index - 1)));
	}
	for (int i = 0; i < DECK; i++)
	{
		*(deck + i) = *(new_deck+i);
	}
	return check;
}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	srand(time(nullptr));
	
	char comand[SIZE];
	char bottom_card[SIZE];

	bool player_turn = true;

	Card arr[DECK] = 
	{
		{"Spades","A"},{"Spades","10"},{"Spades","K"},{"Spades","Q"},{"Spades","J"},{"Spades","9"},
		{"Hearts","A"},{"Hearts","10"},{"Hearts","K"},{"Hearts","Q"},{"Hearts","J"},{"Hearts","9"},
		{"Diamonds","A"},{"Diamonds","10"},{"Diamonds","K"},{"Diamonds","Q"},{"Diamonds","J"},{"Diamonds","9"},
		{"Clubs","A"},{"Clubs","10"},{"Clubs","K"},{"Clubs","Q"},{"Clubs","J"},{"Clubs","9"},
	};
	while (true)
	{
		Shuffle(arr);
		if (Cleaving(arr, 25))
		{
			cout << "If you want any of the following functions to be performed, please type one of the corresponding commands:\n";
			cout << "> start" << endl;
			cout << "> rules" << endl;
			cout << "> settings" << endl << endl << '>';
			cin.ignore();
			cin.getline(comand, SIZE);
			if (CheckString(comand, "start"))
			{
				cout << "You can choose whether to play against the computer or not." << endl;
				cout << "> Player vs Player (p or P)" << endl;
				cout << "> Computer vs Player (c or C)" << endl << endl << '>';
				cin.ignore();
				cin.getline(comand, SIZE);
				if (CheckString(comand, "Player vs Player") || CheckString(comand, "P") || CheckString(comand, "p"))
				{
					cout << "The game started!" << endl;
					Card player1_hand[HAND_COUNT];
					Card player2_hand[HAND_COUNT];
					int card_start_index_p1 = 0, card_end_index_p1 = 3, br = 0, int card_start_index_p2 = 0, card_end_index_p2 = 3;
					for (int i = 0; i < card_end_index_p1; i++)
					{
						player1_hand[i] = arr[i + card_start_index_p1+ card_start_index_p2];
						br++;
					}
					card_start_index_p1 += br;
					card_end_index_p1 += br;
					br = 0;
					for (int i = 0; i < card_end_index_p2; i++)
					{
						player2_hand[i] = arr[i + card_start_index_p1+ card_start_index_p2];
						br++;
					}
					card_start_index_p2 += br;
					card_end_index_p2 += br;
					br = 0;
					for (int i = 0; i < card_end_index_p1; i++)
					{
						player1_hand[i] = arr[i + card_start_index_p1 + card_start_index_p2];
						br++;
					}
					card_start_index_p1 += br;
					br = 0;
					for (int i = 0; i < card_end_index_p1; i++)
					{
						player2_hand[i] = arr[i + card_start_index_p1 + card_start_index_p2];
						br++;
					}
					card_start_index_p2 += br;
					Card bottom_card= arr[card_start_index_p1 + card_start_index_p2];
					if (CheckString(bottom_card.suits, "Spade"))
					{

					}
					switch (random_color)
					{
					case 0:
					{
						char c = 6;
						cout << "Trump suit:" << "\u2660" << "(Spades)" << endl;
						cout << "Bottom card:" << cards[random_card] << "(Spade)" << endl;



						break;
					}
					case 1:
					{
						char c = 3;
						cout << "Trump suit: " << "\u2665" << "(Hearts)" << endl;
						cout << "Bottom card:" << cards[random_card] << "(Heart)" << endl;
						break;
					}
					case 2:
					{
						char c = 4;
						cout << "Trump suit: " << "\u2666" << "(Dimands)" << endl;
						cout << "Bottom card:" << cards[random_card] << "(Dimand)" << endl;
						break;
					}
					case 3:
					{
						char c = 5;
						cout << "Trump suit: " << "\u2663" << "(Clubs)" << endl;
						cout << "Bottom card:" << cards[random_card] << "(Club)" << endl;
						break;
					}
					}
					

				}
			}
			else if (CheckString(comand, "rules"))
			{

				cout << "SANTASE (66)\nEach player gets 6 cards.The Trump suit is chosen at random." << endl;
				cout << "Card values : A = 11, 10 = 10, K = 4, Q = 3, J = 2, 9 = 0." << endl;
				cout << "A marriage(K + Q of the same suit) gives 20 points, or 40 if the trump suit." << endl;
				cout << " The first player to reach 66 points wins the round." << endl;

			}
			else if (CheckString(comand, "settings"))
			{
				cout << "SANTASE (66)\n1) Target points to win[11]" << endl;
				cout << "2) Marriage points(non - trump / trump)[20 / 40]" << endl;
				cout << "3) Show players' points [on]" << endl;
				cout << "4) Last trick + 10[on]" << endl;
				cout << "Enter number to change or 'back' to return:" << endl;




			}
			else
			{

			}
			}
			else
			{

			}
	}
	
	cout << endl;
	for (int i = 0; i < DECK; i++)
	{
		cout << arr[i].numbers << ' ' << arr[i].suits <<endl;
	}

	std::cout << "A\xE2\x99\xA0"; // A♠
	setColor(Color::White);
	std::cout << "\xE2\x99\xA0"; // Spade
	setColor(Color::Red);
	std::cout << "\xE2\x99\xA5"; // Heart
	std::cout << "\xE2\x99\xA6"; // Diamond
	setColor(Color::White);
	std::cout << "\xE2\x99\xA3"; // Club
	return 0;
}
