// przeanalizować treść programu i wyjaśnić, jaki mechanizm spowodował
// pojawienie się podwójnego napisu "przed forkiem"
//
// dodatkowo, zapoznać się z console_codes(4)


#include <unistd.h>
#include <stdio.h>
#include <err.h>

char * FMT[] = {"\e[0m", "\e[1;32m", "\e[46;30m", "\e[43;31;2m"}; 

int main( int argc, char ** argv ) {
  printf("%sprzed forkiem%s\n",FMT[1],FMT[0]);
  switch( fork() ) {
    case -1 : err(1,NULL);
    case  0 : printf("po forku -- %spotomek%s\n",FMT[2],FMT[0]);
	      break;
    default : printf("po forku -- %srodzic%s\n",FMT[3],FMT[0]);
	      break;
  }
  //puts(FMT[0]);
  //putc('\n',stdout);
  return 0;
}

// vim: sts=2 sw=2 :
