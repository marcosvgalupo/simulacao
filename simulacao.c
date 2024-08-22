#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

// gcc exponencial.c -lm -o exponencial

double uniforme(){
    double u = rand() / ((double) RAND_MAX + 1);
    
    // u == 0 --> ln(0) <-- problema
    // limitando u entre (0,1]

    u = 1.0 -u;
    return u;
}

double gera_chegada(double l){
    return (-1.0/l) * log(uniforme());
}

double min(double n1, double n2){
    if(n1 < n2) return n1;
    return n2;
}


int main(){

    double l;

    printf("Informe o tempo médio: ");
    scanf("%lF", &l);
    l = 1.0/l;

    double tempo_simulacao;
    printf("\nInforme o tempo de simulacao: ");
    scanf("%lF", &tempo_simulacao);

    double tempo_decorrido = 0.0;
    double tempo_chegada = gera_chegada(l);
    double tempo_saida = DBL_MAX;

    while(tempo_decorrido <= tempo_simulacao){
        tempo_decorrido = min(tempo_chegada, tempo_saida);

        if(tempo_decorrido == tempo_chegada){
            
        } else{

        }
    }





    return 0;
}