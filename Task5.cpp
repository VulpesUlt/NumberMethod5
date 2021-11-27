#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

namespace T5
{

    double func(double x, int var)
    {
        double y{ 0 };
        switch (var)
        {
        case 9:  y = pow(x, 3) + pow(x, 2) - 2 * x - 1;
            break;
        case 5:  y = cos(x) + 0.25 * x - 0.5;
            break;
        case 18: y = log(x + 1) - pow(x, 3) + 1;
            break;
        }
        return y;
    }

    double funcV(double x, int var)
    {
        double y{ 0 };
        switch (var)
        {
        case 9:  y = 3 * pow(x, 2) + 2 * x - 2;
            break;
        case 5:  y = -sin(x) + 0.25;
            break;
        case 18: y = 1 / (x + 1) - 3 * pow(x, 2);
            break;
        }
        return y;
    }

    double funcA(double x, int var)
    {
        double y{ 0 };
        switch (var)
        {
        case 9:  y = 6 * x + 2;
            break;
        case 5:  y = -cos(x);
            break;
        case 18: y = -1 / ((x + 1) * (x + 1)) - 6 * x;
            break;
        }
        return y;
    }

    double NwtMethod(int var, double b1, double b2, double acc)
    {
        double x{ 0 }, temp{ 0 };
        int iter{ 0 };

        if (func(b1, var) * funcA(b1, var) > 0)
            x = b1;
        else if (func(b2, var) * funcA(b2, var) > 0)
            x = b2;
        else
            return x = 0;

        do
        {
            temp = x;
            x -= func(x, var) / funcV(x, var);
            cout << "Iter: " << iter
                << " | acc: " << left << setprecision(3) << setw(10) << fabs(x - temp)
                << setprecision(6) << " | x: " << x << endl;
            iter++;
        } while (fabs(x - temp) > acc && iter < 100);
        return x;
    }

    double eqfunc(double x, int var)
    {
        double y{ 0 };
        switch (var)
        {
        case 9:  y = cbrt(-pow(x, 2) + 2 * x + 1);
            break;
        case 5:  y = acos(0.5 - 0.25 * x);
            break;
        case 18: y = cbrt(log(x + 1) + 1);
            break;
        }
        return y;
    }

    double eqfuncV(double x, int var)
    {
        double y{ 0 };
        switch (var)
        {
        case 9: y = -1 * pow(x, 2) + 2 * x + 1;
            y = 1 / cbrt(pow(y, 2)) / 3 * (-2 * x + 2);
            break;
        case 5:  y = 1 / 4 / sqrt(1 - pow((0.5 - 0.25 * x), 2));
            break;
        case 18: y = (1 / cbrt(pow((log(x + 1) + 1), 2))) * (1 / (x + 1)) / 3;
            break;
        }
        return y;
    }

    double smplIter(int var, double b1, double b2)
    {
        double x{ 0 }, q{ 0 }, diff{ 0 }, temp{ 0 };
        int iter{ 0 };

        q = (fabs(eqfuncV(b1, var)) > fabs(eqfuncV(b2, var))) ? eqfuncV(b1, var) : eqfuncV(b2, var);
        cout << q << endl;
        x = (b1 + b2) / 2;

        do
        {
            iter++;
            temp = x;
            x = eqfunc(x, var);
            if (iter == 1)
                diff = fabs(x - temp);
            cout << "Iter: " << setw(2) << iter
                << setprecision(6) << " | x: " << x << endl;
        } while (fabs(x - temp) > (pow(q, iter) / (1 - q)) * diff && iter < 2000);


        return x;

    }

    void initT5()
    {
        double b1{ 0 }, b2{ 0 }, acc{ 0 };
        int var{};

        cout << "¬ведите номер варианта: ";
        cin >> var;
        
        if (var == 5 || var == 9 || var == 18)
        {
            cout << "¬ведите левую границу: ";
            cin >> b1;
            cout << "¬ведите правую границу: ";
            cin >> b2;
            cout << "¬ведите требуемую точность: ";
            cin >> acc;

            cout << "===== ћетод Ќьютона =====" << endl;
            cout << "x= " << setprecision(6) << T5::NwtMethod(var, b1, b2, acc) << endl;

            cout << "===== ћетод простой итерации =====" << endl;
            cout << "x= " << setprecision(6) << T5::smplIter(var, b1, b2) << endl;
        }
        else
            cout << "¬ариант є" << var << " не был реализован." << endl;
        
    }

}