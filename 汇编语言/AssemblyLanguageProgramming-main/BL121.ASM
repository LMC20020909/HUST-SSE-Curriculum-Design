assume cs:code
code segment
        mov ax,code
        mov ds,ax
        mov ax,0020H
        mov es,ax
        mov bx,0
S:      mov al,[bx]
        mov es:[bx], al
        inc bx
        loop S
        mov ax, 4c00h
        int 21h
code ends
        end
