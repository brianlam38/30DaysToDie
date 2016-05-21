/*
 *
 * Text Adventure RPG (NEEDS A NAME)
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
#define ATTACK 0
#define BLOCK  1

#define DAYSTOSURVIVE 30		// 

// weapon codes --> None yet

typedef struct _game game * Game;

// main game data --> IDEAS: Include starting class
typedef struct _game {
	int xcoord[5];
	int ycoord[5];
	int heroStartLocation;		//
	int startGamePrompt;		// loads set map descriptions in XY coords
	int gameOverPrompt;			// game over prompted if player dies OR daystosurvive reaches zero
	int enemyLocation;
} game;

// player data --> IDEAS: include player level
typedef struct _hero {
	int heroHealth;
	int takeActionDice;

} hero;

// enemy data --> IDEAS: enemy action diceroll, enemy chance encounters
typedef struct _enemy {
	int enemyHealth;
	int enemy
} enemy;

Game newGame(int xcoord[], int ycoord[]) {

}




