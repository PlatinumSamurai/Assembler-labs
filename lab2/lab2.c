#include <stdio.h>
#include <ctype.h>


int main() {
	short flag = 1;

	while (flag) {
		char seq[4];
		short digitNum = 0;

		while (!digitNum) {
			printf("Enter 3 digits as one number: ");
			fgets(seq, sizeof(seq), stdin);
			setbuf(stdin, NULL);

			for (int i = 0; i < sizeof(seq) - 1; ++i) {
				if (isdigit(seq[i])) {
					digitNum += 1;
				}
				else {
					digitNum = 0;
					printf("Sequence is incorrect! Try again\n\n");
					break;
				}
			}
		}

		__asm {
			mov al, seq[0];	поместить в al значение seq[0]
			mov bl, seq[1];	поместить в bl значение seq[1]
			mov cl, seq[2];	поместить в cl значение seq[2]

			sub al, '0';	получить числовое значение seq[0]
			sub bl, '0';	получить числовое значение seq[1]
			sub cl, '0';	получить числовое значение seq[2]

			cmp al, cl;		выполнить сравнение al и cl
			jbe SWAP;		если al <= cl, то перейти к обмену al и bl
			cmp bl, cl;		иначе выполнить сравнение bl и cl
			ja SWAP;		если bl > cl, то перейти к обмену bl и cl

			cmp cl, 7;		иначе выполнить сравнение cl и 7
			ja ENDS;		если cl > 7, то переход к концу ассемблерной вставки
			sub cl, 7;		иначе вычесть из cl 7
			neg cl;		обратить знак cl
			jmp END;		перейти к выводу


		SWAP : xchg al, bl;	обменять содержимое регистров al и bl
			add al, '0';	получить символьное значение al
			add bl, '0';	получить символьное значение bl
			mov seq[0], al;	поместить в seq[0] значение al
			mov seq[1], bl;	поместить в seq[1] значение bl
			jmp ENDS;		переход к концу ассемблерной вставки

		END: add cl, '0';		получить символьное значение cl
			mov seq[2], cl;	поместить в seq[2] значение cl

		ENDS:;			закончить выполнение ассемблерной вставки

		}

		printf("Result: %s", seq);

		printf("\n\nEnter 0 to finish program: ");
		scanf("%hd", &flag);
		setbuf(stdin, NULL);
		printf("\n\n");
	}

	printf("Program finished\n");

	return 0;
}
