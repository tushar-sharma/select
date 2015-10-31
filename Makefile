CFLAGS=-g -Wall
src=src
bin=bin
select?=
tests=tests
ins=ins
outs=outs
infile=$(ins)/input.txt
outfile=$(outs)/output.txt
k?=

default: build 

build:
	g++ $(CFLAGS) $(src)/main.cpp -o $(bin)/main

run: 
	./$(bin)/main $(infile) $(select) $(k) 

check:
	cat $(outfile)
