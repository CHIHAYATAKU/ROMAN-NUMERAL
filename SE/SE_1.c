#include <stdio.h>
#include <string.h>

#define N 7
#define MAX 100

void roman_to_arabic(char *x);
int main(void)
{
	char x[MAX];

	while (1)
	{
		printf("ローマ字を入力してください.\n");
		printf("同じ文字は連続3回までです.\n");
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
	int num[N] = {1, 5, 10, 50, 100, 500, 1000};
	char roman[N] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
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

		/** Check 4th times  **/
		if (x[i] == x[i + 1] && x[i] == x[i + 2] && x[i] == x[i + 3]) {
			printf("-ERR　同じ文字が4回以上繰り返されています.\n\n");
			break;
		}
		if (i > 0) { 	/* for i+=2 */
			if ((x[i - 1] == x[i] && x[i - 1] == x[i + 1] && x[i - 1] == x[i + 2])) {
				printf("-ERR　同じ文字が4回以上繰り返されています.\n\n");
				break;
			}
		}

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
						if (num[j] == num[0] && tmp % 10 == 5) { 	/* for '..IVI' */
							flag = 1;
						}else if (result >= num[j] && x[i - 1] == x[i] && j != 1 && j != 3 && j != 5) { 	/* for 'CCC'..  */
							result = tmp;
							i++;
						}else if (result > num[j] && x[i - 1] != x[i]) { 	/* for 'VI', 'MCX'...  */
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

							if (tmp == num[1] || tmp == num[3] || tmp == num[5]) { 		/* for 'CDXCX...'... */
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
					for (l = 1; l <= 100; l *= 10) {
						if (num[k] - num[j] == l * 4 || num[k] - num[j] == l * 9) {
							tmp = num[k] - num[j];
							break;
						}
					}

					if (l > 100) {
						flag = 1;
					}

					if (result == 0 && flag != 1) {
						result = result + tmp;
						i += 2;
					}else if (result > tmp && result + tmp != 9 && result + tmp != 90 && result + tmp != 900 && flag != 1) {	/* for 'viv','lxl'... */
						if (i >= 2 && x[i - 2] == x[i] && x[i - 1] == x[i + 1]) {		/* for 'CMCM'...*/
							flag = 1;
						}else {
							if ((j == 0 && k == 1 && (result + tmp) % 10 == 9) || (j == 2 && k == 3 && (result + tmp) % 100 == 90) || (j == 4 && k == 5 && (result + tmp) % 1000 == 900)) {		/* for 'XCVIV'...*/
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