#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

main()
{
     int fd;
     struct stat     statbuf;
     struct passwd* uid;
     struct group* grp;
     
     char fileName[20] = "temp/myfile.file";
     char newFile[20];

     mkdir( "temp", 0755 );          /* temp 라는 디렉토리를 만들고 
					permission을 rwxr-xr-x 로 만든다. */
 
     /* fileName 이라는 파일을 생성하고 permission을 rw-r--r-- 로 만든다. */
     if (  ( fd = creat( fileName , 0644 ) ) < 0 )
     {
         perror( "creat");
         exit(1);
     }

     /* fileName 파일의 속성을 가져온다. */
     if( lstat ( fileName , &statbuf ) < 0 ) {
         perror( "lstat" );
         exit(1);
     }

     /* passwd 구조체 메모리 할당 */
     uid = (struct passwd*)malloc( sizeof( struct passwd ) );
	
     /* group 구조체 메모리 할당 */
     grp = (struct group* )malloc( sizeof( struct group ) );

     /* 사용자 UID 와 일치하는 정보를 가져온다. */
     uid = getpwuid( statbuf.st_uid );

     /* gid로 그룹에 대한 정보를 반환한다. */
     grp = getgrgid( statbuf.st_gid );

     printf( " %s\n", uid->pw_name );
     printf( " %s\n", grp->gr_name );
	
     strcpy ( newFile , fileName );
     strcat ( newFile , ".new");
     rename ( fileName , newFile  );      
 
     /* 심볼릭 링크를 만든다. */
     symlink ( newFile , "my.ln"   );   

     free( uid );
     free( grp );
     close(fd );
}

