#include "ThomasAlgorithm(sweep).h"
#include "CSpline.h"



namespace GCPP18
{
    //using namespace std;
    // ��������� ������������ ������ TInterpCSpline (������� ��� ����������)
    TInterpCSpline::TInterpCSpline() { }

    // ������ ����������� ��������� ������ ����������� ��������� �� ������� aX � aY, 
    // ��� �������� �������� ����� ������������, �  ����� ����� ���� ��������
    TInterpCSpline::TInterpCSpline(float const* aX, float const* aY, unsigned Count)
    {
        for (unsigned i = 0; i < ARRAY_MAX; i++)
        {
            X[i] = -1;

            Y[i] = -1;
        }

        Init(aX, aY, Count);
    }

    // ��������� ����� Init, ������� ��������� ����������� ��� ���� ��������, ��� 2 �����������
    void TInterpCSpline::Init(float const* aX, float const* aY, unsigned Count)
    {
        size_ars_XY = Count;

        if (size_ars_XY > ARRAY_MAX) size_ars_XY = ARRAY_MAX;

        // ��������� ������� X � Y �������� size_arrays_XY (������, �� ���� �����)
        for (unsigned i = 0; i < size_ars_XY; i++)
        {
            X[i] = (*(aX + i));

            Y[i] = (*(aY + i));
        }

        // �������� ����� Init ��� ����������
        Init();
    }

    // ��������� ����� Init ��� ����������
    void TInterpCSpline::Init()
    {
        // ������� ������ h, �������� � ARRAY_MAX
        float h[ARRAY_MAX - 1]{};

        // ��������� ������ h
        for (unsigned i = 0; i < size_ars_XY - 1; ++i)  h[i] = X[i + 1] - X[i];

        // ������� ������ ��������, ����������� ������������ ��� ����. � (- 2 �.�. ��������� �������� �� 1 ������, ��� ���������� ������� �����,
        // � ��� 1 ������� ������� �� ���� �����������, ��� ����. �1 = 0 � ��������� ��� ���� ��������� ��������� �� �����)
        GCPP18::TSysLinEqSolverThomasAlg::TRatios_Equation ThomasAlgEqC_Ratio[ARRAY_MAX - 2]{};

        // ��������� ������ ��������, ����������� � ����. �
        for (unsigned i = 0; i < size_ars_XY - 2; ++i)
        {
            GCPP18::TSysLinEqSolverThomasAlg::TRatios_Equation& ThomasAlgEqC_i = ThomasAlgEqC_Ratio[i];

            ThomasAlgEqC_i.a = h[i];

            ThomasAlgEqC_i.b = 2 * (h[i] + h[i + 1]);

            ThomasAlgEqC_i.c = h[i + 1];

            ThomasAlgEqC_i.d = 3 * ((Y[i + 2] - Y[i + 1]) / h[i + 1] - (Y[i + 1] - Y[i]) / h[i]);
        }


        // ������� ������ Thomas_Alg_C (��� ����� ��������� ����. � ��� ������ �������)
        // 1) -1 - �������� �� 1 ������, ��� ���������� �����
        // 2) -1 - �1 = 0, ������� ��� �� ���������
        float Thomas_Alg_C[ARRAY_MAX - 2];

        // �������� static ������� ��� ������ �������� (������ ������������� �)
        GCPP18::TSysLinEqSolverThomasAlg::Calc_temp(Thomas_Alg_C, ThomasAlgEqC_Ratio, size_ars_XY);

        // ����������� ������������ � ��� 1 � n + 1 ������� = 0 (�� �������� ������-�������)
        SplineC[0].c = 0;
        SplineC[size_ars_XY - 1].c = 0;

        // ����������� ����. � ����������� �������� � ������� ������ ��������
        for (unsigned i = 0; i < size_ars_XY - 2; ++i)
        {
            SplineC[i + 1].c = Thomas_Alg_C[i];
        }

        //������� ������������ b � d
        for (unsigned i = 0; i < size_ars_XY - 1; ++i)
        {
            TSplineC& SplineC_i = SplineC[i], & SplineC_ip1 = SplineC[i + 1];

            SplineC_i.b = (Y[i + 1] - Y[i]) / h[i] - h[i] * (SplineC_ip1.c + 2 * SplineC_i.c) / 3;

            SplineC_i.d = (SplineC_ip1.c - SplineC_i.c) / (3 * h[i]);
        }
        //SplineC.pop_back();
    }

    float TInterpCSpline::operator()(float x) const
    {
        if (size_ars_XY < 4)  return 0;

        if (x <= X[0])  return Y[0];

        if (x >= X[size_ars_XY - 1])  return Y[size_ars_XY - 1];

        unsigned i = 0;

        for (; i < size_ars_XY - 2; ++i)
        {
            if (x >= X[i] && x < X[i + 1])  break;
        }

        const TSplineC& Spl_Rat = SplineC[i];

        float DX = x - X[i], DX2 = DX * DX, DX3 = DX2 * DX;

        return  Y[i] + Spl_Rat.b * DX + Spl_Rat.c * DX2 + Spl_Rat.d * DX3;
    }

} // namespace GCPP18