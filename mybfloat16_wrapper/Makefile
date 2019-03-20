mybfloat16_wrapper: mybfloat16_wrapper.cc
				gcc -c -g -fPIC mybfloat16_wrapper.cc
				gcc -shared -o libmybfloat16_wrapper.so mybfloat16_wrapper.o
				rm mybfloat16_wrapper.o

clean:
				rm libmybfloat16_wrapper.so
