#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define SIZE 4792

int arr[SIZE];
int idx = 0;

void fillPrimes(int number) {
	if (number < 2) return;
	if (number == 2) {
		arr[idx] = pow(number, 2);
		idx++;
		return;
	}
	if (number % 2 == 0) return;

	int max = (int)sqrt(number);
	for (int i = 3; i <= max; i += 2) {
		if (number % i == 0) {
			return;
		}
	}

	arr[idx] = pow(number, 2);
	idx++;
	return;
}

int main() {
	printf("Poradi:\n");
	int res = 0;
	int max = 46340;
	for (int i = 1; i < max; i++) {
		fillPrimes(i);
	}
	int pos;
	while (scanf("%d", &pos) == 1) {
		if (pos < 1) {
			printf("Nespravny vstup.\n");
			return 0;
		}
		res = 0;
		for (int i = 1; i < 2147483647; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (i < arr[j]) {
					res += 1;
					break;
				}
				if (i % arr[j] == 0) break;
			}
			if (res == pos) {
				printf("= %d\n", i);
				break;
			}
		}
	}
	if (!feof(stdin)) {
		printf("Nespravny vstup.\n");
	}
	return 0;
}