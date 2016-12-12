/*
 * Copyright (c) 2016, Nuke Sparrow <nukesparrow@bitmessage.ch>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

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
