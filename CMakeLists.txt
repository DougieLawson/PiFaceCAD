#
# Copyright (C) Dougie Lawson 2015-2017, all rights reserved.
#

cmake_minimum_required(VERSION 3.0)

project(PiFaceCAD)

add_executable(piface piface.c spiLcd.c commonLcd.c)

set_target_properties(piface PROPERTIES COMPILE_FLAGS -DSPI)
find_library(pthread_LIB pthread)
find_library(bcm2835_LIB bcm2835)

target_link_libraries(piface ${pthread_LIB} ${bcm2835_LIB})


