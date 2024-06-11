#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char *addr1 = "1.2.3.4";
	char *addr2 = "1.2.3.256";

	unsigned long conv_addr = inet_addr(addr1);
  // 32bit 정수로 표현& 네트워크 바이트 순서로 정렬(빅 엔디안) =>  0x4030201
	if(conv_addr == INADDR_NONE)
		printf("Error occured");
  else
  	printf("Network ordered integer addr: %#lx \n", conv_addr);

  conv_addr=inet_addr(addr2);
  if(conv_addr == INADDR_NONE)
     printf("Error occured");
  else
     printf("Network ordered integer addr: %#lx \n", conv_addr);
  return 0;
}
