#include "../../ComLib/linuxLib/linComNet.h"
#include "../../ComLib/linuxLib/Func.h"
#include "../SerStruct.h"
#include "../ProtoHandle.h"
#include "config.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;

SerList client[MAX_USER];
SerNum clientNum;
SerStatus gameStatus;


int main(int argc,char **argv){

	InitFunMap();

	int i,maxfd,sockfd,listenfd,connfd;
	int nready;
	ssize_t n;
	fd_set rset,allset;
	socklen_t clilen;
	
	struct sockaddr_in cliaddr;
	struct sockaddr_in servaddr;
	
	listenfd=Socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=INADDR_ANY;

	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	Listen(listenfd,10);
	
	maxfd=listenfd; //initialize

	
	for(i=0;i<MAX_USER;i++){
		client[i].connfd=-1;
		client[i].id=-1;
		client[i].party=-1;
	}
	
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);

	for(;;){
		rset=allset;
		nready=Select(maxfd+1,&rset,NULL,NULL,NULL);
	
		if(FD_ISSET(listenfd,&rset)){//new client connecton
			clilen=sizeof(cliaddr);
			connfd=Accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

			for(i=0;i<MAX_USER;i++){
				if(client[i].connfd<0){
					cout<<"socket="<<connfd<<" connected!"<<endl;
					client[i].connfd=connfd;//save the new sockfd
					break;
				}
			}
			if(i==MAX_USER){
				cout<<"sockfd set full!"<<endl;
			}
			FD_SET(connfd,&allset);//add new to set
			if(connfd>maxfd){
				maxfd=connfd;//for select
			}
			if(nready<=0){
				continue; //no more readable
			}

	
		}
		
		for(i=0;i<MAX_USER;i++){//check all clients for data
			if((sockfd=client[i].connfd)<0){
				continue;
			}
			if(FD_ISSET(sockfd,&rset)){
				int id;
				if((n=Read(sockfd,&id,4))==0){
					cout<<"socket="<<sockfd<<" is disconnect..."<<endl;
					close(sockfd);//connection closed by client
					FD_CLR(sockfd,&allset);
					client[i].connfd=-1;
				}else{
					//cout<<"get the msg:"<<buf<<endl;
					cout<<"get the id="<<id<<endl;
					ProtoHandle(id,sockfd);

				}
				if(nready<=0){
					break;
				}
			
			}
		}
	}
}
