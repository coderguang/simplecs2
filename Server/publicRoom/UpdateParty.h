#ifndef UPDATE_PARTY_H_
#define UPDATE_PARTY_H_
#include "../struct/ShmServer.h"
#include "../proto/Party_toc.h"
#include "../include/BroadcastInterface.h"


extern struct shmList client[MAX_USER];
extern struct shmNum numptr;

void updateParty(){

	int iblue=0; //the blue[] index
	int ired=0; //the red[] index
	
	Party_toc *temp=new Party_toc();
	
	for(int i=0;i<MAX_USER;i++){
		if(client[i].conn>0){
				if(BLUE==client[i].party){
					temp->blue[iblue++]=client[i].id; //get the id to the party blue[] 
					continue;
				}else if(RED==client[i].party){
					temp->red[ired++]=client[i].id;
					continue;
				}					
		}

	}
	
	while(iblue<(MAX_USER/2)){
			temp->blue[iblue++]=0;
	}

	while(ired<(MAX_USER/2)){
			temp->red[ired++]=0;
	}
	//broadcast this to the all
	//
	mBroadcast(ALL,temp,sizeof(Party_toc));


}









#endif
