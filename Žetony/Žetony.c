#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100

typedef struct {
    int first;
    int second;
    int pick1;
    int pick2;
} cell_t;

cell_t memo[SIZE][SIZE];
int length = 0;
int* coins;

void findMoves() {
    for (int i = 0; i < length; i++) {
        memo[i][i].first = coins[i];
        memo[i][i].second = 0;
        memo[i][i].pick1 = i;
        memo[i][i].pick2 = -1;
    }

    for(int l = 2; l <= length; l++) {
        for(int i = 0; i <= length - l; i++) {
            int j = i + l -1;
            int max = INT_MIN;
            int second = INT_MIN;

            // picks the leftest coin
            int firstRes = coins[i] + memo[i+1][j].second;
            int secondRes = memo[i+1][j].first;
            if (firstRes > max) {
                max = firstRes;
                second = secondRes;
                memo[i][j].pick1 = i;
                memo[i][j].pick2 = -1;
            }

            // picks the rightest coin
            firstRes = coins[j] + memo[i][j-1].second;
            secondRes = memo[i][j-1].first;
            if (firstRes > max) {
                max = firstRes;
                second = secondRes;
                memo[i][j].pick1 = j;
                memo[i][j].pick2 = -1;
            }
            
            // picks two leftest coins
            firstRes = coins[i] + coins[i+1] + memo[i+2][j].second;
            secondRes = memo[i+2][j].first;
            if (firstRes > max) {
                max = firstRes;
                second = secondRes;
                memo[i][j].pick1 = i;
                memo[i][j].pick2 = i+1;
            }

            // picks two rightest coins
            firstRes = coins[j] + coins[j-1] + memo[i][j-2].second;
            secondRes = memo[i][j-2].first;
            if (firstRes > max) {
                max = firstRes;
                second = secondRes;
                memo[i][j].pick1 = j;
                memo[i][j].pick2 = j-1;
            }

            // picks leftest and rightest coins
            firstRes = coins[i] + coins[j] + memo[i+1][j-1].second;
            secondRes = memo[i+1][j-1].first;
            if (firstRes > max) {
                max = firstRes;
                second = secondRes;
                memo[i][j].pick1 = i;
                memo[i][j].pick2 = j;
            }

            // save result
            memo[i][j].first = max;
            memo[i][j].second = second; 
        }
    }
}

void printSequence() {
    int i = 0;
    int j = length - 1;
    int step1, step2;
    int player = 1;
    int firstWasTaken = 0;
    for (int k = 0; k < length; k++) {
        step1 = memo[i][j].pick1;
        step2 = memo[i][j].pick2;
        if (step1 == 0 && firstWasTaken) {
            return;
        }
        printf(player == 1 ? "A " : "B ");
        // first coin was taken from the left
        if (step1 <= i) {
            if (step1 == 0) firstWasTaken = 1;
            i += 1;
            // second coin was also taken from the left
            if (step2 <= i && step2 > 0) {
                i += 1;
                printf("%d, %d (%d,%d)\n", step1, step2, coins[step1], coins[step2]);
            }
            // second coin was taken from the right
            else if (step2 > i) {
                j -= 1;
                printf("%d, %d (%d,%d)\n", step1, step2, coins[step1], coins[step2]);
            }
            // second coin was not taken
            else {
                printf("%d (%d)\n", step1, coins[step1]);
            }
        }
        // first coin was taken from the right
        else {
            j -= 1;
            // second coin was also taken from the right
            if (step2 > i) {
                j -= 1;
                printf("%d, %d (%d,%d)\n", step1, step2, coins[step1], coins[step2]);
            }
            // second coin was not taken
            else {
                printf("%d (%d)\n", step1, coins[step1]);
            }
        }
        // swap players
        player = player == 1 ? 2 : 1;
    }
}

int main() {
    printf("Zetony:\n");
    coins = (int*)malloc(sizeof(int));
    int coin, idx = 0;
    char term;
    while (scanf("%d", &coin) == 1) {
        if (scanf("%c", &term) != 0 && term != ' ' && term != '\n') {
            printf("Nespravny vstup.\n"); 
            return 0;
        }
        coins = (int*)realloc(coins, sizeof(int)*(idx+1));
        coins[idx] = coin;
        idx++;
    }
    length = idx;
    if (!feof (stdin) || length > SIZE || length == 0) {
        printf("Nespravny vstup.\n"); 
        return 0;
    }

    findMoves();
    int aRes = memo[0][idx-1].first;
    int bRes = memo[0][idx-1].second;
    printSequence();
    printf("A: %d, B: %d\n", aRes, bRes);

    free(coins);
    return 0;
}