#include "stdafx.h"
#include "iostream"

#include "Headers/matr.h"
#include "Headers/Algorithm.h"

#define EXTERN

using namespace std;

// Вывод отладочной информации
void debugBlock() {
	// Входные данные
	cout << "\n-----------------------------DEBUG------------------------------\n\n";
	cout << "Vhodnie dannie: \n\n";

	cout << "Ax: " << A[0] << " Ay: " << A[1] << " Az: " << A[2] << endl;
	cout << "Wx: " << W[0] << " Wy: " << W[1] << " Wz: " << W[2] << endl;
	cout << "Psi_0: " << psi_0*57.3 << " Teta_0: " << teta_0*57.3 << " Gamma_0: " << gamma_0*57.3 << endl;


	cout << endl;

	cout << "fi_0: " << setprecision(10) << fi_0 << " la_0: " << setprecision(10) << la_0 << endl;

	cout << endl;

	// ----------------------------------------------------------------------------------------------------

	// Матрица перехода и проекции ускорений
	// Матрица перехода
	cout << "Brx matrix: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << Brx[i * 3 + j] << " ";
		cout << endl;
	}

	cout << endl;

	// Проекции ускорений на географическую ось
	cout << "Ag matrix: " << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << Ag[i] << " ";
	}

	cout << endl << endl;

	// ----------------------------------------------------------------------------------------------------

	// Ускорения относительноего движения
	cout << "Ax_g: " << Ag[0] << endl;
	cout << "Ay_g: " << Ag[1] << endl;
	cout << "Az_g: " << Ag[2] << endl;
	cout << endl;

	// ----------------------------------------------------------------------------------------------------


	// Проекции путевой скорости ЛА на оси геограической СК
	cout << "Vn_g: " << setprecision(10) << Vn_g << endl;
	cout << "Vup_g: " << setprecision(10) << Vup_g << endl;
	cout << "Ve_g: " << setprecision(10) << Ve_g << endl;
	cout << endl;

	// ----------------------------------------------------------------------------------------------------

	// Углы и координаты
	cout << "psi: " << psi*57.3 << endl;
	cout << "teta: " << teta*57.3 << endl;
	cout << "gamma: " << gamma*57.3 << endl;

	cout << endl;

	cout << "fi: " << setprecision(10) << fi*57.3 << endl;
	cout << "la: " << setprecision(10) << la*57.3 << endl;
	cout << endl;

	// Текущее время
	cout << "current_time: " << current_time << endl;

	cout << "\n-----------------------------------------------------------\n";

	// ----------------------------------------------------------------------------------------------------
}

// Блок начальной выставки
void initialBlock() {
	// Инициализируем матрицу направляющих косинусов
	Brx = getBrxMatr(psi, teta, gamma); // Георафическая -> приборная

	// Вычисляем составляющие путевой скорости в полусвободной в азимуте СК
	v[0] = Ve_g * cos(azm) - Vn_g * sin(azm);
	v[1] = Ve_g * sin(azm) + Vn_g * cos(azm);
	v[2] = Vup_g;

	vp[0] = Ve_g;
	vp[1] = Vn_g;
	vp[2] = Vup_g;

	// Вычисляем переносные угловые скорости
	Om[0] = -Vn_g * cos(azm) / Rn - Ve_g * sin(azm) / Re;
	Om[1] = -Vn_g * sin(azm) / Rn + Ve_g * cos(azm) / Re;
	Om[2] = 0;

	// Вычисляем проекции угловой скорости вращения Земли
	Ue[0] = -U * cos(fi) * sin(azm);
	Ue[1] = U * cos(fi) * cos(azm);
	Ue[2] = U * sin(fi);
}

// Решение задачи навигации
void navigationBlok() {
	// Записываем значнеия из файла в массивы
	A[0] = Axel.Ax;
	A[1] = Axel.Ay;
	A[2] = Axel.Az;

	W[0] = Gyro.Wx / 57.3;
	W[1] = Gyro.Wy / 57.3;
	W[2] = Gyro.Wz / 57.3;

	// Проецируем ускорения, полученные в приборной СК, в географическую СК
	mxTrans(Bxr, Brx, 3, 3); // Транспонируем матрицу направляющих косинусов
	VrMxMpy(Ag, Bxr, A, 3);  // Умножаем матрицу на столбец

	// Интегрирум полученные ускорения и расчитываем путевую скорость
	v[0] += ((Om[2] + 2 * Ue[2]) * vp[1] - (Om[1] + 2 * Ue[1]) * vp[2] + Ag[0]) * delta_t;
	v[1] += (-(Om[2] + 2 * Ue[2]) * vp[0] + (Om[0] + 2 * Ue[0]) * vp[2] + Ag[1]) * delta_t;
	v[2] += ((Om[1] + 2 * Ue[1]) * vp[0] - (Om[0] + 2 * Ue[0]) * vp[1] + Ag[2] - g) * delta_t;

	// Получаем координаты положения ЛА, интегрируя значения путевой скорости
	fi += Vn_g * delta_t / Re;
	if (fi < 89.99) {
		la += Ve_g * delta_t / (Re * cos(fi));
	}

	// Находим проекции путевой скорости ЛА на географичекую СК
	Ve_g = v[0] * cos(azm) + v[1] * sin(azm);
	Vn_g = -v[0] * sin(azm) + v[1] * cos(azm);
	Vup_g = v[2];

	// Рассчитываем проекции скорости вращени Земли на географическую СК
	Ue[0] = -U * cos(fi) * sin(azm);
	Ue[1] = U * cos(fi) * cos(azm);
	Ue[2] = U * sin(fi);

	// Рассчитываем сотовляющие отностительной угловой скорости
	Om[0] = -Vn_g * cos(azm) / Re - Ve_g * sin(azm) / Re;
	Om[1] = -Vn_g * sin(azm) / Rn - Ve_g * cos(azm) / Re;
	Om[2] = 0;
}

// Решение задачи ориентации
void orientationBlock() {
	// Вычисляется абсолютная угловая скорость географического трёхгранника 
	vrAddNew(Wabs, Om, Ue, 3);
	// перепроектируется в приборную систему координат
	VrMxMpy(Wabs_g, Brx, Wabs, 3);
	// Определяется скорость поворота приборной системы координат относительно географического трёхгранника
	vrSub(Ur, W, Wabs_g, 3);

	// Интегрируется кинематическое уравнение Пуассона для приборной системы координат
	fpoIntegrate(Brx, Ur, delta_t);

	// По элементам матрицы Brx вычисляются углы тангажа, крена и курса 
	teta = atan2(Brx[2], sqrt(Brx[5] * Brx[5] + Brx[8] * Brx[8]));
	gamma = atan2(-Brx[8], Brx[5]);
	psi = atan2(Brx[0], Brx[1]);

	//Перезаписываем значения предыдущих вычислений
	vp[0] = Ve_g;
	vp[1] = Vn_g;
	vp[2] = Vup_g;

	Ap[0] = A[0];
	Ap[1] = A[1];
	Ap[2] = A[2];

	Wp[0] = W[0];
	Wp[1] = W[1];
	Wp[2] = W[2];
}

// Управление работой программы
void algorithmControll() {
	// Выводит debug информацию на каждой 2^n * a итерации цикла
	
	if (show) {
		SetTextCurVisibility(false);
		// Psi
		SetTextCurPos(0, 0);
		cout << fixed << "psi:   ";
		SetTextCurPos(7, 0);
		cout << setprecision(5) << fixed << psi*57.3;
		SetTextCurPos(18, 0);
		cout << fixed << "[grad]";
		SetTextCurPos(25, 0);
		cout << setprecision(5) << fixed << psi;
		SetTextCurPos(35, 0);
		cout << fixed << "[rad]";
		// teta
		SetTextCurPos(0, 1);
		cout << fixed << "teta:  ";
		SetTextCurPos(7, 1);
		cout << setprecision(5) << fixed << teta*57.3;
		SetTextCurPos(18, 1);
		cout << fixed << "[grad]";
		SetTextCurPos(25, 1);
		cout << setprecision(5) << fixed << teta;
		SetTextCurPos(35, 1);
		cout << fixed << "[rad]";
		// Gamma
		SetTextCurPos(0, 2);
		cout << fixed << "gamma: ";
		SetTextCurPos(7, 2);
		cout << setprecision(5) << fixed << gamma*57.3;
		SetTextCurPos(18, 2);
		cout << fixed << "[grad]";
		SetTextCurPos(25, 2);
		cout << setprecision(5) << fixed << gamma;
		SetTextCurPos(35, 2);
		cout << fixed << "[rad]";

		SetTextCurPos(0, 4);
		cout << setprecision(10) << fixed << "fi: " << fi << endl;
		SetTextCurPos(0, 5);
		cout << setprecision(10) << fixed << "la: " << la << endl;

		SetTextCurPos(0, 7);
		cout << setprecision(10) << fixed << "fi_dot: " << Vn_g / Re << endl;
		SetTextCurPos(0, 8);
		cout << setprecision(10) << fixed << "la_dot: " << Ve_g / (Re * cos(fi)) << endl;

		SetTextCurPos(0, 10);
		cout << setprecision(15) << fixed << "Ax_g: " << Ag[0] << endl;
		SetTextCurPos(0, 11);
		cout << setprecision(15) << fixed << "Ay_g: " << Ag[1] << endl;
		SetTextCurPos(0, 12);
		cout << setprecision(15) << fixed << "Az_g: " << Ag[2] << endl;

		SetTextCurPos(0, 14);
		cout << setprecision(15) << fixed << "Vn_g: " << Vn_g << endl;
		SetTextCurPos(0, 15);
		cout << setprecision(15) << fixed << "Vup_g: " << Vup_g << endl;
		SetTextCurPos(0, 16);
		cout << setprecision(15) << fixed << "Ve_g: " << Ve_g << endl;

		SetTextCurPos(0, 18);
		cout << setprecision(15) << fixed << "Wx_g: " << Wg[0] << endl;
		SetTextCurPos(0, 19);
		cout << setprecision(15) << fixed << "Wy_g: " << Wg[1] << endl;
		SetTextCurPos(0, 20);
		cout << setprecision(15) << fixed << "Wz_g: " << Wg[2] << endl;

		SetTextCurPos(0, 22);
		cout << setprecision(3) << fixed << "Current time: " << current_time << " sec" << endl;
		SetTextCurPos(35, 22);
		cout << fixed << (int)current_time << "    " << (current_time > (int)current_time && current_time < (int)current_time + 2 * delta_t) ? true : false;
	}
	
	if (debug) {
		debugBlock();
	}

	if (tick && current_time > debug_time) {
		cout << current_time << endl;
		debug = true;
		system("pause");
		debug_time *= 2;
	}

	// Вывод debug инфорации каждые 2^n * 100 секунд
	if (tick && debug) {
		debug = false;
	}

	// Пауза на каждой итерации цикла
	if (pause) {
		system("pause");
	}

	// Задержка на каждой итерации цикла
	if (delay) {
		Sleep(delay_time);
	}
}