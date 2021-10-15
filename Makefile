BIN_DIR=./bin
MAIN_FILE=${BIN_DIR}/main

RUNNER_OBJ=${BIN_DIR}/runner.o
GENERATOR_OBJ=${BIN_DIR}/generator.o
COUNTER_OBJ=${BIN_DIR}/counter.o

RUNNER_DIR=./runners
GENERATOR_DIR=./generators
COUNTER_DIR=./counters

# Runners
ifeq ($(runner),c)
	RUNNER_COMMAND=gcc -c ${RUNNER_DIR}/c_run.c -o ${RUNNER_OBJ}
endif
ifeq ($(runner),pthread)
	RUNNER_COMMAND=gcc -c ${RUNNER_DIR}/pthread_run.c -o ${RUNNER_OBJ} -lpthread
	FLAGS=-lpthread
endif

# Generators
ifeq ($(generator),c)
	GENERATOR_COMMAND=gcc -c ${GENERATOR_DIR}/c_gen.c -o ${GENERATOR_OBJ}
endif

# Counters
ifeq ($(counter),asm)
	COUNTER_COMMAND=nasm -f elf64 ${COUNTER_DIR}/asm_count.asm -o ${COUNTER_OBJ}
endif
ifeq ($(counter),c)
	COUNTER_COMMAND=gcc -c ${COUNTER_DIR}/c_count.c -o ${COUNTER_OBJ}
endif

all: build
build: clean
		mkdir -p ${BIN_DIR}
		${RUNNER_COMMAND}
		${GENERATOR_COMMAND}
		${COUNTER_COMMAND}
		gcc main.c ${RUNNER_OBJ} ${GENERATOR_OBJ} ${COUNTER_OBJ} -o ${MAIN_FILE} -lm ${FLAGS}
run: build
		${MAIN_FILE}
clean:
		rm -rf ${BIN_DIR}