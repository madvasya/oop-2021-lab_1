#include <iostream>
#include <locale.h>
#include "lab_1.h"

using namespace Lab_1;

int main() {
	setlocale(LC_ALL, "");
	Matrix matr;
	matr.line = nullptr;
	matr.m = 0;
	matr.n = 0;
	int rc;
	
	std::cout << "Добрый день! Поработаем с сильно разреженной прямоугольной матрицей." << std::endl;

	rc = input(matr);
	
	std::cout << (errmsgs[rc]) << std::endl;
	
	output("Введенная матрица", matr);
	//std::cout << "Результат: " << res << std::endl;
	erase(matr);
	return 0;
}