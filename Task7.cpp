#include <iostream>
#include <cmath>
#include <iomanip>
#include "Nmeth.h"

const bool MANUAL = true;

using namespace std;

namespace T7
{	
	double func(double x, int var)
	{
		switch (var)
		{
		case 9:
			return acos(x);
		case 18:
			return sqrt(x) + x;
		}
		return 1;
	}

	void initvarLg (double** point, int var)
	{
		switch (var)
		{
		case 9:
			point[0][0] = -0.4; 
			point[1][0] = -0.1;
			point[2][0] = 0.2;
			point[3][0] = 0.5;
			for (int i = 0; i < 4; i++)
				point[i][1] = func(point[i][0], var);
			break;
		case 18:
			point[0][0] = 0;
			point[1][0] = 1.7;
			point[2][0] = 3.4;
			point[3][0] = 5.1;
			for (int i = 0; i < 4; i++)
				point[i][1] = func(point[i][0], var);
			break;
		}
	}

	void initvarNw(double** point, int var)
	{
		switch (var)
		{
		case 9:
			point[0][0] = -0.4;
			point[1][0] = 0;
			point[2][0] = 0.2;
			point[3][0] = 0.5;
			for (int i = 0; i < 4; i++)
				point[i][1] = func(point[i][0], var);
			break;
		case 18:
			point[0][0] = 0;
			point[1][0] = 1.7;
			point[2][0] = 4.1;
			point[3][0] = 5.1;
			for (int i = 0; i < 4; i++)
				point[i][1] = func(point[i][0], var);
			break;
		}
	}

	void Lagrange (double** point, double pt, int nPt, int var)
	{
		double* coef = new double[nPt];
		double val{ 0 }, temp{0};

		for (int i = 0; i < nPt; i++) // fi / (Xi - Xj)
		{
			coef[i] = point[i][1];
			for (int j = 0; j < nPt; j++)
				if (j != i)
					coef[i] /= point[i][0] - point[j][0];
		}

		cout << "Ln(X)= "; // Вывод полученного полинома
		for (int i = 0; i < nPt; i++)
		{
			if (i == 0)
			{
					cout << coef[i] << "*";
					for (int j = 0; j < nPt; j++)
						if (i != j)
							if (point[j] > 0)
								cout << "(x - " << point[j][0] << ")";
							else
								cout << "(x + " << point[j][0] << ")";

			}
			else
			{
				if (coef[i] > 0)
				{
					cout << " + " << coef[i] << "*";
					for (int j = 0; j < nPt; j++)
						if (i != j)
							if (point[j][0] > 0)
								cout << "(x - " << point[j][0] << ")";
							else
								cout << "(x + " << point[j][0] << ")";
				}
				else
				{
					cout << " - " << fabs(coef[i]) << "*";
					for (int j = 0; j < nPt; j++)
						if (i != j)
							if (point[j][0] > 0)
								cout << "(x - " << point[j][0] << ")";
							else
								cout << "(x + " << point[j][0] << ")";
				}
			}
		}
		cout << endl;

		for (int i = 0; i < nPt; i++) // Значение полинома в точке
		{
			temp = 1;
			for (int j = 0; j < nPt; j++)
			{
				if (j != i)
					temp *= pt - point[j][0];
			}
			val += coef[i] * temp;
		}
		
		cout << "Ln( " << pt << " )= " << val << endl;
		
		if (var != 0)
		{
			cout << "e = " << fabs(func(pt, var) - val) << endl;
			cout << "Погрешность: " << (fabs(func(pt, var) - val) / fabs(func(pt, var))) << endl;
		
			double temp{ 0 };
		}
		


		delete[] coef;
	}
	
	void Newton (double** point, double pt, int nPt, int var)
	{
		double* coef = new double[nPt];
		double val{ 0 }, temp{0};
		int iter{ 0 };

		for (int i = 0; i < nPt; i++) // Запись f(x) в coef
			coef[i] = point[i][1];
		
		for (int iter = 0; iter < nPt; iter++)
		{
			for (int i = nPt - 1; i > iter; i--) // Нахождение разностей f(x0,x1), f(x0,x1,x2), .. , f(x0,..,xn)
			{
				coef[i] = (coef[i - 1] - coef[i]) / (point[i - iter - 1][0] - point[i][0]);
				//cout << coef[i] << "  ";
			}
		}
		cout << endl;

		for (int iter = 0; iter < nPt; iter++)
		{
			temp = 1; // Нахождение значения функции в точке 
			for (int j = 0; j < iter; j++)
			{
				temp *= pt - point[j][0];
			}
			val += coef[iter] * temp;
			//cout << " iter " << iter;
		}
		cout << endl;

		cout << endl; // Вывод получненного многочлена Ньютона
		for (int i = 0; i < nPt; i++) 
		{
			if (coef[i] >= 0 && i != 0)
			{
				cout << " + ";
				cout << fabs(coef[i]);
			}
			else if (coef[i] < 0 && i != 0)
			{
				cout << " - ";
				cout << fabs(coef[i]);
			}
			else
				cout << coef[i];

			for (int j = 0; j < i; j++)
			{
				if (point[j][0] > 0)
					cout << "(x - " << point[j][0] << ")";
				else
					cout << "(x + " << fabs(point[j][0]) << ")";
			}

		}
		cout << endl;
		
		cout << "Ln( " << pt << " )= " << val << endl;
		
		if (var != 0)
		{
			cout << "e = " << fabs(func(pt, var) - val) << endl;
			cout << "Погрешность: " << (fabs(func(pt, var) - val) / fabs(func(pt, var))) << endl;
		}

		delete[] coef;
	}
	
	void initT7 ()
	{
		int var{ 0 }, nPt{ 0 };
		double pt;
		cout << "Введите номер варианта: ";
		cin >> var;
		
		if (var == 9 || var == 18)
		{
			pt = (var == 9) ? 0.1 : 3.0;
			nPt = 4;
			double** point = new double* [nPt];
			for (int i = 0; i < nPt; i++)
				point[i] = new double[2];
			
			initvarLg(point, var);
			Lagrange(point, pt, nPt, var);
			
			initvarNw(point, var);
			Newton(point, pt, nPt, var);

			delete[] point;
		}
		else if (var == 0)
		{
			cout << "Введите количество точек:";
			cin >> nPt;
			double** point = new double* [nPt];
			for (int i = 0; i < nPt; i++)
				point[i] = new double[2];

			cout << "Введите точки:" << endl;
			for (int i = 0; i < nPt; i++)
			{
				cout << "x[" << i + 1 << "] y[" << i + 1 << "]: ";
				cin >> point[i][0];
				cin >> point[i][1];
			}

			cout << "Введите точку, в которой требется найти значение: ";
			cin >> pt;

			Lagrange(point, pt, nPt, var);

			for (int i = 0; i < nPt; i++)
				delete[] point[i];
			delete[] point;
		}
		else
			cout << var << " не реализован" << endl;
	}

}