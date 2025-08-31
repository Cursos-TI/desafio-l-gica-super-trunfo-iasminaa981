/* super_trunfo.c
   Continuação do projeto: comparação entre duas cartas do Super Trunfo.
   Compile: gcc -o super_trunfo super_trunfo.c
   Rodar: ./super_trunfo
*/

#include <stdio.h>
#include <string.h>

/* Estrutura que representa uma carta */
struct Carta {
    char estado[4];           /* ex: "SP" (reduzido) */
    char codigo[8];           /* ex: "A01" */
    char nomeCidade[100];
    int populacao;            /* habitantes */
    float area;               /* km² */
    float pib;                /* unidade conforme cadastro (ex: bilhões) */
    int pontosTuristicos;
};

/* Atributos disponíveis para comparar.
   Mude ATRIBUTO_COMPARACAO abaixo para testar outros. */
enum Atributo { ATR_POPULACAO = 1, ATR_AREA, ATR_PIB, ATR_DENSIDADE, ATR_PIB_PER_CAPITA };

/* ---------- CONFIGURAÇÃO: escolha aqui o atributo para a comparação ---------- */
#define ATRIBUTO_COMPARACAO ATR_POPULACAO
/* Opções: ATR_POPULACAO, ATR_AREA, ATR_PIB, ATR_DENSIDADE, ATR_PIB_PER_CAPITA */
/* ----------------------------------------------------------------------------- */

/* Função para imprimir uma carta com os cálculos (densidade e PIB per capita) */
void imprimirCarta(const struct Carta *c, int indice) {
    double densidade = 0.0;
    double pibPerCapita = 0.0;

    if (c->area != 0.0f) {
        densidade = (double)c->populacao / (double)c->area;
    } /* se area == 0 -> densidade permanece 0 (evita divisão por zero) */

    if (c->populacao != 0) {
        pibPerCapita = (double)c->pib / (double)c->populacao;
    } /* se populacao == 0 -> pib per capita = 0 (evita divisão por zero) */

    printf("Carta %d:\n", indice);
    printf("  Estado: %s\n", c->estado);
    printf("  Código: %s\n", c->codigo);
    printf("  Cidade: %s\n", c->nomeCidade);
    printf("  População: %d\n", c->populacao);
    printf("  Área: %.2f km²\n", c->area);
    printf("  PIB: %.2f (mesma unidade do cadastro)\n", c->pib);
    printf("  Pontos Turísticos: %d\n", c->pontosTuristicos);
    printf("  Densidade Populacional: %.2f hab/km²\n", densidade);
    printf("  PIB per capita (PIB / População): %.8f (mesma unidade do PIB/hab)\n", pibPerCapita);
}

int main() {
    struct Carta carta1, carta2;

    /* ----------------- Cartas pré-definidas (simplificação do nível) -----------------
       Se preferir entrada pelo usuário, comente estas inicializações e
       descomente o bloco de entrada abaixo (marcado como "entrada interativa").
    ------------------------------------------------------------------------------- */

    /* Carta 1 (exemplo) */
    strcpy(carta1.estado, "SP");
    strcpy(carta1.codigo, "A01");
    strcpy(carta1.nomeCidade, "São Paulo");
    carta1.populacao = 12300000;
    carta1.area = 1521.11f;
    carta1.pib = 700.0f; /* por exemplo, 700 (bilhões) conforme seu cadastro */
    carta1.pontosTuristicos = 15;

    /* Carta 2 (exemplo) */
    strcpy(carta2.estado, "RJ");
    strcpy(carta2.codigo, "A02");
    strcpy(carta2.nomeCidade, "Rio de Janeiro");
    carta2.populacao = 6000000;
    carta2.area = 1182.30f;
    carta2.pib = 300.0f;
    carta2.pontosTuristicos = 12;

    /* ----------------- Exemplo de entrada interativa (descomente se quiser) -----------------
    printf("Cadastro da Carta 1:\n");
    printf("Estado (ex: SP): "); scanf("%3s", carta1.estado);
    printf("Código (ex: A01): "); scanf("%7s", carta1.codigo);
    printf("Nome da cidade: "); scanf(" %[^\n]", carta1.nomeCidade);
    printf("População: "); scanf("%d", &carta1.populacao);
    printf("Área (km²): "); scanf("%f", &carta1.area);
    printf("PIB: "); scanf("%f", &carta1.pib);
    printf("Pontos Turísticos: "); scanf("%d", &carta1.pontosTuristicos);

    printf("\nCadastro da Carta 2:\n");
    printf("Estado (ex: RJ): "); scanf("%3s", carta2.estado);
    printf("Código (ex: A02): "); scanf("%7s", carta2.codigo);
    printf("Nome da cidade: "); scanf(" %[^\n]", carta2.nomeCidade);
    printf("População: "); scanf("%d", &carta2.populacao);
    printf("Área (km²): "); scanf("%f", &carta2.area);
    printf("PIB: "); scanf("%f", &carta2.pib);
    printf("Pontos Turísticos: "); scanf("%d", &carta2.pontosTuristicos);
    --------------------------------------------------------------------------------------- */

    /* Exibir cartas e os cálculos auxiliares */
    printf("=== Cartas cadastradas ===\n\n");
    imprimirCarta(&carta1, 1);
    printf("\n");
    imprimirCarta(&carta2, 2);
    printf("\n");

    /* Preparar comparação segundo o atributo escolhido em ATRIBUTO_COMPARACAO */
    int atributo = ATRIBUTO_COMPARACAO;
    const char *nomeAtributo = "Atributo desconhecido";
    double valor1 = 0.0, valor2 = 0.0;
    int menorVence = 0; /* flag: se 1 então menor valor vence (requisito para densidade) */

    switch (atributo) {
        case ATR_POPULACAO:
            nomeAtributo = "População";
            valor1 = (double)carta1.populacao;
            valor2 = (double)carta2.populacao;
            break;
        case ATR_AREA:
            nomeAtributo = "Área (km²)";
            valor1 = (double)carta1.area;
            valor2 = (double)carta2.area;
            break;
        case ATR_PIB:
            nomeAtributo = "PIB";
            valor1 = (double)carta1.pib;
            valor2 = (double)carta2.pib;
            break;
        case ATR_DENSIDADE:
            nomeAtributo = "Densidade Populacional (hab/km²)";
            menorVence = 1; /* para densidade, menor valor vence conforme enunciado */
            valor1 = (carta1.area != 0.0f) ? (double)carta1.populacao / (double)carta1.area : 0.0;
            valor2 = (carta2.area != 0.0f) ? (double)carta2.populacao / (double)carta2.area : 0.0;
            break;
        case ATR_PIB_PER_CAPITA:
            nomeAtributo = "PIB per capita (PIB / População)";
            valor1 = (carta1.populacao != 0) ? (double)carta1.pib / (double)carta1.populacao : 0.0;
            valor2 = (carta2.populacao != 0) ? (double)carta2.pib / (double)carta2.populacao : 0.0;
            break;
        default:
            printf("Atributo de comparação inválido. Verifique ATRIBUTO_COMPARACAO.\n");
            return 1;
    }

    /* Mostra os valores usados na comparação */
    printf("Comparação de cartas (Atributo: %s):\n\n", nomeAtributo);
    if (atributo == ATR_POPULACAO) {
        printf("Carta 1 - %s (%s): %d\n", carta1.nomeCidade, carta1.estado, carta1.populacao);
        printf("Carta 2 - %s (%s): %d\n\n", carta2.nomeCidade, carta2.estado, carta2.populacao);
    } else {
        printf("Carta 1 - %s (%s): %.6g\n", carta1.nomeCidade, carta1.estado, valor1);
        printf("Carta 2 - %s (%s): %.6g\n\n", carta2.nomeCidade, carta2.estado, valor2);
    }

    /* Determina o vencedor */
    if (valor1 == valor2) {
        printf("Resultado: Empate! Ambos os valores são iguais.\n");
    } else {
        int carta1Vence;
        if (menorVence) {
            carta1Vence = (valor1 < valor2) ? 1 : 0;
        } else {
            carta1Vence = (valor1 > valor2) ? 1 : 0;
        }

        if (carta1Vence) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nomeCidade);
        } else {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nomeCidade);
        }
    }

    return 0;
}
