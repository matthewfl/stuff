#! /usr/local/bin/cxx
#include <stdio.h>
#include <iostream>
using namespace std;

main()
{
   FILE *fpipe;
   char *command="bash";
   char line[256];

   if( (fpipe = popen(command, "r")) == NULL)
   {  // If fpipe is NULL
      perror("Problems with pipe");
      return 1;
   }
   while(fpipe) {
   while ( fgets( line, sizeof(line), fpipe))
   {
     printf("ME: %s", line);
   }
   cin.getline(line, sizeof(line));
   fputs(line, fpipe);
   }
   pclose(fpipe);
   return 0;
}
