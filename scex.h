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

/* 
 * File:   scex.h
 * Author: Nuke Sparrow <nukesparrow@bitmessage.ch>
 *
 * Created on December 12, 2016, 2:38 PM
 */

#ifndef SCEX_H
#define SCEX_H

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef PERROR
#include <stdio.h>

#define PERROR(n) perror(n)
#endif

#ifndef PRINTF_ERROR
#include <stdio.h>

#define PRINTF_ERROR(n, ...) fprintf(stderr, n, ##__VA_ARGS__)
#endif

/* Exception numbers */
#define EXNONE 0
#define EXUNSPECIFIED -1
#define EXC -2
    
#define TRY \
    { \
	int _try_error=EXUNSPECIFIED; char *_failed_cond = NULL; \
	do {

#define EXCEPT \
	    _try_error=EXNONE; \
	} while(0); \
	if (_try_error != EXNONE) { \

#define ETRY \
	} \
    } \

#define THROWN (_try_error)
    
#define CATCH(n) if(_try_error == (n))

#ifdef DEBUG

#define THROW(n) \
    { \
	PRINTF_ERROR("Thrown %s(%d) at %s:%d\n", #n, (n), __FILE__, __LINE__); \
	_try_error=(n); \
	_failed_cond="unconditional"; \
	break; \
    }

#define THROW_IF(n,e) if(n) { \
	PRINTF_ERROR("Check failed for %s : (%d) at %s:%d\n", #n, (e), __FILE__, __LINE__); \
	_try_error=(e); \
	_failed_cond=#n; \
	break; \
    }

#else

#define THROW(n) \
    { \
	_try_error=(n); \
	break; \
    }

#define FAIL break;\

#define THROW_IF(n,e) if(n) THROW(e)

#endif

#define THROW_UNLESS(n,e) THROW_IF(!(n),e)
#define THROW_IFNEG(n,e) THROW_IF((n) < 0,e)
#define THROW_IFNULL(n,e) THROW_IF((n) == NULL,e)

#define CTHROW_IF(n) THROW_IF(n,EXC)
#define CTHROW_UNLESS(n) THROW_UNLESS(n,EXC)
#define CTHROW_NEG(n) THROW_IFNEG(n,EXC)
#define CTHROW_NULL(n) THROW_IFNULL(n,EXC)

#define _SIMEX_H_STR_HELPER(x) #x
#define _SIMEX_H_STR(x) _SIMEX_H_STR_HELPER(x)

#define EXCEPT_PRINTC EXCEPT_PRINT("non-libc exception, when only libc exceptions should be caught")

#define EXCEPT_PRINT(e) \
    EXCEPT { \
	if (_failed_cond == NULL) { \
	    _failed_cond = "No error condition for exception, thrown to " __FILE__ ":" _SIMEX_H_STR(__LINE__); \
	}\
	if (_try_error == EXC) { \
	    PERROR(_failed_cond); \
	} else {\
	    PRINTF_ERROR("%s: %s\n", _failed_cond, e);\
	} \
    } ETRY

#ifdef __cplusplus
}
#endif

#endif /* SCEX_H */
