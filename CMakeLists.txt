# -------------------------------------------------------------------------
#  \file    Main Cmake Configuration
#  \author  Herbert Thielen
#  \brief   Main Cmake Configuration file of koelner-phonetik
# -------------------------------------------------------------------------
# A simple example of a catch2 cmake project generating a hello world application
# which prints the git version number.
# It includes unittest generation based on the Catch2 framework.
#
# Copyright 2012-2021 Herbert Thielen
#
# This file is part of the program 'koelner-phonetik',
# see https://gitlab.ai.it.hs-worms.de/swq/23s/koelner-phonetik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# See the cmake tutorial if you need some introduction:
# https://cmake.org/cmake/help/latest/guide/tutorial/index.html
# -------------------------------------------------------------------------

# Well, we tested it with cmake 3.18 on Debian 11 GNU/Linux, but probably
# we won't use very recent features here, so some older version should do
# the job too.
cmake_minimum_required(VERSION 2.8)

# The name of the project. Try 'cmake --help-command project' for details.
project(KataKoelnerPhonetik)

# Be verbose in build output (default: false)
#set (CMAKE_VERBOSE_MAKEFILE true)
# Alternatively, set it on the command line by executing e.g.
#   cd build
#   cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=True ..

# Setup output directories (see 'Mastering Cmake', page 119).
# Put all targets into one directory, not into subdirs (default).
set (LIBRARY_OUTPUT_PATH
  ${PROJECT_BINARY_DIR}
  CACHE PATH
  "Single directory for all libraries."
)
set (EXECUTABLE_OUTPUT_PATH
  ${PROJECT_BINARY_DIR}
  CACHE PATH
  "Single directory for all executables."
)
mark_as_advanced (
  LIBRARY_OUTPUT_PATH
  EXECUTABLE_OUTPUT_PATH
)

# see http://www.cmake.org/Wiki/CMake_Testing_With_CTest
# and 'cmake --help-command enable_testing' and ctest(1)
enable_testing()
add_test(NAME unit-test COMMAND unit-test)  # defined in src/unittest

# add more subdirectories here if necessary
add_subdirectory (src)

# These are just "collectors" of files which should be shown in QtCreator
# Nothing will be built directly out of these.
# Add more files if necessary.
set(buildScripts
    bin/create-buildtag
    bin/run-doxygen
    bin/run-tests
)
set(otherFiles
    README.md
    LICENSE
    .gitignore
    .gitlab-ci.yml
    doc/doxygen/Doxyfile
    doc/doxygen/license.dox
    doc/doxygen/mainpage.dox
    src/app-main/appmain.dox
    src/app-lib/applib.dox
    src/unittest/unittest.dox
)
add_custom_target(otherFiles
    COMMAND true
    COMMENT "pseudo target to collect supporting files"
    SOURCES ${buildScripts}
    SOURCES ${otherFiles}
)
