#include <net/ethernet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void getMac(char *MAC, char *str) {
   char ifPath[256]="/sys/class/net/"; //默认网卡路径
    strcat(ifPath , str);
    strcat(ifPath ,"/address");
    //打开这个设备
    FILE *ff = fopen(ifPath,"r");
    fread(MAC,1, 17, ff);
    fclose(ff);
}
//根据网卡获取ip的通用函数
void getIp(unsigned char *ip, char *itf) {
    int fd;
    struct ifreq ifr;
    in_addr tIP ;

    fd = socket(AF_INET, SOCK_DGRAM, 0);    //using ioctl get IP address
    ifr.ifr_addr.sa_family = AF_INET;
    strcpy(ifr.ifr_name , (char*)itf);
    ioctl(fd, SIOCGIFADDR, &ifr);

    close(fd);

    tIP =((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;
    memcpy((char*)ip , &tIP ,sizeof(in_addr));
    printf("ip is %s", inet_ntoa(tIP));
}

int main(int argc, char *argv[]) {
    struct sockaddr_ll device;
    char NetInterface[10];
    strcpy(NetInterface, argv[1]);
    int index = if_nametoindex ((const char*)NetInterface);
    printf("index is %d\n", index);

    //get MAC， 要设置初始值
    char MAC[18]={0};
    char end[] = "0";
    getMac(MAC, argv[1]);
    printf("%s\n", MAC);

    unsigned char ip[4];
    getIp(ip, argv[1]);
    printf("\n");
    return 0;
}
