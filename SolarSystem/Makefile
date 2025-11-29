CXX = g++
CXXFLAGS = -Wall -Iinclude
LDFLAGS = -lGL -lGLU -lglut -lSDL2 -lSDL2_mixer -lm

TARGET = solar_system
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
