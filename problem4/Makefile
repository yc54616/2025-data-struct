all: generate sort

generate: generate_data.c
	gcc -o generate generate_data.c

sort: sort.c
	gcc -o sort sort.c

clean:
	rm -f generate sort
