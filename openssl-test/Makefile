OPENSSL_DIR:=/usr/local/Cellar/openssl@3/3.0.2
OPENSSL_INCLUDE_PATH:=/usr/local/Cellar/openssl@3/3.0.2/include

aesgcm: aesgcm.o
	@$(CC) aesgcm.o -o aesgcm 
aesgcm.o: aesgcm.c
	@$(CC) -I$(OPENSSL_INCLUDE_PATH) -L$(OPENSSL_DIR)/lib/libssl.a -c aesgcm.c -o aesgcm.o 


clean:
	rm -f aesgcm aesgcm.o
