CFLAGS = -Wall -Werror -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192000 -Wstack-usage=8192000 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr


all: assembler SPU


SPU: obj/SPU.o obj/StackFunc.o obj/StackVerify.o obj/CommandFunc.o
	@g++ $(CFLAGS) obj/SPU.o obj/StackFunc.o obj/StackVerify.o obj/CommandFunc.o  -o SPU


disassembler: obj/disassembler.o obj/StackFunc.o obj/StackVerify.o
	@g++ $(CFLAGS) obj/disassembler.o obj/StackFunc.o obj/StackVerify.o  -o disassembler


assembler: obj/assembler.o obj/FileFunc.o obj/StringFunc.o obj/IndexFunc.o obj/CommandFunc.o obj/StackFunc.o obj/StackVerify.o
	@g++ $(CFLAGS) obj/assembler.o obj/FileFunc.o obj/StringFunc.o obj/IndexFunc.o obj/CommandFunc.o obj/StackFunc.o obj/StackVerify.o -o assembler


obj/StackFunc.o: StackFunc/StackFunc.cpp
	@g++ $(CFLAGS) -c StackFunc/StackFunc.cpp  -o obj/StackFunc.o

obj/StackVerify.o: StackFunc/StackVerify.cpp
	@g++ $(CFLAGS) -c StackFunc/StackVerify.cpp  -o obj/StackVerify.o

obj/FileFunc.o: OneginFunc/FileFunc.cpp
	@g++ $(CFLAGS) -c OneginFunc/FileFunc.cpp  -o obj/FileFunc.o

obj/StringFunc.o: OneginFunc/StringFunc.cpp
	@g++ $(CFLAGS) -c OneginFunc/StringFunc.cpp  -o obj/StringFunc.o

obj/IndexFunc.o: OneginFunc/IndexFunc.cpp
	@g++ $(CFLAGS) -c OneginFunc/IndexFunc.cpp  -o obj/IndexFunc.o

obj/assembler.o: src/assembler.cpp
	@g++ $(CFLAGS) -c src/assembler.cpp  -o obj/assembler.o

obj/disassembler.o: src/disassembler.cpp
	@g++ $(CFLAGS) -c src/disassembler.cpp  -o obj/disassembler.o

obj/SPU.o: src/SPU.cpp
	@g++ $(CFLAGS) -c src/SPU.cpp  -o obj/SPU.o

obj/CommandFunc.o: src/CommandFunc.cpp
	@g++ $(CFLAGS) -c src/CommandFunc.cpp  -o obj/CommandFunc.o
