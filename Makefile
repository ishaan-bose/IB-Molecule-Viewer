CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -O3
LIBS = -L/source/External_Libs/ -lraylib -lGL -lm -lpthread -ldl -lX11

INCLUDES = -I$(CURDIR)/source/IB_Includes/ -I$(CURDIR)/../includes/  -I$(CURDIR)/../includes/raylib/ -I$(CURDIR)/../includes/raygui/ -I$(CURDIR)/../includes/halfFloat/



SRC = source/*.cpp 

TARGET = bin/myApp

run: $(TARGET)
	./$(TARGET)

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)
