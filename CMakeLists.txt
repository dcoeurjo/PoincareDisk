#
# @file testPoincare.cpp
# @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
# Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
# 
# @date 2010/06/01
#


project( PoincareDisc ) 

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/")


FIND_PACKAGE(Cairo REQUIRED)
include_directories( ${CAIRO_INCLUDE_DIRS})
link_directories( ${CAIRO_LIBRARY_DIRS})

# -----------------------------------------------------------------------------
# Check and configure CMake packages
# -----------------------------------------------------------------------------
# Look for modules
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/")


SET(SRCs
  testPoincareDisk
 )

FOREACH(FILE ${SRCs})
  # The executable itself.
  add_executable  ( ${FILE} ${FILE} )
  target_link_libraries( ${FILE} cairo) 
ENDFOREACH(FILE)

