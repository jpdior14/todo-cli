# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# NEW: Include path
# Tell the compiler to look for headers in the 'include' directory
CPPFLAGS = -Iinclude 

# Linker flags (will be needed later for libraries)
LDFLAGS = 

# Directories
SRCDIR = src
OBJDIR = obj

# Target executable
TARGET = todo

# Find all .cpp files in the source directory
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Generate object file names, placing them in the OBJDIR
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Default 'all' rule
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	@echo "LD	==> $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation rule (for objects in OBJDIR from SRCDIR)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@echo "CXX	==> $@"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Clean rule
clean:
	@echo "CLEAN==> Removing build artifacts"
	rm -rf $(OBJDIR) $(TARGET)
