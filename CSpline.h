#pragma once
// Интерполяция функции одной переменной, заданной таблично, кубическими сплайнами
#ifndef _GCPP18_MATH_INTERP_CSPLINE_H_
#define _GCPP18_MATH_INTERP_CSPLINE_H_

#define ARRAY_MAX 100 // Максимальное значение узлов интерполяции (значений по x и y)

//#include "NumTypes.h"
//#include <math.h>

namespace GCPP18
{
	class TInterpCSpline
	{
	public:
		//------------------------------------------------------------------------------------------------
		// Создаем конструкторы класса
		TInterpCSpline();

		TInterpCSpline(float const* aX, float const* aY, unsigned Count);
		//------------------------------------------------------------------------------------------------
		// Создаем методы класса
		void Init(float const* aX, float const* aY, unsigned Count);

		void Init();

		float operator()(float x) const;
		//------------------------------------------------------------------------------------------------
		// Размер массива, который мы принимаем по указателю (Он может быть от 1 - ARRAY_MAX)
		unsigned size_ars_XY;
	private:

		// Cоздаем массивы значений по X и Y (узлы интерполяции)
		float X[ARRAY_MAX];

		float Y[ARRAY_MAX];

		// Структура, описывающая СПЛАЙН-ФУНКЦИЮ (ее коэффициенты b, c, d)
		struct TSplineC
		{
			float b;
			float c;
			float d;
		};

		// Создаем массив из ARRAY_MAX структур, описывающих сплайны, а точнее их коэффициенты
		// Вообще, сплайнов ARRAY_MAX - 1, но мы создаем массив на 1 значения больше для расчетов 
		TSplineC SplineC[ARRAY_MAX];
	};

} // namespace GCPP18

#endif