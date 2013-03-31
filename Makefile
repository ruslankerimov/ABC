#****************************************************************************
# Debug and Profile
#****************************************************************************

DEBUG            := NO
PROFILE          := NO

#****************************************************************************

CC               := gcc
CXX              := g++
LD               := g++
AR               := ar rc
RANLIB           := ranlib

DEBUG_CFLAGS     := -Wall -Wno-format -g -DDEBUG
RELEASE_CFLAGS   := -Wall -Wno-unknown-pragmas -Wno-format -O3

#-L
LIBS             :=

DEBUG_CXXFLAGS   := $(DEBUG_CFLAGS) 
RELEASE_CXXFLAGS := $(RELEASE_CFLAGS)

DEBUG_LDFLAGS    := -g
RELEASE_LDFLAGS  :=

ifeq (YES, $(DEBUG))
   CFLAGS        := $(DEBUG_CFLAGS)
   CXXFLAGS      := $(DEBUG_CXXFLAGS)
   LDFLAGS       := $(DEBUG_LDFLAGS)
else
   CFLAGS        := $(RELEASE_CFLAGS)
   CXXFLAGS      := $(RELEASE_CXXFLAGS)
   LDFLAGS       := $(RELEASE_LDFLAGS)
endif

ifeq (YES, $(PROFILE))
   CFLAGS        := $(CFLAGS) -pg -O3
   CXXFLAGS      := $(CXXFLAGS) -pg -O3
   LDFLAGS       := $(LDFLAGS) -pg
endif

#****************************************************************************
# Preprocessor directives
#****************************************************************************

#-DTIXML_USE_STL
DEFS     :=

#****************************************************************************
# Include paths
#****************************************************************************

#-Isrc
INCS     :=
#-llibs
EXTRA_LIBS :=

#****************************************************************************
# Makefile code common to all platforms
#****************************************************************************

CFLAGS   := $(CFLAGS)   $(DEFS)
CXXFLAGS := $(CXXFLAGS) $(DEFS)

#****************************************************************************
# Source files
#****************************************************************************

SRC_DIR         := src/
EXAMPLES_DIR    := examples/
SRCS            := $(wildcard $(SRC_DIR)*.cpp) $(wildcard $(EXAMPLES_DIR)*.cpp)
OBJS            := $(patsubst %.cpp, %.o, $(SRCS))

#****************************************************************************
# Targets of the build
#****************************************************************************
 
OUTPUT := $(patsubst %.cpp, %, $(wildcard $(EXAMPLES_DIR)*.cpp))
all: $(OUTPUT)

#****************************************************************************
# Output
#****************************************************************************

$(OUTPUT): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) $(EXTRA_LIBS)

#****************************************************************************
# Common rules
#****************************************************************************

# Rules for compiling source files to object files
# For C++
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCS) $< -o $@

# For C
%.o : %.c
	$(CC) -c $(CFLAGS) $(INCS) $< -o $@

# Clean all compiled files
clean:
	-rm -f $(OBJS) $(OUTPUT)

#****************************************************************************
# Dependencies
#****************************************************************************

$(OUTPUT): $(SRC_DIR)ABC.h
$(SRC_DIR)ABC.h: $(SRC_DIR)ABCconfig.h