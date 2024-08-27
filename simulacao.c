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

double gera_tempo(double l){
    return (-1.0/l) * log(uniforme());
}

double min(double n1, double n2){
    if(n1 < n2) return n1;
    return n2;
}


int main(){

    double parametro_chegada, parametro_saida;

    printf("Informe o tempo médio: ");
    scanf("%lF", &parametro_chegada);
    parametro_chegada = 1.0/parametro_chegada;

    printf("Informe o tempo médio de atendimento: ");
    scanf("%lF", &parametro_saida);
    parametro_saida = 1.0/parametro_saida;

    double tempo_simulacao;
    printf("\nInforme o tempo de simulacao: ");
    scanf("%lF", &tempo_simulacao);

    double tempo_decorrido = 0.0;
    double tempo_chegada = gera_tempo(parametro_chegada);
    double tempo_saida = DBL_MAX;

    unsigned long int fila = 0;

    while(tempo_decorrido <= tempo_simulacao){
        tempo_decorrido = min(tempo_chegada, tempo_saida);

        //chegada
        if(tempo_decorrido == tempo_chegada){
            //sistema ocioso
            if(!fila){
                tempo_saida = tempo_decorrido + gera_tempo(parametro_saida);
            }            
            fila++;

            tempo_chegada = tempo_decorrido + gera_tempo(parametro_chegada);
        } else{
            fila--;
            tempo_saida = DBL_MAX;
            if(fila){
                tempo_saida = tempo_decorrido + gera_tempo(parametro_saida);
            }    
        }
    }

    return 0;
}