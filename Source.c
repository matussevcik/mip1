#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vypisAutobazar(FILE** fr)
{
	if ((*fr = fopen("autobazar.txt", "r")) == NULL)//ak sa neotvori subor vypise Neotvoreny subor
		printf("Neotvoreny subor\n");

	else
	{
		if ((*fr = fopen("autobazar.txt", "r")) != NULL)//ak uz bol subor otvoreny tak sa zavrie a otvori znovu, ak sa neotvori spravne vypise Neotvoreny subor
		{
			fclose(*fr);

			if ((*fr = fopen("autobazar.txt", "r")) == NULL)
				printf("Neotvoreny subor\n");
		}

		int riadok = 0;
		char znakSuboru = fgetc(*fr);


		while (znakSuboru != EOF)
		{
			while (riadok < 5)//r je pocet odriadkovani
			{
				if (riadok == 0)
					printf("Meno priezvisko: ");
				while (riadok == 0)//vypise meno a priezvisko
				{
					if (znakSuboru == '\n')
						riadok += 1;
					putchar(znakSuboru);
					znakSuboru = fgetc(*fr);
				}

				if (riadok == 1)
					printf("SPZ: ");
				while (riadok == 1)//vypise spz auta ktore bolo predane
				{
					if (znakSuboru == '\n')
						riadok += 1;
					putchar(znakSuboru);
					znakSuboru = fgetc(*fr);
				}

				if (riadok == 2)
					printf("typ auta: ");
				while (riadok == 2)//vypise typ predaneho auta => ak je 1 auto je nove, 0 ojazdene
				{
					if (znakSuboru == '\n')
						riadok += 1;

					if (znakSuboru == '1')
						printf("nove auto\n");
					if (znakSuboru == '0')
						printf("ojazdene auto\n");

					znakSuboru = fgetc(*fr);
				}

				if (riadok == 3)
					printf("cena: ");
				while (riadok == 3)//vypise cenu predaneho auta
				{
					if (znakSuboru == '\n')
						riadok += 1;
					putchar(znakSuboru);
					znakSuboru = fgetc(*fr);
				}

				if (riadok == 4)
					printf("datum: ");
				while (riadok == 4)//vypise datum od kedy je predajca zamestnany
				{
					if (znakSuboru == '\n')
						riadok += 1;
					putchar(znakSuboru);
					znakSuboru = fgetc(*fr);
				}

				putchar(znakSuboru);//vypise prazdny riadok za jednym vypisom
				znakSuboru = fgetc(*fr);
			}

			riadok = 0;//vynuluje pocet odriadkovani
		}
	}
}



void odmena(FILE** fr)
{
	if (*fr == NULL)
	{
		int datumPouzivatela;
		scanf("%d", &datumPouzivatela);
	}

	else
	{
		int datumPouzivatela;
		scanf("%d", &datumPouzivatela);

		rewind(*fr);//vrati subor na zaciatok

		char znakSuboru = fgetc(*fr);

		int pocetZaznamov = 0;

		while (znakSuboru != EOF)//zisti pocet zaznamov, ktory zisti pomocou porovnavania so znakom \n, toto cislo treba predelit 6 aby sme dostali pocet zaznamov
		{
			if (znakSuboru == '\n')
				pocetZaznamov += 1;

			znakSuboru = fgetc(*fr);
		}
		pocetZaznamov /= 6;

		rewind(*fr);

		for (int i = 1; i <= pocetZaznamov; i++)//podla poctu zaznamov prejde subor a nacitava vsetky udaje a ak predajca pracuje aspon rok vypise meno predajcu, spz a odmenu za predaj podla typu auta
		{
			char meno[50], spz[8];
			int typ, datumZamestnania;
			double cenaAuta, odmenaPredajcu;

			fgets(meno, 50, *fr);

			fgets(spz, 8, *fr);

			int dlzkaMena = strlen(meno);
			meno[dlzkaMena - 1] = '\0';

			spz[7] = '\0';

			fscanf(*fr, "%d", &typ);

			fscanf(*fr, "%lf", &cenaAuta);

			fscanf(*fr, "%d", &datumZamestnania);

			fgetc(*fr);
			fgetc(*fr);

			if (typ == 1)
				odmenaPredajcu = cenaAuta * 0.023;
			if (typ == 0)
				odmenaPredajcu = cenaAuta * 0.051;

			if (datumPouzivatela - datumZamestnania >= 10000)
			{
				printf("%s %s %.2lf\n", meno, spz, odmenaPredajcu);
			}

			if (datumPouzivatela - datumZamestnania < 10000)
				;
		}
	}
}



void nacitajPoleSpz(char** spz, FILE** fr)
{
	if (*fr == NULL)
		;
	else
	{
		int pocetZaznamov = 0;

		rewind(*fr);

		char znakSuboru = fgetc(*fr);

		while (znakSuboru != EOF)//zisti pocet zaznamov v subore
		{
			if (znakSuboru == '\n')
				pocetZaznamov += 1;

			znakSuboru = fgetc(*fr);
		}

		pocetZaznamov /= 6;
		rewind(*fr);

		int poziciaPole = 0, pocetRiadkov = 0;

		znakSuboru = fgetc(*fr);

		if (*spz != NULL)//ak uz bolo pole vytvorene uvolni pamat kde bolo pole vytvorene a alokuje pamat nanovo, podla poctu zaznamov a velkosti spz + 1 miesto pre znak \0		
		{
			free(*spz);
			*spz = malloc(pocetZaznamov * 7 * sizeof(char) + 1);
		}

		else
			*spz = malloc(pocetZaznamov * 7 * sizeof(char) + 1);//ak pole este nebolo vytvorene alokuje pamat podla poctu zaznamov a velkosti spz + 1 miesto pre znak \0
		
		
		while (znakSuboru != EOF)
		{
			while (pocetRiadkov == 0)//x je pocet odriadkovani, ku spz sa vzdy dostaneme ked sme v druhom riadku zapisu, teda ked x=1
			{
				if (znakSuboru == '\n')
					pocetRiadkov += 1;

				znakSuboru = fgetc(*fr);
			}

			while (pocetRiadkov == 1)//zapisuje jednotive spz do pola
			{
				if (znakSuboru == '\n')
					pocetRiadkov += 1;

				if (pocetRiadkov == 1)
				{
					(*spz)[poziciaPole] = znakSuboru;
					poziciaPole++;
				}

				znakSuboru = fgetc(*fr);
			}

			while (pocetRiadkov < 6)
			{
				if (znakSuboru == '\n')
					pocetRiadkov += 1;

				znakSuboru = fgetc(*fr);
			}
			
			pocetRiadkov = 0;//vynuluje pocet odriadkovani a dalsim prikazom prechadza na dalsi zapis resp. na znak konca suboru a ukoci sa cyklus

			znakSuboru = fgetc(*fr);
		}

		(*spz)[poziciaPole] = '\0';
	}
}



void s(char** spz)
{
	if (*spz == NULL)
		printf("Pole nie je vytvorene\n");//ak nebolo este pole vytvorene vypise sa Pole nie je vytvorene
	else
	{
		int k = 0;// k je pozicia v poli
		while ((*spz)[k] != '\0')//vypise postupne vsetky spz zapisane v poli v tvare AA BBB CC a kazda spz bude v jednom riadku
		{
			putchar((*spz)[k]);
			k++;
			putchar((*spz)[k]);
			putchar(' ');
			k++;
			putchar((*spz)[k]);
			k++;
			putchar((*spz)[k]);
			k++;
			putchar((*spz)[k]);
			putchar(' ');
			k++;
			putchar((*spz)[k]);
			k++;
			putchar((*spz)[k]);
			putchar('\n');
			k++;
		}
	}
}



void m(char** spz)
{
	if (*spz == NULL)
		printf("Pole nie je vytvorene\n");
	else
	{
		int i = 0, a = 0, pocet = 0, pocz = 0;
		char c = 'A';
		while ((*spz)[i] != '\0' && c <= 'Z')//zisti pocetnost znaku
		{
			while ((*spz)[a] != '\0')
			{
				if ((*spz)[a] == c)
					pocet += 1;
				a++;
			}
			if (pocet > pocz)//ak je pocet daneho znaku vacsi ako velkost doposial najpocetnejsieho znaku tak sa pocet najpocetnejsieho znaku prepise na tuto hodnotu
				pocz = pocet;
			i++;
			c++;
			a = 0;
			pocet = 0;
		}
		c = c - 26;
		char maxznak = 'A';
		i = 0;
		while ((*spz)[i] != '\0' && c <= 'Z')//podla porovnavania s poctom vyskytu najpocetnejsieho znaku najde najpozetnejsi znak
		{
			while ((*spz)[a] != '\0')
			{
				if ((*spz)[a] == c)
					pocet += 1;
				a++;
			}
			if (pocet == pocz)//ak je pocetnost znaku rovna poctu najpocetnejsieho znaku tak sa do premennej maxznak ulozi tento znak
			{
				maxznak = 'A';
				maxznak = maxznak + i;
			}
			i++;
			c++;
			a = 0;
			pocet = 0;
		}
		printf("%c %d\n", maxznak, pocz);
	}
}



void p(char** spz)
{
	if (*spz == NULL)
		printf("Pole nie je vytvorene\n");
	else
	{
		int k = 7, i = 0, x = 0, j = 0, a = 0;
		while ((*spz)[i] != '\0')
		{
			char* c = malloc(7 * sizeof(char) + 1);
			for (j = i, a = 0; j < i + 7; j++, a++)//do pola c sa prepise spz z pola spz
			{
				c[a] = (*spz)[j];
			}
			c[k] = '\0';
			for (int l = 0, m = k - 1; l < (k - 1) / 2; l++, m--)//kontroluje ci je spz ulozena v poli c palindrom 
			{
				if (c[l] == c[m])
					x += 1;
			}
			if (x == 3)//ak je x = 3 spz je palindrom a vypisu sa prve dva znaky z spz
				printf("%c%c\n", c[0], c[1]);
			free(c);
			i += 7;//prechod na dalsiu spz
			x = 0;
		}
	}
}



void z(char** spz)
{
	if ((*spz) == NULL)
		;
	else
	{
		char* c = malloc(2 * sizeof(char) + 1);
		char* maxpc = malloc(2 * sizeof(char) + 1);
		int k = 0, y = 0, x = 0, maxz = 0;
		while ((*spz)[k] != '\0')
		{
			for (int i = y, j = 0; i < y + 2; i++, j++)//nacita prve dva znaky z pola spz do pola c a v dalsich iteraciach nacita prve dva znaky z dalsej spz v poli
			{
				c[j] = (*spz)[i];
			}
			c[2] = '\0';
			int a = 0;
			while ((*spz)[a] != '\0')//zisti pocetnost spz ulozenej v poli c
			{
				if (c[0] == (*spz)[a])
				{
					if (c[1] == (*spz)[a + 1])
					{
						x += 1;
					}
				}
				a += 7;
			}
			if (maxz < x)//porovna pocet najvacsieho vyskytu s novym poctom a ak je novy pocet vacsi prepise pocet najpocetnejsieho okresu a pole obsahujuce spz tohto okresu
			{
				maxz = x;
				for (int i = 0; i < 2; i++)
				{
					maxpc[i] = c[i];
				}
				maxpc[2] = '\0';
			}
			k += 7;
			y += 7;
			x = 0;
		}
		printf("%c%c %d\n", maxpc[0], maxpc[1], maxz); //vypise sa iba najpocetnejsia a ta co bola v subore zapisana skor ak ich bolo viac s rovnakym poctom vyskytov
		free(c);
		free(maxpc);
	}
}



void b(char** spz)
{
	if ((*spz) == NULL)
		printf("Pole nie je vytvorene");
	else
	{
		int x = 0;
		for (char j = '0'; j <= '9'; j++)
		{
			int i = 0;
			while ((*spz)[i] != '\0')
			{
				if ((*spz)[i] == j)
					x += 1;
				i++;
			}
			if (x != 0)
				printf("%c:%d\n", j, x);
			x = 0;
		}
	}
}



int main()
{
	FILE* fr = NULL;
	char c = getchar();
	char* spz = NULL;
	while (c != 0)
	{
		if (c == 'v')
			vypisAutobazar(&fr);
		if (c == 'o')
			odmena(&fr);
		if (c == 'n')
			nacitajPoleSpz(&spz, &fr);
		if (c == 's')
			s(&spz);
		if (c == 'm')
			m(&spz);
		if (c == 'b')
			b(&spz);
		if (c == 'm')
			m(&spz);
		if (c == 'k')
		{
			if ((fr = fopen("autobazar.txt", "r")) == NULL)
				;
			else fclose(fr);
			free(spz);
			return 0;
		}
		c = getchar();
	}
	return 0;
}