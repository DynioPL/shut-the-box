#include <math.h>
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
bool check_dice();
bool check_tiles(int);

int main(void)
{
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
		
		if (b_sum == 0) {
			printf("Congratulations, You won! All tiles are shuted.\n");
			printf("Another round? [y/N]: ");

			char ch;
			scanf(" %c", &ch);
			if (ch == 'Y' || ch == 'y') {
				reset();
				fflush(stdin);
				continue;
			}
			else {
				printf("Thank you for playing!\n");
				exit(0);				
			}
		}

		if (!check_dice()) {
			int d_ch;
			printf("Looks like you have 7-9 tiles shuted. Would you like to use 1 dice or 2 dice? (type 1 or 2)\n");
			// Workaround because I don't want to use goto :P
			while (true) {
				scanf("%d", &d_ch);
				switch (d_ch) {
					case 1:
						d1 = (rand() % 6) + 1;
						d_sum = d1;
						// That looks kinda stupid.
						printf("You rolled: %d (total: %d).\n", d1, d_sum);
						break; 
					case 2:
						d1 = (rand() % 6) + 1;
						d2 = (rand() % 6) + 1;
						d_sum = d1 + d2;
						printf("You rolled: %d and %d (total: %d).\n", d1, d2, d_sum);
						break;
					default:
						printf("Enter correct number!\n");
						fflush(stdin);
						continue;
				}
				break;
			}
		}
		else {
			d1 = (rand() % 6) + 1;
			d2 = (rand() % 6) + 1;
			d_sum = d1 + d2;
			printf("You rolled: %d and %d (total: %d).\n", d1, d2, d_sum);
		}
		bool possible = check_tiles(d_sum);
	
		if (possible == false) {
			printf("Looks like you can't make sum from remaining tiles. Game over!\n");
			printf("Your score: %d\n", b_sum);
			printf("Another round? [y/N]: ");
		
			// scanning for char input is in my nightmares.
			char ch;
			fflush(stdin);
			scanf(" %c", &ch);
			if (ch == 'Y' || ch == 'y') {
				reset();
				fflush(stdin);
				continue;
			}
			else {
				printf("Thank you for playing!\n");
				exit(0);
			}
		}

		printf("Numbers to shut (type 0 if you want to end the game): \n");
		while (sum < d_sum) {
			fflush(stdin);
			printf("Your sum: %d\n", sum);
			scanf("%d", &num);

			if (num > 9 || num < 0) {
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
	// TODO: Add condition for having only 1 tile below: DONE.
	return 0;

}

void reset()
{
	char a = '1';
	for (int i = 0; i < 9; i++) {
		b[i].val = i+1;
		b[i].c = a;
		a++;
	}	
}

bool check_dice()
{
	int is_shuted = 0;
	for (int i = 6; i < 9; i++) {
		if (b[i].val == 0)
			is_shuted++;
	}
	if (is_shuted == 3)
		return false;
	return true;
}

bool check_tiles(int d_sum) 
{
	bool possible = true;
	if (d_sum < 9) {
		if (b[d_sum - 1].val == 0) {
			// This is the worst algorythm you will ever see.
			// We are checking for possible combinations of 2 one digit numbers which will give us sum of dice
			// We can't execute this algorythm if we draw a 1 or 2.
			if (d_sum < 3)
				possible = false;
			else {
				//Necessary variables.
				int x = d_sum - 1;
				int y = 1;
				int d_sum_half_ceil = ceilf(((float)d_sum / 2));
				int d_sum_half_floor = floorf(((float)d_sum / 2));
				// Main part of algorythm. This loop will execute until a possible combination of numbers is found or until no possible combination is found.
				// We're testing if the sum of remaining tiles is equal to drawn by the dice (value of shuted tile should be 0).
				// The operation vary between odd and even numbers. If the number is odd, we need to include endpoint of interval in loop declaration. Otherwise, we need to exclude it.
				// In the combination is found, set the value of boolean variable to true and break the loop. Otherwise, set to false and try another combination.
				
				// For odd numbers...
				if ((d_sum % 2) != 0) {
					while (x >= d_sum_half_ceil && y <= d_sum_half_floor) {
						if ((b[x - 1].val + b[y - 1].val) == d_sum) {
							possible = true;
							break;
						}
						else {
							possible = false;
						}
						x--;
						y++;
					}
				}
				// ...And for even numbers
				else {
					while (x > d_sum_half_ceil && y < d_sum_half_floor) {
						if ((b[x - 1].val + b[y - 1].val) == d_sum) {
							possible = true;
							break;
						}
						else {
							possible = false;
						}
						x--;
						y++;
					}
				}
			}			
		}
		else {
			possible = true;
		}
	}
	else {
		// Second part of algorythm for sum of numbers greater than 9.
		int x = 9;
		int y = d_sum - x;
		int d_sum_half_ceil = ceilf(((float)d_sum / 2));
		int d_sum_half_floor = floorf(((float)d_sum / 2));
		// The logic remains the same.	
		
		if ((d_sum % 2) != 0) {
			while (x >= d_sum_half_ceil && y <= d_sum_half_floor) {
				if ((b[x - 1].val + b[y - 1].val) == d_sum) {
					possible = true;
					break;	
				}
				else {
					possible = false;
				}
				x--;
				y++;
			}
		}
		else {
			while (x > d_sum_half_ceil && y < d_sum_half_floor) {
				if ((b[x - 1].val + b[y - 1].val) == d_sum) {
					possible = true;
					break;	
				}
				else {
					possible = false;
				}
				x--;
				y++;
			}
		}
	}
	return possible;
}

