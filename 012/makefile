OUTPUT_FILE="problem_012.o"

default:
	gcc -Wall -o ${OUTPUT_FILE} main.c ../lib/numbers.c -lm
	@printf "\nDone.\n"

debug: 
	gcc -Wall -o ${OUTPUT_FILE} -g main.c ../lib/numbers.c -lm

clean: 
	@rm -f ${OUTPUT_FILE}
