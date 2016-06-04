/*
 *
 * 30 DAYS TO DIE
 *
 * Creator: Brian Lam
 * Class: wed-16 kora  Tutor: Jordan Brown
 *
 * 30DTD.h v1.01
 * 		edit log -
 *		1.00 basic game with structs
 *		1.01 put more defines & reduced magic no's
 *		1.02
 *		1.03
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

// survivor action codes
#define USE_ENERGYBAR 0
#define USE_GUN	 	  1
#define USE_MARBLES   2

// survivor item status
#define FALSE 0
#define TRUE  1

// survivor travel codes
#define NORTH 'N'
#define SOUTH 'S'
#define EAST  'E'
#define WEST  'W'

// survivor item
#define FALSE 0
#define TRUE  1

// default game
#define DAYSTOSURVIVE 30		// starting game turn OR no. of days before win game
#define NUM_REGIONS   25		// 5 x 5 square map
#define TOTAL_GAME_ITEMS 3		// total number of game items

//##########################################################################
//BEGINNING OF STRUCT DEFINITION
//##########################################################################

typedef struct _game * Game;

// game map data --> X(WEST = decrement, EAST = increment) / Y(NORTH = increment, SOUTH = decrement)
typedef struct _map {
	//int background;			// hardcoded background descriptions
	int regions[NUM_REGIONS];	// maximum number of regions = 25
	int XYcoord[5][5];			// hardcoded map
	int itemEnergyBarLocation;	// default = 0
	int itemGunLocation;		// default = 0
	int itemMarblesLocation;	// default = 0
} map;

// player data
typedef struct _survivor {
	int takeAction;				// take action (use item)
	char str[20];				// stores player input data
	int survivorLocation;		// survivor current location
	int inventory[TOTAL_GAME_ITEMS];
	//int itemEnergyBar;			// default = 0
	//int itemGun;				// default = 0
	//int itemMarbles;			// default = 0
	//int itemReasoning;			// player always has this item --> default = 1
} survivor;

// enemy data --> IDEAS: enemy action diceroll, enemy chance encounters
typedef struct _killer {
	int killerAction;
	int killerLocation;			// killer start locations + movements throughout the game
} killer;

// main game data --> IDEAS:
typedef struct _game {
	map mapData;				// g->mapData.xxx
	survivor survivorData;	    // g->survivorData.xxx
	killer enemy1;				// g->enemy1.xxx
	killer enemy2;
	killer enemy3;
	int turnCount;				// counts current turn / days to survive
	int startGame;				// loads set map descriptions in XY coords
	int gameOver;				// game over prompted if player dies
	int winGame;				// game win prompted if days to survive reaches 0
} game;

//##########################################################################
//FUNCTION DECLARATIONS
//##########################################################################


void getCurrentTurn(Game g);
void getCurrentInventory(Game g);
void disposeGame (Game g);

//##########################################################################
//RUNGAME MAIN PROGRAM
//##########################################################################

// NOTE: WHEN FREEING GAME MEMORY, FREE THE ADDITIONAL MEMORY LOCATIONS BEFORE FREEING MAIN GAME STRUCT (g)

int main (int argc, char *argv[]) {

	// Game Introduction
	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+...............30 DAYS TO DIE................+\n");
	printf("+.............................................+\n");
	printf("+................INSTRUCTIONS.................+\n");
	printf("+.......There are 3 killers hunting you.......+\n");
	printf("+.............Survive for 30 days.............+\n");
	printf("+............Find items to help you...........+\n");
	printf("+.............................................+\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n\n");

	printf("---------Press the ENTER key to start----------\n\n");
	getchar();

	// Initialise game
	assert(malloc(sizeof(Game)) != NULL);
	Game g = malloc(sizeof(g));			
	assert(g != NULL);
	printf("Game initialised...\n");						

	// initialise game turn = 30
	g->turnCount = DAYSTOSURVIVE;
	assert(DAYSTOSURVIVE == 30);
	printf("Turns initialised...\n");								

	// initialise item location
	g->mapData.itemEnergyBarLocation = g->mapData.XYcoord[0][0];				
	g->mapData.itemGunLocation = g->mapData.XYcoord[0][0];
	g->mapData.itemMarblesLocation = g->mapData.XYcoord[0][0];	

	// initialise survivor items
	g->survivorData.inventory[0] = FALSE;	// energy bar
	g->survivorData.inventory[1] = FALSE;	// gun
	g->survivorData.inventory[2] = FALSE;	// marbles

	// initialise survivor + killer locations
	g->survivorData.survivorLocation = g->mapData.XYcoord[0][0]; 
	g->enemy1.killerLocation = g->mapData.XYcoord[0][4];
	g->enemy2.killerLocation = g->mapData.XYcoord[4][0];
	g->enemy3.killerLocation = g->mapData.XYcoord[4][4];

	while (g->turnCount != 0) {
		// Show current turn
		getCurrentTurn(g);
		// Show player inventory
		getCurrentInventory(g);

		// Trigger item discovery

		// Print background descr
		// Trigger enemy encounter
		// Print available moves to player
		// Scanf player action then strcmp to see if it is a possible action
		// Print result + endgame / restart option available

		g->turnCount--;
	}


/*
	printf("-----What is your name, survivor?-----\n\n");
	fgets(str, 10, stdin);
	printf("Welcome, %s, you have 30 days to survive.\n");
*/
	disposeGame(g);

	printf("End of game...\n");

	return EXIT_SUCCESS;
}

//##########################################################################
//SETTER INTERFACE FUNCTIONS
//##########################################################################

// Disposes game data upon new game or exit
void disposeGame (Game g) {
	free(g);
}

/*
int takeAction() {			// Survivor item actions
}

int takeAction() {			// Survivor item actions
}

int takeMovement() {		// Survivor movement actions
}

int enemyAction() {			// Encounter enemy --> enemy triggers action
}
*/


//##########################################################################
//GETTER INTERFACE FUNCTIONS
//##########################################################################

// Print current turn number
void getCurrentTurn(Game g) {
	if (g->turnCount != 1) {
		printf("---------YOU HAVE %d DAYS TO SURVIVE----------\n\n", g->turnCount);
	} else {
		printf("---------SURVIVE FOR ONE MORE DAY----------\n\n");			
	}
}

// Get current survivor items
void getCurrentInventory(Game g) {		

	printf("YOUR ITEMS:");

	if ((g->survivorData.inventory[0] == FALSE) &&						
		(g->survivorData.inventory[1] == FALSE) &&
		(g->survivorData.inventory[2] == FALSE)) {
		printf("-- You currently have no items --\n\n");
	} else {
		if (g->survivorData.inventory[0] == TRUE) {
			printf("[energy bar]. ");
		} else if (g->survivorData.inventory[0] == FALSE) {
			printf("[EMPTY]. ");			
		} else if (g->survivorData.inventory[1] == TRUE) {
			printf("[gun]. ");
		} else if (g->survivorData.inventory[1] == FALSE) {
			printf("[EMPTY]. ");
		} else if (g->survivorData.inventory[2] == TRUE) {
			printf("[marbles]. ");
		} else if (g->survivorData.inventory[2] == FALSE) {
			printf("[EMPTY]. ");
		}
	}
}

/*
char availableActions (Game g) {

}
*/

/*

int getLegalPath() {		// Gets + displays available paths to survivor
}

int getCurrentLocation() {	// Gets current survivor location
}

int getKillersLocations()	 {	// Gets current location of all killers
}
*/





