DATA SEGMENT
y DW 0
x DB 21 DUP ('$')
str_for_help0 db 'Hello', 16 dup ('$')
str_for_help1 db 'Hello', 16 dup ('$')
ret_msg db 'The return value is: ', '$'  ; The return message.
DATA ENDS 


SSEG SEGMENT STACK   ; Stack definition.
DW 100H DUP(?)
SSEG ENDS 


CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:SSEG
START: MOV AX, DATA
	MOV DS, AX
	MOV ES, AX 

	mov bx, 1
	push bx
	pop cx
	xor cx, 0ffffH
	add cx, 1
	push cx
	pop ax
	mov [y], ax
	lea si, str_for_help0
	lea di, x
	mov cx, 20
	cld   ; df = 0.
	rep movsb
	lea si, x
	push si
	lea si, str_for_help1
	pop di
	mov cx, 20
	cld   ; df = 0.
	repe cmpsb
	jne next0
	mov ax, 1
	jmp next1
next0:mov ax, 0
next1: push ax
	pop bx
	cmp bx, 0
	je next_block0
	mov dx, 100
	push dx
	pop cx
	mov [y], cx
next_block0: 

Return: mov ah, 09h    ; Prints the return message.
	lea dx, ret_msg
	int 21h
	mov ax, [y]
	mov bl, 10
	mov cx, 0
	cmp ax, 0
	jns Stack_Num
	neg ax
	push ax
	mov dl, '-'    ;     Print the minus.
	mov ah, 2
	int 21h
	pop ax

Stack_Num:     ; Enter the number into stack in digits
	div bl
	add ah, '0'    ; Make the digit as ascii digit.
	xor dx, dx
	mov dl, ah
	push dx
	and ax, 00ffh
	inc cx
	cmp al, 0
	jne Stack_Num

Print:  pop dx
	mov ah, 2
	int 21h
	loop Print

MOV AH, 4CH       ; End of code.
INT 21H
CODE ENDS
END START 


