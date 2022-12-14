#include <algorithm> // std::random_shuffle
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

const string spade = "S"; //"♠";
const string diamond = "D"; //"♦";
const string heart = "H"; //"♥";
const string club = "C"; //"♣";

const string suits[4] = { "S", "H", "D", "C" };

string Black = "0";
string Red = "1";
string Green = "2";
string Yellow = "3";
string Blue = "4";
string Purple = "5";
string Cyan = "6";
string White = "7";
string Default = "9";

void printColor(string out, int fg, int bg = 9) {
	cout << "\033[0;3" << fg << ";4" << bg << "m" << out << "\033[0;39;49m";
}

// Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)
const string ranks[13] =
{ "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

/*
   ____    _    ____  ____
  / ___|  / \  |  _ \|  _ \
 | |     / _ \ | |_) | | | |
 | |___ / ___ \|  _ <| |_| |
  \____/_/   \_\_| \_\____/

*/

class CardContainer;
class Hand;

class Card {
protected:
	int suitNum;	 // value 0-3 : num index of suit
	int rank;		 // 0-13      : num value of rank
	int number;		 // 1-52      : unique value determines card
	int value;		 // 1-14      : numeric value used for comparison
	string suitChar; // "♠", "♦", "♣", "♥"
	string rankChar; // Ace, 1 ,2 ,3 ... Q, K
	string fcolor;   // Spade=blue, Diamond=red, etc.
	string bcolor;

public:
	friend class Hand;

	Card(int);
	bool operator<(const Card&);
	bool operator>(const Card&);
	bool operator==(const Card&);
	bool operator!=(const Card&);
	bool operator()(const Card&);
	friend ostream& operator<<(ostream& os, const Card& card);
	friend class CardContainer;
	int getRank() {
		return rank;
	}
	string getRankChar() {
		return rankChar;
	}
	string getSuitChar() {
		return suitChar;
	}
	string getfColor() {
		return fcolor;
	}
	string getbColor() {
		return bcolor;
	}
};

/**
 * Public : operator <<
 *
 * Description:
 *      Overload ostream and send the string representation "Repr"
 *      of the card.
 *
 *      We don't need the scope resolution operator (Card::) since
 *      this is a "friend" of card.
 *
 * Params:
 *      [ostream&] : os
 *      [Card]     : obj
 *
 * Returns:
 *      [ostream&]
 */
ostream& operator<<(ostream& os, const Card& card) {
	os << "\033[0;3" << card.fcolor << ";4" << card.bcolor << "m";
	os << "┌────┐\n";
	os << "│";
	if (card.rank != 9) {
		os << " ";
	}
	os << card.rankChar << " " << card.suitChar << "│\n";
	os << "└────┘";
	os << "\033[0;39;49m";

	return os;
}

/**
 * Public : Card
 *
 * Description:
 *      Represents a single card in a deck of cards to include a
 *      value along with rank and suit. We are assuming a standard
 *      card type in a deck of playing cards.
 *
 * Params:
 *      int :  value from 0 - 51 that represents a card in a deck.
 *
 * Returns:
 *      None
 */
Card::Card(int num) {

	if (num < 0)
	{
		suitChar = "?";
		suitNum = 0;
		fcolor = "7";
		bcolor = "9";
		rank = 0;
		rankChar = "?";
		value = 0;
	}
	else
	{
		number = num;
		suitNum = number / 13;
		suitChar = suits[suitNum];
		fcolor = to_string(suitNum + 2);
		bcolor = "9";
		rank = number % 13;

		if (rank > 8)
		{
			value = 10;
		}
		else if (rank == 0)
		{
			value = 11;
		}
		else
		{
			value = rank + 1;
		}
		rankChar = ranks[rank];
	}
}

bool Card::operator<(const Card& rhs) {
	return this->rank < rhs.rank;
}

bool Card::operator>(const Card& rhs) {
	return this->rank > rhs.rank;
}

bool Card::operator==(const Card& rhs) {
	return this->rank == rhs.rank;
}

bool Card::operator!=(const Card& rhs) {
	return this->rank != rhs.rank;
}

bool Card::operator()(const Card& rhs) {
	return (this->rank < rhs.rank);
}

/*
   ____    _    ____  ____   ____ ___  _   _ _____  _    ___ _   _ _____ ____
  / ___|  / \  |  _ \|  _ \ / ___/ _ \| \ | |_   _|/ \  |_ _| \ | | ____|  _ \
 | |     / _ \ | |_) | | | | |  | | | |  \| | | | / _ \  | ||  \| |  _| | |_) |
 | |___ / ___ \|  _ <| |_| | |__| |_| | |\  | | |/ ___ \ | || |\  | |___|  _ <
  \____/_/   \_\_| \_\____/ \____\___/|_| \_| |_/_/   \_\___|_| \_|_____|_| \_\
*/

class CardContainer {
protected:
	vector<Card*> Cards;

public:
	CardContainer(){};
	CardContainer(int){};
	void Add(Card* newCard)
	{
		Cards.emplace_back(newCard);
	}
	bool isEmpty() { return Cards.size() == 0 ? true : false; };
	void Shuffle()
	{
		random_shuffle(Cards.begin(), Cards.end());
	};
	virtual void Reset()
	{
		Cards.clear();
	}

	Card* At(int loc) 
	{
		return(Cards[loc]);
	}

	friend ostream& operator<<(ostream& os, const CardContainer& cards);
};

ostream& operator<<(ostream& os, const CardContainer& c) {
	for (int i = 0; i < c.Cards.size(); i++) {
		os << "\033[0;3" << c.Cards[i]->getfColor() << ";4"
			<< c.Cards[i]->getbColor() << "m";
		os << "┌────┐";
		os << "\033[0;39;49m";
	}
	os << endl;
	for (int i = 0; i < c.Cards.size(); i++) {
		os << "\033[0;3" << c.Cards[i]->getfColor() << ";4"
			<< c.Cards[i]->getbColor() << "m";
		os << "│";
		if (c.Cards[i]->getRank() != 9) {
			os << " ";
		}
		os << c.Cards[i]->getRankChar() << " " << c.Cards[i]->getSuitChar()
			<< "│";
		os << "\033[0;39;49m";
	}
	os << endl;
	for (int i = 0; i < c.Cards.size(); i++) {
		os << "\033[0;3" << c.Cards[i]->getfColor() << ";4"
			<< c.Cards[i]->getbColor() << "m";
		os << "└────┘";
		os << "\033[0;39;49m";
	}
	os << endl;

	return os;
}




/*
  ____  _____ ____ _  __
 |  _ \| ____/ ___| |/ /
 | | | |  _|| |   | ' /
 | |_| | |__| |___| . \
 |____/|_____\____|_|\_\
*/

class Deck : public CardContainer {
protected:
	int deckSize = 52;

public:
	Deck() { fill(); };
	Deck(int _size)
	{
		deckSize = _size;
		fill();
	}

	void Draw(CardContainer* destination)
	{
		if (this->Cards.size() > 0)
		{
			destination->Add(this->Cards.back());
			Cards.pop_back();
		}
		else
		{
			cout << "Deck is empty." << endl;
		}
	}
	void Reset()
	{
		this->Cards.clear();
		fill();
	}


private:
	void fill()
	{
		for (int i = 0; i < deckSize; i++)
		{
			this->Cards.push_back(new Card(i));
		}
	}
};



/*
  _   _    _    _   _ ____
 | | | |  / \  | \ | |  _ \
 | |_| | / _ \ |  \| | | | |
 |  _  |/ ___ \| |\  | |_| |
 |_| |_/_/   \_\_| \_|____/
*/
class Hand : public CardContainer {
protected:
	int numCards;
public:
	Hand() { numCards = 0; };
	int Size() {
		return Cards.size();
	}


    /**
     * Public : Value
     * 
     * Description:
     *      Adds up the cards in the container and returns that value.
     *      The value of aces can be adjusted with the int param aceValue.
     * 
     * Params:
     *         int aceValue     The value of the ace.
     * 
     * Returns:
     *      - Returns an integer sum of the values of the cards in the hand.
     */
	int Value(int aceValue = 11)
	{
		int sum = 0;

		for(Card* card : Cards)
		{
			if (card->getRankChar() == "A")
				sum += aceValue;
			else
				sum += card->value;
		}

		if (sum > 21 && aceValue == 11) //Since we are trying to avoid busting. If the aces are a large value we will automatically reduce them
			return(Value(1));
		else
			return(sum);
	}
};




/**
 * Player
 * 
 * Description:
 *      Player object represents a player (as opposed to the dealer) in a game of blackjack.
 *      Players have a hand, some money and a bet amount.
 * 
 * Public Methods:
 *      - Player          Constructor
 *      - SetBet          bool
 *      - GetBank         double
 *      - GetHand         Hand*
 *      - Pay(double)     void
 *      - Collect(double) void
 * 
 * 
 * Usage: 
 * 
 *  Player player;
 *  
 *  cout << *player.GetHand();
 *      
 */
class Player {
protected:
	Hand* hand;
	double bank;
	double bet;

public:

	Player()
	{
		hand = new Hand();
		bank = 100;
	}
    /**
     * Public : SetBet
     * 
     * Description:
     *      Allows player to set their bet as long as it is greater than their bank amount.
     * 
     * Params:
     *         none
     * 
     * Returns:
     *      - A bool that indicates if the setting of the bet was successful.
     */
	bool SetBet()
	{
		double _bet;

		cout << string(50, '\n');

		if (bank != 0)
		{

			do
			{
				cout << "==================== B L A C K J A C K ====================" << endl;
				cout << string(5, '\n');
				cout << "   C U R R E N T   B A N K R O L L:   " << bank << endl;
				cout << string(5, '\n');
				cout << "   E N T E R   B E T   T O   P L A Y:   ";
				cin >> _bet;
			} while (_bet > bank && _bet <= 0);

			bet = _bet;
			return true;
		}
		else
		{
			cout << "You're all out of money there, pardner." << endl;
			cout << "              ,'-'," << endl;
			cout << "             :-----:" << endl;
			cout << "         (''' , - , ''')" << endl;
			cout << "         \\   ' .  , `  /" << endl;
			cout << "          \\  '   ^  ? /" << endl;
			cout << "           \\ `   -  ,'" << endl;
			cout << "             `j_ _,'" << endl;
			cout << "       , --`\\ \\ / f" << endl;
			cout << "     ,-      \\_\\/_/'-" << endl;
			cout << "    ,                `," << endl;
			cout << "    ,                   , " << endl;
			cout << "       /\\           \\" << endl;
			cout << "   |    /            \\   '," << endl;
			cout << "   ,   f  :           :`,  ," << endl;
			cout << "   <...\\  ,          : ,- '" << endl;
			cout << "   \\, , , , \\;      : j  '" << endl;
			cout << "    \\    \\          :/^^^^'" << endl;
			cout << "     \\    \\          ; ''':" << endl;
			cout << "      \\   -,        -`.../" << endl;
			cout << "       '    - -,`,--`" << endl;
			cout << "        \\_._'-- '---:" << endl;
                      
			return false;
		}

	}

    double GetBank() { return bank; }

	Hand* GetHand() { return hand; }

	double GetBet() { return bet; }

	void Pay(double amount) { this->bank += amount; }

	void Collect(double amount) { this->bank -= amount; }
};


/**
 * BlackJackGame
 * 
 * Description:
 *      Class implements a main logic loop that combines the other elements
 *      of the blackjack.hpp file to form a fully functional game.
 * 
 * Public Methods:
 *      - BlackJackGame     Constructor
 *      - Start()           Void    Starts an continues the game as long as the player has money
 * 
 * Private Methods:
 *      - PrintGUI(int)     void    Prints different versions of the GUI based on the int parameter
 *      - Upkeep()          void    Resets deck and hands
 *      - Win(float)        void    Procedure if player wins. Pays a multiplier on the bet based on int parameter
 *      - Lose()            void    Procedure if player loses
 *      - Tie()             void    Procedure if there is a tie
 * 
 * Usage: 
 * 
 *  BlackJackGame game;
 *  game.Start()
 *      
 */
	class BlackJackGame
	{
		Player player;
		Deck deck;
		Hand* dealer;
		int endGame;
		int move;

	private:

    /**
     * Private : PrintGUI
     * 
     * Description:
     *      Prints the game gui so the player knows what he can or cannot do.
     * 
     * Params:
     *      int     stage       determines which gui will be displayed
     * 
     * Returns:
     *      nothing.
     */
		void PrintGUI(int stage)
		{
			//STAGES 1. Player Turn, 2. Dealer Turn, 3. Loss, 4. Win!
			cout << string(50, '\n');
			cout << "==================== B L A C K J A C K ====================" << endl;
			cout << "Dealers Hand:" << endl;
			if (stage == 1)
			{
				Hand* temp = new Hand();
				temp->Add(new Card(-1));
				temp->Add(dealer->At(1));
				cout << *temp;
			}
			else
				cout << *dealer;
			cout << string(5, '\n');
			cout << "Player's Hand:" << endl;
			cout << *player.GetHand();
			cout << string(5, '\n');

			switch (stage)
			{
			case 1:
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "|  1. Hit     |   |  2. Stand    |   | Current Bet: " << player.GetBet() << endl;
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "Select: ";
				break;

			case 2:
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "|  D e a l e r ' s      T u r n      | Current Bet: " << player.GetBet() << endl;
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "Select: ";
				break;
			case 3:
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "| 1. Continue |   | 2. Quit      |   | Current Bet: " << player.GetBet() << endl;
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "---------- L O S S ----------" << endl;
				cout << "Continue?: ";
				break;
			case 4:
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "| 1. Continue |   | 2. Quit      |   | Current Bet: " << player.GetBet() << endl;
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "++++++++++ T I E ++++++++++" << endl;
				cout << "Continue?: ";
				break;
			case 5:
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "| 1. Continue |   | 2. Quit      |   | Current Bet: " << player.GetBet() << endl;
				cout << "O-------------O---O--------------O---O--------------------O" << endl;
				cout << "********** Y O U  W I N **********" << endl;
				cout << "Continue?: ";
				break;
			}


		}

    /**
     * Private : Upkeep
     * 
     * Description:
     *      Resets all hands and shuffles the deck so a new round can be played
     * 
     * Params:
     *      none
     * 
     * Returns:
     *          nothing!
     */
		void Upkeep()
		{
			move = 0;
			player.GetHand()->Reset();
			dealer->Reset();
			deck.Reset();
			deck.Shuffle();
		}

    /**
     * Private : Lose
     * 
     * Description:
     *      Procedure if the player loses. Collets money;
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      nothing!
     */
		void Lose()
		{
			PrintGUI(3);
			player.Collect(player.GetBet());
		}

    /**
     * Private : Win
     * 
     * Description:
     *      Procedure if the player Wins. Pays the player a multiple of their bet based on param;
     * 
     * Params:
     *      float multi     the value the player's original bet will be multiplied by and then paid to them.
     * 
     * Returns:
     *      nothing!
     */
		void Win(float multi = 1)
		{
			PrintGUI(5);
			player.Pay(player.GetBet() * multi);
		}

    /**
     * Private : Tie
     * 
     * Description:
     *      Procedure if there is a tie.
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      nothing!
     */
		void Tie()
		{
			PrintGUI(4);
		}


    public:

    /**
     * Public : BlackJackGame()
     * 
     * Description:
     *      Constructor. Sets the dealers hand and makes sure the game doesn't end immediately.
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      nothing!
     */
		BlackJackGame()
		{
			srand(time(0));
			dealer = new Hand();
			endGame = false;
		}

    /**
     * Public : Start
     * 
     * Description:
     *      Main logic loop of a blackjack game. Based upon real life blackjack rules sans insurance and splitting.
     *      First gets players bet and then deals cards to both the dealer and player. After the player makes all their moves,
     *      the dealer goes and then function decides who won.
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      nothing!
     */
		void Start()
		{
			while (!endGame)
			{
				Upkeep();
				//Get PLayer Bet
				if (!player.SetBet())
					break;
				deck.Draw(dealer);
				deck.Draw(dealer);
				deck.Draw(player.GetHand());
				deck.Draw(player.GetHand());

				//PLAYER ACTIONS
				while (player.GetHand()->Value() <= 21 && move != 2)
				{
					PrintGUI(1);
					do
					{
						cin >> move;
					} while (move != 1 && move != 2);

					if (move == 1)
						deck.Draw(player.GetHand());
				}

				if (player.GetHand()->Value() == 21)
				{
					Win(1.5);
				}
				else if (player.GetHand()->Value() > 21)
				{
					Lose();
				}
				else
				{
					//Dealer actually plays

					while (dealer->Value() < 17)
					{
						PrintGUI(2);
						deck.Draw(dealer);
					}

					if (dealer->Value() > 21)
					{
						Win();
					}
					else if (dealer->Value() == 21)
					{
						Lose();
					}
					else
					{
						int pd = 21 - player.GetHand()->Value();
						int dd = 21 - dealer->Value();

						if (dd < pd)
							Lose();
						else if (pd < dd)
							Win(1.5);
						else
							Tie();
					}
				}

				do
				{
					cin >> endGame; //asking user if they want to play again
				} while (endGame != 1 && endGame != 2);
				endGame--;
			}
		}
	};
