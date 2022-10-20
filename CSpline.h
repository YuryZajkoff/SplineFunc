#pragma once
// ������������ ������� ����� ����������, �������� ��������, ����������� ���������
#ifndef _GCPP18_MATH_INTERP_CSPLINE_H_
#define _GCPP18_MATH_INTERP_CSPLINE_H_

#define ARRAY_MAX 100 // ������������ �������� ����� ������������ (�������� �� x � y)

//#include "NumTypes.h"
//#include <math.h>

namespace GCPP18
{
	class TInterpCSpline
	{
	public:
		//------------------------------------------------------------------------------------------------
		// ������� ������������ ������
		TInterpCSpline();

		TInterpCSpline(float const* aX, float const* aY, unsigned Count);
		//------------------------------------------------------------------------------------------------
		// ������� ������ ������
		void Init(float const* aX, float const* aY, unsigned Count);

		void Init();

		float operator()(float x) const;
		//------------------------------------------------------------------------------------------------
		// ������ �������, ������� �� ��������� �� ��������� (�� ����� ���� �� 1 - ARRAY_MAX)
		unsigned size_ars_XY;
	private:

		// C������ ������� �������� �� X � Y (���� ������������)
		float X[ARRAY_MAX];

		float Y[ARRAY_MAX];

		// ���������, ����������� ������-������� (�� ������������ b, c, d)
		struct TSplineC
		{
			float b;
			float c;
			float d;
		};

		// ������� ������ �� ARRAY_MAX ��������, ����������� �������, � ������ �� ������������
		// ������, �������� ARRAY_MAX - 1, �� �� ������� ������ �� 1 �������� ������ ��� �������� 
		TSplineC SplineC[ARRAY_MAX];
	};

} // namespace GCPP18

#endif