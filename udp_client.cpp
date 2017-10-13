#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_SERV 8888
#define BUFF_LEN 256
void udpclient_echo(int s, struct sockaddr* serv) {
    char buff[BUFF_LEN];
    int len = sizeof(*serv);
    while(fgets(buff, BUFF_LEN, stdin)!=NULL) {
        sendto(s, buff, BUFF_LEN, 0, serv, len);       
    }
}
int main(int argc , char ** argv) {
    int s;
    struct sockaddr_in addr_serv;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&addr_serv, 0 , sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    //addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_addr.s_addr = inet_addr(argv[1]);
    addr_serv.sin_port = htons(PORT_SERV);
    udpclient_echo(s, (struct sockaddr*)&addr_serv);
    return 0;
}
