#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

// gcc exponencial.c -lm -o exponencial

typedef struct{
    unsigned long int num_eventos;
    double tempo_anterior;
    double soma_areas;
}little;


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

void inicia_little(little *l){
    l->num_eventos = 0;
    l->soma_areas = 0.0;
    l->tempo_anterior = 0.0;
}

int main(){

    int semente = time(NULL);
    srand(semente);

    double parametro_chegada, parametro_saida;

    printf("Informe o tempo médio entre as chegadas (segundos): ");
    scanf("%lF", &parametro_chegada);
    parametro_chegada = 1.0/parametro_chegada;

    printf("Informe o tempo médio de atendimento (segundos): ");
    scanf("%lF", &parametro_saida);
    parametro_saida = 1.0/parametro_saida;

    double tempo_simulacao;
    printf("Informe o tempo de simulacao (segundos): ");
    scanf("%lF", &tempo_simulacao);

    double tempo_decorrido = 0.0;
    double tempo_chegada = gera_tempo(parametro_chegada);
    double tempo_saida = DBL_MAX;

    unsigned long int fila = 0;
    unsigned long int fila_max = 0;
    
    double soma_ocupacao = 0.0;

    /**
     * variacoes de little
     */
    little en;
    little ew_chegadas;
    little ew_saidas;

    inicia_little(&en);
    inicia_little(&ew_chegadas);
    inicia_little(&ew_saidas);



    while(tempo_decorrido <= tempo_simulacao){
        tempo_decorrido = min(tempo_chegada, tempo_saida);

        //chegada
        if(tempo_decorrido == tempo_chegada){
            //sistema ocioso
            if(!fila){
                tempo_saida = tempo_decorrido + gera_tempo(parametro_saida);

                soma_ocupacao += tempo_saida - tempo_decorrido;
            }            
            fila++;
            fila_max = fila > fila_max ? fila : fila_max;
            tempo_chegada = tempo_decorrido + gera_tempo(parametro_chegada);
            
            /**
             * little
             */
            en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos; //tempo decorrido == tempo atual
            en.num_eventos++;
            en.tempo_anterior = tempo_decorrido;

            ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos; //tempo decorrido == tempo atual
            ew_chegadas.num_eventos++;
            ew_chegadas.tempo_anterior = tempo_decorrido;
        } else{
            fila--;
            tempo_saida = DBL_MAX;
            if(fila){
                tempo_saida = tempo_decorrido + gera_tempo(parametro_saida);
                soma_ocupacao += tempo_saida - tempo_decorrido;
            }
            /**
             * little
             */
            en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos; //tempo decorrido == tempo atual
            en.num_eventos--;
            en.tempo_anterior = tempo_decorrido;

            ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos; //tempo decorrido == tempo atual
            ew_saidas.num_eventos++;
            ew_saidas.tempo_anterior = tempo_decorrido;    
        }
    }

    printf("\n========== RESULTADOS =============");
    printf("\nMaior tamanho de fila alcancado: %ld\n", fila_max);
    printf("Tempo de ocupacao: %lF\n", soma_ocupacao/tempo_decorrido);

    double en_final = en.soma_areas/tempo_decorrido;
    double ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos; 
    double lambda = ew_chegadas.num_eventos/tempo_decorrido; // quantas pessoas chegam por unidade de tempo

    printf("E[N]: %lF\n", en_final);
    printf("E[W]: %lF\n", ew_final);
    printf("Erro de Little: %lF\n", en_final - lambda * ew_final);
    return 0;
}