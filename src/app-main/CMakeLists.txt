# -------------------------------------------------------------------------
#  \file    src Cmake Configuration
#  \author  Herbert Thielen
#  \brief   Cmake build configuration of app-main
# -------------------------------------------------------------------------
# A simple example of a catch2 cmake project generating a hello world application
# which prints the git version number.
#
# Copyright 2012-2023 Herbert Thielen
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
# -------------------------------------------------------------------------

set(appSrcs
    app-main.cpp
)

set(appLibs
    app-lib
    ${Qt5Core_LIBRARIES}
)

add_executable(demo-koelner-phonetik ${appSrcs})

target_link_libraries(demo-koelner-phonetik ${appLibs})
