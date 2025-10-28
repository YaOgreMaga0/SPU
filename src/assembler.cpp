#include "../src_h/assembler.h"

int main(const int argc, const char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "not enough arguments\n");
        return 1;
    }
    const char* FilenameIn = argv[1];
    const char* FilenameOut = argv[2];
    Index Text = MakeIndex(FilenameIn);
    if(Text.buf == NULL || Text.CntLines == -1 || Text.index == NULL)
    {
        fprintf(stderr, "incorrect input file\n");
        MemoryFree(&Text);
        return 1;
    }

    MakeCode(&Text, FilenameOut);
    MemoryFree(&Text);
    return 0;
}

int MakeCode(Index* Text, const char* FilenameOut)
{
    CleanBuf(Text);

    int LabelsCount = 0;
    label* labels = NULL;
    int code_commands_count = CodeSize(Text, &LabelsCount, &labels);

    int* Code = (int*)calloc((size_t)code_commands_count, sizeof(int));

    int num = 0;
    for(int i = 0; i < Text->CntLines; i++)
    {
        if(Text->index[i].string[0] != ':' && Text->index[i].len != 2)
        {
            int command_code = GetCommand(i, Text);
            if(command_code == UNKNOWN_COMMAND)
            {
                fprintf(stderr, "unknown command");
                return UNKNOWN_COMMAND;
            }

            int Arguments_Count = Commands[command_code].Arguments_count;
            Code[num] = command_code;
            num++;

            for(int j = 0; j < Arguments_Count; j++)
            {
                for(int k = 0; k < Text->index[i].len; k++)
                {
                int arg = 0;
                if(Text->index[i].string[k] == '\n')
                {
                        if(strncmp(Text->index[i].string, "PUSH\n", 5) == 0)
                            arg = GetPushArg(Text, i, k);
                        else
                        {
                            if(Text->index[i].string[0] == 'J' || Text->index[i].string[0] == 'C')
                                arg = GetJumpArg(Text, i, k, LabelsCount, labels);
                            else
                                arg = GetArg(Text, i, k);
                            if(arg < 0)
                                return INCORRECT_ARGUMENT;
                        }
                        Code[num] = arg;
                        num++;
                        break;
                    }
                    else if(Text->index[i].string[k] == '\0')
                        return NO_ARGUMENT;
                }
            }
        }
    }
    FILE* OutFile = fopen(FilenameOut, "wb");
    FillSignature(OutFile, code_commands_count);
    fwrite(Code, sizeof(int), (size_t)code_commands_count, OutFile);
    fclose(OutFile);
    free(labels);
    free(Code);
    return 0;
}

int GetCommand(int i, Index* Text)
{
    for(short int j = 0; j < count_of_commands; j++)
    {
        if(strncmp(Text->index[i].string, Commands[j].Name, strlen(Commands[j].Name)) == 0)
            return j;
    }
    return UNKNOWN_COMMAND;
}

int GetPushArg(Index* Text, int i, int j)
{
    int arg = 0;
    arg = atoi(&(Text->index[i].string[j]));
    return arg;
}

int GetJumpArg(Index* Text, int i, int j, int LabelsCount, label* labels)
{
    for(int k = 0; k < LabelsCount; k++)
    {
        if(strcmp(&(Text->index[i].string[j+2]), labels[k].name) == 0)
            return labels[k].pointer;
    }
    fprintf(stderr, "Jump to unknown label in line %d", i + 1);
    return JUMP_TO_UNKNOWN_LABEL;
}

int GetArg(Index* Text, int i, int j)
{
    j++;
    if(Text->index[i].string[j] == '[')
        j++;
    for(int k = 0; k < reg_count; k++)
    {
        if(strncmp(RegNames[k], &(Text->index[i].string[j]), 2) == 0)
            return k;
    }
    fprintf(stderr, "unknown register in line %d\n", i + 1);
    return UNKNOWN_REGISTER;
}

int CodeSize(Index* Text, int* LabelsCount, label** labels)
{
    for(int i = 0; i < Text->CntLines; i++)
    {
        if(Text->index[i].string[0] == ':')
            (*LabelsCount)++;
    }
    *labels = (label*)calloc((size_t)(*LabelsCount), sizeof(label));

    int label_number = 0;

    int code_commands_count = 0;
    for(int i = 0; i < Text->CntLines; i++)
    {
        code_commands_count++;
        if(Text->index[i].len == 2)
            code_commands_count--;
        else
        {
            if(Text->index[i].string[0] != ':')
            {
                int command_code = GetCommand(i, Text);
                if(command_code == UNKNOWN_COMMAND)
                {
                    fprintf(stderr, "unknown command in line %d", i + 1);
                    return UNKNOWN_COMMAND;
                }
                code_commands_count += Commands[command_code].Arguments_count;
            }
            else
            {
                (*labels)[label_number].name = &(Text->index[i].string[1]);
                (*labels)[label_number].pointer = code_commands_count - label_number - 2;
                label_number++;
                code_commands_count--;
            }
        }
    }
    return code_commands_count;
}

int CleanBuf(Index* Text)
{
    for(int i = 0; i < Text->CntLines; i++)
    {
        for(int j = 0; j < Text->index[i].len; j++)
        {
            if(Text->index[i].string[j] == ' ')
                Text->index[i].string[j] = '\n';
            if(Text->index[i].string[j] == ';')
            {
                Text->index[i].string[j] = '\0';
                Text->index[i].len = (int)j;
            }
        }
    }
    return 0;
}

int FillSignature(FILE* OutFile, int code_commands_count)
{
    fwrite(&assembler_version, sizeof(float), 1, OutFile);
    fwrite(&code_commands_count, sizeof(int), 1, OutFile);
    return 0;
}
