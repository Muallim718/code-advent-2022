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
struct hand player_outcome(int player_score);
struct hand opponent_outcome(int player_score);
int outcome(struct hand player, struct hand opponent);

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
    struct hand opponent;

    while (fgets(buffer, SIZE, file) != NULL) {
        char opponents_choice = buffer[0];
        char players_choice = buffer[2];
        players_score = player_point_adjustment(players_choice);
        opponents_score = opponent_point_adjustment(opponents_choice);
        player = player_outcome(players_score);
        opponent = opponent_outcome(opponents_score);
        true_score = players_score + outcome(player, opponent);
        total_score += true_score;
    }
    printf("You will have a total score of %i!\n", total_score);

    return 0;
}

int player_point_adjustment(char players_choice) {
    if (players_choice == 'X') return ROCK;
    else if (players_choice == 'Y') return PAPER;
    return SCISSORS;
}

int opponent_point_adjustment(char opponents_choice) {
    if (opponents_choice == 'A') return ROCK;
    else if (opponents_choice == 'B') return PAPER;
    return SCISSORS;
}

struct hand player_outcome(int player_score) {

    struct hand player;
    player.rock = false; player.paper = false; player.scissors = false;

    if (player_score == 1) player.rock = true;
    else if (player_score == 2) player.paper = true;
    else player.scissors = true;

    return player;
}

struct hand opponent_outcome(int opponent_score) {

    struct hand opponent;
    opponent.rock = false; opponent.paper = false; opponent.scissors = false;

    if (opponent_score == 1) opponent.rock = true;
    else if (opponent_score == 2) opponent.paper = true;
    else opponent.scissors = true;

    return opponent;
}

int outcome(struct hand player, struct hand opponent) {

    if ((player.rock && opponent.scissors) || (player.paper && opponent.rock) || (player.scissors && opponent.paper)) return WIN;
    else if ((player.scissors && opponent.rock) || (player.rock && opponent.paper) || (player.paper && opponent.scissors)) return LOSS;
    else if ((player.rock && opponent.rock) || (player.paper && opponent.paper) || (player.scissors && opponent.scissors)) return DRAW;
}