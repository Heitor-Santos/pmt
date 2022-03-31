CC = g++
CFLAGS = -std=c++17
BIN = ../bin
TARGET = pmt

all: clean compile

compile:
	@mkdir $(BIN)
	@$(CC) $(CFLAGS) main.cpp utils.cpp algorithms/*.cpp -o $(BIN)/$(TARGET)

clean:
	@rm -rf $(BIN)