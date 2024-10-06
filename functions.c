#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char floresta[N][M];
pthread_mutex_t mutex_floresta[N][M];

void inicializar_floresta() {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            floresta[i][j] = (rand() % 2 == 0) ? SENSOR : LIVRE;
            pthread_mutex_init(&mutex_floresta[i][j], NULL);
        }
    }
}

void* sensor_func(void* arg) {
    int x = ((int*)arg)[0];
    int y = ((int*)arg)[1];
    free(arg);

    while (1) {
        pthread_mutex_lock(&mutex_floresta[x][y]);
        if (floresta[x][y] == FOGO) {
            printf("Sensor em (%d, %d) detectou fogo!\n", x, y);
            if (x == 0 || x == N-1 || y == 0 || y == M-1) {
                central_func(x, y);
            } else {
                notificar_vizinhos(x, y);
            }
        }
        pthread_mutex_unlock(&mutex_floresta[x][y]);
        usleep(100000);
    }
}

void notificar_vizinhos(int x, int y) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
            pthread_mutex_lock(&mutex_floresta[nx][ny]);
            if (floresta[nx][ny] == SENSOR) {
                floresta[nx][ny] = FOGO;
                printf("Fogo se espalhou para (%d, %d)\n", nx, ny);
            }
            pthread_mutex_unlock(&mutex_floresta[nx][ny]);
        }
    }
}

void central_func(int x, int y) {
    printf("Central: Fogo detectado na borda em (%d, %d)\n", x, y);
    combate_fogo(x, y);
}

void combate_fogo(int x, int y) {
    pthread_mutex_lock(&mutex_floresta[x][y]);
    if (floresta[x][y] == FOGO) {
        floresta[x][y] = QUEIMADO;
        printf("Fogo controlado em (%d, %d)\n", x, y);
    }
    pthread_mutex_unlock(&mutex_floresta[x][y]);
}

void* gerador_incendios(void* arg) {
    while (1) {
        sleep(3);

        int x = rand() % N;
        int y = rand() % M;

        pthread_mutex_lock(&mutex_floresta[x][y]);
        if (floresta[x][y] == SENSOR) {
            floresta[x][y] = FOGO;
            printf("Incêndio iniciado em (%d, %d)\n", x, y);
        }
        pthread_mutex_unlock(&mutex_floresta[x][y]);
    }
}

void exibir_floresta() {
    printf("Estado atual da floresta:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c ", floresta[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
