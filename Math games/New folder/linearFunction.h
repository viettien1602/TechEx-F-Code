#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double arr[20];

void solveCrammer2nd(double a1, double b1, double c1, double a2, double b2, double c2);
void solveCrammer3rd(double a1, double b1, double c1, double d1, double a2, double b2, double c2, double d2, double a3, double b3, double c3, double d3);
void solveCrammer4th(double a11, double a12, double a13, double a14, double b1, double a21, double a22, double a23, double a24, double b2, double a31, double a32, double a33, double a34, double b3, double a41, double a42, double a43, double a44, double b4);
double determ4x4Matrix(double matrix[4][4]);
void fileToNumLinear();
void mainSolveCrammer2nd();
void mainSolveCrammer3rd();
void mainSolveCrammer4th();


void mainSolveCrammer4th(){

    fileToNumLinear();

	solveCrammer4th(arr[0], arr[1], arr[2], arr[3], arr[4],
					arr[5], arr[6], arr[7], arr[8], arr[9],
					arr[10], arr[11], arr[12], arr[13], arr[14],
					arr[15], arr[16], arr[17], arr[18], arr[19]);

    for (int i = 0; i < 20; i++)
    {
        arr[i] = 0;
    }
}

void mainSolveCrammer3rd()
{
    fileToNumLinear();

	solveCrammer3rd(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9], arr[10], arr[11]);

    for (int i = 0; i < 20; i++)
    {
        arr[i] = 0;
    }
}

void mainSolveCrammer2nd()
{

    fileToNumLinear();

	solveCrammer2nd(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
    for (int i = 0; i < 20; i++)
    {
        arr[i] = 0;
    }
}

void solveCrammer2nd(double a1, double b1, double c1, double a2, double b2, double c2)
{
	FILE *fo;
	fo = fopen("OUTPUT.TXT", "w");

    double d = a1 * b2 - a2 * b1;
    double dx = c1 * b2 - b1 * c2;
    double dy = a1 * c2 - c1 * a2;

    if (d == 0)
    {
        if (dx == dy)
        {
            fprintf(fo, "Countless_solutions");
        }
        else
        {
            fprintf(fo, "No_solution");
        }
    }
    else
    {
        fprintf(fo, "%g\n", dx / d);
        fprintf(fo, "%g", dy / d);
    }
    fclose(fo);
}


void solveCrammer3rd(double a1, double b1, double c1, double d1,
					 double a2, double b2, double c2, double d2,
					 double a3, double b3, double c3, double d3)
{
	FILE *fo;
    fo = fopen("OUTPUT.TXT", "w");

    double  d = a1 * b2 * c3 + b1 * c2 * a3 + a2 * b3 * c1 - c1 * b2 * a3 - b1 * a2 * c3 - a1 * b3 * c2;
    double dx = d1 * b2 * c3 + b1 * c2 * d3 + d2 * b3 * c1 - c1 * b2 * d3 - b1 * d2 * c3 - c2 * b3 * d1;
    double dy = a1 * d2 * c3 + d1 * c2 * a3 + a2 * d3 * c1 - c1 * d2 * a3 - d1 * a2 * c3 - c2 * d3 * a1;
    double dz = a1 * b2 * d3 + b1 * d2 * a3 + a2 * b3 * d1 - d1 * b2 * a3 - b1 * a2 * d3 - d2 * b3 * a1;


    if (d == 0)
    {
        if ((d == 0) && (dy == 0) && (dz == 0))
        {
            fprintf(fo, "Countless_solutions");
        }
        else
        {
            fprintf(fo, "No_solutions");
        }
    }
    else
    {
        fprintf(fo, "%g\n", dx / d);
        fprintf(fo, "%g\n", dy / d);
        fprintf(fo, "%g", dz / d);
    }

    fclose(fo);
}

void solveCrammer4th(double a11, double a12, double a13, double a14, double b1,
                     double a21, double a22, double a23, double a24, double b2,
                     double a31, double a32, double a33, double a34, double b3,
                     double a41, double a42, double a43, double a44, double b4)
{
	FILE *fo;
	fo = fopen("OUTPUT.TXT", "w");

    double D[4][4], Dx[4][4], Dy[4][4], Dz[4][4], Dt[4][4];
    double x, y, z, t;

    D[0][0] = a11;  D[0][1] = a12;  D[0][2] = a13;  D[0][3] = a14;
    D[1][0] = a21;  D[1][1] = a22;  D[1][2] = a23;  D[1][3] = a24;
    D[2][0] = a31;  D[2][1] = a32;  D[2][2] = a33;  D[2][3] = a34;
    D[3][0] = a41;  D[3][1] = a42;  D[3][2] = a43;  D[3][3] = a44;

    Dx[0][0] = b1; Dx[0][1] = a12; Dx[0][2] = a13; Dx[0][3] = a14;
    Dx[1][0] = b2; Dx[1][1] = a22; Dx[1][2] = a23; Dx[1][3] = a24;
    Dx[2][0] = b3; Dx[2][1] = a32; Dx[2][2] = a33; Dx[2][3] = a34;
    Dx[3][0] = b4; Dx[3][1] = a42; Dx[3][2] = a43; Dx[3][3] = a44;

    Dy[0][0] = a11; Dy[0][1] = b1; Dy[0][2] = a13; Dy[0][3] = a14;
    Dy[1][0] = a21; Dy[1][1] = b2; Dy[1][2] = a23; Dy[1][3] = a24;
    Dy[2][0] = a31; Dy[2][1] = b3; Dy[2][2] = a33; Dy[2][3] = a34;
    Dy[3][0] = a41; Dy[3][1] = b4; Dy[3][2] = a43; Dy[3][3] = a44;

    Dz[0][0] = a11; Dz[0][1] = a12; Dz[0][2] = b1; Dz[0][3] = a14;
    Dz[1][0] = a21; Dz[1][1] = a22; Dz[1][2] = b2; Dz[1][3] = a24;
    Dz[2][0] = a31; Dz[2][1] = a32; Dz[2][2] = b3; Dz[2][3] = a34;
    Dz[3][0] = a41; Dz[3][1] = a42; Dz[3][2] = b4; Dz[3][3] = a44;

	Dt[0][0] = a11;  Dt[0][1] = a12;  Dt[0][2] = a13;  Dt[0][3] = b1;
    Dt[1][0] = a21;  Dt[1][1] = a22;  Dt[1][2] = a23;  Dt[1][3] = b2;
    Dt[2][0] = a31;  Dt[2][1] = a32;  Dt[2][2] = a33;  Dt[2][3] = b3;
    Dt[3][0] = a41;  Dt[3][1] = a42;  Dt[3][2] = a43;  Dt[3][3] = b4;


    double det = determ4x4Matrix(D);
    double detX = determ4x4Matrix(Dx);
    double detY = determ4x4Matrix(Dy);
    double detZ = determ4x4Matrix(Dz);
    double detT = determ4x4Matrix(Dt);

    if (det == 0)
    {
    	if((detX == 0) && (detY == 0) && (detZ == 0) && (detT == 0)){
            fprintf(fo, "No_specific_solution");
		}
		else{
            fprintf(fo, "No_solutions");
		}
    }
    else
    {
        x = detX / det;
        y = detY / det;
        z = detZ / det;
        t = detT / det;

        fprintf(fo, "%g\n", x);
        fprintf(fo, "%g\n", y);
        fprintf(fo, "%g\n", z);
        fprintf(fo, "%g", t);
    }

    fclose(fo);
}

double determ4x4Matrix(double matrix[4][4]){

    double s1, s2, s3, s4;

    s1 = matrix[0][0] * (matrix[1][1] * (matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3]) - matrix[1][2] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) + matrix[1][3] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]));
    s2 = matrix[0][1] * (matrix[1][0] * (matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3]) - matrix[1][2] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) + matrix[1][3] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]));
    s3 = matrix[0][2] * (matrix[1][0] * (matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3]) - matrix[1][1] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) + matrix[1][3] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]));
    s4 = matrix[0][3] * (matrix[1][0] * (matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2]) - matrix[1][1] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]) + matrix[1][2] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]));

	double det = s1 - s2 + s3 - s4;
    return det;
}


void fileToNumLinear(){

	FILE *fi;
	int rank;

    fi = fopen("INPUT.txt", "r");
	fscanf(fi, "%d", &rank);

	for(int i = 0; i < rank * (rank + 1); i++)
	{
		double number;
		fscanf(fi, "%lf", &number);
		arr[i] = number;
	}

    fclose(fi);
}
