#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int p[100];
int z=0;


void* fun(void* arg ){
	int c = (int)arg;
	int n;
	char recvbuff[1] = {-1},sendbuff[1]={-1};

    n = recv(c,recvbuff,sizeof(recvbuff),0);
    printf("%d",n);
    if(n<=0){
      printf("client quit!\n");
      close(c);
      exit(1);
    }

    printf("receive %d ok\r\n",recvbuff[0]);
    if(1==recvbuff[0]){
            p[z]=c;
            sendbuff[0]=z;
            printf("send1 ok\r\n");
            send(c,sendbuff,sizeof(sendbuff),0);

            z++;


        }
while (2!=recvbuff[0]){
    n = recv(c,recvbuff,sizeof(recvbuff),0);
    }



        printf("receive2ok\r\n");
        if(2==recvbuff[0]){
	        for(int i=0;i<z-1;i++){
            p[i]=p[i+1];
            sendbuff[0]=i;
            n=send(p[i],sendbuff,sizeof(sendbuff),0);


            printf("send2 ok\r\n");

           }
           z--;

        }


	pthread_exit(NULL);
}

int main(int argc,const char *argv[]){


int rec;
int n=0;
int servfd=-1,connfd=-1;
struct sockaddr_in servaddr;
struct sockaddr_in connaddr;
//creat socket descriptor
servfd=socket(PF_INET,SOCK_STREAM,0);
  if(-1==servfd){

  perror("socket error");
  exit(1);
  }

printf("socket ok\r\n");
//init socketaddr_in
servaddr.sin_family=PF_INET;
servaddr.sin_port=htons(9122);
servaddr.sin_addr.s_addr=inet_addr("192.168.134.130");
//bind port
rec=bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  if(rec==-1){
  perror("bind error");
  close(servfd);
  exit(1);
  }
printf("bind ok\r\n");
//listen
rec=listen(servfd,10);
if(rec==-1){

  perror("listen error");
  close(servfd);
  exit(1);
  }
printf("listen ok\r\n");
//accept
 while(1){
 int addlen=sizeof(connaddr);
 connfd=accept(servfd,(struct sockaddr_in*)&connaddr,&addlen);
  if(connfd==-1){

   perror("accept error");
   continue;//run next cycle
   }
    pthread_t id;
    pthread_create(&id,NULL,fun,(void*)connfd);//值传递，不能地址传递

  }

	/*while(1){
		puts("round again");
		int nfd=epoll_wait(epfd,events,1024,10000);
		for(i=0;i<=nfd;i++){
			memset(recvmasg,0,100);
		    n= recv(events[i].data.fd,recvmasg,100,0);
		    if(1==recvmasg[0]){
		    	ob=(observers*)malloc(sizeof (observers));
	            sb->add(sb, &ob->obs,events[i].data.fd);
		    	sendmasg[0]=ob->obs.pp;
		    	send(events[i].data.fd,sendmasg,sizeof(sendmasg),0);
                epoll_ctl(epfd,EPOLL_CTL_MOD,events[i].data.fd,&events[i]);
			}

			if(2==recvmasg[0]){
				sb->remove(sb);
			}

		}*/



//accept
 /*while(1){
 int addlen=sizeof(connaddr);
 connfd=accept(servfd,(struct sockaddr_in*)&connaddr,&addlen);
  if(connfd==-1){

   perror("accept error");
   continue;//run next cycle
   }
   int pid = fork();
     if(0==pid){
     fun((void*)connfd);

     }
     else if(pid>0){
     fun((void*)connfd);
      sleep(20)
     }*/




/*receive
rec=recv(connfd,recvmasg,sizeof(recvmasg),0);
if(rec==-1){

  perror("recv error");
  close(connfd);
  close(servfd);
  return -1;
  }
printf("recvok\r\n");
printf("get /s",recvmasg);
f=fopen("/home/du/recv.ads","w+");
if(NULL==f){
printf("fopen error");
}

rec=fputs(recvmasg,f);


fclose(f);*/

//close descriptor
close(connfd);
close(servfd);


return 0;


}
