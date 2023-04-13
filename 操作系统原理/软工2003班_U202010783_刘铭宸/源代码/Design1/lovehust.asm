; ==========================================
; hustmrsu.asm
; ���뷽����nasm hustmrsu.asm -o hustmrsu.com
; ʵ�ֹ��ܣ�ʹ�ö�ҳʽ��ַӳ�䣬���HUST��MRSU����任
; ==========================================

%include	"pm.inc"	; ����, ��, �Լ�һЩ˵��

PageDirBase0		equ	200000h	; ҳĿ¼��ʼ��ַ:	2M
PageTblBase0		equ	201000h	; ҳ��ʼ��ַ:		2M +  4K
PageDirBase1		equ	210000h	; ҳĿ¼��ʼ��ַ:	2M + 64K
PageTblBase1		equ	211000h	; ҳ��ʼ��ַ:		2M + 64K + 4K

LinearAddrDemo	equ	00401000h
ProcTask1		equ	00401000h
ProcTask2		equ	00501000h

ProcPagingDemo	equ	00301000h

org	0100h
jmp	LABEL_BEGIN

[SECTION .gdt]
; GDT
;                                         �λ�ַ,       �ν���     , ����
LABEL_GDT:			Descriptor	       0,                 0, 0				; ��������
LABEL_DESC_NORMAL:	Descriptor	       0,            0ffffh, DA_DRW			; Normal ������
LABEL_DESC_FLAT_C:	Descriptor         0,           0fffffh, DA_CR | DA_32 | DA_LIMIT_4K; 0 ~ 4G
LABEL_DESC_FLAT_RW:	Descriptor         0,           0fffffh, DA_DRW | DA_LIMIT_4K	; 0 ~ 4G
LABEL_DESC_CODE32:	Descriptor	       0,  SegCode32Len - 1, DA_CR | DA_32	; ��һ�´����, 32
LABEL_DESC_CODE16:	Descriptor	       0,            0ffffh, DA_C			; ��һ�´����, 16
LABEL_DESC_DATA:	Descriptor	       0,		DataLen - 1, DA_DRW				; Data
LABEL_DESC_STACK:	Descriptor	       0,        TopOfStack, DA_DRWA | DA_32; Stack, 32 λ
LABEL_DESC_STACK1:	Descriptor	       0,       TopOfStack1, DA_DRWA | DA_32; Stack1, 32 λ
LABEL_DESC_LDT1:	Descriptor	       0,       LDT1Len - 1, DA_LDT			; LDT1
LABEL_DESC_TSS1:	Descriptor	       0,       TSSLen1 - 1, DA_386TSS		; TSS1
LABEL_DESC_STACK2:	Descriptor	       0,       TopOfStack2, DA_DRWA | DA_32; Stack2, 32 λ
LABEL_DESC_LDT2:	Descriptor	       0,       LDT2Len - 1, DA_LDT			; LDT2
LABEL_DESC_TSS2:	Descriptor	       0,       TSSLen2 - 1, DA_386TSS		; TSS2
LABEL_DESC_VIDEO:	Descriptor	 0B8000h,            0ffffh, DA_DRW			; �Դ��׵�ַ
; GDT ����

GdtLen		equ	$ - LABEL_GDT	; GDT����
GdtPtr		dw	GdtLen - 1		; GDT����
			dd	0				; GDT����ַ

; GDT ѡ����
SelectorNormal		equ	LABEL_DESC_NORMAL	- LABEL_GDT
SelectorFlatC		equ	LABEL_DESC_FLAT_C	- LABEL_GDT
SelectorFlatRW		equ	LABEL_DESC_FLAT_RW	- LABEL_GDT
SelectorCode32		equ	LABEL_DESC_CODE32	- LABEL_GDT
SelectorCode16		equ	LABEL_DESC_CODE16	- LABEL_GDT
SelectorData		equ	LABEL_DESC_DATA		- LABEL_GDT
SelectorStack		equ	LABEL_DESC_STACK	- LABEL_GDT
SelectorStack1		equ	LABEL_DESC_STACK1	- LABEL_GDT
SelectorLDT1		equ LABEL_DESC_LDT1		- LABEL_GDT
SelectorTSS1		equ LABEL_DESC_TSS1		- LABEL_GDT
SelectorStack2		equ	LABEL_DESC_STACK2	- LABEL_GDT
SelectorLDT2		equ LABEL_DESC_LDT1		- LABEL_GDT
SelectorTSS2		equ LABEL_DESC_TSS2		- LABEL_GDT
SelectorVideo		equ	LABEL_DESC_VIDEO	- LABEL_GDT
; END of [SECTION .gdt]

[SECTION .data1]	 ; ���ݶ�
ALIGN	32
[BITS	32]
LABEL_DATA:
; ʵģʽ��ʹ����Щ����
; �ַ���
_szPMMessage:		db	"In Protect Mode now. ^-^", 0Ah, 0Ah, 0	; ���뱣��ģʽ����ʾ���ַ���
_szMemChkTitle:		db	"BaseAddrL BaseAddrH LengthLow LengthHigh   Type", 0Ah, 0	; ���뱣��ģʽ����ʾ���ַ���
_szRAMSize:			db	"RAM size:", 0
_szReturn:			db	0Ah, 0
; ����
_wSPValueInRealMode:dw	0
_dwMCRNumber:		dd	0	; Memory Check Result
_dwDispPos:			dd	(80 * 6 + 0) * 2	; ��Ļ�� 6 ��, �� 0 �С�
_dwMemSize:			dd	0
_ARDStruct:			; Address Range Descriptor Structure
_dwBaseAddrLow:		dd	0
_dwBaseAddrHigh:	dd	0
_dwLengthLow:		dd	0
_dwLengthHigh:		dd	0
_dwType:			dd	0
_PageTableNumber:	dd	0
_SavedIDTR:			dd	0	; ���ڱ��� IDTR
					dd	0
_SavedIMREG:		db	0	; �ж����μĴ���ֵ
_MemChkBuf:	times	256	db	0
_inwhatcode:		dw	1

; ����ģʽ��ʹ����Щ����
szPMMessage		equ	_szPMMessage	- $$
szMemChkTitle	equ	_szMemChkTitle	- $$
szRAMSize		equ	_szRAMSize	- $$
szReturn		equ	_szReturn	- $$
dwDispPos		equ	_dwDispPos	- $$
dwMemSize		equ	_dwMemSize	- $$
dwMCRNumber		equ	_dwMCRNumber	- $$
ARDStruct		equ	_ARDStruct	- $$
dwBaseAddrLow	equ	_dwBaseAddrLow	- $$
dwBaseAddrHigh	equ	_dwBaseAddrHigh	- $$
dwLengthLow		equ	_dwLengthLow	- $$
dwLengthHigh	equ	_dwLengthHigh	- $$
dwType			equ	_dwType		- $$
MemChkBuf		equ	_MemChkBuf	- $$
PageTableNumber	equ	_PageTableNumber- $$
SavedIDTR		equ	_SavedIDTR	- $$
SavedIMREG		equ	_SavedIMREG	- $$
inwhatcode		equ _inwhatcode - $$
DataLen			equ	$ - LABEL_DATA
; END of [SECTION .data1]


; ȫ�ֶ�ջ��
[SECTION .gs]
ALIGN	32
[BITS	32]
LABEL_STACK:
	times 512 db 0

TopOfStack	equ	$ - LABEL_STACK - 1

; END of [SECTION .gs]

[SECTION .gs1]
ALIGN	32
[BITS	32]
LABEL_STACK1:
	times 512 db 0

TopOfStack1	equ	$ - LABEL_STACK1 - 1

; END of [SECTION .gs1]

[SECTION .gs2]
ALIGN	32
[BITS	32]
LABEL_STACK2:
	times 512 db 0

TopOfStack2	equ	$ - LABEL_STACK2 - 1

; END of [SECTION .gs2]

; TSS1 ---------------------------------------------------------------------------------------------
;��ʼ������״̬��ջ��(TSS1)
[SECTION .tss1]         ;��ø��εĴ�С
ALIGN	32              ;align��һ�������ݶ���ĺꡣͨ��align�Ķ�����1��4��8�ȡ������align 32��û������ģ���Ϊ��������ֻ��32b�ĵ�ַ���߿�ȡ�
[BITS	32]             ;32λģʽ�Ļ�������
LABEL_TSS1:              ;����LABEL_TSS
		DD	0			; Back
		DD	TopOfStack1	; 0 ����ջ   //�ڲ�ring0����ջ����TSS��
		DD	SelectorStack1; 
		DD	0			; 1 ����ջ
		DD	0			; 
		DD	0			; 2 ����ջ
		DD	0			;               //TSS�����ֻ�ܷ���Ring2����ջ��ring3����ջ����Ҫ����
		DD	PageDirBase0; CR3
		DD	0			; EIP
		DD	0			; EFLAGS
		DD	0			; EAX
		DD	0			; ECX
		DD	0			; EDX
		DD	0			; EBX
		DD	Stack1Len	; ESP
		DD	0			; EBP
		DD	0			; ESI
		DD	0			; EDI
		DD	0			; ES
		DD	SelectorLDT1Task			; CS
		DD	SelectorLDT1Stack			; SS
		DD	0			; DS
		DD	0			; FS
		DD	SelectorVideo			; GS
		DD	SelectorLDT1; LDT
		DW	0			; ���������־
		DW	$ - LABEL_TSS1 + 2	; I/Oλͼ��ַ
		DB	0ffh			; I/Oλͼ������־
TSSLen1		equ	$ - LABEL_TSS1   ;��öεĴ�С
; TSS1 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

; TSS2 ---------------------------------------------------------------------------------------------
;��ʼ������״̬��ջ��(TSS2)
[SECTION .tss2]         ;��ø��εĴ�С
ALIGN	32              ;align��һ�������ݶ���ĺꡣͨ��align�Ķ�����1��4��8�ȡ������align 32��û������ģ���Ϊ��������ֻ��32b�ĵ�ַ���߿�ȡ�
[BITS	32]             ;32λģʽ�Ļ�������
LABEL_TSS2:              ;����LABEL_TSS
		DD	0			; Back
		DD	TopOfStack2	; 0 ����ջ   //�ڲ�ring0����ջ����TSS��
		DD	SelectorStack2		; 
		DD	0			; 1 ����ջ
		DD	0			; 
		DD	0			; 2 ����ջ
		DD	0			;               //TSS�����ֻ�ܷ���Ring2����ջ��ring3����ջ����Ҫ����
		DD	PageDirBase1; CR3
		DD	0			; EIP
		DD	0			; EFLAGS
		DD	0			; EAX
		DD	0			; ECX
		DD	0			; EDX
		DD	0			; EBX
		DD	Stack2Len			; ESP
		DD	0			; EBP
		DD	0			; ESI
		DD	0			; EDI
		DD	0			; ES
		DD	SelectorLDT2Task			; CS
		DD	SelectorLDT2Stack			; SS
		DD	0			; DS
		DD	0			; FS
		DD	SelectorVideo			; GS
		DD	SelectorLDT2; LDT
		DW	0			; ���������־
		DW	$ - LABEL_TSS2 + 2	; I/Oλͼ��ַ
		DB	0ffh			; I/Oλͼ������־
TSSLen2		equ	$ - LABEL_TSS2   ;��öεĴ�С
; TSS2 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


; IDT
[SECTION .idt]
ALIGN	32
[BITS	32]
LABEL_IDT:
; ��                                Ŀ��ѡ����,            ƫ��, DCount, ����
%rep 32
			Gate	SelectorCode32, SpuriousHandler,      0, DA_386IGate
%endrep
.020h:		Gate	SelectorCode32,    ClockHandler,      0, DA_386IGate
%rep 95
			Gate	SelectorCode32, SpuriousHandler,      0, DA_386IGate
%endrep
.080h:		Gate	SelectorCode32,  UserIntHandler,      0, DA_386IGate

IdtLen		equ	$ - LABEL_IDT
IdtPtr		dw	IdtLen - 1	; �ν���
			dd	0		; ����ַ
; END of [SECTION .idt]

[SECTION .s16]
[BITS	16]
LABEL_BEGIN:
	mov	ax, cs
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	sp, 0100h

	mov	[LABEL_GO_BACK_TO_REAL+3], ax
	mov	[_wSPValueInRealMode], sp

	; �õ��ڴ���
	mov	ebx, 0
	mov	di, _MemChkBuf
.loop:
	mov	eax, 0E820h
	mov	ecx, 20
	mov	edx, 0534D4150h
	int	15h
	jc	LABEL_MEM_CHK_FAIL
	add	di, 20
	inc	dword [_dwMCRNumber]
	cmp	ebx, 0
	jne	.loop
	jmp	LABEL_MEM_CHK_OK
LABEL_MEM_CHK_FAIL:
	mov	dword [_dwMCRNumber], 0
LABEL_MEM_CHK_OK:

	; ��ʼ�� 16 λ�����������
	mov	ax, cs
	movzx	eax, ax
	shl	eax, 4
	add	eax, LABEL_SEG_CODE16
	mov	word [LABEL_DESC_CODE16 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_CODE16 + 4], al
	mov	byte [LABEL_DESC_CODE16 + 7], ah

	; ��ʼ�� 32 λ�����������
	xor	eax, eax
	mov	ax, cs
	shl	eax, 4
	add	eax, LABEL_SEG_CODE32
	mov	word [LABEL_DESC_CODE32 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_CODE32 + 4], al
	mov	byte [LABEL_DESC_CODE32 + 7], ah

	; ��ʼ�����ݶ�������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_DATA
	mov	word [LABEL_DESC_DATA + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_DATA + 4], al
	mov	byte [LABEL_DESC_DATA + 7], ah

	; ��ʼ����ջ��������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_STACK
	mov	word [LABEL_DESC_STACK + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_STACK + 4], al
	mov	byte [LABEL_DESC_STACK + 7], ah

	; ��ʼ����ջ��������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_STACK1
	mov	word [LABEL_DESC_STACK1 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_STACK1 + 4], al
	mov	byte [LABEL_DESC_STACK1 + 7], ah

	; ��ʼ����ջ��������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_STACK2
	mov	word [LABEL_DESC_STACK2 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_STACK2 + 4], al
	mov	byte [LABEL_DESC_STACK2 + 7], ah


	; ��ʼ�� LDT1 �� GDT �е�������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_LDT1
	mov	word [LABEL_DESC_LDT1 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_LDT1 + 4], al
	mov	byte [LABEL_DESC_LDT1 + 7], ah

	; ��ʼ�� LDT2 �� GDT �е�������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_LDT2
	mov	word [LABEL_DESC_LDT2 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_LDT2 + 4], al
	mov	byte [LABEL_DESC_LDT2 + 7], ah

	; ��ʼ�� TSS1 ������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_TSS1
	mov	word [LABEL_DESC_TSS1 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_TSS1 + 4], al
	mov	byte [LABEL_DESC_TSS1 + 7], ah


	; ��ʼ�� TSS2 ������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_TSS2
	mov	word [LABEL_DESC_TSS2 + 2], ax
	shr	eax, 16
	mov	byte [LABEL_DESC_TSS2 + 4], al
	mov	byte [LABEL_DESC_TSS2 + 7], ah

	; ��ʼ�� LDT1 �е�������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_Task1
	mov	word [LABEL_LDT1_DESC_TASK + 2], ax
	shr	eax, 16
	mov	byte [LABEL_LDT1_DESC_TASK + 4], al
	mov	byte [LABEL_LDT1_DESC_TASK + 7], ah

	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_Data1
	mov	word [LABEL_LDT1_DESC_DATA + 2], ax
	shr	eax, 16
	mov	byte [LABEL_LDT1_DESC_DATA + 4], al
	mov	byte [LABEL_LDT1_DESC_DATA + 7], ah

	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, Local_LABEL_STACK1
	mov	word [LABEL_LDT1_DESC_STACK + 2], ax
	shr	eax, 16
	mov	byte [LABEL_LDT1_DESC_STACK + 4], al
	mov	byte [LABEL_LDT1_DESC_STACK + 7], ah


	; ��ʼ�� LDT2 �е�������
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_Task2
	mov	word [LABEL_LDT2_DESC_TASK + 2], ax
	shr	eax, 16
	mov	byte [LABEL_LDT2_DESC_TASK + 4], al
	mov	byte [LABEL_LDT2_DESC_TASK + 7], ah

	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_Data2
	mov	word [LABEL_LDT2_DESC_DATA + 2], ax
	shr	eax, 16
	mov	byte [LABEL_LDT2_DESC_DATA + 4], al
	mov	byte [LABEL_LDT2_DESC_DATA + 7], ah

	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, Local_LABEL_STACK2
	mov	word [LABEL_LDT2_DESC_STACK + 2], ax
	shr	eax, 16
	mov	byte [LABEL_LDT2_DESC_STACK + 4], al
	mov	byte [LABEL_LDT2_DESC_STACK + 7], ah

	; Ϊ���� GDTR ��׼��
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_GDT		; eax <- gdt ����ַ
	mov	dword [GdtPtr + 2], eax	; [GdtPtr + 2] <- gdt ����ַ

	; Ϊ���� IDTR ��׼��
	xor	eax, eax
	mov	ax, ds
	shl	eax, 4
	add	eax, LABEL_IDT		; eax <- idt ����ַ
	mov	dword [IdtPtr + 2], eax	; [IdtPtr + 2] <- idt ����ַ

	; ���� IDTR
	sidt	[_SavedIDTR]

	; �����ж����μĴ���(IMREG)ֵ
	in	al, 21h
	mov	[_SavedIMREG], al

	; ���� GDTR
	lgdt	[GdtPtr]

	; ���ж�
	; cli

	; ���� IDTR
	lidt	[IdtPtr]

	; �򿪵�ַ��A20
	in	al, 92h
	or	al, 00000010b
	out	92h, al

	; ׼���л�������ģʽ
	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax

	; �������뱣��ģʽ
	jmp	dword SelectorCode32:0	; ִ����һ���� SelectorCode32 װ�� cs, ����ת�� Code32Selector:0  ��

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LABEL_REAL_ENTRY:		; �ӱ���ģʽ���ص�ʵģʽ�͵�������
	mov	ax, cs
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	sp, [_wSPValueInRealMode]

	lidt	[_SavedIDTR]	; �ָ� IDTR ��ԭֵ

	mov	al, [_SavedIMREG]	; ���ָ��ж����μĴ���(IMREG)��ԭֵ
	out	21h, al				; ��

	in	al, 92h			; ��
	and	al, 11111101b	; �� �ر� A20 ��ַ��
	out	92h, al			; ��

	sti			; ���ж�

	mov	ax, 4c00h	; ��
	int	21h			; ���ص� DOS
; END of [SECTION .s16]


[SECTION .s32]; 32 λ�����. ��ʵģʽ����.
[BITS	32]

LABEL_SEG_CODE32:
	mov	ax, SelectorData
	mov	ds, ax			; ���ݶ�ѡ����
	mov	es, ax
	mov	ax, SelectorVideo
	mov	gs, ax			; ��Ƶ��ѡ����

	mov	ax, SelectorStack
	mov	ss, ax			; ��ջ��ѡ����

	mov	esp, TopOfStack

	call	Init8259A

	; ������ʾһ���ַ���
	push	szPMMessage
	call	DispStr
	add	esp, 4

	push	szMemChkTitle
	call	DispStr
	add	esp, 4

	call	DispMemSize		; ��ʾ�ڴ���Ϣ

	call	PagingDemo		; ��ʾ�ı�ҳĿ¼��Ч��

	;sti
	;jmp $

	;jmp		SelectorTSS1:0
	
	mov 	ax, SelectorLDT1
	lldt 	ax
	jmp 	SelectorLDT1Task:0

	call	SetRealmode8259A

	; ����ֹͣ
	jmp	SelectorCode16:0


; Init8259A ---------------------------------------------------------------------------------------------
Init8259A:
	mov	al, 011h
	out	020h, al	; ��8259, ICW1.
	call	io_delay

	out	0A0h, al	; ��8259, ICW1.
	call	io_delay

	mov	al, 020h	; IRQ0 ��Ӧ�ж����� 0x20
	out	021h, al	; ��8259, ICW2.
	call	io_delay

	mov	al, 028h	; IRQ8 ��Ӧ�ж����� 0x28
	out	0A1h, al	; ��8259, ICW2.
	call	io_delay

	mov	al, 004h	; IR2 ��Ӧ��8259
	out	021h, al	; ��8259, ICW3.
	call	io_delay

	mov	al, 002h	; ��Ӧ��8259�� IR2
	out	0A1h, al	; ��8259, ICW3.
	call	io_delay

	mov	al, 001h
	out	021h, al	; ��8259, ICW4.
	call	io_delay

	out	0A1h, al	; ��8259, ICW4.
	call	io_delay

	mov	al, 11111110b	; ����������ʱ���ж�
	out	021h, al	; ��8259, OCW1.
	call	io_delay

	mov	al, 11111111b	; ���δ�8259�����ж�
	out	0A1h, al	; ��8259, OCW1.
	call	io_delay

	ret
; Init8259A ---------------------------------------------------------------------------------------------


; SetRealmode8259A ---------------------------------------------------------------------------------------------
SetRealmode8259A:
	mov	ax, SelectorData
	mov	fs, ax

	mov	al, 017h
	out	020h, al	; ��8259, ICW1.
	call	io_delay

	mov	al, 008h	; IRQ0 ��Ӧ�ж����� 0x8
	out	021h, al	; ��8259, ICW2.
	call	io_delay

	mov	al, 001h
	out	021h, al	; ��8259, ICW4.
	call	io_delay

	mov	al, [fs:SavedIMREG]	; ���ָ��ж����μĴ���(IMREG)��ԭֵ
	out	021h, al			; ��
	call	io_delay

	ret
; SetRealmode8259A ---------------------------------------------------------------------------------------------

io_delay:
	nop
	nop
	nop
	nop
	ret

; int handler ---------------------------------------------------------------
_ClockHandler:
ClockHandler	equ	_ClockHandler - $$
	mov	al, 20h
	out	20h, al				; ���� EOI
	;iretd

	mov ax, SelectorData
	mov ds, ax

	mov ax, word [inwhatcode]
	cmp ax, 1
	je	jumptotss2
	mov ax, 1
	mov word [inwhatcode], ax
	jmp SelectorTSS1:0
	jmp endclockhandle
jumptotss2:	
	mov ax, 2
	mov word [inwhatcode], ax
	jmp SelectorTSS2:0
endclockhandle:
	iretd

_UserIntHandler:
UserIntHandler	equ	_UserIntHandler - $$
	mov	ah, 0Ch				; 0000: �ڵ�    1100: ����
	mov	al, 'I'
	mov	[gs:((80 * 0 + 80) * 2)], ax	; ��Ļ�� 0 ��, �� 70 �С�
	iretd

_SpuriousHandler:
SpuriousHandler	equ	_SpuriousHandler - $$
	mov	ah, 0Ch				; 0000: �ڵ�    1100: ����
	mov	al, '!'
	mov	[gs:((80 * 0 + 70) * 2)], ax	; ��Ļ�� 0 ��, �� 75 �С�
	jmp	$
	iretd
; ---------------------------------------------------------------------------

; ������ҳ���� --------------------------------------------------------------
SetupPaging:
	; �����ڴ��С����Ӧ��ʼ������PDE�Լ�����ҳ��
	xor	edx, edx
	mov	eax, [dwMemSize]
	mov	ebx, 400000h	; 400000h = 4M = 4096 * 1024, һ��ҳ���Ӧ���ڴ��С
	div	ebx
	mov	ecx, eax	; ��ʱ ecx Ϊҳ��ĸ�����Ҳ�� PDE Ӧ�õĸ���
	test	edx, edx
	jz	.no_remainder
	inc	ecx		; ���������Ϊ 0 ��������һ��ҳ��
.no_remainder:
	mov	[PageTableNumber], ecx	; �ݴ�ҳ�����

	; Ϊ�򻯴���, �������Ե�ַ��Ӧ��ȵ������ַ. ���Ҳ������ڴ�ն�.

	; ���ȳ�ʼ��ҳĿ¼
	mov	ax, SelectorFlatRW
	mov	es, ax
	mov	edi, PageDirBase0	; �˶��׵�ַΪ PageDirBase0
	xor	eax, eax
	mov	eax, PageTblBase0 | PG_P  | PG_USU | PG_RWW
.1:
	stosd
	add	eax, 4096		; Ϊ�˼�, ����ҳ�����ڴ�����������.
	loop	.1

	; �ٳ�ʼ������ҳ��
	mov	eax, [PageTableNumber]	; ҳ�����
	mov	ebx, 1024		; ÿ��ҳ�� 1024 �� PTE
	mul	ebx
	mov	ecx, eax		; PTE���� = ҳ����� * 1024
	mov	edi, PageTblBase0	; �˶��׵�ַΪ PageTblBase0
	xor	eax, eax
	mov	eax, PG_P  | PG_USU | PG_RWW
.2:
	stosd
	add	eax, 4096		; ÿһҳָ�� 4K �Ŀռ�
	loop	.2

	mov	eax, PageDirBase0
	mov	cr3, eax
	mov	eax, cr0
	or	eax, 80000000h
	mov	cr0, eax
	jmp	short .3
.3:
	nop

; ��ʼ��ҳĿ¼
	mov	ax, SelectorFlatRW
	mov	es, ax
	mov	edi, PageDirBase1	; �˶��׵�ַΪ PageDirBase1
	xor	eax, eax
	mov	eax, PageTblBase1 | PG_P  | PG_USU | PG_RWW
	mov	ecx, [PageTableNumber]
.4:
	stosd
	add	eax, 4096		; Ϊ�˼�, ����ҳ�����ڴ�����������.
	loop	.4

	; �ٳ�ʼ������ҳ��
	mov	eax, [PageTableNumber]	; ҳ�����
	mov	ebx, 1024		; ÿ��ҳ�� 1024 �� PTE
	mul	ebx
	mov	ecx, eax		; PTE���� = ҳ����� * 1024
	mov	edi, PageTblBase1	; �˶��׵�ַΪ PageTblBase1
	xor	eax, eax
	mov	eax, PG_P  | PG_USU | PG_RWW
.5:
	stosd
	add	eax, 4096		; ÿһҳָ�� 4K �Ŀռ�
	loop	.5

	; �ڴ˼����ڴ��Ǵ��� 8M ��
	mov	eax, LinearAddrDemo
	shr	eax, 22
	mov	ebx, 4096
	mul	ebx
	mov	ecx, eax
	mov	eax, LinearAddrDemo
	shr	eax, 12
	and	eax, 03FFh	; 1111111111b (10 bits)
	mov	ebx, 4
	mul	ebx
	add	eax, ecx
	add	eax, PageTblBase1
	mov	dword [es:eax], ProcTask2 | PG_P | PG_USU | PG_RWW

	mov	eax, PageDirBase1
	mov	cr3, eax
	jmp	short .6
.6:
	nop

	ret
; ��ҳ����������� ----------------------------------------------------------

; ���Է�ҳ���� --------------------------------------------------------------
PagingDemo:
	mov	ax, cs
	mov	ds, ax
	mov	ax, SelectorFlatRW
	mov	es, ax

	push	LenTask1
	push	OffsetTask1
	push	ProcTask1
	call	MemCpy
	add	esp, 12

	push	LenTask2
	push	OffsetTask2
	push	ProcTask2
	call	MemCpy
	add	esp, 12

	push	LenPagingDemoAll
	push	OffsetPagingDemoProc
	push	ProcPagingDemo
	call	MemCpy
	add	esp, 12

	mov	ax, SelectorData
	mov	ds, ax			; ���ݶ�ѡ����
	mov	es, ax

	call	SetupPaging		; ������ҳ

	ret
; ---------------------------------------------------------------------------


; PagingDemoProc ------------------------------------------------------------
PagingDemoProc:
OffsetPagingDemoProc	equ	PagingDemoProc - $$
	mov		eax, LinearAddrDemo
	call	eax
	retf
; ---------------------------------------------------------------------------
LenPagingDemoAll	equ	$ - PagingDemoProc
; ---------------------------------------------------------------------------


; task1 -----------------------------------------------------------------------
task1:
OffsetTask1	equ	task1 - $$
looptask1:
	mov	ah, 0Ch			; 0000: �ڵ�    1100: ����
	mov	al, 'H'
	mov	[gs:((80 * 17 + 0) * 2)], ax	; ��Ļ�� 17 ��, �� 0 �С�
	mov	al, 'U'
	mov	[gs:((80 * 17 + 1) * 2)], ax	; ��Ļ�� 17 ��, �� 1 �С�
	mov	al, 'S'
	mov	[gs:((80 * 17 + 2) * 2)], ax	; ��Ļ�� 17 ��, �� 2 �С�
	mov	al, 'T'
	mov	[gs:((80 * 17 + 3) * 2)], ax	; ��Ļ�� 17 ��, �� 3 �С�
	jmp looptask1
	ret
LenTask1	equ	$ - task1
; ---------------------------------------------------------------------------


; task2 -----------------------------------------------------------------------
task2:
OffsetTask2	equ	task2 - $$
looptask2:
	mov	ah, 0Fh			; 0000: �ڵ�    1111: ����
	mov	al, 'L'
	mov	[gs:((80 * 17 + 0) * 2)], ax	; ��Ļ�� 17 ��, �� 0 �С�
	mov	al, 'O'
	mov	[gs:((80 * 17 + 1) * 2)], ax	; ��Ļ�� 17 ��, �� 1 �С�
	mov	al, 'V'
	mov	[gs:((80 * 17 + 2) * 2)], ax	; ��Ļ�� 17 ��, �� 2 �С�
	mov	al, 'E'
	mov	[gs:((80 * 17 + 3) * 2)], ax	; ��Ļ�� 17 ��, �� 3 �С�
	jmp looptask2
	ret
LenTask2	equ	$ - task2
; ---------------------------------------------------------------------------


; ��ʾ�ڴ���Ϣ --------------------------------------------------------------
DispMemSize:
	push	esi
	push	edi
	push	ecx

	mov	esi, MemChkBuf
	mov	ecx, [dwMCRNumber]	;for(int i=0;i<[MCRNumber];i++) // ÿ�εõ�һ��ARDS(Address Range Descriptor Structure)�ṹ
.loop:					;{
	mov	edx, 5			;	for(int j=0;j<5;j++)	// ÿ�εõ�һ��ARDS�еĳ�Ա����5����Ա
	mov	edi, ARDStruct		;	{			// ������ʾ��BaseAddrLow��BaseAddrHigh��LengthLow��LengthHigh��Type
.1:					;
	push	dword [esi]		;
	call	DispInt			;		DispInt(MemChkBuf[j*4]); // ��ʾһ����Ա
	pop	eax			;
	stosd				;		ARDStruct[j*4] = MemChkBuf[j*4];
	add	esi, 4			;
	dec	edx			;
	cmp	edx, 0			;
	jnz	.1			;	}
	call	DispReturn		;	printf("\n");
	cmp	dword [dwType], 1	;	if(Type == AddressRangeMemory) // AddressRangeMemory : 1, AddressRangeReserved : 2
	jne	.2			;	{
	mov	eax, [dwBaseAddrLow]	;
	add	eax, [dwLengthLow]	;
	cmp	eax, [dwMemSize]	;		if(BaseAddrLow + LengthLow > MemSize)
	jb	.2			;
	mov	[dwMemSize], eax	;			MemSize = BaseAddrLow + LengthLow;
.2:					;	}
	loop	.loop			;}
					;
	call	DispReturn		;printf("\n");
	push	szRAMSize		;
	call	DispStr			;printf("RAM size:");
	add	esp, 4			;
					;
	push	dword [dwMemSize]	;
	call	DispInt			;DispInt(MemSize);
	add	esp, 4			;

	pop	ecx
	pop	edi
	pop	esi
	ret
; ---------------------------------------------------------------------------

%include	"lib.inc"	; �⺯��

SegCode32Len	equ	$ - LABEL_SEG_CODE32
; END of [SECTION .s32]


; 16 λ�����. �� 32 λ���������, ������ʵģʽ
[SECTION .s16code]
ALIGN	32
[BITS	16]
LABEL_SEG_CODE16:
	; ����ʵģʽ:
	mov	ax, SelectorNormal
	mov	ds, ax
	mov	es, ax
	mov	fs, ax
	mov	gs, ax
	mov	ss, ax

	mov	eax, cr0
	and	al, 11111110b
	mov	cr0, eax

LABEL_GO_BACK_TO_REAL:
	jmp	0:LABEL_REAL_ENTRY	; �ε�ַ���ڳ���ʼ�������ó���ȷ��ֵ

Code16Len	equ	$ - LABEL_SEG_CODE16

; END of [SECTION .s16code]

; LDT1
[SECTION .ldt1]
ALIGN	32
LABEL_LDT1:
;                                         �λ�ַ       �ν���     ,   ����
LABEL_LDT1_DESC_TASK:	Descriptor	       0,     Task1Len - 1,   DA_C + DA_32	; Code, 32 λ
LABEL_LDT1_DESC_DATA:	Descriptor	       0,     Data1Len - 1,   DA_DRW		; Data, 32 λ
LABEL_LDT1_DESC_STACK:	Descriptor	       0,  	 	 Stack1Len,   DA_DRW + DA_32; Stack, 32 λ
LDT1Len		equ	$ - LABEL_LDT1

; LDT ѡ����
SelectorLDT1Task	equ	LABEL_LDT1_DESC_TASK - LABEL_LDT1 + SA_TIL
SelectorLDT1Data	equ	LABEL_LDT1_DESC_DATA - LABEL_LDT1 + SA_TIL
SelectorLDT1Stack	equ	LABEL_LDT1_DESC_STACK - LABEL_LDT1 + SA_TIL
; END of [SECTION .ldt]

; Task1 (LDT, 32 λ�����)
[SECTION .la1]
ALIGN	32
[BITS	32]
LABEL_Task1:
	sti
	mov  ax, SelectorVideo
	mov  gs, ax
	call SelectorFlatC:ProcPagingDemo
	jmp	LABEL_Task1
Task1Len	equ	$ - LABEL_Task1
; END of [SECTION .la1]

; Data1
[SECTION .da1]
ALIGN	32
[BITS	32]
LABEL_Data1:
Data1Len	equ $ - LABEL_Data1
; END of [SECTION .da1]

[SECTION .sa1]
ALIGN	32
[BITS	32]
Local_LABEL_STACK1:
	times 512 db 0
Stack1Len	equ	$ - Local_LABEL_STACK1 - 1
; END of [SECTION .sa1]



; LDT2
[SECTION .ldt2]
ALIGN	32
LABEL_LDT2:
;                                         �λ�ַ       �ν���     ,   ����
LABEL_LDT2_DESC_TASK:	Descriptor	       0,     Task2Len - 1,   DA_C + DA_32	; Code, 32 λ
LABEL_LDT2_DESC_DATA:	Descriptor	       0,     Data2Len - 1,   DA_DRW		; Data, 32 λ
LABEL_LDT2_DESC_STACK:	Descriptor	       0,  	 	 Stack2Len,   DA_DRW + DA_32; Stack, 32 λ
LDT2Len		equ	$ - LABEL_LDT2

; LDT ѡ����
SelectorLDT2Task	equ	LABEL_LDT2_DESC_TASK - LABEL_LDT2 + SA_TIL
SelectorLDT2Data	equ	LABEL_LDT2_DESC_DATA - LABEL_LDT2 + SA_TIL
SelectorLDT2Stack	equ	LABEL_LDT2_DESC_STACK - LABEL_LDT2 + SA_TIL
; END of [SECTION .ldt2]

; Task2 (LDT, 32 λ�����)
[SECTION .la2]
ALIGN	32
[BITS	32]
LABEL_Task2:
	sti
	mov  ax, SelectorVideo
	mov  gs, ax
	call SelectorFlatC:ProcPagingDemo
	jmp	LABEL_Task2
Task2Len	equ	$ - LABEL_Task2
; END of [SECTION .la2]

; Data2
[SECTION .da2]
ALIGN	32
[BITS	32]
LABEL_Data2:
Data2Len	equ $ - LABEL_Data2
; END of [SECTION .da2]

[SECTION .sa2]
ALIGN	32
[BITS	32]
Local_LABEL_STACK2:
	times 512 db 0
Stack2Len	equ	$ - Local_LABEL_STACK2 - 1
; END of [SECTION .sa2]
