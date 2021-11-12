#include <iostream>
#include "Nmeth.h"
#include <cmath>

#define LEFT true
#define RIGHT false


using namespace std;



void arrayInput(double** arrayPtr, int numberOflines, int numberOfColumns) // Ввод массива
{
	// cout << "Не вводите вырожденные матрицы позязя. Оно поломаецо(" << endl;
	cout << "Введите матрицу построчно, разделяя значения пробелом: " << endl;
	for (int i = 0; i < numberOflines; i++)
	{
		for (int j = 0; j < numberOfColumns; j++)
		{
			cin >> arrayPtr[i][j];
		}
	}

}

void printArray(double** arrayPtr, int numberOflines, int numberOfColumns) // Вывод массива
{

	for (int i = 0; i < numberOflines; i++)
	{
		for (int j = 0; j < numberOfColumns; j++)
		{
			cout.width(4);
			cout << arrayPtr[i][j] << " ";
		}
		cout << endl;
	}
}

// Метод Гаусса / Функция получает ссылку на массив, его длину и высоту
void __fastcall gaussMethod(double** arrayPtr, int numberOflines, int numberOfColumns)
{
	double det{ 1 };
	double** arrE = new double* [numberOflines]; // Собдание и инициализация единичного массива
	for (int i = 0; i < numberOflines; i++)
		arrE[i] = new double[numberOfColumns];
	for (int i = 0; i < numberOflines; i++)
		for (int j = 0; j < numberOfColumns; j++)
			if (i == j)
				arrE[i][j] = 1;
			else
				arrE[i][j] = 0;

	// Прямой ход / Приведение матрицы к верхнетреугольному виду

	for (int iter = 0; iter < numberOflines - 1; iter++)
		for (int i = iter + 1; i < numberOflines; i++)
			for (int j = numberOfColumns - 1; j > -1; j--)
			{
				for (int j = numberOfColumns - 1; j > -1; j--)
				{
					arrE[i][j] -= arrE[iter][j] * arrayPtr[i][iter] / arrayPtr[iter][iter];
				}

				for (int j = numberOfColumns - 1; j > -1; j--)
				{
					arrayPtr[i][j] -= arrayPtr[iter][j] * arrayPtr[i][iter] / arrayPtr[iter][iter];
				}
			}

	for (int i = 0; i < numberOflines; i++) // Нахождение определителя матрицы
		det *= arrayPtr[i][i];
	cout << "Определитель: " << det << endl;

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

	cout << endl << "Полученные корни: "; // Вывод найденных корней
	for (int i = 0; i < numberOflines; i++)
		cout << answer[i] << "  ";
	cout << endl << endl;

	// Обнуление ячеек выше диагонали

	for (int iter = numberOflines - 1; iter > 0; iter--)
		for (int i = iter - 1; i > -1; i--)
		{
			arrayPtr[i][numberOfColumns - 1] -= arrayPtr[iter][numberOfColumns - 1] * arrayPtr[i][iter] / arrayPtr[iter][iter];
			for (int j = numberOflines - 1; j > -1; j--)
			{
				arrE[i][j] -= arrE[iter][j] * arrayPtr[i][iter] / arrayPtr[iter][iter];
			}

			for (int j = numberOflines - 1; j > -1; j--)
			{
				arrayPtr[i][j] -= arrayPtr[iter][j] * arrayPtr[i][iter] / arrayPtr[iter][iter];
			}
		}

	for (int i = 0; i < numberOflines; i++) // Деление строк на числа диагонали
	{
		for (int j = 0; j < numberOflines; j++)
			arrE[i][j] /= arrayPtr[i][i];
		arrayPtr[i][numberOfColumns - 1] /= arrayPtr[i][i];
		arrayPtr[i][i] /= arrayPtr[i][i];
	}

	cout << "Обратная матрица: " << endl;
	printArray(arrE, numberOflines, numberOflines); // Вывод полученной обратной матрицы

	delete[] answer; // Удаление созданных массивов

	for (int i = 0; i < numberOflines; i++)
		delete[] arrE[i];
	delete[] arrE;

}

void __fastcall threeDiagMethod(double* arrayPtr[], const int numberOflines, const int numberOfColumns)
{
	if (!threeDiagCheck(arrayPtr, numberOflines)) // Проверка матрицы
		cout << "Матрица неверна." << endl;
	else
	{
		double* coefP = new double[numberOflines] { 0 };
		double* coefQ = new double[numberOflines] { 0 };

		// Прямой ход
		coefP[0] = (-1 * arrayPtr[0][1]) / arrayPtr[0][0];
		coefQ[0] = arrayPtr[0][numberOfColumns - 1] / arrayPtr[0][0];
		for (int i = 1; i < numberOflines - 1; i++)
		{
			coefP[i] = (-1 * arrayPtr[i][i + 1]) / (arrayPtr[i][i] + arrayPtr[i][i - 1] * coefP[i - 1]);
			coefQ[i] = (arrayPtr[i][numberOfColumns - 1] - arrayPtr[i][i - 1] * coefQ[i - 1]) / (arrayPtr[i][i] + arrayPtr[i][i - 1] * coefP[i - 1]);
		}
		coefP[numberOflines - 1] = 0;
		coefQ[numberOflines - 1] = (arrayPtr[numberOflines - 1][numberOfColumns - 1] - arrayPtr[numberOflines - 1][numberOflines - 2] * coefQ[numberOflines - 2]) / (arrayPtr[numberOflines - 1][numberOflines - 1] + arrayPtr[numberOflines - 1][numberOflines - 2] * coefP[numberOflines - 2]);

		// Обратный ход
		double* answer = new double[numberOflines];
		answer[numberOflines - 1] = coefQ[numberOflines - 1];
		for (int i = numberOflines - 2; i > -1; i--)
		{
			answer[i] = coefP[i] * answer[i + 1] + coefQ[i];
		}
		for (int i = 0; i < numberOflines; i++)
			cout << "x" << i + 1 << "=[" << answer[i] << "]      "; // Вывод ответа
		cout << endl;
		delete[] coefP;
		delete[] coefQ;
		delete[] answer;
	}
}

void __fastcall threeDiagMethod(double* arrayPtr[], double* ansPtr, const int numberOflines, const int numberOfColumns)
{
	if (!threeDiagCheck(arrayPtr, numberOflines)) // Проверка матрицы
		cout << "Матрица неверна." << endl;
	else
	{
		double* coefP = new double[numberOflines] { 0 };
		double* coefQ = new double[numberOflines] { 0 };

		// Прямой ход
		coefP[0] = (-1 * arrayPtr[0][1]) / arrayPtr[0][0];
		coefQ[0] = arrayPtr[0][numberOfColumns - 1] / arrayPtr[0][0];
		for (int i = 1; i < numberOflines - 1; i++)
		{
			coefP[i] = (-1 * arrayPtr[i][i + 1]) / (arrayPtr[i][i] + arrayPtr[i][i - 1] * coefP[i - 1]);
			coefQ[i] = (arrayPtr[i][numberOfColumns - 1] - arrayPtr[i][i - 1] * coefQ[i - 1]) / (arrayPtr[i][i] + arrayPtr[i][i - 1] * coefP[i - 1]);
		}
		coefP[numberOflines - 1] = 0;
		coefQ[numberOflines - 1] = (arrayPtr[numberOflines - 1][numberOfColumns - 1] - arrayPtr[numberOflines - 1][numberOflines - 2] * coefQ[numberOflines - 2]) / (arrayPtr[numberOflines - 1][numberOflines - 1] + arrayPtr[numberOflines - 1][numberOflines - 2] * coefP[numberOflines - 2]);

		// Обратный ход
		double* answer = new double[numberOflines];
		answer[numberOflines - 1] = coefQ[numberOflines - 1];
		for (int i = numberOflines - 2; i > -1; i--)
		{
			answer[i] = coefP[i] * answer[i + 1] + coefQ[i];
		}
		for (int i = 0; i < numberOflines; i++)
			ansPtr[i] = answer[i];
		cout << endl;
		delete[] coefP;
		delete[] coefQ;
		delete[] answer;
	}
}

bool __fastcall threeDiagCheck(double* arrayPtr[], int numberOflines)
{

	for (int i = 0; i < numberOflines; i++)
	{

		if (i != 0 && i != numberOflines - 1)
			if (arrayPtr[i][i - 1] == 0 || arrayPtr[i][i] == 0 || arrayPtr[i][i + 1] == 0)
				return false;
			else if (i == 0)
			{
				if (arrayPtr[i][i] == 0 || arrayPtr[i][i + 1] == 0)
					return false;
			}
			else if (i == numberOflines - 1)
			{
				if (arrayPtr[i][i - 1] == 0 || arrayPtr[i][i] == 0)
					return false;
			}

		for (int j = 0; j < numberOflines; j++)
		{
			if ((j != i - 1) && (j != i) && (j != i + 1))
				if (arrayPtr[i][j] != 0)
					return false;
		}

	}
	return true;
}

// Решение системы линейных упавнений методом Зейделя
void __fastcall SeidelMethod(double** arrPtr, int numberOfLines, int numberOfColumns)
{
	int iter = 0;
	double precision{ 0 }, temp{ 0 }, alpha{ 0 }, actPrecision{ 0 };
	cout << "Введите требуемую точность: ";
	cin >> precision;

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
				//cout << "iter: " << iter << " line: " << i << " Xpreveious= " << arrPtr[i][i] << " Xacrual= " << temp << endl; // Test output line
				arrPtr[i][i] = temp;
			}
		}
		iter++;
	} while (actPrecision > precision && iter < 40);


	cout << "Колличество итераций: " << iter << endl;
	for (int i = 0; i < numberOfLines; i++)
		cout << "x[" << i + 1 << "]= " << arrPtr[i][i] << endl;
}

// Решение системы линейных упавнений методом простой итерации
void __fastcall JacobiMethod(double** arrPtr, int numberOfLines, int numberOfColumns)
{
	int iter = 0;
	double precision{ 0 }, temp{ 0 }, alpha{ 0 }, actPrecision{ 0 };
	cout << "Введите требуемую точность: ";
	cin >> precision;

	double* answer = new double[numberOfLines];

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
				answer[i] = 0;
				for (int j = 0; j < numberOfLines; j++)
					if (i != j)
						answer[i] += arrPtr[i][j] * arrPtr[j][j];
				answer[i] += arrPtr[i][numberOfColumns - 1];
				actPrecision = (actPrecision > alpha * (abs(answer[i] - arrPtr[i][i]))) ? actPrecision : abs(answer[i] - arrPtr[i][i]);
				//cout << "iter: " << iter << " line: " << i << " Xpreveious= " << arrPtr[i][i] << " Xacrual= " << answer[i] << endl; // Test output line
			}
			for (int i = 0; i < numberOfLines; i++)
				arrPtr[i][i] = answer[i];
		}
		iter++;
	} while (actPrecision > precision && iter < 40);


	cout << "Колличество итераций: " << iter << endl;
	for (int i = 0; i < numberOfLines; i++)
		cout << "x[" << i + 1 << "]= " << arrPtr[i][i] << endl;
	delete[] answer;
}


void __fastcall TurnMethod(double** arrPtr, int numberOfLines, int numberOfColumns)
{
	if (symmetryCheck(arrPtr, numberOfLines, numberOfColumns))
	{
		int x{ 0 }, y{ 0 }, iter{ 0 };
		double temp{ 0 }, precision{ 0 }, actPrecision{ 0 }, angle{ 0 };

		double** arrU = new double* [numberOfLines];
		for (int i = 0; i < numberOfLines; i++)
			arrU[i] = new double[numberOfLines];

		double** arrVect = new double* [numberOfLines];
		for (int i = 0; i < numberOfLines; i++)
			arrVect[i] = new double[numberOfLines];

		cout << "Введите требуемую точность: ";
		cin >> precision;

		do
		{
			actPrecision = 0;
			temp = 0;
			cout << "=================================================" << endl
				<< "iteration: " << iter << endl;

			for (int i = 0; i < numberOfLines; i++) // Нахождение наибольшего элемента и его расположения
				for (int j = i + 1; j < numberOfLines; j++)
					if (temp < abs(arrPtr[i][j]))
					{
						y = i;
						x = j;
						temp = arrPtr[i][j];
					}

			angle = 0.5 * atan(2 * arrPtr[y][x] / (arrPtr[y][y] - arrPtr[x][x])); // Определение угла вращения

			cout << "Max:" << temp << " Column:" << x << " line:" << y << " angle:" << angle << endl; // test

			for (int i = 0; i < numberOfLines; i++) // Создание матрицы вращения
				for (int j = 0; j < numberOfLines; j++)
				{
					if (i == j)
						arrU[i][j] = 1;
					else
						arrU[i][j] = 0;
				}
			arrU[x][x] = cos(angle);
			arrU[y][y] = cos(angle);
			arrU[y][x] = -sin(angle);
			arrU[x][y] = sin(angle);

			multArr(arrPtr, arrU, numberOfLines, LEFT);

			if (iter == 0)
				for (int i = 0; i < numberOfLines; i++)
					for (int j = 0; j < numberOfLines; j++)
						arrVect[i][j] = arrU[i][j];
			else
				multArr(arrVect, arrU, numberOfLines, LEFT);

			transposeArr(arrU, numberOfLines);
			multArr(arrU, arrPtr, numberOfLines, RIGHT);

			for (int i = 0; i < numberOfLines; i++)
				for (int j = i + 1; j < numberOfLines; j++)
					actPrecision += pow(arrPtr[i][j], 2);
			actPrecision = pow(actPrecision, 0.5);

			iter++;
		} while (actPrecision > precision && iter < 100);

		cout << "Собственные значения матрцы: ";
		for (int i = 0; i < numberOfLines; i++)
			cout << "(" << i << ") = " << arrPtr[i][i];
		cout << endl;

		cout << "Собственные векторы матрцы: " << endl;
		printArray(arrVect, numberOfLines, numberOfLines);
		cout << endl << endl;

		for (int i = 0; i < numberOfLines; i++)
			delete[] arrU[i];
		delete[] arrU;

		for (int i = 0; i < numberOfLines; i++)
			delete[] arrVect[i];
		delete[] arrVect;
	}
}

bool __fastcall symmetryCheck(double** arrPtr, int numberOfLines, int numberOfColumns)
{
	if (numberOfLines != numberOfColumns)
	{
		cout << "Матрица не симметрична." << endl;
		return false;
	}
	else
	{
		for (int i = 0; i < numberOfLines; i++)
			for (int j = i + 1; j < numberOfLines; j++)
				if (arrPtr[i][j] != arrPtr[j][i])
				{
					cout << "Матрица не симметрична." << endl;
					return false;
				}
	}
	return true;
}

void __fastcall multArr(double** arrMain, double** arrSec, int rang, bool pos)
{
	double** arrTemp = new double* [rang];
	for (int i = 0; i < rang; i++)
		arrTemp[i] = new double[rang];

	for (int i = 0; i < rang; i++)
		for (int j = 0; j < rang; j++)
		{
			arrTemp[i][j] = 0;
			for (int k = 0; k < rang; k++)
				arrTemp[i][j] += arrMain[i][k] * arrSec[k][j];
		}

	if (pos)
	{
		for (int i = 0; i < rang; i++)
			for (int j = 0; j < rang; j++)
				arrMain[i][j] = arrTemp[i][j];
	}
	else
	{
		for (int i = 0; i < rang; i++)
			for (int j = 0; j < rang; j++)
				arrSec[i][j] = arrTemp[i][j];
	}

	for (int i = 0; i < rang; i++)
		delete[] arrTemp[i];
	delete[] arrTemp;
}

void __fastcall transposeArr(double** arrPtr, int rang)
{
	for (int i = 0; i < rang; i++)
		for (int j = i; j < rang; j++)
			if (i != j)
				swap(arrPtr[i][j], arrPtr[j][i]);
}

void init14()
{
	int n = 0;
	std::cout << "Введите количество уравнений: ";
	std::cin >> n;
	std::cin.clear();

	double** arrayPtr = new double* [n];
	for (int i = 0; i < n; i++)
		arrayPtr[i] = new double[n + 1];

	arrayInput(arrayPtr, n, n);
	printArray(arrayPtr, n, n);
	std::cout << std::endl;

	//gaussMethod(arrayPtr, n, n + 1);
	//JacobiMethod(arrayPtr, n, n + 1);
	//SeidelMethod(arrayPtr, n, n + 1);
	TurnMethod(arrayPtr, n, n);
	printArray(arrayPtr, n, n);
	std::cout << std::endl;

	for (int i = 0; i < n; i++)
		delete[] arrayPtr[i];
	delete[] arrayPtr;
}
