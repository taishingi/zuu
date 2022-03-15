#ifndef YUBEL_CHECK_H
#define YUBEL_CHECK_H

#include <stdio.h>
#include <stdlib.h>
							#include <stdbool.h>
#include <strings.h>

extern unsigned int success;
extern unsigned int failures;
extern int status;
#define immunity() fprintf(stdout,"\nAssertions : %d\nFailures   : %d\nExecuted   : %d\n\n",success,failures,success+failures);
#define check(test, s, f) if(test) {success++; fprintf(stdout,"\n[  Ok  ] %s\n",s); status = EXIT_SUCCESS; } else{ failures++; fprintf(stderr,"\n[  KO  ] %s %s %d\n",f,__FILE__,__LINE__); status = EXIT_FAILURE;} if(status) { immunity(); exit(status);};
#endif
