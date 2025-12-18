#include <iostream>
using namespace std;
const int SIZE = 100;

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
bool CheckString(char* string1,const char* string2)
{
	int size = 0;
	while (*(string2+size)!='\0')
	{
		size++;
	}
	bool check = true;
	for (int i = 1; i < size; i++)
	{
		if (*(string1 + i-1) != *(string2 + i))
		{
			check = false;
		}
	}
	return check;
}
using namespace std;
int main()
{
	cout << "If you want any of the following functions to be performed, please type one of the corresponding commands:\n";
	cout << "> start"<< endl;
	cout << "> rules" << endl;
	cout << "> settings" << endl<<endl<<'>';
	char comand[SIZE];
	cin.ignore();
	cin.getline(comand,SIZE);

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

		if (CheckString(comand,"start"))
		{
			cout << "You can choose whether to play against the computer or not."<<endl;
			cout << "> Player vs Player (p or P)" << endl;
			cout << "> Computer vs Player (c or C)" << endl << endl << '>';
			cin.ignore();
			cin.getline(comand, SIZE);
			if (CheckString(comand,"Player vs Player") || CheckString(comand, "P") || CheckString(comand, "p"))
			{
				
				cout << "The game started!" << endl;
				int random_color = rand() % 4;
				int random_card = rand() % 6;
				switch (random_color)
				{
					case 0:
					{
						char c = 6;
						cout << "Trump suit :"<< c<< "(Spades)" << endl;
						cout << "Bottom card :" << cards[random_card] <<"(Spade)"<< endl;
						break;
					}
					case 1:
					{
						char c = 3;
						cout << "Trump suit : " << c << "(Hearts)" << endl;
						cout << "Bottom card :" << cards[random_card] << "(Heart)" << endl;
						break;
					}
					case 2:
					{
						char c = 4;
						cout << "Trump suit : " << c << "(Dimands)" << endl;
						cout << "Bottom card :" << cards[random_card] << "(Dimand)" << endl;
						break;
					}
					case 3:
					{
						char c = 5;
						cout << "Trump suit : " << c << "(Clubs)" << endl;
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
				string player1_hand[SIZE_OF_HAND] = {};
				for (int i = 0; i < SIZE_OF_HAND; i++)
				{
					int random = rand() %25;
					if (cards_with_colors[random] != "")
					{
						player1_hand[i] = cards_with_colors[random];
						cards_with_colors[random] = "";
					}
					else
					{
						i--;
					}
				}
				string player2_hand[SIZE_OF_HAND];
				cin.ignore();
				cin.getline(comand, SIZE);
				if (CheckString(comand, "hand"))
				{
					for (int i = 0; i < SIZE_OF_HAND; i++)
					{
						cout << player1_hand[i] << ',';


					}
				}
				else if (CheckString(comand, "play"))
				{

				}
				else if (CheckString(comand, "switch-nine"))
				{

				}
				


			}
			else if (CheckString(comand, "Computer vs Player")  || CheckString(comand, "C") || CheckString(comand, "c"))
			{
				cout << "The game started!" << endl;
				cout << "Trump suit : ♥(Hearts)" << endl;
				cout << "Bottom card : 10♥" << endl;
				cout << "Player 1’s turn" << endl;
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
	
	return 0;
}
