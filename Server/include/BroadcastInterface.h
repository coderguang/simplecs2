#ifndef BROARDCAST_INTERFACE_H_
#define BROARDCAST_INTERFACE_H_

//this is using for broardcast
//it have 3 arguments
//type: it decide this proto broardcast to who,blue or red or all
//proto: this it the proto
//len: the size of the proto

#include "../struct/ShmServer.h"
#include "../proto/Message.h"
#include "../../../ComLib/linuxLib/linHead.h"

using namespace std;

//use InitFirst functions to instead it's own init functions

static const int BLUE=1;
static const int RED=2;
static const int ALL=3; 

extern struct shmList client[MAX_USER];

//make a for loop to get the shmList's socket fd,check it flag does't it value or not
void mBroadcast(int type,Message *msg,size_t len){

			if(BLUE==type){  //if this should be broadcast to blue party
						for(int i=0;i<MAX_USER;i++){
								if(client[i].conn>0){  //if this is value
										if(BLUE==client[i].party){
													Writen(client[i].conn,msg,len);	//broadcast this proto to the socket fd;
											}	
								}
						}
			}else if(RED==type){  //if this should be broadcast to red party
						for(int i=0;i<MAX_USER;i++){
								if(client[i].conn>0){  //if this is value
										if(RED==client[i].party){
													Writen(client[i].conn,msg,len);	//broadcast this proto to the socket fd;
											}	
								}
						}
			}else if(ALL==type){  //if this should be broadcast to blue party
						for(int i=0;i<MAX_USER;i++){
								if(client[i].conn>0){  //if this is value
										Writen(client[i].conn,msg,len);	//broadcast this proto to the socket fd;
								}	

						}
			}						
		
}
		










#endif

