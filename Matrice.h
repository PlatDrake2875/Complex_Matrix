#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED

class Matrice
{
protected:
    static int M_Diag;
    Complex<double>** v;
public:
    Matrice(){v = NULL;}
    virtual ~Matrice(){v = NULL;}
    static void update(){M_Diag++;}
    static void afis_diag() {cout << M_Diag << '\n';}
};

int Matrice::M_Diag = 0;
#endif // MATRICE_H_INCLUDED
