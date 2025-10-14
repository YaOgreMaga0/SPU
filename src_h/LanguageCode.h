#ifndef LANGUAGECODE_H
#define LANGUAGECODE_H

#include <stdio.h>
#include "CommandFunc.h"

int GetCommand(FILE* fp);
int LanguageCode(char* filename);
int TurnNameIntoCode(const char* command);

#endif //LANGUAGECODE_H
