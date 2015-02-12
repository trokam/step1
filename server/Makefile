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

CPPFLAGS=-c -Wall -I./include -I../common/include -Wcpp 

LDFLAGS=-g

LDLIBS= -lboost_program_options \
        -lboost_random \
        -lboost_regex \
        -lboost_signals \
        -lboost_system \
        -lboost_thread \
        -lcurl \
        -lfcgi \
        -ljsoncpp \
        -lpqxx \
        -lwt \
        -lwtfcgi

BIN=./bin
COMMON_DIR=../common/src
INSTALL_USER_BIN_DIR=/usr/local/bin/
INSTALL_SERVER_BIN_DIR=/usr/local/bin/trokam/server

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# action
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SOURCES_ACTION= src/main_action.cpp \
				src/action_processor.cpp \
                src/db_handler.cpp \
                src/options.cpp \
                src/postgresql.cpp \
                src/server_log.cpp \
                $(COMMON_DIR)/converter.cpp \
                $(COMMON_DIR)/file_management.cpp \
                $(COMMON_DIR)/machine.cpp \
                $(COMMON_DIR)/random.cpp \
                $(COMMON_DIR)/token.cpp

OBJECTS_ACTION=$(SOURCES_ACTION:.cpp=.o)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# search
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SOURCES_SEARCH= src/main_search.cpp \
				src/db_handler.cpp \
                src/options.cpp \
                src/page_search.cpp \
                src/postgresql.cpp \
                src/render.cpp \
                src/shared_search.cpp \
                src/server_log.cpp \
                $(COMMON_DIR)/converter.cpp \
                $(COMMON_DIR)/file_management.cpp \
                $(COMMON_DIR)/machine.cpp \
                $(COMMON_DIR)/random.cpp \
                $(COMMON_DIR)/token.cpp

OBJECTS_SEARCH=$(SOURCES_SEARCH:.cpp=.o)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# initialize
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SOURCES_INITIALIZE= src/main_initialize.cpp \
					src/db_handler.cpp \
                    src/options.cpp \
                    src/postgresql.cpp \
                    $(COMMON_DIR)/converter.cpp \
                    $(COMMON_DIR)/desk_log.cpp \
                    $(COMMON_DIR)/file_management.cpp \
                    $(COMMON_DIR)/machine.cpp \
                    $(COMMON_DIR)/random.cpp \
                    $(COMMON_DIR)/token.cpp

OBJECTS_INITIALIZE=$(SOURCES_INITIALIZE:.cpp=.o)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# targets
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

all: server

server: action search initialize

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# individual recipes
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

action: $(OBJECTS_ACTION)
	$(CC) $(LDFLAGS) $(OBJECTS_ACTION) -o $(BIN)/$@ $(LDLIBS) 

search: $(OBJECTS_SEARCH)
	$(CC) $(LDFLAGS) $(OBJECTS_SEARCH) -o $(BIN)/$@ $(LDLIBS)

initialize: $(OBJECTS_INITIALIZE)
	$(CC) $(LDFLAGS) $(OBJECTS_INITIALIZE) -o $(BIN)/$@ $(LDLIBS)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# These are the list of files and the automatically
# generated dependencies to build them
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
	sudo mkdir -p $(INSTALL_SERVER_BIN_DIR)
	sudo cp ./bin/action $(INSTALL_SERVER_BIN_DIR)
	sudo cp ./bin/search $(INSTALL_SERVER_BIN_DIR)
	sudo mkdir -p $(INSTALL_USER_BIN_DIR)
	sudo cp ./bin/initialize $(INSTALL_USER_BIN_DIR)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY : clean
clean :
	-rm -f bin/*
	-rm -f src/*.o
	-rm -f $(COMMON_DIR)/*.o
