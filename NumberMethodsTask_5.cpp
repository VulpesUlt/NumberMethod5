﻿// NumberMethods5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Nmeth.h"
#include <iostream>
#include <iomanip>

const int NTASK = 8;
const bool MANUAL = true;

using namespace std;

int main()
{
    string cont;
    int nTask{ 0 };
    setlocale(LC_ALL, "Russian");

    do
    {
        //cout << "Введите номер задания: ";
        //cin >> nTask;
        switch (NTASK)
        {
        case 1: init14();
            break;
        case 5: T5::initT5();
            break;
        case 6: T6::initT6();
            break;
        case 7: T7::initT7();
            break;
        case 8: T8::initT8();
            break;
        }
        //cout << "Завершить работу? (y/n)";
        //cin >> cont;
        //system("cls");
    } while (cont != "n" && !MANUAL);

    system("pause");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
