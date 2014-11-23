section .text

global test_division_by_zero_exception
test_division_by_zero_exception:
    mov eax, 0
    mov edx, 0
    mov ebx, 0
    div ebx
    ret