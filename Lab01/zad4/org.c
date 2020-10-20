// przeanalizować treść programu i wyjaśnić, jaki mechanizm spowodował
// pojawienie się podwójnego napisu "przed forkiem"
//
// dodatkowo, zapoznać się z console_codes(4)


#include <unistd.h>
#include <stdio.h>
#include <err.h>

char * FMT[] = {"\e[0m", "\e[1;32m", "\e[46;30m", "\e[43;31;2m"}; 

int main( int argc, char ** argv ) {
  printf("%sprzed forkiem%s",FMT[1],FMT[0]);
  switch( fork() ) {
    case -1 : err(1,NULL);
    case  0 : printf("\npo forku -- %spotomek",FMT[2]);
	      break;
    default : printf("\npo forku -- %srodzic",FMT[3]);
	      break;
  }
  puts(FMT[0]);
  putc('\n',stdout);
  return 0;
}

// podwójny napis przed forkiem wynika z faktu, że printf nie ma znaku nowej linii. W efekcie napis trafia do bufora, po czym następuje fork. Potomne procesy dostają ten napis. Następnie w zależności od pidu wchodzi do switcha i wypisuje na ekran ponieważ trafia się znak nowej linii. 
//
// ogólnie printf działa tak, że wypisze na ekran dopiero gdy trafi na \n, albo siłowo wymusimy flushem, albo nastąpi koniec programu i wtedy też wypisze.
