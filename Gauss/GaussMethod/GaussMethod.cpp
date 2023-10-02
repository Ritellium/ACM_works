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

		out1 << "������� ����� �.�.�" << endl;
		solveSystemSED(matr, b).output(out1);
		out1 << endl;
		out1 << "������� � ������� ��������� �� �������" << endl;
		solveSystemColumn(matr, b).output(out1);
		out1 << endl;
		out1 << "������� � ������� ��������� �� ����������" << endl;
		solveSystemFullMatr(matr, b).output(out1);
		out1 << endl;
		
		out1 << "������������ A: " << matr.findDeterminator().toString() << endl;
		out1 << "������� A^-1" << endl;
		matr.findReverse().output(out1);
		out1 << "������������ A^-1: " << matr.findReverse().findDeterminator().toString() << endl;

		in1.close();
		out1.close();
	}
	catch (exception& c)
	{
		out1 << c.what();
	}

	return 0;
}
