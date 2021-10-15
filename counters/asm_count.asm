section .text

global count_prime_numbers

; param order: { rdi, rsi, rdx, rcx, r8, r9 }, r10, r11 <- volative

; extern int count_prime_numbers(int start, int stop, int* primes)
; rdi = int start
; rsi = int stop
; rdx = int* primes
count_prime_numbers:
    mov r12, 0   ; DEF r12 -> count = 0
    mov r10, 3   ; DEF r10 -> root = 3
    mov r13, rdx ; DEF r13 -> arr[]
    mov r15, rsi ; DEF r15 -> stop
    mov r9, rdi  ; DEF r9  -> n = start

    sub r9, 2  ; n -= 2 to offset initial increase
OUTER_LOOP_HEAD:
    add r9, 2  ; n += 2
    ; if (n >= stop) goto ENDING
    cmp r9, r15 ; n - stop
    jg ENDING

OUTER_LOOP_RESET:
    mov rax, r10 ; rax = root
    mul rax      ; rax = root * root

    cmp rax, r9  ; square - n
    jge NO_INCREMENT
    inc r10      ; root++
    jmp OUTER_LOOP_RESET

NO_INCREMENT:
    mov r11, 0  ; DEF r11 -> i = 0
INNER_LOOP_HEAD:
    inc r11 ; i++, starts at 1 intentionally

    ; if (arr[i] > root) found prime
    cmp [r13 + r11*4], r10d ; arr[i] - root
    jg FOUND_PRIME

    ; if (n % arr[i] == 0) break;
    mov rax, r9  ; rax = n
    xor rdx, rdx ; rdx = 0
    mov esi, [r13 + r11*4] ; rsi = arr[i]
    div rsi      ; rdx = n % arr[i]

    cmp rdx, 0   ; n % arr[i] - 0
    jz OUTER_LOOP_HEAD  ; not a prime
    jmp INNER_LOOP_HEAD ; could still be prime

FOUND_PRIME:
    inc r12
    jmp OUTER_LOOP_HEAD

ENDING:
    mov rax, r12
    ret