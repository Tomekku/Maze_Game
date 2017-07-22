#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <windows.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>


char *realpath(const char *path, char resolved_path[PATH_MAX]);

#endif
