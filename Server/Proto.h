/**
 *every proto header file must include in here
 */
#ifndef PROTO_H_
#define PROTO_H_

/**
 *all Message proto base on this class
 *only id and error_code are common
 *author:coderguang
 *date:2014/04/08
 */
#pragma pack(1)
class Message{
public:
	int id;
	int error_code;
	
	int GetID()const{
		return id;
	}
	int GetError_code(){
		return error_code;
	}
};

static const int ACCOUNTSIZE=8;
static const int PASSWDSIZE=16;

#pragma pack(1)
class Lanuch_tos:public Message
{
	public:
		char account[ACCOUNTSIZE];
		int acclen;
		char passwd[PASSWDSIZE];
		int paslen;

		Lanuch_tos(){
		}

};

static const int NAMESIZE=8;
static const int LASTIPSIZE=16;
static const int LASTLANUCHSIZE=32;

#pragma pack(1)
class LanuchResult_toc:public Message
{
public:
		int account_id;
		int setting;
		int party;
		char name[NAMESIZE];
		int namelen;
		char lastIP[LASTIPSIZE];
		int iplen;
		char lastLanuch[LASTLANUCHSIZE];
		int timelen;
		
		LanuchResult_toc(){
			id=pLanuchResultID;
			error_code=0;
		}

		LanuchResult_toc(string n,string lastTime,string lastip,int s,int a_id){
				id=pLanuchResultID;
				namelen=n.length();
				memcpy(name,n.c_str(),n.length()+1);	
				timelen=lastTime.length();
				memcpy(lastLanuch,lastTime.c_str(),lastTime.length()+1);	
				iplen=lastip.length();
				memcpy(lastIP,lastip.c_str(),lastip.length()+1);
				setting=s;
				account_id=a_id;
		}
		
};

static const int MAX_CHAT_SIZE=32;
#pragma pack(1)
class Chat_tocs:public Message{
public:
		int user_id;//who send this chat
		int type;//the party
		char msg[MAX_CHAT_SIZE];
		int msglen;
		
		Chat_tocs(){
			id=pChatID;
			error_code=0;
		}
		
		Chat_tocs(int uid,int t,string ms){
			id=pChatID;
			error_code=0;
			user_id=uid;
			type=t;
			msglen=ms.length();
			memcpy(msg,ms.c_str(),ms.length()+1);

		}



};

#pragma pack(1)
class Party_toc:public Message{
public:
	//the party list id
	/**
	int r1;	
	int r2;
	int r3;
	int r4;
	int r5;

	int b1;
	int b2;
	int b3;
	int b4;
	int b5;
	**/
	
	
	int red[MAX_USER/2];
	int blue[MAX_USER/2];

	 Party_toc(){
			id=partyID;
			error_code=0;
	}

	Party_toc(int rr1,int rr2,int rr3,int rr4,int rr5,int bb1,int bb2,int bb3,int bb4,int bb5){

		id=partyID;
		error_code=0;

		red[0]=rr1;
		red[1]=rr2;
		red[2]=rr3;
		red[3]=rr4;
		red[4]=rr5;
		
		blue[0]=bb1;
		blue[1]=bb2;
		blue[2]=bb3;
		blue[3]=bb4;
		blue[4]=bb5;

		/**
		r1=rr1;
		r2=rr2;
		r3=rr3;
		r4=rr4;
		r5=rr5;

		b1=bb1;
		b2=bb2;
		b3=bb3;
		b4=bb4;
		b5=bb5;
		**/
	}


};

#pragma pack(1)

class Party_change_tocs:public Message{

public:
		Party_change_tocs(){
				id=partyChangeID;
				error_code=0;
		}



};

#pragma pack(1)
class GameStart_tocs:public Message{

public:
	int r1=0;
	int r2=0;
	int r3=0;
	int r4=0;
	int r5=0;
	
	int b1=0;
	int b2=0;
	int b3=0;
	int b4=0;
	int b5=0;


	GameStart_tocs(){
		id=gameStartID;
		error_code=0;
	}


};

#pragma pack(1)
class Pos_tocs:public Message{
public:
	int userID;
	int x;
	int y;
	int z;
	
};




#endif
