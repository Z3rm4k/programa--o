#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PLAYERS 2
#define NUM_SPACES 20

typedef struct {
    char name[50];
    int money;
    int position;
} Player;

typedef struct {
    char name[50];
    int price;
    int owner;
} Space;

Player players[NUM_PLAYERS];
Space spaces[NUM_SPACES];

void initializeGame() {
    strcpy(players[0].name, "Jogador 1");
    players[0].money = 1500;
    players[0].position = 0;

    strcpy(players[1].name, "Jogador 2");
    players[1].money = 1500;
    players[1].position = 0;

    strcpy(spaces[0].name, "Início");
    spaces[0].price = 0;
    spaces[0].owner = -1;

    // Preencha os detalhes para os outros espaços do tabuleiro

    // ...

    // Por exemplo:
    strcpy(spaces[1].name, "Propriedade 1");
    spaces[1].price = 200;
    spaces[1].owner = -1;
}

void printBoard() {
    system("cls");  // Limpa a tela do prompt de comando (Windows)
    // system("clear"); // Limpa a tela do prompt de comando (Linux/Mac)

    // Imprime o tabuleiro com base nas posições dos jogadores e propriedades

    printf("Tabuleiro do Monopoly\n\n");

    // Imprima os detalhes do tabuleiro

    // ...

    // Por exemplo:
    for (int i = 0; i < NUM_SPACES; i++) {
        printf("[%d] %s - Preço: %d - Dono: %s\n", i, spaces[i].name, spaces[i].price,
               spaces[i].owner != -1 ? players[spaces[i].owner].name : "Nenhum");
    }

    printf("\n");

    // Imprima os detalhes dos jogadores

    // ...

    // Por exemplo:
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Jogador %d: %s - Dinheiro: %d - Posição: %d\n", i + 1, players[i].name, players[i].money,
               players[i].position);
    }
}

int rollDice() {
    return (rand() % 6) + 1;
}

void playTurn(int currentPlayer) {
    printf("Vez do jogador: %s\n", players[currentPlayer].name);

    // Realize as ações do turno: rolar dados, mover jogador, lidar com propriedades, etc.

    int diceRoll = rollDice();
    printf("Resultado do dado: %d\n", diceRoll);

    players[currentPlayer].position = (players[currentPlayer].position + diceRoll) % NUM_SPACES;

    // Lide com a propriedade atual, como comprar, pagar aluguel, etc.

    // ...

    // Exemplo: comprar propriedade se possível
    if (spaces[players[currentPlayer].position].owner == -1) {
        printf("Deseja comprar %s por %d? (1 - Sim, 2 - Não): ", spaces[players[currentPlayer].position].name,
               spaces[players[currentPlayer].position].price);

        int choice;
        scanf("%d", &choice);

        if (choice == 1 && players[currentPlayer].money >= spaces[players[currentPlayer].position].price) {
            players[currentPlayer].money -= spaces[players[currentPlayer].position].price;
            spaces[players[currentPlayer].position].owner = currentPlayer;
            printf("Parabéns! Você comprou %s!\n", spaces[players[currentPlayer].position].name);
        } else {
            printf("Você optou por não comprar %s.\n", spaces[players[currentPlayer].position].name);
        }
    }

    // Atualize outros elementos do jogo, como dinheiro, aluguéis, etc.

    // ...

    // Exemplo: cobrar aluguel se o jogador cair em uma propriedade de outro jogador
    if (spaces[players[currentPlayer].position].owner != -1 && spaces[players[currentPlayer].position].owner != currentPlayer) {
        int rent = spaces[players[currentPlayer].position].price * 0.1; // 10% do preço da propriedade
        players[currentPlayer].money -= rent;
        players[spaces[players[currentPlayer].position].owner].money += rent;
        printf("Você pagou %d de aluguel para %s.\n", rent, players[spaces[players[currentPlayer].position].owner].name);
    }

    // Aguarde a entrada do jogador para continuar
    printf("Pressione Enter para continuar...\n");
    getchar();
    getchar();
}

int main() {
    srand(time(NULL));

    initializeGame();

    int currentPlayer = 0;
    int gameOver = 0;

    while (!gameOver) {
        printBoard();
        playTurn(currentPlayer);

        // Verifique se algum jogador faliu
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (players[i].money <= 0) {
                gameOver = 1;
                break;
            }
        }

        currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
    }

    printf("Fim de jogo!\n");

    // Exiba o vencedor ou qualquer outra informação relevante

    return 0;
}
