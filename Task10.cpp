#include <iostream>
#include <cmath>
#include <iomanip>
#include "Nmeth.h"

const int X = 0;
const int Y = 1;

using namespace std;


namespace T10
{
	double firstDiff(double** arrPtr, int nPt, double Pt)
	{
		int counter{ 0 };

		while (arrPtr[Y][counter] > Pt)
			counter++;

		if (counter < nPt - 1)
		{
			return (arrPtr[Y][counter + 1] - arrPtr[Y][counter]) / (arrPtr[X][counter + 1] - arrPtr[X][counter]) +
				   ((arrPtr[Y][counter + 2] - arrPtr[Y][counter + 1]) / (arrPtr[X][counter + 2] - arrPtr[X][counter + 1]) - 
				   (arrPtr[Y][counter + 1] - arrPtr[Y][counter]) / (arrPtr[X][counter + 1] - arrPtr[X][counter])) /
				   (arrPtr[X][counter + 2] - arrPtr[X][counter]) * 
					(2 * Pt - arrPtr[X][counter] - arrPtr[X][counter + 1]);
		}
		else
		{
			return -1;
		}
	}
	
	double secondDiff(double** arrPtr, int nPt, double Pt)
	{
		int counter{ 0 };

		while (arrPtr[Y][counter] > Pt)
			counter++;

		if (counter < nPt - 1)
		{
			return 2 * ((arrPtr[Y][counter + 2] - arrPtr[Y][counter + 1]) / (arrPtr[X][counter + 2] - arrPtr[X][counter + 1]) -
				(arrPtr[Y][counter + 1] - arrPtr[Y][counter]) / (arrPtr[X][counter + 1] - arrPtr[X][counter])) /
				(arrPtr[X][counter + 2] - arrPtr[X][counter]);
		}
		else
		{
			return -1;
		}
	}
	
	void initT10()
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

		int Pt{ 0 };
		cout << "Введите точку, в которой необхожимо найти значение производной: ";
		cin >> Pt;

		cout << firstDiff(arrPtr, nPt, Pt) << endl;

		cout << secondDiff(arrPtr, nPt, Pt) << endl;

		for (int i = 0; i < 6; i++)
			delete[] arrPtr[i];
		delete[] arrPtr;
	}
}