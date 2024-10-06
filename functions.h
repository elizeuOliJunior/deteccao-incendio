#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>

#define N 30
#define M 30

#define LIVRE '-'
#define SENSOR 'T'
#define FOGO '@'
#define QUEIMADO '/'

void inicializar_floresta();
void* sensor_func(void* arg);
void* gerador_incendios(void* arg);
void central_func(int x, int y);
void combate_fogo(int x, int y);
void notificar_vizinhos(int x, int y);
void exibir_floresta();

extern pthread_mutex_t mutex_floresta[N][M];

extern char floresta[N][M];

#endif
