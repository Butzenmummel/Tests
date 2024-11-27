//============================================================================
// Name           : aufgabe.cpp
// Description    : unit test (in exam "Softwarequalitaet")
//============================================================================
//
// Aufgabe:
// ========
// Die in Aufgabe 5 (siehe ausgedruckte Papierversion der Pruefungsangabe)
// beschriebenen Aufgaben sollen geloest und die entsprechenden Tests sollen
// implementiert werden.
//
// Folgende Aufgaben sind durchzufuehren:
// 1. Erzeugen Sie einen Fork des Pruefungs-Repositories in ihren
//    _persoenlichen_ Gitlab-Bereich, aendern Sie dabei bitte nicht den
//    Repository-Namen.
// 2. Clonen Sie das persoenliche Gitlab-Repository auf den Rechner im Labor.
// 3. Erstellen Sie die in der Aufgabenstellung geforderten Tests.
// 4. Aendern Sie moeglichst den Git-Commiter auf Ihren Namen und Ihre E-Mail
//    (es soll also moeglichst nicht "labor" als Commiter auftauchen).
// 5. Committen Sie die Aenderungen im lokalen Repository (Laborrechner).
// 6. Pushen Sie die Aenderungen zu ihrem Gitlab-Repository
//    (_keinen_ Merge-Request anlegen).
// 7. Schreiben Sie die ersten 8 Zeichen der git-Commit-Nummer Ihrer
//    Loesung auf das Deckblatt (ablesen in Ihrem Gitlab-Repository,
//    beispielsweise Menu-Punkt "Code->Commits" des Seitenmenues).
//
// ************************************************************
// * ACHTUNG: Ohne Push kann keine Aenderung bewertet werden! *
// ************************************************************
//
// Falls durch Ihre Tests Fehler gefunden werden, muessen Sie den
// Quellcode der Applikation nicht korrigieren; Sie sollten aber
// moeglichst sicher sein, dass nicht Ihr Test den Fehlerzustand
// enthaelt.
//
// Minimalanforderungen fuer die Punktevergabe:
// - Sie haben eine Aenderung durchgefuehrt.
// - Das Unit-Test-Programm ist mit Ihren Tests immer noch build- und ausfuehrbar
//   und bricht bei Ausfuehrung nicht sofort die Tests ab.
// - Sie haben Ihre Loesung in Ihr Git-Repository des Gitlab-Servers gepusht.
// - Sie haben die Commit-Nummer Ihrer Loesung auf das Deckblatt der Pruefungsangabe geschrieben.
//
// Bewertungskriterien:
// - Vollstaendigkeit des Testumfangs entsprechend der Aufgabenstellung
// - Korrektheit der Testfaelle
// - Struktur der Testfaelle und Commits (wartbar kodiert, datengetrieben _falls
//   sinnvoll_, Ersteller:in im Commit-Log erkennbar etc.)
//============================================================================

// Turn off clazy analysis annotations regarding TEST_CASEs.
// Seen in QtCreator 4.15.1 and 5.15.2, probably more.
// See https://github.com/KDE/clazy/blob/master/docs/man/clazy.pod
// clazy:excludeall=non-pod-global-static

#include "testHelper.h"
#include "app-lib/KoelnerPhonetik.h"

using namespace std;
using KoelnerPhonetik::WordListAnalyzer;

// maxFrequencyOfAnyCode Test
TEST_CASE("Testen Pruefungsaufgabe 5b") {
    WordListAnalyzer a;
    WordListAnalyzer::IntVectorStrMap ftc;

    auto [inputLine, expected] = GENERATE(
            table<string, int> ( {
                                    // newline (backslash n) für neues Wort
        {"",0},                     // leeres Element
        {"hallo", 1},               // ein Wort
        {"hallo\nhallo", 2},        // 2 Wörter mit gleichem Code
        {"hallo\ntest", 1},         // Wörter mit unterschiedlichem Code
        {"hallo\nhallo\ntest", 2}   // Kombination aus gleichen und untersch. Wörtern
    } )
    );

    istringstream input (inputLine);

    CAPTURE(inputLine);

    a.analyse(input);

    CAPTURE(a.getMaxFrequencyOfAnyCode());

    CHECK(a.getMaxFrequencyOfAnyCode() == expected);
}
