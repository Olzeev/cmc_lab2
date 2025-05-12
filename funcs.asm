section .data
    ; коэффициенты в функциях
    c1 dd -2
    c2 dd 14
    c3 dd 2
    c4 dd 6

    buf dq 0


section .text
    global _f1, _f2, _f3, _derf1, _derf2, _derf3

    _f1:
        push ebp
        mov ebp, esp

        finit

        fld qword[ebp + 8]
        fldln2
        fxch                ; st(0) = x, st(1) = ln(2)
        fyl2x               ; st(1) * log_2(st(0))
                            ; ln(x) = log_2(x) / log_2(e) = log_2(x) * ln(2)
        
        leave
        ret

    _f2:
        push ebp
        mov ebp, esp

        finit

        fld qword[ebp + 8]
        fild dword[c1]      ; -2
        fmulp               ; -2x
        fild dword[c2]      ; 14
        faddp               ; -2x + 14

        leave
        ret
        
    _f3:
        push ebp
        mov ebp, esp

        finit

        fld qword[ebp + 8]
        fild dword[c3]      ; 2
        fsubrp              ; 2 - x

        fld1
        fdivrp              ; 1 / (2-x)

        fild dword[c4]      ; 6
        faddp               ; 1/(2-x) + 6

        leave
        ret

    _derf1:
        push ebp
        mov ebp, esp

        finit

        fld1
        fld qword[ebp + 8]
        fdivp               ; 1 / x

        leave
        ret

    _derf2:
        push ebp
        mov ebp, esp

        finit

        fild dword[c1]      ; -2

        leave
        ret

    _derf3:
        push ebp
        mov ebp, esp

        finit

        fld qword[ebp + 8]
        fild dword[c3]      ; 2
        fsubrp              ; 2 - x

        fst qword[buf]      ; buf = 2 - x
        fmul qword[buf]     ; (2-x)^2

        fld1
        fdivrp              ; 1 / (2-x)^2

        leave
        ret