CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -O3
LIBS = -lraylib -lGL -lm -lpthread -ldl -lX11
INCLUDES = -I$(CURDIR)/source/IB_Includes/ -I$(CURDIR)/../includes/  -I$(CURDIR)/../includes/raylib/  -I$(CURDIR)/../includes/imgui/  -I$(CURDIR)/../includes/rlImGui/


SRC = source/*.cpp source/External_Libs/*.cpp

TARGET = bin/myApp

run: bin/myApp
	./bin/myApp

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)
