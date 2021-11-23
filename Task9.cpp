#include <iostream>
#include <cmath>
#include <iomanip>
#include "Nmeth.h"

using namespace std;

const int X = 0;
const int Y = 1;

namespace T9
{
	void __fastcall SeidelMethod(double** arrPtr, int numberOfLines, int numberOfColumns)
	{
		int iter = 0;
		const double precision{ 0.000000001 };
		double temp{ 0 }, alpha{ 0 }, actPrecision{ 0 };

		do
		{
			if (iter == 0) // Нулевая итерация
			{
				for (int i = 0; i < numberOfLines; i++)
				{
					temp = 0;
					for (int j = 0; j < numberOfColumns; j++)
						if (i != j)
						{
							if (j != numberOfColumns - 1)
							{
								arrPtr[i][j] /= -arrPtr[i][i];
								temp += arrPtr[i][j];
							}
							else
								arrPtr[i][j] /= arrPtr[i][i];
						}
					arrPtr[i][i] = arrPtr[i][numberOfColumns - 1];
					alpha = (alpha > abs(temp)) ? alpha : abs(temp);
				}
				if (alpha > 1)
				{
					cout << "Не выполнено учловие сходимости." << endl;
					break;
				}
				actPrecision = alpha;
				alpha /= 1 - alpha;
			}
			else
			{
				actPrecision = 0;
				for (int i = 0; i < numberOfLines; i++)
				{
					temp = 0;
					for (int j = 0; j < numberOfLines; j++)
						if (i != j)
							temp += arrPtr[i][j] * arrPtr[j][j];
					temp += arrPtr[i][numberOfColumns - 1];
					actPrecision = (actPrecision > alpha * (abs(temp - arrPtr[i][i]))) ? actPrecision : abs(temp - arrPtr[i][i]);
					arrPtr[i][i] = temp;
				}
			}
			iter++;
		} while (actPrecision > precision && iter < 40);
	}
	
	void krammer(double** arr)
	{
		int del = arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
		int delA = arr[0][2] * arr[1][1] - arr[1][2] * arr[0][1];
		int delB = arr[0][0] * arr[1][2] - arr[1][0] * arr[0][2];

		arr[0][0] = delA / del;
		arr[1][1] = delB / del;
	}

	void linearFunc(double** arrPtr, int nPt)
	{
		
		double** arr = new double* [2];
		arr[0] = new double[3];
		arr[1] = new double[3];

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 3; j++)
				arr[i][j] = 0;
		
		for(int i = 0; i < nPt; i ++)
		{
			arr[0][0] += arrPtr[X][i] * arrPtr[X][i];
			arr[0][1] += arrPtr[X][i];
			arr[0][2] += arrPtr[X][i] * arrPtr[Y][i];

			arr[1][2] += arrPtr[X][i];
		}
		arr[1][0] = arr[0][1];
		arr[1][1] = nPt;

		krammer(arr);
	
		cout << endl << "Приближающий многочлен 1-ой степени:" << endl;
		if (arr[1][1] >= +0)
			cout << arr[0][0] << "*X + " << arr[1][1] << endl;
		if (arr[1][1] < 0)
			cout << arr[0][0] << "*X - " << fabs(arr[1][1]) << endl;
	
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
		
		SeidelMethod(arr, 3, 4);
		
		cout << endl << "Приближающий многочлен 2-ой степени:" << endl;

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
		
		for (int i = 0; i < 3; i++)
			delete[] arr[i];
		delete[] arr;
	}
	
	void initT9 ()
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
			cin >> arrPtr[X][i];
			cin >> arrPtr[Y][i];
		}

		linearFunc(arrPtr, nPt);

		quadraticFunc(arrPtr, nPt);

		for (int i = 0; i < 6; i++)
			delete[] arrPtr[i];
		delete[] arrPtr;
	}
}