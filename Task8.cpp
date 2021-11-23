#include <iostream>
#include <cmath>
#include <iomanip>
#include "Nmeth.h"

const int X = 0;
const int Y = 1;
const int H = 2;
const int A = 3;
const int B = 4;
const int C = 5;
const int D = 6;

#define puk cout << "Пук пук пук";

using namespace std;

namespace T8
{
	void cbSpline(double** arrPtr, int nPt)
	{
		arrPtr[H][0] = 0;
		for (int i = 0; i < nPt - 1; i++)
		{
			arrPtr[H][i + 1] = arrPtr[X][i + 1] - arrPtr[X][i];
			//cout << arrPtr[H][i + 1] << "   ";
		}

		double** arrCPtr = new double* [nPt - 2];
		for (int i = 0; i < nPt - 2; i++)
			arrCPtr[i] = new double[nPt - 1];
		for (int i = 0; i < nPt - 2; i++)
			for (int j = 0; j < nPt - 1; j++)
				arrCPtr[i][j] = 0;
		
		// Составление матрицы для нахождения Cn
		for (int i = 0; i < nPt - 2; i++)
		{
			if (i != 0 && i != nPt - 3)
			{
				arrCPtr[i][i - 1] = arrPtr[H][i];
				arrCPtr[i][i] = 2 * (arrPtr[H][i] + arrPtr[H][i + 1]);
				arrCPtr[i][i + 1] = arrPtr[H][i + 2];
				arrCPtr[i][nPt - 2] = 3 * ((arrPtr[Y][i + 2] - arrPtr[Y][i + 1]) / arrPtr[H][i + 1] - (arrPtr[Y][i + 1] - arrPtr[Y][i]) / arrPtr[H][i]);
			}
			else if (i == 0)
			{
				arrCPtr[i][i] = 2 * (arrPtr[H][i + 1] + arrPtr[H][i + 2]);
				arrCPtr[i][i + 1] = arrPtr[H][i + 2];
				arrCPtr[i][nPt - 2] = 3 * ((arrPtr[Y][i + 2] - arrPtr[Y][i + 1]) / arrPtr[H][i + 2] - (arrPtr[Y][i + 1] - arrPtr[Y][i]) / arrPtr[H][i + 1]);
			}
			else
			{
				arrCPtr[i][i - 1] = arrPtr[H][i];
				arrCPtr[i][i] = 2 * (arrPtr[H][i] + arrPtr[H][i + 1]);
				arrCPtr[i][nPt - 2] = 3 * ((arrPtr[Y][i + 2] - arrPtr[Y][i + 1]) / arrPtr[H][i + 1] - (arrPtr[Y][i + 1] - arrPtr[Y][i]) / arrPtr[H][i]);
			}
		}
		//printArray(arrCPtr, nPt - 2, nPt - 1);
		
		// Нахождение коэффициентов С
		double* tempPtr = new double[nPt - 2];
		threeDiagMethod(arrCPtr, tempPtr, nPt - 2, nPt - 1);
		for (int i = 0; i < nPt - 2; i++)
			arrPtr[C][i + 2] = tempPtr[i];
		arrPtr[C][1] = 0; // т.к. C1 = 0
		arrPtr[C][0] = 0;
		delete[] tempPtr;
		
		arrPtr[A][0] = 0; // Запись коэффициентов А
		for (int i = 1; i < nPt; i++)
			arrPtr[A][i] = arrPtr[Y][i - 1];

		arrPtr[B][0] = 0; // Нахождение коэффициентов В
		for (int i = 1; i < nPt - 1; i++)
			arrPtr[B][i] = ((arrPtr[Y][i] - arrPtr[Y][i - 1]) / arrPtr[H][i]) - (arrPtr[H][i] * (arrPtr[C][i + 1] + 2 * arrPtr[C][i])) / 3;
		arrPtr[B][nPt - 1] = ((arrPtr[Y][nPt - 1] - arrPtr[Y][nPt - 2]) / arrPtr[H][nPt - 1]) - arrPtr[H][nPt - 1] * 2 * arrPtr[C][nPt - 1] / 3;

		arrPtr[D][0] = 0; // Нахождение коэффициентов D
		for (int i = 1; i < nPt; i++)
			arrPtr[D][i] = (arrPtr[C][i + 1] - arrPtr[C][i]) / (3 * arrPtr[H][i]);

		cout << " i | " << " [Xi-1;Xi]  | " << "    Ai   | " << "    Bi   | " << "    Ci   | " << "    Di   " << endl;
		for (int i = 1; i < nPt; i++)
			cout << setw(2) << i
			<< " | " << setw(4) << arrPtr[X][i - 1] << " - " << setw(4) << arrPtr[X][i]
			<< " | " << setw(8) << setprecision(4) << arrPtr[A][i]
			<< " | " << setw(8) << setprecision(4) << arrPtr[B][i]
			<< " | " << setw(8) << setprecision(4) << arrPtr[C][i]
			<< " | " << setw(8) << setprecision(4) << arrPtr[D][i] << endl;
		cout << endl;

		double val{ 0 }, newPoint{ 0 };
		int counter{ 0 };
		cout << "Введите Х при котором требуется найти значение функции: ";
		cin >> newPoint;
		
		if (newPoint > arrPtr[X][0] && newPoint < arrPtr[X][nPt - 1])
		{
			do
				counter++;
			while (newPoint > arrPtr[X][counter]);
		}
		cout << "Отрезок " << counter << " [" << arrPtr[X][counter - 1] << ";" << arrPtr[X][counter] << "]" << endl;

		val = arrPtr[A][counter] + arrPtr[B][counter] * (newPoint - arrPtr[X][counter - 1]);
		val += arrPtr[C][counter] * powf((newPoint - arrPtr[X][counter - 1]), 2);
		val += arrPtr[D][counter] * powf((newPoint - arrPtr[X][counter - 1]), 3);
		
		cout << "Значание функции в точке [" << newPoint << "]: " << val << endl;

		for (int i = 0; i < nPt - 2; i++)
			delete[] arrCPtr[i];
		delete[] arrCPtr;
	}
	
	void initT8()
	{
		int nPt{ 0 };
		cout << "Введите количество точек: ";
		cin >> nPt;

		double** arrPtr = new double* [7];
		for (int i = 0; i < 7; i++)
			arrPtr[i] = new double[nPt];
		
		cout << "Введите точки и значения функции в них (х): (у):";

		for (int i = 0; i < nPt; i++)
		{
			//cout << "x(" << i << ") y(" << i << ")" << endl;
			cin >> arrPtr[X][i];
			cin >> arrPtr[Y][i];
			//arrPtr[Y][i] = arrPtr[X][i] * log(arrPtr[X][i]);
		}
		
		cbSpline(arrPtr, nPt);
		
		puk

		for (int i = 0; i < 6; i++)
			delete[] arrPtr[i];
		delete[] arrPtr;
	}
}