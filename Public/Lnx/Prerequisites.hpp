/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

/* Function type macros */
#define INLINE inline __attribute__ ((always_inline))
#define NOINLINE __attribute__((noinline))
#define FUNCTION_NO_RETURN_START 
#define FUNCTION_NO_RETURN_END __attribute__((noreturn))
#define TRIGGER_BREAKPOINT() raise(SIGABRT)

#define DLLIMPORT __attribute__((visibility("default")))
#define DLLEXPORT __attribute__((visibility("default")))

/* String constants */
#ifndef PATH_SEPARATOR
#define PATH_SEPARATOR '/'
#endif
#ifndef PATH_SEPARATOR_WIDE
#define PATH_SEPARATOR_WIDE L'/'
#endif

#define FUNCTION_FULL __PRETTY_FUNCTION__

#ifndef PTHREAD_STACK_MIN
#define PTHREAD_STACK_MIN	16384
#endif