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
	
	std::cout << "������ ����! ���������� � ������ ����������� ������������� ��������." << std::endl;

	rc = input(matr);
	
	std::cout << (errmsgs[rc]) << std::endl;
	
	output("��������� �������", matr);
	//std::cout << "���������: " << res << std::endl;
	erase(matr);
	return 0;
}