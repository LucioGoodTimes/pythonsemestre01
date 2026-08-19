#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

const char* carinhas[] = {"UwU", ">w<", "pwp", "OwO"};

int main() {
	srand(time(NULL));

	printf("Oi C finalmente uma língua de verdade\n");

	int crescente = 1;
	int x = 0;

	while (1) {
		for (int i = 0; i < x; i++) {
			// printf("%c ", 65 + i);
			int randr = rand() % 4;
			printf("%s ", carinhas[randr]);
		}
		printf("\n");
		if (crescente) x++;
		else x--;
		if (x == 26 || x == 0) crescente = !crescente;
		sleep(1);
	}
	printf("\n");

	return 0;
}
