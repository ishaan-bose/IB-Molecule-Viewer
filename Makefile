CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -O3
LIBS = -lraylib -lGL -lm -lpthread -ldl -lX11

#imgui is causing some issues, i may look into it later, or might just use raylibs gui lol
IMGUIINCLUDE = -I$(CURDIR)/../includes/imgui/  -I$(CURDIR)/../includes/rlImGui/

INCLUDES = -I$(CURDIR)/source/IB_Includes/ -I$(CURDIR)/../includes/  -I$(CURDIR)/../includes/raylib/  

EXTERNALLIBS = source/External_Libs/*.cpp #please include this in the SRC whenever an external lib is there, if no external lib then dont include
SRC = source/*.cpp 

TARGET = bin/myApp

run: bin/myApp
	./bin/myApp

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)
