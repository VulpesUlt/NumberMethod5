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
			break;
		case 18:
			point[0][0] = 0;
			point[1][0] = 1.7;
			point[2][0] = 4.1;
			point[3][0] = 5.1;
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

		cout << "Ln(X)= "; // ����� ����������� ��������
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

		for (int i = 0; i < nPt; i++) // �������� �������� � �����
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
			cout << "�����������: " << (fabs(func(pt, var) - val) / fabs(func(pt, var))) << endl;
		}
		
		delete[] coef;
	}
	
	void Newton (double** point, double pt, int nPt, int var)
	{
		cout << "� ������..." << endl;
	}
	
	void initT7 ()
	{
		int var{ 0 }, nPt{ 0 };
		double pt;
		cout << "������� ����� ��������: ";
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
			cout << "������� ���������� �����:";
			cin >> nPt;
			double** point = new double* [nPt];
			for (int i = 0; i < nPt; i++)
				point[i] = new double[2];

			cout << "������� �����:" << endl;
			for (int i = 0; i < nPt; i++)
			{
				cout << "x[" << i + 1 << "] y[" << i + 1 << "]: ";
				cin >> point[i][0];
				cin >> point[i][1];
			}

			cout << "������� �����, � ������� �������� ����� ��������: ";
			cin >> pt;

			Lagrange(point, pt, nPt, var);

			for (int i = 0; i < nPt; i++)
				delete[] point[i];
			delete[] point;
		}
		else
			cout << var << " �� ����������" << endl;
	}

}