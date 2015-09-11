install:lib
	cp libShoreClient.so $(LIBPATH)/shoreClient/lib
	cp shoreClient.h $(LIBPATH)/shoreClient/include

lib:
	gcc shoreClient.c -o libShoreClient.so --shared -lzmq -ljansson

clean:
	rm *.so
