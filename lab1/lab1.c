#include <stdio.h>
#include <limits.h>
#include <math.h>


short int answerAsm(const short int x, const char y, const char z) {
    short int v = 0;

    __asm {
        mov al, z;                  переместить в al z
        cbw;                        расширить z до слова
        add ax, 2;                  прибавить к z 2
        imul x;                     умножить(z + 2) на x
        mov bx, ax;                 переместить младшее слово z в bx
        mov cx, dx;                 переместить старшее слово z в cx
        mov al, y;                  переместить в al y
        cbw;                        расширить y до слова
        mov dx, 5;                  переместить 5 в dx
        imul dx;                    умножить y на 5

        sub ax, bx;                 вычесть из младшего слова 5y младшее слово (z + 2)x
        sbb dx, cx;                 вычесть из старшего слова y старшее слово (z + 2)x

        mov bx, ax;                 переместить младшее слово 5y - (z + 2)x в bx

        ;                           вычисление знаменателя
        mov al, z;                  переместить в al z
        cbw;                        расширить z до слова
        dec ax;                     вычесть из z 1
        
        xchg ax, bx;                поменять местами ax и bx
        
        idiv bx;                    разделить 5y - (z + 2)x на (z - 1)

        inc ax;                     прибавить к слову (5y - (z + 2)x) / (z - 1)  1

        mov v, ax;                  перместить в v (5y - (z + 2)x) / (z - 1) + 1
    };

    return v;
}

short int answerC(const short int x, const char y, const char z) {
    return (5 * y - (z + 2) * x) / (z - 1) + 1;
}


int main() {
    short int x;
    short int v;
    char y;
    char z;
    short int vAsm;
    short int vC;

    int flag = 1;


    printf("\t\tTest results\n");

    x = -0x1; y = 0x3; z = 0x2; v = 0x14;
    printf("\tx = %x, y = %x, z = %x, v = %x \n", x, y, z, v);
    vC = answerC(x, y, z);
    printf("C result:\t\t%d\tor\t%x (base 16)\n", vC, vC);
    vAsm = answerAsm(x, y, z);
    printf("Assembler result:\t%d\tor\t%x (base 16)\n\n", vAsm, vAsm);

    x = -0x2F3; y = 0x5B; z = 0x7F; v = 0x309;
    printf("\tx = %x, y = %x, z = %x, v = %x \n", x, y, z, v);
    vC = answerC(x, y, z);
    printf("C result:\t\t%d\tor\t%x (base 16)\n", vC, vC);
    vAsm = answerAsm(x, y, z);
    printf("Assembler result:\t%d\tor\t%x (base 16)\n\n", vAsm, vAsm);

    printf("Enter 0 to finish: ");
    scanf_s("%d", &flag);

    while(flag) {
        int i;

        while(1) {
            printf("Enter x: ");
            scanf_s("%x", &i);
            if(abs(i) <= SHRT_MAX) {
                x = (short)i;
                break;
            } else {
                printf("Value out of range! Try again\n\n");
            }
        }

        while(1) {
            printf("Enter y: ");
            scanf_s("%x", &i);
            if(abs(i) <= CHAR_MAX) {
                y = (char)i;
                break;
            } else {
                printf("Value out of range! Try again\n\n");
            }
        }

        while(1) {
            printf("Enter z: ");
            scanf_s("%x", &i);
            if(abs(i) <= CHAR_MAX && i != 0x1) {
                z = (char)i;
                break;
            } else {
                printf("Value out of range or equals to 1 (division by zero)! Try again\n\n");
            }
        }

        while(1) {
            printf("Enter v: ");
            scanf_s("%x", &i);
            if(abs(i) <= SHRT_MAX) {
                v = (short)i;
                break;
            } else {
                printf("Value out of range! Try again\n\n");
            }
        }

        if(flag) {
            vC = answerC(x, y, z);
            printf("C result:\t\t%d\tor\t%x (base 16)\n", vC, vC);
            vAsm = answerAsm(x, y, z);
            printf("Assembler result:\t%d\tor\t%x (base 16)\n\n", vAsm, vAsm);
        }

        printf("Enter 0 to finish: ");
        scanf_s("%d", &flag);
    }

    printf("\n Program finished\n");

    return 0;
}
