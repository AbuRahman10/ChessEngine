//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"
#include "iostream"
using namespace std;

// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr)
{
    g.setStartBord();
    update();
}
// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {

    // Volgende schaakstukken worden aangemaakt om het voorbeeld te illustreren.
    // In jouw geval zullen de stukken uit game g komen

    if (clicking == false) // als er voor het eerst geklikt wordt (clicking blijft false)
    {
        if (AI_of_Sp == false)
        {
            vraagAI();
            AI_of_Sp = true;
        }
        if (g.schaak(player2) or g.schaak(player1)) // gaat een nieuwe game starten als de user het wilt
        {
            if (g.schaakmat(zwart))
            {
                vraagNewGame();
                return;
            }
            else if (g.schaakmat(wit))
            {
                vraagNewGame();
                return;
            }
        }
        if (g.pat(player2) or g.pat(player1))
        {
            vraagNewGame();
            return;
        }
        if (g.getPiece(r,k) != nullptr) // player 2 = zwart; zwart mag niet eerst beginnen
        {
            if (g.getPiece(r,k)->getKleur() == player2)
            {
                return;
            }
        }
        schaakStuk = g.getPiece(r,k);

        if (schaakStuk == nullptr)
        {
            return;
        }
        is_undo = false;

        huidige_stuk = schaakStuk;
        g.vorige_positie = g.coordinaat(schaakStuk); // undo en redo

        setTileSelect(r,k,true);  //het geselecteerde vak kleurt groen

        vector<pair<int,int>> geldigeZETTEN;
        geldigeZETTEN = schaakStuk->geldige_zetten(g);

        for (pair<int,int> i : geldigeZETTEN)
        {
            if (g.valid_move(schaakStuk,i.first,i.second))
            {
                if (displayMoves())
                {
                    setTileFocus(i.first,i.second, true); //alle geldige zetten van het bestaande schaakstuk blauw kleuren
                }
            }
        }
        threatbox(schaakStuk);
        clicking = true;  // clicking wordt true want zo kan je weten of dat er een tweede keer geklikt wordt of niet
        threatsOFF();
        return;
    }

    if (clicking == true) // als er een tweede keer geklikt wordt (als het eerste klik voldaan is)
    {

        if (g.valid_move(huidige_stuk,r,k)) // voor undo en redo
        {
            g.te_pakken_stuk = g.getPiece(r,k);
            no_undo = false;
            no_redo = false;
            is_undo = true;
        }
        else if (g.no_move(huidige_stuk,r,k)) // voor undo en redo
        {
            g.te_pakken_stuk = huidige_stuk;
            g.volgende_posiitie = g.coordinaat(huidige_stuk);
            no_undo = true;
            no_redo = false;
            is_redo = false;
        }
        else if (!g.valid_move(huidige_stuk,r,k)) // voor undo en redo
        {
            g.te_pakken_stuk = huidige_stuk;
            g.volgende_posiitie = g.coordinaat(huidige_stuk);
            no_undo = true;
            no_redo = true;
        }
        if (g.move(schaakStuk,r,k) == true)  // als de move geldig is
        {
            g.volgende_posiitie = g.coordinaat(g.getPiece(r,k));
            g.move(schaakStuk,r,k); // verplaats het stuk naar de gevraagde plaats
            update(); //update de visual
            Select_Focus_OFF(); //de selectering wordt ongedaan gemaakt

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (g.getPiece(i,j) != nullptr)
                    {
                        threatsON(g.getPiece(i,j));  //alle bedreigde stukken weergeven
                    }
                }
            }
            promotie(schaakStuk);
            if (g.schaak(player2) or g.schaak(player1)) //brengt een message wanneer er schaak, schaakmat of pat veroorzaakt wordt
            {
                if (g.schaakmat(zwart))
                {
                    message("Wit wint!");
                    clicking = false;
                    return;
                }
                else if (g.schaakmat(wit))
                {
                    message("Zwart wint!");
                    clicking = false;
                    return;
                }
                else
                {
                    message("Schaak!");
                }
            }
            if (g.pat(player2) or g.pat(player1))
            {
                message("Gelijkspel (Draw)");
                clicking = false;
                return;
            }
            player_change(); // en de speler wordt gewisseld (kleur gewisseld)
            clicking = false; // zo beeïndigt de tweede klik
            if (isAI)
            {
                AIgui();
            }
            return; //niet meer verder gaan
        }

        else if (g.move(schaakStuk,r,k) == false) // als de move niet geldig is
        {
            if (g.no_move(schaakStuk,r,k)) //als er op hetzelfde stuk geselecteerd wordt
            {
                Select_Focus_OFF();
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (g.getPiece(i,j) != nullptr)
                        {
                            threatsON(g.getPiece(i,j));  //alle bedreigde stukken weergeven
                        }
                    }
                }
                clicking = false;
                return;
            }
            message("Dit zet is ongeldig"); //als het te_verplaatsen stuk naar een ongeldige plaats verplaatst wordt
            Select_Focus_OFF();

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (g.getPiece(i,j) != nullptr)
                    {
                        threatsON(g.getPiece(i,j)); //alle bedreigde stukken weergeven
                    }
                }
            }
            clicking = false;
            return;
        }
        player_change();
        clicking = false;
    }
}

// deze functie gaat de beurt telkens wisselen van de twee spelers
void SchaakGUI::player_change()
{
    zw tempkleur = player2;
    player2 = player1;
    player1 = tempkleur;
}

//deze functie gaat het game opnieuw instellen
void SchaakGUI::newGame()
{
    g.clearSchaakBord();
    clearBoard();
    g.setStartBord();
    player1 = wit;
    player2 = zwart;
    removeAllMarking();
    removeAllPieceThreats();
    update();
}

//deze functie slaagt een game op
void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for  (int i=0;i<8;i++) {
            out << QString("Pb");
        }
        for  (int r=3;r<7;r++) {
            for (int k=0;k<8;k++) {
                out << QString(".");
            }
        }
        for  (int i=0;i<8;i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}
//deze functie opent een opgeslagen game
void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Invalid File Format");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString& Q) {
            message(Q);
        }
    }
    update();
}

//gaat de verplaatsing ongedaan maken
void SchaakGUI::undo()
{
    if (huidige_stuk == nullptr)
    {
        return;
    }
    if (is_undo == true and no_undo == false and huidige_stuk != nullptr)
    {
        g.move_back(huidige_stuk);
        update();
        removeAllPieceThreats();
        removeAllMarking();
        player_change();
        message("Je hebt undo gekozen");
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (g.getPiece(i,j) != nullptr)
                {
                    threatsON(g.getPiece(i,j));  //alle bedreigde stukken weergeven
                }
            }
        }
        is_undo = false;
        is_redo = true;
    }
    else if (no_undo == false)
    {
        message("Je hebt geen undo keuze meer");
        no_undo = false;
    }
}
//dit gaat een stuk terug herplaatsen
void SchaakGUI::redo()
{
    if (huidige_stuk == nullptr)
    {
        return;
    }
    if (is_redo == true and huidige_stuk != nullptr)
    {
        g.redo_move(huidige_stuk);
        update();
        removeAllPieceThreats();
        removeAllMarking();
        player_change();
        message("Je hebt redo gekozen");
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (g.getPiece(i,j) != nullptr)
                {
                    threatsON(g.getPiece(i,j));  //alle bedreigde stukken weergeven
                }
            }
        }
        is_redo = false;
        is_undo = true;
    }
    else if (no_redo == false)
    {
        message("Je hebt geen redo keuze meer");
        no_redo = false;
    }
}

//brengt een message wanneer er iets gecheckt wordt bij visuals
void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Visualization changed : ")+visstring);
}

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update()
{
    clearBoard(); //bord eerst grafisch leeg maken
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (g.getPiece(i,j) != nullptr)
            {
                setItem(i,j,g.getPiece(i,j)); //elke stuk toevoegen die geen nullptr is
            }
        }
    }
}

// deze functie schakelt setTileFocus(), setTileSelect() en setTileThreat() uit
void SchaakGUI::Select_Focus_OFF()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            setTileSelect(i,j, false);
            setTileFocus(i,j, false);
            setTileThreat(i,j, false);
        }
    }
}

// deze functie gaat een gegeven schaakstuk rood kleuren als die bedreigt wordt
void SchaakGUI::threatsON(SchaakStuk* schaakStuk1)
{   // gaat naar de vijands stukken kijken; als de gegeven schaakstuk in 1 van de vijands geldige zetten zit -> bedreigd (rood)
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (g.getPiece(i,j) != nullptr and g.getPiece(i,j)->getKleur() != schaakStuk1->getKleur())
            {
                SchaakStuk* stuk = g.getPiece(i,j);
                vector<pair<int,int>> geldigeZETTEN;
                geldigeZETTEN = stuk->geldige_zetten(g);

                for (pair<int,int> i : geldigeZETTEN)
                {
                    if (g.getPiece(i.first,i.second) == schaakStuk1)
                    {
                        if (displayThreats() and schaakStuk1->getKleur() == player1)
                        {
                            setPieceThreat(i.first,i.second, true);
                        }
                        else if (displayKills() and schaakStuk1->getKleur() != player1)
                        {
                            setPieceThreat(i.first,i.second, true);
                        }
                    }
                }
            }
        }
    }
}

// deze functie gaat de bepaalde tegels van de geldige zetten van
// de gegeven schaakstuk rood kleuren als die daar in gevaar kan staat
void SchaakGUI::threatbox(SchaakStuk *schaakStuk1)
{
    for (int i = 0; i < 8; i++) //door heel het bord gaan
    {
        for (int j = 0; j < 8; j++)
        {
            SchaakStuk* stuk = g.getPiece(i,j);
            if (g.getPiece(i,j) != nullptr and g.getPiece(i,j)->getKleur() != schaakStuk1->getKleur()) //naar de vijand kijken
            {
                vector<pair<int,int>> moveZETTEN;
                moveZETTEN = schaakStuk1->geldige_zetten(g);

                for (pair<int,int> x : moveZETTEN)
                {
                    if (g.valid_move(schaakStuk1,x.first,x.second) == true)
                    {
                        vector<pair<int,int>> verslaan;
                        verslaan = stuk->verslaan(g);

                        for (pair<int,int> zet : verslaan)
                        {   //als een geldige zet (zetten die kunnen verslaan) van vijand overeenkomen met de geldige zetten van de gegeven schaakstuk -> bedreigd (rood)
                            if (zet == x)
                            {
                                setTileThreat(x.first,x.second, true);
                            }
                        }
                    }
                }
            }
        }
    }
}

// dit functie gaat de rode kleur op de bedreigde stukken wegdoen
void SchaakGUI::threatsOFF()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            setPieceThreat(i,j, false);
        }
    }
}

//deze functie gaat het schaakstuk promoveren naar de stuk naar keuze
void SchaakGUI::promotie(SchaakStuk *stuk)
{
    if (stuk != nullptr and stuk->ISpion())
    {
        if (stuk->getKleur() == wit and g.coordinaat(stuk).first == 0)
        {   //ik ga 4 keuzes creëren door 4 Abstractbuttons (knoppen krijgen een functie mee) te maken
            QMessageBox c;
            c.setText("Keuze:");
            QAbstractButton* koningin = reinterpret_cast<QAbstractButton *>(c.addButton("Koningin",QMessageBox::ActionRole)); // QT website
            QAbstractButton* paard = reinterpret_cast<QAbstractButton *>(c.addButton("Paard", QMessageBox::ActionRole));
            QAbstractButton* loper = reinterpret_cast<QAbstractButton *>(c.addButton("Loper", QMessageBox::ActionRole));
            QAbstractButton* toren = reinterpret_cast<QAbstractButton *>(c.addButton("Toren", QMessageBox::ActionRole));

            c.exec();

            //promoveren naar de gekozen stuk
            if (c.clickedButton() == paard)
            {
                g.promotiePAARD(stuk);
            }
            else if (c.clickedButton() == koningin)
            {
                g.promotieKONINGIN(stuk);
            }
            else if (c.clickedButton() == loper)
            {
                g.promotieLOPER(stuk);
            }
            else if (c.clickedButton() == toren)
            {
                g.promotieTOREN(stuk);
            }
            update();

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (g.getPiece(i,j) != nullptr)
                    {
                        threatsON(g.getPiece(i,j));
                    }
                }
            }
        }
        else if (stuk->getKleur() == zwart and g.coordinaat(stuk).first == 7)
        {
            QMessageBox c;
            c.setText("Keuze:");
            QAbstractButton* koningin = reinterpret_cast<QAbstractButton *>(c.addButton("Koningin",QMessageBox::ActionRole)); // QT website
            QAbstractButton* paard = reinterpret_cast<QAbstractButton *>(c.addButton("Paard", QMessageBox::ActionRole));
            QAbstractButton* loper = reinterpret_cast<QAbstractButton *>(c.addButton("Loper", QMessageBox::ActionRole));
            QAbstractButton* toren = reinterpret_cast<QAbstractButton *>(c.addButton("Toren", QMessageBox::ActionRole));

            c.exec();

            if (c.clickedButton() == paard)
            {
                g.promotiePAARD(stuk);
            }
            else if (c.clickedButton() == koningin)
            {
                g.promotieKONINGIN(stuk);
            }
            else if (c.clickedButton() == loper)
            {
                g.promotieLOPER(stuk);
            }
            else if (c.clickedButton() == toren)
            {
                g.promotieTOREN(stuk);
            }
            update();
        }
    }
}

// vraagt een nieuwe game te laten opstarten
void SchaakGUI::vraagNewGame()
{
    //bij ja -> newGame()
    QMessageBox c;
    c.setText("Spel opnieuw opstarten?:");
    QAbstractButton* ja = reinterpret_cast<QAbstractButton *>(c.addButton("JA",QMessageBox::ActionRole)); // QT website
    QAbstractButton* neen = reinterpret_cast<QAbstractButton *>(c.addButton("NEEN", QMessageBox::ActionRole));

    c.exec();

    if (c.clickedButton() == ja)
    {
        message("Spel wordt opnieuw gestart!");
        newGame();
    }
    else if (c.clickedButton() == neen)
    {
        message("Bedankt om te spelen! (Ctrl + N voor een nieuwe spel)");
        removeAllPieceThreats();
        removeAllMarking();
        return;
    }
}

void SchaakGUI::vraagAI()
{
    //bij ja -> newGame()
    QMessageBox c;
    c.setText("Wil je tegen de computer spelen?");
    QAbstractButton* computer = reinterpret_cast<QAbstractButton *>(c.addButton("COMPUTER",QMessageBox::ActionRole)); // QT website
    QAbstractButton* speler2 = reinterpret_cast<QAbstractButton *>(c.addButton("TWEE SPELERS", QMessageBox::ActionRole));

    c.exec();

    if (c.clickedButton() == computer)
    {
        message("Veel Succes!");
        isAI = true;
    }
    else if (c.clickedButton() == speler2)
    {
        message("Geniet Van De Game!");
    }
}

void SchaakGUI::AIgui()
{
    g.AI();
    update();
    player_change();
}
