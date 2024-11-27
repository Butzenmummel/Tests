//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      Contains the KoelnerPhonetik class definition.
//============================================================================
/// \copyright  GNU General Public License (GPL) Version 3
//
// Copyright 2023 SWQ team
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

#if !defined(KOELNERPHONETIK_H)
#define KOELNERPHONETIK_H

#include <QString>
#include <string>
#include <iostream>
#include <map>
#include <vector>

namespace KoelnerPhonetik {
    /// \defgroup code Koelner Phonetik encoding functions
    /// Generate phonetic code of input in UTF-8 format using the
    /// Koelner Phonetik algorithm.
    /// See https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik
    /// @{

    /// Phonetic code of input as std::string in UTF-8 format.
    /// \returns the code as std::string
    std::string code(std::string const & input);

    /// Phonetic code of input as char* in UTF-8 format.
    /// \returns the code as QString
    QString code(char const * const input);

    /// Phonetic code of input as QString.
    /// \returns the code as QString
    QString code(QString const & input);
    /// @}

    /// Analyze a word list using Koelner Phonetik codes.
    class WordListAnalyzer {
        public:
            /// Analyse input using code().
            /// By definition, a "word" is one line of the input stream,
            /// i.e. code() will be called for a whole line of input. You
            /// have to organize the input stream by yourself in case that's
            /// not what you want.
            void analyse( std::istream & input );

            /// Print analysis results on output (default: std::cout).
            void printResults( std::ostream & output = std::cout );


            /// Access functions to analysis details.
            /// @{

            /// Get the maximum frequency of any code.
            int getMaxFrequencyOfAnyCode() const;

            /// Get read access to the codeToWord multimap.
            typedef std::multimap<std::string, std::string> StrStrMultiMap;
            StrStrMultiMap const & getCodeToWord() const;

            /// Get read access to the codeToFrequency map.
            typedef std::map<std::string, int> StrIntMap;
            StrIntMap const & getCodeToFrequency() const;

            /// Get read access to the frequencyToCodes map.
            typedef std::map<int, std::vector<std::string>> IntVectorStrMap;
            IntVectorStrMap const & getFrequencyToCodes() const;

            /// @}

        private:
            /// Pairs of phonetic code (key) and word (values).
            /// As codes can be equal for different words, we need
            /// a multimap.
            StrStrMultiMap codeToWord;

            /// Number of times a code was found.
            StrIntMap codeToFrequency;

            /// The maximum frequency of any code.
            int maxFrequencyOfAnyCode = 0;

            /// Pairs of frequency and vector of codes found at this frequency.
            IntVectorStrMap frequencyToCodes;
    };
}

#endif
