#include "stdafx.h"
#include "iostream"

#include "Headers/matr.h"
#include "Headers/MatrixFuncs.h"

using namespace std;

// Матрица ориентации, связывающуя географическую полусвободную в азимуте и приборную систему координат
double* getBrxMatr(double p, double t, double gam) {
	double *m = new double[9];

	m[0] = sin(p) * cos(t);                                m[1] = cos(p) * cos(t);                                 m[2] = sin(t);
	m[3] = cos(p) * sin(gam) - sin(p) * sin(t) * cos(gam); m[4] = -sin(p) * sin(gam) - cos(p) * sin(t) * cos(gam); m[5] = cos(t) * cos(gam);
	m[6] = cos(p) * cos(gam) + sin(p) * sin(t) * sin(gam); m[7] = -sin(p) * cos(gam) + cos(p) * sin(t) * sin(gam); m[8] = -cos(t) * sin(gam);

	return m;
}

// Транспонированная матрица ориентации: проиборная -> полусвободная в азимуте
double* getBxrMatr(double p, double t, double gam) {
	double *rx = getBrxMatr(p, t, gam);
	double *xr = new double[9];

	mxTrans(xr, rx, 3, 3);

	return xr;
}

// Формирование кососимметрической матрицы
void skewMx(double Mx[9], double Vr[3])
{
	Mx[0] = 0;       Mx[1] = Vr[2];   Mx[2] = -Vr[1];
	Mx[3] = -Vr[2];  Mx[4] = 0;       Mx[5] = Vr[0];
	Mx[6] = Vr[1];   Mx[7] = -Vr[0];  Mx[8] = 0;
}

// Интегрирование кинематического уравнения Пуасона
void fpoIntegrate(double* m, double* w, double dt) {
	double* E = new double[9];
	double* tmp = new double[9];
	double* res = new double[9];
	double* ws = new double[9];
	double* ws2 = new double[9];	

	mxEdinich(E, 3);
	skewMx(ws, w);
	mxMpy(ws2, ws, ws, 3, 3, 3);


	for (int i = 0; i < 9; i++) {
		tmp[i] = E[i] + ws[i] * dt + 0.5 * dt * ws2[i];
	}

	mxMpy(res, tmp, m, 3, 3, 3);

	vrSet(m, res, 9);
}
