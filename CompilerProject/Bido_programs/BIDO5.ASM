DATA SEGMENT
x DW 0
check_int DW 0
check_bool DW 0
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

	mov bx, 0
	push bx
	pop ax
	mov [x], ax
	mov dx, 1
	push dx
	pop cx
	mov [check_int], cx
	mov bx, 1
	push bx
	pop ax
	mov [check_bool], ax
	mov cx, [check_int]
	push cx
	mov dx, [check_bool]
	push dx
	pop bx
	pop ax
	cmp ax, bx
	je next0
	mov ax, 0
	jmp next1
next0: mov ax, 1
next1: push ax
	pop cx
	cmp cx, 0
	je next_block0
	mov ax, 1
	push ax
	pop dx
	mov [x], dx
next_block0: 

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


