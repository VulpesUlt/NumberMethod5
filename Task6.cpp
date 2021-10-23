#include <iostream>
#include <cmath>
#include <iomanip>
#include "Nmeth.h"

using namespace std;

namespace T6
{
	struct result
	{
		double f1;
		double f2;
	};

	void initT6()
	{
		int var{ 0 };
		cout << "Введите номер варианта: ";
		cin >> var;

		cout << "===== Метод Ньютона =====" << endl;
		NewtMethod(var);

		cout << "===== Метод Простой Итерации" << endl;
		iterMethod(var);

	}

	double func1 (double x1, double x2, int var)
	{
		double y{ 0 };
		switch(var)
		{
		case 5:
			break;
		case 9:
			break;
		case 18:
			break;
		}
		return y;
	}
	
	double func2 (double x1, double x2, int var)
	{
		double y{ 0 };
		switch (var)
		{
		case 5:
			break;
		case 9:
			break;
		case 18:
			break;
		}
		return y;
	}

	double func1d1 (double x1, double x2, int var)
	{
		double y{ 0 };
		switch (var)
		{
		case 5:
			break;
		case 9:
			break;
		case 18:
			break;
		}
		return y;
	}

	double func1d2double (double x1, double x2, int var)
	{
		double y{ 0 };
		switch (var)
		{
		case 5:
			break;
		case 9:
			break;
		case 18:
			break;
		}
		return y;
	}

	double func2d1double(double x1, double x2, int var)
	{
		double y{ 0 };
		switch (var)
		{
		case 5:
			break;
		case 9:
			break;
		case 18:
			break;
		}
		return y;
	}

	double func2d2double(double x1, double x2, int var)
	{
		double y{ 0 };
		switch (var)
		{
		case 5:
			break;
		case 9:
			break;
		case 18:
			break;
		}
		return y;
	}

	void NewtMethod (int var)
	{

	}

	void iterMethod (int var)
	{
	
	}
} 