/*===================[Libraries]==================*/
#include "pch.h"
#include <iostream>
#include <clocale>

/*===================[Header]=====================*/
using namespace std;

int *Perechislenie(int mM);
void mn(int *A, int powerA, int *B, int powerB);
int *Obedinenie(int *A, int *B, int powerA, int powerB);
int *peresechenie(int *A, int *B, int powerA, int powerB);

/*===================[Main]=======================*/
int main() {
	setlocale(LC_ALL, "rus");
	int *A, *B;
	int powerA, powerB, powerC, powerD; //Мощность множества
	int i, val;


	cout << "Введите мощность множества А (от 0 до 100):  ";
	cin >> powerA;
	A = new int[powerA]; //Создание множества А
	cout << endl;

	cout << "Введите мощность множества B (от 0 до 100):  ";
	cin >> powerB;
	B = new int[powerB];  //Создание множества Б


	A = Perechislenie(powerA);  //Ввод элементов множества А с клавиатуры
	B = Perechislenie(powerB);  //Ввод элементов множества Б с клавиатуры

	//Вывод меню
	while (true) {
		system("pause");  //Пауза перед выводом меню
		system("cls");  //Очистка экрана
		mn(A, powerA, B, powerB); //Вывод множеств на экран
		cout << "Выберите операцию:" << endl;
		cout << "   1. Объединение множеств\n   2. Пересечение множеств\n";
		cin >> val;

		switch (val) {
		case 1: {
			cout << "Объединение множеств" << endl;
			int *C = new int[powerA + powerB];  //Создание множества C 
			C = Obedinenie(A, B, powerA, powerB); //Нахождение пересечения
			powerC = C[0];
			for (int i = 1; i <= powerC; i++) cout << C[i] << " "; //Вывод на экран множества
			cout << endl;
		} break;
		case 2: {
			cout << "Пересечение множеств" << endl;
			int *D = new int[powerA + powerB]; //Создание множества D 
			D = peresechenie(A, B, powerA, powerB); //Нахождение пересечения
			powerD = D[0];
			for (int i = 1; i <= powerD; i++) cout << D[i] << " ";  //Вывод на экран множества
			cout << endl;
		} break;
		}
	}
}


/*===================[Functions]==================*/
//Функция для вывода элементов мн-в А и Б на экран
void mn(int *A, int powerA, int *B, int powerB) {
	cout << "A =  ";
	cout << "{";
	for (int i = 0; i < powerA; i++) {  //Цикл для вывода
		cout << A[i];
		if (i < (powerA - 1)) cout << ", ";
	}
	cout << "}" << endl;

	cout << "B =  ";
	cout << "{";
	for (int i = 0; i < powerB; i++) {  //Цикл для вывода
		cout << B[i];
		if (i < (powerB - 1)) cout << ", ";
	}
	cout << "}" << endl;
}

//Функция для ввода элементов множества
int *Perechislenie(int mM) {
	int *M = new int[mM];
	if (mM == 0) {
		cout << endl << "Пустое множество!" << endl;
		return M;
	}
	cout << endl << "Введте элементы множества:  " << endl;
	for (int i = 0; i < mM; i++) cin >> M[i];
	return M;
}

//Функция для нахождения объеденения мн-в
int *Obedinenie(int *A, int *B, int powerA, int powerB) {
	int mO = powerA + powerB + 1, i = 0;
	int *C = new int[mO]; //Создание мн-ва C
	if (powerB == 0 && powerA == 0) {
		cout << "Пустое множество!";
		return C;
	}
	if (powerA == 0) {
		for (i = 0; i < powerB; i++) {
			C[i + 1] = B[i];
		}
		C[0] = i;
		return C;
	}
	if (powerB == 0) {
		for (i = 0; i < powerA; i++) {
			C[i + 1] = A[i];
		}
		C[0] = i;
		return C;
	}
	for (i = 0; i < powerA; i++) {
		C[i + 1] = A[i];
	}
	for (int b = 0; b < powerB; b++) {
		for (int a = 0; a < powerA; a++) {
			if (B[b] == A[a]) break;
			if (B[b] != A[a]) {
				if (a == (powerA - 1)) {
					i++;
					C[i] = B[b];
				}
				else
					continue;
			}
		}
	}
	C[0] = i;
	return C;
}

//Функция для нахождения пересечения мн-в
int *peresechenie(int *A, int *B, int powerA, int powerB) {
	int *D = new int[powerB + powerA];
	int i = 0;
	if (powerA == 0 || powerB == 0) {
		cout << "С = {Пустое множество}";
		return D;
	}
	for (int b = 0; b < powerB; b++) {
		for (int a = 0; a < powerA; a++) {
			if (B[b] == A[a]) {
				i++;
				D[i] = B[b];
			}
		}
	}
	if (i == 0) cout << endl << "Пустое множество!" << endl;
	D[0] = i;
	return D;
}