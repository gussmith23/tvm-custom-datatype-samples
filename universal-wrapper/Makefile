universal-posit-wrapper: universal-posit-wrapper.cc
				gcc -c -g -fPIC universal-posit-wrapper.cc
				gcc -shared -o libposit.so universal-posit-wrapper.o
				rm universal-posit-wrapper.o

clean:
				rm libposit.so
