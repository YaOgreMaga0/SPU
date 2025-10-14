#include <string.h>

#include "../src_h/translator.h"
#include "../src_h/LanguageCode.h"
#include "../src_h/ByteCode.h"

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        if(strncmp(argv[1], "--language", 10) == 0)
        {
            LanguageCode(argv[2]);
            return 0;
        }
        if(strncmp(argv[1], "--byte", 6) == 0)
        {
            ByteCode(argv[2]);
            return 0;
        }
        else
        {
            fprintf(stderr, "unknown command");
            return 1;
        }
    }
    else if(argc == 4)
    {
        if(strncmp(argv[1], "--translator", 12) == 0)
        {
            Translator(argv[2], argv[3]);
            return 0;
        }
        else
        {
            fprintf(stderr, "unknown command");
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "unknown command");
        return 1;
    }
}
