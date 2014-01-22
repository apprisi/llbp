CXX = g++
CXXFLAGS = -Wall -g -O3
#-std=gnu++98 -fPIC

LD_FLAGS = -Llib/opencv

#LIBFLAGS = -fopenmp

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

OBJECTS =	$(BUILD_DIR)/llbp.o \
			$(BUILD_DIR)/main.o
			
TARGET = $(BIN_DIR)/llbp

.PHONY: all clean

all: $(TARGET)

$(OBJECTS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	
$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET) $(OBJECTS)