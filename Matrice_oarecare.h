#ifndef MATRICE_OARECARE_H_INCLUDED
#define MATRICE_OARECARE_H_INCLUDED
/*
(dynamic_cast<*m> p -> lin) -> dim = p -> lin; // downcasting
dynamic_cast se face cu pointeri
upcasting -> vector de pointeri cu matrice pe care fac verificarea de triangulariatate
*/
class Matrice_oarecare : public Matrice
{
    int lin, col;
    bool diagonala = 0, vazut = 0;
public:
    //CONSTRUCTORI---------------------------------------------------------------------------------
    Matrice_oarecare() : Matrice() {};
    Matrice_oarecare(int lin, int col = 0);
    Matrice_oarecare& operator=(const Matrice_oarecare&);
    //DESSTRUCTORI---------------------------------------------------------------------------------
    ~Matrice_oarecare();
    //OPERATII ALGEBRICE BINARE---------------------------------------------------------------------------------
    Matrice_oarecare& operator +(Matrice_oarecare&);
    Matrice_oarecare& operator -(Matrice_oarecare&);
    Matrice_oarecare& operator /(Matrice_oarecare&);
    Matrice_oarecare& operator *(Matrice_oarecare&);
    //OPERATII ALGEBRICE BINARE CU ATRIBUIRE---------------------------------------------------------------------------------
    Matrice_oarecare& operator +=(Matrice_oarecare&);
    Matrice_oarecare& operator -=(Matrice_oarecare&);
    Matrice_oarecare& operator /=(Matrice_oarecare&);
    Matrice_oarecare& operator *=(Matrice_oarecare&);
    //OPERATII ALGEBRICE UNARE---------------------------------------------------------------------------------
    Transpusa();
    Inversa();
    Matrice_oarecare& operator ++();
    Matrice_oarecare& operator ++(int);
    Matrice_oarecare& operator --();
    Matrice_oarecare& operator --(int);
    //CITIRE---------------------------------------------------------------------------------
    friend istream& operator >> (istream&, Matrice_oarecare&);
    friend ostream& operator << (ostream&, const Matrice_oarecare&);
    //OBLIGATORII
    void diag();
    void afis();
};

Matrice_oarecare::Matrice_oarecare(int lin, int col)
{
    this -> lin = lin;
    this -> col = col;
    v = new Complex<double>*[lin + 1]();
    for(int i = 0; i <= lin; ++i)
    {
        v[i] = new Complex<double>[col + 1]();
    }
}

Matrice_oarecare& Matrice_oarecare:: operator=(const Matrice_oarecare& ob)
{
    if(this != &ob)
    {
        lin = ob.lin;
        col = ob.col;
        v = new Complex<double>*[lin + 1]();
        for(int i = 0; i <= lin; ++i)
        {
            v[i] = new Complex<double>[col + 1]();
        }
        for(int i = 1; i <= ob.lin; ++i)
            for(int j = 1; j <= ob.col; ++j)
                v[i][j] = ob.v[i][j];
    }
    return *this;
}

Matrice_oarecare::~Matrice_oarecare()
{
    if(v != NULL)
    {
        for(int i = 0; i <= lin; ++i)
        {
            delete[] v[i];
        }
        delete[] v;
    }
    //cout << "Destructor apelat m_o\n";
}

Matrice_oarecare& Matrice_oarecare::operator + (Matrice_oarecare& ob)
{
    try
    {
        if(lin == ob.lin && col == ob.col)
        {
            Matrice_oarecare temp(lin + 1, col + 1);
            for(int i = 1; i <= lin; ++i)
                for(int j = 1; j <= col; ++j)
                    temp.v[i][j] = v[i][j] + ob.v[i][j];
            return temp;
        }
        else
            throw 1;
    }
    catch(int x)
    {
        cout << "Nu poti aduna cele doua matrice pentru ca nu au acelasi numar de linii si de coloane!\n";
    }
}

Matrice_oarecare& Matrice_oarecare::operator - (Matrice_oarecare& ob)
{
    try
    {
        if(lin == ob.lin && col == ob.col)
        {
            Matrice_oarecare temp(lin + 1, col + 1);
            for(int i = 1; i <= lin; ++i)
                for(int j = 1; j <= col; ++j)
                    temp.v[i][j] = v[i][j] - ob.v[i][j];
            return temp;
        }
        else
            throw 1;
    }
    catch(int x)
    {
        cout << "Nu poti scade cele doua matrice pentru ca nu au acelasi numar de linii si de coloane!\n";
    }
}

Matrice_oarecare& Matrice_oarecare::operator * (Matrice_oarecare& ob)
{
    try
    {
        if(col == ob.lin)
        {
            Matrice_oarecare temp(ob.lin + 1, col + 1);
            for(int i = 1; i <= ob.lin; ++i)
                for(int j = 1; j <= col; ++j)
                    for(int k = 1; k <= col; ++k)
                        temp.v[i][j] += v[i][k] * ob.v[k][j];
            return temp;
        }
        else
            throw 1;
    }
    catch(int x)
    {
        cout << "Nu poti inmulti doua matrice in care numarul de coloane din prima matrice nu corespunde cu cel al liniilor din a doua!\n";
    }
}

Matrice_oarecare& Matrice_oarecare::operator ++()
{
    for(int i = 1; i <= lin; ++i)
        for(int j = 1; j <= col; ++j)
            v[i][j]++;
}

Matrice_oarecare& Matrice_oarecare::operator --()
{
    for(int i = 1; i <= lin; ++i)
        for(int j = 1; j <= col; ++j)
            v[i][j]++;
}

Matrice_oarecare& Matrice_oarecare::operator ++(int x)
{
    Matrice_oarecare temp(lin + 1, col + 1);
    for(int i = 1; i <= lin; ++i)
        for(int j = 1; j <= col; ++j)
            temp.v[i][j] = v[i][j]++;
    return temp;
}

Matrice_oarecare& Matrice_oarecare::operator --(int x)
{
    Matrice_oarecare temp(lin + 1, col + 1);
    for(int i = 1; i <= lin; ++i)
        for(int j = 1; j <= col; ++j)
            temp.v[i][j] = v[i][j]--;
    return temp;
}

istream& operator >> (istream& in, Matrice_oarecare& ob)
{
    string S;
    bool OK;
    cout <<"Introduceti numarul de linii:";
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
        }
        catch(bool OK)
        {
            cout << "Nu ati introdus un numar. Incercati din nou:";
        }
    }
    while(!OK);
    ob.lin = stoi(S);
    cout <<"Introduceti numarul de coloane:";
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
        }
        catch(bool OK)
        {
            cout << "Nu ati introdus un numar. Incercati din nou:";
        }
    }
    while(!OK);
    ob.col = stoi(S);

    //cout << ob.lin << " " << ob.col << '\n';
    ob.v = new Complex<double>*[ob.lin + 1]();
    for(int i = 0; i <= ob.lin; ++i)
        ob.v[i] = new Complex<double>[ob.col + 1]();

    for(int i = 1; i <= ob.lin; ++i)
        for(int j = 1; j <= ob.col; ++j)
            in >> ob.v[i][j];

    return in;
}

ostream& operator << (ostream& out, const Matrice_oarecare& ob)
{
    for(int i = 1; i <= ob.lin; ++i)
    {
        for(int j = 1; j <= ob.col; ++j)
            out << ob.v[i][j] << " ";
        out << '\n';
    }
    return out;
}

void Matrice_oarecare::diag()
{
    try
    {
        if(lin == col)
        {
            if(!vazut)
            {
                bool tri_sup = 1;
                for(int i = 1; i <= lin; ++i)
                    for(int j = 1; j < i; ++j)
                        if(v[i][j] != 0)
                        {
                            tri_sup = 0;
                            break;
                        }
                bool tri_inf = 1;
                for(int i = 1; i <= lin; ++i)
                    for(int j = i + 1; j <= lin; ++j)
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
        else
            throw(1);
    }
    catch(int x)
    {
        cout << "Matrice nepatratica.\n";
    }
}

void Matrice_oarecare::afis()
{
    try
    {
        if(lin == col)
        {
            Complex<double> ans(1,1);
            for(int i = 1; i <= lin; ++i)
            {
                ans *= v[i][i];
                for(int j = 1; j <= col; ++j)
                    cout << v[i][j] << " ";
                cout << '\n';
            }
            cout << "Determinantul matricii este: " << ans << '\n';
        }
        else
            throw(1);
    }
    catch(int x)
    {
        cout << "Matrice nepatratica.\n";
    }
}

#endif // MATRICE_OARECARE_H_INCLUDED
