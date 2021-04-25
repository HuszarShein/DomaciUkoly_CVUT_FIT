#include <stdio.h>
#include <stdlib.h>

int scanRGB();
int scanZavorky();
void scanNum();
int scanCarky();
void prekladDo16(int num);
void symbol(int mod1);

char res[7];
int a = 1;

int prvni, druha, treti;

int main()
{
	printf("Zadejte barvu v RGB formatu:\n");
	scanRGB();
	scanZavorky();
	prekladDo16(prvni);
	prekladDo16(druha);
	prekladDo16(treti);
	res[6] = '\0';
	printf("#%s\n", res);
	return 0;
}

int scanRGB()
{
	char r, g, b;
	while (1) {
		scanf("%c", &r);
		if ((r != ' ') && (r != '\t') && (r != 'r'))
		{
			printf("Nespravny vstup.\n");
			exit(0);
		}
		else if (r == 'r')
		{
			scanf("%c%c", &g, &b);
			if ((g != 'g') || (b != 'b'))
			{
				printf("Nespravny vstup.\n");
				exit(0);
			}
			else
				return 1;
		}
	};
}

int scanZavorky()
{
	char Zavorka;
	while (1) {
		scanf("%c", &Zavorka);
		if ((Zavorka != ' ') && (Zavorka != '\t') && (Zavorka != '('))
		{
			printf("Nespravny vstup.\n");
			exit(0);
		}
		else if (Zavorka == '(')
		{
			scanNum();
			while (1) {
				scanf("%c", &Zavorka);
				if ((Zavorka != ' ') && (Zavorka != '\t') && (Zavorka != ')'))
				{
					printf("Nespravny vstup.\n");
					exit(0);
				}
				else if (Zavorka == ')')
				{
					return 1;
				}
			};
		}
	};
}

void scanNum()
{
	scanf("%d", &prvni);
	scanCarky();
	scanf("%d", &druha);
	scanCarky();
	scanf("%d", &treti);
	if ((prvni > 255) || (prvni < 0) || (druha > 255) || (druha < 0) || (treti > 255) || (treti < 0))
	{
		printf("Nespravny vstup.\n");
		exit(0);
	}
}

int scanCarky()
{
	char carka;
	while (1) {
		scanf("%c", &carka);
		if ((carka != ' ') && (carka != '\t') && (carka != ','))
		{
			printf("Nespravny vstup.\n");
			exit(0);
		}
		else if (carka == ',')
		{
			return 1;
		}
	};
}

void prekladDo16(int num)
{
	int mod1;
	mod1 = num % 16;
	if ((9 < mod1) && (mod1 < 16))
		symbol(mod1);
	else
	{
		res[a] = mod1 +48;
		a--;
	}
	num = num / 16;
	mod1 = num % 16;
	if ((9 < mod1) && (mod1 < 16))
		symbol(mod1);
	else
	{
		res[a] = mod1 + 48;
		a--;
	}
	a = a + 4;
}

void symbol(int num)
{
	switch (num)
	{
	case 10:
		res[a] = 'A';
		break;
	case 11:
		res[a] = 'B';
		break;
	case 12:
		res[a] = 'C';
		break;
	case 13:
		res[a] = 'D';
		break;
	case 14:
		res[a] = 'E';
		break;
	case 15:
		res[a] = 'F';
		break;
	}
	a--;
}