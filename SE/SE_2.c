#include <stdio.h>
#include <string.h>

#define N 9
#define MAX 1024

void roman_to_arabic(char *x);
int main(void)
{
	char x[MAX];

	while (1)
	{
		printf("ローマ数字を入力してください.\n");
        printf("5000と10000には対応しています．文字はそれぞれWとTとします．\n");
        printf("同じ文字は4回以上連続で入力できます．\n");
		printf("終了したい場合は'exit'と入力してください.\n");

		/*** INPUT ROMAN NUMERAL ***/
		scanf("%s", x);

		if (strcmp(x, "exit") == 0) { /* exit check */
			break;
		}

		roman_to_arabic(x);
	}

	return 0;
}

void roman_to_arabic(char *x)
{
	int num[N] = {1, 5, 10, 50, 100, 500, 1000, 5000, 10000};
	char roman[N] = {'I', 'V', 'X', 'L', 'C', 'D', 'M', 'W', 'T'};
	int i, j, k, l, m;
	int result = 0;
	int flag = 0;
	int tmp;

	for (i = 0; x[i] != 0; i++) { /* Convert to capital */
		if (x[i] <= 'z' && x[i] >= 'a') {
			x[i] = x[i] - ('a' - 'A');
		}
	}
	/*** ROMAN TO ARABIC PROCESS  ***/
	i = 0;
	while (x[i] != '\0') {		/* by NULL */

		/** Convert process  **/
		j = 0;
		while (j < N) {

			if (x[i] == roman[j]) {
				k = j + 1; 		/* Next x */

				while (x[i + 1] != roman[k] && k < N) {
					k++;
				}

				if (k >= N) { 	/* If NOW >= NEXT  */
					tmp = result + num[j];
					if (result == 0) {
						result = tmp;
						i++;
					}else {
						if (result >= num[j] && x[i - 1] == x[i] && j != 1 && j != 3 && j != 5 && j != 7) { 	/* for 'CCC'..  */
							result = tmp;
							i++;
						}else if (result > num[j] && x[i - 1] != x[i]) { 	/* for 'VI', 'MCX'...  */
                            if (num[j] == num[0] && tmp % 10 == 5) { 	/* for '..IVI' */
							    flag = 1;
                            }
							for (l = 2; l < N; l += 2) {
								for (m = 1; m < 5; m++) {
									if (tmp == m * num[l]) {
										flag = 1;
									}
								}
								if (flag == 1) {
									break;
								}
							}

							if (tmp == num[1] || tmp == num[3] || tmp == num[5] || tmp == num[7]) { 		/* for 'CDXCX...'... */
								flag = 1;
							}

							if (flag != 1) {
								result = tmp;
								i++;
							}
						}else {
							flag = 1;
						}
					}
				}else { 	/* If NOW < NEXT */
					for (l = 1; l <= 1000; l *= 10) {
						if (num[k] - num[j] == l * 4 || num[k] - num[j] == l * 9) {
							tmp = num[k] - num[j];
							break;
						}
					}

					if (l > 1000) {
						flag = 1;
					}

					if (result == 0 && flag != 1) {
						result = result + tmp;
						i += 2;
					}else if (result > tmp && result + tmp != 9 && result + tmp != 90 && result + tmp != 900 && result + tmp != 9000 && flag != 1) {	/* for 'viv','lxl'... */
						if (i >= 2 && x[i - 2] == x[i] && x[i - 1] == x[i + 1]) {		/* for 'CMCM'...*/
							flag = 1;
						}else {
							if ((j == 0 && k == 1 && (result + tmp) % 10 == 9) || (j == 2 && k == 3 && (result + tmp) % 100 == 90) || (j == 4 && k == 5 && (result + tmp) % 1000 == 900) || (j == 6 && k == 7 && (result + tmp) % 10000 == 9000)) {		/* for 'XCVIV'...*/
								flag = 1;
							}else {
								result = result + tmp;
								i += 2;
							}
						}
					}else {
						flag = 1;
					}
				}
				break;
			}

			j++;	/* search which roman numeral */
		}

		if (j >= N) {
			printf("-ERR %d番目か%d番目の文字がローマ数字ではありません.\n\n", i + 1, i + 2);
			break;
		}

		if (flag == 1) {
			printf("ローマ数字の決まりに則ってください. \n\n");
			break;
		}
	}

	if (i == strlen(x)) {		/* if successed */
		printf("%s -> %d\n\n", x, result);
	}

	return;
}