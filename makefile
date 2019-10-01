COMPILER  = clang++ -std=c++17
CFLAGS    = -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers -Ofast -mavx2 -fopenmp
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS = 
else
  LDFLAGS =
endif
LIBS      =
INCLUDE   = -I/home/saito/.linuxbrew/Cellar/eigen/3.3.7/include/eigen3 -I/usr/include
TARGET    = ./bin/$(shell basename `readlink -f .`)
SRCDIR    = ./src
ifeq "$(strip $(SRCDIR))" ""
  SRCDIR  = .
endif
SOURCES   = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR    = ./obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR  = .
endif
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp makefile
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
