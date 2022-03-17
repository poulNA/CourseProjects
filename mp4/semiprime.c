#include <stdlib.h>
#include <stdio.h>
/* Partners: ilashl2, gangulo2
Debugging Process:
1. main.c was missing a semicolon at ret=... Necessary for compilation.
2. In is_prime return 0 changed to return 1 and return 1 changed to 
   return 0 in order to end is_prime properly and print the right values.
3. In print_semiprimes, change k=i%j to k=i/j. We want the quotient not
   the remainder.
4. In print_semiprimes after printf("d", i), put in ret = 1; to change 
   the return value to 1. If semiprime return value should be 1.
5. After that ret = 1;, put in break; to exit the loop. Once
   we determine that the current number is semiprime, we need
   to go on to the next number, not keep incrementing. */
/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1;
		 	break;
                    } 
                }
            }
        }

    }
    printf("\n");
    return ret;

}
