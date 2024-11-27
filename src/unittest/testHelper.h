//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Test helper functions.
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

#include "catch.hpp"
#include <QString>
#include <iosfwd>
#include <sstream>

using namespace std;

/// Helper function for Catch2 to output QStrings
inline
ostream & operator << (ostream & os, QString const & s) {
    return os << s.toStdString();
}
