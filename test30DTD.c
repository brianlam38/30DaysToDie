/*
 *
 * 30 DAYS TO DIE
 *
 * Creator: Brian Lam
 * Class: wed-16 kora  Tutor: Jordan Brown
 *
 * test30DTD.c
 *
 * TEST GAME CODE
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "30DTD.h"

int main (int argc, char * argv[]) {
    printf ("Testing the game\n");

    testgetTurnNumber();
    testgetCampus();
    testgetARC();
    testgetDiscipline();
    testgetDiceValue();


    printf ("All tests passed! You are Awesome!\n");

    return EXIT_SUCCESS;
}



