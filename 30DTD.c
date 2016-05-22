/*
 *
 * 30 DAYS TO DIE
 *
 * Creator: Brian Lam
 * Class: wed-16 kora  Tutor: Jordan Brown
 *
 * 30DTD.h v1.01
 * 		edit log -
 *		1.00 basic game
 *		1.01 added macro titles + more comments
 *		1.02
 *		1.03
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

// survivor action codes
#define USE_ENERGYBAR 0
#define USE_GUN	 	  1
#define USE_MARBLES   2
#define USE_REASONING 3

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

//##########################################################################
//BEGINNING OF STRUCT DEFINITION
//##########################################################################

typedef struct _game * Game;

// game map data --> X(WEST = decrement, EAST = increment) / Y(NORTH = increment, SOUTH = decrement)
typedef struct _map {
	int background;				// hardcoded background descriptions
	int regions[NUM_REGIONS];	// maximum number of regions = 25
	int XYcoord[5][5];			// hardcoded map
	int itemLocation;			// item locations
} map;

// player data
typedef struct _survivor {
	int takeAction;				// take action (use item)
	int survivorLocation;		// survivor current location
	int itemEnergyBar;			// default = 0
	int itemGun;				// default = 0
	int itemMarbles;			// default = 0
	int itemReasoning;			// player always has this item --> default = 1
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
//RUNGAME MAIN PROGRAM
//##########################################################################

// NOTE: WHEN FREEING GAME MEMORY, FREE THE ADDITIONAL MEMORY LOCATIONS BEFORE FREEING MAIN GAME STRUCT (g)

int main (int argc, char *argv[]) {
	printf("+++++++++++++++++++++++++++++++++++++++++\n");
	printf("+............30 DAYS TO DIE.............+\n");
	printf("+.............By Brian Lam..............+\n");
	printf("+.......................................+\n");
	printf("+.............INSTRUCTIONS..............+\n");
	printf("+....There are 3 killers hunting you....+\n");
	printf("+..........Survive for 30 days..........+\n");
	printf("+.......................................+\n");
	printf("+++++++++++++++++++++++++++++++++++++++++\n");

	printf("Game end...\n");
	return EXIT_SUCCESS;
}

//##########################################################################
//BEGINNING OF SETTER INTERFACE FUNCTIONS
//##########################################################################

Game newGame (void) {				// initialises game map + descriptions, survivor + killer + items starting positions

	Game g = malloc(sizeof(g));									// setting aside memory for game

	g->turnCount = DAYSTOSURVIVE;								// initialise game turn = 30

	g->survivorData.itemEnergyBar = FALSE;						// initialise survivor items
	g->survivorData.itemGun = FALSE;
	g->survivorData.itemMarbles = FALSE;
	g->survivorData.itemReasoning = TRUE;

	g->survivorData.survivorLocation = g->mapData.XYcoord[0][0]; // initialise survivor + killer locations
	g->enemy1.killerLocation = g->mapData.XYcoord[0][4];
	g->enemy2.killerLocation = g->mapData.XYcoord[4][0];
	g->enemy3.killerLocation = g->mapData.XYcoord[4][4];

	return g;
}

//##########################################################################
//BEGINNING OF GETTER INTERFACE FUNCTION
//##########################################################################


/*
int takeAction() {			// Survivor item actions
}

int takeMovement() {		// Survivor movement actions
}

int enemyAction() {			// Encounter enemy --> enemy triggers action
}
*/

/* GETTER FUNCTIONS */

/*
int getCurrentItems() {		// Get current survivor items
}

int getCurrentTurn() {		// Turn starts at 30, then decreases by 1 per player action
}

int getLegalPath() {		// Gets + displays available paths to survivor
}

int getCurrentLocation() {	// Gets current survivor location
}

int getKillersLocations()	 {	// Gets current location of all killers
}
*/

