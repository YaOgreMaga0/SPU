SPU: obj/SPU.o obj/ByteCode.o obj/LanguageCode.o obj/translator.o obj/CommandFunc.o obj/StackFunc.o obj/StackVerify.o obj/FileFunc.o obj/StringFunc.o obj/IndexFunc.o
	g++ obj/SPU.o obj/ByteCode.o obj/LanguageCode.o obj/translator.o obj/StackFunc.o obj/StackVerify.o obj/CommandFunc.o obj/FileFunc.o obj/StringFunc.o obj/IndexFunc.o -o SPU

obj/SPU.o: src/SPU.cpp
	g++ -c src/SPU.cpp -o obj/SPU.o

obj/StackFunc.o: src/StackFunc.cpp
	g++ -c src/StackFunc.cpp -o obj/StackFunc.o

obj/StackVerify.o: src/StackVerify.cpp
	g++ -c src/StackVerify.cpp -o obj/StackVerify.o

obj/CommandFunc.o: src/CommandFunc.cpp
	g++ -c src/CommandFunc.cpp -o obj/CommandFunc.o

obj/ByteCode.o: src/ByteCode.cpp
	g++ -c src/ByteCode.cpp -o obj/ByteCode.o

obj/LanguageCode.o: src/LanguageCode.cpp
	g++ -c src/LanguageCode.cpp -o obj/LanguageCode.o

obj/translator.o: src/translator.cpp
	g++ -c src/translator.cpp -o obj/translator.o

obj/FileFunc.o: OneginFunc/FileFunc.cpp
	g++ -c OneginFunc/FileFunc.cpp -o obj/FileFunc.o

obj/StringFunc.o: OneginFunc/StringFunc.cpp
	g++ -c OneginFunc/StringFunc.cpp -o obj/StringFunc.o

obj/IndexFunc.o: OneginFunc/IndexFunc.cpp
	g++ -c OneginFunc/IndexFunc.cpp -o obj/IndexFunc.o
