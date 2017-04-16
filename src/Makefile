CC1 = g++
CC2 = clang++
CCFLAGS = -Wall -std=c++11
EXEC_NAME = main
UNAME_S = $(shell uname -s)

SRC =          \
	trie.cpp		 \
	main.cpp

OBJ = ${SRC:.cpp=.o}

ifeq ($(UNAME_S),Darwin)
  CCFLAGS += -stdlib=libc++
endif

all: ${OBJ}
ifeq ($(UNAME_S),Darwin)
	$(CC2) $(CCFLAGS) -o ${EXEC_NAME} ${OBJ}
else
ifeq ($(UNAME_S),Linux)
	$(CC1) $(CCFLAGS) -o ${EXEC_NAME} ${OBJ}
endif
endif

%.o: %.cpp
ifeq ($(UNAME_S),Darwin)
	$(CC2) $(CCFLAGS) -c -o $@ $+
else
ifeq ($(UNAME_S),Linux)
	$(CC1) $(CCFLAGS) -c -o $@ $+
endif
endif

clean:
	rm ${EXEC_NAME} *.o
