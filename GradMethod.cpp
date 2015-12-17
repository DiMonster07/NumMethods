#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int size_m = 4;
float e = 0.0001;

float matrix [4][4] =
{{1.67f, 0.32f, 0.12f, 0.57f},
 {0.32f, 4.17f, 0.65f, 0.15f},
 {0.12f, 0.65f, 3.15f, 0.22f},
 {0.57f, 0.15f, 0.22f, 1.84f}};

float matrixT[4][4]{0};
float b[] = {1.34, 0.85, 1.29, 2.11};
float xp[4]{0};
float r[4]{0};
float ATr[4]{0}; 
float AATr[4]{0}; 
float t[4]{0};

int k = 4;

void PrintM();
void GradMethod();
void transposeMatrix();
void CalcR();
void CalcATr();
void CalcAATr();

int main()
{
	cout << "Matrix: " << endl;
	PrintM();
	cout << "GradMethod" << endl;
	GradMethod();
	return 0;
}

void GradMethod()
{
	int c = 0;
	float et = 99999999;
	xp[0] = float(b[0]/matrix[0][0]); xp[1] = float(b[1]/matrix[1][1]); 
	xp[2] = float(b[2]/matrix[2][2]); xp[3] = float(b[3]/matrix[3][3]);
	transposeMatrix();
	while (et > e)
	{
		CalcR();
		CalcATr();
		CalcAATr();
		float u = float((r[0]*AATr[0] + r[1]*AATr[1] + r[2]*AATr[2] + r[3]*AATr[3])/(AATr[0]*AATr[0] + AATr[1]*AATr[1] + AATr[2]*AATr[2] + AATr[3]*AATr[3]));
		for (int i = 0; i < 4; i++)
			t[i] = xp[i] - u*ATr[i];
		et = max(max(fabs(t[0] - xp[0]), fabs(t[1] - xp[1])), max(fabs(t[2] - xp[2]), fabs(t[3] - xp[3])));
		for (int i = 0; i < 4; i++)
			xp[i] = t[i];
		c++;
	}
	printf("x1: %f; x2: %f; x3: %f; x4: %f;", xp[0], xp[1], xp[2], xp[3]);
	cout << c << endl;
}

void CalcAATr()
{
	for (int i = 0; i < 4; i++)
	{
		AATr[i] = 0;
		for (int j = 0; j < 4; j++)
			AATr[i] += matrix[i][j]*ATr[j];
	}
}

void CalcATr()
{
	for (int i = 0; i < 4; i++)
	{
		ATr[i] = 0;
		for (int j = 0; j < 4; j++)
			ATr[i] += matrixT[i][j]*r[j];
	}
}

void CalcR()
{
	for (int i = 0; i < 4; i++)
	{
		r[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			r[i] += matrix[i][j]*xp[j];
		}
		r[i] -= b[i];
	}
}

void transposeMatrix()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrixT[i][j] = matrix[j][i];
}

void PrintM ()
{
	for (int i = 0; i < size_m; i++)
	{
		for (int j = 0; j < size_m; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << b[i] << endl;
	}
	cout << endl;
}