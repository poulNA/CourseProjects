;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; Start the 27counter and pointer at 0. Start at the HISTR_ADRR and print out
; the character starting from x40, which is '@'. Print the remaining 4 
; characters by implementing left shift from R3 to R0. R3 is where the data
; HISTR_ADDR will be. Then print a new line and increment counter and pointer.
; Loop 27 times by doing counter-27 and if it hits 0 program is done.
; Add pointer to HISTR_ADDR to point to the next address for next data for 
; the hex count.

; partners: ilashl2, gangulo2

; R0: Printed Value
; R1: Digit Counter
; R2: Bit Counter
; R3: Data for the hex value
; R4: Temp value for inequality if conditions
; R5: 27Counter/Address Pointer
; R6: Temp value for inequality if conditions

			AND R5, R5, #0  ; R5(counter/pointer) = 0
BIN			LD R0, CHAR    ; R0 = '@'
			ADD R0, R0, R5  ; current character
			OUT			    ; Print char
			LD R0, SPACE    ; R0 = 'space'
			OUT			    ; Print space
			LD R0, HIST_ADDR ; R0 = first address
			ADD R0, R0, R5  ; R0 = current memory address
			LDR R3, R0, #0  ; Load memory address R0 into R3
			
			

			AND R1, R1, #0; initialize digit counter
			ADD R1, R1, #4; set counter to 4
Digit_Loop	AND R0, R0, #0; Clear digit/R0
			AND R2, R2, #0; initialize bit counter
			ADD R2, R2, #4; set bit counter to 4
Bit_Loop	ADD R0, R0, R0; left shift r0(digit)
			ADD R3, R3, #0; Set CC according to R3
			BRzp Pos_Loop  ;
Neg_Loop 	ADD R0, R0, #1; add 1 to R0
Pos_Loop 	Add R0, R0, #0; add 0 to R0
			ADD R3, R3, R3; left shift R3
			ADD R2, R2, #-1; 
			BRp Bit_Loop ;
			
			AND R4, R4, #0; Clear R4
			ADD R4, R0, #-9; R4 = digit-9
			BRp More_than  ; digit more than 9
			LD R4, A_Fill  ; Load R4 with #48
Less_than_equal ADD R0, R0, R4; add '0' to digit
			BRnzp PRINTS   ; jump to PRINTS
More_than	LD R4, A10     ; Load R4 with #55
		    ADD R0, R0, R4 ; add 'A'-10
PRINTS		OUT            ; prints
		
			ADD R1, R1, #-1; Decrement digit counter
			BRp Digit_Loop ; jump to Digit_Loop
			
			LD R0, NEWLINE ; R0 = 'new line'
			OUT			   ; Print a new line

			ADD R5, R5, #1 ; Increment R5 by 1
			LD R6, TS	   ; R6 = -27
			ADD R6, R5, R6 ; counter-27
			BRn BIN		   ; If not 27 loops, do anotha


DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
A_Fill		.FILL #48 ; decimal representation of ascii '0'
A10			.FILL #55 ; decimal repressentation of ascii 'A' - 10
SPACE		.FILL x20 ; hex value of ascii 'space'
CHAR		.FILL x40 ; hex value of ascii '@'
NEWLINE		.FILL x000A ; hex value of a new line
TS			.FILL #-27 ; -27

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
