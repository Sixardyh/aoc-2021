; Runs on 64-bit Linux, assembled with nasm
FILE_LINES      equ 1000
READ            equ 0
WRITE           equ 1
EXIT            equ 60
STDIN           equ 0
STDOUT          equ 1


SECTION .bss
line:           resb 13
counters:       resb 13


SECTION .text
global main
main:

        call    readLine               ; get input line by line
;        push    line

        ; xor     r8w, r8w                ; initialize r8w to 0
        ; mov     rcx, 12
        ; call    toBits                 ; construct the bits, char by char

        mov     rcx, 12
        call    countBits

        call    printLine
        mov     rax, EXIT
        mov     rdi, 0
        syscall

; reads a line from STDIN and puts in into line:
readLine:
        mov     rax, READ
        mov     rdi, STDIN
        mov     rsi, line
        mov     rdx, 13
        syscall
        ret

; convert the string into bits
; toBits:
;         and     r10w, 0b1111111111111110
;         cmp     [rsi], 0x30             ; rsi still points to line?
;         je      .leftshift
;         or      r10w, 0b0000000000000001
;
; .leftshift:
;         shl     r10w, 1
;         inc     rsi
;         dec     rcx
;         jnz     toBits

countBits:


printLine:
        mov     rax, WRITE
        mov     rdi, STDOUT
        mov     rsi, line
        mov     rdx, 1
        syscall
        ret

