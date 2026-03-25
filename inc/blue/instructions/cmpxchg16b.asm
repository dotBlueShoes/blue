OPTION PROLOGUE:NONE
OPTION EPILOGUE:NONE

PUBLIC x_cmpxchg16b
PUBLIC atomic_cmpxchg16b
PUBLIC x_cmpxchg16b_zf
PUBLIC atomic_cmpxchg16b_zf

.CODE


x_cmpxchg16b PROC
    push rbx

    ; Store pointer addresses 
    mov  r9, RCX ; b[0] & b[1]
    mov r10, RDX ; a[0] & a[1]

    mov rcx, QWORD PTR [ r9 + 8] ; b-1
    mov rbx, QWORD PTR [ r9]     ; b-0           
    mov rdx, QWORD PTR [r10 + 8] ; a-1
    mov rax, QWORD PTR [r10]     ; a-0

    cmpxchg16b QWORD PTR [r8]

    ; Make the value under pointer equar to rdx/rax. ;
    mov QWORD PTR [r10 + 8], rdx
    mov QWORD PTR [r10], rax

    pop rbx

    ret
x_cmpxchg16b ENDP


; atomic because only shared memory touched is [r8]
atomic_cmpxchg16b PROC
    push rbx

    ; Store pointer addresses 
    mov  r9, rcx ; b[0] & b[1]
    mov r10, rdx ; a[0] & a[1]

    mov rcx, QWORD PTR [ r9 + 8] ; b-1
    mov rbx, QWORD PTR [ r9]     ; b-0           
    mov rdx, QWORD PTR [r10 + 8] ; a-1
    mov rax, QWORD PTR [r10]     ; a-0

    lock cmpxchg16b QWORD PTR [r8]

    ; Make the value under pointer equar to rdx/rax. ;
    mov QWORD PTR [r10 + 8], rdx
    mov QWORD PTR [r10], rax

    pop rbx

    ret
atomic_cmpxchg16b ENDP


x_cmpxchg16b_zf PROC
    push rbx

    ; Store pointer addresses 
    mov  r9, RCX ; b[0] & b[1]
    mov r10, RDX ; a[0] & a[1]

    mov rcx, QWORD PTR [ r9 + 8] ; b-1
    mov rbx, QWORD PTR [ r9]     ; b-0           
    mov rdx, QWORD PTR [r10 + 8] ; a-1
    mov rax, QWORD PTR [r10]     ; a-0

    cmpxchg16b QWORD PTR [r8]

    ; Make the value under pointer equar to rdx/rax. ;
    mov QWORD PTR [r10 + 8], rdx
    mov QWORD PTR [r10], rax

    pop rbx

    setz al
    movzx rax, al

    ret
x_cmpxchg16b_zf ENDP


; atomic because only shared memory touched is [r8]
atomic_cmpxchg16b_zf PROC
    push rbx

    ; Store pointer addresses 
    mov  r9, rcx ; b[0] & b[1]
    mov r10, rdx ; a[0] & a[1]

    mov rcx, QWORD PTR [ r9 + 8] ; b-1
    mov rbx, QWORD PTR [ r9]     ; b-0           
    mov rdx, QWORD PTR [r10 + 8] ; a-1
    mov rax, QWORD PTR [r10]     ; a-0

    lock cmpxchg16b QWORD PTR [r8]

    ; Make the value under pointer equar to rdx/rax. ;
    mov QWORD PTR [r10 + 8], rdx
    mov QWORD PTR [r10], rax

    pop rbx

    setz al
    movzx rax, al

    ret
atomic_cmpxchg16b_zf ENDP


;  8 bytes -> return address
; 32 bytes -> shadow_space
; 40 bytes -> 5th arg

; 1. OUT variable passing working
; example1 ; x_cmpxchg16b PROC
; example1 ;     mov rax, [rsp + 40]
; example1 ;     mov qword ptr [rax], 20
; example1 ;     mov qword ptr [rax + 8], 20
; example1 ;     ret
; example1 ; x_cmpxchg16b ENDP

; 2. OUT variable returning working
; example2 ; x_cmpxchg16b PROC
; example2 ;     mov rcx, 22 ; b-1
; example2 ;     mov rdx, 1  ; a-1
; example2 ;     mov rbx, 22 ; b-0
; example2 ;     mov rax, 10 ; a-0
; example2 ; 
; example2 ;     mov r10, [rsp + 40]
; example2 ;     cmpxchg16b QWORD PTR [r10]
; example2 ; 
; example2 ;     ret
; example2 ; x_cmpxchg16b ENDP

; 3. reference passing
; example3 ; x_cmpxchg16b PROC
; example3 ;     mov rcx, QWORD PTR [rcx] ; b-1
; example3 ;     mov rdx, QWORD PTR [rdx] ; a-1
; example3 ; 
; example3 ;     mov rbx, QWORD PTR [r8] ; b-0
; example3 ;     mov rax, QWORD PTR [r9] ; a-0
; example3 ; 
; example3 ;     mov r10, [rsp + 40]
; example3 ;     cmpxchg16b QWORD PTR [r10]
; example3 ; 
; example3 ;     ret
; example3 ; x_cmpxchg16b ENDP

; 4. Done well but not actually thead-safe because each value in array can change during mov'es.
; example4 ; x_cmpxchg16b PROC
; example4 ;     push rbx ; Non-volatile registers, and because we're pushing onto stack +8 offset.
; example4 ; 
; example4 ;     mov rcx, QWORD PTR [rcx] ; b-1
; example4 ;     mov rbx, QWORD PTR [r8]  ; b-0
; example4 ; 
; example4 ;     ; Reuse r8 register as pointer-information because we need rdx register. ;
; example4 ;     mov r8, rdx              
; example4 ; 
; example4 ;     mov rdx, QWORD PTR [rdx] ; a-1
; example4 ;     mov rax, QWORD PTR [r9]  ; a-0
; example4 ; 
; example4 ;     mov r10, [rsp + 40 + 8]
; example4 ;     lock cmpxchg16b QWORD PTR [r10]
; example4 ; 
; example4 ;     ; Make the value under pointer equar to rdx/rax. ;
; example4 ;     mov QWORD PTR [r8], rdx
; example4 ;     mov QWORD PTR [r9], rax
; example4 ; 
; example4 ;     pop rbx
; example4 ; 
; example4 ;     ret
; example4 ; x_cmpxchg16b ENDP


END