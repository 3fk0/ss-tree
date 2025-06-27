# SS-Tree Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
LDFLAGS = 

# Directories
SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = .

# Target executable
TARGET = $(BINDIR)/ss-tree

# Source files
SOURCES = main.cpp \
          $(SRCDIR)/SStree.cpp \
          $(SRCDIR)/input/input_control.cpp \
          $(SRCDIR)/operations_wrapper/wrapper.cpp \
          $(SRCDIR)/parser/csv_parser.cpp

# Object files
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Include directories
INCLUDES = -I$(INCDIR) -I$(SRCDIR)

# Default target
all: $(TARGET)

# Create target executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files to object files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create directories
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)/input
	mkdir -p $(OBJDIR)/$(SRCDIR)/operations_wrapper
	mkdir -p $(OBJDIR)/$(SRCDIR)/parser

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean build artifacts
clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)

# Rebuild everything
rebuild: clean all

# Install target (if needed)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall target
uninstall:
	rm -f /usr/local/bin/ss-tree

# Debug build
debug: CXXFLAGS += -DDEBUG -g -O0
debug: $(TARGET)

# Release build
release: CXXFLAGS += -DNDEBUG -O3
release: $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the ss-tree executable (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and build"
	@echo "  debug    - Build with debug flags"
	@echo "  release  - Build with optimizations"
	@echo "  run      - Build and run the program"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove from /usr/local/bin"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all clean rebuild install uninstall debug release run help

# Dependency tracking
-include $(OBJECTS:.o=.d)

# Generate dependency files
$(OBJDIR)/%.d: %.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MT $(@:.d=.o) $< > $@