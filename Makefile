default: psi _psi.so

CC = /usr/local/bin/g++-10 -O3 -std=c++2a -fcoroutines -ftree-vectorize
SWIG = swig

%.o: %.cpp
	$(CC) -c -o $@ $< 

psi: psi.o DenseMatrix.o ReferenceCountingPointer.o Util.o
	$(CC) -o psi $^ -lblas -llapack  -lmatio

psiAn: psiAn.o
	$(CC) -o psiAn $^

psi.py psi_wrap.cxx: psi.i
	$(SWIG) -python -c++ $<

psi_wrap.o: psi_wrap.cxx
	$(CC) -fPIC -o $@ -c $^ `python3-config --cflags`

_psi.so: psi_wrap.o psiAn.o
	$(CC) -shared -o $@ $^ `python3-config --libs --ldflags` -lpython3.8 -lmatio

clean:
	rm *.o *.cxx *.so *.i *.a psi psiAn psi_wrap.* 

