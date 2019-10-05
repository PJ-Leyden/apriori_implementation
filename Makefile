all:
	clang++ myapriori.cpp -o myapriori.out
	./myapriori.out datafile1.txt 10
	./myapriori.out datafile1.txt 20
	./myapriori.out datafile1.txt 30
	./myapriori.out datafile1.txt 50

clean:
	rm -rf myapriori.out