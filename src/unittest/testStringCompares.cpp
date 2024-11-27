//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Some tests to explore comparisons of std:string objects.
/// 		    It's meant that you modify the tests to fail for studying the test outputs.
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
#include <string>
#include <sstream>
using namespace std;

/// \test Test comparison between std::string and C string.
TEST_CASE("stringComparesToCharArray", "[catch2]") {
    /// Check the behaviour by changing the expected string so that
    /// the test fails. It should show readable output for the actual
    /// and expected strings.
    char const * const expected = "Foo Bar Baz";
    string const myString = "Foo Bar Baz";

    CHECK(myString == expected);
}

/// \test Test comparison between std::string objects.
TEST_CASE("stringComparesToString", "[catch2]") {
    /// Check the behaviour by changing the expected string so that
    /// the test fails. It should show readable output for the actual
    /// and expected strings.
    string const expected = "Foo Bar Baz";
    string const myString = "Foo Bar Baz";

    CHECK(myString == expected);
}

/// \test Test comparison between std::ostringstream and C string.
TEST_CASE("ostringstreamComparesToCharArray", "[catch2]") {
    /// Check the behaviour by changing the expected string so that
    /// the test fails. It should show readable output for the actual
    /// and expected strings.
    char const * const expected = "Foo Bar Baz";
    ostringstream output;
    output << "Foo Bar Baz";

    CHECK(output.str() == expected);
}

/// \test Test comparison between std::ostringstream and std::string.
TEST_CASE("ostringstreamComparesToString", "[catch2]") {
    /// Check the behaviour by changing the expected string so that
    /// the test fails. It should show readable output for the actual
    /// and expected strings.
    string const expected = "Foo Bar Baz";
    ostringstream output;
    output << "Foo Bar Baz";

    CHECK(output.str() == expected);
}

/// \test Test comparison between two std::ostringstream objects.
TEST_CASE("ostringstreamComparesToOstringstream", "[catch2]") {
    /// Check the behaviour by changing the expected string so that
    /// the test fails. It should show readable output for the actual
    /// and expected strings.
    ostringstream const expected("Foo Bar Baz");
    ostringstream output;
    output << "Foo Bar Baz";

    CHECK(output.str() == expected.str());
    // CHECK(output == expected);  // doesn't compile: no operator==()!
}




/// \test Test comparison of bool.
TEST_CASE("booleanDifferenceIsPrinted", "[catch2]") {
    bool t = false;  // change to different values to see output of failing CHECK
    bool f = false;
    CHECK(t == f);
}
