//============================================================================
/// \file
/// \ingroup    g_applib
/// \brief      Contains the VersionInfo implementation parts.
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

#include "VersionInfo.h"
#include "generated-version.h"

using namespace std;

const string VersionInfo::buildTag(BUILDTAG);
const string VersionInfo::version(GITVERSION);

string VersionInfo::getVersion()
{
    return version;
}

string VersionInfo::getBuildTag()
{
    return buildTag;
}
