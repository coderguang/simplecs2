#ifndef SER_STRUCT_H_
#define SER_STRUCT_H_

class SerNum{
	public:
		int counter;
		int blue;
		int red;	
};

class SerList{
	public:
		int connfd;
		int id;
		int party;
};

enum Status{IN_ROOM,IN_GAME,IN_RESULT};

class SerStatus{
	public:
		Status status;
};




#endif
