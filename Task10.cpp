#include <iostream>
#include <cmath>
#include <iomanip>
#include "Nmeth.h"

const int X = 0;
const int Y = 1;

using namespace std;


namespace T10
{
	void  firstDiff(double** arrPtr, int nPt, double Pt)
	{
		int counter{ 0 };
		double left{ 0 }, right{ 0 }, mid{ 0 };
		
		while (arrPtr[X][counter] < Pt)
			counter++;
		counter++;

		left = (arrPtr[Y][counter] - arrPtr[Y][counter - 1]) / (arrPtr[X][counter] - arrPtr[X][counter - 1]);
		right = (arrPtr[Y][counter + 1] - arrPtr[Y][counter]) / (arrPtr[X][counter + 1] - arrPtr[X][counter]);
		mid = (left + right) / 2;

		cout << endl << "Первая производная заданной функции в точке " << Pt << ": " << endl;
		cout << "Левая: " << left << " | Правая: " << right << " | Центральная: " << mid << endl;

	}
	
	void secondDiff(double** arrPtr, int nPt, double Pt)
	{
		int counter{ 0 };
		double diff{ 0 };

		while (arrPtr[X][counter] < Pt)
			counter++;
		counter++;
	
		diff = arrPtr[X][counter + 1] - arrPtr[X][counter];
		diff = (arrPtr[Y][counter + 1] - 2 * arrPtr[Y][counter] + arrPtr[Y][counter - 1]) / pow(diff, 2);

		cout << endl << "Вторая производная заданной функции в точке " << Pt << ": " << diff << endl;
	}
	
	void initT10()
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

		int Pt{ 0 };
		cout << "Введите точку, в которой необхожимо найти значение производной: ";
		cin >> Pt;

		firstDiff(arrPtr, nPt, Pt);

		secondDiff(arrPtr, nPt, Pt);

		for (int i = 0; i < 2; i++)
			delete[] arrPtr[i];
		delete[] arrPtr;
	}
}