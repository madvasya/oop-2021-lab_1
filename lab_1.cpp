#include <iostream>
#include "lab_1.h"

namespace Lab_1 {
	int input(Matrix& matr) {
		const char* pr = "";
		int m, n;
		do {
			std::cout << pr << std::endl;
			std::cout << "¬ведите число строк в матрице: -->" << std::endl;
			pr = "ќшибка! ќжидалось целое число больше нул€.";
			if (getNum(m) < 0)
				return WRONG_INPUT;
		} while (m < 1);
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "¬ведите число столбцов в матрице: -->" << std::endl;
			pr = "ќшибка! ќжидалось целое число больше нул€.";
			if (getNum(n) < 0)
				return WRONG_INPUT;
		} while (n < 1);

		matr.m = m;
		matr.n = n;
		
		insert(matr, 0, 0, 6);
		insert(matr, 1, 1, 9);
		insert(matr, 2, 2, 5);
		insert(matr, 3, 3, 6);
		insert(matr, 4, 4, 8);

		
		return SUCCESS;
	}

	int insert(Matrix& matr, int m, int n, int value) {
		if (!matr.line) {//если вставл€ем першiй элемент (первую строчку)
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
		while (tmpline->next && tmpline->m <= m) {
			tmpline = tmpline->next;
		}
		if (tmpline->m == m) { //если вставл€ем новый элемент в строку
			Column* tmpcol = new Column;
			tmpcol->n = n;
			tmpcol->value = value;
			tmpcol->next = tmpline->column;
			tmpline->column = tmpcol;
			return SUCCESS;
		}
		else {//запилить нормальный пор€док вставки элементов, а то сейчас строчка с m = 1 вставл€етс€ после нулевой
			//долбоебство бл€ть какое-то
			Line* newline = new Line;
			newline->m = m;
			newline->column = new Column;
			Column* tmpcol = newline->column;
			tmpcol->n = n;
			tmpcol->next = nullptr;
			tmpcol->value = value;

			newline->next = tmpline->next;
			tmpline->next = newline;
			return SUCCESS;
		}
	}

	int output(const char* msg, Matrix matr) {
		if (!matr.line) {
			std::cout << "ћатрица пуста!" << std::endl;
			return 1;
		}
		int m = matr.m;
		int n = matr.n;
		Line* tmpline = matr.line; // √≈…— ќ≈ √≈…—“¬ќ » ≈ЅјЌќ≈ √ќ¬Ќќ ЅЋя“№№№№
		for (int i = 0; i < m; i++) {  
			if (tmpline->column && tmpline->m == i) {
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
				for (int j = 0; j < m; j++) {
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
}