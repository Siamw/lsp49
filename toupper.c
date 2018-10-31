#include <stdio.h>

#define MAX 256 

main( int argc, char* argv[] )
{
      char buf[MAX];

      FILE* dst, *src;
      int c;
      
      if( argc!= 3){
           printf(" error!" );
      }
      
      src = fopen ( argv[1], "rt" );
      dst = fopen ( argv[2], "wt" );
      
      while ( ( c = fgetc( src ) ) != EOF  ) {
              if (  c >= 'a' &&  c <= 'z' )
                   c -= 32;
     
               fputc( c, dst );

       }
      
       fclose( src );
       fclose( dst );

}
