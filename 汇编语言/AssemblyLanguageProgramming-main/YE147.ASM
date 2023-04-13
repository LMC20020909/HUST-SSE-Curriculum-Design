.386
DATA SEGMENT USE16
N		DW		0			;读入的总数据数
NUM		DW      0			;前六位是1的数据的个数
ISOK	DW      0			;GETHI函数返回值之一，当前的数是否为前六位是1的数，是为1，否为0
READ	DW		0			;GETNUM函数返回值之一，若成功返回读入的数
READOK	DW		0			;GETNUM函数返回值之一，若成功返回1，否为0
REXP	DW		1			;GETNUM函数所需中间变量，10的累乘器
OKNUM	DW		10 DUP(0)	;记录前六位是1的数据
BUF		DB		64			;读入缓冲区
		DB		0
		DB		64 DUP(0)
OUT1	DB		'This program is used to test whether the first six bits in the binary sense of N positive numbers(0 <= x <= 65535) are 1', 0DH, 0AH, 'Please input N(0 <= N <= 10)', 0DH, 0AH, '$'
OUT2	DB		'Input WORNG!!!', 0DH, 0AH, '$'
OUT3	DB		'We calculate this kind of number,we get $'
OUT4	DB		'N is too big!! ', 0DH, 0AH, '$'
OUT5	DB		'Plead input $'
OUT6	DB		' numbers!', 0DH, 0AH, '$'
CRLF	DB		0DH, 0AH, '$'
OUTNUM	DB		0			;传递要输出的数据
DATA ENDS

STACK SEGMENT USE16 STACK
        DW      100 DUP(0)
STACK ENDS

CODE SEGMENT USE16
        ASSUME DS:DATA, CS:CODE, SS:STACK
START:  MOV AX, DATA
		MOV DS, AX
		MOV AX, STACK
		MOV SS, AX
		LEA DX, OUT1		;输出提示信息1
		MOV AH, 9
		INT 21H
LOOPC:	CALL GETNUM			;循环读入总数据数，直到读入成功
		CMP WORD PTR READOK, 1H
		JNE LOOPC
		CMP WORD PTR READ, 10
		JA	OVER
		JMP NOVER
OVER:	LEA DX, OUT4
		MOV AH, 9
		INT 21H
		JMP LOOPC
NOVER:	MOV AX, WORD PTR READ;保存总数据量
		MOV N, AX
		MOV CX, AX
		MOV BX, 0
		LEA DX, OUT5		;输出提示信息
		MOV AH, 9
		INT 21H
		MOV AX, WORD PTR N
		MOV WORD PTR OUTNUM, AX
		CALL OUTPUT
		LEA DX, OUT6
		MOV AH, 9
		INT 21H
LOOPF:	CMP CX, 0			;循环读入,判断N次
		JE LOOPFND			;CX = 0循环结束，进行输出	
LOOPG:	CALL GETNUM			;循环读入当前需判断的数，直到读入成功
		CMP WORD PTR READOK, 1H
		JNE LOOPG
		PUSH WORD PTR READ	;利用栈传递参数
		CALL TESTHI			;调用函数检测前六位是否为1
		CMP WORD PTR ISOK, 1
		JNE NOTOK
		INC WORD PTR NUM
		MOV AX, WORD PTR READ
		MOV WORD PTR OKNUM[BX], AX;保存此符合条件的数
		ADD BX, 2
NOTOK:	DEC CX
		JMP LOOPF
LOOPFND:LEA DX, OUT3		;输出提示信息3
		MOV AH, 9
		INT 21H
		MOV AX, WORD PTR NUM;输出符合条件的数的总数
		MOV WORD PTR OUTNUM, AX
		CALL OUTPUT
		LEA DX, CRLF		;输出换行
		MOV AH, 9
		INT 21H
		MOV CX, WORD PTR NUM;循环输出符合条件的数
		MOV BX, 0
LOOPH:	CMP CX, 0
		JE	LOOPHND
		MOV AX, WORD PTR OKNUM[BX];输出符合条件的数
		MOV WORD PTR OUTNUM, AX
		CALL OUTPUT
		LEA DX, CRLF		;输出换行
		MOV AH, 9
		INT 21H
		ADD BX, 2
		DEC CX
		JMP LOOPH
LOOPHND:MOV AH, 4CH			;程序结束
        INT 21H
		
GETNUM PROC					;本函数用于输入一个十进制数，保存至READ中，若成功READOK为1，否则置0
		PUSHA				;保存信息
		PUSHF
		MOV WORD PTR READ, 0H;初始化
		MOV WORD PTR REXP, 1H
		MOV WORD PTR READOK, 1H
		LEA DX, BUF			;输入一个字符串
		MOV AH, 10
		INT 21H
		LEA DX, CRLF		;输出换行
		MOV AH, 9
		INT 21H
		MOV BL, BUF+1		;将字符串长度保存于BX
		MOV BH, 0
		CMP BX, 0			;判断字符串是否为空
		JE	GETWR
		MOV CX, BX
		DEC BX
LOOPB:	MOV AL, BYTE PTR BUF[BX+2];得到字符串最尾端的字符，注意加2！！！
		MOV AH, 0			;注意AH赋值0！！！
		DEC BX
		CMP AX, 30H			;判断字符是否合法
		JS	GETWR
		CMP AX, 39H			;判断字符是否合法
		JA GETWR
		SUB AX, 30H
		MUL WORD PTR REXP	;AX与累乘器相乘，保存至AX
		JC	GETWR			;检查输入是否超出范围
		ADD WORD PTR READ, AX;READ加上这个值
		JC	GETWR			;检查输入是否超出范围
		MOV AX, 10			;累乘器乘10
		MUL WORD PTR REXP
		MOV WORD PTR REXP, AX
		LOOP LOOPB
		JMP ENDGET
GETWR:	LEA DX, OUT2		;输出提示信息2
		MOV AH, 9
		INT 21H
		MOV WORD PTR READOK, 0H
ENDGET:	POPF
		POPA
		RET
GETNUM ENDP

TESTHI PROC					;本函数用于判断一个数是否前六位为1，传递的参数保存至栈中，结果保存于ISOK中，若是ISOK为1，否则置0
        PUSH BP				;保存信息
        MOV BP, SP
        PUSHA				;保存信息
        PUSHF
        MOV AX, 4[BP]		;得到传递的参数
        MOV CX, 6			;循环6次
        MOV WORD PTR ISOK, 0H
LOOPA:  SHL AX, 1
        JNC BITWR			;判断进位标识符是否为1，若不是1则本数不符合前六位均是1的要求
        LOOP LOOPA
        MOV WORD PTR ISOK, 1H
BITWR:  POPF
        POPA
        POP BP
        RET 4
TESTHI ENDP

OUTPUT PROC					;本函数用于将一个数按照10进制位输出，输出的数为字OUTNUM，使用栈倒序输出
		PUSHA				;保存信息
		PUSHF
		MOV AX, WORD PTR OUTNUM
		MOV BX, 10
		XOR CX, CX			;清零
LOOPI:	XOR DX, DX
		DIV BX				;AX除10除数保存至AX，余数保存至DX
		OR 	DX, 0E30H		;转换为ASCII码并将15号调用放入AL
		PUSH DX				;DX压栈保存输出			
		INC CX				;计数
		CMP AX, 0			;循环纸质AX为0
		JNZ LOOPI
LOOPJ:	POP AX
		INT 10H
		LOOP LOOPJ
		POPF
		POPA
		RET
OUTPUT ENDP
CODE ENDS
        END START
