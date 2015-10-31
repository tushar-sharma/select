CFLAGS=-g -Wall
src=src
bin=bin
select?=
tests=tests
file=$(ins)/input.txt

default: build 

build:
	g++ $(CFLAGS) $(src)/main.cpp -o $(bin)/main

run: 
	./$(bin)/main $(file) $(select) 
