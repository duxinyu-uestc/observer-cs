#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


int main(int argc,const char *argv[]){
  int  rec;
  int k=1;
  int clifd;
  char sendmasg[1];
  char recvmasg[1];
  sendmasg[0]=6;
  struct sockaddr_in cliaddr;
  struct sockaddr_in servaddr;
  //creat client desciptor
  clifd=socket(PF_INET,SOCK_STREAM,0) ;
  if(-1==clifd){

  perror("clifd error");
  return -1;
  }
printf("socket ok\r\n");
//connect
cliaddr.sin_family=PF_INET;
cliaddr.sin_port=htons(9122);
cliaddr.sin_addr.s_addr=inet_addr("192.168.134.130");

 rec=connect(clifd,(struct sockaddr*) &cliaddr,sizeof(cliaddr));

if(rec==-1){
  perror("connect error");
  close(clifd);
  return -1;
  }
printf("connect ok\r\n");

while(sendmasg[0]!=1){
scanf("%d",&sendmasg[0]);
}
rec=send(clifd,sendmasg,sizeof(sendmasg),0);

if(rec==-1){
  perror("send error");
  close(clifd);
  return -1;
  }
printf("send %d ok\r\n",sendmasg[0]);
 recv(clifd,recvmasg,sizeof(recvmasg),0);
 printf("recv1 ok\r\n");
 printf("location%d\r\n",recvmasg[0]);


while(recvmasg[0]!=0){

rec=recv(clifd,recvmasg,sizeof(recvmasg),0);
if(rec>0){
printf("recv2 ok\r\n");
printf("location%d\r\n",recvmasg[0]);
rec=0;
}
}
scanf("%d",&sendmasg[0]);
rec=send(clifd,sendmasg,sizeof(sendmasg),0);
if(rec==-1){
  perror("send error");
  close(clifd);
  return -1;
  }
printf("send2 ok\r\n");


close(clifd);
return 0;
}
