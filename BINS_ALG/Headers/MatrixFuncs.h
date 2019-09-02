#pragma once

#include "../Include/MatrixFuncs.cpp"

double* teta_povorot(double angle);
double* gamma_povorot(double angle);
double* psi_povorot(double angle);
double* matr_perehoda(double* first_povorot, double* second_povorot, double* third_povorot);
double* myPuasonIntegrate(double* C, double* W, double* Wg, double dt);
void fpoIntegrate(double* m, double* w, double dt);


void skewMx(double Mx[9], double Vr[3]);

void ortonormMx(double* m);

double* getBrxMatr(double p, double t, double gam);
double* getBxrMatr(double p, double t, double gam);

double* getBnxMatr(double l, double a, double f);
double* getBxnMatr(double l, double a, double f);