#include "functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    pthread_t sensores[N][M];
    pthread_t thread_geradora;

    inicializar_floresta();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int* pos = malloc(2 * sizeof(int));
            pos[0] = i;
            pos[1] = j;
            pthread_create(&sensores[i][j], NULL, sensor_func, pos);
        }
    }

    pthread_create(&thread_geradora, NULL, gerador_incendios, NULL);

    while (1) {
        sleep(5);
        exibir_floresta();
    }

    pthread_join(thread_geradora, NULL);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            pthread_join(sensores[i][j], NULL);
        }
    }

    return 0;
}
