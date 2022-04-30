CC = g++

PROG = lax

SRC := src
BUILD := build

SOURCES := $(shell find $(SRC) -name '*.cpp')
OBJS := $(SOURCES:$(SRC)/%.cpp=$(BUILD)/%.o)

all: $(BUILD)/$(PROG)

run: $(BUILD)/$(PROG)
	./$(BUILD)/$(PROG) $(file)


$(BUILD)/$(PROG): $(OBJS)
	$(CC) -o $(BUILD)/$(PROG) $^

$(OBJS): $(BUILD)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@
