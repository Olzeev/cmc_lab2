section .data
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
        fldln2               ; ST(0) = ln(2), ST(1) = x
        fxch                 ; ST(0) = x, ST(1) = ln(2)
        fyl2x
        
        leave
        ret

    _f2:
        push ebp
        mov ebp, esp

        finit

        fld qword[ebp + 8]
        fild dword[c1]
        fmulp
        fild dword[c2]
        faddp

        leave
        ret
        
    _f3:
        push ebp
        mov ebp, esp

        finit

        fld qword[ebp + 8]
        fild dword[c3]
        fsubrp

        fld1
        fdivrp

        fild dword[c4]
        faddp

        leave
        ret

    _derf1:
        push ebp
        mov ebp, esp

        finit

        fld1
        fld qword[ebp + 8]
        fdivp

        leave
        ret

    _derf2:
        push ebp
        mov ebp, esp

        finit

        fild dword[c1]

        leave
        ret

    _derf3:
        push ebp
        mov ebp, esp

        finit

        fld qword[ebp + 8]
        fild dword[c3]
        fsubrp

        fst qword[buf]
        fmul qword[buf]

        fld1
        fdivrp

        leave
        ret