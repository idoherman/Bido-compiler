DATA SEGMENT
x DW 0
y DW 0
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

	mov bx, 4
	push bx
	mov cx, 4
	push cx
	pop dx
	xor dx, 0ffffH
	add dx, 1
	push dx
	pop bx
	pop ax
	add ax, bx
	push ax
	pop ax
	mov [x], ax
	mov ax, [x]
	push ax
	mov bx, 4
	push bx
	pop dx
	pop cx
	cmp cx, dx
	je next0
	mov cx, 0
	jmp next1
next0: mov cx, 1
next1: push cx
	pop ax
	cmp ax, 0
	je next_block0
	mov cx, [x]
	push cx
	pop dx
	xor dx, 0ffffH
	add dx, 1
	push dx
	pop bx
	mov [y], bx
	jmp next_block1
next_block0: 
	mov bx, 4
	push bx
	pop ax
	mov [x], ax
next_block1: 

Return: mov ah, 09h    ; Prints the return message.
	lea dx, ret_msg
	int 21h
	mov ax, [x]
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


