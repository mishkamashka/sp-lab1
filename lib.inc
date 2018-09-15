section .text

string_length:
    xor rax, rax
    .loop:
        cmp byte [rdi+rax], 0
        je .end
        inc rax
        jmp .loop
    .end:
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

print_uint:
    xor rax, rax
    ret


print_int:
    xor rax, rax
    ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
    ret 

section .data
word_buffer times 256 db 0

section .text

read_word:
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret 


string_copy:
    ret
