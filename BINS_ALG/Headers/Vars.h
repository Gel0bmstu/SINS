#pragma once

#ifndef VARS_H
#define VARS_H

#ifndef EXTERN
#define EXTERN      extern
#endif

#include "stdio.h"
//#include "Headers/matr.h"

struct Axel_data {
    double Ax;
    double Ay;
    double Az;
};

struct g_Axel {
    double Agx;
    double Agy;
    double Agz;
};

struct Gyro_data {
    double Wx;
    double Wy;
    double Wz;
};

struct g_Gyro {
    double Wgx;
    double Wgy;
    double Wgz;
};

struct Ang {
	double psi;
	double teta;
	double gamma;
};

struct Vel {
	double Vn;
	double Ve;
	double Vup;
	double fi;
	double la;
};

// ����������� ������� ��������
EXTERN Ang Angls;
EXTERN Vel V;
EXTERN Axel_data Axel;
EXTERN Gyro_data Gyro;

// ����������� ��������� �� �����
EXTERN FILE *result;
EXTERN FILE *Source;
EXTERN FILE *Vels;
EXTERN FILE *Debug;

// ������������� "������� ������"

// ��������� ������
EXTERN double current_time;
EXTERN double delta_t = 0.0025; // 0.0025 - 400 ��

						 // ���� ����������
EXTERN double psi = -119.311523 / 57.3; // rad
EXTERN double teta = 2.50546 / 57.3; // rad
EXTERN double gamma = 0.14229 / 57.3; // rad

EXTERN double fi = 55.68885 / 57.3; // rad
EXTERN double la = 38.84487 / 57.3; // rad

							 // ��������� ������ ������������� �� 
EXTERN double azm = 0; // rad

EXTERN double h = 150; // [�]

				// �������� �������� � ���� OgXgYgZg (�������������� ��)
EXTERN double Vn_g = -8.03819466e-5;
EXTERN double Vup_g = 6.02864599e-5;
EXTERN double Ve_g = -0.00140668406;

// ��������� �������� ���������, ��������� � ����� (� ���� ���������� 
// ��������� ��� �������� �� ��������)
EXTERN double fi_0 = fi;
EXTERN double la_0 = la;

EXTERN double psi_0 = psi;
EXTERN double teta_0 = teta;
EXTERN double gamma_0 = gamma;

// ������, ���������� � ��� ���������� (�� ����� IMU_Il.dat)
EXTERN double *A = new EXTERN double[3]; // ��������� � �����
EXTERN double *W = new EXTERN double[3]; // ������� �������� � ����������

						   // ��������, ����������� �� ��������� ���� ������ ���������
EXTERN double *Ap = new double[3];
EXTERN double *Wp = new double[3];

EXTERN double *Om = new double[3];

// ---------------------------------------------------------------------------------------------------

// ������������ ������� �������� � ������������� � ������� ��
EXTERN double *v = new double[3];

// ����������� ������

// ������� ��������� ��, ��������������� � �������������� ��
// �� ������� ����� "�������" ������������ ���������
EXTERN double* Ax = new double[3];

// ������� ��������� � ��������� � �������������� ��
EXTERN double* Ag = new double[3];
EXTERN double* Wg = new double[3];

EXTERN double* Wx = new double[3];
EXTERN double* Ue = new double[3];

// ������� ������������ ���������
EXTERN double* Brx = new double[9];
EXTERN double* Bxr = new double[9];

EXTERN double* Wabs = new double[3];
EXTERN double* Wabs_g = new double[3];

EXTERN double* Ur = new double[3];

EXTERN double *vp = new double[3];

// ��������, ����������, ������� ������ ������ ��������� ��������
EXTERN double debug_time = 50;

// ����� ���������� ���������� (������� � BINS_ALG.cpp)
EXTERN bool debug;
EXTERN bool show;
EXTERN bool pause;
EXTERN bool delay;
EXTERN bool tick;
EXTERN bool record;

EXTERN int delay_time = 5;
// ---------------------------------------------------------------------------------------------------------------------------------------
#endif