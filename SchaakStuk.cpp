//  Student: Abobaker Rahman
//  Rolnummer: 2022825
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"
#include <functional>

//-----------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//
//                                              PION

vector<pair<int, int>> Pion::geldige_zetten(Game &game) const {

    //(pion_zetten had ik vergeten overal aan te passen bij andere klasse schaakstukken)
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    pair<int,int> coordinaat(game.coordinaat(this));   //coordinaat van het gegeven schaakstuk (this)

    // EN PASSANT

    //WIT

    if (this->getKleur() == wit and coordinaat.first == 3 and game.en_passantWIT == false)
    {
        SchaakStuk* rechts_en_passant = game.getPiece(coordinaat.first,coordinaat.second + 1);
        SchaakStuk* links_en_passant = game.getPiece(coordinaat.first,coordinaat.second - 1);

        if (game.schaakstuk_bestaat(rechts_en_passant) and rechts_en_passant->ISpion() and rechts_en_passant->getKleur() != this->getKleur()) //kjken naar rechts en passant verslaan
        {
            if (coordinaat.second == 0 and game.kol1zwart == false) //kol1zwart = true betekent dat zwart zijn pion al 1tje verschoven heeft dus en passent gaat niet meer op dit pion
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1, coordinaat.first - 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 2 and game.kol3zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1, coordinaat.first - 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 4 and game.kol5zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1, coordinaat.first - 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 6 and game.kol7zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1, coordinaat.first - 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 1 and game.kol2zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1, coordinaat.first - 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 3 and game.kol4zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1, coordinaat.first - 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 5 and game.kol6zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1, coordinaat.first - 2,coordinaat.second + 1);
            }
        }
        if (game.schaakstuk_bestaat(links_en_passant) and links_en_passant->ISpion() and links_en_passant->getKleur() != this->getKleur()) //kjken naar links en passant verslaan
        {
            if (coordinaat.second == 1 and game.kol0zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1, coordinaat.first - 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 2 and game.kol1zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1, coordinaat.first - 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 3 and game.kol2zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1, coordinaat.first - 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 4 and game.kol3zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1, coordinaat.first - 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 5 and game.kol4zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1, coordinaat.first - 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 6 and game.kol5zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1, coordinaat.first - 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 7 and game.kol6zwart == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1, coordinaat.first - 2,coordinaat.second - 1);
            }
        }
    }

    //ZWART

    if (this->getKleur() == zwart and coordinaat.first == 4 and game.en_passantZWART == false)
    {

        SchaakStuk* rechts_en_passant = game.getPiece(coordinaat.first,coordinaat.second + 1);
        SchaakStuk* links_en_passant = game.getPiece(coordinaat.first,coordinaat.second - 1);


        if (game.schaakstuk_bestaat(rechts_en_passant) and rechts_en_passant->ISpion() and rechts_en_passant->getKleur() != this->getKleur())
        {
            if (coordinaat.second == 0 and game.kol1wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1, coordinaat.first + 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 1 and game.kol2wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1, coordinaat.first + 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 2 and game.kol3wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1, coordinaat.first + 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 3 and game.kol4wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1, coordinaat.first + 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 4 and game.kol5wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1, coordinaat.first + 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 5 and game.kol6wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1, coordinaat.first + 2,coordinaat.second + 1);
            }
            else if (coordinaat.second == 6 and game.kol7wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1, coordinaat.first + 2,coordinaat.second + 1);
            }
        }
        if (game.schaakstuk_bestaat(links_en_passant) and links_en_passant->ISpion() and links_en_passant->getKleur() != this->getKleur())
        {
            if (coordinaat.second == 1 and game.kol0wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1, coordinaat.first + 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 2 and game.kol1wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1, coordinaat.first + 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 3 and game.kol2wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1, coordinaat.first + 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 4 and game.kol3wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1, coordinaat.first + 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 5 and game.kol4wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1, coordinaat.first + 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 6 and game.kol5wit == false)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1, coordinaat.first + 2,coordinaat.second - 1);
            }
            else if (coordinaat.second == 7 and !game.kol6wit)
            {
                voegEnPassant(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1, coordinaat.first + 2,coordinaat.second - 1);
            }
        }
    }

    // REST
    if (this->getKleur() == zwart)
    {
        if (game.schaakstuk_bestaat(game.getPiece(coordinaat.first + 1,coordinaat.second)) or game.lege_vak(game.getPiece(coordinaat.first + 1,coordinaat.second),coordinaat.first + 1,coordinaat.second)) //als het schaakstuk boven dit pion (this) bestaat of leeg is
        {
            free_square(game,pion_zetten,coordinaat.first + 1,coordinaat.second);
        }

        if (coordinaat.first == 1)        //als het pion of zijn originele plaats staat
        {
            if (game.schaakstuk_bestaat(game.getPiece(coordinaat.first + 2,coordinaat.second)) or game.lege_vak(game.getPiece(coordinaat.first + 2,coordinaat.second),coordinaat.first + 2,coordinaat.second)) //als het schaakstuk 2 plaatsen hoger dan dit pion (this) bestaat of leeg is
            {
                if (game.lege_vak(game.getPiece(coordinaat.first + 1,coordinaat.second),coordinaat.first + 1,coordinaat.second))
                {
                    free_square(game,pion_zetten,coordinaat.first + 2,coordinaat.second);
                }
            }
        }

        if (game.schaakstuk_bestaat(game.getPiece(coordinaat.first + 1,coordinaat.second + 1))) //als het schaakstuk rechts boven van dit pion (this) bestaat
        {
            color_different(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1);
        }

        if (game.schaakstuk_bestaat(game.getPiece(coordinaat.first + 1,coordinaat.second - 1)))//als het schaakstuk links boven van dit pion (this) bestaat
        {
            color_different(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1);
        }
    }
    else if (this->getKleur() == wit)
    {
        if (game.schaakstuk_bestaat(game.getPiece(coordinaat.first - 1,coordinaat.second)) or game.lege_vak(game.getPiece(coordinaat.first - 1,coordinaat.second),coordinaat.first - 1,coordinaat.second)) //als het schaakstuk boven dit pion (this) bestaat of leeg is
        {
            free_square(game,pion_zetten,coordinaat.first - 1,coordinaat.second);
        }

        if (coordinaat.first == 6)        //als het pion of zijn originele plaats staat
        {
            if (game.schaakstuk_bestaat(game.getPiece(coordinaat.first - 2,coordinaat.second)) or game.lege_vak(game.getPiece(coordinaat.first - 2,coordinaat.second),coordinaat.first - 2,coordinaat.second)) //als het schaakstuk 2 plaatsen hoger dan dit pion (this) bestaat of leeg is
            {
                if (game.lege_vak(game.getPiece(coordinaat.first - 1,coordinaat.second),coordinaat.first - 1,coordinaat.second))
                {
                    free_square(game,pion_zetten,coordinaat.first - 2,coordinaat.second);
                }
            }
        }

        if (game.schaakstuk_bestaat(game.getPiece(coordinaat.first - 1,coordinaat.second - 1))) //als het schaakstuk links boven van dit pion (this) bestaat
        {
            color_different(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1);
        }

        if (game.schaakstuk_bestaat(game.getPiece(coordinaat.first - 1,coordinaat.second + 1)))//als het schaakstuk rechts boven van dit pion (this) bestaat
        {
            color_different(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1);
        }
    }
    return pion_zetten;
}

bool Pion::ISkoning() const
{
    return false;
}

bool Pion::ISpion() const {
    return true;
}

vector<pair<int, int>> Pion::verslaan(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    pair<int,int> coordinaat(game.coordinaat(this));   //coordinaat van het gegeven schaakstuk (this)

    if (this->getKleur() == zwart)
    {
        if ((coordinaat.first + 1 < 8 and coordinaat.second + 1 < 8) and (coordinaat.first + 1 >= 0 and coordinaat.second + 1 >=0))
        {
            pair<int,int> rechts(coordinaat.first + 1,coordinaat.second + 1);   // voeg dan die coordinaat toe in vector pion_zetten
            pion_zetten.push_back(rechts);
        }
        if ((coordinaat.first + 1 < 8 and coordinaat.second - 1 < 8) and (coordinaat.first + 1 >= 0 and coordinaat.second - 1 >=0))
        {
            pair<int,int> links(coordinaat.first + 1,coordinaat.second - 1);   // voeg dan die coordinaat toe in vector pion_zetten
            pion_zetten.push_back(links);
        }
    }
    else if (this->getKleur() == wit)
    {
        if ((coordinaat.first - 1 < 8 and coordinaat.second - 1 < 8) and (coordinaat.first - 1 >= 0 and coordinaat.second - 1 >=0))
        {
            pair<int,int> rechts(coordinaat.first - 1,coordinaat.second - 1);   // voeg dan die coordinaat toe in vector pion_zetten
            pion_zetten.push_back(rechts);
        }
        if ((coordinaat.first - 1 < 8 and coordinaat.second + 1 < 8) and (coordinaat.first - 1 >= 0 and coordinaat.second + 1 >=0))
        {
            pair<int,int> links(coordinaat.first - 1,coordinaat.second + 1);   // voeg dan die coordinaat toe in vector pion_zetten
            pion_zetten.push_back(links);
        }
    }
    return pion_zetten;
}

bool Pion::IStoren() const {
    return false;
}

bool Pion::ISpaard() const {
    return false;
}

bool Pion::ISkoningin() const {
    return false;
}

bool Pion::ISloper() const {
    return false;
}

//-----------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//
//                                             TOREN

vector<pair<int, int>> Toren::geldige_zetten(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    meervakken(game,pion_zetten,"+","none");
    meervakken(game,pion_zetten,"none","+");
    meervakken(game,pion_zetten,"none","-");
    meervakken(game,pion_zetten,"-","none");

    return pion_zetten;
}

bool Toren::ISkoning() const {
    return false;
}

bool Toren::ISpion() const {
    return false;
}

vector<pair<int, int>> Toren::verslaan(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    meervakkenVERSLAAN(game,pion_zetten,"+","none");
    meervakkenVERSLAAN(game,pion_zetten,"none","+");
    meervakkenVERSLAAN(game,pion_zetten,"none","-");
    meervakkenVERSLAAN(game,pion_zetten,"-","none");

    return pion_zetten;
}

bool Toren::IStoren() const {
    return true;
}

bool Toren::ISpaard() const {
    return false;
}

bool Toren::ISkoningin() const {
    return false;
}

bool Toren::ISloper() const {
    return false;
}

//-----------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//
//                                           KONING

vector<pair<int, int>> Koning::geldige_zetten(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    pair<int,int> coordinaat(game.coordinaat(this));   //coordinaat van het gegeven schaakstuk (this)

    //ROKADE
    //wit
    if (this->getKleur() == wit and (coordinaat.first == 7 and coordinaat.second == 4))
    {
        if (game.getPiece(7,7) != nullptr and game.getPiece(7,7)->IStoren())
        {
            if (game.getPiece(7,5) == nullptr and game.getPiece(7,6) == nullptr)
            {
                pair<int,int> voor(7,6);   // voeg dan die coordinaat toe in vector pion_zetten
                pion_zetten.push_back(voor);
            }
        }
        if (game.getPiece(7,0) != nullptr and game.getPiece(7,0)->IStoren())
        {
            if (game.getPiece(7,1) == nullptr and game.getPiece(7,2) == nullptr and game.getPiece(7,3) == nullptr)
            {
                pair<int,int> voor(7,2);   // voeg dan die coordinaat toe in vector pion_zetten
                pion_zetten.push_back(voor);
            }
        }
    }
    //ROKADE
    //zwart
    if (this->getKleur() == zwart and (coordinaat.first == 0 and coordinaat.second == 4))
    {
        if (game.getPiece(0,7) != nullptr and game.getPiece(0,7)->IStoren())
        {
            if (game.getPiece(0,5) == nullptr and game.getPiece(0,6) == nullptr)
            {
                pair<int,int> voor(0,6);   // voeg dan die coordinaat toe in vector pion_zetten
                pion_zetten.push_back(voor);
            }
        }
        if (game.getPiece(0,0) != nullptr and game.getPiece(0,0)->IStoren())
        {
            if (game.getPiece(0,1) == nullptr and game.getPiece(0,2) == nullptr and game.getPiece(0,3) == nullptr)
            {
                pair<int,int> voor(0,2);   // voeg dan die coordinaat toe in vector pion_zetten
                pion_zetten.push_back(voor);
            }
        }
    }
    //NAAR VOOR
    voeg_toe(game,pion_zetten,coordinaat.first + 1,coordinaat.second);
    //NAAR LINKS
    voeg_toe(game,pion_zetten,coordinaat.first,coordinaat.second + 1);
    //NAAR RECHTS
    voeg_toe(game,pion_zetten,coordinaat.first,coordinaat.second - 1);
    //NAAR ACHTER
    voeg_toe(game,pion_zetten,coordinaat.first - 1,coordinaat.second);

    //diagonaal links naar boven
    voeg_toe(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1);

    //diagonaal rechts naar boven
    voeg_toe(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1);

    //diagonaal rechts naar onder
    voeg_toe(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1);

    //diagonaal links naar onder
    voeg_toe(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1);

    return pion_zetten;
}

bool Koning::ISkoning() const
{
    return true;
}

bool Koning::ISpion() const {
    return false;
}

vector<pair<int, int>> Koning::verslaan(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    pair<int,int> coordinaat(game.coordinaat(this));   //coordinaat van het gegeven schaakstuk (this)

    //NAAR VOOR
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first + 1,coordinaat.second);
    //NAAR LINKS
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first,coordinaat.second + 1);
    //NAAR RECHTS
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first,coordinaat.second - 1);
    //NAAR ACHTER
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first - 1,coordinaat.second);

    //diagonaal links naar boven
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 1);

    //diagonaal rechts naar boven
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 1);

    //diagonaal rechts naar onder
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 1);

    //diagonaal links naar onder
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 1);

    return pion_zetten;
}

bool Koning::IStoren() const {
    return false;
}

bool Koning::ISpaard() const {
    return false;
}

bool Koning::ISkoningin() const {
    return false;
}

bool Koning::ISloper() const {
    return false;
}

//-----------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//
//                                          LOPER

vector<pair<int, int>> Loper::geldige_zetten(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden


    meervakken(game,pion_zetten,"+","+");
    meervakken(game,pion_zetten,"+","-");
    meervakken(game,pion_zetten,"-","-");
    meervakken(game,pion_zetten,"-","+");
    return pion_zetten;
}

bool Loper::ISkoning() const {
    return false;
}

bool Loper::ISpion() const {
    return false;
}

vector<pair<int, int>> Loper::verslaan(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    meervakkenVERSLAAN(game,pion_zetten,"+","+");
    meervakkenVERSLAAN(game,pion_zetten,"+","-");
    meervakkenVERSLAAN(game,pion_zetten,"-","-");
    meervakkenVERSLAAN(game,pion_zetten,"-","+");
    return pion_zetten;
}

bool Loper::IStoren() const {
    return false;
}

bool Loper::ISpaard() const {
    return false;
}

bool Loper::ISkoningin() const {
    return false;
}

bool Loper::ISloper() const {
    return true;
}

//-----------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//
//                                             KONINGIN

vector<pair<int, int>> Koningin::geldige_zetten(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden


    //----------------HORIZONTAAL EN VERTICAAL----------------------------//
    //--------------------------------------------------------------------//

    meervakken(game,pion_zetten,"+","none");
    meervakken(game,pion_zetten,"none","+");
    meervakken(game,pion_zetten,"none","-");
    meervakken(game,pion_zetten,"-","none");

    //------------------DIAGONAAL---------------------------//
    //------------------------------------------------------//

    meervakken(game,pion_zetten,"+","+");
    meervakken(game,pion_zetten,"+","-");
    meervakken(game,pion_zetten,"-","-");
    meervakken(game,pion_zetten,"-","+");

    return pion_zetten;
}

bool Koningin::ISkoning() const {
    return false;
}

bool Koningin::ISpion() const {
    return false;
}

vector<pair<int, int>> Koningin::verslaan(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden


    //----------------HORIZONTAAL EN VERTICAAL----------------------------//
    //--------------------------------------------------------------------//

    meervakkenVERSLAAN(game,pion_zetten,"+","none");
    meervakkenVERSLAAN(game,pion_zetten,"none","+");
    meervakkenVERSLAAN(game,pion_zetten,"none","-");
    meervakkenVERSLAAN(game,pion_zetten,"-","none");

    //------------------DIAGONAAL---------------------------//
    //------------------------------------------------------//

    meervakkenVERSLAAN(game,pion_zetten,"+","+");
    meervakkenVERSLAAN(game,pion_zetten,"+","-");
    meervakkenVERSLAAN(game,pion_zetten,"-","-");
    meervakkenVERSLAAN(game,pion_zetten,"-","+");

    return pion_zetten;
}

bool Koningin::IStoren() const {
    return false;
}

bool Koningin::ISpaard() const {
    return false;
}

bool Koningin::ISkoningin() const {
    return true;
}

bool Koningin::ISloper() const {
    return false;
}

vector<pair<int, int>> Paard::geldige_zetten(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    pair<int,int> coordinaat(game.coordinaat(this));   //coordinaat van het gegeven schaakstuk (this)


    //NAAR LINKS->VOOR->HOOG
    voeg_toe(game,pion_zetten,coordinaat.first + 2,coordinaat.second + 1);
    //NAAR RECHTS->VOOR->HOOG
    voeg_toe(game,pion_zetten,coordinaat.first + 2,coordinaat.second - 1);

    //NAAR RECHTS->ACHTER->LAAG
    voeg_toe(game,pion_zetten,coordinaat.first - 2,coordinaat.second - 1);
    //NAAR LINKS->ACHTER->LAAG
    voeg_toe(game,pion_zetten,coordinaat.first - 2,coordinaat.second + 1);
    //NAAR LINKS->VOOR->NAAST
    voeg_toe(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 2);
    //NAAR LINKS->ACHTER->NAAST
    voeg_toe(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 2);

    //NAAR RECHTS->ACHTER->NAAST
    voeg_toe(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 2);

    //NAAR RECHTS->ACHTER->NAAST
    voeg_toe(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 2);

    return pion_zetten;
}

//-----------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//
//                                             PAARD

bool Paard::ISkoning() const {
    return false;
}

bool Paard::ISpion() const {
    return false;
}

vector<pair<int, int>> Paard::verslaan(Game &game) const
{
    vector<pair<int, int>> pion_zetten; //vector die uiteindelijk gereturned moet worden

    pair<int,int> coordinaat(game.coordinaat(this));   //coordinaat van het gegeven schaakstuk (this)


    //NAAR LINKS->VOOR->HOOG
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first + 2,coordinaat.second + 1);
    //NAAR RECHTS->VOOR->HOOG
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first + 2,coordinaat.second - 1);

    //NAAR RECHTS->ACHTER->LAAG
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first - 2,coordinaat.second - 1);
    //NAAR LINKS->ACHTER->LAAG
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first - 2,coordinaat.second + 1);
    //NAAR LINKS->VOOR->NAAST
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first + 1,coordinaat.second + 2);
    //NAAR LINKS->ACHTER->NAAST
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first - 1,coordinaat.second + 2);

    //NAAR RECHTS->ACHTER->NAAST
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first - 1,coordinaat.second - 2);

    //NAAR RECHTS->ACHTER->NAAST
    voeg_toeVERSLAAN(game,pion_zetten,coordinaat.first + 1,coordinaat.second - 2);

    return pion_zetten;
}

bool Paard::IStoren() const {
    return false;
}

bool Paard::ISpaard() const {
    return true;
}

bool Paard::ISkoningin() const {
    return false;
}

bool Paard::ISloper() const {
    return false;
}

//-----------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//
//                                 GEMEENSCHAPPELIJKE FUNCTIES

void SchaakStuk::free_square(Game &game, vector<pair<int, int>> &zetten, int x, int y) const
{
    if (game.lege_vak(game.getPiece(x,y),x,y))
    {
        voeg_aan_vector(game,zetten,x,y);
    }
}

void SchaakStuk::color_different(Game &game, vector<pair<int, int>> &zetten, int x, int y) const
{
    if (game.getPiece(x,y)->getKleur() != this->getKleur()) //als de kleur verschillend is (bij een schaakstuk)
    {
        voeg_aan_vector(game,zetten,x,y);
    }
}

void SchaakStuk::meervakken(Game &game, vector<pair<int, int>> &zetten, const string op1, const string op2) const
{

    pair<int,int> coordinaat(game.coordinaat(this));   //coordinaat van het gegeven schaakstuk (this)

    pair<int,int> nieuwe_coordinaat(game.coordinaat(this));

    function<int(int, int)> add = plus<int>();
    function<int(int, int)> min = minus<int>();


    for (int i = 1; i < 8; i++)
    {
        if (op1 == "+")
        {
            nieuwe_coordinaat.first = add(nieuwe_coordinaat.first,i);
        }
        else if (op1 == "-")
        {
            nieuwe_coordinaat.first = min(nieuwe_coordinaat.first,i);
        }
        if (op2 == "+")
        {
            nieuwe_coordinaat.second = add(nieuwe_coordinaat.second,i);
        }
        else if (op2 == "-")
        {
            nieuwe_coordinaat.second = min(nieuwe_coordinaat.second,i);
        }
        SchaakStuk* nieuwpiece = game.getPiece(nieuwe_coordinaat.first, nieuwe_coordinaat.second);
        if (game.schaakstuk_bestaat(nieuwpiece) or game.lege_vak(nieuwpiece,nieuwe_coordinaat.first, nieuwe_coordinaat.second)) //als het schaakstuk boven dit koningin (this) bestaat of leeg is
        {
            if (game.getPiece(nieuwe_coordinaat.first, nieuwe_coordinaat.second) == nullptr)
            {
                voeg_aan_vector(game,zetten,nieuwe_coordinaat.first , nieuwe_coordinaat.second);
            }
            else if (game.getPiece(nieuwe_coordinaat.first, nieuwe_coordinaat.second)->getKleur() != this->getKleur()) //als de kleur verschillend is (bij een schaakstuk)
            {
                voeg_aan_vector(game,zetten,nieuwe_coordinaat.first , nieuwe_coordinaat.second);
                break;
            }
            else if (game.getPiece(nieuwe_coordinaat.first, nieuwe_coordinaat.second)->getKleur() == this->getKleur())
            {
                break;
            }
        }
        nieuwe_coordinaat = coordinaat;
    }
}

void SchaakStuk::voeg_toe(Game &game,vector<pair<int, int>> &zetten, int x, int y) const
{
    if (game.schaakstuk_bestaat(game.getPiece(x,y)) or game.lege_vak(game.getPiece(x,y),x,y)) //als het schaakstuk boven dit koningin (this) bestaat of leeg is
    {
        if (game.getPiece(x,y) == nullptr)
        {
            voeg_aan_vector(game,zetten,x,y);
        }
        else if (game.getPiece(x,y)->getKleur() != this->getKleur()) //als de kleur verschillend is (bij een schaakstuk)
        {
            voeg_aan_vector(game,zetten,x,y);
        }
    }
}

void SchaakStuk::meervakkenVERSLAAN(Game &game, vector<pair<int, int>> &zetten, const string op1, const string op2) const
{
    pair<int,int> coordinaat(game.coordinaat(this));   //coordinaat van het gegeven schaakstuk (this)

    pair<int,int> nieuwe_coordinaat(game.coordinaat(this));

    function<int(int, int)> add = plus<int>();
    function<int(int, int)> min = minus<int>();


    for (int i = 1; i < 8; i++)
    {
        if (op1 == "+")
        {
            nieuwe_coordinaat.first = add(nieuwe_coordinaat.first,i);
        }
        else if (op1 == "-")
        {
            nieuwe_coordinaat.first = min(nieuwe_coordinaat.first,i);
        }
        if (op2 == "+")
        {
            nieuwe_coordinaat.second = add(nieuwe_coordinaat.second,i);
        }
        else if (op2 == "-")
        {
            nieuwe_coordinaat.second = min(nieuwe_coordinaat.second,i);
        }
        if (game.schaakstuk_bestaat(game.getPiece(nieuwe_coordinaat.first , nieuwe_coordinaat.second)) or game.lege_vak(game.getPiece(nieuwe_coordinaat.first, nieuwe_coordinaat.second),nieuwe_coordinaat.first, nieuwe_coordinaat.second)) //als het schaakstuk boven dit koningin (this) bestaat of leeg is
        {
            if (game.getPiece(nieuwe_coordinaat.first, nieuwe_coordinaat.second) == nullptr)
            {
                voeg_aan_vector(game,zetten,nieuwe_coordinaat.first, nieuwe_coordinaat.second);
            }
            else if (game.getPiece(nieuwe_coordinaat.first, nieuwe_coordinaat.second)->getKleur() != this->getKleur()) //als de kleur verschillend is (bij een schaakstuk)
            {
                voeg_aan_vector(game,zetten,nieuwe_coordinaat.first, nieuwe_coordinaat.second);
                break;
            }
            else if (game.getPiece(nieuwe_coordinaat.first, nieuwe_coordinaat.second)->getKleur() == this->getKleur())
            {
                voeg_aan_vector(game,zetten,nieuwe_coordinaat.first, nieuwe_coordinaat.second);
                break;
            }
        }
        nieuwe_coordinaat = coordinaat;
    }
}

void SchaakStuk::voeg_toeVERSLAAN(Game &game, vector<pair<int, int>> &zetten, int x, int y) const
{
    if (game.schaakstuk_bestaat(game.getPiece(x,y)) or game.lege_vak(game.getPiece(x,y),x,y)) //als het schaakstuk boven dit koningin (this) bestaat of leeg is
    {
        if (game.getPiece(x,y) == nullptr)
        {
            voeg_aan_vector(game,zetten,x,y);
        }
        else if (game.getPiece(x,y)->getKleur() != this->getKleur() or game.getPiece(x,y)->getKleur() == this->getKleur()) //als de kleur verschillend is (bij een schaakstuk)
        {
            voeg_aan_vector(game,zetten,x,y);
        }
    }
}

void SchaakStuk::voeg_aan_vector(Game &game, vector<pair<int, int>> &zetten, int x, int y) const
{
    pair<int, int> voor(x,y);   // voeg dan die coordinaat toe in vector pion_zetten
    zetten.push_back(voor);
}

void SchaakStuk::voegEnPassant(Game &game, vector<pair<int, int>> &zetten, int x, int y, int a, int b) const
{
    if (game.lege_vak(game.getPiece(x,y),x,y) and game.lege_vak(game.getPiece(a,b),a,b)) //als zijn verslaan-plaats leeg is en 1 hoger dan die verslaan-plaats ook leeg is
    {
        voeg_aan_vector(game,zetten,x,y);
    }
}