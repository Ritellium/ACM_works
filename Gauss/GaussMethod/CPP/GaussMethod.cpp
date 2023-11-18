#include "../Headers/MatrixTemp.h"
#include "../Headers/Double.h"
#include <Windows.h>

/*
1. При заданном n сгенерировать случайным образом квадратную матрицу размера n*n, имеющую диагональное доминирование. Элементы матрицы действительные числа с двумя знаками после запятой.
2. Сгенерировать случайным образом вектор решений х. (два знака после запятой).
3. По сгенерированным данным вычислить вектор b свободных членов системы по формуле b = Аx.

4. Для полученных данных:
а) найти решение системы указанными методами. Выполнить проверку путем вычисления вектора невязки;
6) найти матрицу, обратную к матрице системы. Выполнить проверку;
в) вычислить определитель матрицы системы; г) найти число обусловленности (норма на выбор);
В случае, если какой-либо из предложенных методов требует симметрии матрицы, построенную выше систему модернизировать путем применения трансформации Гаусса

Вариант 2:
-- Метод Гаусса с выбором главного элемента по строке, 
-- Метод отражений, 
-- Метод Зейделя, 
-- Метод градиентного спуска.
*/

int main()
{
	SetConsoleOutputCP(1251);
	try {
		int n = 3;
		std::cout << "Введите размерность матрицы системы n > 0: " << std::endl;
		std::cin >> n;

		double rad;
		std::cout << "Введите радиус случайного числа (x из [-r, r]) r > 0: " << std::endl;
		std::cin >> rad;

		Double bound_diag(rad/double(n));
		Double bound(rad);
		//Double::set_type_precision(5);

		Matrix A(n);
		A.generate_diagDomination(bound_diag);
		std::cout << "Сгенерированная матрица A" << std::endl;
		A.output(std::cout);

		Matrix x(n, 1);
		x.generate(bound);
		std::cout << "Сгенерированный столбец неизвестных x" << std::endl;
		x.output(std::cout);

		Matrix b = A * x;
		std::cout << "Вычисленный столбец неоднородности b" << std::endl;
		b.output(std::cout);
		std::cout  << std::endl;

		// Вычисления

		std::cout << "Решение методом Гаусса с выбором максимума по строке" << std::endl;
		solve_system_choiceMaxInLine(A, b).output(std::cout) << std::endl;

		std::cout << "Решение методом отражений" << std::endl;
		solve_system_reflection(A, b).output(std::cout) << std::endl;

		std::cout << "Решение итерационным методом Гаусса-Зейделя" << std::endl;
		solve_system_zeidel(A, b).output(std::cout) << std::endl;

		std::cout << "Решение итерационным методом Градиентного спуска" << std::endl;
		solve_system_gradient(A, b).output(std::cout) << std::endl;
		

		std::cout << "Определитель A: " << A.find_determinator().toString() << endl;
	
		auto A_rev = A.findReverse();
		auto the_num = A.norm_sphere() * A_rev.norm_sphere();

		std::cout << "Число обусловленности A: " << the_num << endl;

		std::cout << "Матрица A^-1: " << endl;
		A_rev.output(std::cout);

		
	}
	catch (exception& c)
	{
		std::cout << c.what();
	}

	return 0;
}
