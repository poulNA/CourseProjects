/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
/* INTRO:
   First off, this game takes the input from the user and makes sure it's a one valid int and calls srand.
   Secondly, it intializes max_score and number of guesses as well as copies the strings from the answer pool
   to the solutions based on the "random" number from seed.
   Thirdly, it asks for the user's guess, makes sure they are four valid strings from the pool, then compares it
   with the solution set. If they are correct and in the right position, they are "perfect" and count as 1000pts.
   If they are correct but in the wrong position, they are "misplaced" and count as 100pts. The current score is
   calculated and max score is updated if need be.

   Partners: gangulo2, ilashl2
*/
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      // your code here
      // invalid case
	printf("set_seed: invalid seed\n");
	return 0;
    }
    // your code here
    // valid case so call srand
	else {
		srand(seed);
		return 1;
	}
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    //your code here
  guess_number = 1;
  max_score = -1;
  int random;
  //copy pool to solutions from the random number
  for (int i = 0; i < 4; i++) {
 	random = rand() % 8;
  	strcpy(solutions[i], pool[random]); 
  }
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
  // your code here
  int curr;
  //check for invalid cases
 char guess[4][10];
 char post[2];
 int varscan = sscanf(guess_str, "%s%s%s%s%1s", guess[0], guess[1], guess[2], guess[3], post);
	if (varscan != 4) {
		printf("make_guess: invalid guess\n");
		return 0;
	} 
	for (int i = 0; i < 4; i++) {
		if (is_valid(guess[i]) == 0) {
			printf("make_guess: invalid guess\n");
			return 0;
		}
	}
  //check perfect and misplaced cases.
int perfect = 0;
int misplaced = 0;
int checkedg[4] = {0, 0, 0, 0};
int checkeds[4] = {0, 0, 0, 0};
	for (int i = 0; i < 4; i++) {
		if (strcmp(guess[i], solutions[i]) == 0 && checkedg[i] == 0 && checkeds[i] == 0) {
			perfect++;
			checkedg[i] = 1;
			checkeds[i] = 1;
			continue;
		}
	}
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++) {
			if (strcmp(guess[i], solutions[j]) == 0 && checkedg[i] == 0 && checkeds[j] == 0) {
				misplaced++;
				checkedg[i] = 1;
				checkeds[j] = 1;
				break;
			}
		}
	}
  //print statements, max_score and curr calculations, and returns
  printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
  guess_number++;
  curr = 1000*perfect + 100*misplaced;
  if (max_score < curr) {max_score = curr;}
  printf("Your score is %d and cur max score is %d.\n", curr, max_score);
  if (perfect == 4) {
	return 2;
  } else {
    	return 1;
    }
  
}


