CC=gcc 
LD=gcc

INCDIR=../include
SRC=../src

VPATH=$(SRC)
CFLAGS=-I$(INCDIR) -g

TARGET=mem_hog
SRCS=$(foreach dir, .. $(SRC), $(wildcard $(dir)/*.c))
SRCS:=$(notdir $(SRCS))


OBJS=$(SRCS:.c=.o)

all:$(TARGET)

$(TARGET):$(OBJS)
	$(LD) $^ -o$(TARGET) $(LIBS)
	mv $(TARGET) ../

%o:%c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -rf ./depend
	-rm -rf $(OBJS)
	-rm -f ../$(TARGET)

depend: $(SRCS)
	$(CC) -M $(CFLAGS) $^ > $@

-include depend
