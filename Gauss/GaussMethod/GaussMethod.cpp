#include "MatrixTemp.h"
#include "Rational.h"

int main()
{
	std::ifstream in1;
	std::ofstream out1;
	in1.open("in.txt");
	out1.open("out.txt");

	try {
		int n;
		in1 >> n;

		Matrix<Rational> matr(n);
		matr.input(in1);

		int n2;
		int m2;
		in1 >> n2;
		in1 >> m2;

		Matrix<Rational> b(n2, m2);
		b.input(in1);

		out1 << "Решение через С.Е.Д" << endl;
		solveSystemSED(matr, b).output(out1);
		out1 << endl;
		out1 << "Решение с выбором максимума по столбцу" << endl;
		solveSystemColumn(matr, b).output(out1);
		out1 << endl;
		out1 << "Решение с выбором максимума по подматрице" << endl;
		solveSystemFullMatr(matr, b).output(out1);
		out1 << endl;
		
		out1 << "Определитель A: " << matr.find_determinator().toString() << endl;
		out1 << "Матрица A^-1" << endl;
		matr.findReverse().output(out1);
		out1 << "Определитель A^-1: " << matr.findReverse().find_determinator().toString() << endl;

		in1.close();
		out1.close();
	}
	catch (exception& c)
	{
		out1 << c.what();
	}

	return 0;
}
