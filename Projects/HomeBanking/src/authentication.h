#include "sope.h"
#include <string.h>
#include <stdlib.h>

void generateSALT(char *salt);

void generateHASH(char * salt, char * password, char* result);

bool checkPassword(bank_account_t *bank_account, char * password);
