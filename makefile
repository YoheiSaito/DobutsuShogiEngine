# COMPILER  = clang++ -std=c++17 -Ofast
COMPILER  = clang++ -std=c++17 -g
CFLAGS    = -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers -mavx2 -fopenmp
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS = 
else
  LDFLAGS =
endif

BOOST_LIBS= -lboost_system -lboost_atomic -lboost_chrono -lboost_context\
			-lboost_coroutine -lboost_date_time -lboost_filesystem \
			-lboost_graph -lboost_graph_parallel -lboost_iostreams \
			-lboost_locale -lboost_log -lboost_log_setup -lboost_math_c99 \
			-lboost_math_c99f -lboost_math_c99l -lboost_math_tr1 \
			-lboost_math_tr1f -lboost_math_tr1l -lboost_mpi  \
			-lboost_prg_exec_monitor -lboost_program_options  -lboost_random\
			-lboost_regex -lboost_serialization -lboost_signals -lboost_system\
			-lboost_thread -lboost_timer -lboost_unit_test_framework \
			-lboost_wave -lboost_wserialization
LIBS      = $(BOOST_LIBS)
INCLUDE   = -I/usr/include\
			-I/usr/include/eigen3 \
			-I/home/saito/.linuxbrew/Cellar/eigen/3.3.7/include/eigen3
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
OBJECTS         = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	-mkdir -p bin
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp makefile
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)
run: $(TARGET)
	clear
	./bin/DobutsuShogiEngine ./test.ini

$(DEBUG_TARGET): $(DEBUG_OBJECTS) $(LIBS)
	-mkdir -p bin
	$(DEBUG_COMPILER) -o $@ $^ $(LDFLAGS)
debug: $(DEBUG_TARGET)
	lldb ./bin/DobutsuShogiEngine-debug  ./test.ini

-include $(DEPENDS)
