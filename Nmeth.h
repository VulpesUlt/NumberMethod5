#pragma once

// Tasl 1-4=====================================================

const double PI = 3.141592653589793;

void arrayInput(double** arrayPtr, int numberOflines, int numberOfColumns);
void printArray(double** arrayPtr, int numberOflines, int numberOfColumns);

void __fastcall gaussMethod(double** arrayPtr, int numberOflines, int numberOfColumns);

void __fastcall threeDiagMethod(double* arrayPtr[], int numberOflines, int numberOfColumns);
void __fastcall threeDiagMethod(double* arrayPtr[], double* ansPtr, const int numberOflines, const int numberOfColumns);
bool __fastcall threeDiagCheck(double* arrayPtr[], int numberOflines);

void __fastcall SeidelMethod(double** arrPtr, int numberOfLines, int numberOfCulumns);
void __fastcall JacobiMethod(double** arrPtr, int numberOfLines, int numberOfCulumns);

bool __fastcall symmetryCheck(double** arrPtr, int numberOfLines, int numberOfColumns);
void __fastcall TurnMethod(double** arrPtr, int numberOfLines, int numberOfColumns);
void __fastcall multArr(double** arrMain, double** arrSec, int rang, bool pos);
void __fastcall transposeArr(double** arrPtr, int rang);

void init14();

// Task 5 ======================================================

namespace T5
{
	void initT5();
}

// Task 6 ======================================================

namespace T6
{
	void initT6();
}

// Task 7 ======================================================

namespace T7
{
	void initT7();
}


namespace T8
{
	void initT8();
}

namespace T9
{
	void initT9();
}

namespace T10
{
	void initT10();
}