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

     mkdir( "temp", 0755 );          /* temp ��� ���丮�� ����� 
					permission�� rwxr-xr-x �� �����. */
 
     /* fileName �̶�� ������ �����ϰ� permission�� rw-r--r-- �� �����. */
     if (  ( fd = creat( fileName , 0644 ) ) < 0 )
     {
         perror( "creat");
         exit(1);
     }

     /* fileName ������ �Ӽ��� �����´�. */
     if( lstat ( fileName , &statbuf ) < 0 ) {
         perror( "lstat" );
         exit(1);
     }

     /* passwd ����ü �޸� �Ҵ� */
     uid = (struct passwd*)malloc( sizeof( struct passwd ) );
	
     /* group ����ü �޸� �Ҵ� */
     grp = (struct group* )malloc( sizeof( struct group ) );

     /* ����� UID �� ��ġ�ϴ� ������ �����´�. */
     uid = getpwuid( statbuf.st_uid );

     /* gid�� �׷쿡 ���� ������ ��ȯ�Ѵ�. */
     grp = getgrgid( statbuf.st_gid );

     printf( " %s\n", uid->pw_name );
     printf( " %s\n", grp->gr_name );
	
     strcpy ( newFile , fileName );
     strcat ( newFile , ".new");
     rename ( fileName , newFile  );      
 
     /* �ɺ��� ��ũ�� �����. */
     symlink ( newFile , "my.ln"   );   

     free( uid );
     free( grp );
     close(fd );
}

