#include <iostream>
using namespace std;

int main()
{
	cout << "If you want any of the following functions to be performed, please type one of the corresponding commands:\n";
	cout << "> start"<< endl;
	cout << "> rules" << endl;
	cout << "> settings" << endl<<endl<<'>';
	string arr = "";
	cin >> arr;
	if (arr == "start")
	{
		cout << "You can choose whether to play against the computer or not.";
		cout << "> Player vs Player" << endl;
		cout << "> Computer vs Player" << endl << endl << '>';
		if (arr == "Player vs Player" || arr == "P" || arr == "p")
		{

		}
		else if (arr == "Computer vs Player" || arr == "P" || arr == "p")
		{
			cout << "SANTASE (66)\nEach player gets 6 cards.The Trump suit is chosen at random.";
			cout << "Card values : A = 11, 10 = 10, K = 4, Q = 3, J = 2, 9 = 0.";
			cout << "A marriage(K + Q of the same suit) gives 20 points, or 40 if the trump suit.";
			cout << " The first player to reach 66 points wins the round.";
		}
	}
	else if (arr == "rules")
	{
		cout << "The game started!" << endl;
		cout << "Trump suit : ♥(Hearts)" << endl;
		
		cout << "Bottom card : 10♥" << endl;
			cout << "Player 1’s turn" << endl;
			
			
	}
	else if (arr == "settings")
	{

	}
	else
	{

	}
	return 0;
}