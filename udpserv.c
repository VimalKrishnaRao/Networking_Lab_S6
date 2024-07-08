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
    bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    len=sizeof(cli_addr);
    for(;;)
    {
        recvfrom(sockfd,buff,MAX,0,(struct sockaddr*)&cli_addr,&len);
        if(strncmp("exit",buff,4)==0)
        {
            printf("\nRecieved EXIT request\nEXITTING\n");
            break;
        }
        else
        {
            printf("\n[FROM CLIENT]:%s",buff);
            printf("\n[TO CLIENT]:");
            fgets(str,MAX,stdin);
            sendto(sockfd,str,MAX,0,(struct sockaddr*)&cli_addr,sizeof(cli_addr));
        }
    }
    close(sockfd);
    return 0;
}