#ifndef YUBEL_PERF_H
#define YUBEL_PERF_H

#include "check.h"
#include <time.h>

#define execution(expected, function)  clock_t start; clock_t end; start = clock(); function(); end = clock(); if(expected < end - start) {success++; puts("ok"); } else{ failures++; puts("KO");} if(status){exit(status);}
#endif
