COMPILER  = clang++ -std=c++17
CFLAGS    = -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers -Ofast -mavx2 -fopenmp
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS = 
else
  LDFLAGS =
endif

LIBS      = -lboost_system -lboost_atomic -lboost_chrono -lboost_context -lboost_coroutine -lboost_date_time -lboost_filesystem -lboost_graph -lboost_graph_parallel -lboost_iostreams -lboost_locale -lboost_log -lboost_log_setup -lboost_math_c99 -lboost_math_c99f -lboost_math_c99l -lboost_math_tr1 -lboost_math_tr1f -lboost_math_tr1l -lboost_mpi  -lboost_prg_exec_monitor -lboost_program_options  -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_timer -lboost_unit_test_framework -lboost_wave -lboost_wserialization
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
