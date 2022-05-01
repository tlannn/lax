CC = g++

PROG = lax

SRC := src
BUILD := build

SOURCES := $(shell find $(SRC) -name '*.cpp')
OBJS := $(SOURCES:$(SRC)/%.cpp=$(BUILD)/%.o)

all: $(BUILD)/$(PROG)

run: $(BUILD)/$(PROG)
	./$(BUILD)/$(PROG) $(file)

clean:
	rm -rf $(BUILD)

$(BUILD)/$(PROG): $(OBJS)
	$(CC) -o $(BUILD)/$(PROG) $^

$(OBJS): $(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@
