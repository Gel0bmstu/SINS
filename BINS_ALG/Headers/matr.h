#pragma once

#include "Vars.h"
#include "Settings.h"

//---------------------------------------------------------------------------
// Инициализация массивов: Dest[i] = Val
template <typename TD>
void vrSet(TD *Dest, TD Value, int Size)
{
	while (Size--)  *Dest++ = Value;
}


//---------------------------------------------------------------------------
// Поэлементное копирование массивов: Dest[i] = Src[i]
template <typename TD, typename TS>
void vrSet(TD *Dest, TS* Src, int Size)
{
	while (Size--)  *Dest++ = (TD)(*Src++);
}




//---------------------------------------------------------------------------
// Поэлементное увеличение массива на константу: Dest[i] += Value
template <typename TD, typename TV>
void vrAdd(TD *Dest, TV Value, int Size)
{
	while (Size--)  *Dest++ += (TD)(Value);
}


//---------------------------------------------------------------------------
// Поэлементное увеличение массива на константу с занесением результата в отдельный массив:
// Dest[i]  = Src[i] + Value
template <typename TD, typename TS, typename TV>
void vrAdd(TD *Dest, TS *Src, TV Value, int Size)
{
	while (Size--)  *Dest++ = (TD)(*Src++ + Value);
}


//---------------------------------------------------------------------------
// Поэлементное сложение массивов: Dest[i] += Src[i]
template <typename TD, typename TS>
void vrAdd(TD *Dest, TS *Src, int Size)
{
	while (Size--)  *Dest++ += (TD)(*Src++);
}

//---------------------------------------------------------------------------
// Поэлементное сложение массивов с записью в другой массив: Dest[i] = Src1[i] + Src2[i]
template <typename TD, typename TS>
void vrAddNew(TD *Dest, TS *Src1, TS *Src2, int Size)
{
	while (Size--)  *Dest++ = (TD)(*Src1++) + (TD)(*Src2++);
}


//---------------------------------------------------------------------------
// Поэлементное уменьшение массива на константу: Dest[i] -= Value
template <typename TD, typename TV>
void vrSub(TD *Dest, TV Value, int Size)
{
	while (Size--)  *Dest++ -= (TD)(Value);
}


//---------------------------------------------------------------------------
// Поэлементное уменьшение массива на константу с занесением результата в отдельный массив:
// Dest[i]  = Src[i] - Value
template <typename TD, typename TS, typename TV>
void vrSub(TD *Dest, TS *Src, TV Value, int Size)
{
	while (Size--)  *Dest++ = (TD)(*Src++ - Value);
}


//---------------------------------------------------------------------------
// Поэлементное вычитание массивов: Dest[i] -= Src[i]
template <typename TD, typename TS>
void vrSub(TD *Dest, TS *Src, int Size)
{
	while (Size--)  *Dest++ -= (TD)(*Src++);
}




//---------------------------------------------------------------------------
// Поэлементное вычитание массивов с занесением результата в отдельный массив:
// Dest[i] = Left[i] - Right[i]
template <typename TD, typename TL, typename TR>
void vrSub(TD *Dest, TL *Left, TR *Right, int Size)
{
	while (Size--)  *Dest++ = (TD)(*Left++ - *Right++);
}


//---------------------------------------------------------------------------
// Поэлементное умножение массива на константу: Dest[i] *= Value
template <typename TD, typename TV>
void vrMpy(TD *Dest, TV Value, int Size)
{
	while (Size--)  *Dest++ *= (TD)(Value);
}


//---------------------------------------------------------------------------
// Умножение матриц: Dest[lr,rc] = Left[lr,lc] * Right[rr,rc]
void mxMpy(double *Dest, double *Left, double *Right, int lr, int lc_rr, int rc)
{
	int lo = 0;

	FOR(r, lr)               // = dr
	{
		double *pL = Left + lo;
		FOR(c, rc)           // = dc
		{
			double *pR = Right + c;
			*Dest = 0;
			FOR(i, lc_rr)
			{
				*Dest += (double)((*pL++) * (*pR));
				pR += rc;
			}
			Dest++;
			pL -= lc_rr;
		}
		lo += lc_rr;
	}
}

//---------------------------------------------------------------------------
// Создание единичной квадратной матрицы
template <typename TD>
void mxEdinich(TD *Mx, int Rows)
{
	FOR(i, Rows*Rows) {
		if (i % (Rows + 1) == 0) {
			Mx[i] = 1;
		}
		else {
			Mx[i] = 0;
		}
	}
}


//---------------------------------------------------------------------------
// Транспонирование векторов и матриц: Dest = Src'T
template <typename TD, typename TS>
void mxTrans(TD *Dest, TS *Src, int Rows, int Cols)
{
	FOR(r, Rows)
	{
		TD* pD = Dest + r;
		FOR(c, Cols)
		{
			*pD = (TD)(*Src++);
			pD += Rows;
		}
	}
}

// Умножение столбца на матрицу (Res[s, 1] = Mx[s, s] * Vr[s, 1]):
template <typename T>
void VrMxMpy(T* r, T* m, T* v, int s) {

	FOR(i, s) {
		r[i] = 0.0;
		FOR(j, s) {
			r[i] += m[i * s + j] * v[j];
		}
	}
}
