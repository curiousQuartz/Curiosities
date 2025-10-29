# ...existing code...
CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -pedantic -O2 -DGL_SILENCE_DEPRECATION

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDLIBS += -framework OpenGL -framework GLUT
else
	LDLIBS += -lGL -lGLU -lglut
endif

OBJS := main.o GamePlay.o ShapeShifter.o Door.o SpecialTiles.o
TARGET := shapeshifter

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
# ...existing code...