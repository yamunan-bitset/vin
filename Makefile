CXX        = gcc
CFLAGS     = -g
LINKERLIBS = -lIL -lGL -lGLU -lglut
OBJS       = src/vin.o
OUT        = vin
PATH       = /usr/bin/

build: $(OBJS)
	$(CXX) $(OBJS) $(CFLAGS) $(LINKERLIBS) -o $(OUT)

clean:
	rm -rf $(OBJS) $(OUT)

install:
	sudo cp $(OUT) $(PATH)
