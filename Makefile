## Set which compiler to use by defining CCCOM:
##GNU GCC compiler
#CCCOM=g++ -m64 -std=c++11 
##Clang compiler (good to use on Mac OS)
#CCCOM=clang++ -std=c++1y
##Intel C++ compiler (good to use with Intel MKL if available)
CCCOM=g++ -std=c++11 -g
#########


## Flags to give the compiler for "release mode"



#LIBFLAGS = -larmadillo
LIBSPECTRA = -I/media/xuejian/WORK/spectra/spectra-0.2.0/spectra-0.2.0/include/ -I/media/xuejian/WORK/spectra/eigen-eigen-07105f7124f9/







obj=main.o Parameter.o OP.o #Sub.o P_Sub.o#QWave.o Super.o DMRGP.o Corr.o
main:$(obj)
	$(CCCOM) -o main $(obj)  $(LIBSPECTRA)
main.o:main.cpp 
	$(CCCOM) -c main.cpp $(LIBSPECTRA)
Parameter.o:Parameter.h Parameter.cpp
	$(CCCOM) -c Parameter.cpp -O2 $(LIBSPECTRA)
OP.o:OP.cpp OP.h
	$(CCCOM) -c OP.cpp -O2 $(LIBSPECTRA)
.PHONY:clean
clean:
	rm -f main $(obj)















