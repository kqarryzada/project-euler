# Creates a shared object file so that Python functions may make use of the functions in
# triangle.c.

OUTPUT_FILE="triangle.so"
# FLAGS="-lm" # -lmgp"


default:
	gcc -Wall -shared -Wl,-soname,triangle -o ${OUTPUT_FILE} -fPIC ../lib/triangle.c
	@printf "\nDone.\n"

clean:
	@rm -f ${OUTPUT_FILE}
