.386
DATA SEGMENT USE16
A       DW      M
BUF     DB      'AB',0DH, 0AH
M       DB      2 DUP(1), 2 DUP(2 DUP(2), 'B')
DATA ENDS

STACK SEGMENT USE16 STACK
        DW      100 DUP(0)
STACK ENDS

CODE SEGMENT USE16
        ASSUME DS:DATA, SS:STACK, CS: CODE
START:  MOV AX, DATA
        MOV DS, AX
        MOV AX, STACK
        MOV SS, AX
        MOV AL, 40H + 70H
        MOV AX, 1 LT 2
        MOV AL, A
        MOV DX, BUF
        MOV AL, M
        MOV BUF, AL
        MOV AH, 4CH
        INT 21
CODE ENDS
        END START
