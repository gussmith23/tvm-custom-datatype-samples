CC?=gcc

mybfloat16: mybfloat16.cc
				$(CC) -c -fpic mybfloat16.cc
				$(CC) -shared -o libmybfloat16.so mybfloat16.o
				rm mybfloat16.o

clean:
				rm mybfloat16.so
