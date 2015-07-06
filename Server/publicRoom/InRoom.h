#ifndef IN_ROOM__H_
#define IN_ROOM_H_

#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> //for read write
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include "../proto/Proto.h"
#include "../publicRoom/UpdateParty.h"
#include "../proto/ProtoID.h"
#include "../struct/PersonData.h"
#include "../struct/ShmServer.h"
#include "../game/Gameing.h"
using namespace std;


void InRoomLoop(int connfd){
	
	cout<<"lanuch success,come to publicRoom"<<endl;
	
			if(pChatID==id){
					//cout<<"receive the chat in the room"<<endl;

					Chat_tocs *temp=new Chat_tocs();
					memset(temp,'\0',sizeof(Chat_tocs));

					readn(connfd,&temp->error_code,sizeof(Chat_tocs)-4);
						
					temp->id=pChatID;
					temp->msg[temp->msglen]='\0';
					
					cout<<"receive chat:uid="<<temp->user_id<<"  msg="<<temp->msg<<" err_code="<<temp->error_code<<endl;
					
					//Chat_tocs *chat=new Chat_tocs();
					//strcpy(chat->msg,temp->msg);

					//cout<<"chat id="<<chat->user_id<<"  msg="<<chat->msg<<" err_code="<<temp->error_code<<endl;

					//writen(connfd,&temp->id,sizeof(Chat_tocs));
					//broadcast this msg to the all

					//mBroadcast(ALL,chat,sizeof(Chat_tocs));

					mBroadcast(ALL,temp,sizeof(Chat_tocs));
					
			}else if(partyChangeID==id){//get the party change tos
					
					Party_change_tocs *temp=new Party_change_tocs();
					readn(connfd,&temp->error_code,sizeof(Party_change_tocs)-4);
					
					cout<<"get the party change proto"<<endl;

					cout<<"come to shm"<<endl;
					
					if(BLUE==PersonData::m_Party){

							//cout<<"now he is blue"<<endl;

							if(numptr->redCounter>=(MAX_USER/2)){//if another party if full
								
									//cout<<"can't join red,full!"<<endl;

									Err_toc *temp=new Err_toc(PARTY_IS_FULL);
									writen(connfd,&temp->id,sizeof(Err_toc));
	
							}else{//change the party

									numptr->blueCounter--;
									numptr->redCounter++;

									for(int i=0;i<MAX_USER;i++){
										if(1==listptr->flag[i]&&PersonData::m_ID==listptr->id[i]){
													listptr->party[i]=RED;	
													//should change the PersonData
													PersonData::m_Party=RED;
													cout<<"change to red"<<endl;
										}					

									}

									updateParty();//this need the listmutex,so must post before this

									//talk to the client ,he's party is change
									Party_change_tocs *t=new Party_change_tocs();
									writen(connfd,&t->id,sizeof(Party_change_tocs));

							}
					}else if(RED==PersonData::m_Party){
							if(numptr->blueCounter>=(MAX_USER/2)){//if another party if full
									Err_toc *temp=new Err_toc(PARTY_IS_FULL);
									writen(connfd,&temp->id,sizeof(Err_toc));
							}else{//change the party
									numptr->blueCounter++;
									numptr->redCounter--;

									for(int i=0;i<MAX_USER;i++){
										if(1==listptr->flag[i]&&PersonData::m_ID==listptr->id[i]){
													listptr->party[i]=BLUE;	
													PersonData::m_Party=BLUE;
													cout<<"change to Blue"<<endl;
				
										}					

									}
									updateParty();

									//talk to the client ,he's party is change
									Party_change_tocs *t=new Party_change_tocs();
									writen(connfd,&t->id,sizeof(Party_change_tocs));

							}
				}else{//if get something wrong and didn't cast any befor,post the mutex

							cout<<"didn't match any party!"<<endl;
				}

			}else if(gameStartID==id){//receive the start game proto


				GameStart_tocs *temp=new GameStart_tocs();

				readn(connfd,&temp->error_code,sizeof(GameStart_tocs)-4);
					
					for(int i=0;i<5;i++){
						string str="game start after seconds ";
						str+=IntToStr(i);
						Chat_tocs *t=new Chat_tocs(1000,ALL,str);
						mBroadcast(ALL,t,sizeof(Chat_tocs));
						DelayTime(2);
					 }

					//DelayTime(2);

					mBroadcast(ALL,temp,sizeof(GameStart_tocs));

			}else{//some error sream ,receive it and do nothing
					char buf[128];
					readn(connfd,&buf,128);
			}
				


}

#endif
