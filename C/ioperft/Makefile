CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c18

all: ioperft.c
	$(CC) $^ $(CFLAGS) -o ioperft
	$(CC) $^ $(CFLAGS) -o ioperft_0 -O0
	$(CC) $^ $(CFLAGS) -o ioperft_1 -O1
	$(CC) $^ $(CFLAGS) -o ioperft_2 -O2
	$(CC) $^ $(CFLAGS) -o ioperft_3 -O3
	$(CC) $^ $(CFLAGS) -o ioperft_f -Ofast
	$(CC) $^ $(CFLAGS) -o ioperft_g -Og
	$(CC) $^ $(CFLAGS) -o ioperft_s -Os
	$(CC) $^ $(CFLAGS) -o ioperft_z -Oz

.PHONY: clean

clean:
	rm ioperft ioperft_*
