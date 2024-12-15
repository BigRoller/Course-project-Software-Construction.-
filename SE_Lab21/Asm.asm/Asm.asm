.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
SetConsoleOutputCP PROTO : DWORD
SetConsoleCP PROTO : DWORD
includelib "C:\Users\glora\Desktop\Лабы КПО\SE_Lab21\SE_Lab21\Debug\Standart_lib.lib"
ExitProcess PROTO : DWORD
GLOBAL_fi_1 PROTO  : SDWORD,  : SDWORD
GLOBAL_fs_1 PROTO  : DWORD,  : DWORD
extern __substr : PROC
extern __strlen : PROC
extern __writeline : PROC
extern __write : PROC
extern __writeint : PROC
extern __stoi : PROC

.stack 4096
.const
ZERO_DIVISION BYTE "zero division", 0
TYPE_OVERFLOW BYTE "type overflow", 0
l1 SDWORD 2
l2 SDWORD 3
l3 SDWORD 111
l4 SDWORD 's'
l5 SDWORD -18
l6 SDWORD 26
l7 BYTE "очень длинная строка, которая правильно обрабатывается", 0
l8 BYTE "1234567890", 0
l9 SDWORD 0
l10 SDWORD 7
l11 SDWORD 1
l12 BYTE "привет", 0
l13 BYTE " ", 0
l14 BYTE "-123", 0
l15 SDWORD 0

.data
fi_z_2 SDWORD 0
fs_c_2 BYTE 256 dup(0)
main_y_2 SDWORD 0
main_z_2 SDWORD 0
main_a_2 SDWORD 0
main_b_2 SDWORD 0
main_x_2 SDWORD 0
main_c_2 SDWORD 0
main_sa_2 BYTE 256 dup(0)
main_sb_2 BYTE 256 dup(0)
main_sc_2 BYTE 256 dup(0)

.code
ERROR_ZERO_DIVISION:
push OFFSET ZERO_DIVISION
call __writeline
push -1
call ExitProcess
ERROR_TYPE_OVERFLOW:
push OFFSET TYPE_OVERFLOW
call __writeline
push -1
call ExitProcess

GLOBAL_fi_1 PROC fi_x_1_parm : SDWORD, fi_y_1_parm : SDWORD
push fi_y_1_parm
mov eax, fi_y_1_parm
push fi_x_1_parm
mov eax, fi_x_1_parm
pop eax
pop ebx
add eax, ebx
push eax
push fi_x_1_parm
mov eax, fi_x_1_parm
pop eax
pop ebx
imul eax, ebx
push eax
cmp eax, 2147483647
jg ERROR_TYPE_OVERFLOW
cmp eax, -2147483648
 jl ERROR_TYPE_OVERFLOW
pop fi_z_2 
push fi_z_2
mov eax, fi_z_2
mov eax, fi_z_2
ret
GLOBAL_fi_1 ENDP

GLOBAL_fs_1 PROC fs_a_1_parm : DWORD, fs_b_1_parm : DWORD
push l2
mov eax, l2
push l1
mov eax, l1
push fs_a_1_parm
mov eax, fs_a_1_parm
call __substr 
push eax
pop esi
mov edi, offset fs_c_2
copy_loop0:
mov al, [esi]
mov[edi], al
inc esi
inc edi
cmp al, 0
jne copy_loop0
push OFFSET fs_c_2 
mov eax, OFFSET fs_c_2
ret
GLOBAL_fs_1 ENDP

main PROC
push 1251d
call SetConsoleOutputCP
push 1251d
call SetConsoleCP
push l3
mov eax, l3
cmp eax, 2147483647
jg ERROR_TYPE_OVERFLOW
cmp eax, -2147483648
 jl ERROR_TYPE_OVERFLOW
pop main_a_2 
push main_a_2
mov eax, main_a_2
pop eax
neg eax
 push eax
cmp eax, 2147483647
jg ERROR_TYPE_OVERFLOW
cmp eax, -2147483648
 jl ERROR_TYPE_OVERFLOW
pop main_c_2 
push l5
mov eax, l5
push l4
mov eax, l4
pop eax
pop ebx
add eax, ebx
push eax
cmp eax, 2147483647
jg ERROR_TYPE_OVERFLOW
cmp eax, -2147483648
 jl ERROR_TYPE_OVERFLOW
pop main_y_2 
push l6
mov eax, l6
cmp eax, 256
jg ERROR_TYPE_OVERFLOW
cmp eax, 0
jl ERROR_TYPE_OVERFLOW
pop main_x_2 
push OFFSET l7 
pop esi
mov edi, offset main_sa_2
copy_loop1:
mov al, [esi]
mov[edi], al
inc esi
inc edi
cmp al, 0
jne copy_loop1
push OFFSET l8 
pop esi
mov edi, offset main_sb_2
copy_loop2:
mov al, [esi]
mov[edi], al
inc esi
inc edi
cmp al, 0
jne copy_loop2
push main_a_2
mov eax, main_a_2
push main_y_2
mov eax, main_y_2
call GLOBAL_fi_1 
push eax
cmp eax, 2147483647
jg ERROR_TYPE_OVERFLOW
cmp eax, -2147483648
 jl ERROR_TYPE_OVERFLOW
pop main_z_2 
push OFFSET main_sa_2 
push OFFSET main_sb_2 
call GLOBAL_fs_1 
push eax
pop esi
mov edi, offset main_sc_2
copy_loop3:
mov al, [esi]
mov[edi], al
inc esi
inc edi
cmp al, 0
jne copy_loop3
push l9
mov eax, l9
cmp eax, 256
jg ERROR_TYPE_OVERFLOW
cmp eax, 0
jl ERROR_TYPE_OVERFLOW
pop main_x_2 
push l10
mov eax, l10
push main_x_2
mov eax, main_x_2
pop eax
pop ebx
cmp eax, ebx
jb FLAG0
jae FOR_END0
FLAG0:
push OFFSET l12 
call __writeline
push l11
mov eax, l11
push main_x_2
mov eax, main_x_2
pop eax
pop ebx
add eax, ebx
push eax
cmp eax, 256
jg ERROR_TYPE_OVERFLOW
cmp eax, 0
jl ERROR_TYPE_OVERFLOW
pop main_x_2 
push l10
mov eax, l10
push main_x_2
mov eax, main_x_2
pop eax
pop ebx
cmp eax, ebx
jb FLAG0
jae FOR_END0
FOR_END0:
push OFFSET main_sc_2 
call __write
push OFFSET main_sc_2 
call __strlen 
push eax
call __writeint
push OFFSET l13 
call __writeline
push OFFSET l14 
call __stoi 
push eax
call __writeint
push l15
mov eax, l15
mov eax, l15
call ExitProcess
main ENDP
end main
