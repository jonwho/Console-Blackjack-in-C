// Student: Jonathan Ho
// Instructor: Mr. Wagner
// Class: ComSci 121
// Date: 5/11/09

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DECK_SIZE 52

typedef enum
{
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
	JACK, QUEEN, KING,
	ACE
} CARD_NAME;

typedef struct
{
	CARD_NAME name;
	int value;
} CARD;

/*
	Initializes the given card array to a typical 52 card deck.
*/
void initDeck(CARD deck[])
{
	int counter;
	int curr_value = 0; //For the obscure bug that occurs; the "skipping" of counter
	for(counter = 0; counter < DECK_SIZE; counter++)
	{
		deck[counter].name = counter % 13; //Gets card name
		if(deck[counter].name == JACK ||
		deck[counter].name == QUEEN ||
		deck[counter].name == KING)
			deck[counter].value = 10; //Gets card value for face cards
		else if(deck[counter].name == ACE)
			deck[counter].value = 11; //Gets card value for Ace
		else
		{
			deck[counter].value = curr_value % 9 + 2; //Gets card value for # cards
			curr_value++;
		}
	}
}

/*
	Randomly shuffles the cards in the deck.
*/
void shuffleDeck(CARD deck[])
{
	CARD temp; //Temporary value holder
	int curr_index; //Used to switch places with new_loc
	int new_loc; //New location of card in deck
	for(curr_index = 0; curr_index < DECK_SIZE; curr_index++)
	{
		new_loc = rand() % DECK_SIZE; //Picks subscript from DECK_SIZE - 1 for array
		temp = deck[curr_index]; //Type CARD temp gets card from 0 - 51
		deck[curr_index] = deck[new_loc]; //Current card gets new location
		deck[new_loc] = temp; //New location gets temp
	}
}

/*
	Prints the given card to the console.
*/
void printCard(CARD card)
{
	switch(card.name)
	{
		//Prints Card Name and Card Value assigned from initDeck
		case TWO:
			printf(" Two (%d)", card.value);
			break;
		case THREE:
			printf(" Three (%d)", card.value);
			break;
		case FOUR:
			printf(" Four (%d)", card.value);
			break;
		case FIVE:
			printf(" Five (%d)", card.value);
			break;
		case SIX:
			printf(" Six (%d)", card.value);
			break;
		case SEVEN:
			printf(" Seven (%d)", card.value);
			break;
		case EIGHT:
			printf(" Eight (%d)", card.value);
			break;
		case NINE:
			printf(" Nine (%d)", card.value);
			break;
		case TEN:
			printf(" Ten (%d)", card.value);
			break;
		case JACK:
			printf(" Jack (%d)", card.value);
			break;
		case QUEEN:
			printf(" Queen (%d)", card.value);
			break;
		case KING:
			printf(" King (%d)", card.value);
			break;
		case ACE:
			printf(" Ace (%d)", card.value);
			break;
	}
}


/*
	Prints a card in the deck using *curr as an subscript.
	curr is incremented to point to the next card to be dealt.
	Returns the value of the card which was just dealt.
*/
int dealCard(CARD deck[], int *curr)
{
	printCard(deck[*curr]); //Calls printCard with current card
	++*curr; //*curr++ doesn't work
	return deck[*curr - 1].value;
}

/*
	Prompts the user for stand and hit.  Deals cards to the player.
	Checks for a bust.
	A return value of 1 indicates the player did not bust.
	A return value of 0 indicates the player did bust.
*/
int playerTurn(CARD deck[], int *player_value, int *current_card)
{
	char opt[5], hit[] = "hit", stand[] = "stand";
	printf("Player's turn:\n");
	//Loops for player action
	do
	{
		printf("Options: [hit] [stand]\n");
		scanf("%s", opt);
		if(strcmp(opt, hit) == 0)
		{
			printf("New card:");
			*player_value += dealCard(deck, current_card);
			if(*player_value < 22)
				printf("\nPlayer has: %d\n", *player_value);
		}
		else if(strcmp(opt, stand) == 0)
			return 1;
	} while(*player_value < 22);
	printf("\nPlayer bust!  You lose.\n");
	return 0;
}

/*
	Deals cards to the dealer until dealer_value > 17 or a bust occurs.
	A return value of 1 indicates the dealer did not bust.
	A return value of 0 indicates the dealer did bust.
*/
int dealerTurn(CARD deck[], int *dealer_value, int *current_card)
{
	printf("Dealer's turn:\n");
	//Loop until dealer hits soft 17 or bust occurs
	do
	{
		//Check if dealer_value > 17
		if(*dealer_value > 16)
		{
			printf("Dealer stands.\n");
			return 1;
		}
		//Dealer must hit until value > 17 or bust occurs
		else
		{
			printf("New card:");
			*dealer_value += dealCard(deck, current_card);
			printf("\nDealer has: %d\n", *dealer_value);
		}
	} while(*dealer_value < 22);
	//Dealer busts
	printf("Dealer bust!  You win.\n");
	return 0;
}

/*
	Checks to see which value is higher: player_value or dealer_value.
	If the player wins, bankroll is increased by bet.
	If the dealer wins, bankroll is decreased by bet.
*/
void handleEndRound(int player_value, int dealer_value, int *bankroll, int bet)
{
	//Compare player value with dealer value
	if(player_value == dealer_value)
		printf("Push!\n"); //Player ties, bankroll remains the same
	else if(player_value > dealer_value)
	{
		printf("You win!\n");
		*bankroll += bet; //Player wins, bankroll incremented by bet
	}
	else
	{
		printf("You lose!\n");
		*bankroll -= bet; //Player loses, decremented by bet
	}
	printf("Current bankroll: %d\n", *bankroll);
}

/*
	Deals two cards to each player.  player_value and dealer_value take on the
	values of their respective hands.
*/
void handleBeginRound(CARD deck[], int *player_value, int *dealer_value, int *current_card)
{
	int counter;
	printf("Current hand:");
	//Deal two cards to player, then add card values together into player_value
	for(counter = 0; counter < 2; counter++)
	{
		*player_value += dealCard(deck, current_card);
	}
	printf(".  Player has: %d\n", *player_value);
	printf("Dealer hand:");
	//Deal two cards to dealer, then add card values together into dealer_value
	for(counter = 0; counter < 2; counter++)
	{
		*dealer_value += dealCard(deck, current_card);
	}
	printf(".  Dealer has: %d\n", *dealer_value);
}

/*
	Retrieves the bet from the user.  Loops until the user
	enters a valid number (greater than zero and less than
	bankroll).  This valid number is returned.
*/
int getBet(int bankroll)
{
	int bet; //Value wished to be gambled by user
	//Loop until a valid bet is made
	do
	{
		printf("Current bankroll: %d\n", bankroll); //Displays bankroll available
		printf("Enter bet:\n");
		scanf("%d", &bet);
		if(bet > bankroll || bet <= 0)
			printf("Bet must be greater than zero and at most %d\n", bankroll);
	} while(bet > bankroll || bet <= 0);
	return bet;
}

/*
	Asks the user if they would like to play again.
	If the player's bankroll is zero, tell the user
	they are broke and return.
	A return value of 1 indicates the game should continue
	A return value of 0 indicates the game should stop
*/
int keepOnGoing(int bankroll)
{
	char choice[3], yes[] = "yes", no[] = "no";
	//Bankroll is not sufficient to continue
	if(bankroll == 0)
	{
		printf("You are broke, get out of the casino!\n");
		return 0;
	}
	//Ask if user would like to play again
	else
	{
		printf("Would you like to play again?  [yes] [no]\n");
		scanf("%s", choice);
		if(strcmp(choice, yes) == 0)
				return 1;
		else if(strcmp(choice, no) == 0)
			return 0;
	}
}

/* You may redesign this code however you please.
   Using this code is completely optional.
*/

int main(int argc, char *argv[])
{
	int bankroll;
	CARD deck[DECK_SIZE];
	/* handle command line arguments */
	if(argc > 3 || argc == 1)
	{
		printf("Usage: %s [bankroll] [optional: seed]\n", argv[0]); //Prints error and usage of program
		return 0;
	}
	else if(argc > 1)
	{
		bankroll = atoi(argv[1]);
		srand(time(NULL));
		if(argc == 3)
			srand(atoi(argv[2]));
	}

	printf("== Blackjack v1.0 ==\n");
	printf("Initializing deck...\n");
	initDeck(deck);

	/* One iteration represents the win or loss of one round */
	do
	{

		int current_card = 0, /* Next card to be dealt.  Valid values are 0 to (DECK_SIZE-1) */
			player_value = 0, /* Value of the player's hand */
			dealer_value = 0, /* Value of the dealer's hand */
			bet = 0;	      /* bet placed by the player */

		printf("Shuffling deck...\n");
		shuffleDeck(deck);
		bet = getBet(bankroll);
		handleBeginRound(deck, &player_value, &dealer_value, &current_card);
		/* if the player didn't bust */
		if(playerTurn(deck, &player_value, &current_card))
		{
			/* if the dealer didn't bust */
			if(dealerTurn(deck, &dealer_value, &current_card))
				handleEndRound(player_value, dealer_value, &bankroll, bet);
			else
				bankroll += bet;
		}
		else
			bankroll -= bet;
	} while(keepOnGoing(bankroll));

	printf("Goodbye!\n");
}
