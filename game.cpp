//  Student: Abobaker Rahman
//  Rolnummer: 2022825
//  Opmerkingen: (bvb aanpassingen van de opgave)
//
#include "game.h"
#include "SchaakStuk.h"
#include "iostream"
using namespace std;


Game::Game() {}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
void Game::setStartBord()
{
    //eerst nullptrs toevoegen in heel het bord om later stukken op een bepaalde positie te kunnen toevoegen
    for (int i = 0; i < 8; i++)
    {
        schaakbord.push_back({});
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            schaakbord[i].push_back(nullptr);
        }
    }
    //ZWART
//-----------------------------------------
//-----------------------------------------
    //Toren
    schaakbord[0][0] = new Toren(zwart);
    schaakbord[0][7] = new Toren(zwart);


    //Paarden
    schaakbord[0][1] = new Paard(zwart);
    schaakbord[0][6] = new Paard(zwart);

    //Lopers
    schaakbord[0][2] = new Loper(zwart);
    schaakbord[0][5] = new Loper(zwart);

    //Koningin
    schaakbord[0][3] = new Koningin(zwart);
    //Koning
    schaakbord[0][4] = new Koning(zwart);
//--------------------------------------------------
    //Pionen zwart EN wit

    for (int i = 0; i < 8; i++)
    {
        schaakbord[1][i] = new Pion(zwart);
        schaakbord[6][i] = new Pion(wit);
    }
    //---------------------------------------------------
    //WIT
//-----------------------------------------
//-----------------------------------------
    //Toren

    schaakbord[7][0] = new Toren(wit);
    schaakbord[7][7] = new Toren(wit);

    //Paarden
    schaakbord[7][1] = new Paard(wit);
    schaakbord[7][6] = new Paard(wit);

    //Lopers
    schaakbord[7][2] = new Loper(wit);
    schaakbord[7][5] = new Loper(wit);

    //Koningin
    schaakbord[7][3] = new Koningin(wit);
    //Koning
    schaakbord[7][4] = new Koning(wit);
}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k)
{
    pair<int,int> nieuwe_positie(r,k);

    SchaakStuk* schaakStuk = getPiece(r,k);

    pair<int,int> oude_positie(coordinaat(s));

    vector<pair<int,int>> geldigeZETTEN;
    geldigeZETTEN = s->geldige_zetten(*this);

    if (!geldigeZETTEN.empty()) // als er geldige zetten bestaan
    {
        for (pair<int,int> i : geldigeZETTEN) // doorheen de geldige zetten gaan
        {
            //DE 4 MOGELIJKE ROKADES CHECKEN
            if (ISrokade(s,r,k) and !schaak(s->getKleur()))
            {
                if ((r == 7 and k == 6) and castle_wit == false and valid_move(s,7,5) == true)
                {
                    //DE VERPLAATSING
                    SchaakStuk* toren = getPiece(7,7);
                    setPiece(r,k,s);
                    setPiece(7,5, getPiece(7,7));
                    schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                    schaakbord[7][7] = nullptr;
                    if (schaak(getPiece(r,k)->getKleur())) //BIJ SCHAAK TERUG NAAR DE OUDE POSITIE VERPLAATSEN
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[i.first][i.second] = schaakStuk;
                        schaakbord[7][7] = toren; //OOK DE TOREN
                        setPiece(7,5, nullptr);
                        return false;
                    }
                    castle_wit = true; //ROKADE UITGEVOERD -> GEEN ROKADE MEER VOOR DE AANGEGEVEN KLEUR
                    return true;
                }
                else if ((r == 7 and k == 2) and castle_long_wit == false and valid_move(s,7,3) == true)
                {
                    SchaakStuk* toren = getPiece(7,0);
                    setPiece(r,k,s);
                    setPiece(7,3, getPiece(7,0));
                    schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                    schaakbord[7][0] = nullptr;
                    if (schaak(getPiece(r,k)->getKleur()))
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[i.first][i.second] = schaakStuk;
                        schaakbord[7][0] = toren;
                        setPiece(7,3, nullptr);
                        return false;
                    }
                    castle_long_wit = true;
                    return true;
                }
                else if ((r == 0 and k == 6) and castle_zwart == false and valid_move(s,0,5) == true)
                {
                    SchaakStuk* toren = getPiece(0,7);
                    setPiece(r,k,s);
                    setPiece(0,5, getPiece(0,7));
                    schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                    schaakbord[0][7] = nullptr;
                    if (schaak(getPiece(r,k)->getKleur()))
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[i.first][i.second] = schaakStuk;
                        schaakbord[0][7] = toren;
                        setPiece(0,5, nullptr);
                        return false;
                    }
                    castle_zwart = true;
                    return true;
                }
                else if ((r == 0 and k == 2) and castle_long_zwart == false and valid_move(s,0,3) == true)
                {
                    SchaakStuk* toren = getPiece(0,0);
                    setPiece(r,k,s);
                    setPiece(0,3, getPiece(0,0));
                    schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                    schaakbord[0][0] = nullptr;
                    if (schaak(getPiece(r,k)->getKleur()))
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[i.first][i.second] = schaakStuk;
                        schaakbord[0][0] = toren;
                        setPiece(0,3, nullptr);
                        return false;
                    }
                    castle_long_zwart = true;
                    return true;
                }
            }
            else if (ISrokade(s,r,k) and schaak(s->getKleur()))
            {
                return false; // IN GEVAL VAN SCHAAK GAAT ROKADE NIET
            }
            else if (i == nieuwe_positie) // als de nieuwe gevraagde positie geldig is -> verander dan de plaats ervan
            {
                en_passantOFF(s,r,k); //ZIE DEFINITIES
                en_passantOFF2hoger(s,r,k);
                if (en_passant(s)) //bij en passant, de 'gepasseerde' pion ook verwijderen omdat je het niet rechtstreeks verslaat
                {
                    if (s->getKleur() == wit and (r == oude_positie.first - 1 and k == oude_positie.second + 1) and en_passantWIT == false)
                    {
                        schaakbord[oude_positie.first][oude_positie.second + 1] = nullptr;
                        en_passantWIT = true; //ZIE DEFINITIE
                    }
                    else if (s->getKleur() == wit and (r == oude_positie.first - 1 and k == oude_positie.second - 1) and en_passantWIT == false)
                    {
                        schaakbord[oude_positie.first][oude_positie.second - 1] = nullptr;
                        en_passantWIT = true;
                    }
                    if (s->getKleur() == zwart and (r == oude_positie.first + 1 and k == oude_positie.second + 1) and en_passantZWART == false)
                    {
                        schaakbord[oude_positie.first][oude_positie.second + 1] = nullptr;
                        en_passantZWART = true;
                    }
                    else if (s->getKleur() == zwart and (r == oude_positie.first + 1 and k == oude_positie.second - 1) and en_passantZWART == false)
                    {
                        schaakbord[oude_positie.first][oude_positie.second - 1] = nullptr;
                        en_passantZWART = true;
                    }
                }

                geen_en_passantOFF(s, r, k); //ZIE DEFINITIE

                setPiece(r,k,s);
                schaakbord[oude_positie.first][oude_positie.second] = nullptr; //ALS DE MOVE GELDIG IS -> OUDE PLAATS WORDT LEEG (NULL)

                en_passant_checken(s); //ZIE DEFINITIE

                if (schaak(getPiece(r,k)->getKleur())) //ALS HET STUK ZICH VERPLAATST EN SCHAAK VEROORZAAKT -> MOVE IS NIET GELDIG
                {
                    setPiece(oude_positie.first,oude_positie.second,s); // TERUG NAAR OUDE PLAATS
                    schaakbord[i.first][i.second] = schaakStuk; // DE GEVULDE VAK WORDT TERUG GEVULD MET DE OORSPRONGELIJKE STUK
                    if (en_passant(s)) //bij en passant, de 'gepasseerde' pion ook terug zetten
                    {
                        if (s->getKleur() == wit and (r == oude_positie.first - 1 and k == oude_positie.second + 1))
                        {
                            schaakbord[oude_positie.first][oude_positie.second + 1] = new Pion(wit);
                            en_passantWIT = false;
                        }
                        else if (s->getKleur() == wit and (r == oude_positie.first - 1 and k == oude_positie.second - 1))
                        {
                            schaakbord[oude_positie.first][oude_positie.second - 1] = new Pion(wit);
                            en_passantWIT = false;
                        }
                        if (s->getKleur() == zwart and (r == oude_positie.first + 1 and k == oude_positie.second + 1))
                        {
                            schaakbord[oude_positie.first][oude_positie.second + 1] = new Pion(zwart);
                            en_passantZWART = false;
                        }
                        else if (s->getKleur() == zwart and (r == oude_positie.first + 1 and k == oude_positie.second - 1))
                        {
                            schaakbord[oude_positie.first][oude_positie.second - 1] = new Pion(zwart);
                            en_passantZWART = false;
                        }
                    }
                    return false;
                }
                //ROKADE; DUS IN DIT VOORWAARDE IS ER GEEN ROKADE UITGEVOERD (2 GEVALLEN: WIT EN ZWART)
                if (s->ISkoning() and s->getKleur() == wit)  // ALS DE KONING BEWEEGT -> KLEINE EN LANGE ROKADE WORDEN FALSE
                {
                    castle_wit = true;
                    castle_long_wit = true;
                }
                // ALS DE TOREN BEWEGEN -> AFHANKELIJK VAN DIT TOREN, KLEINE OF LANGE ROKADE -> FALSE
                else if (s->IStoren() and s->getKleur() == wit and (coordinaat(s).first == 7 and coordinaat(s).second == 7))
                {
                    castle_wit = true;
                }
                else if (s->IStoren() and s->getKleur() == wit and (coordinaat(s).first == 0 and coordinaat(s).second == 7))
                {
                    castle_long_wit = true;
                }
                if (s->ISkoning() and s->getKleur() == zwart)
                {
                    castle_zwart = true;
                    castle_long_zwart = true;
                }
                else if (s->IStoren() and s->getKleur() == zwart and (coordinaat(s).first == 0 and coordinaat(s).second == 7))
                {
                    castle_zwart = true;
                }
                else if (s->IStoren() and s->getKleur() == zwart and (coordinaat(s).first == 0 and coordinaat(s).second == 0))
                {
                    castle_long_zwart = true;
                }

                return true; // DE MOVE IS GELDIG
            }
        }
    }
    return false;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur)
{
    for (int i = 0; i < 8; i++) // doorheen het bord gaan
    {
        for (int j = 0; j < 8; j++)
        {
            if (getPiece(i,j) != nullptr) // het moet andere kleur zijn en ook geen lege vak
            {
                if (getPiece(i,j)->getKleur() != kleur)
                {
                    SchaakStuk* schaakStuk = getPiece(i,j);
                    vector<pair<int,int>> geldigeZETTEN;
                    geldigeZETTEN = schaakStuk->geldige_zetten(*this);

                    for (pair<int,int> x : geldigeZETTEN) //doorheen de geldige zetten van het andere kleur
                    {
                        SchaakStuk* stukgeldig = getPiece(x.first,x.second);
                        if (stukgeldig != nullptr and stukgeldig->ISkoning()) //als 1 van de geldige zetten de koning is -> schaak (true)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur)
{

    if (kingStuck(kleur) and schaak(kleur)) //als de koning geen geldige zetten heeft en ook schaak staat
    {
        for (int i = 0; i < 8; i++) // doorheen het bord gaan
        {
            for (int j = 0; j < 8; j++)
            {
                if (getPiece(i,j) != nullptr and getPiece(i,j)->getKleur() == kleur and !getPiece(i,j)->ISkoning())
                {
                    SchaakStuk* schaakStuk = getPiece(i,j);
                    vector<pair<int,int>> geldigeZETTEN;
                    geldigeZETTEN = schaakStuk->geldige_zetten(*this);

                    for (int x = 0; x < geldigeZETTEN.size(); x++) //doorheen de geldige zetten van dit stuk gaan
                    {
                        if (valid_move(schaakStuk,geldigeZETTEN[x].first,geldigeZETTEN[x].second)) // GEEN STUK VAN GEGEVEN KLEUR HEEFT GELDIG MOVE -> SCHAAKMAT
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur)
{
    if (!schaak(kleur)) // als het kleur niet in schaak staat
    {
        for (int i = 0; i < 8; i++) // doorheen het bord gaan
        {
            for (int j = 0; j < 8; j++)
            {
                if (getPiece(i,j) != nullptr and getPiece(i,j)->getKleur() == kleur) // als het stuk van de aangegeven kleur is
                {
                    SchaakStuk* schaakStuk = getPiece(i,j);
                    vector<pair<int,int>> geldigeZETTEN;
                    geldigeZETTEN = schaakStuk->geldige_zetten(*this);

                    for (pair<int,int> i : geldigeZETTEN) //doorheen de geldige zetten van dit stuk gaan
                    {
                        if (valid_move(schaakStuk,i.first,i.second)) // als er één stuk minsten 1 geldige zet heeft -> geen pat (false)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k)
{
    // Hier komt jouw code om op te halen welk stuk op rij r, kolom k staat

    if ((r < 8 and k < 8) and (r >= 0 and k >=0)) // r EN k MOETEN BEIDE BINNEN DIMENSIE ZIJN
    {
        if (schaakbord[r][k] != nullptr)
        {
            return schaakbord[r][k];
        }
        else
        {
            return nullptr;
        }
    }
    return nullptr;
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s)
{
    // Hier komt jouw code om een stuk neer te zetten op het bord
    if ((r < 8 and k < 8) and (r >= 0 and k >=0))
    {
        schaakbord[r][k] = s;
    }
}

//returnt de coordinaat van de aangegeven schaakstuk terug
pair<int, int> Game::coordinaat(const SchaakStuk* schaakStuk) const
{

    pair<int,int> coordinaat; //IN HET BORD ZOEKEN NAAR HET STUK DIE HETZELFDE IS ALS DE PARAMETER -> COORDINAAT OPGESLAGEN IN PAIR<int,int>

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (schaakStuk == schaakbord[i][j])
            {
                coordinaat.first = i;
                coordinaat.second = j;
            }
        }
    }

    return coordinaat;
}

//geeft aan of de aangegeven schaakstuk bestaat en binnen dimensie is
bool Game::schaakstuk_bestaat(const SchaakStuk *schaakStuk) const
{

    if (schaakStuk == nullptr)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 8; i++) // DOORHEEN DE BORD GAAN
        {
            for (int j = 0; j < 8; j++)
            {
                if (schaakbord[i][j] == schaakStuk) // ALS ER EEN SCHAAKSTUK BESTAAT DIE GELIJK IS AAN DE GEGEVEN SCHAAKSTUK -> GEGEVEN SCHAAKSTUK BESAAT
                {
                    return true;
                }
            }
        }
        return false;
    }
}

//geeft true als de gegeven schaakstuk geen beweging maakt
bool Game::no_move(SchaakStuk *s, int r, int k)
{
    if (move(s,r,k) == false) //KIJKEN BIJ ONGELDIGE ZETTEN WANT OP DEZELFDE PLAATS BLIJVEN = ONGELDIG (bij Schaakstuk::geldige_zetten)
    {
        if (coordinaat(s) == coordinaat(getPiece(r,k))) //ALS NIEUWE POSITIE == OUDE POSITIE -> NO MOVE (true)
        {
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

//geeft true als de koning van de gegeven kleur geen beweging kan maken
bool Game::kingStuck(zw kleur)
{
    for (int i = 0; i < 8; i++) // doorheen het bord gaan
    {
        for (int j = 0; j < 8; j++)
        {
            if (getPiece(i,j) != nullptr and getPiece(i,j)->getKleur() == kleur and getPiece(i,j)->ISkoning()) //als het stuk een koning is van de gegeven kleur
            {
                SchaakStuk* schaakStuk = getPiece(i,j);
                vector<pair<int,int>> geldigeZETTEN;
                geldigeZETTEN = schaakStuk->geldige_zetten(*this);

                for (pair<int,int> i : geldigeZETTEN) //doorheen de geldige zetten van dit stuk gaan
                {
                    if (valid_move(schaakStuk,i.first,i.second) == true)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true; //true WANNEER KONING GEEN ENKELE GELDIGE ZET HEEFT
}

//doet hetzelfde werk als move() maar verplaatst het stuk niet (wordt bij een if statement gebruikt)
bool Game::valid_move(SchaakStuk *s, int r, int k)
{
    pair<int,int> nieuwe_positie(r,k);

    SchaakStuk* schaakStuk = getPiece(r,k);

    pair<int,int> oude_positie(coordinaat(s));

    vector<pair<int,int>> geldigeZETTEN;
    geldigeZETTEN = s->geldige_zetten(*this);

    if (!geldigeZETTEN.empty()) // als er geldige zetten bestaan
    {
        for (pair<int,int> i : geldigeZETTEN) // doorheen de geldige zetten gaan
        {
            if (ISrokade(s,r,k) and !schaak(s->getKleur()))
            {
                if ((r == 7 and k == 6) and castle_wit == false and valid_move(s,7,5) == true)
                {
                    SchaakStuk* toren = getPiece(7,7);
                    setPiece(r,k,s);
                    setPiece(7,5, getPiece(7,7));
                    schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                    schaakbord[7][7] = nullptr;
                    if (schaak(getPiece(r,k)->getKleur()))
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[7][6] = schaakStuk;
                        schaakbord[7][7] = toren;
                        setPiece(7,5, nullptr);
                        return false;
                    }
                    else
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[7][6] = schaakStuk;
                        schaakbord[7][7] = toren;
                        setPiece(7,5, nullptr);
                        return true;
                    }
                }
                else if ((r == 7 and k == 2) and castle_long_wit == false and valid_move(s,7,3) == true)
                {
                    SchaakStuk* toren = getPiece(7,0);
                    setPiece(r,k,s);
                    setPiece(7,3, getPiece(7,0));
                    schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                    schaakbord[7][0] = nullptr;
                    if (schaak(getPiece(r,k)->getKleur()))
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[7][2] = schaakStuk;
                        schaakbord[7][0] = toren;
                        setPiece(7,3, nullptr);
                        return false;
                    }
                    else
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[7][2] = schaakStuk;
                        schaakbord[7][0] = toren;
                        setPiece(7,3, nullptr);
                        return true;
                    }
                }
                else if ((r == 0 and k == 6) and castle_zwart == false and valid_move(s,0,5) == true)
                {
                    SchaakStuk* toren = getPiece(0,7);
                    setPiece(r,k,s);
                    setPiece(0,5, getPiece(0,7));
                    schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                    schaakbord[0][7] = nullptr;
                    if (schaak(getPiece(r,k)->getKleur()))
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[0][6] = schaakStuk;
                        schaakbord[0][7] = toren;
                        setPiece(0,5, nullptr);
                        return false;
                    }
                    else
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[0][6] = schaakStuk;
                        schaakbord[0][7] = toren;
                        setPiece(0,5, nullptr);
                        return true;
                    }
                }
                else if ((r == 0 and k == 2) and castle_long_zwart == false and valid_move(s,0,3) == true)
                {
                    SchaakStuk* toren = getPiece(0,0);
                    setPiece(r,k,s);
                    setPiece(0,3, getPiece(0,0));
                    schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                    schaakbord[0][0] = nullptr;
                    if (schaak(getPiece(r,k)->getKleur()))
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[0][2] = schaakStuk;
                        schaakbord[0][0] = toren;
                        setPiece(0,3, nullptr);
                        return false;
                    }
                    else
                    {
                        setPiece(oude_positie.first,oude_positie.second,s);
                        schaakbord[0][2] = schaakStuk;
                        schaakbord[0][0] = toren;
                        setPiece(0,3, nullptr);
                        return true;
                    }
                }
            }
            else if (ISrokade(s,r,k) and schaak(s->getKleur()))
            {
                return false;
            }
            else if (i == nieuwe_positie) // als de nieuwe gevraagde positie geldig is -> verander dan de plaats ervan
            {
                setPiece(r,k,s);
                schaakbord[oude_positie.first][oude_positie.second] = nullptr;
                if (schaak(getPiece(r,k)->getKleur()))
                {
                    setPiece(oude_positie.first,oude_positie.second,s);
                    schaakbord[i.first][i.second] = schaakStuk;
                    return false;
                }
                else
                {
                    setPiece(oude_positie.first,oude_positie.second,s);
                    schaakbord[i.first][i.second] = schaakStuk;
                    return true;
                }
            }
        }
    }
    return false;
}

//geeft aan of de koning van de bepaalde kleur een rokade kan uitvoeren of niet
bool Game::ISrokade(SchaakStuk *s, int r, int k)
{
    pair<int,int> nieuwe_positie(r,k);

    vector<pair<int,int>> geldigeZETTEN;
    geldigeZETTEN = s->geldige_zetten(*this);

    if (!geldigeZETTEN.empty() and s->ISkoning() and (coordinaat(s).first == 7 and coordinaat(s).second == 4)) // als er geldige zetten bestaan
    {
        for (pair<int,int> i : geldigeZETTEN) // doorheen de geldige zetten gaan
        {
            if (i == nieuwe_positie and (i.first == 7 and i.second == 2) and getPiece(7,0) != nullptr) // als de nieuwe gevraagde positie geldig (rokade-postie) is -> verander dan de plaats ervan
            {
                return true;
            }
            else if (i == nieuwe_positie and (i.first == 7 and i.second == 6) and getPiece(7,7) != nullptr)
            {
                return true;
            }
        }
    }
    else if (!geldigeZETTEN.empty() and s->ISkoning() and (coordinaat(s).first == 0 and coordinaat(s).second == 4)) // als er geldige zetten bestaan
    {
        for (pair<int,int> i : geldigeZETTEN) // doorheen de geldige zetten gaan
        {
            if (i == nieuwe_positie and (i.first == 0 and i.second == 2) and getPiece(0,0) != nullptr) // als de nieuwe gevraagde positie geldig is -> verander dan de plaats ervan
            {
                return true;
            }
            else if (i == nieuwe_positie and (i.first == 0 and i.second == 6) and getPiece(0,7) != nullptr)
            {
                return true;
            }
        }
    }
    return false;
}

//wordt gebruikt bij undo; verplaatst het stuk terug naar zijn vorige positie
void Game::move_back(SchaakStuk* s)
{
    //ROKADE (terug koning en toren op hun oorspronkelijke plaats zetten)
    if (castle_wit == true)
    {
        //koning
        schaakbord[vorige_positie.first][vorige_positie.second] = s;
        schaakbord[volgende_posiitie.first][volgende_posiitie.second] = te_pakken_stuk;

        //toren
        schaakbord[7][7] = new Toren(wit);
        schaakbord[7][5] = nullptr;

        castle_wit = false;
    }
    else if (castle_long_wit == true)
    {
        //koning
        schaakbord[vorige_positie.first][vorige_positie.second] = s;
        schaakbord[volgende_posiitie.first][volgende_posiitie.second] = te_pakken_stuk;

        //toren
        schaakbord[7][0] = new Toren(wit);
        schaakbord[7][3] = nullptr;

        castle_long_wit = false;
    }
    else if (castle_zwart == true)
    {
        //koning
        schaakbord[vorige_positie.first][vorige_positie.second] = s;
        schaakbord[volgende_posiitie.first][volgende_posiitie.second] = te_pakken_stuk;

        //toren
        schaakbord[0][7] = new Toren(zwart);
        schaakbord[0][5] = nullptr;

        castle_zwart = false;
    }
    else if (castle_long_zwart == true)
    {
        //koning
        schaakbord[vorige_positie.first][vorige_positie.second] = s;
        schaakbord[volgende_posiitie.first][volgende_posiitie.second] = te_pakken_stuk;

        //toren
        schaakbord[0][0] = new Toren(zwart);
        schaakbord[0][3] = nullptr;

        castle_long_zwart = false;
    }
    else if (s->ISkoning() and s->getKleur() == wit and (castle_wit == true and castle_long_wit == true) and (coordinaat(s).first == 7 and coordinaat(s).second == 4))
    {
        schaakbord[vorige_positie.first][vorige_positie.second] = s;
        schaakbord[volgende_posiitie.first][volgende_posiitie.second] = te_pakken_stuk;

        castle_wit = false;
        castle_long_wit = false;
    }
    else if (s->ISkoning() and s->getKleur() == zwart and (castle_zwart == true and castle_long_zwart == true) and (coordinaat(s).first == 0 and coordinaat(s).second == 4))
    {
        schaakbord[vorige_positie.first][vorige_positie.second] = s;
        schaakbord[volgende_posiitie.first][volgende_posiitie.second] = te_pakken_stuk;

        castle_zwart = false;
        castle_long_zwart = false;
    }
    // REST
    else
    {
        schaakbord[vorige_positie.first][vorige_positie.second] = s;
        schaakbord[volgende_posiitie.first][volgende_posiitie.second] = te_pakken_stuk;
    }
}

//wordt gebruikt bij redo; verplaatst het stuk terug naar zijn positie voor dat undo uitgevoerd werd
void Game::redo_move(SchaakStuk *s)
{
    move(s,volgende_posiitie.first,volgende_posiitie.second);  //'VOLGENDE POSITIE' IS DE POSITIE VOOR UNDO
}

//geeft aan of het stuk en passant kan uitvoeren of niet
bool Game::en_passant(SchaakStuk *s)
{
    if (!s->ISpion()) //HET MOET EEN PION ZIJN
    {
        return false;
    }

    pair<int,int> positie(coordinaat(s));

    //WIT

    if (s->getKleur() == wit and positie.first == 3)
    {
        SchaakStuk* rechts_en_passant = getPiece(positie.first,positie.second + 1);
        SchaakStuk* links_en_passant = getPiece(positie.first,positie.second - 1);

        if (schaakstuk_bestaat(rechts_en_passant) and rechts_en_passant->ISpion() and rechts_en_passant->getKleur() != s->getKleur())
        {
            if (lege_vak(getPiece(positie.first - 1,positie.second + 1),positie.first - 1,positie.second + 1) and lege_vak(getPiece(positie.first - 2,positie.second + 1),positie.first - 2,positie.second + 1)) //als zijn verslaan-plaats leeg is en 1 hoger dan die verslaan-plaats ook leeg is
            {
                return true;
            }
        }
        else if (schaakstuk_bestaat(links_en_passant) and links_en_passant->ISpion() and links_en_passant->getKleur() != s->getKleur())
        {
            if (lege_vak(getPiece(positie.first - 1,positie.second - 1),positie.first - 1,positie.second - 1) and lege_vak(getPiece(positie.first - 2,positie.second - 1),positie.first - 2,positie.second - 1)) //als zijn verslaan-plaats leeg is en 1 hoger dan die verslaan-plaats ook leeg is
            {
                return true;
            }
        }
    }

    // ZWART

    else if (s->getKleur() == zwart and positie.first == 4)
    {

        SchaakStuk* rechts_en_passant = getPiece(positie.first,positie.second + 1);
        SchaakStuk* links_en_passant = getPiece(positie.first,positie.second - 1);

        if (schaakstuk_bestaat(rechts_en_passant) and rechts_en_passant->ISpion() and rechts_en_passant->getKleur() != s->getKleur())
        {
            if (lege_vak(getPiece(positie.first + 1,positie.second + 1),positie.first + 1,positie.second + 1) and lege_vak(getPiece(positie.first + 2,positie.second + 1),positie.first + 2,positie.second + 1)) //als zijn verslaan-plaats leeg is en 1 hoger dan die verslaan-plaats ook leeg is
            {
                return true;
            }
        }
        else if (schaakstuk_bestaat(links_en_passant) and links_en_passant->ISpion() and links_en_passant->getKleur() != s->getKleur())
        {
            if (lege_vak(getPiece(positie.first + 1,positie.second - 1),positie.first + 1,positie.second - 1) and lege_vak(getPiece(positie.first + 2,positie.second - 1),positie.first + 2,positie.second + 1)) //als zijn verslaan-plaats leeg is en 1 hoger dan die verslaan-plaats ook leeg is
            {
                return true;
            }
        }
    }
    return false;
}

//kijkt of een pion 1 keer van zijn start positie naar 1 rij hoger komt,
// dan schakelt deze functie de en-passant mogelijkheid op die kolom uit
void Game::en_passantOFF(SchaakStuk *s, int r, int k)
{
    pair<int,int> nieuwe_positie(r,k);

    pair<int,int> oude_positie(coordinaat(s));

    if (s->ISpion() and s->getKleur() == zwart and en_passantWIT == false) //ZWART
    {
        if (oude_positie.first == 1) //BIJ ELKE KOLOM KIJKEN OF DAT DE PION 1 PLAATS HOGER HEEFT OPGESCHOVEN VANAF ZIJN OORSPR. PLAATS
        {
            en_passantOFFGEM(oude_positie.second,0,r,oude_positie.first + 1,kol0zwart);
            en_passantOFFGEM(oude_positie.second,1,r,oude_positie.first + 1,kol1zwart);
            en_passantOFFGEM(oude_positie.second,2,r,oude_positie.first + 1,kol2zwart);
            en_passantOFFGEM(oude_positie.second,3,r,oude_positie.first + 1,kol3zwart);
            en_passantOFFGEM(oude_positie.second,4,r,oude_positie.first + 1,kol4zwart);
            en_passantOFFGEM(oude_positie.second,5,r,oude_positie.first + 1,kol5zwart);
            en_passantOFFGEM(oude_positie.second,6,r,oude_positie.first + 1,kol6zwart);
            en_passantOFFGEM(oude_positie.second,7,r,oude_positie.first + 1,kol7zwart);
        }
    }
    if (s->ISpion() and s->getKleur() == wit and en_passantZWART == false) //WIT
    {
        if (oude_positie.first == 6)
        {
            en_passantOFFGEM(oude_positie.second,0,r,oude_positie.first - 1,kol0wit);
            en_passantOFFGEM(oude_positie.second,1,r,oude_positie.first - 1,kol1wit);
            en_passantOFFGEM(oude_positie.second,2,r,oude_positie.first - 1,kol2wit);
            en_passantOFFGEM(oude_positie.second,3,r,oude_positie.first - 1,kol3wit);
            en_passantOFFGEM(oude_positie.second,4,r,oude_positie.first - 1,kol4wit);
            en_passantOFFGEM(oude_positie.second,5,r,oude_positie.first - 1,kol5wit);
            en_passantOFFGEM(oude_positie.second,6,r,oude_positie.first - 1,kol6wit);
            en_passantOFFGEM(oude_positie.second,7,r,oude_positie.first - 1,kol7wit);
        }
    }
}

//als er een en-passant mogelijkheid is en het stuk toch geen en-passant move gaat doen,
//dan kan je geen en-passant meer doen op die kolom
void Game::geen_en_passantOFF(SchaakStuk *s, int r, int k)
{
    pair<int,int> nieuwe_positie(r,k);

    pair<int,int> oude_positie(coordinaat(s));

    SchaakStuk* rechterstuk = getPiece(oude_positie.first,oude_positie.second + 1);
    pair<int,int> rechterstuk_positie(oude_positie.first,oude_positie.second + 1);

    SchaakStuk* linkerstuk = getPiece(oude_positie.first,oude_positie.second - 1);
    pair<int,int> linkerstuk_positie(oude_positie.first,oude_positie.second - 1);

    if (en_passant(s) and schaakstuk_bestaat(rechterstuk) and rechterstuk != nullptr and rechterstuk->ISpion() and rechterstuk->getKleur() != s->getKleur())
    {
        geen_en_passantOFFGEM(s, oude_positie.second, 0, k, oude_positie.second + 1, kol1zwart, kol1wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 1, k, oude_positie.second + 1, kol2zwart, kol2wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 2, k, oude_positie.second + 1, kol3zwart, kol3wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 3, k, oude_positie.second + 1, kol4zwart, kol4wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 4, k, oude_positie.second + 1, kol5zwart, kol5wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 5, k, oude_positie.second + 1, kol6zwart, kol6wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 6, k, oude_positie.second + 1, kol7zwart, kol7wit);
    }
    else if (en_passant(s) and schaakstuk_bestaat(linkerstuk) and linkerstuk != nullptr and linkerstuk->ISpion() and linkerstuk->getKleur() != s->getKleur())
    {
        geen_en_passantOFFGEM(s, oude_positie.second, 1, k, oude_positie.second - 1, kol0zwart, kol0wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 2, k, oude_positie.second - 1, kol1zwart, kol1wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 3, k, oude_positie.second - 1, kol2zwart, kol2wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 4, k, oude_positie.second - 1, kol3zwart, kol3wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 5, k, oude_positie.second - 1, kol4zwart, kol4wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 6, k, oude_positie.second - 1, kol5zwart, kol5wit);
        geen_en_passantOFFGEM(s, oude_positie.second, 7, k, oude_positie.second - 1, kol6zwart, kol6wit);
    }
}

//als er een en-passant mogelijkheid is en het stuk toch geen en-passant move gaat doen,
//maar een andere stuk van hetzelfde kleur beweegt, en-passant gaat dan niet meer op die bepaalde kolom
void Game::en_passant_checken(SchaakStuk *s)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {   //checken of dat er al een en passant vorm ligt op het bord van de gegeven kleur
            if (getPiece(i,j) != nullptr and en_passant(getPiece(i,j)) and getPiece(i,j) != s and getPiece(i,j)->getKleur() == s->getKleur())
            {
                SchaakStuk* rechterstuk = getPiece(i,j + 1);
                pair<int,int> rechterstuk_positie(i,j + 1);
                //KIJKEN WELKE RICHTING EN PASSANT UITGEVOERD WORDT (zodat ik weet welke en-passant op welke kolom false moet worden)
                if (schaakstuk_bestaat(rechterstuk) and rechterstuk != nullptr and rechterstuk->ISpion() and rechterstuk->getKleur() != s->getKleur())
                {
                    en_passant_checkenGEM(s,j+1,1,kol1zwart,kol1wit);
                    en_passant_checkenGEM(s,j+1,2,kol2zwart,kol2wit);
                    en_passant_checkenGEM(s,j+1,3,kol3zwart,kol3wit);
                    en_passant_checkenGEM(s,j+1,4,kol4zwart,kol4wit);
                    en_passant_checkenGEM(s,j+1,5,kol5zwart,kol5wit);
                    en_passant_checkenGEM(s,j+1,6,kol6zwart,kol6wit);
                    en_passant_checkenGEM(s,j+1,7,kol7zwart,kol7wit);
                }

                SchaakStuk* linkerstuk = getPiece(i,j - 1);
                pair<int,int> linkerstuk_positie(i,j - 1);

                if (schaakstuk_bestaat(linkerstuk) and linkerstuk != nullptr and linkerstuk->ISpion() and linkerstuk->getKleur() != s->getKleur())
                {
                    en_passant_checkenGEM(s,j-1,0,kol0zwart,kol0wit);
                    en_passant_checkenGEM(s,j-1,1,kol1zwart,kol1wit);
                    en_passant_checkenGEM(s,j-1,2,kol2zwart,kol2wit);
                    en_passant_checkenGEM(s,j-1,3,kol3zwart,kol3wit);
                    en_passant_checkenGEM(s,j-1,4,kol4zwart,kol4wit);
                    en_passant_checkenGEM(s,j-1,5,kol5zwart,kol5wit);
                    en_passant_checkenGEM(s,j-1,6,kol6zwart,kol6wit);
                }
            }
        }
    }
}

//als een pion 2 naar voor komt en als er geen pion naast hem ligt,
//dan kan je geen en-passant meer uitvoeren op die kolom
void Game::en_passantOFF2hoger(SchaakStuk *s, int r, int k)
{
    pair<int,int> nieuwe_positie(r,k);

    pair<int,int> oude_positie(coordinaat(s));

    if (s->ISpion() and s->getKleur() == zwart)
    {
        if (oude_positie.first == 1 and r == 3)
        {
            SchaakStuk* rechterstuk = getPiece(r,k + 1);
            SchaakStuk* linkerstuk = getPiece(r,k - 1);
            if (oude_positie.second == 0)
            {
                if (rechterstuk == nullptr or !rechterstuk->ISpion())
                {
                    kol0zwart = true;
                }
            }
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,1,kol1zwart);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,2,kol2zwart);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,3,kol3zwart);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,4,kol4zwart);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,5,kol5zwart);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,6,kol6zwart);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,7,kol7zwart);
            if (oude_positie.second == 7)
            {
                if (linkerstuk == nullptr or !linkerstuk->ISpion())
                {
                    kol7zwart = true;
                }
            }
        }
    }
    if (s->ISpion() and s->getKleur() == wit)
    {
        SchaakStuk* rechterstuk = getPiece(r,k + 1);
        SchaakStuk* linkerstuk = getPiece(r,k - 1);
        if (oude_positie.first == 6 and r == 4)
        {
            if (oude_positie.second == 0)
            {
                if (rechterstuk == nullptr or !rechterstuk->ISpion())
                {
                    kol0wit = true;
                }
            }
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,1,kol1wit);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,2,kol2wit);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,3,kol3wit);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,4,kol4wit);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,5,kol5wit);
            en_passantOFF2hogerGEM(linkerstuk,rechterstuk,oude_positie.second,6,kol6wit);
            if (oude_positie.second == 7)
            {
                if ((linkerstuk == nullptr or !linkerstuk->ISpion()))
                {
                    kol7wit = true;
                }
            }
        }
    }
}

//de volgende 4 functies laten de gegeven stukken promoveren (veranderen) naar de aangekozen nieuwe stuk bij promotie
void Game::promotiePAARD(SchaakStuk *stuk)
{
    SchaakStuk* paard = new Paard(stuk->getKleur());
    schaakbord[coordinaat(stuk).first][ coordinaat(stuk).second] = paard;
}

void Game::promotieKONINGIN(SchaakStuk *stuk)
{
    SchaakStuk* koningin = new Koningin(stuk->getKleur());
    schaakbord[coordinaat(stuk).first][ coordinaat(stuk).second] = koningin;
}

void Game::promotieLOPER(SchaakStuk *stuk)
{
    SchaakStuk* loper = new Loper(stuk->getKleur());
    schaakbord[coordinaat(stuk).first][ coordinaat(stuk).second] = loper;
}

void Game::promotieTOREN(SchaakStuk *stuk)
{
    SchaakStuk* toren = new Toren(stuk->getKleur());
    schaakbord[coordinaat(stuk).first][ coordinaat(stuk).second] = toren;
}

// gaat het bord leeg maken voor newGame
void Game::clearSchaakBord()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            schaakbord[i][j] = nullptr;
        }
    }
}

bool Game::lege_vak(SchaakStuk* schaakStuk,int x, int y)
{
    if ((x < 8 and y < 8) and (x >= 0 and y >=0))
    {
        if (schaakStuk == nullptr)
        {
            return true;
        }
    }
    return false;
}

void Game::en_passant_checkenGEM(SchaakStuk *s, int j, int k, bool &kol_zwart,bool &kol_wit)
{
    if (j == k)
    {
        if (s->getKleur() == wit)
        {
            kol_zwart = true;
        }
        else if (s->getKleur() == zwart)
        {
            kol_wit = true;
        }
    }
}

void Game::geen_en_passantOFFGEM(SchaakStuk *s, int oude_pos1, int col, int k, int oude_pos2, bool &kol_zwart, bool &kol_wit)
{
    if (oude_pos1 == col and k != oude_pos2 + 1)
    {
        if (s->getKleur() == wit)
        {
            kol_zwart = true;
        }
        else if (s->getKleur() == zwart)
        {
            kol_wit = true;
        }
    }
}

void Game::en_passantOFF2hogerGEM(SchaakStuk *linkerstuk, SchaakStuk *rechterstuk, int oude_pos, int k, bool &kol_kleur)
{
    if (oude_pos == k)
    {
        if ((linkerstuk == nullptr or !linkerstuk->ISpion()) and (rechterstuk == nullptr or !rechterstuk->ISpion()))
        {
            kol_kleur = true;
        }
    }
}

void Game::en_passantOFFGEM(int oude_pos1, int col, int r, int oude_pos2, bool &kol_kleur)
{
    if (oude_pos1 == col and r == oude_pos2)
    {
        kol_kleur = true;
    }
}

