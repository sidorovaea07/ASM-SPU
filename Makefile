FLAGS=-D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

PT_ONEG=../../2Dmas/evgene
PT_ASM=source/AsmProject
PT_SPU=source/SPUProject
PT_OBJ=obj
PT_BLT=build

all: asm spu
	
asmprog:
	./${PT_BLT}/asm 
	
spuprog:
	./${PT_BLT}/spu

asm: Stack.o FileWork.o PtrsWork.o AsmMain.o StrFunc.o MyASM.o
	g++ ${PT_OBJ}/Stack.o ${PT_OBJ}/FileWork.o ${PT_OBJ}/PtrsWork.o ${PT_OBJ}/AsmMain.o ${PT_OBJ}/StrFunc.o ${PT_OBJ}/MyASM.o ${FLAGS} -o ${PT_BLT}/asm
	./${PT_BLT}/asm

spu: Stack.o FileWork.o SpuMain.o MySPU.o
	g++ ${PT_OBJ}/Stack.o ${PT_OBJ}/FileWork.o ${PT_OBJ}/SpuMain.o ${PT_OBJ}/MySPU.o ${FLAGS} -o ${PT_BLT}/spu
	./${PT_BLT}/spu

stack: Stack.o
	g++ ${PT_OBJ}/Stack.o ${FLAGS} -o stack
	./stack

FileWork.o: ${PT_ONEG}/FileWork.cpp
	g++ ${PT_ONEG}/FileWork.cpp ${FLAGS} -c -o ${PT_OBJ}/FileWork.o

PtrsWork.o: ${PT_ONEG}/PtrsWork.cpp
	g++ ${PT_ONEG}/PtrsWork.cpp ${FLAGS} -c -o ${PT_OBJ}/PtrsWork.o

StrFunc.o: ${PT_ONEG}/StrFunc.cpp
	g++ ${PT_ONEG}/StrFunc.cpp ${FLAGS} -c -o ${PT_OBJ}/StrFunc.o

MyASM.o: ${PT_ASM}/MyASM.cpp
	g++ ${PT_ASM}/MyASM.cpp ${FLAGS} -c -o ${PT_OBJ}/MyASM.o

MySPU.o: ${PT_SPU}/MySPU.cpp
	g++ ${PT_SPU}/MySPU.cpp ${FLAGS} -c -o ${PT_OBJ}/MySPU.o

SpuMain.o: ${PT_SPU}/SpuMain.cpp
	g++ ${PT_SPU}/SpuMain.cpp ${FLAGS} -c -o ${PT_OBJ}/SpuMain.o

AsmMain.o: ${PT_ASM}/AsmMain.cpp
	g++ ${PT_ASM}/AsmMain.cpp ${FLAGS} -c -o ${PT_OBJ}/AsmMain.o

Stack.o: source/Stack.cpp
	g++ source/Stack.cpp ${FLAGS} -c -o ${PT_OBJ}/Stack.o

clean:
	rm -rf *.o *.exe *.dmp *.log *.log.dmp *.exe.log.dmp

build:
	make -C SPUProject
