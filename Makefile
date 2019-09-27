all:
	clang++ myapriori.cpp -o myapriori.out
	./myapriori.out datafile1.txt 30

clean:
	rm -rf myapriori.out