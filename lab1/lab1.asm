.ORIG x3000
; write your code here

			AND R1, R1, #0; initialize digit counter
			ADD R1, R1, #4; set counter to 4
Digit_Loop	BRz DONE ; ends program
			AND R0, R0, #0; Clear digit/R0
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
			HALT ; 
A_Fill		.FILL #48
A10			.FILL #55
			
DONE		.END;
 
			
