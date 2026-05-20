/*
 * normal.c
 *
 *  Created on: 2026/05/19
 *      Author: Students of Introduction Lectures on Special Subjects
 */

#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

/* 行列サイズ */
#define N 512

double** alloc_matrix(int n);
void make_matrix(double **a, double **b, int n);
void check_matrix(double **c, int n);

int main(int argc, char *argv[]) {
	/* 変数宣言 */
	int i, j, k; /* 行列成分の添字 */
	double **a, **b, **c, **tb; /* 行列 A, B, C tB */
	clock_t t0, t1; /* 時間計測用 */

	a = alloc_matrix(N);
	b = alloc_matrix(N);
	c = alloc_matrix(N);
	tb = alloc_matrix(N);
	make_matrix(a, b, N);

	t0 = clock();
	for (i = 0; i < N; i++) { /* 行列の乗算を計算 */
		for (j = 0; j < N; j++) {
			c[i][j] = 0.0;
			for (k = 0; k < N; k++) {
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	t1 = clock();

	check_matrix(c, N);
	printf("計算時間は %.3f 秒です．\n", (double) (t1 - t0) / CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}

double** alloc_matrix(int n) {
	double **m;
	int i;

	m = (double**) malloc(n * sizeof(double*));
	m[0] = (double*) malloc(n * n * sizeof(double));
	for (i = 1; i < n; i++) {
		m[i] = &m[0][i * n];
	}
	return m;
}

void make_matrix(double **a, double **b, int n) {
	int i, j;

	printf("次数 %d の行列の積を計算します．\n", n);

	for (i = 0; i < n; i++) { /* 行列 A,B の成分を設定 */
		for (j = 0; j < n; j++) {
			a[i][j] = (double) (i + 2) / (double) (j + 1);
			b[i][j] = (double) (i + 1) / (double) (j + 2);
		}
	}
	return;
}

void check_matrix(double **c, int n) {
	int i, j;
	double sum = 0.0, error;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sum = sum
					+ fabs(c[i][j] - (double) ((i + 2) * n) / (double) (j + 2));
		}
	}
	error = sum / (double) (n * n);
	printf("誤差の平均絶対値：%.3e\n", error);

	return;
}
