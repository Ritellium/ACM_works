#include "../Headers/MatrixTemp.h"
#include "../Headers/Double.h"
#include <Windows.h>

/*
1. ��� �������� n ������������� ��������� ������� ���������� ������� ������� n*n, ������� ������������ �������������. �������� ������� �������������� ����� � ����� ������� ����� �������.
2. ������������� ��������� ������� ������ ������� �. (��� ����� ����� �������).
3. �� ��������������� ������ ��������� ������ b ��������� ������ ������� �� ������� b = �x.

4. ��� ���������� ������:
�) ����� ������� ������� ���������� ��������. ��������� �������� ����� ���������� ������� �������;
6) ����� �������, �������� � ������� �������. ��������� ��������;
�) ��������� ������������ ������� �������; �) ����� ����� ��������������� (����� �� �����);
� ������, ���� �����-���� �� ������������ ������� ������� ��������� �������, ����������� ���� ������� ��������������� ����� ���������� ������������� ������

������� 2:
-- ����� ������ � ������� �������� �������� �� ������, 
-- ����� ���������, 
-- ����� �������, 
-- ����� ������������ ������.
*/

int main()
{
	SetConsoleOutputCP(1251);
	try {
		int n = 3;
		std::cout << "������� ����������� ������� ������� n > 0: " << std::endl;
		std::cin >> n;

		double rad;
		std::cout << "������� ������ ���������� ����� (x �� [-r, r]) r > 0: " << std::endl;
		std::cin >> rad;

		Double bound_diag(rad/double(n));
		Double bound(rad);
		//Double::set_type_precision(5);

		Matrix A(n);
		A.generate_diagDomination(bound_diag);
		std::cout << "��������������� ������� A" << std::endl;
		A.output(std::cout);

		Matrix x(n, 1);
		x.generate(bound);
		std::cout << "��������������� ������� ����������� x" << std::endl;
		x.output(std::cout);

		Matrix b = A * x;
		std::cout << "����������� ������� �������������� b" << std::endl;
		b.output(std::cout);
		std::cout  << std::endl;

		// ����������

		std::cout << "������� ������� ������ � ������� ��������� �� ������" << std::endl;
		solve_system_choiceMaxInLine(A, b).output(std::cout) << std::endl;

		std::cout << "������� ������� ���������" << std::endl;
		solve_system_reflection(A, b).output(std::cout) << std::endl;

		std::cout << "������� ������������ ������� ������-�������" << std::endl;
		solve_system_zeidel(A, b).output(std::cout) << std::endl;

		std::cout << "������� ������������ ������� ������������ ������" << std::endl;
		solve_system_gradient(A, b).output(std::cout) << std::endl;
		

		std::cout << "������������ A: " << A.find_determinator().toString() << endl;
	
		auto A_rev = A.findReverse();
		auto the_num = A.norm_sphere() * A_rev.norm_sphere();

		std::cout << "����� ��������������� A: " << the_num << endl;

		std::cout << "������� A^-1: " << endl;
		A_rev.output(std::cout);

		
	}
	catch (exception& c)
	{
		std::cout << c.what();
	}

	return 0;
}
