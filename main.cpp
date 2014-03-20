#include <iostream>
#include <cstring>
#include <Windows.h>
#include <time.h>

using namespace std;											

void readRules();												
int playBlackjack(int);											
int visitCashier(int);										
						
struct deck
{
	char cardName[10];
	char cardFamily[10];
	int  cardValue;
};

int main(void)
{
	//Declarations for Menu and jazz
	bool inCasino = true;
	int menuChoice, casinoVisit = 0;

	//Declarations for chips and what not
	int chips;

	char playerName[50];

	cout << "\n\n"
		 << "********************************************************************************"
		 << "*                                                                              *"
		 << "*                            Welcome to the Casino                             *"
		 << "*                                                                              *"
		 << "********************************************************************************\n\n";

	Sleep(2000);
	
	cout << "May I take your name for the guest list: \n";
	cin.getline(playerName, 50);
	cin.clear();
								//The player name is purely cosmetic

	cout << "\nYou have been given a loan of 1000 chips to start with";
	chips = 1000;
								//Gives the player some starting chips
	Sleep(1500);
	system("CLS");	

	do
	{
		system("CLS");

		cout << "\n\n"
 			 << "********************************************************************************"
			 << "*                                                                              *"
			 << "*                                 CASINO FLOOR                                 *"
			 << "*                                                                              *"
			 << "********************************************************************************\n\n";
		
		if(casinoVisit == 0)
		{
			cout << "Greetings " << playerName << ". How may I be of service?:\n";
		}
		else		//Cosmetic feature using the player name and whether or not they have been here before
		{
			cout << "Welcome back " << playerName << ". How may I be of service?:\n";
		}
	

		casinoVisit = 1;	//Cosmetic feature to change the message above
	
		cout << "1. Read The Rules\n"
			 << "2. Take Out/Repay chips\n"
			 << "3. Play Blackjack\n"
			 << "4. Leave Casino\n";
		cin.clear();
							//The above prints out the menu choice to give the player an option
		do
		{
			cin  >> menuChoice;
			cin.get();
			cin.clear();

			if(menuChoice + 1 > 256)
			{
				menuChoice = 0;
			}
												//A do loop to make sure the player chooses a valid option
			switch(menuChoice)
			{
				case 1:		readRules();
							break;
				case 2:		chips = visitCashier(chips);
							break;
				case 3:		chips = playBlackjack(chips);
							break;
				case 4:		inCasino = false;
							break;
				default:	menuChoice = 0;
			}
			
			if(menuChoice == 0)
			{
				cout << "\nPlease enter a valid option: ";
				cin.clear();
				cin.ignore();
			}

		}
		while(menuChoice == 0);

		menuChoice = 0;
	}
	while(inCasino);
							//As long as the player chooses a choice besides to leave the casino, the game will stay within the above loop
	cout << "We hope you enjoyed your time here\n\n";
	Sleep(1000);
	return 0;
}

void readRules()
{
	system("CLS");
	
	//Just stating the rules of Blackjack and how they work within my game

	cout << "\n\n"
	 	 << "********************************************************************************"
		 << "*                                                                              *"
		 << "*                                       RULES                                  *"
		 << "*                                                                              *"
		 << "********************************************************************************\n\n";
	
	Sleep(1500);
	cout << "The rules will be read one segment at a time.\n\nTo continue to the next segment, press 'Enter'\n\n";

	cin.get();
	cout << "Blackjack Basic Rules\n\n"
		 << "The aim of the game is to accumulate a higher point total that the dealer,\nwithout going over 21\n"
		 << "You are dealt cards in which are added up to make your point total\n"
		 << "The cards 2 through 10 have their number as their value, where Jack, Queen and\nKing are worth 10 each\n"
		 << "The Ace card can be worth either 1 or 11, and can be combined with a card worth 10 to achieve Blackjack\n\n";

	cin.get();
	cout << "The Initial Deal\n\n"
		 << "At the start of a hand, the Players and Dealer receive two cards each\n"
		 << "The Players cards are dealt face up, and the Delear has one face up, one\nface down\n"
		 << "As mentioned before, the best possible hand in Blackjack is Blackjack, which\nuses the Ace and any 10 point card\n"
		 << "The Player who has Blackjack automatically wins, unless another Blackjack is\npresent, then it is a tie\n\n";
	cin.get();
	cout << "The Players Turn\n\n"
		 << "When the cards have been dealt the players take their go before the Dealer\n"
		 << "The Player can choose to STAND with their current hand, or aquire more cards\nvia HIT\n"
		 << "The Player can choose to HIT as long as their hand value is 21 or under\n"
		 << "If the Players hand goes over 21, then they immediatly lose (bust)\n\n";

	cin.get();
	cout << "The Dealers Turn\n\n"
		 << "When all Players have finished their turn, the Dealer takes theirs\n"
		 << "If the Dealer has a hand value lower than 17, than they must take a card\n"
		 << "Like the Player, if the Dealer gets a Blackjack (Ace and 10 point card),\nthey win automatically\n"
		 << "The Dealer will keep hitting until their hand is worth more than 17, or they\nbust\n\n";

	cin.get();
	cout << "Showdown\n\n"
		 << "If neither the Dealer or Player bust, then they go into Showdown\n"
		 << "Here, both the Player and Dealer compare there hands to see who has the higher\nvalue\n"
		 << "The person with the higher value wins the hand\n\n"
		 << "Please press Enter to return to the Casino Floor\n";
	
	cin.get();
	cin.clear();
}

int playBlackjack(int chips)
{
	//p = Player, d = Dealer and a bunch of variables for stuff
	int  dealCard, cardsLeft = 52, bet, pHand, dHand, pAces, dAces, temp, d1, d2;												
	char play = 'n', hit = 's';									
	bool pBlackjack, dBlackjack, pBust, playCheck = true,
		 pHasAce, dHasAce;	

	deck Card[52];	  //Structure for the deck

	//Initialise the Deck	
	for(int tempValue = 0; tempValue < 52; tempValue++)
	{
		int tempCard = tempValue % 13;			//Based on the number in the for loop, will work out its number value through modulus
		int tempSuit = ((tempValue + 12) / 13); //Based on the number in the for loop, will work out its stui through math

		switch(tempCard)
		{
			case 1:		strcpy(Card[tempValue].cardName,"Ace");
						Card[tempValue].cardValue = 11;				//If the modulus returns 1 (first card in loop), it will be named Ace and have a value of 11
						break;
			case 2:		strcpy(Card[tempValue].cardName,"Two");		//If the modulus returns 2 (second card), it will be named Two and have a value of 2
						Card[tempValue].cardValue = 2;
						break;
			case 3:		strcpy(Card[tempValue].cardName,"Three");	//Three and so on
						Card[tempValue].cardValue = 3;
						break;
			case 4:		strcpy(Card[tempValue].cardName,"Four");
						Card[tempValue].cardValue = 4;
						break;
			case 5:		strcpy(Card[tempValue].cardName,"Five");
						Card[tempValue].cardValue = 5;
						break;
			case 6:		strcpy(Card[tempValue].cardName,"Six");
						Card[tempValue].cardValue = 6;
						break;
			case 7:		strcpy(Card[tempValue].cardName,"Seven");
						Card[tempValue].cardValue = 7;
						break;
			case 8:		strcpy(Card[tempValue].cardName,"Eight");
						Card[tempValue].cardValue = 8;
						break;
			case 9:		strcpy(Card[tempValue].cardName,"Nine");
						Card[tempValue].cardValue = 9;
						break;
			case 10:	strcpy(Card[tempValue].cardName,"Ten");
						Card[tempValue].cardValue = 10;
						break;
			case 11:	strcpy(Card[tempValue].cardName,"Jack");
						Card[tempValue].cardValue = 10;
						break;
			case 12:	strcpy(Card[tempValue].cardName,"Queen");
						Card[tempValue].cardValue = 10;
						break;
			default:	strcpy(Card[tempValue].cardName,"King");
						Card[tempValue].cardValue = 10;
						break;
		}

		switch(tempSuit)									
		{
			case 1:		strcpy(Card[tempValue].cardFamily,"Spade");		//If the division returns 1, it is a Spade			
						break;								
			case 2:		strcpy(Card[tempValue].cardFamily,"Heart");		//If the division returns 2, it is a Heart
						break;
			case 3:		strcpy(Card[tempValue].cardFamily,"Diamond");
						break;
			default:	strcpy(Card[tempValue].cardFamily,"Club");
						break;
		}
	}

	//Start the game
	do
	{
		if(chips == 0)		//Checks if the player has chips before the game starts
		{
			cout << "You appear to be out of chips, please come back when you are able to play";
			Sleep(3000);
			break;												
		}

		srand((unsigned)time(NULL));
		for(int i=0; i<52;i++)			//Shuffles the deck before the game starts
		{								//And will shuffle again only if the player restarts
			int shuffle = rand() % 52;
			deck tempCard = Card[i];
			Card[i] = Card[shuffle];
			Card[shuffle] = tempCard;
		}

		dealCard = 0;					//Sets the card in the deck array to 0 so it starts at the beginning of the deck
		cardsLeft = 52;					//Could have used (52 - dealcard), but it's more manageable with a variable
	
		do
		{
			bet = 0;

			pBlackjack = false;
			pHasAce = false;
			pBust = false;				//Sets major game values to default
			pAces = 0;
			pHand = 0;
										//These set and reset the values on a new hand
			dBlackjack = false;
			dHasAce = false;
			dAces = 0;
			dHand = 0;

			system("CLS");

			cout << "\n\n"		//Setup phase which includes betting and the initial 4 cards
	 			 << "********************************************************************************"
				 << "*                                                                              *"
				 << "*                                  SETUP PHASE                                 *"
				 << "*                                                                              *"
					 << "********************************************************************************\n\n";

			Sleep(1000);

			cout << "\n\n"
	 			 << "                                 ***************\n"
				 << "                                     BETTING    \n"
				 << "                                 ***************\n\n";

			//The following is the betting phase, and should be self explanatory

			cout << "Please enter a bet for this hand. Your current chip count is " << chips << endl;
			cin  >> bet;

			do
			{
				if(!playCheck)
				{
					cout << "You have entered an invalid bet, please try again: ";
					cin  >> bet;
				}
					//If the bet is higher than the players chips, or lower than 0, try again
				if(bet > chips || bet < 0)
				{
					playCheck = false;
				}
				else
				{
					playCheck = true;
				}

			}
			while(!playCheck);			

			chips -= bet;	//Minus the bet from the players chips
			cin.clear();	//Clear the cin stream
			cin.ignore();	//Ignore anything that has popped through

			cout << "\nYou have bet " << bet << ". You have " << chips << " chips left";
			//Tell the player how many chips they have bet, and how many they have remaining

			Sleep(1000);

			cout << "\n\n"
	 			 << "                                 ***************\n"
				 << "                                   FIRST CARDS  \n"
				 << "                                 ***************\n\n";


			for(int round = 1; round <= 4; round++)
			{
				if(round == 1 || round == 3)
				{ //Tell the player the card they have been dealt from the card structure, and its suit
					cout << "The Player has been dealt " << Card[dealCard].cardName << " of " << Card[dealCard].cardFamily << "s\n\n";
					
					temp = Card[dealCard].cardValue;		

					//The following is to test if the card is an ace
					if(temp == 11)
					{		//if the value is 11 (ace), add an ace to the players hand
						pAces++;
						pHand += 11;
					} 
					else
					{		//otherwise just add the value
						pHand += temp;
					}

					dealCard++;
				}
				else
				{	//The dealers turn, check to see if any of the dealt cards are aces
					temp = Card[dealCard].cardValue;		

					if(temp == 11)
					{
						dAces++;	//if ace, add ace
						dHand += 11;
					} 
					else
					{
						dHand += temp;	//otherwise don't
					}

					if(round == 2)
					{	//Tell the player what the dealer has recieved
						cout << "The Dealer has been dealt " << Card[dealCard].cardName << " of " << Card[dealCard].cardFamily << "s\n\n";
						d1 = dealCard; //remembers the dealers card to remind the player later
					}
					else
					{	//One of the dealers cards are dealt face down
						cout << "The Dealer puts his other card face down";
						d2 = dealCard;//remembers the dealers face down card to show later
					}
					dealCard++;
				}
			}

			if(pHand == 21)													
			{
				pBlackjack = true;
			}
								//Checks to see if the inital hand is 21
			if(dHand == 21)		//(Blackjack can only be obtained with 2 cards)
			{
				dBlackjack = true;
			}

			cardsLeft -= 4;

			Sleep(1000);

			cout << "\n\n"
	 			 << "********************************************************************************"
				 << "*                                                                              *"
				 << "*                                 PLAYERS TURN                                 *"
				 << "*                                                                              *"
				 << "********************************************************************************\n\n";

			do
			{
				if(pAces > 0 || pHasAce)
				{								//This function is to moderate the players hand
					if(pHand > 21 || pHasAce)	//Checks if the player is bust or has any aces unused
					{
						if(pHand > 21)			//Tells the player that their hand is being changed to stop them from busting
						{
							cout << "You have gone over the value of 21, the Ace has been demoted to stop this\n\n";
						}

						for(pAces; pAces > 0; pAces--)
						{					//This for loop activates if the player has an ace and has gone over 21	
							pHand -= 10;	//For every ace after this has triggered, '10' will be taken away				
						}					//from the hand, as if the Ace were worth 1 instead of 11.
															
						Sleep(1000);
						pHasAce = true;
					}
				}

				if(pHand > 21)		//If the players hand exceeds 21 (busts), break out of the loop
				{
					break;
				}

				if(pHand == 21)								
				{					//Checks to see if the players hand is 21, and if so stops them from playing on
					if(pBlackjack)
					{
						cout << "Blackjack!";				
					}
					else	//Stops the player from exceeding 21 if they reach it
					{
						cout << "The Player has a hand of 21, and cannot proceed further";
						Sleep(1000);
					}
					break;
				}

				if(pHand < 21)	//As long as the player hasn't bust and wants to play on, this if() is triggered
				{										
					cout << "Your current hand value is " << pHand << "\n\n";
					cout << "Would you like to [H]it or [S]tand?: ";

					do
					{
						cin  >> hit;
						cout << endl;

						playCheck = true;

						if((hit == 's') || (hit == 'S'))
						{
							break;		//If the players chooses to stand, breaks out of the loop, moving on to the next phase
						}

						if((hit == 'h') || (hit == 'H'))
						{
							cout << "The Player has been dealt " << Card[dealCard].cardName << " of " << Card[dealCard].cardFamily << "s\n\n";
							temp = Card[dealCard].cardValue;

							if(temp == 11)
							{					//If the player chooses to hit, this if() adds another card to their hand and checks if they have been dealt an ace
								pAces++;
							}

							pHand += temp;				//Adds the new card to their hand
							cardsLeft--, dealCard++;	//Move the dealing card up the array, and the cards left down
						}
						else
						{
							cout << "You have entered an invalid character\n\nWould you like to [H]it or [S]tand?: ";
							playCheck = false;		//Validation to make sure the player chooses either stand or hit					
						}
					}
					while(!playCheck);
				}									//Ending do/while loops based on input
			}
			while((hit == 'h') || (hit == 'H'));	//As long as the player hits, keep allowing to carry on

			if(pHand > 21)
			{
				cout << "The Player has bust with " << pHand << "\n\n";
				pBust = true;
			}										//Checks one more time if the player has bust, and sets the bust flag as true

			Sleep(1000);

			cout << "\n\n"
	 			 << "********************************************************************************"
				 << "*                                                                              *"
				 << "*                                 DEALERS TURN                                 *"
				 << "*                                                                              *"
				 << "********************************************************************************\n\n";

			//The dealers turn, completely automated

			if(!pBust) //If they player has bust, they have already lost and so there is no need to continue
			{
				//To start of the dealers turn, the dealers face up and face down card are told to the player
				cout << "The Dealers face up card was " << Card[d1].cardName << " of " << Card[d1].cardFamily << "s\n\n";
				cout << "The Dealers face down card was " << Card[d2].cardName << " of " << Card[d2].cardFamily << "s\n\n";
				cout << "The Dealers hand value is " << dHand << "\n\n";

				if(dHand > 21 && dAces > 0)
				{							//Conversion of the ace if the Dealer busts
					cout << "The Dealer would have bust, but his Ace has been demoted to prevent this\n\n";
					dHand -= 10, dAces --;
					dHasAce = true;
				}

				while(!pBlackjack)	
				{					//The dealer MUST hit if he has a card value of <17
					while(dHand < 17)
					{
						cout << "The Dealer deals " << Card[dealCard].cardName << " of " << Card[dealCard].cardFamily << "s\n\n";
						temp = Card[dealCard].cardValue;
						dHand += temp;			
						dealCard++;

						if(temp == 11)
						{
							dAces++;	//Checks to see if the dealer is dealt an Ace
							dHasAce = true;
						}

						cardsLeft--;

						if(dAces > 0 || dHasAce)
						{
							if(dHand > 21 || dHasAce)
							{					//Same loop to make all Aces == 1 if need be
								for(dAces; dAces > 0; dAces--)
								{
									dHand -= 10;			
								}
							}
						}

						if(dHand > 21)
						{						//Checks to see if the dealer has bust
							cout << "The Dealer has bust with " << dHand;
							break;										
						}
												//Informs the player of the dealers hand value
						cout << "The Dealers new hand value is " << dHand << "\n\n";
						Sleep(1000);
					}

					if(dHand >= 17)
					{
						break;		//Once the dealer hits 17 or higher, breaks out of the loop
					}
				}

				if(dBlackjack)
				{
					cout << "The Dealer has Blackjack\n\n";
				}	//if the dealer has blackjack, informs the player of this
			}
			else
			{
				cout << "The Player has bust, and thus there is no need to continue\n\n";
			}			//If the player has bust, then they have already lost

			Sleep(1000);

			if(!pBust)
			{									//Blackjack winning conditions

			cout << "\n\n"
	 			 << "                                 ***************\n"
				 << "                                     SHOWDOWN 	 \n"
				 << "                                 ***************\n\n";

				if(pBlackjack|| dBlackjack)	//If either play has Blackjack, compare
				{
					if(pBlackjack && dBlackjack)	//Tie
					{
						cout << "Both the Player and Dealer have Blackjack\n\n"
							 << "The pot is split between the Player and the Dealer\n\n"
							 << "The Player receives " << (bet >> 1) << " chips\n\n";
						chips += (bet >> 1);
					}

					if (pBlackjack && !dBlackjack)	//Player wins
					{
						cout << "The Player has Blackjack, and wins " << (bet * 2) << " chips\n\n";
						chips += (bet << 1);
					} 
				
					if(!pBlackjack && dBlackjack)	//Dealer wins
					{
						cout << "The Dealer has Blackjack\n\nThe Player has lost the bet\n\n";
					}																				
				}
				else	
				{								//Other winning conditions		
					if(dHand > 21)
					{				//If the dealer has bust, the player wins
						cout << "The Player wins " << (bet << 1) << " chips\n\n";
						chips += (bet << 1);
					}
					else
					{						//Compares the dealers and players hands
						if(pHand > dHand)
						{
							cout << "The Players hand is greater than the Dealers hand\n\nThe Player wins " << (bet << 1) << " chips\n\n";
							chips += (bet << 1);
						}

						if(pHand < dHand)
						{
							cout << "The Dealers hand is greater than the Players hand\n\nThe Player loses the bet\n\n";
						}

						if(pHand == dHand)
						{
							cout << "Both hands have the same value\n\nThe pot is split\n\nThe Player receives " << (bet >> 1) << " chips\n\n";
							chips += (bet >> 1);
						}
					}
				}
			}

			if(chips == 0)
			{						//If the player doesn't have any chips, they cannot play on
				cout << "\n\nYou have run out of chips and can not continue. Thank you for playing\n\n";
				play = 'n';
				Sleep(1000);
				break;
			}				
	
			do					//Checks to see if there are enough cards left to play
			{
				if(cardsLeft <= 10)
				{
					if(cardsLeft <= 6)		//If there are less than 6, reset the game
					{
						break;
					}
											//Infrom the player of the low card amount
					cout << "There are " << cardsLeft << " cards left in the deck\n";
					cout << "Do you want to continue playing? [Y]es [N]o ";
					cin  >> play;
					cout << "\n\n";
				}
				else
				{							//If there enough cards, offer to play using the same deck (no shuffle)
					cout << "Would you like to play another hand? [Y]es [N]o ";
					cin  >> play;
					cout << "\n\n";
				}

				switch(play)
				{				//Validation on the play choice
					case 'y':
					case 'Y':
					case 'n':
					case 'N': playCheck = true;
							  break;
					default : playCheck = false;
							  cout << "You have entered an invalid choice, please try again\n\n";
							  break;
				}
			}
			while(!playCheck);

			if((play == 'n') || (play == 'N'))	//If the player doesn't want to play, go to the casino lobby
			{
				break;
			}
		}
		while(cardsLeft > 6);

		if((play == 'n') || (play == 'N'))
		{
			break;		//Go to casino lobby
		}

		do
		{
			if(cardsLeft <= 6)
			{						//This is outside of the 'hand loop' so playing again would reshuffle the deck
				cout << "The deck has run out of useable cards\n\n";
	
				if(chips > 0)
				{					//If the player has chips left to spend, offer them to play again
					cout << "Would you like to play another hand? [Y]es [N]o ";
					cin  >> play;
				}
				else	
				{					//Otherwise return them to the lobby
					cout << "You have run out of chips, please return to the casino lobby";
					play = 'n';
				}

				switch(play)
				{
					case 'y':
					case 'Y':
					case 'n':
					case 'N': playCheck = true;
							  break;
					default : playCheck = false;
							  cout << "You have entered an invalid choice, please try again\n\n";
							  break;
				}
			}
		}
		while(!playCheck);

	}
	while((play == 'y') || (play == 'Y'));

	cin.clear();
	cin.ignore();

	return chips;
}

int visitCashier(int chips)
{
	int pay, loan;
	static int debt = 1000;

	system("CLS");

	//This is a cosmetic/gameplay feature. In real life you have the option to purchase more chips when you are out
	//So I thought implementing the same idea in the game would be a good way to make it more authentic

	cout << "\n\n"
 		 << "********************************************************************************"
		 << "*                                                                              *"
		 << "*                                      CASHIER                                 *"
		 << "*                                                                              *"
		 << "********************************************************************************\n\n";				 

	cout << "You currently owe the casino " << debt;

	if(chips > debt)
	{
		cout << ". Would you like to:\n\n"
			 << "1. Repay your loan (in full)\n"
			 << "2. Take out a loan?\n"
			 << "3. Leave\n";
		do
		{
			cin  >> pay;
			cin.get();
			cin.clear();

			if(pay + 1 > 256)
			{
				pay = 0;
			}

			switch(pay)
			{
				case 1:		chips -= debt;
							debt =  0;
							cout << "\nYou now have " << chips << " chips left.\nI hope you enjoy the rest of your time here";
							break;
				case 2:		cout << "\nHow much would you like to take out?\n";
							cin  >> loan;
							debt += loan;
							chips += loan;
							cout << "\nYou now have " << chips << " chips, and owe the casino " << debt;
							break;
				case 3:		break;
				default:	pay = 0;
			}

			if(pay == 0)
			{
				cout << "\nPlease enter a valid option: ";
				cin.clear();
				cin.ignore();				
			}
		}
		while(pay == 0);
	}
	else
	{
		cout << ", and cannot affort to pay back your debt.\nWould you like to:\n\n"
			 << "1. Take out a loan?\n"
			 << "2. Leave\n";

		do
		{
			cin  >> pay;

			switch(pay)
			{
				case 1:		cout << "\nHow much would you like to take out?\n";
							cin  >> loan;
							debt += loan;
							chips += loan;
							cout << "\nYou now have " << chips << " chips, and owe the casino " << debt;
							break;
				case 2:		break;
				default:	pay = 0;
							break;
			
			}

			if(pay == 0)
			{
				cout << "\nPlease enter a valid option: ";
			}
		}
		while(pay == 0);
	}

	Sleep(1500);
	return chips;
}
