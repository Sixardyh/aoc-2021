; Runs on 64-bit Linux, assembled with nasm
; TODO: don't fuck up EOF, print string instead of bytes, close file, part2
FILE_LINES      equ 98
FILE_SIZE       equ 10000
READ            equ 0
WRITE           equ 1
OPEN            equ 2
EXIT            equ 60
STDIN           equ 0
STDOUT          equ 1
O_RDONLY        equ 0

BRA_O             equ 40
CURL_O            equ 123
SQUARE_O          equ 91
TRI_O             equ 60
BRA_C             equ 41
CURL_C            equ 125
SQUARE_C          equ 93
TRI_C             equ 62

%macro PRINT 2
        mov     rax, WRITE
        mov     rdi, STDOUT
        mov     rsi, %1
        mov     rdx, %2
        syscall
%endmacro

SECTION .data
test:           db "test", 10
corr:           db "corr", 10
newl:           db "newl", 10
file_name:      db "input.txt", 0h


SECTION .bss
content:        resb FILE_SIZE
sum:            resb 8
str_output:     resb 2


SECTION .text
global _start
_start:

        call    loadFile               ; get input line by line

        mov     r10, content            ; buffer pointer
        mov     r8, FILE_LINES
        mov     rax, 0
        mov     [sum], rax

goThroughFile:
        xor     r11, r11                ; temp sum
        xor     r9, r9                  ; push counter
        call    goThroughLine
        add     [sum], r11
        dec     r8
        jnz     goThroughFile

; print output here
        PRINT   sum, 10

        mov     rax, EXIT
        mov     rdi, 0
        syscall

; open, read and close the file
loadFile:
        mov     rax, OPEN
        mov     rdi, file_name
        mov     rdx, O_RDONLY
        syscall

        mov     rdi, rax                ; load file descriptor
        mov     rax, READ
        mov     rdx, FILE_SIZE
        dec     rdx
        mov     rsi, content
        syscall
        ret

; main function tbh
goThroughLine:
        cmp     byte [r10], BRA_O
        je      .pushOpening
        cmp     byte [r10], CURL_O
        je      .pushOpening
        cmp     byte [r10], TRI_O
        je      .pushOpening
        cmp     byte [r10], SQUARE_O
        je      .pushOpening

.popClosing:
        dec     r9                       ; decrement counter
        cmp     byte [r10], BRA_C
        je      .isClosingBra
        cmp     byte [r10], CURL_C
        je      .isClosingCurl
        cmp     byte [r10], TRI_C
        je      .isClosingTri

.isClosingSquare:
        pop     rcx
        cmp     byte [rcx], SQUARE_O
        je      .end
        add     r11, 57
        jmp     .cleanCorrupted

.isClosingBra:
        pop     rcx
        cmp     byte [rcx], BRA_O
        je      .end
        add     r11, 3
        jmp     .cleanCorrupted

.isClosingCurl:
        pop     rcx
        cmp     byte [rcx], CURL_O
        je      .end
        add     r11, 1197
        jmp     .cleanCorrupted

.isClosingTri:
        pop     rcx
        cmp     byte [rcx], TRI_O
        je      .end
        add     r11, 25137

.cleanCorrupted:
        pop     rcx
        dec     r9
        jnz     .cleanCorrupted

.gotoNewline:
        inc     r10
        cmp     byte [r10], 0x0A
        jne     .gotoNewline
        dec     r10
        jmp     .end

.pushOpening:
        push    r10
        inc     r9                       ; increment push counter

.end:
        inc     r10
        mov     rax, 10
        cmp     byte [r10], 0x0A
        jne     goThroughLine
        inc     r10
        cmp     r9, 0
        jne     .cleanNotCorrupted
        ret

.cleanNotCorrupted:
        pop     rcx
        dec     r9
        jnz     .cleanNotCorrupted
        ret

