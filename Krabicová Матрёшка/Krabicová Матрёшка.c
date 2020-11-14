#include <stdio.h>
#include <stdbool.h>

int res = 0;

void comparasing(double, double, double, double, double, double);
void swap(double*, double*, double*);

int main()
{
	bool A_vetsi, a = false;
	double Ax, Ay, Az, Bx, By, Bz;
	printf("Zadejte strany krabice A:\n");
	if (scanf("%lf%lf%lf", &Ax, &Ay, &Az) != 3)
	{
		printf("Nespravny vstup.\n");
		return 0;
	}
	if ((Ax <= 0) || (Ay <= 0) || (Az <= 0))
	{
		printf("Nespravny vstup.\n");
		return 0;
	}
	printf("Zadejte strany krabice B:\n");
	if (scanf("%lf%lf%lf", &Bx, &By, &Bz) != 3)
	{
		printf("Nespravny vstup.\n");
		return 0;
	}
	if ((Bx <= 0) || (By <= 0) || (Bz <= 0))
	{
		printf("Nespravny vstup.\n");
		return 0;
	}
	swap(&Ax, &Ay, &Az);
	swap(&Bx, &By, &Bz);
	if (((Ax - 0.4) >= Bx) && ((Ay - 0.4) >= By) && ((Az - 0.4) >= Bz))
	{
		A_vetsi = true;
		a = true;
	}
	else if (((Bx - 0.4) >= Ax) && ((By - 0.4) >= Ay) && ((Bz - 0.4) >= Az))
	{
		A_vetsi = false;
		a = true;
	}
	if (a == true)
	{
		if (A_vetsi == true)
		{
			comparasing(Ax, Bx, Ay, By, Az, Bz);
			comparasing(Ax, By, Ay, Bx, Az, Bz);
			comparasing(Ax, By, Ay, Bz, Az, Bx);
			comparasing(Ax, Bx, Ay, Bz, Az, By);
			comparasing(Ax, Bx, Ay, By, Az, Bz);
			comparasing(Ax, Bz, Ay, By, Az, Bx);
			comparasing(Ax, Bz, Ay, Bx, Az, By);
			printf("Do A lze umistit %d krabic(e) B.\n", res);
		}
		else {
			comparasing(Bx, Ax, By, Ay, Bz, Az);
			comparasing(Bx, Ay, By, Ax, Bz, Az);
			comparasing(Bx, Ay, By, Az, Bz, Ax);
			comparasing(Bx, Ax, By, Az, Bz, Ay);
			comparasing(Bx, Ax, By, Ay, Bz, Az);
			comparasing(Bx, Az, By, Ay, Bz, Ax);
			comparasing(Bx, Az, By, Ax, Bz, Ay);
			printf("Do B lze umistit %d krabic(e) A.\n", res);
		}
	}
	else
		printf("Krabice nelze umistit do sebe.\n");
	return 0;
}

void comparasing(double A1, double B1, double A2, double B2, double A3, double B3)
{
	int X = (A1 - 0.4) / B1;
	int Y = (A2 - 0.4) / B2;
	int Z = (A3 - 0.4) / B3;
	int res_local = X * Y * Z;
	if (res < res_local)
		res = res_local;
}

void swap(double *X, double *Y, double *Z)
{
	if (*X > *Y)
	{
		int temp = *X;
		*X = *Y;
		*Y = temp;
	}
	if (*Y > *Z)
	{
		int temp = *Y;
		*Y = *Z;
		*Z = temp;
	}
	if (*X > *Y)
	{
		int temp = *X;
		*X = *Y;
		*Y = temp;
	}
}