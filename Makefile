main: interface.o dbms.o main.o
	g++ -o main main.o interface.o dbms.o

dbms.o: 
	g++ -c dbms.cpp

interface.o: dbms.o 
	g++ -c interface.cpp

main.o: interface.o dbms.o
	g++ -c main.cpp

clean:
	rm -f main main.o interface.o dbms.o
