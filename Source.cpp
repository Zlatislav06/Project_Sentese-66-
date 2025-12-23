#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
const int DECK = 24;
const int MAX_SUITS = 9;
const int ELEMENT = 3;
const int CMD_SIZE = 100;
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
bool CheckSuit(char* string1, const char* string2)
{
	int size = 0;
	while (*(string2 + size) != '\0')
	{
		size++;
	}
	bool check = true;
	for (int i = 0; i < size; i++)
	{
		if (*(string1 + i) != *(string2 + i))
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
void printColor(Card card)
{
	if (CheckSuit(card.suits, "Spades"))
	{

		setColor(Color::Gray);
		cout << "\xE2\x99\xA0";
		setColor(Color::White);

	}
	else if (CheckSuit(card.suits, "Hearts"))
	{

		setColor(Color::Red);
		cout << "\xE2\x99\xA5";
		setColor(Color::White);

	}
	else if (CheckSuit(card.suits, "Diamonds"))
	{

		setColor(Color::Red);
		cout << "\xE2\x99\xA6";
		setColor(Color::White);

	}
	else if (CheckSuit(card.suits, "Clubs"))
	{

		setColor(Color::Gray);
		cout << "\xE2\x99\xA3";
		setColor(Color::White);

	}
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
void HandPrint(Card * hand)
{
	cout << hand[0].numbers;
	printColor(hand[0]);
	for (int i = 1; i < HAND_COUNT; i++)
	{
		cout << ", ";
		cout << hand[i].numbers;
		printColor(hand[i]);

	}
}
int Points(char *number_of_suits)
{
	int r = 0;
	if (CheckSuit(number_of_suits, "A"))
	{
		r=11;
	}
	if (CheckSuit(number_of_suits, "10"))
	{
		r=10;
	}
	if (CheckSuit(number_of_suits, "K"))
	{
		r=4;
	}
	if (CheckSuit(number_of_suits, "Q"))
	{
		r=3;
	}
	if (CheckSuit(number_of_suits, "J"))
	{
		r=2;
	}
	if (CheckSuit(number_of_suits, "9"))
	{
		r=0;
	}
	return r;
}
int WinPoints(char* p1,char* p2,bool& winner)
{
	int points_of_p1 = Points(p1);
	int points_of_p2 = Points(p2);
	if (points_of_p1 > points_of_p2)
	{
		winner = true;
		return points_of_p1+ points_of_p2;
	}
	if (points_of_p1 < points_of_p2)
	{
		winner = false;
		return points_of_p1 + points_of_p2;
	}

}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	srand(time(nullptr));
	
	char comand[CMD_SIZE];
	char bottom_card[CMD_SIZE];
	
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
			cin.getline(comand, CMD_SIZE);
			if (CheckString(comand, "start"))
			{
				cout << "You can choose whether to play against the computer or not." << endl;
				cout << "> Player vs Player (p or P)" << endl;
				cout << "> Computer vs Player (c or C)" << endl << endl << '>';
				cin.ignore();
				cin.getline(comand, CMD_SIZE);
				if (CheckString(comand, "Player vs Player") || CheckString(comand, "P") || CheckString(comand, "p"))
				{
					int sum_p1 = 0, sum_p2 = 0;
					cout << "The game started!" << endl;
					Card player1_hand[HAND_COUNT];
					Card player2_hand[HAND_COUNT];
					int card_start_index_p1 = 0, card_end_index_p1 = 3, br = 0, card_start_index_p2 = 0, card_end_index_p2 = 3;
					for (int i = card_start_index_p1; i < card_end_index_p1; i++)
					{
						player1_hand[i] = arr[i + card_start_index_p1+ card_start_index_p2];
						br++;
					}
					card_start_index_p1 += br;
					card_end_index_p1 += br;
					br = 0;
					for (int i = card_start_index_p2; i < card_end_index_p2; i++)
					{
						player2_hand[i] = arr[i + card_start_index_p1+ card_start_index_p2];
						br++;
					}
					card_start_index_p2 += br;
					card_end_index_p2 += br;
					br = 0;
					for (int i = card_start_index_p1; i < card_end_index_p1; i++)
					{
						player1_hand[i] = arr[i + card_start_index_p1 + card_start_index_p2];
						br++;
					}
					card_start_index_p1 += br;
					br = 0;
					for (int i = card_start_index_p2; i < card_end_index_p1; i++)
					{
						player2_hand[i] = arr[i + card_start_index_p1 + card_start_index_p2];
						br++;
					}
					card_start_index_p2 += br;
					br = 0;
					Card bottom_card= arr[card_start_index_p1 + card_start_index_p2];
					br++;
					if (CheckSuit(bottom_card.suits, "Spades"))
					{
						
						cout << "Trump suit:";
						setColor(Color::Gray);
						cout<< "\xE2\x99\xA0";
						setColor(Color::White);
						cout<< "(Spades)" << endl;

						cout << "Bottom card:";
						cout << bottom_card.numbers;
						setColor(Color::Gray);
						cout<< "\xE2\x99\xA0" << endl;
						setColor(Color::White);
					}
					else if(CheckSuit(bottom_card.suits, "Hearts"))
					{
						cout << "Trump suit:";
						setColor(Color::Red);
						cout << "\xE2\x99\xA5";
						setColor(Color::White);
						cout << "(Hearts)" << endl;

						cout << "Bottom card:";
						
						cout << bottom_card.numbers;
						setColor(Color::Red);
						cout<< "\xE2\x99\xA5" << endl;
						setColor(Color::White);
					}
					else if (CheckSuit(bottom_card.suits, "Diamonds"))
					{
						cout << "Trump suit:";
						setColor(Color::Red);
						cout << "\xE2\x99\xA6";
						setColor(Color::White);
						cout << "(Diamonds)" << endl;

						cout << "Bottom card:";
						
						cout << bottom_card.numbers;
						setColor(Color::Red);
						cout<< "\xE2\x99\xA6" << endl;
						setColor(Color::White);
					}
					else if (CheckSuit(bottom_card.suits, "Clubs"))
					{
						cout << "Trump suit:";
						setColor(Color::Gray);
						cout << "\xE2\x99\xA3";
						setColor(Color::White);
						cout << "(Clubs)" << endl;

						cout << "Bottom card:";
						cout << bottom_card.numbers;
						setColor(Color::Gray);
						cout<< "\xE2\x99\xA3" << endl;
						setColor(Color::White);
					}
					cout << endl;
					while (true)
					{
						cout << "Players have several actions to control the hand:" << endl;
						cout << "> hand" << endl;
						cout << "> play" << endl;
						cout << "> switch-nine" << endl;
						if (player_turn)
						{
							cout << "Player 1's turn" << endl << endl << '>';
						}
						else
						{
							cout << "Player 2's turn" << endl << endl << '>';
						}
						
						cin.getline(comand, CMD_SIZE);
						if (CheckSuit(comand, "hand"))
						{
							cout << endl;
							if (player_turn)
							{
								cout << "Your hand(P1): [";
								HandPrint(player1_hand);
								cout << "]";
							}
							else
							{
								cout << "Your hand(P2): [";
								HandPrint(player2_hand);
								cout << "]";
							}
							cout << endl<<endl;
						}
						else if (CheckSuit(comand, "play") || CheckSuit(comand, "p"))
						{
							int index_p1,index_p2;
							while (true)
							{
								cout << "Select the card you want to play using the index(0-5):";
								cin >> index_p1;
								if (index_p1 < 0 || index_p1>5)
								{
									setColor(Color::Red);
									cout << "Invalid index! Try again!" << endl;
									setColor(Color::White);
								}
								else
								{
									break;
								}
							}
							if (player_turn)
							{
								cout << "You(P1) choose: " << player1_hand[index_p1].numbers;
								printColor(player1_hand[index_p1]);
								
								
							}
							else
							{
								cout << "You(P2) choose: " << player2_hand[index_p2].numbers;
								printColor(player2_hand[index_p2]);
							}
							cout << endl;
							if (player_turn)
							{
								cout << "Player 2's turn" << endl<<endl;
								cout << "Your hand(P2): [";
								HandPrint(player2_hand);
								cout << "]"<<endl<<endl;
								cout << "Select the card you want to play using the index(0-5):";
								cin >> index_p2;
								while (true)
								{
									if (index_p2 < 0 || index_p2>5)
									{
										setColor(Color::Red);
										cout << "Invalid index! Try again!" << endl;
										setColor(Color::White);
									}
									else
									{
										break;
									}
								}
								
								cout << "You(P2) choose: " << player2_hand[index_p2].numbers;
								printColor(player2_hand[index_p2]);
								bool winner = true;
								int win_points = WinPoints(player1_hand[index_p1].numbers, player2_hand[index_p2].numbers, winner);
								if (CheckSuit(player1_hand[index_p1].suits, player2_hand[index_p2].suits))
								{
									
									
										
										
										if (winner)
										{
											sum_p1 += win_points;
											player_turn = true;
										}
										else
										{
											sum_p2 += win_points;
											player_turn = false;
										}
								}
								else
								{
									if (CheckSuit(player1_hand[index_p1].suits, bottom_card.suits))
									{
										sum_p1 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
										player_turn = true;
									}
									else if (CheckSuit(player2_hand[index_p2].suits, bottom_card.suits))
									{
										sum_p2 += Points(player2_hand[index_p2].numbers)+ Points(player1_hand[index_p1].numbers);
										player_turn = false;
									}
									else
									{

										sum_p1 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
										player_turn = true;
									}
								}
								player1_hand[index_p1] = arr[card_start_index_p1 + card_start_index_p2 + br];
								br++;
								player2_hand[index_p2] = arr[card_start_index_p1 + card_start_index_p2 + br];
								br++;


							}
							else
							{
								cout << "Player 1's turn" << endl << endl;
								cout << "Your hand(P1): [";
								HandPrint(player1_hand);
								cout << "]" << endl << endl;
								cout << "Select the card you want to play using the index(0-5):";
								cin >> index_p1;
								while (true)
								{
									if (index_p1 < 0 || index_p1>5)
									{
										setColor(Color::Red);
										cout << "Invalid index! Try again!" << endl;
										setColor(Color::White);
									}
									else
									{
										break;
									}
								}

								cout << "You(P1) choose: " << player1_hand[index_p1].numbers;
								printColor(player1_hand[index_p1]);
								bool winner = true;
								int win_points = WinPoints(player1_hand[index_p1].numbers, player2_hand[index_p2].numbers, winner);
								if (CheckSuit(player1_hand[index_p1].suits, player2_hand[index_p2].suits))
								{




									if (winner)
									{
										sum_p2 += win_points;
										player_turn = true;
									}
									else
									{
										sum_p1 += win_points;
										player_turn = false;
									}
								}
								else
								{
									if (CheckSuit(player1_hand[index_p1].suits, bottom_card.suits))
									{
										sum_p1 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
										player_turn = true;
									}
									else if (CheckSuit(player2_hand[index_p2].suits, bottom_card.suits))
									{
										sum_p2 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
										player_turn = false;
									}
									else
									{

										sum_p2 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
										player_turn = true;
									}
								}
								
								player2_hand[index_p2] = arr[card_start_index_p1 + card_start_index_p2 + br];
								br++;
								player1_hand[index_p1] = arr[card_start_index_p1 + card_start_index_p2 + br];
								br++;
							}
							
							cout << endl << endl;
							cout << "Result:" << endl;
							cout << "P1: " << sum_p1 << endl;
							cout << "P2: " << sum_p2 << endl;
							
						}
						else if (CheckString(comand, "switch-nine"))
						{

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
