main: interface.o dbms.o main.o
	g++ -std=c++17 -o main main.o interface.o dbms.o

dbms.o: 
	g++ -std=c++17 -c dbms.cpp

interface.o: dbms.o 
	g++ -std=c++17 -c interface.cpp

main.o: interface.o dbms.o
	g++ -std=c++17 -c main.cpp

clean:
	rm -f main main.o interface.o dbms.o
