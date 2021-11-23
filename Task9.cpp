#include <iostream>
#include <cmath>
#include <iomanip>
#include "Nmeth.h"

using namespace std;

const int X = 0;
const int Y = 1;

namespace T9
{
	void __fastcall gaussMethod(double** arrayPtr, int numberOflines, int numberOfColumns)
	{

		// Прямой ход / Приведение матрицы к верхнетреугольному виду

		for (int iter = 0; iter < numberOflines - 1; iter++)
			for (int i = iter + 1; i < numberOflines; i++)
				for (int j = numberOfColumns - 1; j > -1; j--)
				{
					arrayPtr[i][j] -= arrayPtr[iter][j] * arrayPtr[i][iter] / arrayPtr[iter][iter];
				}

		// Обратный ход. Нахождение корней

		double* answer = new double[numberOflines];
		for (int i = 0; i < numberOflines; i++)
		{
			answer[i] = 0;
		}

		for (int i = numberOflines - 1; i > -1; i--)
		{
			for (int j = numberOfColumns - 2; j > 0; j--)
			{
				if (i != j)
					answer[i] = answer[i] - answer[j] * arrayPtr[i][j];
			}
			answer[i] = (arrayPtr[i][numberOfColumns - 1] + answer[i]) / arrayPtr[i][i];
		}

		for (int i = 0; i < numberOflines; i++)
			arrayPtr[i][i] = answer[i];

		delete[] answer; // Удаление созданных массивов
	}

	void linearFunc(double** arrPtr, int nPt)
	{
		double** arr = new double* [2];
		arr[0] = new double[3];
		arr[1] = new double[3];

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 3; j++)
				arr[i][j] = 0;

		for (int i = 0; i < nPt; i++)
		{
			arr[0][0] += arrPtr[X][i] * arrPtr[X][i];
			arr[0][1] += arrPtr[X][i];
			arr[0][2] += arrPtr[X][i] * arrPtr[Y][i];

			arr[1][2] += arrPtr[Y][i];
		}
		arr[1][0] = arr[0][1];
		arr[1][1] = nPt;

		gaussMethod(arr, 2, 3);

		cout << endl << "Приближающий многочлен 1-ой степени: ";
		if (arr[1][1] >= +0)
			cout << arr[0][0] << "*X + " << arr[1][1] << endl;
		if (arr[1][1] < 0)
			cout << arr[0][0] << "*X - " << fabs(arr[1][1]) << endl;

		double errorSum{ 0 };
		for (int i = 0; i < nPt; i++)
			errorSum += pow((arr[0][0] * arrPtr[X][i] + arr[1][1] - arrPtr[Y][i]), 2);
		
		cout << "Сумма квадратов ошибок: " << errorSum << endl;

		for (int i = 0; i < 2; i++)
			delete[] arr[i];
		delete[] arr;
	}
	
	void quadraticFunc(double** arrPtr, int nPt)
	{
		double** arr = new double* [3];
		for (int i = 0; i < 3; i++)
		{
			arr[i] = new double[4];
			for (int j = 0; j < 4; j++)
				arr[i][j] = 0.0;
		}

		for (int i = 0; i < nPt; i++)
		{
			arr[0][0] += pow(arrPtr[X][i], 4);			
			arr[0][1] += pow(arrPtr[X][i], 3);
			arr[0][2] += pow(arrPtr[X][i], 2);
			arr[0][3] += pow(arrPtr[X][i], 2) * arrPtr[Y][i];
			
			arr[1][2] += arrPtr[X][i];
			arr[1][3] += arrPtr[X][i] * arrPtr[Y][i];

			arr[2][3] += arrPtr[Y][i];
		}
		arr[1][0] = arr[0][1];
		arr[1][1] = arr[0][2];

		arr[2][0] = arr[0][2];
		arr[2][1] = arr[1][2];
		arr[2][2] = nPt;
		
		gaussMethod(arr, 3, 4);
		
		cout << endl << "Приближающий многочлен 2-ой степени: ";

		cout << arr[0][0] << "*X^2";
		if (arr[1][1] >= +0)
			cout << " + " << arr[1][1] << "*X";
		else
			cout << " - " << fabs(arr[1][1]) << "*X";
		if (arr[2][2] >= +0)
			cout << " + " << arr[2][2];
		else
			cout << " - " << fabs(arr[2][2]);
		cout << endl;

		double errorSum{ 0 };
		for (int i = 0; i < nPt; i++)
			errorSum += pow((arr[0][0] * pow(arrPtr[X][i], 2) + arr[1][1] * arrPtr[X][i] + arr[2][2] - arrPtr[Y][i]), 2);

		cout << "Сумма квадратов ошибок: " << errorSum << endl;
		
		for (int i = 0; i < 3; i++)
			delete[] arr[i];
		delete[] arr;
	}
	
	void initT9 ()
	{
		int nPt{ 0 };
		cout << "Введите количество точек: ";
		cin >> nPt;

		double** arrPtr = new double* [2];
		for (int i = 0; i < 2; i++)
			arrPtr[i] = new double[nPt];

		cout << "Введите точки и значения функции в них (х): (у):";

		for (int i = 0; i < nPt; i++)
		{
			cin >> arrPtr[X][i];
			cin >> arrPtr[Y][i];
		}

		linearFunc(arrPtr, nPt);

		quadraticFunc(arrPtr, nPt);

		for (int i = 0; i < 2; i++)
			delete[] arrPtr[i];
		delete[] arrPtr;
	}
}