lib:
	gcc shoreClient.c -o libShoreClient.so --shared

install:lib
	cp libShoreClient.so $(LIBPATH)/shoreClient/lib
	cp shoreClient.h $(LIBPATH)/shoreClient/include



clean:
	rm *.so
