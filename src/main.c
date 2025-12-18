#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Box {
	char c;
	int val;
} BOX;

BOX b[9];

void reset(); 

int main(void) {
	int num, sum, b_sum;
	unsigned int d1, d2, d_sum;

	srand((unsigned int)time(NULL));
	printf("Welcome to Shut the Box!\n");
	reset();

	while (true) {
		num = 0;
		sum = 0;
		b_sum = 0;
		for (int i = 0; i < 9; i++) {
			printf("| %c ", b[i].c);
			b_sum += b[i].val;
		}
		printf("|\n");

		d1 = (rand() % 6) + 1;
		d2 = (rand() % 6) + 1;
		d_sum = d1 + d2;
		
		printf("You rolled: %d and %d (total: %d).\n", d1, d2, d_sum);
		printf("Numbers to shut (type 0 if you want to end the game): \n");
		while (sum < d_sum) {
			fflush(stdin);
			printf("Your sum: %d\n", sum);
			scanf("%d", &num);

			if (num > 9) {
				printf("Please enter correct tile to shut.\n");
			}
			else if (b[num - 1].c == 'X') {
				printf("This tile is already shuted. try again.\n");
				num = 0;
			}
			else if ((sum + num) > d_sum) {
				printf("Your sum is bigger than die's sum. Try again.\n");
			}
			else if (num == 0) {
				printf("Thank you for playing!\n");
				exit(0);
			}
			else {
				sum += num;
				b[num - 1].val = 0;
				b[num - 1].c = 'X';
			}
		}
	}

	return 0;
}

void reset() {
	char a = '1';
	for (int i = 0; i < 9; i++) {
		b[i].val = i+1;
		b[i].c = a;
		a++;
	}	
}

