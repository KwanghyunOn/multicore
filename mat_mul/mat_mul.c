#include "mat_mul.h"

#include <pthread.h>
#include <stdio.h>

#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

static float *A, *B, *C;
static int M, N, K;
static int num_threads;

int ib = 64, kb = 48;

typedef struct Tdata {
	int is, ie;
} Tdata;

static void* mat_mul_thread(void *data) {
	Tdata* td = (Tdata*)data;
	int is = td->is, ie = td->ie;
	for(int ii = is; ii < ie; ii += ib) {
		for(int kk = 0; kk < K; kk += kb) {
			for(int k = kk; k < min(K, kk + kb); k++) {
				for(int i = ii; i < min(ie, ii + ib); i++) {
					for(int j = 0; j < N; j++) {
						C[i * N + j] += A[i * K + k] * B[k * N + j];
					}
				}
			}
		}
	}
	return NULL;
}

void mat_mul(float *_A, float *_B, float *_C, int _M, int _N, int _K, int _num_threads) {
	A = _A, B = _B, C = _C;
	M = _M, N = _N, K = _K;
	num_threads = _num_threads;

	Tdata td[num_threads];
	for(int i = 0; i < num_threads; i++) {
		td[i].is = M / num_threads * i + min(i, M % num_threads);
		td[i].ie = M / num_threads * (i+1) + min(i+1, M % num_threads);
	}

	pthread_t threads[num_threads];
	for(int i = 0; i < num_threads; i++)
		pthread_create(&threads[i], NULL, mat_mul_thread, &td[i]);
		
	for(int i = 0; i < num_threads; i++)
		pthread_join(threads[i], NULL);
}
