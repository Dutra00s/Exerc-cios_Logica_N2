#include <stdio.h>
#include <math.h>
#include <time.h>

#define PI 3.1414592 /* valor dado no enunciado */

/* 1. Maior de dois números */
double maior(double a, double b) {
    if (a > b)
        return a;
    return b;
}

/* 2. Mês e quantidade de dias */
void mostrar_mes(int numero) {
    switch (numero) {
        case 1:  printf("janeiro - 31 dias\n"); break;
        case 2:  printf("fevereiro - 28 dias\n"); break;
        case 3:  printf("março - 31 dias\n"); break;
        case 4:  printf("abril - 30 dias\n"); break;
        case 5:  printf("maio - 31 dias\n"); break;
        case 6:  printf("junho - 30 dias\n"); break;
        case 7:  printf("julho - 31 dias\n"); break;
        case 8:  printf("agosto - 31 dias\n"); break;
        case 9:  printf("setembro - 30 dias\n"); break;
        case 10: printf("outubro - 31 dias\n"); break;
        case 11: printf("novembro - 30 dias\n"); break;
        case 12: printf("dezembro - 31 dias\n"); break;
        default: printf("Numero invalido (use de 1 a 12)\n");
    }
}

/* 3. Fahrenheit -> Celsius */
double fahrenheit_para_celsius(double f) {
    return (f - 32.0) * (5.0 / 9.0);
}

/* 4. Volume do cilindro */
double volume_cilindro(double altura, double raio) {
    return PI * raio * raio * altura;
}

/* 5. Volume da esfera (4.0/3.0 evita divisão inteira) */
double volume_esfera(double raio) {
    return (4.0 / 3.0) * PI * raio * raio * raio;
}

/* 6. Opções de pagamento */
char escolher_opcao(double total) {
    char opcao;
    printf("\nOpcoes de pagamento:\n");
    printf("a) A vista com 10%% de desconto\n");
    printf("b) Em 2 vezes (preco da etiqueta)\n");
    if (total > 100)
        printf("c) De 3 a 10 vezes com 3%% de juros ao mes\n");

    while (1) {
        printf("Escolha a opcao: ");
        scanf(" %c", &opcao);
        if (opcao == 'a' || opcao == 'b' || (opcao == 'c' && total > 100))
            return opcao;
        printf("Opcao invalida.\n");
    }
}

void pagamento_a_vista(double total) {
    printf("A vista: R$ %.2f\n", total * 0.90);
}

void pagamento_duas_vezes(double total) {
    printf("2 parcelas de R$ %.2f\n", total / 2);
}

void pagamento_parcelado(double total) {
    int n;
    double i = 0.03, parcela;

    do {
        printf("Numero de parcelas (3 a 10): ");
        scanf("%d", &n);
    } while (n < 3 || n > 10);

    /* prestação com juros compostos (tabela Price) */
    parcela = total * i / (1 - pow(1 + i, -n));
    printf("%d parcelas de R$ %.2f (total R$ %.2f)\n", n, parcela, parcela * n);
}

void programa_pagamento(void) {
    double total;
    char opcao;

    printf("Total gasto pelo cliente: R$ ");
    scanf("%lf", &total);

    opcao = escolher_opcao(total);
    if (opcao == 'a')
        pagamento_a_vista(total);
    else if (opcao == 'b')
        pagamento_duas_vezes(total);
    else
        pagamento_parcelado(total);
}

/* 7. Locações grátis (1 a cada 15 filmes) */
void locacoes_gratis(int A[500], int gratis[500]) {
    int i;
    for (i = 0; i < 500; i++)
        gratis[i] = A[i] / 15;
}

/* 8. Trocas na matriz 10x10 (enunciado conta de 1, C conta de 0) */
void trocar_matriz(int A[10][10]) {
    int i, j, aux;

    /* linha 2 com linha 8 */
    for (j = 0; j < 10; j++) {
        aux = A[1][j];
        A[1][j] = A[7][j];
        A[7][j] = aux;
    }
    /* coluna 4 com coluna 10 */
    for (i = 0; i < 10; i++) {
        aux = A[i][3];
        A[i][3] = A[i][9];
        A[i][9] = aux;
    }
    /* diagonal principal com secundária */
    for (i = 0; i < 10; i++) {
        aux = A[i][i];
        A[i][i] = A[i][9 - i];
        A[i][9 - i] = aux;
    }
    /* linha 5 com coluna 10 */
    for (j = 0; j < 10; j++) {
        aux = A[4][j];
        A[4][j] = A[j][9];
        A[j][9] = aux;
    }
}

/* 9. Soma das colunas na 61ª linha da matriz 61x10 */
void somar_colunas(int M[61][10]) {
    int i, j, soma;
    for (j = 0; j < 10; j++) {
        soma = 0;
        for (i = 0; i < 60; i++)
            soma += M[i][j];
        M[60][j] = soma;
    }
}

/* 10. Idade em anos, meses e dias */
int dias_do_mes(int mes, int ano) {
    int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
    if (mes == 2 && bissexto)
        return 29;
    return dias[mes - 1];
}

void calcular_idade(int dia, int mes, int ano) {
    time_t agora = time(NULL);
    struct tm *hoje = localtime(&agora);
    int d = hoje->tm_mday;
    int m = hoje->tm_mon + 1;
    int a = hoje->tm_year + 1900;

    int anos = a - ano;
    int meses = m - mes;
    int dias = d - dia;

    if (dias < 0) {
        meses--;
        int mes_anterior = (m == 1) ? 12 : m - 1;
        int ano_anterior = (m == 1) ? a - 1 : a;
        dias += dias_do_mes(mes_anterior, ano_anterior);
    }
    if (meses < 0) {
        anos--;
        meses += 12;
    }
    printf("Idade: %d anos, %d meses e %d dias\n", anos, meses, dias);
}

/* ---------- Testes ---------- */
int main(void) {
    int A[500], gratis[500], i, j;
    int mat[10][10], M[61][10];

    printf("%.2f\n", maior(3, 7));
    mostrar_mes(4);
    printf("%.2f\n", fahrenheit_para_celsius(212)); /* 100.00 */
    printf("%.2f\n", volume_cilindro(10, 2));
    printf("%.2f\n", volume_esfera(3));

    for (i = 0; i < 500; i++)
        A[i] = i % 50;
    locacoes_gratis(A, gratis);
    printf("%d %d %d\n", gratis[14], gratis[15], gratis[45]); /* 0 1 3 */

    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            mat[i][j] = i * 10 + j;
    trocar_matriz(mat);

    for (i = 0; i < 61; i++)
        for (j = 0; j < 10; j++)
            M[i][j] = 1;
    somar_colunas(M);
    printf("%d\n", M[60][0]); /* 60 */

    calcular_idade(15, 3, 2005);
    programa_pagamento();
    return 0;
}
