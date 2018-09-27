section .text

string_length:
	mov rax, -1
	.loop:
		inc rax
		cmp byte[rdi + rax], 0
		jnz .loop
	ret

print_string:
	call string_length
	mov rdx, rax
	mov rsi, rdi
	mov rax, 1
	mov rdi, 1
	syscall
	ret

print_char:
	dec rsp
	mov [rsp], rdi
	mov rdi, 1
	mov rsi, rsp
	mov rax, 1
	syscall
	inc rsp
	ret

print_newline:
	mov rdi, 10
	call print_char
	ret

print_int:
	cmp rdi, 0
	jns print_uint
	xor rdi, -1
	inc rdi
	push rdi
	mov rdi, '-'
	call print_char
	pop rdi

print_uint:
	mov rax, rdi
	mov r8, 10
	times 11 push word 0	;?
	mov r9, rsp
	add rsp, 21
	mov byte [rsp], 0
	.loop:
		xor rdx, rdx	; rax = (rdx rax)/r8, rdx = res
	dec rsp
	div r8
	add rdx, '0'	; add 30 to make ascii code
	mov byte [rsp], dl
	test rax, rax
	jnz .loop
        mov rdi, rsp
        call print_string
        mov rsp, r9
        add rsp, 22			;?
        ret

string_equals:
        push rdi
        push rsi
        call string_length
        mov r8, rax
        pop rsi
        mov rdi, rsi
        push rsi
        call string_length
        mov rcx, rax
        pop r8
        pop rsi
        pop rdi
        xor rax, rax
        cmp r8, rcx
        jnz .exit
        test rcx, rcx
        jz .emptystring
        .loop:
        	dec rcx
		mov r9b, byte[rsi + rcx]
		cmp r9b, byte[rdi + rcx]
		jnz .exit
		test rcx, rcx
		jnz .loop
        .emptystring:
        	inc rax
        .exit:
        	ret

read_char:
        xor rax, rax
        push rax	; take place in stack with zero, not to override necessary data in stack, couse reads only in memory
        mov rdi, 0
        mov rsi, rsp
        mov rdx, 1
        syscall
        mov rax, [rsp]
        add rsp, 8
        ret

section .data
word_buffer times 256 db 0

section .text

read_word:
        push r8
        mov r8, word_buffer
        .skip:
		call read_char
		test rax, rax	;check if end
		jz .exit
		cmp rax, 32	;skip _ till first letter
		jle .skip
        .read:
		mov [r8], rax
		inc r8
		call read_char
		cmp rax, 32
		jg .read	;till space or lower !
        .exit:
		mov rdi, word_buffer
		call string_length
		mov rdx, rax
		mov rax, word_buffer
	pop r8
	ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
        xor rax, rax
        xor rdx, rdx
        
        ret

; rdi poins to a string
; returns rax: number, rdx : length
parse_int:
        xor rax, rax
        ret 


string_copy:
        ret
