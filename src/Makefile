#==================================================
# Makefile version: 1.0
# Setting time: 2013/04/30
#==================================================
.PHONY : clean run
#ver=debug

#==================================================
# Platform Detect MACRO
#==================================================
OSUPPER = $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
OSLOWER = $(shell uname -s 2>/dev/null | tr [:upper:] [:lower:])

#Flags to detect 32-bit or 64-bit OS platform
OS_SIZE = $(shell uname -m | sed -e "s/i.86/32/" -e "s/x86_64/64/")
OS_ARCH = $(shell uname -m | sed -e "s/i386/i686/")

# These flags will override any settings
ifeq ($(i386),1)
	OS_SIZE = 32
	OS_ARCH = i686
endif
ifeq ($(x86_64),1)
	OS_SIZE = 64
	OS_ARCH = x86_64
endif

ifeq ($(OS_SIZE), 32)
	mflags = -m32
else
	mflags = -m64
endif

#==================================================
# Command Define
#==================================================
CC            = gcc
CXX           = g++
PRE_PROCESSOR = ${CXX}
LINKER        = ${CXX}
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
DEL_FILE      = rm -f
DEL_DIR       = rm -rf
MKDIR         = mkdir -p
MOVE          = mv -u
ARG           = 
STDIN         = 
SHELL         = /bin/sh

#==================================================
# Flag Define -- build version dependant
#==================================================
ifeq ($(ver),debug)
	CFLAGS   = -g3 -Wall -Ddebug -pthread ${DEFINES} 
	CXXFLAGS = -g3 -Wall -Ddebug ${DEFINES} 
else
	CFLAGS   = -O3 -Wall -pthread ${DEFINES} 
	CXXFLAGS = -O3 -Wall ${DEFINES} 
endif
LIBS     = -L. -lncurses -pthread $(QT_LIBS)
INCLUDE  = -I. -I/usr/share/qt4/mkspecs/linux-g++-64 -I/usr/include/qt/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -fPIC

#==================================================
# Source, library, bin Define
#==================================================
TARGET = minesweeper
BIN_DIR     = bin
LIBRARY_DIR = library
SOURCE_FILE = main.cpp mainwindow.cpp minesweeper.cpp qlandbutton.cpp $(QT_MOCSOURCE) $(QT_RCCSOURCE)
OBJECT_FILE += $(addsuffix .o, $(basename $(SOURCE_FILE)))

#==================================================
# Qt restrict
#==================================================
QT_LIBS  = -lQtCore -lQtGui -lQtOpenGL
QT_PATH = /usr/lib/qt4/bin/
QT_MOCFILE = mainwindow.h qlandbutton.h
QT_RCCFILE = minesweeper.qrc
QT_UICFILE = 
QT_MOCSOURCE = $(addprefix moc_, $(addsuffix .cpp, $(basename $(QT_MOCFILE))))
QT_RCCSOURCE = $(addprefix qrc_, $(addsuffix .cpp, $(basename $(QT_RCCFILE))))
QT_UICSOURCE = $(addprefix ui_,  $(addsuffix .h,   $(basename $(QT_UICFILE))))

#==================================================
# Compile implicit rules, and Qt rules
#==================================================

%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR)

%.o:%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR)

moc_%.cpp: %.h
	$(QT_PATH)moc-qt4 $(DEFINES) $(INCLUDE) $< -o $@

qrc_%.cpp: %.qrc
	$(QT_PATH)rcc-qt4 $< -o $@

ui_%.h: %.ui
	$(QT_PATH)uic-qt4 $< -o $@

#==================================================
# Compile rules
#==================================================

default: new_dir $(TARGET)

new_dir:
	$(MKDIR) $(LIBRARY_DIR) $(BIN_DIR)

$(TARGET): $(OBJECT_FILE)
	cd $(LIBRARY_DIR); \
	$(LINKER) -o $@ $(OBJECT_FILE) $(LIBS); \
	cd ..
	mv $(LIBRARY_DIR)/$@ $(BIN_DIR)

run: 
	./$(BIN_DIR)/$(TARGET) $(ARG)

clean: 
	$(DEL_FILE) $(QT_MOCSOURCE) $(QT_RCCSOURCE) $(QT_UICSOURCE)
	$(DEL_FILE) $(LIBRARY_DIR)/*.o
	$(DEL_FILE) $(BIN_DIR)/$(TARGET)

clean_all: 
	${DEL_DIR} ${LIBRARY_DIR} ${BIN_DIR} 
