/*
 Program PL Conv
 Written             /\
 in 1993           /    \/\    Jaroslaw Strzalkowski
 by:             /     /    \  Krakow, Poland
               /     /        \

 Zrodlo przenosne - kompiluje sie bez problemow pod wszelkimi systemami.
 Kompilacja pod Unixem komenda: cc -o plconv plconv.c
 Instrukcja uzycia: plconv h

 Styczen 1996 - Wojtek.Bogusz@fuw.edu.pl - drobne poprawki :-)
 konwersja ze standardow dwu znakowych, 
 mozliwosc konwersji z dowlonego wymienionego nizej standardu na dowolny
 ... 
 Lipiec 2004 - Marcin Wrochniak (vrok@intersec.pl) - obsluga UTF-8
*/

#include <stdio.h>
#include <string.h>

/* -- tabele kodow jednoznakowych
   -- UWAGA: Mazovia musi byc, i musi byc pierwsza. */
struct pl_onec_struct {
	char *name;
	unsigned char code[18];
} pl_onec[] = {
{ "Mazovia",     { 143, 149, 144, 156, 165, 163, 152, 160, 161, 134, 141, 145, 146, 164, 162, 158, 166, 167 } },
{ "ISO-Latin-2", { 161, 198, 202, 163, 209, 211, 166, 172, 175, 177, 230, 234, 179, 241, 243, 182, 188, 191 } },
{ "CSK",         { 128, 129, 130, 131, 132, 133, 134, 136, 135, 160, 161, 162, 163, 164, 165, 166, 168, 167 } },
{ "Cyfromat",    { 128, 129, 130, 131, 132, 133, 134, 136, 135, 137, 138, 139, 140, 141, 142, 143, 145, 144 } },
{ "DHN",         { 128, 129, 130, 131, 132, 133, 134, 136, 135, 137, 138, 139, 140, 141, 142, 143, 145, 144 } },
{ "IINTE-ISIS",  { 128, 129, 130, 131, 132, 133, 134, 135, 136, 144, 145, 146, 147, 148, 149, 150, 151, 152 } },
{ "IBM-Latin-2", { 164, 143, 168, 157, 227, 224, 151, 141, 189, 165, 134, 169, 136, 228, 162, 152, 171, 190 } },
{ "IEA-Swierk",  { 143, 128, 144, 156, 165, 153, 235, 157, 146, 160, 155, 130, 159, 164, 162, 135, 168, 145 } },
{ "Logic",       { 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145 } },
{ "Microvex",    { 143, 128, 144, 156, 165, 147, 152, 157, 146, 160, 155, 130, 159, 164, 162, 135, 168, 145 } },
{ "Windows-EE",  { 161, 198, 202, 163, 209, 211, 140, 143, 175, 185, 230, 234, 179, 241, 243, 156, 159, 191 } },
{ "Ventura",     { 151, 153, 165, 166, 146, 143, 142, 144, 128, 150, 148, 164, 167, 145, 162, 132, 130, 135 } },
{ "ELWRO-Junior",{ 193, 195, 197, 204, 206, 207, 211, 218, 217, 225, 227, 229, 236, 238, 239, 243, 250, 249 } },
{ "AmigaPL",     { 194, 202, 203, 206, 207, 211, 212, 218, 219, 226, 234, 235, 238, 239, 243, 244, 250, 251 } },
{ "brak",        {  65,  67,  69,  76,  78,  79,  83,  90,  90,  97,  99, 101, 108, 110, 111, 115, 122, 122 } }
};

/* -- tabele kodow wieloznakowych */
struct pl_multic_struct {
char *name;
char fcode;
char *code[18];
} pl_multic[] = {
{ "TeX.W-wa.1", '@',  { "A",     "C",     "E",     "L",     "N",     "O",     "S",     "Z",     "R",
                        "a",     "c",     "e",     "l",     "n",     "o",     "s",     "z",     "x"     } },
{ "TeX.W-wa.2", '\"', { "A",     "C",     "E",     "L",     "N",     "O",     "S",     "Z",     "R",
                        "a",     "c",     "e",     "l",     "n",     "o",     "s",     "z",     "x"    } },
{ "TeX-ohida",   0,  { "\\c{A}","\\'C",  "\\c{E}","\\L{}", "\\'N",  "\\'O",  "\\'S",  "\\'Z",  "\\.Z",
                        "\\c{a}","\\'c",  "\\c{e}","\\l{}", "\\'n",  "\\'o",  "\\'s",  "\\'z",  "\\.z"   } },
{ "UTF-8",   0,  { "Ą", "Ć",  "Ę", "Ł", "Ń",  "Ó",  "Ś",  "Ż",  "Ź",
                        "ą", "ć",  "ę", "ł", "ń",  "ó",  "ś",  "ż",  "ź"   } },	
{ "tyldy",      '~',  { "A",     "C",     "E",     "L",     "N",     "O",     "S",     "Z",     "X",
                        "a",     "c",     "e",     "l",     "n",     "o",     "s",     "z",     "x"     } }
};

int main( argc, argv )
int argc;
char *argv[];
{
	int i, j;                      /* -- licznikowe                          */
	int n_onec   = sizeof( pl_onec )   / sizeof( struct pl_onec_struct );
	int n_multic = sizeof( pl_multic ) / sizeof( struct pl_multic_struct );
                  /* -- rozmiary tabel kodow standardow    */
	int kind;     /* -- rodzaj konwersji: 
					 00 - niemozliwa
					 11 - jednoznakowy:jednozn.
					 12 - jedno:wielo
					 21 - wielo:jedno
					 22 - wielo:wielo                                  */
	int std1;  /* -- numer standardu wejsciowego w obrebie tabeli    */
	int std2; /* -- numer standardu wyjsciowego w obrebie tabeli    */
	char *str;   /* -- pomocniczy ptr do stringu                       */
	int c;       /* -- do czytania kolejnych znakow                    */

	/* -- -------------------------------------------------------------
	   -- lista nazw standardow
	   -- */
	if( argc == 2 && !strcmp( argv[1], "L" ) ) {
		puts( "\n     A   C   E   L   N   O   S   Z'  Z.  a   c   e   l   n   o   s   z'  z." );
		puts( "---------------------------------------------------------------------------\n" );

		puts( "Standardy jednoznakowe:" );
		puts( "-----------------------" );
		for( i = 0; i < n_onec; i++ ) {
			printf( "%s:\n    ", pl_onec[i].name );
			for( j = 0; j < 18; j++ )
				printf( " %03d", pl_onec[i].code[j] );
			printf( "\n" );
		}

		puts( "\nStandardy kilkuznakowe:" );
		puts(   "-----------------------" );
		for( i = 0; i < n_multic; i++ ) {
			printf( "%s:\n    ", pl_multic[i].name );
			for( j = 0; j < 18; j++ ) {
				if( j == 9 )
					printf("\n    ");
				if( pl_multic[i].fcode == 0 )
					printf( " (%-5s)", pl_multic[i].code[j] );
				else
					printf( " (%c%-4s)", pl_multic[i].fcode, pl_multic[i].code[j] );
			}
			printf( "\n" );
		}
		exit(0);
	}/* lista nazw */

	if( argc == 2 && !strcmp( argv[1], "l" ) ) {
		puts("Nazwy standardow jednoznakowych:");
		puts("--------------------------------");
		c = 0;
		for( i = 0; i < n_onec; i++ ) {
			if( c+strlen(pl_onec[i].name) > 80 ) {
				printf("\n%s   ", pl_onec[i].name);
				c  = strlen(pl_onec[i].name)+3;
			} else {
				printf("%s   ", pl_onec[i].name);
				c += strlen(pl_onec[i].name)+3;
			}
		}
		puts("\nNazwy standardow kilkuznakowych:");
		puts(  "--------------------------------");
		c = 0;
		for( i = 0; i < n_multic; i++ ) {
			if( c+strlen(pl_multic[i].name) > 80 ) {
				printf("\n%s   ", pl_multic[i].name);
				c  = strlen(pl_multic[i].name)+3;
			} else {
				printf("%s   ", pl_multic[i].name);
				c += strlen(pl_multic[i].name)+3;
			}
		}
		printf("\n");
		exit(0);
	}

	/* -- --------------------------------------------------------
	   -- konwersja
	   -- */
	if( argc >= 2 ) {
		kind = 0;
		/* Standard wyjsciowy */
		if((str = strchr(argv[1], ':')) == NULL) {
			std2 = 0;
			kind = 1;
		} else {
			*str = 0;
			str++;
			for( i = 0; i < n_onec; i++ )
				if( !strcmp( str, pl_onec[i].name ) )
					break;
			if( i < n_onec ) {
				kind = 1;
				std2 = i;
			} else {
				for( i = 0; i < n_multic; i++ )
					if( !strcmp( str, pl_multic[i].name ) )
						break;
				if( i < n_multic ) {
					kind = 2;
					std2 = i;
				} else {
					fprintf( stderr, "plconv: Nieznany standard wyjsciowy: %s\nUruchom:\nplconv l\nw celu wypisania listy nazw.\n", str );
					exit(2);
				}
			}
		}
		/* Standard wejsciowy */
		for( i = 0; i < n_onec; i++ )
			if( !strcmp( argv[1], pl_onec[i].name ) )
				break;
		if( i < n_onec ) {
			kind += 10;
			std1 = i;
		} else {
			for( i = 0; i < n_multic; i++ )
				if( !strcmp( argv[1], pl_multic[i].name ) )
					break;
			if( i < n_multic ) {
				kind += 20;
				std1 = i;
			} else {
				fprintf( stderr, "plconv: Nieznany standard wejsciowy: %s\nUruchom:\nplconv l\nw celu wypisania listy nazw.\n", argv[1] );
				exit(2);
			}
		}

		if( kind == 0 || ( kind >= 20 && pl_multic[i].fcode == 0 ) ) {
			fprintf( stderr, 
					"plconv: Niestety, takiej konwersji nie wykonam\n" );
			exit(1);
		}

		fprintf(stderr, "%s -> %s\n", 
				(kind == 11 || kind == 12 ) ? pl_onec[std1].name : pl_multic[std1].name,
				(kind == 11 || kind == 21 ) ? pl_onec[std2].name : pl_multic[std2].name );

		/* -- input --> output z konwersja */
		while( (c = getchar()) != EOF ) {

			if( kind == 11 || kind == 12 ) {
				/* -- konwersja ze standardow jednoznakowych */
				/* -- sprawdz czy dany znak jest polska litera */
				for( j = 0; j < 18; j++ )
					if( c == pl_onec[ std1 ].code[j] )
						break;
				if( j < 18 ) {
					/* -- jest polska litera */
					if( kind == 11 ) {
						putchar( pl_onec[ std2 ].code[j] );
					} else {
						if( pl_multic[ std2 ].fcode == 0 ) {
							printf( "%s", pl_multic[ std2 ].code[j] );
						} else {
							printf( "%c%s", pl_multic[ std2 ].fcode, 
								   pl_multic[ std2 ].code[j] );
						}
					}
				} else {
					putchar( c );
				}
			} else {
				/* -- konwersja ze standardow dwuznakowych */
				if( c == pl_multic[ std1 ].fcode ) {
					if( (c = getchar()) == EOF ) {
						putchar( pl_multic[ std1 ].fcode );
						break;
					}
					for( j = 0; j < 18; j++ )
						if( c == pl_multic[ std1 ].code[j][0] )
							break;
					if( j < 18 ) {
						/* -- jest polska litera */
						if( kind == 21 ) {
							putchar( pl_onec[ std2 ].code[j] );
						} else {
							if( pl_multic[ std2 ].fcode == 0 ) {
								printf( "%s", pl_multic[ std2 ].code[j] );
							} else {
								printf( "%c%s", pl_multic[ std2 ].fcode, 
									   pl_multic[ std2 ].code[j] );
							}
						}
					} else {
						putchar( pl_multic[ std1 ].fcode );
						putchar( c );
					}
				} else {
					putchar( c );
				}
			}
		}/* inp->outp */
		exit(0);
	}/* konwersja */


	/* -- --------------------------------------------------------
	   -- bledne parametry
	   -- */
	fprintf( stderr, "\
PL Conv - konwersja polskich liter pomiedzy wszelakimi \"standardami\".\n\
(c) Jaroslaw Strzalkowski <js@uci.agh.edu.pl>, Krakow, Marzec  1993\n\
    Wojtek.Bogusz@fuw.edu.pl,                          Styczen 1996\n\
Public domain - kopiowanie na prawo i lewo mile widziane.\n\
\n\
Uzycie:\n\
plconv std1[:std2] [nazwa_pliku] - konwersja ze std1 na \n\
              Mazovie [lub na std2] [z pliku nazwa_pliku]\n\
              Rezultat konwersji wypisywany jest na stdout\n\
plconv l    - lista nazw \"standardow\"\n\
plconv L    - lista nazw i kodow \"standardow\"\n\
");
  exit(2);
  return 0; /* dummy */
}
