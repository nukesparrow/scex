#include <stdio.h>
#include <errno.h>

#include "scex.h"

int main(int argc, char** argv) {
    TRY {
        printf("Try\n");
	TRY {
	    THROW(1);
	    printf("Yo!\n");
	} EXCEPT {
	    printf("Err #%d!\n", THROWN);
	} ETRY
        THROW_UNLESS(1==2, -2);
        printf("No!\n");
    } EXCEPT {
        printf("Except #%d\n", THROWN);
    } ETRY

    printf("Done with first\n");

    TRY {
	errno = ENOENT; // No such file or directory
	int retval = -1;
	CTHROW_NEG(retval); // Condition: "retval" , should print: "(retval) < 0: No such file or directory"
    } EXCEPT_PRINTC

    printf("Done with second\n");

    TRY {
	THROW_IF(1, -3);   // Condition: "1" , should print: "1: error!"
    } EXCEPT_PRINT("error!")

    printf("Done with third\n");

    return 0;
}
