all: p0.c
	gcc p0.c -o ppmrw

clean:
	rm -rf ppmrw *~
