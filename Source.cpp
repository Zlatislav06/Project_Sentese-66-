#include <iostream>
using namespace std;


void Shuffle(char cards[],int size=6)
{
	char new_cards[]{ 0 };
	for (int i = 0; i < size; i++)
	{
		new_cards[i] = cards[i];
	}
	for (int i = 0; i < size; i++)
	{
		int random = rand() % (6-i);
		if (new_cards[random] != 0)
		{
			cards[i] = new_cards[random];
			new_cards[random] = 0;
		}
		else
		{
			i--;
		}
			
		
		
	}
	for (int i = 0; i < size; i++)
	{
		cout << cards[i]<<' ';
	}
}
using namespace std;
int main()
{
	cout << "If you want any of the following functions to be performed, please type one of the corresponding commands:\n";
	cout << "> start"<< endl;
	cout << "> rules" << endl;
	cout << "> settings" << endl<<endl<<'>';
	string comand = "";
	cin >> comand;
	char colors[] = {'♠','♥','♦','♣'};
	char cards[] = 
	{ 
		'A','10','K','Q','L','9'
		
	};
	string cards_with_colors[] =
	{
		"A♠","10♠","K♠","Q♠","L♠","9♠",
		"A♥","10♥","K♥","Q♥","L♥","9♥",
		"A♦","10♦","K♦","Q♦","L♦","9♦",
		"A♣","10♣","K♣","Q♣","L♣","9♣",
	};
	//Shuffle(new_cards);
	while (true)
	{
		if (comand == "start")
		{
			cout << "You can choose whether to play against the computer or not."<<endl;
			cout << "> Player vs Player (p or P)" << endl;
			cout << "> Computer vs Player (c or C)" << endl << endl << '>';
			cin >> comand;
			if (comand == "Player vs Player" || comand == "P" || comand == "p")
			{
				
				cout << "The game started!" << endl;
				int random_color = rand() % 4;
				int random_card = rand() % 6;
				switch (random_color)
				{
					case 0:
					{
						cout << "Trump suit :"<<u8"♠(Spades)" << endl;
						cout << "Bottom card :" << cards[random_card] <<"(Spade)"<< endl;
						break;
					}
					case 1:
					{
						cout << "Trump suit : " << u8"♥(Hearts)" << endl;
						cout << "Bottom card :" << cards[random_card] << "(Heart)" << endl;
						break;
					}
					case 2:
					{
						cout << "Trump suit : " << u8"♦(Dimands)" << endl;
						cout << "Bottom card :" << cards[random_card] << "(Dimand)" << endl;
						break;
					}
					case 3:
					{
						cout << "Trump suit : " << u8"♣(Clubs)" << endl;
						cout << "Bottom card :" << cards[random_card] << "(Club)" << endl;
						break;
					}
				}
				cout << endl;
				cout << "Players have several actions to control the hand:"<<endl;
				cout << "> hand" << endl;
				cout << "> play" << endl;
				cout << "> switch-nine" << endl << endl;
				cout << "Player 1's turn" << endl << endl << '>';
				const int SIZE_OF_HAND = 6;
				string plear1_hand[SIZE_OF_HAND]{ 0 };
				string plear2_hand[SIZE_OF_HAND]{ 0 };
				cin >> comand;
				if (comand == "hand")
				{

				}
				else if (comand == "play")
				{

				}
				else if (comand == "switch-nine")
				{

				}
				


			}
			else if (comand == "Computer vs Player" || comand == "c" || comand == "C")
			{
				cout << "The game started!" << endl;
				cout << "Trump suit : ♥(Hearts)" << endl;
				cout << "Bottom card : 10♥" << endl;
				cout << "Player 1’s turn" << endl;
			}
		}
		else if (comand == "rules")
		{

			cout << "SANTASE (66)\nEach player gets 6 cards.The Trump suit is chosen at random." << endl;
			cout << "Card values : A = 11, 10 = 10, K = 4, Q = 3, J = 2, 9 = 0." << endl;
			cout << "A marriage(K + Q of the same suit) gives 20 points, or 40 if the trump suit." << endl;
			cout << " The first player to reach 66 points wins the round." << endl;

		}
		else if (comand == "settings")
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
	
	return 0;
}
