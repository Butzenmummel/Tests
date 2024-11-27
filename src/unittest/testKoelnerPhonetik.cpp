//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Test accessing the KoelnerPhonetik library.
//============================================================================
/// \copyright  GNU General Public License (GPL) Version 3
//
// Copyright 2023 SWQ students team and Herbert Thielen
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

#include "testHelper.h"
#include "app-lib/KoelnerPhonetik.h"
#include "app-lib/KoelnerPhonetik.h"

using namespace std;

/// Helper functions in anonymous (local) namespace
namespace {
    void tolower( QString & s ) {
        s = s.toLower();
    }

    void toupper( QString & s ) {
        s = s.toUpper();
    }
}


/// \test tolower/toupper works for German umlauts
TEST_CASE("Test conversion of german Umlauts")
{
    QString upperUmlauts = "ABC_ÄÖÜ";
    QString lowerUmlauts = "abc_äöü";

    SECTION("test tolower") {
        tolower(upperUmlauts);
    }

    SECTION("test toupper") {
        toupper(lowerUmlauts);
    }

    CHECK(upperUmlauts == lowerUmlauts);
}

/// \test class KoelnerPhonetik for minimal strings without context.
/// See table in https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Buchstabencodes
TEST_CASE("KoelnerPhonetik::code() for minimal strings without context","[koelner]")
{
    auto [input, expected] = GENERATE(
            table<QString, QString> ( {
        { "a", "0" },
        { "e", "0" },
        { "i", "0" },
        { "j", "0" },
        { "o", "0" },
        { "u", "0" },
        { "y", "0" },
        { "ä", "0" },
        { "ö", "0" },
        { "ü", "0" },
        { "h", ""  },
        { "b", "1" },
        { "f", "3" },
        { "v", "3" },
        { "w", "3" },
        { "g", "4" },
        { "k", "4" },
        { "q", "4" },
        { "l", "5" },
        { "m", "6" },
        { "n", "6" },
        { "r", "7" },
        { "s", "8" },
        { "ß", "8" },
        { "z", "8" },
    } )
    );

    SECTION("lowercase") {
        tolower(input);
    }

    SECTION("uppercase") {
        toupper(input);
    }

    QString output = KoelnerPhonetik::code(input);

    CAPTURE(input);
    CHECK(output == expected);
}

/// \test class KoelnerPhonetik for minimal strings with context.
/// See table in https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Buchstabencodes
/// TODO Add test case(s) regarding the "außer nach" and "außer vor" lines of the
/// wikipedia table.
TEST_CASE("KoelnerPhonetik::code() for minimal strings with context","[koelner]")
{
    auto [input, expected] = GENERATE(
            table<QString, QString> ( {
        { "p", "1" },   // nicht vor H
        { "d", "2" },   // nicht vor C, S, Z
        { "t", "2" },   // nicht vor C, S, Z
        { "ph", "3" },  // vor H
        { "ca", "4" },  // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "ch", "4" },  // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "ck", "4" },  // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "cl", "45" }, // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "co", "4" },  // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "cq", "4" },  // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "cr", "47" }, // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "cu", "4" },  // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "cx", "48" }, // im Anlaut vor A, H, K, L, O, Q, R, U, X
        { "x", "48" },  // nicht nach C, K, Q
        { "c", "8" },   // im Anlaut außer vor A, H, K, L, O, Q, R, U, X
        { "dc", "8" },  // vor C, S, Z
        { "ds", "8" },  // vor C, S, Z
        { "dz", "8" },  // vor C, S, Z
        { "tc", "8" },  // vor C, S, Z
        { "ts", "8" },  // vor C, S, Z
        { "tz", "8" },  // vor C, S, Z
        { "cx", "48" }, // X nach C, K, Q
        { "kx", "48" }, // X nach C, K, Q
        { "qx", "48" }, // X nach C, K, Q
    } )
    );

    SECTION("lowercase") {
        tolower(input);
    }

    SECTION("uppercase") {
        toupper(input);
    }

    QString output = KoelnerPhonetik::code(input);

    CAPTURE(input);
    CHECK(output == expected);
}

/// \test class KoelnerPhonetik for Wikipedia Example Wikipedia.
/// See example below table in https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Beispiel
TEST_CASE("KoelnerPhonetik::code() for Wikipedia example Wikipedia","[koelner]")
{
    CHECK( KoelnerPhonetik::code("Wikipedia") == "3412" );
}

/// \test class KoelnerPhonetik for Wikipedia Example Breschnew.
/// See example below table in https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Buchstabencodes
TEST_CASE("KoelnerPhonetik::code() for Wikipedia example Breschnew","[koelner]")
{
    CHECK( KoelnerPhonetik::code("Breschnew") == "17863" );
}

/// \test class KoelnerPhonetik for Wikipedia Example Müller-Lüdenscheidt.
/// See example in https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Beispiel
TEST_CASE("KoelnerPhonetik::code() for Wikipedia example Müller-Lüdenscheidt","[koelner]")
{
    CHECK( KoelnerPhonetik::code("Müller-Lüdenscheidt") == "65752682" );
}

/// \test class KoelnerPhonetik for Wikipedia Example Heinz Classen.
/// See example in https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Beispiel
TEST_CASE("KoelnerPhonetik::code() for Wikipedia example Heinz Classen","[koelner]")
{
    CHECK( KoelnerPhonetik::code("Heinz Classen") == "068 4586" );
}


/// \test code with the conversion from QString into String.
TEST_CASE("KoelnerPhonetik::code() for the Conversion from QString into String","[koelner]")
{
    CHECK( KoelnerPhonetik::code("Breschnew"s) == "17863"s );
}


/// \test class KoelnerPhonetik for examples in original paper by Hans Joachim Postel.
TEST_CASE("KoelnerPhonetik::code() for examples in paper by H. J. Postel","[koelner]")
{
    auto [input, expected] = GENERATE(
            table<QString, QString> ( {
        { "AAHOEH", "0" },
        { "AHU", "0" },
        { "ARTEL", "0725" },
        { "ARDELE", "0725" },

        { "BOUDELAIR", "1257" },
        { "BAUDLAIRE", "1257" },
        { "PUTLER", "1257" },
        { "BUTTLER", "1257" },

        { "HAMRIN", "0676" },
        { "HANRIN", "0676" },

        { "MUELLER", "657" },
        { "MILLER", "657" },
        { "MOELLER", "657" },
        { "MOLIERE", "657" },
        { "MALHEUR", "657" },
        { "NIEHLER", "657" },

        { "MADLER", "6257" },
        { "NADLER", "6257" },

        { "BRESCHNEW", "17863" },
        { "BREZNEV", "17863" },
        { "BRESHMOW", "17863" },
        { "PRECZNEFF", "17863" },

        { "HRADSCHIN", "786" },
        { "RADZIN", "786" },
        { "RETSIEM", "786" },

        { "CHRUSCHZOW", "4783" },
        { "CRESZEW", "4783" },
        { "KHRECZUV", "4783" },

        { "MARX", "6748" },
        { "MURKS", "6748" },
        { "MIRCKX", "6748" },
        { "MIRCX", "6748" },

        { "Ritter", "727" },
        { "Popow", "113" },
    } )
    );

    QString output = KoelnerPhonetik::code(input);

    CAPTURE(input);
    CHECK(output == expected);
}

TEST_CASE("Beispiel für analyse()")
{
    KoelnerPhonetik::WordListAnalyzer a;
    ostringstream output;
    string inputLine = "hallo";
    istringstream input (inputLine);

    CAPTURE(inputLine);

    a.analyse(input);
    a.printResults(output);

    QString result = QString::fromStdString(output.str());

    CAPTURE(result);
    CHECK(result.contains("05 (1): hallo"));
    CHECK(a.getMaxFrequencyOfAnyCode() == 1);
}

TEST_CASE("CodeToWord map is initially empty")
{
    KoelnerPhonetik::WordListAnalyzer a;

    auto codeToWordMap = a.getCodeToWord(); // some std::multimap

    CHECK( codeToWordMap.empty() );
}
