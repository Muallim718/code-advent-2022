#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10
#define ROCK 1
#define PAPER 2
#define SCISSORS 3
#define WIN 6
#define DRAW 3
#define LOSS 0

struct hand {
    bool rock;
    bool paper;
    bool scissors;
};

int player_point_adjustment(char choice);
int opponent_point_adjustment(char choice);
struct hand player_outcome(int player_score, int opponents_score);
int outcome(struct hand player);

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    char buffer[SIZE];
    int players_score = 0;
    int opponents_score = 0; 
    int true_score = 0;
    int total_score = 0;

    if (argc != 2) {
        printf("Usage: ./rps rps.txt\n");
        return 1;
    }

    if (file == NULL) {
        printf("File failed to open.\n");
        return 1;
    }

    struct hand player;

    while (fgets(buffer, SIZE, file) != NULL) {
        char opponents_choice = buffer[0];
        char players_choice = buffer[2];
        players_score = player_point_adjustment(players_choice);
        opponents_score = opponent_point_adjustment(opponents_choice);
        player = player_outcome(players_score, opponents_score);
        true_score = players_score + outcome(player);
        total_score += true_score;;
    }
    printf("You will have a total score of %i!\n", total_score);

    fclose(file);
    return 0;
}

int player_point_adjustment(char players_choice) {
    if (players_choice == 'X') return LOSS;
    else if (players_choice == 'Y') return DRAW;
    return WIN;
}

int opponent_point_adjustment(char opponents_choice) {
    if (opponents_choice == 'A') return ROCK;
    else if (opponents_choice == 'B') return PAPER;
    return SCISSORS;
}

struct hand player_outcome(int player_score, int opponents_score) {

    struct hand player;
    player.rock = false; player.paper = false; player.scissors = false;

    if ((player_score == WIN && opponents_score == SCISSORS) || (player_score == DRAW && opponents_score == ROCK) || (player_score == LOSS && opponents_score == PAPER)) player.rock = true;
    else if ((player_score == WIN && opponents_score == ROCK) || (player_score == DRAW && opponents_score == PAPER) || (player_score == LOSS && opponents_score == SCISSORS)) player.paper = true;
    else if ((player_score == WIN && opponents_score == PAPER) || (player_score == DRAW && opponents_score == SCISSORS) || (player_score == LOSS && opponents_score == ROCK)) player.scissors = true;

    return player;
}

int outcome(struct hand player) {

    if (player.rock) return ROCK;
    else if (player.paper) return PAPER;
    else if (player.scissors) return SCISSORS;
}