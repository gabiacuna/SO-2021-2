# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = laberinto
TARGET1 = buscar

all: $(TARGET)

$(TARGET): $(TARGET).c
Lab:
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
	./$(TARGET)
Bus: 
	$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).c
	./$(TARGET1)
clean:
	$(RM) $(TARGET) 
	$(RM) $(TARGET1)
