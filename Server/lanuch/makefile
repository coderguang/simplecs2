server : server.cpp
	g++ -g -o server -g server.cpp  -std=c++11 -I/usr/include/mysql -rdynamic -L/usr/lib64/mysql -lmysqlclient  -lpthread -lrt ../lib/libdb.a
clean :
	rm server *.gch *.o ../../*.gch ../../*.o

