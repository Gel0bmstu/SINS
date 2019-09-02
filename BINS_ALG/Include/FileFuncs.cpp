#include "Headers/FileFunc.h"
#include "Headers/Settings.h"
#include "Headers/Vars.h"

#define EXTERN
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

// -------------------------------------------------------------------------------------------------------

// Вспомогательный блок функций для algorithmControll()

// Вывод данных в консоль на одной строке

double
z;
HANDLE
myConsole;

// Установка каретки консоли в нужное положение
void SetTextCurPos(short col, short row) {
	myConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coor;
	Coor.X = col; Coor.Y = row;
	SetConsoleCursorPosition(myConsole, Coor);
}

// Включить / Выключить видимость каретки
void SetTextCurVisibility(bool vsbl) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 2; info.bVisible = vsbl;
	SetConsoleCursorInfo(myConsole, &info);
}

// -------------------------------------------------------------------------------------------------------


// Функция пропуска строки
int skipLine(FILE **pFile)
{
    char Symb;

    for (; ;)
    {
        if (fscanf_s(*pFile, "%c", &Symb, 1) != 1)
            return ERROR;                   // ��������� ����� �����

        if (Symb == '\n')
            return SUCCESS;                 // ����� ������ ������
    }
}
//--------------------------------------------------------------------

// Чтение айла с данными БЧЭ
double readFile() {
    double time;
    int num = fscanf_s(Source, "%lf %lf %lf %lf %lf %lf %lf %*lf",
        &time,
        &Axel.Ax, &Axel.Ay, &Axel.Az,
        &Gyro.Wx, &Gyro.Wy, &Gyro.Wz);

    return time;
}
//--------------------------------------------------------------------

// Получение значнеий проекций путеой скорости ЛА на географическую СК
void getVels() {
	int num = fscanf_s(Vels, "%lf %lf %lf %lf %lf",
		&V.fi, &V.la, &V.Vn, &V.Vup, &V.Ve);
}
//--------------------------------------------------------------------

// Открытие / Создание файлов, для чтения / записи данных
void filePreparation() {
	// Файл с кратким результатом работы алгоритма
	fopen_s(&result, "res.dat", "w+");
	fprintf(result, "  TIME            psi         teta       gamma      fi         la\n");

	// Файл с плным результатом, удобный для отладки
	fopen_s(&Debug, "debug.dat", "w+");
	fprintf(Debug, "  TIME            psi         teta       gamma      fi         la         azm        Ax_x         Ay_x         Az_x        Ax_g         Ay_g         Az_g         Vn_g         Vup_g         Ve_g         Wx_g         Wy_g         Wz_g\n");

	// Исходный файл с данными БЧЭ
	fopen_s(&Source, "IMU_Il.dat", "r");
	skipLine(&Source);

	// Файл со скоростями, полученными с БЧЭ
	fopen_s(&Vels, "vel.txt", "r");
	skipLine(&Vels);

	skipLine(&Source);
	skipLine(&Vels);
}
//--------------------------------------------------------------------

// Запись результата работы алгоритма в файлы res.dat и debug.dat
void writeFile() {
	if (record && (current_time > (int)current_time && current_time < (int)current_time + 2 * delta_t)) {
		fprintf(result, "  %lf        %.10lf    %.10lf    %.10lf   %.10lf    %.10lf\n",
			current_time, psi*57.3, teta*57.3, gamma*57.3, fi*57.3, la*57.3);
	}

	if (record && (current_time >(int)current_time && current_time < (int)current_time + 2 * delta_t)) {
		fprintf(Debug, "  %lf        %.10lf    %.10lf    %.10lf   %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf    %.10lf\n",
			current_time, psi*57.3, teta*57.3, gamma*57.3, fi*57.3, la*57.3, azm*57.3, A[0], A[1], A[2], Ag[0], Ag[1], Ag[2], Vn_g, Vup_g, Ve_g, Om[0] * 57.3, Om[1] * 57.3, Om[2] * 57.3);
	}
}
//--------------------------------------------------------------------

