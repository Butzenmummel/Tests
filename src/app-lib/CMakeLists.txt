# -------------------------------------------------------------------------
#  app-lib library cmake configuration file of Catch2 cmake project.
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

set(libSrcs
    app-lib.h
    VersionInfo.h VersionInfo.cpp
    KoelnerPhonetik.h KoelnerPhonetik.cpp
)


add_library(app-lib STATIC ${libSrcs})

# Generate the version header file.
# The command in add_custom_target will be run at every build time
# to ensure the git version number in the header file is correct. If
# the header file content does not change, the script takes care to
# keep the modification date untouched, so no unnecessary compiler call
# will result from this.
set(generatedVersionInfoFile ${PROJECT_BINARY_DIR}/generated-version.h)
set(generatedVersionScript ${PROJECT_SOURCE_DIR}/bin/create-buildtag)
add_custom_target (gitVersion ALL
    # call bash explicitely, required on Windows
    bash ${generatedVersionScript} ${generatedVersionInfoFile}
    DEPENDS ${generatedVersionScript}
    SOURCES ${generatedVersionScript}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Running create-buildtag"
    VERBATIM
)
# Be sure the header file is generated before the compilation starts.
add_dependencies(app-lib gitVersion)

