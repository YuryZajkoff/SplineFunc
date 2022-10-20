#include "ThomasAlgorithm(sweep).h"

namespace GCPP18
{

	bool TSysLinEqSolverThomasAlg::Calc_temp(float* ptr_C, TRatios_Equation* ptr_ThomasAlgEqC_Ratio, unsigned size_XY)
	{
		//если количество уравнений меньше 2, вернуть ложь
		if (size_XY - 2 < 2)  return false;

		//создание массива структур коэффициентов A и B (-3 берется из того условия, что
		// 1) -1 берется из условия количества сплайнов меньше на 1 от количсетва узлов интерполяции
		// 2) -1 берется из условия С1 = 0 
		// 3) -1 берется из уловия расчета коэф С, Сn находится с помощью пром коэф А(n-1) и B(n-1)
		TIntermediate_Ratio_Eq_AB Eq_AB[ARRAY_MAX - 3]{};

		//создание ссылки на 0 элемент вектора, хранящего значения коэф. необходимых для нахождения С
		const TRatios_Equation& EqRatioC_0 = ptr_ThomasAlgEqC_Ratio[0];

		//создание ссылки на 0 элемент вектора, хранящего значения промежуточных коэф. А и В
		TIntermediate_Ratio_Eq_AB& Eq_AB_0 = Eq_AB[0];

		// Находим первое значение промежуточных коэф. А и В
		Eq_AB_0.A = -EqRatioC_0.c / EqRatioC_0.b;
		Eq_AB_0.B = EqRatioC_0.d / EqRatioC_0.b;

		//unsigned FirstLoopEndIndex = EqC.size() - 1;

		// Расчет промежуточных (прогоночных коэф. A и B)
		for (unsigned i = 1; i < size_XY - 3; ++i)
		{
			const TRatios_Equation& EqC_i = ptr_ThomasAlgEqC_Ratio[i];

			TIntermediate_Ratio_Eq_AB& Eq_AB_i = Eq_AB[i];

			const TIntermediate_Ratio_Eq_AB& Eq_AB_im1 = Eq_AB[i - 1];

			float e = EqC_i.a * Eq_AB_im1.A + EqC_i.b;

			Eq_AB_i.A = -EqC_i.c / e;

			Eq_AB_i.B = (EqC_i.d - EqC_i.a * Eq_AB_im1.B) / e;
		}

		// Создаем ссылку на последний элемент массива типа float_t, хранящего коэф С
		float& c_Array = ptr_C[size_XY - 3];

		// Создаем ссылку на последний элемент массива структур, хранящего коэф при С
		const TRatios_Equation& Rat_Eq_C_N = ptr_ThomasAlgEqC_Ratio[size_XY - 3];

		// Создаем ссылку на последний элемент массива структур, хранящего коэф А и В
		const TIntermediate_Ratio_Eq_AB& Imt_RatAB_Nm1 = Eq_AB[size_XY - 4];

		// Считаем последний коэф С и записываем его в массив
		c_Array = (Rat_Eq_C_N.d - Rat_Eq_C_N.a * Imt_RatAB_Nm1.B) / (Rat_Eq_C_N.b + Rat_Eq_C_N.a * Imt_RatAB_Nm1.A);

		//Рассчитываем коэффициенты С
		for (unsigned i = size_XY - 3; i > 0; --i)
		{
			float& c_Array_i = ptr_C[i];

			float& c_Array_m1 = ptr_C[i - 1];

			const TIntermediate_Ratio_Eq_AB& Imt_RatAB_Nm1 = Eq_AB[i - 1];

			c_Array_m1 = Imt_RatAB_Nm1.A * c_Array_i + Imt_RatAB_Nm1.B;
		}
		return true;
	}
} // namespace GCPP18
