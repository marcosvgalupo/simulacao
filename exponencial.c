#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// gcc exponencial.c -lm -o exponencial

double uniforme(){
    double u = rand() / ((double) RAND_MAX + 1);
    
    // u == 0 --> ln(0) <-- problema
    // limitando u entre (0,1]

    u = 1.0 -u;
    return u;
}

int main(){

    //Na exponencial, E[X] = 1/l
    double l;

    printf("Informe o tempo médio: ");
    scanf("%lF", &l);
    l = 1.0/l;


    // iniciando a sequencia pseudo aleatoria
    int semente = time(NULL); // o valor da semente varia
    srand(semente); // garante a geração de diferentes sequencias pseudo aleatorias


    double qtd_valores_gerados = 100000000;
    double soma = 0.0;


    for(int i = 0; i < qtd_valores_gerados; i++){
        double valor = (-1.0/l) * log(uniforme());
        // printf("%lF\n", valor);
        // getchar();
        soma += valor;
    }

    printf("Média dos valores gerados: %lF\n", (soma/qtd_valores_gerados));

    return 0;
}
