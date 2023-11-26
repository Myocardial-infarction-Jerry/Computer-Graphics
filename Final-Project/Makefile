CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -g

SRCDIR = src
INCDIR = includes
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/main

.PHONY: all clean run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE) > image.ppm
	sips -s format png image.ppm --out image.png

clean:
	rm -rf $(OBJDIR) $(BINDIR)