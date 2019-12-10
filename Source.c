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



void vypisSpzPole(char** spz)
{
	if (*spz == NULL)
		printf("Pole nie je vytvorene\n");//ak nebolo este pole vytvorene vypise sa Pole nie je vytvorene
	
	else
	{
		int poziciaPole = 0;

		while ((*spz)[poziciaPole] != '\0')//vypise postupne vsetky spz zapisane v poli v tvare AA BBB CC a kazda spz bude v jednom riadku
		{
			putchar((*spz)[poziciaPole++]);
			putchar((*spz)[poziciaPole++]);
			putchar(' ');

			putchar((*spz)[poziciaPole++]);
			putchar((*spz)[poziciaPole++]);
			putchar((*spz)[poziciaPole++]);
			putchar(' ');

			putchar((*spz)[poziciaPole++]);
			putchar((*spz)[poziciaPole++]);

			putchar('\n');

		}
	}
}



void maxZnak(char** spz)
{
	if (*spz == NULL)
		printf("Pole nie je vytvorene\n");

	else
	{
		int poziciaHladanyZnak = 0, poziciaPole = 0, pocetAktualny = 0, pocetMax = 0;
		char znak = 'A';

		while ((*spz)[poziciaHladanyZnak] != '\0' && znak <= 'Z')//zisti pocetnost znaku
		{
			while ((*spz)[poziciaPole] != '\0')
			{
				if ((*spz)[poziciaPole] == znak)
					pocetAktualny += 1;

				poziciaPole++;
			}

			if (pocetAktualny > pocetMax)//ak je pocet daneho znaku vacsi ako velkost doposial najpocetnejsieho znaku tak sa pocet najpocetnejsieho znaku prepise na tuto hodnotu
				pocetMax = pocetAktualny;

			poziciaHladanyZnak++;
			znak++;

			poziciaPole = 0;
			pocetAktualny = 0;
		}

		znak -= 26;
		char maxznak = 'A';
		poziciaHladanyZnak = 0;

		while ((*spz)[poziciaHladanyZnak] != '\0' && znak <= 'Z')//podla porovnavania s poctom vyskytu najpocetnejsieho znaku najde najpozetnejsi znak
		{
			while ((*spz)[poziciaPole] != '\0')
			{
				if ((*spz)[poziciaPole] == znak)
					pocetAktualny += 1;

				poziciaPole++;
			}

			if (pocetAktualny == pocetMax)//ak je pocetnost znaku rovna poctu najpocetnejsieho znaku tak sa do premennej maxznak ulozi tento znak
			{
				maxznak = 'A';
				maxznak = maxznak + poziciaHladanyZnak;
			}

			poziciaHladanyZnak++;
			znak++;

			poziciaPole = 0;
			pocetAktualny = 0;
		}

		printf("%c %d\n", maxznak, pocetMax);
	}
}



void palindrom(char** spz)
{
	if (*spz == NULL)
		printf("Pole nie je vytvorene\n");

	else
	{
		int poziciaMalePole = 7, poziciaPole = 0, pocetRovnakyZnak = 0, i = 0, j = 0;

		while ((*spz)[poziciaPole] != '\0')
		{
			char* polePalindrom = malloc(7 * sizeof(char) + 1);

			for (i = poziciaPole, j = 0; i < poziciaPole + 7; i++, j++)//do pola c sa prepise spz z pola spz
				polePalindrom[j] = (*spz)[i];


			polePalindrom[poziciaMalePole] = '\0';


			for (int l = 0, k = poziciaMalePole - 1; l < (poziciaMalePole - 1) / 2; l++,k--)//kontroluje ci je spz ulozena v poli c palindrom 
				if (polePalindrom[l] == polePalindrom[k])
					pocetRovnakyZnak += 1;


			if (pocetRovnakyZnak == 3)//ak je pocet rovnakych znakov = 3, spz je palindrom a vypisu sa prve dva znaky z spz
				printf("%c%c\n", polePalindrom[0], polePalindrom[1]);
			free(polePalindrom);


			poziciaPole += 7;//prechod na dalsiu spz
			pocetRovnakyZnak = 0;
		}
	}
}



void maxZnacka(char** spz)
{
	if ((*spz) == NULL)
		;
	else
	{
		char* poleMale = malloc(2 * sizeof(char) + 1);
		char* maxSPZ = malloc(2 * sizeof(char) + 1);

		int poziciaPole = 0, poziciaOkres = 0, pocetRovnake = 0, maxZnacka = 0;

		while ((*spz)[poziciaPole] != '\0')
		{
			for (int i = poziciaOkres, j = 0; i < poziciaOkres + 2; i++, j++)//nacita prve dva znaky z pola spz do pola c a v dalsich iteraciach nacita prve dva znaky z dalsej spz v poli
				poleMale[j] = (*spz)[i];

			poleMale[2] = '\0';

			int pozicia = 0;

			while ((*spz)[pozicia] != '\0')//zisti pocetnost spz ulozenej v poli c
			{
				
				if (poleMale[0] == (*spz)[pozicia])
					if (poleMale[1] == (*spz)[pozicia + 1])
						pocetRovnake += 1;

				pozicia += 7;
			}


			if (maxZnacka < pocetRovnake)//porovna pocet najvacsieho vyskytu s novym poctom a ak je novy pocet vacsi prepise pocet najpocetnejsieho okresu a pole obsahujuce spz tohto okresu
			{
				maxZnacka = pocetRovnake;

				for (int i = 0; i < 2; i++)
					maxSPZ[i] = poleMale[i];


				maxSPZ[2] = '\0';
			}

			poziciaPole += 7;
			poziciaOkres += 7;
			pocetRovnake = 0;
		}

		printf("%c%c %d\n", maxSPZ[0], maxSPZ[1], maxZnacka); //vypise sa iba najpocetnejsia a ta co bola v subore zapisana skor ak ich bolo viac s rovnakym poctom vyskytov

		free(poleMale);
		free(maxSPZ);
	}
}



void pocetCislic(char** spz)
{
	if ((*spz) == NULL)
		printf("Pole nie je vytvorene");

	else
	{
		for (char cislica = '0'; cislica <= '9'; cislica++)
		{
			int poziciaPole = 0, pocetnost = 0;;

			while ((*spz)[poziciaPole] != '\0')
			{
				if ((*spz)[poziciaPole] == cislica)
					pocetnost += 1;

				poziciaPole++;
			}

			if (pocetnost != 0)
				printf("%c: %d\n", cislica, pocetnost);

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
			vypisSpzPole(&spz);

		if (c == 'p')
			palindrom(&spz);

		if (c == 'b')
			pocetCislic(&spz);

		if (c == 'm')
			maxZnak(&spz);

		if (c == 'z')
			maxZnacka(&spz);

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