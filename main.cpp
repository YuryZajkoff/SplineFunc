#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "CSpline.h"
#include "ThomasAlgorithm(sweep).h"

using namespace std;


// Отлаживаем алгоритм сплайнов
int main()
{
	float accuracy = 0.01;

	const unsigned size_nodes = 6;

	const unsigned size_check = 4;

	srand(85);

	// Массивы, хранящие узлы интерполяции
	float arrayNodes_X[size_nodes]{0, 0.05, 0.27, 1.32, 2.4, 6.4};
	float arrayNodes_Y[size_nodes]{0, 0.361, 1.665, 4.31, 4.863, 5};

	// Массивы, хранящие точки для проверки алгоритма
	float array_X[size_check]{-5, 0.0015, 1.8, 4.48};
	float array_Y[size_check]{0,0.0112,4.664, 4.994};

	// Маcсив рассчитанных значений функции
	float array_calc_Y[size_check]{};

	/*for (unsigned i = 0; i < size_check; ++i)
	{
		array_X[i] = 0 + rand() % (100 - 0 + 1);

		array_Y[i] = 6 * sqrt(array_X[i]);
	}*/

	float temp = 0;

	/*for (unsigned i = 0; i < size_nodes; ++i)
	{
		arrayNodes_X[i] = temp;

		temp += 5;

		arrayNodes_Y[i] = 6 * sqrt(arrayNodes_X[i]);
	}*/
	//--------------------------------------------------------------------------------

	GCPP18::TInterpCSpline Test_Spline(arrayNodes_X, arrayNodes_Y, size_nodes);

	for (unsigned i = 0; i < size_check; i++)
	{
		const float& Y = array_X[i];
		//array_calc_Y[i] = GCPP18::TInterpCSpline::operator()(46.457);
		array_calc_Y[i] = Test_Spline(Y);
	}
	//--------------------------------------------------------------------------------
	for (unsigned i = 0; i < size_check; i++)
	{
		if (abs(array_Y[i] - array_calc_Y[i]) >= accuracy)
		{
			cout << " | " << "=(";
		}
		else
		{
			cout << " | " << "=)";
		}
	}
	std::cout << endl << endl;
	//--------------------------------------------------------------------------------

	cout << "Complite" << endl;

	return 0;
}