/*
Program korzysta z dwóch funkcji pomocniczych. Każda przyjmuje, jako parametr,
wskaźnik na strukturę FILE, odpowiadającą za otwarty plik, do którego można
zapisywać.

Pierwsza z funkcji wpisuje do dostarczonego pliku pięć (5) kolejnych krotności
liczby 0,625 (z dokładnością do 3 cyfr po przecinku).
Druga, wyznacza sekwencję 19 liczb typu short int, dodając do poprzedniej
wartość 80. Nieujemne wartości z ciągu są (kolejno) wpisywane do zadanego
pliku.

Obie funkcje zaczynają obliczenia od 0, a każde kolejne wywołanie powoduje
kontynuowanie od wartości, na której skończyło się poprzednie.
(Uwaga, funkcje nie mogą korzystać ze zmiennych globalnych).


Program przyjmuje parametry:
 -d <int>   - wartością parametru może być 1 albo 2,
 -k <int>   - wartością parametru jest liczba nieujemna,
oraz argument pozycyjny, interpretowany jako ścieżka do pliku.

Program wykonuje następujące czynności:
1. W zależności od wartości parametru -d, otwiera zadany plik (w trybie do
   zapisu) jeden lub dwa razy. Jeżeli takiego pliku wcześniej nie było, to go
   tworzy, a jeżeli był, to skraca jego długość do 0 bajtów.
2. Wywołuje naprzemiennie wymienione wyżej funkcje, tyle razy, ile wynosi
   wartość parametru -k.
   Jeżeli plik był otwarty dwa razy, to do każdej z funkcji przekazuje inny
   wskaźnik.

Po uruchomieniu programu sprawdzić, jak zmieniają się wyniki, w zależności od
kombinacji parametrów.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


double pierwsza(int fd, double in)
{
	double res;
	res=in;
	for (int i=1;i<=5;i++)
	{
		res=res+0.625*i;
		char buff[30];
		int n=sprintf(buff, "%.3f\n", res);
		write(fd, buff, n);
	}
	return res;
}

double druga(int fd, double in)
{
	short int res, res2;
	res = in;
	for (int i=1; i<=19; i++)
	{
		res+=80;
		if (res>=0)
		{
			char buff[30];
			int n=sprintf(buff, "%d\n", res);
			write(fd, buff, n);
			res2=res;
		}
	}
	return res2;
}


int main (int argc, char* argv[])
{
	int opt;
	int d;
	int k;
	while ((opt=getopt(argc, argv, "d:k:")) != -1)
	{
		switch(opt)
		{
			case 'd':
				d=strtol(optarg,NULL,10);
				printf("%d\n",d);
				if (d!=1 && d!=2)
				{
					printf("Parametr d musi być 1 albo 2! Exit.\n");
					exit(-1);
				}
				break;
			case 'k':
				k=strtol(optarg,NULL,10);
				printf("%d\n",k);
				if (k<0)
				{
					printf("Parametr k nie może być ujemny! Exit.\n");
					exit(-2);
				}
				break;
			default:
				printf("Tylko argumenty k i d. Exit.\n");
				exit (-3);
		}
	}
	if (argc-optind!=1)
	{	
		printf("Można podać tylko jeden parametr pozycyjny! Exit.");
		exit( -4);
	}
	char file_name[40];
	sprintf(file_name,"%s\n",argv[optind]);
	printf("%s",file_name);



	if (d==1)
	{
		//funkcja, która nadupca jednokrotne otwarcie pliku
		int fd;
		fd=open(argv[optind], O_CREAT|O_WRONLY|O_TRUNC|O_APPEND,0666);
		
		double res_pierwsza =0;
		double res_druga=0;

		for (int i=1; i<=k; i++)
		{
			res_pierwsza=pierwsza(fd,res_pierwsza);
			res_druga=druga(fd,res_druga);
		}
		close(fd);
	}

	else if (d==2)
	{
		//tudu	int fd;
		int fd1;
		int fd2;
		fd1=open(argv[optind], O_CREAT|O_WRONLY|O_TRUNC|O_APPEND,0666);
		fd2=open(argv[optind], O_CREAT|O_WRONLY|O_TRUNC|O_APPEND,0666);
		
		double res_pierwsza=0;
		double res_druga=0;

		for (int i=1; i<=k; i++)
		{
			res_pierwsza=pierwsza(fd1,res_pierwsza);
			res_druga=druga(fd2,res_druga);
		}
		close(fd1);
		close(fd2);
	}

return 0;
}
