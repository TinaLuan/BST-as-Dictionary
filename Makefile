# Makefile for COMP20003 Assignment01
# tluan1
# Tian Luan 769321

CC = gcc
CFLAGS = -c -Wall

yelp1: main_1.o dictops_1.o
	$(CC) main_1.o dictops_1.o -o yelp1

yelp2: main_2.o dictops_2.o
	$(CC) main_2.o dictops_2.o -o yelp2

main_1.o: main_1.c
	$(CC) $(CFLAGS) main_1.c

main_2.o: main_2.c
	$(CC) $(CFLAGS) main_2.c

dictops_1.o: dictops_1.c
	$(CC) $(CFLAGS) dictops_1.c dictops_1.h

dictops_2.o: dictops_2.c
	$(CC) $(CFLAGS) dictops_2.c dictops_2.h
