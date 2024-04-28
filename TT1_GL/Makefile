CC=g++
CFLAGS=-c -Wall 
OBJ = main.o circuit.o Condensateur.o Generateur.o ij.o Inductance.o M.o mat.o matAij.o Nports.o Resistance.o Switch.o Courant.o inductMut.o
OBJ_testUni1 = test_Matvect.o circuit.o Condensateur.o Generateur.o ij.o Inductance.o M.o mat.o matAij.o Nports.o Resistance.o Switch.o Courant.o inductMut.o
OBJ_sol1 = testSol_1.o circuit.o Condensateur.o Generateur.o ij.o Inductance.o M.o mat.o matAij.o Nports.o Resistance.o Switch.o Courant.o inductMut.o
OBJ_Sol2 = testSol_2.o circuit.o Condensateur.o Generateur.o ij.o Inductance.o M.o mat.o matAij.o Nports.o Resistance.o Switch.o Courant.o inductMut.o
OBJ_Sol3 = testSol_3.o circuit.o Condensateur.o Generateur.o ij.o Inductance.o M.o mat.o matAij.o Nports.o Resistance.o Switch.o Courant.o inductMut.o

all : main
all1 : test_Matvect
all_sol1 : testSol_1
all_sol2 : testSol_2
all_sol3 : testSol_3

main : $(OBJ)
	$(CC) -o main $(OBJ)

main.cpp : Nports.hpp circuit.hpp mat.hpp ij.hpp matAij.hpp 
	$(CC) $(CFLAGS) main.cpp

test_Matvect : $(OBJ_testUni1)
	$(CC) -o test_Matvect $(OBJ_testUni1)

test_Matvect.cpp : circuit.hpp Nports.hpp
	$(CC) $(CFLAGS) test_Matvect.cpp

testSol_1 : $(OBJ_sol1)
	$(CC) -o testSol_1 $(OBJ_sol1)

testSol_1.cpp : Nports.hpp circuit.hpp mat.hpp ij.hpp matAij.hpp
	$(CC) $(CFLAGS) testSol_1.cpp

testSol_2 : $(OBJ_Sol2)
	$(CC) -o testSol_2 $(OBJ_Sol2)

testSol_2.cpp : Nports.hpp circuit.hpp mat.hpp ij.hpp matAij.hpp
	$(CC) $(CFLAGS) testSol_2.cpp

testSol_3 : $(OBJ_Sol3)
	$(CC) -o testSol_3 $(OBJ_Sol3)

testSol_3.cpp : Nports.hpp circuit.hpp mat.hpp ij.hpp matAij.hpp
	$(CC) $(CFLAGS) testSol_3.cpp

Nports.o :  Nports.hpp 
	$(CC) $(CFLAGS) Nports.cpp 

circuit.o : ij.hpp Nports.hpp Generateur.hpp Condensateur.hpp Inductance.hpp M.hpp Resistance.hpp Switch.hpp Courant.hpp inductMut.hpp
	$(CC) $(CFLAGS) circuit.cpp 

Condensateur.o : Nports.hpp
	$(CC) $(CFLAGS) Condensateur.cpp

Generateur.o : Nports.hpp
	$(CC) $(CFLAGS) Generateur.cpp

Inductance.o : Nports.hpp
	$(CC) $(CFLAGS) Inductance.cpp

M.o : Nports.hpp
	$(CC) $(CFLAGS) M.cpp

Resistance.o : Nports.hpp
	$(CC) $(CFLAGS) Resistance.cpp

ij.o : mat.hpp 
	$(CC) $(CFLAGS) ij.cpp

mat.o : 
	$(CC) $(CFLAGS) mat.cpp

matAij.o : ij.hpp mat.hpp
	$(CC) $(CFLAGS) matAij.cpp


test_main : all clean
	./main
	
test_uni1 : all1 clean
	./test_Matvect

test_sol_1 : all_sol1 clean
	./testSol_1	

test_sol_2 : all_sol2 clean
	./testSol_2	

test_sol_3 : all_sol3 clean
	./testSol_3	

clean :
	rm -rf *.o

