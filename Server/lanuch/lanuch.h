#ifndef LANUCH_H_
#define LANUCH_H_
#include <memory>
#include "../Proto.h"
#include "../../../ComLib/linuxLib/linHead.h"

void lanuch(int sockfd){
		std::shared_ptr<Lanuch_tos> ptr(new Lanuch_tos());	

		Readn(sockfd,&ptr->error_code,sizeof(Lanuch_tos)-4);
		
		













}




#endif
