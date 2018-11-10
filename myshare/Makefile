.PHONY:all clean
all:write main
main:main.cpp libadd.so 
	g++ -o $@ $< -L. -ladd
write:write.cpp
	g++ -o $@ $^
libadd.so: myadd.cpp
	g++ -fPIC -shared -o $@ $^
clean:
	rm -f write main myadd.o 
