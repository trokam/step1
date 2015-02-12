# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#                            T R O K A M
#                  Free and Open Source Search Engine
#
#  Service        http://trokam.com/search
#  About          http://trokam.com/pages/about
#  Development    http://dev.trokam.com/
#  Repository     https://github.com/trokam
#  News           https://twitter.com/trokam
#
#  Copyright (C) 2015, Nicolas Slusarenko
#                      nicolas.slusarenko@trokam.com
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CC=g++

CPPFLAGS=-c -Wall -I./include -I../common/include

LDFLAGS=-g

LDLIBS=-lboost_system \
       -lboost_random \
       -lboost_regex \
       -lboost_program_options \
       -lcurl \
       -lexttextcat \
       -lmagic \
       -ljsoncpp \

BIN=./bin
COMMON_DIR=../common/src
INSTALL_BIN_DIR=/usr/local/bin
INSTALL_CONFIG_DIR=/usr/local/etc/trokam

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# cruncher
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SOURCES_CRUNCHER= src/main_cruncher.cpp \
                  src/action_handler.cpp \
                  src/file_converter.cpp \
                  src/html_handler.cpp \
                  src/language.cpp \
                  src/options.cpp \
                  src/sort.cpp \
                  src/text_processor.cpp \
                  src/url_processor.cpp \
                  src/web_cruncher.cpp \
                  src/web_handler.cpp \
                  src/word_stats.cpp \
                  $(COMMON_DIR)/converter.cpp \
                  $(COMMON_DIR)/file_management.cpp \
                  $(COMMON_DIR)/desk_log.cpp \
                  $(COMMON_DIR)/machine.cpp \
                  $(COMMON_DIR)/random.cpp \
                  $(COMMON_DIR)/token.cpp

OBJECTS_CRUNCHER=$(SOURCES_CRUNCHER:.cpp=.o)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# targets
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

all: cruncher

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# individual recipes
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

cruncher: $(OBJECTS_CRUNCHER)
	$(CC) $(LDFLAGS) $(OBJECTS_CRUNCHER) -o $(BIN)/$@ $(LDLIBS)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# These are the list of files and the automatically
# generated rules to build them
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DEPENDENCIES= $(OBJECTS:.o=.d)

include $(DEPENDENCIES:.cpp=.d)

%.d: %.cpp
		@set -e; rm -f $@; \
		$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY : install
install :
	sudo mkdir -p $(INSTALL_CONFIG_DIR)
	sudo cp ./config/*.cfg $(INSTALL_CONFIG_DIR)
	sudo cp ./bin/cruncher $(INSTALL_BIN_DIR)
	sudo cp ./src/loop_cruncher $(INSTALL_BIN_DIR)
	sudo chmod a+x $(INSTALL_BIN_DIR)/loop_cruncher
	sudo cp ./config/fpdb.conf /usr/share/libexttextcat/

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY : clean
clean :
	-rm -f bin/*
	-rm -f src/*.o
	-rm -f $(COMMON_DIR)/*.o
