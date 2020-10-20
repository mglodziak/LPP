/*
[Używać wyłącznie funkcji niskopoziomowych.]

Program przyjmuje dowolną liczbę argumentów, traktowanych jako ścieżki 
w systemie plików. Do każdego parametru, który prowadzi do ISTNIEJĄCEGO 
pliku regularnego, otworzyć ten plik i  dopisać na jego koniec linijkę tekstu
z bieżącą wartością zegara (odczytaną zaraz po otwarciu tego pliku).
Linijka ma kończyć się znakiem przejścia do nowej linii.

Uwaga, należy nie używać funkcji lseek (ani podobnych).
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd;
	struct timespec ts;


	for (int i=1; i<argc; i++)
	{
		fd=open(argv[i], O_WRONLY | O_APPEND);
		if (fd==-1)
		{
			printf("ERROR: file %s not exist..\n", argv[i]);
			continue;
		}
		timespec_get(&ts, TIME_UTC);
		char buff[50];
		strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
		char output[50];
		int n;
		n=sprintf(output, "Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
		printf("%d\n",n);
		write(fd, output, n);

		close(fd);
	}

return 0;
}


