//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Some tests to explore Catch2 test object generation.
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
using std::string;
#include <iterator>
using std::begin, std::end;
#include <initializer_list>
using std::initializer_list;
#include <vector>
using std::vector;

/// A test case to demonstrate the Catch2 test function behaviour.
/// By studying the outputs, you can verify that attributes are not shared
/// between the different test cases sections, i.e. there is a new function
/// call for every execution of a test section.
/// That means, one test section doesn't have side effects to another test
/// section.

TEST_CASE("Test Catch2 Behaviour", "[catch2]")
{
    // This setup part is run for every section again.
    int objectCount = 0;
    static int objectNumber = 0;
    int someAttributeWhichIsUsedInTestCases = 0;

    REQUIRE(objectCount == 0);

    ++ objectNumber;

    /// \test Our first test case section which modifies an attribute.
    SECTION("firstTestCaseSection") {
        CHECK(someAttributeWhichIsUsedInTestCases == 0);
        someAttributeWhichIsUsedInTestCases=1;
        CHECK(someAttributeWhichIsUsedInTestCases == 1);
        CHECK(objectNumber == 1);
    }

    /// \test Our second test case section which gets a modified attribute.
    /// See firstTestCaseSection which doesn't have side effects on us!
    SECTION("secondTestCaseSection") {
        CHECK(someAttributeWhichIsUsedInTestCases == 0);
        someAttributeWhichIsUsedInTestCases=2;
        CHECK(someAttributeWhichIsUsedInTestCases == 2);
        CHECK(objectNumber == 2);
    }

    // This teardown part is run for every section again.

    // CHECK(someAttributeWhichIsUsedInTestCases == 1); // will fail for secondTestCaseSection

    someAttributeWhichIsUsedInTestCases=99;
    CHECK(someAttributeWhichIsUsedInTestCases == 99);

    ++objectCount;
    CHECK(objectCount == 1);
}

/// A test case to demonstrate some of Catch2's data driven test features.
/// See https://gitlab.ai.it.hs-worms.de/swq/frameworks/Catch2/-/blob/main/docs/generators.md
TEST_CASE("try using generator", "[catch2]")
{
    // See https://gitlab.ai.it.hs-worms.de/swq/frameworks/Catch2/-/blob/main/examples/302-Gen-Table.cpp
    SECTION("using table()") {
        // For the C++ syntax on the left of the assignment, see
        // https://en.cppreference.com/w/cpp/language/structured_binding
        auto [data, expected] = GENERATE(
                table<string, size_t> ( {
                                          { "abc", 3 },
                                          { "defg", 4 },
                                          { "hi", 2 }
                                        } )
        );

        CAPTURE(data);

        //    CHECK(data.size() == expected+1); // try to see it failing :-)
        CHECK(data.size() == expected);
    }

    SECTION("using from_range()") {
        struct TestData {
                string data;
                size_t expected;
        };
        TestData const testValues[] = {
            { "abc", 3 },
            { "defg", 4 },
            { "hi", 2 }
        };

        TestData testValue = GENERATE_REF( from_range( begin(testValues),
                                                   end(testValues) )
                                       );

        CAPTURE(testValue.data);

        // CHECK(testValue.data.size() == testValue.expected+1); // try to see it failing :-)
        CHECK(testValue.data.size() == testValue.expected);
    }

    SECTION("using from_range() with vector") {
        struct TestData {
                string data;
                size_t expected;
        };
        vector<TestData> const testValues = {
            { "abc", 3 },
            { "defg", 4 },
            { "hi", 2 }
        };

        auto [data, expected] = GENERATE_REF( from_range(testValues) );

        CAPTURE(data);

        // CHECK(data.size() == expected+1); // try to see it failing :-)
        CHECK(data.size() == expected);
    }

    SECTION("using values()") {
        struct TestData {
                string data;
                size_t expected;
        };

        TestData testValue = GENERATE( values( {
                                                   TestData( { "abc", 3 } ),
                                                   TestData( { "defg", 4} )
                                               }
                                             )
                                     );

        CAPTURE(testValue.data);

        // CHECK(testValue.data.size() == testValue.expected+1); // try to see it failing :-)
        CHECK(testValue.data.size() == testValue.expected);
    }

    SECTION("using values() with initializer_list") {
        struct TestData {
                string data;
                size_t expected;
        };

        auto [data, expected] = GENERATE( values( initializer_list<TestData> {
                                                    { "abc", 3 },
                                                    { "defg", 4}
                                                  }
                                                )
                                        );

        CAPTURE(data);

        // CHECK(data.size() == expected+1); // try to see it failing :-)
        CHECK(data.size() == expected);
    }
}
