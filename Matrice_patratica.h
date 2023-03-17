#ifndef MATRICE_PATRATICA_H_INCLUDED
#define MATRICE_PATRATICA_H_INCLUDED


class Matrice_patratica : public Matrice
{
    int dim;
    bool diagonala = 0, vazut = 0;
public:
    //CONSTRUCTORI---------------------------------------------------------------------------------
    Matrice_patratica() : Matrice() {};
    Matrice_patratica(int dim);
    Matrice_patratica& operator=(const Matrice_patratica&);
    //DESSTRUCTORI---------------------------------------------------------------------------------
    ~Matrice_patratica();
    //OPERATII ALGEBRICE BINARE---------------------------------------------------------------------------------
    Matrice_patratica& operator +(Matrice_patratica&);
    Matrice_patratica& operator -(Matrice_patratica&);
    Matrice_patratica& operator /(Matrice_patratica&);
    Matrice_patratica& operator *(Matrice_patratica&);
    //OPERATII ALGEBRICE BINARE CU ATRIBUIRE---------------------------------------------------------------------------------
    Matrice_patratica& operator +=(Matrice_patratica&);
    Matrice_patratica& operator -=(Matrice_patratica&);
    Matrice_patratica& operator /=(Matrice_patratica&);
    Matrice_patratica& operator *=(Matrice_patratica&);
    //OPERATII ALGEBRICE UNARE---------------------------------------------------------------------------------
    Transpusa();
    Inversa();
    Matrice_patratica& operator ++();
    Matrice_patratica& operator ++(int);
    Matrice_patratica& operator --();
    Matrice_patratica& operator --(int);
    //OPERATII DE I/O---------------------------------------------------------------------------------
    friend istream& operator >> (istream&, Matrice_patratica&);
    friend ostream& operator << (ostream&, const Matrice_patratica&);
    //OPERATII OBLIGATORII PENTRU PROIECT---------------------------------------------------------------------------------
    void diag();
    void afis();
};

Matrice_patratica::Matrice_patratica(int dim)
{
    this -> dim = 0;
    v = new Complex<double>*[dim + 1]();
    for(int i = 0; i <= dim; ++i)
    {
        v[i] = new Complex<double>[dim + 1]();
    }
}

Matrice_patratica& Matrice_patratica:: operator=(const Matrice_patratica& ob)
{
    if(this != &ob)
    {
        dim = ob.dim;
        v = new Complex<double>*[dim + 1]();
        for(int i = 0; i <= dim; ++i)
        {
            v[i] = new Complex<double>[dim + 1]();
        }
        for(int i = 1; i <= ob.dim; ++i)
            for(int j = 1; j <= ob.dim; ++j)
                v[i][j] = ob.v[i][j];
    }
    return *this;
}

Matrice_patratica::~Matrice_patratica()
{
    if(v != NULL)
    {
        for(int i = 0; i <= dim; ++i)
        {
            delete[] v[i];
        }
        delete[] v;
    }
    cout << "Destructor apelat m_pf\n";
}

Matrice_patratica& Matrice_patratica::operator + (Matrice_patratica& ob)
{
    try
    {
        if(dim == ob.dim)
        {
            Matrice_patratica temp(dim + 1);
            for(int i = 1; i <= dim; ++i)
                for(int j = 1; j <= dim; ++j)
                    temp.v[i][j] = v[i][j] + ob.v[i][j];
            return temp;
        }
        else
            throw 1;
    }
    catch(int x)
    {
        cout << "Nu poti aduna cele doua matrice pentru ca nu au acelasi numar de dimii si de dimoane!\n";
    }
}

Matrice_patratica& Matrice_patratica::operator - (Matrice_patratica& ob)
{
    try
    {
        if(dim == ob.dim)
        {
            Matrice_patratica temp(dim + 1);
            for(int i = 1; i <= dim; ++i)
                for(int j = 1; j <= dim; ++j)
                    temp.v[i][j] = v[i][j] - ob.v[i][j];
            return temp;
        }
        else
            throw 1;
    }
    catch(int x)
    {
        cout << "Nu poti scade cele doua matrice pentru ca nu au acelasi numar de dimii si de dimoane!\n";
    }
}

Matrice_patratica& Matrice_patratica::operator * (Matrice_patratica& ob)
{
    try
    {
        if(dim == ob.dim)
        {
            Matrice_patratica temp(ob.dim + 1);
            for(int i = 1; i <= ob.dim; ++i)
                for(int j = 1; j <= dim; ++j)
                    for(int k = 1; k <= dim; ++k)
                        temp.v[i][j] += v[i][k] * ob.v[k][j];
            return temp;
        }
        else
            throw 1;
    }
    catch(int x)
    {
        cout << "Nu poti inmulti doua matrice in care numarul de dimoane din prima matrice nu corespunde cu cel al dimiilor din a doua!\n";
    }
}

Matrice_patratica& Matrice_patratica::operator ++()
{
    for(int i = 1; i <= dim; ++i)
        for(int j = 1; j <= dim; ++j)
            v[i][j]++;
}

Matrice_patratica& Matrice_patratica::operator --()
{
    for(int i = 1; i <= dim; ++i)
        for(int j = 1; j <= dim; ++j)
            v[i][j]++;
}

Matrice_patratica& Matrice_patratica::operator ++(int x)
{
    Matrice_patratica temp(dim + 1);
    for(int i = 1; i <= dim; ++i)
        for(int j = 1; j <= dim; ++j)
            temp.v[i][j] = v[i][j]++;
    return temp;
}

Matrice_patratica& Matrice_patratica::operator --(int x)
{
    Matrice_patratica temp(dim + 1);
    for(int i = 1; i <= dim; ++i)
        for(int j = 1; j <= dim; ++j)
            temp.v[i][j] = v[i][j]--;
    return temp;
}

istream& operator >> (istream& in, Matrice_patratica& ob)
{
    string S;
    bool OK;
    cout <<"Introduceti dimensiunea matrice:";
    do
    {
        in >> S;
        OK = 1;
        try
        {
            for(int i = 0; i < S.size(); ++i)
                if(!isdigit(S[i]))
                {
                    OK = 0;
                    throw OK;
                }
            ob.dim = stoi(S);
        }
        catch(bool OK)
        {
            cout << "Nu ati introdus un numar. Incercati din nou:";
        }
    }
    while(!OK);
    //cout << ob.dim << '\n';
    ob.v = new Complex<double>*[ob.dim + 1]();
    for(int i = 0; i <= ob.dim; ++i)
        ob.v[i] = new Complex<double>[ob.dim + 1]();

    for(int i = 1; i <= ob.dim; ++i)
        for(int j = 1; j <= ob.dim; ++j)
            in >> ob.v[i][j];
    return in;
}

ostream& operator << (ostream& out, const Matrice_patratica& ob)
{
    for(int i = 1; i <= ob.dim; ++i)
    {
        for(int j = 1; j <= ob.dim; ++j)
            out << ob.v[i][j] << " ";
        out << '\n';
    }
    return out;
}

void Matrice_patratica::diag()
{
    if(!vazut)
    {
        bool tri_sup = 1;
        for(int i = 1; i <= dim; ++i)
            for(int j = 1; j < i; ++j)
                if(v[i][j] != 0)
                {
                    tri_sup = 0;
                    break;
                }
        bool tri_inf = 1;
        for(int i = 1; i <= dim; ++i)
            for(int j = i + 1; j <= dim; ++j)
                if(v[i][j] != 0)
                {
                    tri_inf = 0;
                    break;
                }
        diagonala = max(tri_inf, tri_sup);
        vazut = true;
        cout << ((tri_inf || tri_sup) ? update(), "Matrice diagonala.\n" : "Matrice nediagonala.\n");
    }
    else
    {
        cout << (diagonala ? "Matrice diagonala.\n" : "Matrice nediagonala.\n");
    }
}

void Matrice_patratica::afis()
{
    Complex<double> ans(1,1);
    for(int i = 1; i <= dim; ++i)
    {
        ans *= v[i][i];
        for(int j = 1; j <= dim; ++j)
            cout << v[i][j] << " ";
        cout << '\n';
    }
    cout << "Determinantul matricii este: " << ans << '\n';
}

#endif // MATRICE_PATRATICA_H_INCLUDED
