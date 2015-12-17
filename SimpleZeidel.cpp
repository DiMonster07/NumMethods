#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int size_m = 4;
float e = 0.0001;
float matrix [4][4] =
{{6.22f, 1.42f, -1.72f, 1.91f},
 {1.42f, 5.33f, 1.11f, -1.82f},
 {-1.72f, 1.11f, 5.24f, 1.42f},
 {1.91f, -1.82f, 1.42f, 6.55f}};

float b [] = {7.53, 6.06, 8.05, 8.06};

int k = 4;

void CreateM ();
void PrintM ();
void SimpleIteration ();
void Zeidel();

int main()
{
	CreateM();
	PrintM();
	cout << "Simple Iteration" << endl;
    SimpleIteration();
    cout << "Zeidel" << endl;
	Zeidel();
	return 0;
}

void Zeidel()
{
	float x1, x2, x3, x4 = 0;
	x1 = b[0]/matrix[0][0];
	x2 = b[1]/matrix[1][1] - float(matrix[1][0]/matrix[1][1])*x1;
	x3 = b[2]/matrix[2][2] - float(matrix[2][0]/matrix[2][2])*x1 - float(matrix[2][1]/matrix[2][2])*x2;
	x4 = b[3]/matrix[3][3] - float(matrix[3][0]/matrix[3][3])*x1 - float(matrix[3][1]/matrix[3][3])*x2
			- float(matrix[3][2]/matrix[3][3])*x3;
	float te = 999999.000;
	int c = 0;
	while (te > e)
	{
		c++;
		float t1 = float(b[0]/matrix[0][0]) - float(matrix[0][1]/matrix[0][0])*x2 -
				float(matrix[0][2]/matrix[0][0])*x3 - float(matrix[0][3]/matrix[0][0])*x4;
		float t2 = float(b[1]/matrix[1][1]) - float(matrix[1][0]/matrix[1][1])*t1 -
				float(matrix[1][2]/matrix[1][1])*x3 - float(matrix[1][3]/matrix[1][1])*x4;
		float t3 = float(b[2]/matrix[2][2]) - float(matrix[2][0]/matrix[2][2])*t1 -
				float(matrix[2][1]/matrix[2][2])*t2 - float(matrix[2][3]/matrix[2][2])*x4;
		float t4 = float(b[3]/matrix[3][3]) - float(matrix[3][0]/matrix[3][3])*t1 -
				float(matrix[3][1]/matrix[3][3])*t2 - float(matrix[3][2]/matrix[3][3])*t3;
		te = max(max(fabs(t1 - x1), fabs(t2 - x2)), max(fabs(t3 - x3), fabs(t4 - x4)));
		printf("%f\n", te);
		x1 = t1; x2 = t2; x3 = t3; x4 = t4;
	}
	cout << "Count iteration: " << c + 1 << endl;
	printf("x1: %f; x2: %f; x3: %f; x4: %f;\n", x1, x2, x3, x4);
}

void SimpleIteration ()
{
	float x1, x2, x3, x4 = 0;
	x1 = float(b[0]/matrix[0][0]); x2 = float(b[1]/matrix[1][1]); x3 = float(b[2]/matrix[2][2]); x4 = float(b[3]/matrix[3][3]);
	float te = 999999.;
	int c = 0;
	while (te > e)
	{
		c++;
		float t1 = float(b[0]/matrix[0][0]) - float(matrix[0][1]/matrix[0][0])*x2 -
				float(matrix[0][2]/matrix[0][0])*x3 - float(matrix[0][3]/matrix[0][0])*x4;
		float t2 = float(b[1]/matrix[1][1]) - float(matrix[1][0]/matrix[1][1])*x1 -
				float(matrix[1][2]/matrix[1][1])*x3 - float(matrix[1][3]/matrix[1][1])*x4;
		float t3 = float(b[2]/matrix[2][2]) - float(matrix[2][0]/matrix[2][2])*x1 -
				float(matrix[2][1]/matrix[2][2])*x2 - float(matrix[2][3]/matrix[2][2])*x4;
		float t4 = float(b[3]/matrix[3][3]) - float(matrix[3][0]/matrix[3][3])*x1 -
				float(matrix[3][1]/matrix[3][3])*x2 - float(matrix[3][2]/matrix[3][3])*x3;
		te = max(max(fabs(t1 - x1), fabs(t2 - x2)), max(fabs(t3 - x3), fabs(t4 - x4)));
		printf("%f\n", te);
		x1 = t1; x2 = t2; x3 = t3; x4 = t4;
	}
	cout << "Count iteration: " << c + 1 << endl;
	printf("x1: %f; x2: %f; x3: %f; x4: %f;\n", x1, x2, x3, x4);
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

void CreateM ()
{
	for (int i = 0; i < size_m; i++)
		matrix[i][i] += k;
}
