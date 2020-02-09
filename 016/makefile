OUTPUT_FILE="problem_016.o"
FLAGS="-lm" # -lgmp"

default:
	gcc -Wall -o ${OUTPUT_FILE} main.c ../lib/numbers.c ${FLAGS}
	@printf "\nDone.\n"

debug: 
	gcc -Wall -o ${OUTPUT_FILE} -g main.c ../lib/numbers.c ${FLAGS}
clean: 
	@rm -f ${OUTPUT_FILE}
