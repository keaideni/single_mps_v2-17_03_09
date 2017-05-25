## Set which compiler to use by defining CCCOM:
##GNU GCC compiler
#CCCOM=g++ -m64 -std=c++11 
##Clang compiler (good to use on Mac OS)
#CCCOM=clang++ -std=c++1y
##Intel C++ compiler (good to use with Intel MKL if available)
CCCOM=g++ -std=c++14 -g
#########


## Flags to give the compiler for "release mode"



#LIBFLAGS = -larmadillo
LIBSPECTRA = -I/media/xuejian/WORK/spectra/spectra-0.2.0/spectra-0.2.0/include/ -I/media/xuejian/WORK/spectra/eigen-eigen-67e894c6cd8f/







obj=main.o Parameter.o OP.o SiteWave.o Sub.o SubLattice.o#QWave.o Super.o DMRGP.o Corr.o
main:$(obj)
	$(CCCOM) -o main $(obj)  $(LIBSPECTRA)
main.o:main.cpp test_Sub.h test_SiteWave.h test_sublattice.h
	$(CCCOM) -c main.cpp $(LIBSPECTRA)
Parameter.o:Parameter.h Parameter.cpp
	$(CCCOM) -c Parameter.cpp -O2 $(LIBSPECTRA)
OP.o:OP.cpp OP.h
	$(CCCOM) -c OP.cpp -O2 $(LIBSPECTRA)
SiteWave.o:SiteWave.h SiteWave.cpp
	$(CCCOM) -c SiteWave.cpp -O2 $(LIBSPECTRA)
Sub.o:Sub.h Sub.cpp
	$(CCCOM) -c Sub.cpp -O2 $(LIBSPECTRA)
SubLattice.o:SubLattice.h SubLattice.cpp
	$(CCCOM) -c SubLattice.cpp -O2 $(LIBSPECTRA)
.PHONY:clean
clean:
	rm -f main $(obj)















