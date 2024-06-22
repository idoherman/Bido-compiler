DATA SEGMENT
letter DW '$'
check DW 0
result DW 0
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

	mov bx, 'a'
	push bx
	pop ax
	mov [letter], ax
	mov dx, 1
	push dx
	pop cx
	mov [check], cx
	mov bx, 0
	push bx
	pop ax
	mov [result], ax
	mov cx, [letter]
	push cx
	mov dx, 'a'
	push dx
	pop bx
	pop ax
	cmp ax, bx
	je next0
	mov ax, 0
	jmp next1
next0: mov ax, 1
next1: push ax
	mov cx, [check]
	push cx
	pop ax
	pop dx
	cmp dx, 0
	je next2
	cmp ax, 0
	je next2
	mov dx, 1
jmp next3 
next2: mov dx, 0
next3: push dx
	mov bx, 0
	push bx
	mov cx, 0
	push cx
	pop ax
	pop dx
	cmp dx, ax
	je next4
	mov dx, 0
	jmp next5
next4: mov dx, 1
next5: push dx
	pop cx
	pop bx
	cmp bx, 0
	je next6
	cmp cx, 0
	je next6
	mov bx, 1
jmp next7 
next6: mov bx, 0
next7: push bx
	pop dx
	cmp dx, 0
	je next_block0
	mov bx, 1
	push bx
	pop ax
	mov [result], ax
next_block0: 

Return: mov ah, 09h    ; Prints the return message.
	lea dx, ret_msg
	int 21h
	mov ax, [result]
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


