#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
const int DECK = 24;
const int MAX_SUITS = 9;
const int ELEMENT = 3;
const int CMD_SIZE = 100;
const int HAND_COUNT = 6;
const int MARRIAGE = 2;
const int SETTINGS = 4;
const int BOOLELEMENT1 = 0;
const int BOOLELEMENT2 = 1;
const int FILEREADER = 1024;
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
			break;
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
	if (index < 1 || index>24)
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
void HandPrintAfterDeck(Card* hand,int size)
{
	cout << hand[0].numbers;
	printColor(hand[0]);
	for (int i = 1; i < size; i++)
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
void ReplaceWithLastCard(Card* deck,Card card)
{
	Card new_deck[DECK];
	Card last_card = deck[DECK-1];
	for (int i = 0; i < DECK; i++)
	{
		if (CheckSuit(deck[i].suits, card.suits) && CheckSuit(deck[i].numbers, card.numbers))
		{
			new_deck[i] = last_card;
		}
		else if (CheckSuit(deck[i].suits, last_card.suits) && CheckSuit(deck[i].numbers, last_card.numbers))
		{
			new_deck[i] = card;
		}
		else
		{
			new_deck[i] = deck[i];
		}
		
	}
	for (int i = 0; i < DECK; i++)
	{
		*(deck + i) = new_deck[i];
	}
}
void SwitchWithNine(Card* deck, Card * hand, Card nine)
{
	Card new_deck[DECK];
	Card new_hand[HAND_COUNT];
	Card last_card = deck[DECK - 1];
	for (int i = 0; i < DECK; i++)
	{
		if (CheckSuit(deck[i].suits, last_card.suits) && CheckSuit(deck[i].numbers, last_card.numbers))
		{
			new_deck[i] = nine;
		}
		else
		{
			new_deck[i] = deck[i];
		}

	}
	for (int i = 0; i < HAND_COUNT; i++)
	{
		if (CheckSuit(deck[i].suits, nine.suits) && CheckSuit(deck[i].numbers, nine.numbers))
		{
			new_hand[i] = last_card;
		}
		else
		{
			new_hand[i] = hand[i];
		}
	}
	for (int i = 0; i < DECK; i++)
	{
		*(deck + i) = new_deck[i];
	}
	for (int i = 0; i < HAND_COUNT; i++)
	{
		*(hand + i) = new_hand[i];
	}
}
void CheckWithPrint(Card* arr)
{
	for (int i = 0; i < DECK; i++)
	{
		cout <<endl<<i+1<<") " << arr[i].numbers;
		printColor(arr[i]);
		cout << ", ";

	}
}
bool SerachForCardFromEqualSuit(Card * hand,Card card,int size)
{
	bool check = false;
	for (int i = 0; i < size; i++)
	{
		if (CheckSuit(hand[i].suits,card.suits))
		{
			check = true;
			break;
		}
	}
	return check;
}
void EndOfRound(bool player_turn, int sum_p1,int sum_p2,int& points_p1, int& points_p2)
{
	
	
	int win_points_of_round = 0;
	ofstream file("current_result.txt");
	if (!file.is_open())
	{
		cout << "Couldn't open file.";
		return;
	}
	if (player_turn)
	{
		
		if (sum_p1 >= 66)
		{
			if (sum_p2 >= 33)
			{
				win_points_of_round = 1;
			}
			else if (sum_p2 < 33)
			{
				win_points_of_round = 2;
			}
			else if (sum_p2 == 0)
			{
				win_points_of_round = 3;
			}
			points_p1 += win_points_of_round;
			setColor(Color::Green);

			cout << "Player 1 wins the round! (+" << win_points_of_round << " game points)" << endl;
			file << "Winner - Player 1 (+" << win_points_of_round << ") | Player 1: " << sum_p1 << " points | Player 2: " << sum_p2 << " points" << endl;
			setColor(Color::White);
		}
		else
		{
			if (sum_p1 > 0)
			{
				win_points_of_round = 2;
			}
			else if (sum_p1 == 0)
			{
				win_points_of_round = 3;
			}
			points_p2 += win_points_of_round;
			setColor(Color::Red);
			cout << "Player 1 lose!!!" << endl;
			setColor(Color::Green);
			cout << "Player 2 wins the round! (+" << win_points_of_round << " game points)" << endl;
			file << "Winner - Player 2 (+" << win_points_of_round << ") | Player 1: " << sum_p1 << " points | Player 2: " << sum_p2 << " points" << endl;
			setColor(Color::White);
		}
	}
	else
	{
		if (sum_p2 >= 66)
		{
			if (sum_p1 >= 33)
			{
				win_points_of_round = 1;
			}
			else if (sum_p1 < 33)
			{
				win_points_of_round = 2;
			}
			else if (sum_p1 == 0)
			{
				win_points_of_round = 3;
			}
			sum_p2 += win_points_of_round;
			setColor(Color::Green);
			cout << "Player 2 wins the round! (+" << win_points_of_round << " game points)" << endl;
			file << "Winner - Player 2 (+" << win_points_of_round << ") | Player 1: " << sum_p1 << " points | Player 2: " << sum_p2 << " points" << endl;
			setColor(Color::White);
		}
		else
		{
			if (sum_p2 > 0)
			{
				win_points_of_round = 2;
			}
			else if (sum_p2 == 0)
			{
				win_points_of_round = 3;
			}
			points_p1 += win_points_of_round;
			setColor(Color::Red);
			cout << "Player 2 lose!!!" << endl;
			setColor(Color::Green);
			cout << "Player 1 wins the round! (+" << win_points_of_round << " game points)" << endl;
			file << "Winner - Player 1 (+" << win_points_of_round << ") | Player 1: " << sum_p1 << " points | Player 2: " << sum_p2 << " points" << endl;
			setColor(Color::White);
		}
		cout << "Player 1: " << sum_p1 << " | Player 2: " << sum_p2;
	}
	
}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	srand(time(nullptr));
	
	char comand[CMD_SIZE];
	char bottom_card[CMD_SIZE];
	char marriage_suit[MAX_SUITS];
	bool player_turn = true;
	bool specials = false;
	bool check_nine = false;
	bool end = false;
	int cards_of_hand = 6;
	int points_p1 = 0;
	int points_p2 = 0;
	int round = 1;
	bool winner = true;
	bool check_close = true;
	//settings
	int max_points = 11;
	int non_trump_merriage = 20;
	int trump_merriage = 40;
	bool on_or_off[MARRIAGE];
	on_or_off[BOOLELEMENT1] = true;
	on_or_off[BOOLELEMENT2] = true;

	Card last_trick[MARRIAGE];
	Card arr[DECK] = 
	{
		{"Spades","A"},{"Spades","10"},{"Spades","K"},{"Spades","Q"},{"Spades","J"},{"Spades","9"},
		{"Hearts","A"},{"Hearts","10"},{"Hearts","K"},{"Hearts","Q"},{"Hearts","J"},{"Hearts","9"},
		{"Diamonds","A"},{"Diamonds","10"},{"Diamonds","K"},{"Diamonds","Q"},{"Diamonds","J"},{"Diamonds","9"},
		{"Clubs","A"},{"Clubs","10"},{"Clubs","K"},{"Clubs","Q"},{"Clubs","J"},{"Clubs","9"},
	};
	while (true)
	{
		
		
			cout << "If you want any of the following functions to be performed, please type one of the corresponding commands:\n";
			cout << "> start" << endl;
			cout << "> rules" << endl;
			cout << "> settings" << endl << endl << '>';
			cin.ignore();
			cin.getline(comand, CMD_SIZE);
			if (CheckString(comand, "start"))
			{
				
				cout << endl;
				
					cout << "You can choose whether to play against the computer or not." << endl;
					cout << "> Player vs Player (p or P)" << endl;
					cout << "> Computer vs Player (c or C)" << endl << endl << '>';
					
					cin.getline(comand, CMD_SIZE);
					if (CheckSuit(comand, "Player vs Player") || CheckSuit(comand, "P") || CheckSuit(comand, "p"))
					{
						int sum_p1 = 0, sum_p2 = 0;
						cout << "The game started!" << endl<<endl;
						while (points_p1<max_points && points_p2 < max_points)
						{
							int cleaving_index;
							cout << "Player one chooses where to split the deck (write index of card):";
							cin >> cleaving_index;
							 sum_p1 = 0, sum_p2 = 0;
							 Shuffle(arr);
							if (Cleaving(arr, cleaving_index))
							{
								setColor(Color::Aqua);
								cout << "Round " << round<<"!"<<endl<<endl;
								setColor(Color::White);
								Card player1_hand[HAND_COUNT];
								Card player2_hand[HAND_COUNT];
								int card_start_index_p1 = 0, card_end_index_p1 = 3, br = 0, card_start_index_p2 = 0, card_end_index_p2 = 3;
								for (int i = card_start_index_p1; i < card_end_index_p1; i++)
								{
									player1_hand[i] = arr[i + card_start_index_p1 + card_start_index_p2];
									br++;
								}
								card_start_index_p1 += br;
								card_end_index_p1 += br;
								br = 0;
								for (int i = card_start_index_p2; i < card_end_index_p2; i++)
								{
									player2_hand[i] = arr[i + card_start_index_p1 + card_start_index_p2];
									br++;
								}
								card_start_index_p2 += br;
								card_end_index_p2 += br;
								br = 0;
								int index = 0;
								for (int i = card_start_index_p1; i < card_end_index_p1; i++)
								{
									player1_hand[i] = arr[index + card_start_index_p1 + card_start_index_p2];
									br++;
									index++;
								}
								card_start_index_p1 += br;
								br = 0;
								index = 0;
								for (int i = card_start_index_p2; i < card_end_index_p2; i++)
								{
									player2_hand[i] = arr[index + card_start_index_p1 + card_start_index_p2];
									br++;
									index++;
								}
								card_start_index_p2 += br;
								br = 0;
								Card bottom_card = arr[card_start_index_p1 + card_start_index_p2];

								ReplaceWithLastCard(arr, bottom_card);

								if (CheckSuit(bottom_card.suits, "Spades"))
								{

									cout << "Trump suit:";
									setColor(Color::Gray);
									cout << "\xE2\x99\xA0";
									setColor(Color::White);
									cout << "(Spades)" << endl;

									cout << "Bottom card:";
									cout << bottom_card.numbers;
									setColor(Color::Gray);
									cout << "\xE2\x99\xA0" << endl;
									setColor(Color::White);

								}
								else if (CheckSuit(bottom_card.suits, "Hearts"))
								{
									cout << "Trump suit:";
									setColor(Color::Red);
									cout << "\xE2\x99\xA5";
									setColor(Color::White);
									cout << "(Hearts)" << endl;

									cout << "Bottom card:";

									cout << bottom_card.numbers;
									setColor(Color::Red);
									cout << "\xE2\x99\xA5" << endl;
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
									cout << "\xE2\x99\xA6" << endl;
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
									cout << "\xE2\x99\xA3" << endl;
									setColor(Color::White);
								}

								cout << endl;
								bool marrige = false;
								while (cards_of_hand > 0)
								{

									cout << "Players have several actions to control the hand:" << endl;
									cout << "> hand" << endl;
									cout << "> play" << endl;


									if (specials)
									{
										if (!check_nine && check_close)
										{
											cout << "> switch-nine" << endl;
										}
										cout << "> marriage" << endl;
										if (check_close)
										{
											cout << "> close" << endl;
										}
										cout << "> information" << endl;
										cout << "> end" << endl;
									}
									if (player_turn)
									{
										cout << "Player 1's turn" << endl << endl << '>';
									}
									else
									{
										cout << "Player 2's turn" << endl << endl << '>';
									}
									
									cin.getline(comand, CMD_SIZE);
									if (CheckSuit(comand, "hand") || CheckSuit(comand, "h"))
									{
										cout << endl;
										if (cards_of_hand == HAND_COUNT)
										{
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
										}
										else
										{
											if (player_turn)
											{
												cout << "Your hand(P1): [";
												HandPrintAfterDeck(player1_hand, cards_of_hand);
												cout << "]";
											}
											else
											{
												cout << "Your hand(P2): [";
												HandPrintAfterDeck(player2_hand, cards_of_hand);
												cout << "]";
											}
										}

										cout << endl << endl;
									}
									else if (CheckSuit(comand, "play") || CheckSuit(comand, "p"))
									{
										specials = true;
										int index_p1, index_p2;
										if (card_start_index_p1 + card_start_index_p2 + br < DECK)
										{
											if (player_turn)
											{
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
												cout << "You(P1) choose: " << player1_hand[index_p1].numbers;
												printColor(player1_hand[index_p1]);
												if (marrige)
												{

													if (CheckSuit(player1_hand[index_p1].numbers, "K") || CheckSuit(player1_hand[index_p1].numbers, "Q"))
													{
														marrige = false;
														if (CheckSuit(marriage_suit, bottom_card.suits))
														{
															sum_p1 += trump_merriage;
														}
														else
														{
															sum_p1 += non_trump_merriage;
														}
													}
													else
													{
														cout << endl << "You have only marriage, if you play \"K\" and \"Q\" " << endl;
														continue;

													}
												}
											}
											else
											{

												while (true)
												{
													cout << "Select the card you want to play using the index(0-5):";
													cin >> index_p2;
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
												if (marrige)
												{

													if (CheckSuit(player2_hand[index_p2].numbers, "K") || CheckSuit(player2_hand[index_p2].numbers, "Q"))
													{
														marrige = false;
														if (CheckSuit(marriage_suit, bottom_card.suits))
														{
															sum_p2 += trump_merriage;
														}
														else
														{
															sum_p2 += non_trump_merriage;
														}
													}
													else
													{
														cout << endl << "You have only marriage, if you play \"K\" and \"Q\" " << endl;
														continue;

													}
												}

											}
											cout << endl;
											if (player_turn)
											{

												cout << "Player 2's turn" << endl << endl;
												cout << "Your hand(P2): [";
												HandPrint(player2_hand);
												cout << "]" << endl << endl;
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
													cout << "Select the card you want to play using the index(0-5):";
													cin >> index_p2;
												}

												cout << "You(P2) choose: " << player2_hand[index_p2].numbers;
												printColor(player2_hand[index_p2]);
												winner = true;
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
														sum_p2 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
														player_turn = false;
													}
													else
													{

														sum_p1 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
														player_turn = true;
													}
												}
												last_trick[0] = player1_hand[index_p1];
												last_trick[1] = player2_hand[index_p2];
												player1_hand[index_p1] = arr[card_start_index_p1 + card_start_index_p2 + br];
												br++;
												player2_hand[index_p2] = arr[card_start_index_p1 + card_start_index_p2 + br];
												br++;
												int can_not_close = DECK - 3;
												if ((card_start_index_p1 + card_start_index_p2 + br) < can_not_close)
												{
													check_close = true;
												}
												else
												{
													check_close = false;
												}


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
													cout << "Select the card you want to play using the index(0-5):";
													cin >> index_p1;
												}

												cout << "You(P1) choose: " << player1_hand[index_p1].numbers;
												printColor(player1_hand[index_p1]);
												winner = false;
												int win_points = WinPoints(player2_hand[index_p2].numbers, player1_hand[index_p1].numbers, winner);
												if (CheckSuit(player1_hand[index_p1].suits, player2_hand[index_p2].suits))
												{
													if (winner)
													{
														sum_p2 += win_points;
														player_turn = false;
													}
													else
													{
														sum_p1 += win_points;
														player_turn = true;
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
														player_turn = false;
													}
												}
												last_trick[0] = player1_hand[index_p1];
												last_trick[1] = player2_hand[index_p2];
												player2_hand[index_p2] = arr[card_start_index_p1 + card_start_index_p2 + br];
												br++;
												player1_hand[index_p1] = arr[card_start_index_p1 + card_start_index_p2 + br];
												br++;
												int can_not_close = DECK - 3;
												if ((card_start_index_p1 + card_start_index_p2 + br) < can_not_close)
												{
													check_close = true;
												}
												else
												{
													check_close = false;
												}
											}
										}
										else
										{
											if (player_turn)
											{
												while (true)
												{
													cout << "Select the card you want to play using the index(0-" << cards_of_hand - 1 << "):";
													cin >> index_p1;
													if (index_p1 < 0 || index_p1>cards_of_hand - 1)
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
												if (marrige)
												{

													if (CheckSuit(player1_hand[index_p1].numbers, "K") || CheckSuit(player1_hand[index_p1].numbers, "Q"))
													{
														marrige = false;
														if (CheckSuit(marriage_suit, bottom_card.suits))
														{
															sum_p1 += trump_merriage;
														}
														else
														{
															sum_p1 += non_trump_merriage;
														}
													}
													else
													{
														cout << endl << "You have only marriage, if you play \"K\" and \"Q\" " << endl;


													}
												}
											}
											else
											{

												while (true)
												{
													cout << "Select the card you want to play using the index(0-" << cards_of_hand - 1 << "):";
													cin >> index_p2;
													if (index_p2 < 0 || index_p2>cards_of_hand - 1)
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
												if (marrige)
												{

													if (CheckSuit(player2_hand[index_p2].numbers, "K") || CheckSuit(player2_hand[index_p2].numbers, "Q"))
													{
														marrige = false;
														if (CheckSuit(marriage_suit, bottom_card.suits))
														{
															sum_p2 += trump_merriage;
														}
														else
														{
															sum_p2 += non_trump_merriage;
														}
													}
													else
													{
														cout << endl << "You have only marriage, if you play \"K\" and \"Q\" " << endl;
														continue;

													}
												}

											}
											cout << endl;
											if (player_turn)
											{

												cout << "Player 2's turn" << endl << endl;
												cout << "Your hand(P2): [";
												HandPrintAfterDeck(player2_hand, cards_of_hand);
												cout << "]" << endl << endl;
												while (true)
												{
													cout << "Select the card you want to play using the index(0-" << cards_of_hand - 1 << "):";
													cin >> index_p2;


													if (index_p2 < 0 || index_p2>5)
													{
														setColor(Color::Red);
														cout << "Invalid index! Try again!" << endl;
														setColor(Color::White);
													}
													else
													{
														if (CheckSuit(player2_hand[index_p2].suits, player1_hand[index_p1].suits))
														{
															break;
														}
														else
														{
															if (SerachForCardFromEqualSuit(player2_hand, player1_hand[index_p1], cards_of_hand))
															{
																setColor(Color::Red);
																cout << "Please, choose a card of the same suit!" << endl;
																setColor(Color::LightYellow);
																cout << "We know you have it! ;)" << endl;
															}
															else
															{
																if (CheckSuit(player2_hand[index_p2].suits, bottom_card.suits))
																{
																	break;
																}
																else
																{
																	if (SerachForCardFromEqualSuit(player2_hand, bottom_card, cards_of_hand))
																	{
																		setColor(Color::Red);
																		cout << "Please, choose a card of the main suit!" << endl;
																		setColor(Color::LightYellow);
																		cout << "We know you have it! ;)" << endl;
																	}
																	else
																	{
																		break;
																	}
																}

															}
															setColor(Color::White);
														}
													}


												}

												cout << "You(P2) choose: " << player2_hand[index_p2].numbers;
												printColor(player2_hand[index_p2]);
												winner = true;
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
														sum_p2 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
														player_turn = false;
													}
													else
													{

														sum_p1 += Points(player2_hand[index_p2].numbers) + Points(player1_hand[index_p1].numbers);
														player_turn = true;
													}
												}
												last_trick[0] = player1_hand[index_p1];
												last_trick[1] = player2_hand[index_p2];
												for (int i = index_p1; i < cards_of_hand - 1; i++)
												{
													player1_hand[i] = player1_hand[i + 1];
												}
												for (int i = index_p2; i < cards_of_hand - 1; i++)
												{
													player2_hand[i] = player2_hand[i + 1];
												}
												cards_of_hand--;



											}
											else
											{
												cout << "Player 1's turn" << endl << endl;
												cout << "Your hand(P1): [";
												HandPrintAfterDeck(player1_hand, cards_of_hand);
												cout << "]" << endl << endl;

												while (true)
												{

													cout << "Select the card you want to play using the index(0-" << cards_of_hand - 1 << "):";
													cin >> index_p1;
													if (index_p1 < 0 || index_p1>cards_of_hand - 1)
													{
														setColor(Color::Red);
														cout << "Invalid index! Try again!" << endl;
														setColor(Color::White);
													}
													else
													{
														if (CheckSuit(player2_hand[index_p2].suits, player1_hand[index_p1].suits))
														{
															break;
														}
														else
														{
															if (SerachForCardFromEqualSuit(player1_hand, player2_hand[index_p2], cards_of_hand))
															{
																setColor(Color::Red);
																cout << "Please, choose a card of the same suit!" << endl;
																setColor(Color::LightYellow);
																cout << "We know you have it! ;)" << endl;
															}
															else
															{
																if (CheckSuit(player1_hand[index_p1].suits, bottom_card.suits))
																{
																	break;
																}
																else
																{
																	if (SerachForCardFromEqualSuit(player1_hand, bottom_card, cards_of_hand))
																	{
																		setColor(Color::Red);
																		cout << "Please, choose a card of the main suit!" << endl;
																		setColor(Color::LightYellow);
																		cout << "We know you have it! ;)" << endl;
																	}
																	else
																	{
																		break;
																	}
																}

															}
															setColor(Color::White);
														}
													}


												}

												cout << "You(P1) choose: " << player1_hand[index_p1].numbers;
												printColor(player1_hand[index_p1]);
												winner = false;
												int win_points = WinPoints(player2_hand[index_p2].numbers, player1_hand[index_p1].numbers, winner);
												if (CheckSuit(player1_hand[index_p1].suits, player2_hand[index_p2].suits))
												{
													if (winner)
													{
														sum_p2 += win_points;
														player_turn = false;
													}
													else
													{
														sum_p1 += win_points;
														player_turn = true;
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
														player_turn = false;
													}
												}

												last_trick[0] = player1_hand[index_p1];
												last_trick[1] = player2_hand[index_p2];
												for (int i = index_p1; i < cards_of_hand - 1; i++)
												{
													player1_hand[i] = player1_hand[i + 1];
												}
												for (int i = index_p2; i < cards_of_hand - 1; i++)
												{
													player2_hand[i] = player2_hand[i + 1];
												}
												cards_of_hand--;
											}
										}
										if (on_or_off[BOOLELEMENT1])
										{
											cout << endl << endl;
											cout << "Result:" << endl;
											cout << "P1: " << sum_p1 << endl;
											cout << "P2: " << sum_p2 << endl;
										}
										

									}
									else if (CheckSuit(comand, "switch-nine") || CheckSuit(comand, "sw"))
									{
										if (player_turn)
										{

											Card nine;
											for (int i = 0; i < HAND_COUNT; i++)
											{
												if (CheckSuit(player1_hand[i].suits, bottom_card.suits) && CheckSuit(player1_hand[i].numbers, "9"))
												{
													nine = player1_hand[i];
													check_nine = true;
													break;
												}
											}
											
													if (check_nine)
													{
														cout << "Player 1's switch with nine!" << endl;
														SwitchWithNine(arr, player1_hand, nine);
													}
													else
													{
														setColor(Color::Red);
														cout << "You don't have this nine!!!";
														setColor(Color::White);
													}
											
											

										}
										else
										{

											Card nine;
											for (int i = 0; i < HAND_COUNT; i++)
											{
												if (CheckSuit(player2_hand[i].suits, bottom_card.suits) && CheckSuit(player2_hand[i].numbers, "9"))
												{
													nine = player2_hand[i];
													check_nine = true;
													break;
												}
											}
											if (check_nine)
											{
												cout << "Player 2's switch with nine!" << endl;
												SwitchWithNine(arr, player2_hand, nine);
											}
											else
											{
												setColor(Color::Red);
												cout << "You don't have this nine!!!";
												setColor(Color::White);
											}
										}
									}

									if (CheckSuit(comand, "marriage") || CheckSuit(comand, "m"))
									{

										bool QK[MARRIAGE];
										QK[BOOLELEMENT1] = false;
										QK[BOOLELEMENT2] = false;
										cout << "Plase write your suit from the marriage(Spades, Hearts, Diamonds, Clubs): ";
										cin.getline(marriage_suit, MAX_SUITS + 1);
										cout << endl;
										if (player_turn)
										{
											for (int i = 0; i < HAND_COUNT; i++)
											{
												if (CheckSuit(player1_hand[i].suits, marriage_suit) && CheckSuit(player1_hand[i].numbers, "Q"))
												{
													QK[BOOLELEMENT1] = true;
												}
												if (CheckSuit(player1_hand[i].suits, marriage_suit) && CheckSuit(player1_hand[i].numbers, "K"))
												{
													QK[BOOLELEMENT2] = true;
												}
											}
											if (QK[BOOLELEMENT1] && QK[BOOLELEMENT2])
											{

												marrige = true;
											}
											else
											{
												setColor(Color::Red);
												cout << "You don't have a merriage!!!";
												setColor(Color::White);
											}

										}
										else
										{
											for (int i = 0; i < HAND_COUNT; i++)
											{
												if (CheckSuit(player2_hand[i].suits, marriage_suit) && CheckSuit(player2_hand[i].numbers, "Q"))
												{
													QK[BOOLELEMENT1] = true;
												}
												if (CheckSuit(player2_hand[i].suits, marriage_suit) && CheckSuit(player2_hand[i].numbers, "K"))
												{
													QK[BOOLELEMENT2] = true;
												}
											}
											if (QK[BOOLELEMENT1] && QK[BOOLELEMENT2])
											{

												marrige = true;
											}
											else
											{
												setColor(Color::Red);
												cout << "You don't have a merriage!!!";
												setColor(Color::White);
											}

										}
									}
									if (CheckSuit(comand, "close") || CheckSuit(comand, "c"))
									{
										if (specials && check_close)
										{
											cout << endl << "Stock closed. No more cards will be drawn." << endl << "Strict rules are now in effect" << endl;
											br = br + 20;
										}
										else
										{
											setColor(Color::Red);
											cout << "Invalid action!!!";
											setColor(Color::White);
										}



									}
									if (CheckSuit(comand, "end") || CheckSuit(comand, "e"))
									{
										//if()
										ofstream file("current_result.txt");
										if (!file.is_open())
										{
											cout << "Couldn't open file.";
											return 1;
										}
										file << "Round "<<round<<": ";
										end = true;
										cout << endl << "Round " << round << " ended." << endl;
										round++;
										cout << "Calculating points..." << endl;
										EndOfRound(player_turn, sum_p1, sum_p2, points_p1, points_p2);
										file.close();
										break;
									}
									if (CheckSuit(comand, "information") || CheckSuit(comand, "i"))
									{
										cout << "The player can see through these actions all the information about the specific game:" << endl;
										cout << "> last-trick" << endl;
										cout << "> trump" << endl;
										cout << "> history" << endl;
										cout << "> status " << endl << endl << "> ";
										
										cin.getline(comand, CMD_SIZE);
										if (CheckSuit(comand, "last-trick") || CheckSuit(comand, "l"))
										{
											cout << endl << "Player 1:" << last_trick[0].numbers;
											printColor(last_trick[0]);
											cout << endl << "Player 2:" << last_trick[1].numbers;
											printColor(last_trick[1]);
											if (winner)
											{
												setColor(Color::Green);
												cout << endl << "Winner: Player 1" << endl;
											}
											else
											{
												setColor(Color::Green);
												cout << endl << "Winner: Player 2" << endl;
											}
											setColor(Color::White);
										}
										else if (CheckSuit(comand, "trump") || CheckSuit(comand, "t"))
										{
											cout << endl << "Trump:";
											printColor(bottom_card);
											cout << endl;
										}
										else if (CheckSuit(comand, "history") || CheckSuit(comand, "h"))
										{
											char buffer[FILEREADER];
											cout << endl;
											setColor(Color::Green);
											ifstream file("current_result.txt");
											if (!file.is_open())
											{
												cout << "Couldn't open file."<<endl;
												return 1;
											}
											setColor(Color::Gray);
											while (file.getline(buffer, FILEREADER))
											{
												cout << buffer << endl;
											}
											cout << "Round " << round <<": Ongoing!" << endl;
											setColor(Color::Green);
											cout << "Player 1 - " << points_p1 << " | Player 2 - " << points_p2;
											setColor(Color::White);
											cout << endl;

										}
										else if (CheckSuit(comand, "status") || CheckSuit(comand, "status"))
										{

										}
										cout << endl;

									}
									


								}
								
								
								
							}
							else
							{
								setColor(Color::Red);
								cout << endl << "Invalid cleaving!" << endl;
								setColor(Color::White);
							}
							if (!end)
							{
								if (on_or_off[BOOLELEMENT2])
								{
									if (player_turn)
									{
										sum_p1 += 10;
									}
									else
									{
										sum_p2 += 10;
									}
								}
								ofstream file("current_result.txt");
								if (!file.is_open())
								{
									cout << "Couldn't open file.";
									return 1;
								}
								file << "Round " << round << ": ";
								cout << endl << "Round " << round << " ended." << endl;
								round++;
								cout << "Calculating points..." << endl;
								EndOfRound(player_turn, sum_p1, sum_p2, points_p1, points_p2);
								cout << endl << endl;
								file.close();
								end = false;
								cards_of_hand = 6;
							}
					


						}
						round = 0;

							
					}
					if (CheckSuit(comand, "Computer vs Player") || CheckSuit(comand, "c") || CheckSuit(comand, "C"))
					{
						setColor(Color::Red);
						cout << "This mod is in development."<<endl;
						setColor(Color::White);
					}
					cout << endl;
			}
			else if (CheckString(comand, "rules"))
			{

				cout << "SANTASE (66)" << endl<< "Each player gets 6 cards.The Trump suit is chosen at random." << endl;
				cout << "Card values : A = 11, 10 = 10, K = 4, Q = 3, J = 2, 9 = 0." << endl;
				cout << "A marriage(K + Q of the same suit) gives 20 points, or 40 if the trump suit." << endl;
				cout << " The first player to reach 66 points wins the round." << endl << endl;

			}
			else if (CheckString(comand, "settings"))
			{
				char number_for_change[SETTINGS];
				while (CheckString(number_for_change, "back"))
				{
					cout << "SANTASE (66)" << endl;
					cout << "1) Target points to win[11]" << endl;
					cout << "2) Marriage points(non - trump / trump)[20 / 40]" << endl;
					cout << "3) Show players' points [on]" << endl;
					cout << "4) Last trick + 10[on]" << endl;
					cout << "Enter number to change or 'back' to return:" << endl << endl;
					cout << "Choose number:";

					int change_number = 0;
					
					cin.getline(number_for_change, SETTINGS + 1);
					if (number_for_change[0] > '0' && number_for_change[0] < '9')
					{
						switch (number_for_change[0])
						{
						case '1':
						{
							change_number = 1;
							break;
						}
						case '2':
						{
							change_number = 2;
							break;
						}
						case '3':
						{
							change_number = 3;
							break;

						}
						case '4':
						{
							change_number = 4;
							break;
						}
						default:
						{
							setColor(Color::Red);
							cout << endl << "Invalid number!" << endl;
							setColor(Color::White);
							break;
						}

						}
						switch (change_number)
						{
						case 1:
						{
							cout << "Target points to win:";
							cin >> max_points;
							break;
						}
						case 2:
						{
							cout << "Marriage points(non - trump):";
							cin >> non_trump_merriage;
							cout << "Marriage points(trump):";
							cin >> trump_merriage;
							break;
						}
						case 3:
						{
							char show[ELEMENT];
							cout << "Do you want to show players' points(Yes/No)(y/n):";
							cin.getline(show, ELEMENT + 1);
							if (CheckSuit(show, "Yes") || CheckSuit(show, "y"))
							{
								on_or_off[BOOLELEMENT1] = true;
							}
							else if (CheckSuit(show, "No") || CheckSuit(show, "n"))
							{
								on_or_off[BOOLELEMENT1] = false;
							}
							break;

						}
						case 4:
						{
							char show[ELEMENT];
							cout << "Do you want to last trick (+10 points)(Yes/No)(y/n):";
							cin.getline(show, ELEMENT + 1);
							if (CheckSuit(show, "Yes") || CheckSuit(show, "y"))
							{
								on_or_off[BOOLELEMENT2] = true;
							}
							else if (CheckSuit(show, "No") || CheckSuit(show, "n"))
							{
								on_or_off[BOOLELEMENT2] = false;
							}
							break;
						}
						}
					}
					else
					{
						if (CheckSuit(number_for_change, "back"))
						{
							break;
						}
						else
						{
							setColor(Color::Red);
							cout << endl << "Invalid command!!!" << endl;
							setColor(Color::White);
						}
					}
				}
				
			}
			else
			{
				setColor(Color::Red);
				cout << endl << "Invalid command!!!" << endl;
				setColor(Color::White);
			}
		
	}
	
	cout << endl;
	for (int i = 0; i < DECK; i++)
	{
		cout << arr[i].numbers << ' ' << arr[i].suits <<endl;
	}

	std::cout << "A\xE2\x99\xA0"; // A♠
	setColor(Color::White);
	std::cout << "\xE2\x99\xA0"; // Spades		
	setColor(Color::Red);
	std::cout << "\xE2\x99\xA5"; // Heart
	std::cout << "\xE2\x99\xA6"; // Diamond
	setColor(Color::White);
	std::cout << "\xE2\x99\xA3"; // Club
	return 0;
}
