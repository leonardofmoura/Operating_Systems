#include "server_parser.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include "logging_server.h"
#include "authentication.h"

int handle_requests();