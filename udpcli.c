#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#define PORT 5000
#define MAX 60
int main(int argc,char*argv[])
{
    int len;
    char buff[MAX],str[MAX];
    struct sockaddr_in serv_addr,cli_addr;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    len=sizeof(serv_addr);
    for(;;)
    {
        printf("\n[TO SERVER]:");
        fgets(buff,MAX,stdin);
        sendto(sockfd,buff,MAX,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        if(strncmp("exit",buff,4)==0)
        {
            printf("\nRecieved EXIT request\nEXITTING\n");
            break;
        }
        else
        {
            recvfrom(sockfd,str,MAX,0,(struct sockaddr*)&serv_addr,&len);
            printf("\n[FROM SERVER]:%s",str);
        }
    }
    close(sockfd);
}