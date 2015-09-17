install:lib
ifdef LIBPATH
	cp libShoreClient.so $(LIBPATH)/shoreClient/lib
	cp shoreClient.h $(LIBPATH)/shoreClient/include
endif

lib:
	gcc -fPIC shoreClient.c -o libShoreClient.so --shared -lzmq -ljansson

clean:
	rm *.so
