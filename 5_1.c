#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define N 512

void init_matrix(float* mat) {
    for (int i = 0; i < N * N; i++) {
        float random_0_to_1 = (float)rand() / RAND_MAX;
        mat[i] = 1.0f + random_0_to_1 * 90.0f;
    }
}

void save_full_matrix(const char* filename, float* mat) {
    printf("Сохранение полной матрицы в файл %s \n", filename);
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf(" не удалось создать файл \n");
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(f, "%.5g ", mat[i * N + j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    printf(" файл успешно сохранён \n");
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    float* A = (float*)malloc(N * N * sizeof(float));
    float* B = (float*)malloc(N * N * sizeof(float));
    float* C = (float*)malloc(N * N * sizeof(float));

    if (!A || !B || !C) {
        printf(" ошибка выделения памяти \n");
        return 1;
    }

    srand(0);
    init_matrix(A);
    init_matrix(B);

    printf("Начинаем умножение %dx%d \n", N, N);

    clock_t start = clock();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0.0f;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Время выполнения: %.6f сек\n", time_spent);

    save_full_matrix("result_1.txt", C);

    free(A); free(B); free(C);
    return 0;
}