#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _MSC_VER
#include <malloc.h>
#else
#include <mm_malloc.h>
#endif

#define N 512


void init_matrix(float* mat) {
    for (int i = 0; i < N * N; i++) {
        float random_0_to_1 = (float)rand() / RAND_MAX;
        mat[i] = 1.0f + random_0_to_1 * 9.0f;
    }
}


void save_full_matrix(const char* filename, float* mat) {
    printf("Сохранение полной матрицы в файл %s \n", filename);
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Не удалось создать файл\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(f, "%.5f ", mat[i * N + j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Файл успешно сохранен.\n");
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    float* A = (float*)_mm_malloc(N * N * sizeof(float), 32);
    float* B = (float*)_mm_malloc(N * N * sizeof(float), 32);
    float* C = (float*)_mm_malloc(N * N * sizeof(float), 32);

    if (!A || !B || !C) {
        printf("Ошибка выделения памяти \n");
        return 1;
    }

    srand(0);
    init_matrix(A);
    init_matrix(B);

    for (int i = 0; i < N * N; i++) C[i] = 0.0f;
    printf("Начинаем умножение %dx%d \n", N, N);

    clock_t start = clock();

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            __m256 vecA = _mm256_set1_ps(A[i * N + k]);

            for (int j = 0; j < N; j += 8) {
                __m256 vecB = _mm256_load_ps(&B[k * N + j]);

                __m256 vecC = _mm256_load_ps(&C[i * N + j]);

                vecC = _mm256_fmadd_ps(vecA, vecB, vecC);

                _mm256_store_ps(&C[i * N + j], vecC);
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Время выполнения: %.6f сек\n", time_spent);

    save_full_matrix("result_2.txt", C);

    _mm_free(A); _mm_free(B); _mm_free(C);
    return 0;
}