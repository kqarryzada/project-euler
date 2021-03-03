OUTPUT_FILE="problem_018.o"
FLAGS="-lm" # -lmgp"

default:
	gcc -Wall -o ${OUTPUT_FILE} problem_018.c ../lib/triangle.c ${FLAGS}
	@printf "\nDone.\n"

debug:
	gcc -Wall -o ${OUTPUT_FILE} -g problem_018.c ../lib/triangle.c ${FLAGS}
clean:
	@rm -f ${OUTPUT_FILE}
