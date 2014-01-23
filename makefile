CXX = g++
CXXFLAGS = -Wall -g -O3
#-std=gnu++98 -fPIC

LD_FLAGS = -Llib/cv -Llib/vl -lvl -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_flann 

INCLUDE_FLAGS = -Iinclude/
#LIBFLAGS = -fopenmp

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

OBJECTS =	$(BUILD_DIR)/llbp.o \
			$(BUILD_DIR)/main.o
			
TARGET = $(BIN_DIR)/llbp

.PHONY: all clean

all: $(TARGET)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE_FLAGS)
	
$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LD_FLAGS)

clean:
	$(RM) $(TARGET) $(OBJECTS)
