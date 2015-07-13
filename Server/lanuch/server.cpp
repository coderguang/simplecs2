#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "NetConstant.h"
#include "../../ComLib/linuxLib/linHead.h"
#include "../SerStruct.h"
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
/**
 *this is the server main process
 *all user process are fork from this process
 *after fork from this ,child process do it's own things
 *author:coderguagn
 *date:2015/07/06
 */


SerList client[MAX_USER];
SerNum clientNum;
SerStatus gameStatus;

int main(int argc,char **argv){
	int maxfd,listenfd,sockfd,connfd;	//the  listen  fd
	int sel[FD_SETSIZE];
	fd_set rset,allset;
	int nready;
	
	ssize_t n;
	socklen_t clilen;

	struct sockaddr_in cliaddr;	//client addr
	struct sockaddr_in servaddr;	//server addr
	
	
	listenfd=Socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=INADDR_ANY;

	
	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	Listen(listenfd,BACKLOG);
	
	maxfd=listenfd;
	
	for(int i=0;i<MAX_USER;i++){
		client[i].connfd=-1;
		client[i].id=-1;
		client[i].party=-1;	
	}
	for(int i=0;i<FD_SETSIZE;i++){
		sel[i]=-1;
	}

	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);

	for(;;){
		rset=allset;
		nready=Select(maxfd+1,&rset,NULL,NULL,NULL);

		if(FD_ISSET(listenfd,&rset)){//new connection
			clilen=sizeof(cliaddr);
			connfd=Accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
			
			int i;
			for(i=0;i<MAX_USER;i++){
				if(client[i].connfd<0){
					client[i].connfd=connfd;
					cout<<"connfd="<<connfd<<"  is connecting"<<endl;
					break;
				}
			}
			
			if(i==MAX_USER){
				cout<<"sockfd is full"<<endl;
			}

			FD_SET(connfd,&allset);//add new conn to set
		
			if(nready<=0){
				continue;
			}

		}	

		
		//get data
		for(int i=0;i<MAX_USER;i++){
			if((sockfd=client[i].connfd)<0){
				continue;
			}
			
			if(FD_ISSET(sockfd,&rset)){
				int id=0;
				int nread;
				if((nread=Read(sockfd,&id,4))==0){
					Close(sockfd);
					FD_CLR(sockfd,&allset);
					cout<<"socket = "<<client[i].connfd<<" is disconnect.."<<endl;
					client[i].connfd=-1;
				}else{
					cout<<"get the msg ,id="<<id<<endl;
				}
			}
			if(nready<=0){
				break;
			}
		}
	



	}
	


	
		

}

