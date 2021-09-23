#pragma once

enum {
	SUCCESS = 0,
	WRONG_INPUT = 1,
	DUPLICATE = 2,
	MATR_OVERFLOW = 3
};

namespace Lab_1 {
	struct Column {
		int n;
		int value;
		Column* next;
	};

	struct Line {
		int m;
		Line* next;
		Column* column;
	};

	struct Matrix {
		int m; // кол-во строк 
		int n; // кол-во столбцов
		Line* line;
	};

	template <class T>
	int getNum(T& a) {
		std::cin >> a;
		if (!std::cin.good())
			return -1;
		return 1;
	}

	inline int isgreater(double a, double b) {
		return a > b;
	}

	inline int isless(double a, double b) {
		return a < b;
	}

	int input(Matrix&);
	int insert(Matrix&, int, int, int);
	int output(const char*, Matrix);
	void erase(Matrix&);
	int minmax(Matrix a, double&);
	double minmax(double a[], int m, int(*f)(double, double));
}

