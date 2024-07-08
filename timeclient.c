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
    int sockfd,len;
    int num=1;
    time_t start_time,current_time,rtt;
    
    struct sockaddr_in serv_addr,cli_addr;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(PORT);
    len=sizeof(serv_addr);
    start_time=time(NULL);
    sendto(sockfd,&num,sizeof(num),0,(struct sockaddr*)&serv_addr,len);
    recvfrom(sockfd,&current_time,sizeof(current_time),0,(struct sockaddr*)&serv_addr,&len);
    rtt=time(NULL)-start_time;
    current_time += rtt/2;
    printf("\nSERVER'S TIME:%s",ctime(&current_time));
    close(sockfd);
}