//============================================================================
/// \file
/// \ingroup    g_main
/// \brief      Contains the application's main function.
/// \details    No details necessary on this complex functionality :-)
///
/// \copyright  GNU General Public License (GPL) Version 3
//
// Copyright 2012-2023 Herbert Thielen and SWQ students team
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

#include "app-lib/app-lib.h"
#include <fstream>
#include <iostream>

using namespace std;

static char const * const wordListPath = "/usr/share/dict/ngerman";

int main()
{
    cout << "Kölner Phonetik demo version "
         << VersionInfo::getVersion()
         << " (" << VersionInfo::getBuildTag() << ")" << endl;

    ifstream inputFile(wordListPath);
    if( ! inputFile ) {
        cerr << "Could'nt open " << wordListPath << ", aborting." << endl;
        exit(1);
    }

    KoelnerPhonetik::WordListAnalyzer a;
    a.analyse( inputFile );
    a.printResults();
}
