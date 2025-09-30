#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum Shape { ROCK, LIZARD, SCISSORS, PAPER, SPOCK, SHAPE_COUNT };


const char *shape_names[] = { "🪨", "🦎", "✂️", "🗒️", "🖖" };


int check_winner(enum Shape player, enum Shape agent) {
    if (player == agent) return 0; 

    
    if ((player == ROCK     && (agent == SCISSORS || agent == LIZARD)) ||
        (player == PAPER    && (agent == ROCK || agent == SPOCK)) ||
        (player == SCISSORS && (agent == PAPER || agent == LIZARD)) ||
        (player == LIZARD   && (agent == PAPER || agent == SPOCK)) ||
        (player == SPOCK    && (agent == ROCK || agent == SCISSORS)))
    {
        return 1; // Player wins
    }
    return -1; // Agent wins
}

int main() {
    srand(time(NULL)); 

    int player_score = 0, agent_score = 0;
    char mode;

    printf("Welcome to 🪨 ✂️ 🗒️ 🖖 🦎 !\n");
    printf("(s) Single player\n(e) Exit\n");
    printf("Select an item: ");
    mode = getchar();
    getchar(); 

    if (mode == 'e') {
        printf("Bye! 👋\n");
        return 0;
    }

    printf("Starting game 🎉\n");

    while (1) {
        int choice;
        printf("\nSelect a shape:\n");
        for (int i = 0; i < SHAPE_COUNT; i++) {
            printf("%d%s  ", i, shape_names[i]);
        }
        printf(": ");

        if (scanf("%d", &choice) != 1 || choice < 0 || choice >= SHAPE_COUNT) {
            printf("❌ Shape key does not exist. Try again.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        enum Shape player = (enum Shape) choice;
        enum Shape agent  = (enum Shape) (rand() % SHAPE_COUNT);

        printf("Agent: %d%s\n", agent, shape_names[agent]);

        int result = check_winner(player, agent);
        if (result == 0) {
            printf("It's a draw!\n");
        } else if (result == 1) {
            player_score++;
            printf("You win this round!\n");
        } else {
            agent_score++;
            printf("Agent wins this round!\n");
        }

        printf("👫:%d 🤖:%d\n", player_score, agent_score);

        // End game condition
        if (player_score == 5 || agent_score == 5) {
            if (player_score > agent_score) {
                printf("🎉 You won the game!\n");
            } else {
                printf("🤖 Agent won the game!\n");
            }
            break;
        }
    }

    return 0;
}
