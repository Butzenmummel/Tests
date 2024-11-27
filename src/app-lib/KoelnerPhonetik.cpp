//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      Contains the KoelnerPhonetik implementation parts.
//============================================================================
/// \copyright  GNU General Public License (GPL) Version 3
//
// Copyright 2012-2023 Herbert Thielen and SWQ team
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

#include "KoelnerPhonetik.h"
#include <algorithm>

using namespace std;

namespace {
    /// Predicate is the type of a pointer to a function returning bool.
    using Predicate = bool (*) (QString const & s, int index, QString const & context);

    struct CodeCondition {
            Predicate const predicate;
            QString const context;
            QString const code;
    };

    bool always (QString const &, int, QString const &) {
        return true;
    }

    Predicate const otherwise { always };

    bool before (QString const & input, int index, QString const & context) {
        ++index;                        // following character is of interest
        if( index >= input.length() )   // no following character
            return false;
        return context.contains(input[index]);
    }

    bool notBefore (QString const & input, int index, QString const & context) {
        return not before(input, index, context);
    }

    bool anlautBefore(QString const & input, int index, QString const & context) {
        if( index > 0  &&
            input[index-1] != ' ' ) {
            // it's an anlaut only at the beginning or after a space
            return false;
        }

        return before(input, index, context);
    }

    bool after(QString const & input, int index, QString const & context) {
        if( index == 0 )   // no previous character
            return false;
        --index;                        // previous character is of interest
        return context.contains(input[index]);
    }

    bool notAfter(QString const & input, int index, QString const & context) {
        return not after(input, index, context);
    }

    /// Add a code to the result QString according to the Kölner Phonetik rules.
    /// See rules below table at
    /// https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Grundregeln
    /// Ignore code repetitions.
    void addCode(QString & result, QString const & code) {
        for( auto const & c: code ) {
            if( ! result.endsWith(c) ) {
                result += c;
            }
        }
    }

    /// Remove '0' from the result code according to the Kölner Phonetik rules.
    /// See rules below table at
    /// https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Grundregeln
    /// Remove '0' except at the beginning.
    QString removeZeros(QString const & result) {
        if( result.isEmpty() )
            return result;

        // keep the first code digit unconditionally
        QString resultWithoutZero(result[0]);
        // remove zeros from the following code digits
        for( int i=1; i<result.size(); ++i) {
            if( result[i] != '0' ) {
                resultWithoutZero += result[i];
            }
        }

        return resultWithoutZero;
    }
} // end of local namespace

namespace KoelnerPhonetik {
    QString code(QString const & upperLowerInput)
    {
        // Conversions as of table
        // in https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik#Buchstabencodes
        static map<QChar,vector<CodeCondition> > const CodeTable {
            { 'a', { {always, "", "0"} } },
            { u'ä', { {always, "", "0"} } }, // extension: German umlaut
            { 'e', { {always, "", "0"} } },
            { 'i', { {always, "", "0"} } },
            { 'j', { {always, "", "0"} } },
            { 'o', { {always, "", "0"} } },
            { u'ö', { {always, "", "0"} } }, // extension: German umlaut
            { 'u', { {always, "", "0"} } },
            { u'ü', { {always, "", "0"} } }, // extension: German umlaut
            { 'y', { {always, "", "0"} } },
            { 'b', { {always, "", "1"} } },
            { 'p', { {notBefore, "h", "1"}, {otherwise, "", "3"} } },
            { 'd', { {notBefore, "csz", "2"}, {otherwise, "", "8"} } },
            { 't', { {notBefore, "csz", "2"}, {otherwise, "", "8"} } },
            { 'f', { {always, "", "3"} } },
            { 'v', { {always, "", "3"} } },
            { 'w', { {always, "", "3"} } },
            { 'g', { {always, "", "4"} } },
            { 'k', { {always, "", "4"} } },
            { 'q', { {always, "", "4"} } },
            { 'c', { {anlautBefore, "ahkloqrux", "4"},
                    {after, "sz", "8"}, // note the priority over the following line!
                    {before, "ahkoqux", "4" },
                    {otherwise, "ahkloqrux", "8",}
                } },
            { 'x', { {notAfter, "ckq", "48"}, {otherwise, "", "8"} } },
            { 'l', { {always, "", "5"} } },
            { 'm', { {always, "", "6"} } },
            { 'n', { {always, "", "6"} } },
            { 'r', { {always, "", "7"} } },
            { 's', { {always, "", "8"} } },
            { u'ß', { {always, "", "8"} } }, // extension: German sharp s
            { 'z', { {always, "", "8"} } },
            { ' ', { {always, "", " "} } }, // extension: allow sentences as input
        };

        QString input = upperLowerInput.toLower();

        QString result;
        for( int i = 0; i < input.length(); ++i ) {
            if( input[i] == 'h' )
                continue;

            auto const & entry = CodeTable.find(input[i]);
            if( entry == CodeTable.end() ) {
                // no entry, ignore
                continue;
            }

            auto const & conditions = entry->second;
            for( auto const & condition: conditions ) {
                if( condition.predicate(input, i, condition.context) ) {
                    addCode(result, condition.code);
                    break;
                }
            }
        }

        return removeZeros(result);
    }

    string code( string const & input )
    {
        return code( QString().fromStdString(input) ).toStdString();
    }

    QString code( char const * const input )
    {
        return code( QString(input) );
    }

    void WordListAnalyzer::analyse(istream & inputFile)
    {
        string word;    // we assume a line is a "word"
        while( getline(inputFile, word) ) {
            string code = KoelnerPhonetik::code(word);
            codeToWord.insert({code, word});
            codeToFrequency[code] = codeToWord.count(code);
            if( codeToFrequency[code] > maxFrequencyOfAnyCode ) {
                maxFrequencyOfAnyCode = codeToFrequency[code];
            }
        }

        for( auto & [code, frequency]: codeToFrequency ) {
            frequencyToCodes[frequency]
                    .push_back(code);
        }
    }

    void WordListAnalyzer::printResults(ostream & output)
    {
        output << "Found " << codeToWord.size() << " words, "
               "maximum frequency is " << maxFrequencyOfAnyCode << endl;

        output << "Found " << frequencyToCodes.size()
            << " different frequencies." << endl;

        for( auto & [frequency, codes]: frequencyToCodes ) {
            for( auto & c: codes ) {
                output << c << " (" << frequency << "): ";
                auto [start, end] = codeToWord.equal_range(c);
                for( auto i = start; i != end; ++i ) {
                    output << i->second << " ";
                }
                output << endl;
            }
        }
    }

    int WordListAnalyzer::getMaxFrequencyOfAnyCode() const
    {
        return maxFrequencyOfAnyCode;
    }

    const multimap<string, string> & WordListAnalyzer::getCodeToWord() const
    {
        return codeToWord;
    }

    const map<string, int> & WordListAnalyzer::getCodeToFrequency() const
    {
        return codeToFrequency;
    }

    const map<int, vector<string>> & WordListAnalyzer::getFrequencyToCodes() const
    {
        return frequencyToCodes;
    }

} // end of namespace KoelnerPhonetik
