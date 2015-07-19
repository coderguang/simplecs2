#ifndef MODULE_H_
#define MODULE_H_
#include "ProtoID.h"
#include <map>
#include <memory>
#include "lanuch/lanuch.h"

/**
 *This is the proto handler,all proto receive from client will be hand out in here
 *
 *
 * */

std::map<int,void (*)(int)> funMap;

//must make the function ptr in map before use it
void InitFunMap(){

	funMap[pLanuchID]=lanuch;



}



void ProtoHandle(int id,int sockfd){
	auto fn=funMap[id];
	fn(sockfd);	
}





#endif
