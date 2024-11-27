# -------------------------------------------------------------------------
#  src directory cmake configuration file of Catch2 cmake project.
# -------------------------------------------------------------------------
#  Copyright (C) 2017-2021 Herbert Thielen
# 
#  This file is part of "koelner-phonetik".
# 
#  koelner-phonetik is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  koelner-phonetik is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHACNTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with koelner-phonetik.  If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------------------------------

set( subdirs
    app-lib
    app-main
    unittest
)

# We use the QtCore library for QString.
# see also http://doc.qt.io/qt-5/cmake-manual.html
find_package(Qt5 COMPONENTS Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
message("Using Qt5Core at location ${QtCore_location}")
add_definitions(${Qt5Core_DEFINITIONS})
message("Qt5Core_DEFINITIONS=${Qt5Core_DEFINITIONS}")
add_compile_options(${Qt5Core_EXECUTABLE_COMPILE_FLAGS})

include_directories(
    # We add the current directory, i.e. the 'src' subdirectory, to the include directories,
    # so the compiler will find '#include "app-lib/app-lib.h"' when
    # 'app-lib' is a subdirectory of 'src'.
    ${CMAKE_CURRENT_SOURCE_DIR}
    # We also add the build directory to the include directories,
    # as some files (e.g. the version header file) may be generated there.
    ${PROJECT_BINARY_DIR}
    # Qt5Core includes are located here; variable is introduced by the Qt5 package
    ${Qt5Core_INCLUDE_DIRS}
)

# We insist to get the features of the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# additional compiler flags
if (CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(
        -Wall
        -Wextra
        -Werror
        -Wdeprecated
        -pedantic
        # -Weffc++  # incompatible with Qt 5.15.2!
        -fPIC       # required for Qt
    )
    # Overwrite default debug compiler switch, which is only "-g".
    # See 'info gcc' for details on the options.
    # -g3 generates maximal debug information
    # -Og "should be the optimization level of choice for the standard
    #      edit-compile-debug cycle, offering a reasonable level of optimization
    #      while maintaining fast compilation and a good debugging experience.
    #      It is a better choice than '-O0' for producing deubggable code
    #      because some compiler passes that collect debug information are
    #      disabled at '-O0'." (citation from GCC manual 'info gcc')
    # -fno-inline be sure to suppress inlining
    # --coverage is required for gcov
    # For libstdc++ debug support enabled by -D_GLIBCXX_DEBUG, see
    # https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode.html or
    # /usr/share/doc/gcc-10-base/libstdc++/manual/debug_mode.html
    # (if e.g. on Debian 11 GNU/Linux, libstdc++-10-doc is installed).
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Og -fno-inline --coverage -D_GLIBCXX_DEBUG"
        CACHE STRING "Flags used by the compiler during debug builds."
        FORCE
    )
endif (CMAKE_COMPILER_IS_GNUCC)

foreach( dir ${subdirs} )
    add_subdirectory (${dir})
endforeach()

message("Configured compilation flags:")
message("CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO=${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
