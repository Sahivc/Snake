GXX = g++
GXXFLAGS = -std=c++17

TARGET = Snake

SOURCE = src/main.cpp \
		src/entities/board.cpp \
		src/entities/snake.cpp \
		src/entities/food.cpp \
		src/renderer/renderer.cpp \
		src/pathfinder/pathfinder.cpp \
		src/common/randnum.cpp

HEAD_FILE = src/

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(OS),Windows_NT)
RM = del /f
EXE = .exe
else
RM = rm -f
EXE = 
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET):$(SOURCE)
	$(GXX) $(GXXFLAGS) $(SOURCE) -o $(TARGET) -I $(HEAD_FILE) $(SFML_LIBS)

clean:
	$(RM) $(TARGET)$(EXE)

