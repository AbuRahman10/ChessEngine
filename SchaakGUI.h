//
// Created by toonc on 12/17/2021.
//

#ifndef SCHAKEN_SCHAAKGUI_H
#define SCHAKEN_SCHAAKGUI_H

#include "guicode/ChessWindow.h"
#include "SchaakStuk.h"
#include <QMessageBox>
#include <QAction>

class SchaakStuk;

class SchaakGUI:public ChessWindow {
public:

    SchaakGUI();
    void update();
    bool clicking = false; //telkens als er een 2de keer geklikt wordt, wordt clicking true

    zw player1 = wit;
    zw player2 = zwart;

    bool is_undo = false; //bevestigt dat undo mogelijk is
    bool no_undo = false; //bevestigt dat er geen undo meer is
    bool is_redo = false; //bevestigt dat er geen undo meer is
    bool no_redo = false; //bevestigt dat redo mogelijk is

    vector<pair<SchaakStuk*,pair<int,int>>> stuk_EN_coordinaat;

    bool AI_of_Sp = false;
    bool isAI = false;

    SchaakStuk* huidige_stuk;

private:

    SchaakStuk* schaakStuk; //het stuk waarop er geklikt wordt

    Game g; //de gegeven game

    void clicked(int x, int y) override; // Deze functie wordt opgeroepen telkens er op het schaakbord
    void player_change(); // deze functie gaat de beurt telkens wisselen van de twee spelers
    void Select_Focus_OFF(); // deze functie schakelt setTileFocus(), setTileSelect() en setTileThreat() uit
    void threatsON(SchaakStuk* schaakStuk1); // deze functie gaat een gegeven schaakstuk rood kleuren als die bedreigt wordt

    // deze functie gaat de bepaalde tegels van de geldige zetten van
    // de gegeven schaakstuk rood kleuren als die daar in gevaar kan staat
    void threatbox(SchaakStuk* schaakStuk1);
    void threatsOFF(); // dit functie gaat de rode kleur op de bedreigde stukken wegdoen
    void promotie(SchaakStuk* stuk); //deze functie gaat de schaakstuk promoveren naar de stuk naar keuze
    void newGame() override; //deze functie gaat het game opnieuw instellen
    void open() override; //deze functie opent een opgeslagen game
    void save() override; //deze functie slaagt een game op
    void undo() override; //gaat de verplaatsing ongedaan maken
    void redo() override; //dit gaat een stuk terug herplaatsen
    void visualizationChange() override;

    void vraagNewGame(); // vraagt een nieuwe game te laten opstarten

    void vraagAI();
    void AIgui();

/*  Overgeerfde functies van ChessWindow:

    void removeAllMarking();
    void clearBoard();
    void setItem(int i,int j,SchaakStuk* p);
    void setPieceThreat(int i,int j,bool b);
    void removeAllPieceThreats();
    void setTileSelect(int i,int j,bool b);
    void setTileFocus(int i,int j,bool b);
    void setTileThreat(int i,int j,bool b);

    bool displayKills();
    bool displayMoves();
    bool displayThreats();
*/
};


#endif //SCHAKEN_SCHAAKGUI_H
