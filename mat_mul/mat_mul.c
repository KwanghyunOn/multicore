#include "mat_mul.h"

#include <pthread.h>

static float *A, *B, *C;
static int M, N, K;
static int num_threads;

static void* mat_mul_thread(void *data) {
  for (int i = 0; i < M; ++i) {
    for (int k = 0; k < K; ++k) {
      for (int j = 0; j < N; ++j) {
        C[i * N + j] += A[i * K + k] * B[k * N + j];
      }
    }
  }
  return NULL;
}

void mat_mul(float *_A, float *_B, float *_C, int _M, int _N, int _K, int _num_threads) {
  A = _A, B = _B, C = _C;
  M = _M, N = _N, K = _K;
  num_threads = _num_threads;

  pthread_t thread;
  pthread_create(&thread, NULL, mat_mul_thread, NULL);
  pthread_join(thread, NULL);
}
