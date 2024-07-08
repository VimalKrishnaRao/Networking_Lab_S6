#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#define PORT 5003
#define ADD "127.0.0.1"
int main(int argc,char*argv[])
{
    int sockfd,len,num;
    time_t current_time;
    struct sockaddr_in serv_addr,cli_addr;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(PORT);
    bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    len=sizeof(cli_addr);
    while(1)
    {
        recvfrom(sockfd,&num,sizeof(num),0,(struct sockaddr*)&cli_addr,&len);
        current_time=time(NULL);
        printf("\nClient at %s:%d asked for time:%s",ADD,PORT,ctime(&current_time));
        sendto(sockfd,&current_time,sizeof(current_time),0,(struct sockaddr*)&cli_addr,len);
    }
    close(sockfd);
}