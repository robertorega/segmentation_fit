CC = gcc
CFLAGS = -Wall -g

TARGET = segmentation_fit

SRCS = main.c coda.c hash.c pila.c utile_coda.c utile_hash.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
