#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

namespace T6
{

	class array 
	{
	public:
		double arr[2][2];

		double det()
		{
			return (arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0]);
		}
	};
	
	double func1 (double x1, double x2, int var)
	{
		switch(var)
		{
		case 5: return (x1 - cos(x2) - 1);

		case 9:
			break;
		case 18:
			break;
		}
	}

	double func2 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5: 
			return (x2 - log10l (x1 + 1) - 2);
		case 9:
			break;
		case 18:
			break;
		}
	}

	double func1d1 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5: 
			return 1.0;
		case 9:
			break;
		case 18:
			break;
		}
	}

	double func1d2 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5:
			return sin(x2);
		case 9:
			break;
		case 18:
			break;
		}
	}

	double func2d1 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5:
			return (-1 / (x1 + 1) + log(10));
		case 9:
			break;
		case 18:
			break;
		}
	}

	double func2d2 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5:
			return 1.0;
		case 9:
			break;
		case 18:
			break;
		}
	}

	void NewtMethod (double x1s, double x2s, double precision, int var)
	{
		array I, A1, A2;
		double temp1, temp2, actPrecision{ 0 }, x1 ,x2;
		int iter{ 0 };
		x1 = x1s;
		x2 = x2s;
		do
		{
			temp1 = x1;
			temp2 = x2;
			actPrecision = 0;
			
			I.arr[0][0] = func1d1(x1, x2, var);
			I.arr[0][1] = func1d2(x1, x2, var);
			I.arr[1][0] = func2d1(x1, x2, var);
			I.arr[1][1] = func2d2(x1, x2, var);

			A1.arr[0][0] = func1(x1, x2, var);
			A1.arr[0][1] = func1d2(x1, x2, var);
			A1.arr[1][0] = func2(x1, x2, var);
			A1.arr[1][1] = func2d2(x1, x2, var);

			A2.arr[0][0] = func1d1(x1, x2, var);
			A2.arr[0][1] = func1(x1, x2, var);
			A2.arr[1][0] = func2d1(x1, x2, var);
			A2.arr[1][1] = func2(x1, x2, var);

			x1 -= A1.det() / I.det();
			x2 -= A2.det() / I.det();

			actPrecision = (fabs(x1 - temp1) > fabs(x2 - temp2)) ? fabs(x1 - temp1) : fabs(x2 - temp2);
			
			cout << "x[1]= " << setprecision(6) << x1 << " | x[2]= " << setprecision(6) << x2 << endl;
			
			iter++;
		} while (actPrecision > precision && iter < 100);

		cout << "Количество итераций: " << iter + 1 << endl;
		cout << "x[1]= " << setprecision(6) << x1 << " | x[2]= " << setprecision(6) << x2 << endl;
	}

	void iterMethod (int var)
	{
	
	}

	void initT6()
	{
		double x1{ 0 }, x2{ 0 }, precision{ 0 };
		int var{ 0 };
		cout << "Введите номер варианта: ";
		cin >> var;
		cout << "Введите левую границу: ";
		cin >> x1;
		cout << "Введите правую границу: ";
		cin >> x2;
		cout << "Введите требуемую точность: ";
		cin >> precision;

		cout << "===== Метод Ньютона =====" << endl;
		T6::NewtMethod (x1, x2, precision, var);

		cout << "===== Метод Простой Итерации" << endl;
		T6::iterMethod(var);

	}

} 