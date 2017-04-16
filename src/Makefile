CC = g++
CCFLAGS = -Wall -std=c++11
EXEC_NAME = main
UNAME_S = $(shell uname -s)

SRC =          \
	trie.cpp		 \
	main.cpp

OBJ = ${SRC:.cpp=.o}

ifeq ($(UNAME_S),Darwin)
  CCFLAGS += -stdlib=libc++
	CC = clang++
endif

all: ${OBJ}
	$(CC) $(CCFLAGS) -o ${EXEC_NAME} ${OBJ}

%.o: %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $+

clean:
	rm ${EXEC_NAME} *.o
