all:
	clang++ myapriori.cpp -o myapriori.out
	./myapriori.out datafile1.txt 40

clean:
	rm -rf myapriori.out