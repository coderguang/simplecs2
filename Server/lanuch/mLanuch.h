#ifndef MLANUCH_H_
#define MLANUCH_H_

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
#include "../myDB/dbcpp/DBInterface.h"
#include "../myDB/dbcpp/DBErr.h"
#include "../struct/ShmServer.h"
#include "../include/BroadcastInterface.h"
#include "../publicRoom/UpdateParty.h"
#include "../struct/PersonData.h"
#include "../../../ComLib/linuxLib/linComNet.h"

using namespace std;
extern shmList client[MAX_USER];
extern shmNum clientNum;
extern shmStatus status;

void mLanuchGame(int connfd,string ip,int id){

			if(pLanuchID==id){
						Lanuch_tos *ptr=new Lanuch_tos();
						memset(ptr,'\0',sizeof(Lanuch_tos));
						Readn(connfd,&ptr->error_code,sizeof(Lanuch_tos)-4);
						
						ptr->account[ptr->acclen]='\0';
						ptr->passwd[ptr->paslen]='\0';

						cout<<"try lanuch:accounts="<<ptr->account<<"  passwd="<<ptr->passwd<<endl;
						string account=ptr->account;
						string passwd=ptr->passwd;
						struct Lanuch lanResult;
						int rNum=LanuchAccount(account,passwd,ip,lanResult);

						cout<<"rNum="<<rNum<<endl;
						
						//lanuch success
						if(0==rNum){
							//save this to the shmList				

							int partyTemp=0;//use to remember this account's party

							for(int i=0;i<MAX_USER;i++){
								//cout<<"in lanuch:flag["<<i<<"]="<<client->flag[i]<<"  pid="<<client->pid[i]<<" id="<<client->id[i]<<endl;
								if(-1==client[i].conn){
										if(clientNum.blueCounter<=clientNum.redCounter&&clientNum.blueCounter<(MAX_USER/2)){
												client[i].party=BLUE;
												clientNum.counter++;
												clientNum.blueCounter++;
												partyTemp=BLUE;
										}else if(clientNum.blueCounter>clientNum.redCounter&&clientNum.redCounter<(MAX_USER/2)){
												client[i].party=RED;
												clientNum.counter++;
												clientNum.redCounter++;
												partyTemp=RED;
										}else{ //if the server is full
												Err_toc *err=new Err_toc(SERVER_FULL);
												Writen(connfd,&err->id,sizeof(Err_toc));
												close(connfd);
												exit(1);

										}


										//if decide the party success,take it to list
										client[i].id=lanResult.id;
									//	client[i].conn=connfd;

										//cout<<"id="<<client->id[i]<<" in the client,the party is "<<client->party[i]<<endl;

										break;
								}
							}					

							LanuchResult_toc *result=new LanuchResult_toc(lanResult.name,lanResult.lastlanuch,lanResult.lastIP,lanResult.setting,lanResult.id);
							//cout<<"name="<<result->name<<"  lastlanuch="<<result->lastLanuch<<"  lastip="<<result->lastIP<<"  setting="<<result->setting<<endl<<endl;
							
							result->party=partyTemp;
							result->error_code=0;
							Writen(connfd,&result->id,sizeof(LanuchResult_toc));


							//set the static PersonData
							PersonData::m_ID=result->account_id;
							PersonData::m_Party=result->party;
							PersonData::m_Name=lanResult.name;
							PersonData::m_LastTime=lanResult.lastlanuch;
							PersonData::m_LastIP=lanResult.lastIP;
							
							//set success!
							//cout<<"Person id="<<PersonData::m_ID<<" party="<<PersonData::m_Party<<" name="<<PersonData::m_Name<<"lastlanuch="<<PersonData::m_LastTime<<" ip="<<PersonData::m_LastIP<<endl;

							

							//if it lanuch right,break this loop and come to the public room loop
							//send the Party_toc
							
							//Party_toc *ptemp=new Party_toc(1000,1001,1002,1003,1004,1005,1006,1007,1008,1009);	
							//Writen(connfd,&ptemp->id,sizeof(Party_toc));
							//boardcast the updateparty to all
						
							updateParty();							

						}else{
							Err_toc *err=new Err_toc(rNum);
							Writen(connfd,&err->id,sizeof(Err_toc));
						}
					}else{//if receive the other proto or error stream,read it and throw is to memset the socket stream
						 char errbuf[64];
						 Readn(connfd,&errbuf,64);

					}
				

			}
}

#endif
