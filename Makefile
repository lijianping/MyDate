MyDate: main.o my_date.o
	g++ main.o my_date.o -o MyDate
my_date.o: my_date.h my_date.cc
	g++ -c my_date.cc
main.o: my_date.h main.cc
	g++ -c main.cc
clean:
	rm -r main.o my_date.o MyDate
