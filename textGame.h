/*
 *
 * 30 DAYS TO DIE
 *
 * Creator: Brian Lam
 * Class: wed-16 kora  Tutor: Jordan Brown
 *
 * textGame.h v1.0
 * 		edit log -
 *		1.00
 *		1.01
 *		1.02
 *		1.03
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

// hero action codes
#define EAT_ENERGYBAR 0
#define SHOOT_GUN	  1
#define 

// hero travel codes
#define NORTH 0
#define SOUTH 1
#define EAST  2
#define WEST  3

// game structure
#define DAYSTOSURVIVE 30		// days until game over prompts
#define MAX_REGIONS 25			// 5 x 5 square map

// weapon codes --> Add a special gun with bonus attack action

typedef struct _game game * Game;

// main game data --> IDEAS: Include starting class
typedef struct _game {
	map mapData;				// g->mapData.xxx
	killer enemy1;				// g->enemy1.xxx
	killer enemy2;
	killer enemy3;
	survivor survivorData;	    // g->survivorData.xxx
	int startGamePrompt;		// loads set map descriptions in XY coords
	int gameOverPrompt;			// game over prompted if player dies OR daystosurvive reaches zero
} game;

typedef struct _map {
	int backgroundData;			// background description
	int regions[MAX_REGIONS];	// maximum number of regions = 25
	int xcoord[5];				// hardcoded map
	int ycoord[5];				// hardcoded map
} map;

// player data --> IDEAS: include player level
typedef struct _survivor {
	items equipment;			// items that the survivor can use
	int heroHealth;
	int daysToSurvive;			// days until death
	int takeAction;				// take action (travel, use item)
	int currentLocation;
} survivor;

// enemy data --> IDEAS: enemy action diceroll, enemy chance encounters
typedef struct _killer {
	int killerLocation;
	int killerHealth;
	int killer
} enemy;

// game items
typedef struct _items {

} items;

Game newGame(int xcoord[], int ycoord[]) {

}




