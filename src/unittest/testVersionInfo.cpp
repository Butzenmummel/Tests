//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Test accessing the generated version information.
//============================================================================
/// \copyright  GNU General Public License (GPL) Version 3
//
// Copyright 2012-2021 Herbert Thielen
//
// This file is part of the program 'koelner-phonetik',
// see https://gitlab.ai.it.hs-worms.de/swq/23s/koelner-phonetik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//============================================================================

// Turn off clazy analysis annotations regarding TEST_CASEs.
// Seen in QtCreator 4.15.1 and 5.15.2, probably more.
// See https://github.com/KDE/clazy/blob/master/docs/man/clazy.pod
// clazy:excludeall=non-pod-global-static

#include "catch.hpp"
#include "app-lib/VersionInfo.h"
#include <iostream>
#include <cctype>
using namespace std;

namespace {     // local namespace, i.e. no function export
/// Check whether str has printable characters only (or is empty).
inline
bool isPrintable(const string &str)
{
    for(auto it : str) {
        if( ! isprint(it) )
            return false;
    }

    return true;
}
} // end of local namespace


/// \test VersionInfo::getVersion() returns a non-empty string
TEST_CASE("getVersionIsNotEmpty","[versioninfo]")
{
    // Arrange resp. Setup
    string retrievedVersion;

    // Act resp. Execute
    retrievedVersion = VersionInfo::getVersion();

    // give some output regardless of check result
    WARN( "Software version is " << retrievedVersion );

    // Assert resp. Verify
    CHECK_FALSE( retrievedVersion.empty() );

    // Teardown is automatically here (just delete local variable from stack)
}

/// \test VersionInfo::getVersion() returns a printable string
TEST_CASE("getVersionIsPrintable","[versioninfo]")
{
    // Arrange resp. Setup
    string retrievedVersion;

    // Act resp. Execute
    retrievedVersion = VersionInfo::getVersion();

    // Assert resp. Verify
    CAPTURE(retrievedVersion);     // output value in case CHECK fails
    CHECK( isPrintable(retrievedVersion) );

    // Teardown is automatically here (just delete local variable from stack)
}

/// \test VersionInfo::getBuildTag() returns a non-empty string
TEST_CASE("getBuildTagIsNotEmpty","[versioninfo]")
{
    // Arrange resp. Setup
    string retrievedBuildTag;

    // Act resp. Execute
    retrievedBuildTag = VersionInfo::getBuildTag();

    // give some output regardless of check result
    WARN( "Build Tag is " << retrievedBuildTag );

    // Assert resp. Verify
    CHECK_FALSE( retrievedBuildTag.empty() );

    // Teardown is automatically here (just delete local variable from stack)
}

/// \test VersionInfo::getBuildTag() returns a printable string
TEST_CASE("getBuildTagIsPrintable","[versioninfo]")
{
    // Arrange resp. Setup
    string retrievedBuildTag;

    // Act resp. Execute
    retrievedBuildTag = VersionInfo::getBuildTag();

    // Assert resp. Verify
    CAPTURE(retrievedBuildTag);     // output value in case CHECK fails
    CHECK( isPrintable(retrievedBuildTag) );

    // Teardown is automatically here (just delete local variable from stack)
}
