#include <iostream>
#include "lab_1.h"

namespace Lab_1 {
	int input(Matrix& matr) {
		const char* pr = "";
		int m, n;
		do {
			std::cout << pr << std::endl;
			std::cout << "Введите число строк в матрице: -->" << std::endl;
			pr = "Ошибка! Ожидалось целое число больше нуля.";
			if (getNum(m) < 0)
				return WRONG_INPUT;
		} while (m < 1);
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Введите число столбцов в матрице: -->" << std::endl;
			pr = "Ошибка! Ожидалось целое число больше нуля.";
			if (getNum(n) < 0)
				return WRONG_INPUT;
		} while (n < 1);

		matr.m = m;
		matr.n = n;

		int elem_number = m * n;
		int i = 0, elem_m, elem_n, elem_value;
		std::cout << "Ввод матрицы. Введите не-цифру, чтобы закончить заполнение матрицы. Строки и столбцы нумеруются с 1." << std::endl;
		do {
			std::cout << "Введите номер строки, номер столбца и значение элемента: ";
			if (getNum(elem_m) < 0 || getNum(elem_n) < 0 || getNum(elem_value) < 0) {
				break;
			}
			if (elem_m < 1 || elem_n < 1) {
				std::cout << "Ошибка! Номер строки/столбца не может быть меньше нуля!" << std::endl;
				continue;
			}

			else if (elem_m > m || elem_n > n) {
				std::cout << "Ошибка! Позиция элемента выходит за размеры матрицы!" << std::endl;
				continue;
			}
			else {
				std::cout << errmsgs[insert(matr, elem_m-1, elem_n-1, elem_value)] << std::endl;
				i++;
			}
		}while(i < elem_number);
		
		return SUCCESS;
	}

	int insert(Matrix& matr, int m, int n, int value) {
		if (!matr.line) {//если вставляем самый первый элемент (первую строчку)
			Line* tmpline = new Line;
			tmpline->m = m;
			tmpline->next = nullptr;
			tmpline->column = new Column;
			tmpline->column->n = n;
			tmpline->column->next = nullptr;
			tmpline->column->value = value;
			matr.line = tmpline;
			return SUCCESS;
		}

		Line* tmpline = matr.line;
		while (tmpline->next && tmpline->next->m <= m) {
			/*	После этого циклика мы оказываемся либо на строке, после которого вставляем, 
				либо на строке с таким же номером m (чтобы добавлять в строку) */
			tmpline = tmpline->next; 
		}
		if (tmpline->m == m) { //если вставляем новый элемент в строку
			//ищем позицию для вставки - элемент, после которого вставляем:
			Column* tmpcol = tmpline->column;
			while (tmpcol->next && tmpcol->next->n <= n) {
				if (tmpcol->next->n == n)
					return DUPLICATE;
				tmpcol = tmpcol->next;
			}
			if (tmpcol->n == n)
				return DUPLICATE;

			//если нужно вставить элемент в начало списка
			if(tmpcol->n > n){
				Column* newcol = new Column;
				newcol->n = n;
				newcol->value = value;
				newcol->next = tmpcol;
				tmpline->column = newcol;
				return SUCCESS;
			}

			//или обычная вставка
			else {
				Column* newcol = new Column;
				newcol->n = n;
				newcol->value = value;
				newcol->next = tmpcol->next;
				tmpcol->next = newcol;
				return SUCCESS;
			}
		}
		else { //новая строка с её первый элементом
			Line* newline = new Line;
			newline->m = m;
			newline->column = new Column;
			Column* tmpcol = newline->column;
			tmpcol->n = n;
			tmpcol->next = nullptr;
			tmpcol->value = value;

			//вдруг нужно вставить в начало списка?
			//тебе лишь бы вставить, дорогой
			if (tmpline->m > m) {
				newline->next = tmpline;
				matr.line = newline;
			}
			else {
				newline->next = tmpline->next;
				tmpline->next = newline;
			}
			return SUCCESS;
		}
	}

	int output(const char* msg, Matrix matr) {
		if (!matr.line) {
			std::cout << "Матрица пуста!" << std::endl;
			return 1;
		}
		int m = matr.m;
		int n = matr.n;
		Line* tmpline = matr.line; 
		for (int i = 0; i < m; i++) {  
			if (tmpline && tmpline->m == i) {
				Column* tmpcol = tmpline->column;
				for (int j = 0; j < n; j++) {
					if (tmpcol && tmpcol->n == j) {
						std::cout << tmpcol->value << " ";
						tmpcol = tmpcol->next;
					}
					else
						std::cout << "0" << " ";
				}
				tmpline = tmpline->next;
			}
			else {
				for (int j = 0; j < n; j++) {
					std::cout << "0" << " ";
				}
			}
			std::cout << std::endl;
		}
		return SUCCESS;
	}

	void erase(Matrix& matr) {
		if (!matr.line)
			return;
		int m = matr.m;
		int n = matr.n;
		while (matr.line) {
			Line* tempLine = matr.line;
			/*while (tempLine->first) {
				Column* tempCol = tempLine->first;

			}*/
			matr.line = matr.line->next;
			delete tempLine;
		}
	}

	int sumdigits(int a) {
		int sum = 0;
		while (a > 0) {
			sum += a % 10;
			a /= 10;
		}
		return sum;
	}

	Matrix makevector(Matrix matr) {
		Matrix result;
		result.line = nullptr;
		if (!matr.line) {
			return result;
		}
		result.m = 1;
		result.n = matr.m;

		Line* tmpline = matr.line;
		for (int i = 0; i < matr.m; i++) {
			if (tmpline && tmpline->m == i) {
				Column* tmpcol = tmpline->column;
				int firstSum = sumdigits(tmpcol->value); //сумма первого элемента
				int strSum = 0; //сумма подходящих чисел строки
				tmpcol = tmpcol->next;
				while (tmpcol) {
					if (sumdigits(tmpcol->value) == firstSum)
						strSum += tmpcol->value;
					tmpcol = tmpcol->next;
				}
				insert(result, 0, i, strSum);
				tmpline = tmpline->next;
			}
		}
		return result;
	}
}