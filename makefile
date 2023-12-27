test: clean
	echo "Tested successfully"

clean: run
	rm ./test_dict

run: compile
	./test_dict -f ./wordlist-ao-20101027.txt -w palavra

compile:
	gcc -g -Wall test_dict.c Dictionary.c -o test_dict

