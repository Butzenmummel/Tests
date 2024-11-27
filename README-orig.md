# Kata Kölner Phonetik

[![pipeline status](https://gitlab.ai.it.hs-worms.de/swq-prf/swq-prf-23s/badges/develop/pipeline.svg)](https://gitlab.ai.it.hs-worms.de/swq-prf/swq-prf-23s/-/commits/develop)
[![coverage report](https://gitlab.ai.it.hs-worms.de/swq-prf/swq-prf-23s/badges/develop/coverage.svg)](https://gitlab.ai.it.hs-worms.de/swq-prf/swq-prf-23s/-/jobs/artifacts/develop/file/build/coverage-html/index.html?job=test)

Dies ist ein Übungsprojekt (Kata) für das Modul "Softwarequalität".

Es basiert auf unserem Basis-Projekt [Catch2 TDD cmake starter project](
https://gitlab.ai.it.hs-worms.de/swq/base-projects/catch2-cmake-project).

[[_TOC_]]

Zur Bearbeitung der Aufgabe legen Sie bitte [Branches](
https://gitlab.ai.it.hs-worms.de/swq-prf/swq-prf-23s/-/branches)
wie `team/zwiebel-hacker` oder `team/hau-die-software` an mit beliebigen Namen,
dem Präfix `team/`, sodass wir die Übersicht behalten können. Seien Sie nett
zueinander und kapern Sie nicht den Branch eines anderen Teams, sonst müssen
wir in Forks und/oder mit Restriktionen arbeiten.

## Aufgabenstellung

Es soll eine C++ Klasse erstellt werden, Strings vom Typ [`QString`](https://doc.qt.io/qt-5/qstring.html#details) in eine
phonetische Darstellung entsprechend dem Algorithmus "Kölner Phonetik" (vgl.
[Wikipedia](https://de.wikipedia.org/wiki/K%C3%B6lner_Phonetik)) umwandelt.  
(Die Verwendung von `QString` macht einiges am String-Handling leichter, da
die C++20 Unterstützung von `u8string` noch ausbaufähig ist – in kommenden
Versionen des C++ Standard kann evtl. `u8string` genutzt werden.)

Damit können z.B. phonetische Suchen für ähnlich klingende Worte (z.B. die
Namen "Mayer", "Meyer", "Maier") durchgeführt werden oder auch bei textuellen
Nutzer-Eingaben Wortergänzungen oder Rechtschreibkorrekturen basierend auf
phonetisch "passenden" Worten angeboten werden.

Als Test-Applikation könnten z.B. gleichklingende Worte aus der Wortliste
`/usr/share/dict/ngerman` des Debian-Linux-Pakets `wngerman` nach Häufigkeit
sortiert ausgegeben werden (die Liste enthält ca. 356000 Worte).

Zur Speicherung der Wort-Phonetik-Paare könnte z.B. auch die Klasse aus dem
[Kata "Verkettete Liste"](
https://gitlab.ai.it.hs-worms.de/swq/katas/verkettete-liste) verwendet werden.

--------------------------------------------------------------

# Catch2 nomenclature

Note that
[Catch2 (see tutorial)](https://gitlab.ai.it.hs-worms.de/swq/frameworks/Catch2/-/blob/main/docs/tutorial.md) test
uses a nomenclature which has small differences against the usual ISTQB
nomenclature:

ISTQB defines test _suites_ consisting of different test _cases_, and each
test case is defined by it's input and expected results; see the [ISTQB glossary entries](https://glossary.istqb.org/):
- [test case](https://glossary.istqb.org/en_US/term/test-case-2)
- [test suite](https://glossary.istqb.org/en_US/term/test-suite-1-3)

Catch2 doesn't have something called _test suite_, but you may use the
test case _tag_ to group different test cases to a test suite.

Additionally, Catch2 uses a _TestCase_ (optionally) as a container of several
_Sections_; for each test case section, the test case is executed once again
from start. See this section of the
[Catch2 Tutorial](https://gitlab.ai.it.hs-worms.de/swq/frameworks/Catch2/-/blob/main/docs/tutorial.md#test-cases-and-sections)


[[_TOC_]]

# Build Instructions

## Prerequisites
To use this project, you need the following tools; see below for installation
instructions.

- `git` (revision control system)
- `g++` (C++ compiler)
- `cmake` (project build environment)
- `doxygen` (documentation generator)
- `graphviz` (graphics generate, supports doxygen to generate e.g.
              class diagrams etc.)
- `lcov` (line coverage analysis)
- Though not necessarily required, we use and recommend the QtCreator IDE.

Our reference development platform is Debian 11 GNU/Linux, though the project
should be buildable on other development platforms too (like MS Windows or
Apple MacOS), if the mentioned free software tools are installed.

## Installing the build tools

### Debian 11 GNU/Linux

Required tools to build and analyse the project:
- `sudo apt update`
- `sudo apt install build-essential qtbase5-dev git cmake doxygen graphviz lcov`

Additional tools are not strictly required, but recommended:
- `sudo apt install gitk doxygen-gui git-gui`
- `sudo apt install git-doc cmake-doc doxygen-doc`

QtCreator IDE and some debugging tool (takes about 900MB extra storage):
- `sudo apt install qtcreator valgrind`

This might work on current Ubuntu installations too, but that's untested.

## Checking out the code
After forking the project, you can check out the code on the command line with a command similar to:
```
git clone https://infXXXX@gitlab.ai.it.hs-worms.de/infXXXX/swq-prf-23s.git
```

## Building the application
```
  cd build          # only if not already there
  cmake ..          # prepares the Makefiles
  make              # generates helloworld
  ./helloworld      # enjoy the famous program
```

## Cleaning the build directory
- initially the build directory is empty, so all files there are
  generated by the build - and if you didn't save anything there, you
  can safely remove all files by using 'rm'
- alternatively, just remove the files built by 'make':
```
  cd build          # only if not already there
  make clean        # optionally, remove generated binaries
```

# Creating the documentation
The documentation is built with [Doxygen](http://www.stack.nl/~dimitri/doxygen):
- `bin/run-doxygen` will create the html doc in `doc/html`

# Running coverage analysis
To create the unit test application and to run the coverage analysis, a small
shell script `bin/run-tests` is provided. It saves the coverage analysis
in `build/coverage-html`. Before running the script, you have to build
the `unittest` application with coverage instrumentation. The coverage
instrumentiation is included in our builds for the build type debug:

```
  cd build
  cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=True ..
  make unit-test
  cd ..
  bin/run-tests
  xdg-open build/coverage-html/index.html       # start browser
```

# License
This catch2 cmake project is licensed under the [GNU General Pulibc License
version 3](LICENSE) (or later).

It is intended to use a [Copyleft](https://www.gnu.org/licenses/copyleft.html)
license, as our work is paid by the public, and: [Public Money? Public
Code!](https://fsfe.org/activities/publiccode/index.html)

```
# This file is part of the program 'koelner-phonetik',
# see https://gitlab.ai.it.hs-worms.de/swq-prf/swq-prf-23s
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
