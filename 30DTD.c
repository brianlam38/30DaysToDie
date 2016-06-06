/*
 *
 * 30 DAYS TO DIE
 *
 * Creator: Brian Lam
 * Class: wed-16 kora  Tutor: Jordan Brown
 *
 * 30DTD.h v1.03
 * 		edit log -
 *		1.00 basic game with structs
 *		1.01 added getCurrentTurn, getCurrentInventory
 *		1.02 added itemDiscovery
 *		1.03 added pathing system
 *		1.04 added 1 enemy + encounter
 *		1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// survivor item status
#define FALSE 0
#define TRUE  1

// hardcoded map
#define REGION_1_P_LOC	1		// Survivor location
#define REGION_2		2
#define REGION_3		3
#define REGION_4_E_LOC  4		// Killer 1 location
#define REGION_5_BAR	5		// Energy bar location
#define REGION_6 		6
#define REGION_7 		7
#define REGION_8 		8
#define REGION_9		9
#define REGION_10		10
#define REGION_11_GUN	11		// Gun location
#define REGION_12		12
#define REGION_13_E_LOC	13		// Killer 2 location
#define REGION_14 		14
#define REGION_15_MAR 	15		// Marbles location
#define REGION_16_E_LOC	16		// Killer 3 location

// default game
#define DAYSTOSURVIVE 30		// starting game turn OR no. of days before win game
#define NUM_REGIONS   16		// 4 x 4 square map

//##########################################################################
//BEGINNING OF STRUCT DEFINITION
//##########################################################################

typedef struct _game * Game;

// game map data
typedef struct _map {
	int regions[NUM_REGIONS];
	int XYcoord[4][4];
} map;

// player data
typedef struct _survivor {
	int takeAction;
	int survivorLocation;
	int itemEnergyBar;			// default = FALSE
	int itemGun;				// default = FALSE
	int itemMarbles;			// default = FALSE
} survivor;

// enemy data
typedef struct _killer {
	int killerAction;
	int killerLocation;
} killer;

// main game struct
typedef struct _game {
	map mapData;
	survivor survivorData;
	killer enemy1;
	killer enemy2;
	killer enemy3;
	int turnCount;
} game;

// ##########################################################################
// FUNCTION DECLARATIONS
// ##########################################################################

void getCurrentTurn(Game g);
void itemDiscovery (Game g);
void getCurrentInventory(Game g);
void enemyEncounter (Game g);
//void enemyMovement (Game g);
void disposeGame (Game g);
void takeMovement(Game g);

// ##########################################################################
// MAIN PROGRAM
// ##########################################################################

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

	// hardcoded map + item locations
	g->mapData.XYcoord[0][0] = REGION_1_P_LOC;
	g->mapData.XYcoord[0][1] = REGION_2;
	g->mapData.XYcoord[0][2] = REGION_3;
	g->mapData.XYcoord[0][3] = REGION_4_E_LOC;
	g->mapData.XYcoord[1][0] = REGION_5_BAR;
	g->mapData.XYcoord[1][1] = REGION_6;
	g->mapData.XYcoord[1][2] = REGION_7;
	g->mapData.XYcoord[1][3] = REGION_8;
	g->mapData.XYcoord[2][0] = REGION_9;
	g->mapData.XYcoord[2][1] = REGION_10;
	g->mapData.XYcoord[2][2] = REGION_11_GUN;
	g->mapData.XYcoord[2][3] = REGION_12;
	g->mapData.XYcoord[3][0] = REGION_13_E_LOC;
	g->mapData.XYcoord[3][1] = REGION_14;
	g->mapData.XYcoord[3][2] = REGION_15_MAR;
	g->mapData.XYcoord[3][3] = REGION_16_E_LOC;

	// initialise survivor items
	g->survivorData.itemEnergyBar = FALSE;
	g->survivorData.itemGun = FALSE;	
	g->survivorData.itemMarbles = FALSE;

	// initialise survivor + killer locations	
	g->survivorData.survivorLocation = REGION_1_P_LOC;	
	g->enemy1.killerLocation = REGION_4_E_LOC;			
	g->enemy2.killerLocation = REGION_13_E_LOC;			
	g->enemy3.killerLocation = REGION_16_E_LOC;			

	// MAIN RUNGAME FUNCTION
	while (g->turnCount != 0) {
		getCurrentTurn(g);					// Show current turn
		itemDiscovery(g);					// Trigger item discovery
		getCurrentInventory(g);				// Show player inventory
		enemyEncounter (g);					// Trigger enemy encounter
		takeMovement(g);					// Show player movement options
		g->turnCount--;
	}

	// END GAME
	disposeGame(g);
	printf("End of game...\n");

	return EXIT_SUCCESS;
}

// ##########################################################################
// SETTER INTERFACE FUNCTIONS
// ##########################################################################

/* ITEM DISCOVERY */
void itemDiscovery (Game g) {
	// Discover energy bar
	if (g->survivorData.survivorLocation == REGION_5_BAR) {
		printf("   You found a PROTEIN BAR on the floor!\n\n");
		// Add energy bar to inventory			
		g->survivorData.itemEnergyBar = TRUE;

	// Discover gun
	} else if ((g->survivorData.survivorLocation == REGION_11_GUN) &&
		(g->survivorData.itemGun == FALSE)) {
		printf("   You found a GUN on the floor!\n\n");
		// Add gun to inventory
		g->survivorData.itemGun = TRUE;

	// Discover marbles
	} else if ((g->survivorData.survivorLocation == REGION_15_MAR) &&
		(g->survivorData.itemMarbles == FALSE)) {
		printf("   You found a BAG OF MARBLES on the floor!\n\n");
		// Add marbles to inventory
		g->survivorData.itemMarbles = TRUE;
		// No discovery
	} else {
		printf("   There is nothing around that you can use. \n\n");
	}
}

/* ENEMY ENCOUNTERS */
void enemyEncounter (Game g) {
	char enemy1Action[15];
	char useBar[10];
	char useGun[10];
	char useMar[15];

	// Enemy 1 encounter
	if (g->enemy1.killerLocation == g->survivorData.survivorLocation) {
		printf("A strange man appears.\n");
		printf("He brandishes a large knife.\n");
		printf("He begins to walk in your direction.\n\n");

		if ((g->survivorData.itemEnergyBar == TRUE) || (g->survivorData.itemGun == TRUE) ||
			(g->survivorData.itemMarbles == TRUE)) {
			printf("YOUR AVAILABLE ACTIONS: ['USE BAR']['USE GUN']['USE MARBLES']\n\n");
			scanf("%s", enemy1Action);
			strcpy(enemy1Action, useBar);
			strcpy(enemy1Action, useGun);
			strcpy(enemy1Action, useMar);
			while (g->enemy1.killerLocation == g->survivorData.survivorLocation) {

				if ((strcmp(enemy1Action, useBar) == 0) && (g->survivorData.itemEnergyBar == TRUE)) {
					printf("The strange man sees you eating a protein bar.\n");
					printf("He thinks twice about attacking you.\n\n");
					printf("He walks away.\n\n");
					g->survivorData.itemEnergyBar = FALSE;
				} else if ((strcmp(enemy1Action, useGun) == 0) && (g->survivorData.itemGun == TRUE)) {
					printf("You pull out your gun and point it at the man.\n");
					printf("You pull the trigger...... and you miss.\n");
					printf("It seems to have frightened him. He runs away.\n\n");
					g->survivorData.itemGun = FALSE;				
				} else if ((strcmp(enemy1Action, useMar) == 0) && (g->survivorData.itemMarbles == TRUE)) {
					printf("You throw a bag of marbles in front of him.\n");
					printf("He continues to walk faster towards you....\n");
					printf("He trips on the marbles and falls over.\n");
					printf("You seem to be safe to move for now.\n\n");
					g->survivorData.itemEnergyBar = FALSE;	
				} else {
					printf("You don't have that item.\n\n");
					scanf("%s", enemy1Action);
				}
			}
		} else {
			printf("YOUR AVAILABLE ACTIONS: [YOU HAVE NO ITEMS TO USE]\n\n");
			printf("You frantically try to escape, but the man catches\n");
			printf("up to you. He plunges the knife through your body\n");
			printf("and you black out...\n\n");
			printf("--------------------GAME OVER---------------------\n");			
			printf("-------------YOU SURVIVED FOR %d DAYS-------------\n", g->turnCount);
			exit(0);
		}
	}
}

/* HARDCODED MAP MOVEMENT */
void takeMovement (Game g) {
	printf("WHERE DO YOU WANT TO GO NEXT? \n");
	char playerInput = '\0';

	if (g->survivorData.survivorLocation == REGION_1_P_LOC) {
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		while (g->survivorData.survivorLocation == REGION_1_P_LOC) {	// Region 1 options
			scanf("%c", &playerInput);
			if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_2;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_5_BAR;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_2) {			// Region 2 options
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_2) {
			scanf("%c", &playerInput);
			if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_1_P_LOC;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_6;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_3;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_3) {			// Region 3 options
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_3) {
			scanf("%c", &playerInput);
			if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_2;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_7;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_4_E_LOC;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_4_E_LOC) {	// Region 4 options
		printf("'S' to move SOUTH\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_4_E_LOC) {
			scanf("%c", &playerInput);
			if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_3;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_8;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_5_BAR) {		// Region 5 options
		printf("'N' to move NORTH\n");			
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		while (g->survivorData.survivorLocation == REGION_5_BAR) {	
			scanf("%c", &playerInput);	
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_1_P_LOC;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_9;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_6;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_6) {			// Region 6 options
		printf("'N' to move NORTH\n");			
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_6) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_2;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_10;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_7;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_5_BAR;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_7) {			// Region 7 options
		printf("'N' to move NORTH\n");			
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_7) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_3;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_11_GUN;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_8;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_6;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_8) {			// Region 8 options
		printf("'N' to move NORTH\n");			
		printf("'S' to move SOUTH\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_8) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_4_E_LOC;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_12;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_16_E_LOC;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_9) {			// Region 9 options
		printf("'N' to move NORTH\n");			
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		while (g->survivorData.survivorLocation == REGION_9) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_5_BAR;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_13_E_LOC;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_10;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_10) {			// Region 10 options
		printf("'N' to move NORTH\n");			
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_10) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_6;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_14;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_11_GUN;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_9;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_11_GUN) {		// Region 11 options
		printf("'N' to move NORTH\n");			
		printf("'S' to move SOUTH\n");
		printf("'E' to move EAST\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_11_GUN) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_7;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_15_MAR;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_12;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_10;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_12) {			// Region 12 options
		printf("'N' to move NORTH\n");			
		printf("'S' to move SOUTH\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_12) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_8;
			} else if (playerInput == 'S') {
				g->survivorData.survivorLocation = REGION_16_E_LOC;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_1_P_LOC;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_13_E_LOC) {	// Region 13 options
		printf("'N' to move NORTH\n");			
		printf("'E' to move EAST\n");
		while (g->survivorData.survivorLocation == REGION_13_E_LOC) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_9;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_14;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_14) {			// Region 14 options
		printf("'N' to move NORTH\n");			
		printf("'E' to move EAST\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_14) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_10;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_15_MAR;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_13_E_LOC;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_15_MAR) {		// Region 15 options
		printf("'N' to move NORTH\n");			
		printf("'E' to move EAST\n");
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_15_MAR) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_11_GUN;
			} else if (playerInput == 'E') {
				g->survivorData.survivorLocation = REGION_16_E_LOC;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_14;
			}
		}	
	} else if (g->survivorData.survivorLocation == REGION_16_E_LOC) {	// Region 16 options
		printf("'N' to move NORTH\n");			
		printf("'W' to move WEST\n");
		while (g->survivorData.survivorLocation == REGION_16_E_LOC) {		
			scanf("%c", &playerInput);
			if (playerInput == 'N') {
				g->survivorData.survivorLocation = REGION_12;
			} else if (playerInput == 'W') {
				g->survivorData.survivorLocation = REGION_15_MAR;
			}
		}
	}
	printf("\n\n");
}

/* DISPOSE GAME DATA */
void disposeGame (Game g) {
	free(g);
}

// ##########################################################################
// GETTER INTERFACE FUNCTIONS
// ##########################################################################

/* PRINT CURRENT TURN NUMBER */
void getCurrentTurn(Game g) {
	if (g->turnCount != 1) {
		printf("______________________________________________\n");
		printf("|                                            |\n");
		printf("|         YOU HAVE %d DAYS TO SURVIVE        |\n", g->turnCount);
		printf("|____________________________________________|\n");
	// last day
	} else {
		printf("______________________________________________\n");
		printf("|                                            |\n");
		printf("|         SURVIVE FOR ONE MORE DAY!      	 |\n");
		printf("|____________________________________________|\n");
	}
}

/* GET CURRENT INVENTORY */
void getCurrentInventory(Game g) {		

	printf("YOUR ITEMS:");

	// NO ITEMS
	if ((g->survivorData.itemEnergyBar == FALSE) &&						
		(g->survivorData.itemGun == FALSE) &&
		(g->survivorData.itemMarbles == FALSE)) {
		printf("[You currently have no items]\n\n");
	} else {
		// INVENTORY SLOT 1
		if (g->survivorData.itemEnergyBar == TRUE) {
			printf("[A protein bar]");
		} else {
			printf("[EMPTY]");			
		}
		// INVENTORY SLOT 2
		if (g->survivorData.itemGun == TRUE) {
			printf("[A gun]");
		} else {
			printf("[EMPTY]");
		}
		// INVENTORY SLOT 3
		if (g->survivorData.itemMarbles == TRUE) {
			printf("[A bag of marbles].\n\n");
		} else {
			printf("[EMPTY].\n\n");
		}
	}
}


