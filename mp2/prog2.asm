;
;
;
.ORIG x3000
;This program is designed to emulate a stack postfix calculator.
;Push will push digit values into the stack and operators will pop and calculate.
;It takes an expression in postfix format and gives the answer in hex utilizing a 
;stack and printing hex algorithm we used last mp1. 
;Partners: ilashel2, gangulo2
;init registers
 
AND R0, R0, #0 ;
AND R1, R1, #0 ;
AND R2, R2, #0 ;
AND R3, R3, #0 ;
AND R4, R4, #0 ;
AND R5, R5, #0 ;
AND R6, R6, #0 ;
AND R7, R7, #0 ;


;Start of User input

NEW_CHAR GETC
OUT
JSR EVALUATE  ; Jump to start evaluating input

 



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

ST R0, PRI_SaveR0 ;
ST R1, PRI_SaveR1 ;
ST R2, PRI_SaveR2 ;
ST R3, PRI_SaveR3 ;
ST R4, PRI_SaveR4 ;


AND R1, R1, #0 ; Initialize digit counter
ADD R1, R1, #4 ; Send counter to 4
END_LOOP BRz END        ;
AND R0, R0, #0 ; Initialize digit
AND R2, R2, #0 ; Initialize Bit Counter
ADD R2, R2, #4 ; Set bit counter to 4
BIT_LOOP ADD R0, R0, R0 ; Left shift R3
ADD R3, R3, #0 ; Set CC
BRzp POS_LOOP   ; If postive then jump to positive loop
NEG_LOOP ADD R0, R0, #1 ; Add 1 to digit
POS_LOOP    ADD R0, R0, #0 ; Add 0 to digit
ADD R3, R3, R3 ; Left shift R3
ADD R2, R2, #-1; Decrement bit counter
BRp BIT_LOOP   ; Loop back to bit_loop
AND R4, R4, #0 ; Clear register
ADD R4, R0, #-9; Add -9 to digit
BRp MORE_THAN  ; Jump to more than
LD R4, ONE   ; Load 48 in register
ADD R0, R0, R4 ; Add 48 to R0
BRnzp PRINT    ; PRINT
MORE_THAN   LD R4, TWO   ; Load 55 in R4
ADD R0, R0, R4 ; Add 55 to R0
PRINT OUT            ; Outputs R0
ADD R1, R1, #-1; Decrement Counter
BRp END_LOOP   ;Loops to Beginning

LD R0, PRI_SaveR0 ;
LD R1, PRI_SaveR1 ;
LD R2, PRI_SaveR2 ;
LD R3, PRI_SaveR3 ;
LD R4, PRI_SaveR4 ;
END
HALT

PRI_SaveR0 .BLKW #1 ;
PRI_SaveR1 .BLKW #1 ;
PRI_SaveR2 .BLKW #1 ;
PRI_SaveR3 .BLKW #1 ;
PRI_SaveR4 .BLKW #1 ;

ONE .FILL #48 ;
TWO .FILL   #55 ;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE


AND R3, R0, #0 ; Initialize register
AND R4, R4, #0 ; init reg
AND R2, R2, #0 ; init reg



;OPERAND and operator checker



;space?

LD R1, SPACE    ;Load value for space
ADD R1, R0, R1  ; add the values
BRz NEW_CHAR ; if zero then loop back to user input

;OPERAND?

LD R1, NINE   ; load value for 9 in r1
ADD R1, R0, R1 ; add values
BRp OPPCHECK ; if zero then go to checker
LD R1, ZERO     ; load value for zero in r1
ADD R1, R0, R1 ; add values
BRn OPPCHECK ; if negative then jump to checker
LD R1, OFFSET ; offset r1 to get proper decimal
ADD R0, R0, R1  ; add r1 and r0
JSR PUSH ; pushes operand to stack
BRnzp NEW_CHAR  ; go back to user input
JSR OPPCHECK    ; jump to checker
BRnzp NEW_CHAR  ; go back to user input

OPPCHECK  
LD R1, EQUALS  ;Loads equal value in r1
ADD R1, R0, R1 ; adds values
BRz EQUAL   ; if zero then jump to equal

LD R1, OPPOMULT ; this checks for "*"
ADD R1, R0, R1 ;
BRz MULTIPLY    ;
LD R1, OPPOADD  ; checks for "+"
ADD R1, R0, R1  ;
BRz PLU         ;

LD R1, OPPOMINUS ;checks for "-"
ADD R1, R0, R1 ;
BRz MINU     ;

LD R1, OPPODIV ;checks for "/"
ADD R1, R0, R1 ;
BRz DIVI ;

LD R1, OPPOEXP ;checks for "^"
ADD R1, R0, R1 ;
BRz EXPO ;
BRnzp PRINT_I    ;jump to invalid prompt



EQUAL
LD R3, STACK_TOP   ; load stack top
LD R4, STACK_START ; load stack start
NOT R3, R3         ; invert r3
ADD R3, R3, #1   ; add 1 for twos compliment
ADD R4, R4, R3     ; add them together
ADD R4, R4, #-1    ; decrement r4
BRnp PRINT_I   ; JUMP TO INVALID
JSR POP   ; jump to pop routine
ADD R3, R0, #0 ; add output to r3
ADD R5, R0, #0 ; add output to r5
BRnzp PRINT_HEX     ; print answer to screen


MULTIPLY
JSR POP        ; pops r0
ADD R5, R5, #0 ;
BRp PRINT_I    ; CHECKS R5 FOR INVALID
ADD R4, R0, #0 ;
JSR POP        ; pops r0
ADD R5, R5, #0 ;
BRp PRINT_I    ; CHECKS R5 FOR INVALID
ADD R3, R0, #0 ;
JSR MUL   ; jump to multiplication routine
JSR PUSH       ; push to stack
BRnzp NEW_CHAR ; jump to user input

PLU
ST R7, SAVE_R7 ;save R7
JSR POP ;POP first time,
ADD R5, R5, #0
BRp PRINT_I ;and check underflow
ADD R4, R4, R0
JSR POP ;second pop and second underflow check
ADD R5, R5, #0
BRp PRINT_I ;jump to invalid prompt
ADD R3, R3, R0
JSR PLUS ;if it's valid, perform the plus step
JSR PUSH
BRnzp NEW_CHAR ;jump to user input

MINU
JSR POP        ; same as previous codes
ADD R5, R5, #0 ;
BRp PRINT_I    ; CHECKS R5 FOR INVALID

ADD R4, R0, #0 ;
JSR POP        ;
ADD R5, R5, #0 ;
BRp PRINT_I    ; CHECKS R5 FOR INVALID
ADD R3, R0, #0 ;
JSR MIN   ;
JSR PUSH       ;
BRnzp NEW_CHAR ;same as previous codes


DIVI
JSR POP        ; same as previous codes
ADD R5, R5, #0 ;
BRp PRINT_I    ; CHECKS R5 FOR INVALID
ADD R4, R0, #0 ;
JSR POP        ;
ADD R5, R5, #0 ;
BRp PRINT_I    ; CHECKS R5 FOR INVALID
ADD R3, R0, #0 ;
JSR DIV   ;
JSR PUSH       ;
BRnzp NEW_CHAR ; same as previous codes

EXPO
JSR POP        ; same as previous codes
ADD R5, R5, #0 ;
BRp PRINT_I    ; CHECKS R5 FOR INVALID
ADD R4, R0, #0 ;
JSR POP        ;
ADD R5, R5, #0 ;
BRp PRINT_I    ; CHECKS R5 FOR INVALID
ADD R3, R0, #0 ;
JSR EXP   ; Jump to EXP
EXP_FINISH JSR PUSH   ; shortcut to end of exponent expression
BRnzp NEW_CHAR ; jump to user input

;prompt for invalid
PRINT_I
LEA R0, WARNING
PUTS
HALT


;fills for operators
OPPOMUlT .FILL xFFD6
OPPOADD .FILL xFFD5
OPPOMINUS .FILL xFFD3
OPPODIV .FILL xFFD1
OPPOEXP .FILL xFFA2
SAVE_R7 .BLKW #1
WARNING .STRINGZ "INVALID EXPRESSION"
EQUALS .FILL #-61
SPACE .FILL #-32
NINE  .FILL #-57
ZERO .FILL #-48
OFFSET .FILL #-48


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS
;your code goes here

ST R3, PLUS_SaveR3 ;
ST R4, PLUS_SaveR4 ;

ADD R0, R3, R4 ; Adds inputs together and saves in r0

LD R3, PLUS_SaveR3 ;
LD R4, PLUS_SaveR4 ;

RET

PLUS_SaveR3 .BLKW #1
PLUS_SaveR4 .BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN
;your code goes here

ST R3, MIN_SaveR3 ;
ST R4, MIN_SaveR4 ;

NOT R4, R4     ; inverts r4
ADD R4, R4, #1 ; adds 1 for 2s complement
ADD R0, R3, R4 ;adds the inputs together

LD R3, MIN_SaveR3 ;
LD R4, MIN_SaveR4 ;

RET   ; return

MIN_SaveR3 .BLKW #1 ;
MIN_SaveR4 .BLKW #1 ;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL
;your code goes here

ST R3, MUL_SaveR3 ;
ST R4, MUL_SaveR4 ;

AND R0, R0, #0  ; initialize
ADD R4, R4, #0  ; setting cc  
BRz DONE    ; jump to done
MULTIP ADD R0, R0, R3  ;
ADD R4, R4, #-1 ; decrement counter
BRp MULTIP ; multiplication loop

DONE
LD R3, MUL_SaveR3 ;
LD R4, MUL_SaveR4 ;

RET ; return

MUL_SaveR3 .BLKW #1 ;
MUL_SaveR4 .BLKW #1 ;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
;your code goes here

ST R3, DIV_SaveR3 ;
ST R4, DIV_SaveR4 ;

AND R0, R0, #0 ; initialize
NOT R4, R4     ; invert
ADD R4, R4, #1 ; add 1 for 2s compliment
DIV_LOOP ADD R3, R3, R4 ; add values
BRn DIV_END    ; jump to end
ADD R0, R0, #1 ; increment
BRp DIV_LOOP   ;
DIV_END
LD R3, DIV_SaveR3 ;
LD R4, DIV_SaveR4 ;

RET ; return
 
DIV_SaveR3 .BLKW #1 ;
DIV_SaveR4 .BLKW #1 ;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here

ST R3, EXP_SaveR3 ;
ST R4, EXP_SaveR4 ;

AND R0, R0, #0
ADD R0, R0, #1 ;Set initial value of R0 to 1
AND R1, R1, #0
ADD R1, R1, R4 ;Move exponent value in R4 to R1
BRz COMPLETE
AND R4, R4, #0
ADD R4, R4, R3 ;Move base value R3 to R4
AND R3, R3, #0
ADD R3, R3, R0
JSR MUL ;R0 = R3 * R4
AND R3, R3, #0
ADD R3, R3, R0 ;Duplicate value in R0 to R3
ADD R1, R1, #-1
BRz COMPLETE ;If exponent counter counts to 0, exit EXP
BRnzp #-6 ;Go back to multiply steps


COMPLETE BRnzp EXP_FINISH

EXP_SaveR3 .BLKW #1 ;
EXP_SaveR4 .BLKW #1 ;


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
ST R3, PUSH_SaveR3 ;save R3
ST R4, PUSH_SaveR4 ;save R4
AND R5, R5, #0 ;
LD R3, STACK_END ;
LD R4, STACk_TOP ;
ADD R3, R3, #-1 ;
NOT R3, R3 ;
ADD R3, R3, #1 ;
ADD R3, R3, R4 ;
BRz OVERFLOW ;stack is full
STR R0, R4, #0 ;no overflow, store value in the stack
ADD R4, R4, #-1 ;move top of the stack
ST R4, STACK_TOP ;store top of stack pointer
BRnzp DONE_PUSH ;
OVERFLOW
ADD R5, R5, #1 ;
DONE_PUSH
LD R3, PUSH_SaveR3 ;
LD R4, PUSH_SaveR4 ;
RET


PUSH_SaveR3 .BLKW #1 ;
PUSH_SaveR4 .BLKW #1 ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
ST R3, POP_SaveR3 ;save R3
ST R4, POP_SaveR4 ;save R3
AND R5, R5, #0 ;clear R5
LD R3, STACK_START ;
LD R4, STACK_TOP ;
NOT R3, R3 ;
ADD R3, R3, #1 ;
ADD R3, R3, R4 ;
BRz UNDERFLOW ;
ADD R4, R4, #1 ;
LDR R0, R4, #0 ;
ST R4, STACK_TOP ;
BRnzp DONE_POP ;
UNDERFLOW
ADD R5, R5, #1 ;
DONE_POP
LD R3, POP_SaveR3 ;
LD R4, POP_SaveR4 ;
RET


POP_SaveR3 .BLKW #1 ;
POP_SaveR4 .BLKW #1 ;
STACK_END .FILL x3FF0 ;
STACK_START .FILL x4000 ;
STACK_TOP .FILL x4000 ;


.END
