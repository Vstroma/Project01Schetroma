
output: MYpsSchetroma.o 
	gcc MYpsSchetroma.o -o    out

CPUinfo.o: MYpsSchetroma.c
	gcc -c MYpsSchetroma.c
MemInfo.o: MYpsSchetroma.c
	gcc -c MYpsSchetroma.c

clean: 
	rm *.o out