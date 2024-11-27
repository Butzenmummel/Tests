# -------------------------------------------------------------------------
#  Unit test cmake configuration file of koelner-phonetik.
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

set(testSrcs
    catch.hpp
    testmain.cpp
    testHelper.h

    testCatch2Behaviour.cpp
    testStringCompares.cpp
    testVersionInfo.cpp
    testKoelnerPhonetik.cpp

    aufgabe.cpp
)

set(testLibs
    app-lib
    ${Qt5Core_LIBRARIES}
)

add_executable(unit-test ${testSrcs})

target_link_libraries(unit-test ${testLibs})
