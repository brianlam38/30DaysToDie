/*
 *
 * 30 DAYS TO DIE
 *
 * Creator: Brian Lam
 * Class: wed-16 kora  Tutor: Jordan Brown
 *
 * run30DTD.c v1.0
 * 		edit log -
 *		1.00 basic game
 *		1.01
 *		1.02
 *		1.03
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "30DTD.c"

int main(int argc, char *argv[]) {

	printf ("Starting game...\n");
	Game g = 0;

	if (g->turnCount == DAYSTOSURVIVE) {
	printf("+++++++++++++++++++++++++++++++++++++++++\n");
	printf("+            30 DAYS TO DIE             +\n");
	printf("+   		  By Brian Lam              +\n");
	printf("+      							        +\n");
	printf("+      	      INSTRUCTIONS              +\n");
	printf("+  (1) There are 3 killers hunting you. +\n");
	printf("+ 		 (2) Survive for 30 days.       +\n");
	printf("+      							        +\n");
	printf("+++++++++++++++++++++++++++++++++++++++++\n");
	}

	return EXIT_SUCCESS;
}