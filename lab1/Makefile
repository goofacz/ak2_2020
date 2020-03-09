all: app_c app_s

app_s: app.s
	as app.s -g -o app_s.o
	ld app_s.o -o app_s

app_c: app.c
	gcc app.c -m32 -O0 -g -o app_c -lpthread

clean:
	rm -f app_s app_c app_s.*
