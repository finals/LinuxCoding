#include <unistd.h>
#include <fcntl.h>
 
int main()
{
        int fd;
        char buf[4096];
    
        sleep(10); //run ./funtion.sh to trace vfs_read of this process
        fd = open("/home/file", O_RDONLY);
        read(fd, buf, 4096);
        read(fd, buf, 4096);
  
        return 0;
}
