ASSUME CS:CODESG
CODESG SEGMENT
        MOV ax,2000H
        MOV ss,ax
        MOV sp,0
        ADD sp,10
        pop ax
        pop bx
        push ax
        push bx
        pop ax
        pop bx
        mov ax,0c00H
        int 21H
CODESG ENDS
        END
