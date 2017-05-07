
default: sha-512

sha-512: sha-512.c
	gcc sha-512.c -o sha-512

clean:
	-rm -f sha-512
