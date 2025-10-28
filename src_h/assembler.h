#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../OneginFunc/FileFunc.h"
#include "../OneginFunc/StringFunc.h"
#include "../OneginFunc/IndexFunc.h"
#include "CommandFunc.h"

typedef enum
{
    UNKNOWN_COMMAND = -1,
    NO_ARGUMENT = -2,
    JUMP_TO_UNKNOWN_LABEL = -3,
    UNKNOWN_REGISTER = -4,
    INCORRECT_ARGUMENT = -5
} AssemblerErrors;

typedef struct
{
    char* name;
    int pointer;
} label;

const float assembler_version = 1.3f;

int CodeSize(Index* Text, int* LabelsCount, label** labels);
int MakeCode(Index* Text, const char* FilenameOut);
int GetCommand(int i, Index* Text);
int GetPushArg(Index* Text, int i, int j);
int GetJumpArg(Index* Text, int i, int j, int LabelsCount, label* labels);
int GetArg(Index* Text, int i, int j);
int CleanBuf(Index* Text);
int FillSignature(FILE* OutFile, int code_commands_count);

#endif //ASSEMBLER_H
