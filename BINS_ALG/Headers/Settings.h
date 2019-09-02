#pragma once

#include "iostream"
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <Windows.h>

char *ru(const char *Str);

#define SUCCESS 1
#define ERROR 0
#define ERRORS 1

#define omega_shullera 1.2383e-3 // ����� ������� [���/���]
#define Re 6378136 // ������ ����� [�] 
#define Rn 6356800
#define R 6378136
#define U 7.292115e-5 // �������� �������� ����� [���/���]
#define U_deg 0.00416667 // �������� ������� ����� [����/���]
#define g 9.8066 // ��������� ���������� ������� [�/���^2]
#define pi 3.14159256

#define FOR( i,N) for (int i=0; i<(N); i++)

using namespace std;