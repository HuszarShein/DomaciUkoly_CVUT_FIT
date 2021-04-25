#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int scanOper();
int calc();

char sym;
int oper;
double prvni, druhe, res;

int main()
{
	printf("Zadejte vzorec:\n");
	if (scanf("%lf", &prvni) == 0)
	{
		printf("Nespravny vstup.\n");
		return 0;
	}
	scanOper();
	if (scanf("%lf", &druhe) == 0)
	{
		printf("Nespravny vstup.\n");
		return 0;
	}
	while (1) {
		scanf("%c", &sym);
		if ((sym != ' ') && (sym != '\t') && (sym != '='))
		{
			printf("Nespravny vstup.\n");
			return 0;
		}
		if (sym == '=')
			break;
	}
	calc();
	printf("%g", res);
	return 0;
}

int scanOper()
{
	while (1) {
		scanf("%c", &sym);
		if ((sym != ' ') && (sym != '\t') && (sym != '+') && (sym != '-') && (sym != '*') && (sym != '/'))
		{
			printf("Nespravny vstup.\n");
			exit(0);
		}
		switch (sym) {
		case '+':
			oper = 0; 
			return 0;
		case '-':
			oper = 1;
			return 0;
		case '*':
			oper = 2;
			return 0;
		case '/':
			oper = 3;
			return 0;
		}
	}
	return 0;
}

int calc()
{
	switch (oper)
	{
	case 0:
		res = prvni + druhe;
		break;
	case 1:
		res = prvni - druhe;
		break;
	case 2:
		res = prvni * druhe;
		break;
	case 3:
		if (druhe == 0)
		{
			printf("Nespravny vstup.\n");
			exit(0);
		}
		/*if (prvni > 1 && druhe > 1) {
			res = (prvni) / druhe;
		}*/
		/*if (((prvni < 1) && (prvni > -1)) || ((druhe < 1) && (druhe > -1)))
			res = prvni / druhe;
		else
			res = (prvni / druhe);*/
		printf("%g", trunc(prvni / druhe));
		exit(0);
	}
	return 0;
}
