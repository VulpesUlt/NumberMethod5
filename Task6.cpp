#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

namespace T6
{

	//========================================================================== Метод Ньютона
	
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
		case 5:
			return (x1 - cos(x2) - 1);
		case 9:
			return (x1 * x1 + x2 * x2 - 16);
		case 18:
			return (4 * x1 - cos(x2));
		case 0: 
			return (0.1 * x1 * x1 + x1 + 0.2 * x2 - 0.3);
		}
		return 1;
	}

	double func2 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5: 
			return (x2 - log10 (x1 + 1) - 2);
		case 9:
			return (x1 - exp(x2) + 4);
		case 18:
			return (4 * x2 - exp(x1));
		case 0: 
			return (0.2 * x1 * x1 + x2 - 0.1 * x1 * x2 - 0.7);
		}
		return 1;
	}

	double func1d1 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5: 
			return 1.0;
		case 9:
			return (2 * x1);
		case 18:
			return 4;
		case 0:
			return (0.2 * x1 + 1);
		}
		return 1;
	}

	double func1d2 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5:
			return sin(x2);
		case 9:
			return (2 * x2);
		case 18:
			return (sin(x2));
		case 0:
			return (0.4 * x2);
		}
		return 1;
	}

	double func2d1 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5:
			return (-1 / (x1 + 1) * log(10));
		case 9:
			return 1;
		case 18:
			return (-exp(x1));
		case 0:
			return (0.4 * x1 - 0.1 * x2);
		}
		return 1;
	}

	double func2d2 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5:
			return 1.0;
		case 9:
			return (-exp(x2));
		case 18:
			return 4;
		case 0:
			return (1 - 0.1 * x2);
		}
		return 1;
	}

	void NewtMethod (double x1, double x2, double precision, int var)
	{
		array I, A1, A2;
		double temp1, temp2, actPrecision{ 0 };
		int iter{ 0 };
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

		cout << endl << "Количество итераций: " << iter << endl;
		cout << "x[1]= " << setprecision(6) << x1 << " | x[2]= " << setprecision(6) << x2 << endl;
	}

	//========================================================================== Метод Простой Итерации
	
	double eqfunc1 (double x1, double x2, int var)
	{
		switch (var)
		{
		case 5: 
			return (cos(x2) + 1);
		case 9:
			return (sqrt(16 - x2 * x2));
		case 18:
			return (cos(x2) / 4);
		case 0:
			return (0.1 * x1 * x1 + x1 + 0.2 * x2 - 0.3);
		}
		return 1;
	}
	
	double eqfunc2(double x1, double x2, int var)
	{
		switch (var)
		{
		case 5: 
			return (log10(x1 + 1) + 2);
		case 9:
			return (log(x1 + 4));
		case 18:
			return (exp(x1) / 4);
		case 0:
			return (0.1 * x1 * x1 + x1 + 0.2 * x2 - 0.3);
		}
		return 1;
	}

	double eqfunc1d1(double x1, double x2, int var)
	{
		switch (var)
		{
		case 5:
			return 0;
		case 9:
			return 0;
		case 18:
			return 0;
		case 0:
			return (0.1 * x1 * x1 + x1 + 0.2 * x2 - 0.3);
		}
		return 1;
	}

	double eqfunc1d2(double x1, double x2, int var)
	{
		switch (var)
		{
		case 5: 
			return ( -sin(x2) );
		case 9:
			return (-x2 / sqrt(16 - x2 * x2));
		case 18:
			return (-cos(x2) / 4);
		case 0:
			return (0.1 * x1 * x1 + x1 + 0.2 * x2 - 0.3);
		}
		return 1;
	}

	double eqfunc2d1(double x1, double x2, int var)
	{
		switch (var)
		{
		case 5: 
			return ( 1 / ( log(10) * (x1 + 1) ) );
		case 9:
			return (1 / (x1 + 4));
		case 18:
			return (exp(x1) / 4);
		case 0:
			return (0.1 * x1 * x1 + x1 + 0.2 * x2 - 0.3);
		}
		return 1;
	}

	double eqfunc2d2(double x1, double x2, int var)
	{
		switch (var)
		{
		case 5:
			return 0;
		case 9:
			return 0;
		case 18:
			return 0;
		case 0:
			return (0.1 * x1 * x1 + x1 + 0.2 * x2 - 0.3);
		}
		return 1;
	}

	void iterMethod (double x1, double x2, double precision, int var)
	{
		double q{ 0 }, temp{ 0 }, prevNorm{0}, norm{ 0 };
		int iter{ 0 };
		q = ( fabs(eqfunc1d1(x1, x2, var) + eqfunc1d2(x1, x2, var)) > fabs(eqfunc2d1(x1, x2, var) + eqfunc2d2(x1, x2, var)) ) ? fabs(eqfunc1d1(x1, x2, var) + eqfunc1d2(x1, x2, var)) : fabs(eqfunc2d1(x1, x2, var) + eqfunc2d2(x1, x2, var));
		cout << q << endl;
		
		if (fabs(q) > 1)
		{
			cout << "|Q| > 1" << endl;
			return;
		}

		do
		{
			prevNorm = norm;
			temp = x1;
			x1 = eqfunc1(x1, x2, var);
			norm = fabs(x1 - temp);
			
			temp = x2;
			x2 = eqfunc2(x1, x2, var);
			norm = ( fabs(x2 - temp) > norm) ? fabs(x2 - temp) : norm;
			
			cout << "x[1]= " << setprecision(6) << x1 << " | x[2]= " << setprecision(6) << x2 << endl;
			iter++;
		} while (prevNorm < q / (1 - q) * norm  && iter < 100);

		cout << endl << "Количество итераций: " << iter << endl;
		cout << "x[1]= " << setprecision(6) << x1 << " | x[2]= " << setprecision(6) << x2 << endl;
	}

	//========================================================================== Ввод данных

	void initT6()
	{
		double x1{ 0 }, x2{ 0 }, precision{ 0 };
		int var{ 0 };
		cout << "Введите номер варианта: ";
		cin >> var;
		cout << "Введите начальный х1: ";
		cin >> x1;
		cout << "Введите начальный х2: ";
		cin >> x2;
		cout << "Введите требуемую точность: ";
		cin >> precision;

		cout << endl << "===== Метод Ньютона =====" << endl;
		T6::NewtMethod (x1, x2, precision, var);

		cout << endl << "===== Метод Простой Итерации =====" << endl;
		T6::iterMethod(x1, x2, precision, var);

	}

} 