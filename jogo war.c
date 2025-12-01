#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura dos territórios
typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
} Territorio;

// Estrutura dos jogadores
typedef struct {
    char nome[30];
    char* missao;
    Territorio* territorio;
} Jogador;

// Função para simular o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- Iniciando batalha entre %s e %s ---\n", atacante->nome, defensor->nome);
    printf("Tropas do atacante (%s): %d\n", atacante->nome, atacante->tropas);
    printf("Tropas do defensor (%s): %d\n", defensor->nome, defensor->tropas);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if ((atacante->tropas + dadoAtacante) > (defensor->tropas + dadoDefensor)) {
        printf("\nO território %s venceu a batalha!\n", atacante->nome);
        defensor->tropas = atacante->tropas / 2; 
        strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
        defensor->cor[sizeof(defensor->cor) - 1] = '\0';
    } else {
        printf("\nO território %s defendeu com sucesso!\n", defensor->nome);
        atacante->tropas = atacante->tropas / 2;
    }

    printf("\n--- Situação após o duelo ---\n");
    printf("%s - Tropas: %d - Cor: %s\n", atacante->nome, atacante->tropas, atacante->cor);
    printf("%s - Tropas: %d - Cor: %s\n", defensor->nome, defensor->tropas, defensor->cor);
}

// Função para atribuir missão
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função para exibir regras
void exibirRegras() {
    printf("\n--- REGRAS DO JOGO ---\n");
    printf("Bem-vindo ao Jogo War!\n");
    printf("O objetivo é conquistar o território inimigo.\n");
    printf("Cada jogador controla um exército e um território inicial.\n");
    printf("Você pode escolher o seu território e atacar outro aleatório.\n");
    printf("O resultado do duelo é decidido com base nas tropas e em uma rolagem de dados.\n");
    printf("Se o território inimigo perder, ele passa a ser seu!\n");
    printf("------------------------\n\n");
}

int main() {
    srand(time(NULL));

    // Criação dos territórios
    int totalTerritorios = 5;
    Territorio* territorios = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));

    strncpy(territorios[0].nome, "América", sizeof(territorios[0].nome));
    strncpy(territorios[0].cor, "Verde", sizeof(territorios[0].cor));
    territorios[0].tropas = 5;

    strncpy(territorios[1].nome, "Europa", sizeof(territorios[1].nome));
    strncpy(territorios[1].cor, "Azul", sizeof(territorios[1].cor));
    territorios[1].tropas = 3;

    strncpy(territorios[2].nome, "Ásia", sizeof(territorios[2].nome));
    strncpy(territorios[2].cor, "Vermelho", sizeof(territorios[2].cor));
    territorios[2].tropas = 2;

    strncpy(territorios[3].nome, "África", sizeof(territorios[3].nome));
    strncpy(territorios[3].cor, "Amarelo", sizeof(territorios[3].cor));
    territorios[3].tropas = 4;

    strncpy(territorios[4].nome, "Oceania", sizeof(territorios[4].nome));
    strncpy(territorios[4].cor, "Branco", sizeof(territorios[4].cor));
    territorios[4].tropas = 1;

    // Missões
    char* missoes[] = {
        "Destruir o exército inimigo.",
        "Conquistar 3 territórios seguidos.",
        "Eliminar todas as tropas azuis.",
        "Dominar metade do mapa.",
        "Manter seu território invicto por 3 rodadas."
    };

    char missaoJogador[100];
    atribuirMissao(missaoJogador, missoes, 5);

    int opcao, jogando = 1;

    while (jogando) {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Iniciar duelo\n");
        printf("2 - Ver missão\n");
        printf("3 - Regras do jogo\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                printf("\nEscolha seu território:\n");
                for (int i = 0; i < totalTerritorios; i++) {
                    printf("%d - %s (Cor: %s, Tropas: %d)\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
                }

                int escolha;
                printf("\nDigite o número do seu território: ");
                scanf("%d", &escolha);
                escolha--;

                if (escolha < 0 || escolha >= totalTerritorios) {
                    printf("Escolha inválida!\n");
                    break;
                }

                int inimigo;
                do {
                    inimigo = rand() % totalTerritorios;
                } while (inimigo == escolha);

                atacar(&territorios[escolha], &territorios[inimigo]);

                int continuar;
                printf("\nDeseja iniciar outro duelo? (1 - Sim / 0 - Não): ");
                scanf("%d", &continuar);
                if (continuar == 0) jogando = 0;

                break;
            }

            case 2:
                printf("\nSua missão: %s\n", missaoJogador);
                break;

            case 3:
                exibirRegras();
                break;

            case 0:
                jogando = 0;
                break;

            default:
                printf("\nOpção inválida!\n");
        }
    }

    printf("\nJogo encerrado. Obrigado por jogar!\n");
    free(territorios);
    return 0;
}
