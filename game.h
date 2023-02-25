//  Student: Abobaker Rahman
//  Rolnummer: 2022825
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H
#include "vector"

#include "SchaakStuk.h"
#include "guicode/chessboard.h"

using namespace std;

class SchaakStuk;
class Game {
// variabelen om de status van het spel/bord te bewaren
public:
    Game();
    ~Game();

    bool castle_wit = false;
    bool castle_zwart = false;
    bool castle_long_wit = false;
    bool castle_long_zwart = false;

    pair<int,int> vorige_positie;
    pair<int,int> volgende_posiitie = {};
    SchaakStuk* te_pakken_stuk;

    // EN PASSANT
    // elke kolom heeft een bool voor en passant, zo kan ik weten op welke kolom een stuk en passant kan uitvoeren
    bool kol0wit = false;
    bool kol1wit = false;
    bool kol2wit = false;
    bool kol3wit = false;
    bool kol4wit = false;
    bool kol5wit = false;
    bool kol6wit = false;
    bool kol7wit = false;

    bool kol0zwart = false;
    bool kol1zwart = false;
    bool kol2zwart = false;
    bool kol3zwart = false;
    bool kol4zwart = false;
    bool kol5zwart = false;
    bool kol6zwart = false;
    bool kol7zwart = false;

    // EN PASSANT VERSLAAN
    // zo kan ik weten of er en passant uitgevoerd is of niet, bij true gaat en passant niet meer bij een kleur

    bool en_passantWIT = false;
    bool en_passantZWART = false;

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k
    bool schaak(zw kleur); //geeft aan of het schaak is bij de aangegeven kleur
    bool schaakmat(zw kleur); //geeft aan of een bepaalde kleur in schaakmat positie ligt, dan gaat de oppositie winnen
    bool pat(zw kleur); // wordt true wanneer de koning niet schaak is, maar dat geen enkele schaakstuk van de gegeven kleur kan bewegen
    void setStartBord(); // Zet het bord klaar; voeg de stukken op de jusite plaats toe

    pair<int,int> coordinaat(const SchaakStuk* schaakStuk) const; //geeft de coordinaat van de aangegeven schaakstuk

    bool schaakstuk_bestaat(const SchaakStuk* schaakStuk) const; //geeft aan of de aangegeven schaakstuk bestaat en binnen dimensie is

    // Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
    // Als er geen schaakstuk staat op deze positie, geef nullptr terug
    SchaakStuk* getPiece(int r, int k);

    // Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
    // Als er al een schaakstuk staat, wordt het overschreven.
    void setPiece(int r, int k, SchaakStuk* s);


    bool no_move(SchaakStuk* s,int r, int k); //geeft true als de gegeven schaakstuk geen beweging maakt

    bool kingStuck(zw kleur); //geeft true als de koning van de gegeven kleur geen beweging kan maken

    bool valid_move(SchaakStuk* s,int r, int k); //doet hetzelfde werk als move maar verplaatst het stuk niet (bij een if statement gebruikt)

    bool ISrokade(SchaakStuk* s,int r, int k); //geeft aan of de koning van de bepaalde kleur een rokade kan uitvoeren

    void move_back(SchaakStuk* s); //wordt gebruikt bij undo; verplaatst het stuk terug naar zijn vorige positie

    void redo_move(SchaakStuk* s); //wordt gebruikt bij redo; verplaatst het stuk terug naar zijn positie voor dat undo uitgevoerd werd

    bool en_passant(SchaakStuk *s); //geeft aan of het stuk en passant kan uitvoeren of niet


    //kijkt of een pion 1 keer van zijn start positie naar 1 rij hoger komt,
    // dan schakelt deze functie de en-passant mogelijkheid op die kolom uit
    void en_passantOFF(SchaakStuk* s, int r, int k);
    void en_passantOFFGEM(int oude_pos1, int col, int r, int oude_pos2, bool &kol_kleur);

    //als er een en-passant mogelijkheid is en het stuk toch geen en-passant move gaat doen,
    //dan kan je geen en-passant meer doen op die kolom
    void geen_en_passantOFF(SchaakStuk* s, int r, int k);
    void geen_en_passantOFFGEM(SchaakStuk* s, int oude_pos1, int col, int k, int oude_pos2, bool &kol_zwart,bool &kol_wit);

    //als er een en-passant mogelijkheid is en het stuk toch geen en-passant move gaat doen,
    //maar een andere stuk van het zelfde kleur beweegt, en-passant gaat dan niet meer op die bepaalde kolom
    void en_passant_checken(SchaakStuk* s);
    void en_passant_checkenGEM(SchaakStuk* s,int j,int k,bool &kol_zwart,bool &kol_wit);

    //als een pion 2 naar voor komt en als er geen stuk naast hem ligt,
    //dan kan je geen en-passant meer uitvoeren op die kolom
    void en_passantOFF2hoger(SchaakStuk* s, int r, int k);
    void en_passantOFF2hogerGEM(SchaakStuk *linkerstuk, SchaakStuk *rechterstuk, int oude_pos, int k, bool &kol_kleur);

    //de volgende 4 functies laten de gegeven stukken promoveren naar de aangekozen nieuwe stuk bij promotie
    void promotiePAARD(SchaakStuk* stuk);
    void promotieKONINGIN(SchaakStuk* stuk);
    void promotieLOPER(SchaakStuk* stuk);
    void promotieTOREN(SchaakStuk* stuk);

    void clearSchaakBord(); // gaat het bord leeg maken voor newGame

    bool lege_vak(SchaakStuk* schaakStuk,int x,int y);

private:
    // Hier zet jij jouw datastructuur neer om het bord te bewaren ...

    vector<vector<SchaakStuk*>> schaakbord;
};


#endif //SCHAKEN_GAME_H