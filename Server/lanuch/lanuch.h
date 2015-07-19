#ifndef LANUCH_H_
#define LANUCH_H_
#include <memory>
#include <string>
#include "../Proto.h"
#include "../../../ComLib/linuxLib/linHead.h"
#include "../myDB/dbcpp/DBInterface.h"
#include "../myDB/dbcpp/DBErr.h"
#include "../struct/strLanuch.h"


void lanuch(int sockfd){
		std::shared_ptr<Lanuch_tos> ptr(new Lanuch_tos());	

		Readn(sockfd,&ptr->error_code,sizeof(Lanuch_tos)-4);
		
		ptr->account[ptr->acclen]='\0';
		ptr->passwd[ptr->paslen]='\0';

		std::string account=ptr->account;
		std::string passwd=ptr->passwd;

		std::cout<<"account="<<account<<"   passwd="<<passwd<<std::endl;

		struct Lanuch lanResult;

		int rNum=LanuchAccount(account,passwd,"",lanResult);

		std::cout<<"return num is "<<rNum<<std::endl;
		
			













}




#endif
