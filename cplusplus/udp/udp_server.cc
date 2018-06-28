#include <iostream>
#include <string.h>

#include "udp.h"

int main(void)
{
   auto ctx = udp::UDPServer("127.0.0.1", 12345);
   char buf[1024];
   
   while (true) {
       bzero(buf, sizeof(buf));
       int nbytes = ctx.Recvfrom(buf, sizeof(buf), 0);
       std::cout << "recv " << nbytes << " bytes: " << buf << std::endl;

       if (nbytes <= 0) {
           break;
       }

       strcpy(buf, "message from server");

       nbytes = ctx.Sendto(buf, strlen(buf)+1, 0);
       std::cout << "send " << nbytes << " bytes: " << buf <<std::endl;
       if (nbytes <= 0) {
           break;
       }
    }
   

   return 0;
}
