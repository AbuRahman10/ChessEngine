//  Student: Abobaker Rahman
//  Rolnummer: 2022825
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include "guicode/chessboard.h"
#include "iostream"


using namespace std;

class Game;

enum zw{zwart,wit};

class SchaakStuk {
public:
    SchaakStuk(zw kleur): kleur(kleur) {}

    virtual Piece piece() const=0;      // Verander deze functie niet!
                                        // Deze functie wordt gebruikt door
                                        // setItem(x,y,SchaakStuk*) van
                                        // SchaakGUI

    zw getKleur() const { return kleur; }

    virtual vector<pair<int,int>> geldige_zetten(Game &game) const = 0; // de geldige zetten die de schaakstuk heeft afhankelijk van het spel

    // met de functies hier beneden weet ik welke soort schaakstuk een gegeven parameter/Schaakstuk* is
    virtual bool ISkoning() const = 0;

    virtual bool ISpion() const = 0;

    virtual bool IStoren() const = 0;

    virtual bool ISpaard() const = 0;

    virtual bool ISkoningin() const = 0;

    virtual bool ISloper() const = 0;

    //dit functie heeft dezelfde werk zoals geldige_zetten maar;
    //kijkt naar plaatsen waar een vijand kan komen en het kan eten (nodig voor setTileThreat van SchaakGUI)
    virtual vector<pair<int,int>> verslaan(Game &game) const = 0;

    void meervakken(Game &game, vector<pair<int, int>> &zetten,const string op,const string op2) const;

    void meervakkenVERSLAAN(Game &game, vector<pair<int, int>> &zetten,const string op,const string op2) const;

    void voeg_toe(Game &game,vector<pair<int, int>> &zetten,int x, int y) const;

    void voeg_toeVERSLAAN(Game &game,vector<pair<int, int>> &zetten,int x, int y) const;

    void voeg_aan_vector(Game &game,vector<pair<int, int>> &zetten,int x, int y) const;

    void voegEnPassant(Game &game,vector<pair<int, int>> &zetten,int x, int y, int a, int b) const;

    void free_square(Game &game,vector<pair<int, int>> &zetten,int x, int y) const;

    void color_different(Game &game,vector<pair<int, int>> &zetten,int x, int y) const;

private:
    zw kleur;
};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game &game) const override;

    bool ISkoning() const override;

    bool ISpion() const override;

    bool IStoren() const override;

    bool ISpaard() const override;

    bool ISkoningin() const override;

    bool ISloper() const override;

    vector<pair<int,int>> verslaan(Game &game) const override;
};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game &game) const override;

    bool ISkoning() const override;

    bool ISpion() const override;

    bool IStoren() const override;

    bool ISpaard() const override;

    bool ISkoningin() const override;

    bool ISloper() const override;

    vector<pair<int,int>> verslaan(Game &game) const override;
};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game &game) const override;

    bool ISkoning() const override;

    bool ISpion() const override;

    bool IStoren() const override;

    bool ISpaard() const override;

    bool ISkoningin() const override;

    bool ISloper() const override;

    vector<pair<int,int>> verslaan(Game &game) const override;
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game &game) const override;

    bool ISkoning() const override;

    bool ISpion() const override;

    bool IStoren() const override;

    bool ISpaard() const override;

    bool ISkoningin() const override;

    bool ISloper() const override;

    vector<pair<int,int>> verslaan(Game &game) const override;
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game &game) const override;

    bool ISkoning() const override;

    bool ISpion() const override;

    bool IStoren() const override;

    bool ISpaard() const override;

    bool ISkoningin() const override;

    bool ISloper() const override;

    vector<pair<int,int>> verslaan(Game &game) const override;
};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int,int>> geldige_zetten(Game &game) const override;

    bool ISkoning() const override;

    bool ISpion() const override;

    bool IStoren() const override;

    bool ISpaard() const override;

    bool ISkoningin() const override;

    bool ISloper() const override;

    vector<pair<int,int>> verslaan(Game &game) const override;
};

#endif //SCHAKEN_SCHAAKSTUK_H
