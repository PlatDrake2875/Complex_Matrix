#ifndef NR_COMPLEX_H_INCLUDED
#define NR_COMPLEX_H_INCLUDED

using namespace std;

template <class T> class Complex
{
    T im, re;
public:
    //CONSTRUCTORI---------------------------------------------------------------------------------
    Complex();
    Complex(double re, double im = 0.f);
    Complex(const Complex&);
    //DESTRUCTORI----------------------------------------------------------------------------------
    ~Complex() {};
    //OPEARTORI RELATIONALI------------------------------------------------------------------------
    Complex& operator =(const Complex&);
    bool operator ==(const Complex&);
    bool operator !=(const Complex&);
    int operator >(const Complex&);
    //OPERATORI ARITMETICI BINARI------------------------------------------------------------------
    Complex operator +(const Complex&);
    Complex operator -(const Complex&);
    Complex operator *(const Complex&);
    Complex operator /(const Complex&);
    //OPERATORI ARITMETICI UNARI------------------------------------------------------------------
    Complex operator ++();
    Complex operator ++(int);
    Complex operator --();
    Complex operator --(int);
    //OPERATORI ARITMETICI BINARI CU ATRIBUIRE-----------------------------------------------------
    Complex operator +=(const Complex&);
    Complex operator -=(const Complex&);
    Complex operator *=(const Complex&);
    Complex operator /=(const Complex&);
    //OPEARATORI I/O-------------------------------------------------------------------------------
    friend istream& operator >>(istream& in, Complex& ob)
    {
        string S;
        bool OK, OK_virgula, to_convert;
        do
        {
            in >> S;
            ob.re = 0;
            OK = 1;
            OK_virgula = 1;
            to_convert = 0;
            try
            {
                for(int i = 0; i < S.size(); ++i)
                {
                    if(!isdigit(S[i]))
                    {
                        if(!to_convert && S[i] == '.')
                            to_convert = 1;
                        else
                        {
                            OK = 0;
                            throw OK;
                        }
                    }
                }
                ob.re = stof(S);
            }
            catch(bool OK)
            {
                cout << "Nu ati introdus un numar. Incercati din nou:";
            }
        }
        while(!OK);
        do
        {
            in >> S;
            ob.im = 0;
            OK = 1;
            OK_virgula = 1;
            to_convert = 0;
            try
            {
                for(int i = 0; i < S.size(); ++i)
                {
                    if(!isdigit(S[i]))
                    {
                        if(!to_convert && S[i] == '.')
                            to_convert = 1;
                        else
                        {
                            OK = 0;
                            throw OK;
                        }
                    }
                }
                ob.im = stof(S);
            }
            catch(bool OK)
            {
                cout << "Nu ati introdus un numar. Incercati din nou:";
            }
        }
        while(!OK);
        return in;
    }
    friend ostream& operator <<(ostream& out, Complex& ob)
    {
        out << setprecision(10) << ob.re << " " << ob.im << "i ";
        return out;
    }
    //MISC-----------------------------------------------------------------------------------------
    void Eval_cmp(const Complex&);
    T abs();                                           // norma numarului complex

};

template <class T> Complex<T>::Complex()
{
    im = 0;
    re = 0;
}

template <class T> Complex<T>::Complex(double re, double im)
{
    this -> im = im;
    this -> re = re;
}

template <class T> Complex<T>& Complex<T>::operator=(const Complex<T>& ob)
{
    if(this != &ob)
    {
        re = ob.re;
        im = ob.im;
    }
    return *this;
}

template <class T> Complex<T>::Complex(const Complex& ob)
{
    *this = ob;
}

template <class T> Complex<T> Complex<T>::operator +(const Complex<T>& ob)
{
    Complex<T> temp;
    temp.re = re + ob.re;
    temp.im = im + ob.im;
    return temp;
}

template <class T> Complex<T> Complex<T>::operator +=(const Complex<T>& ob)
{
    re += ob.re;
    im += ob.im;
    return *this;
}

template <class T> Complex<T> Complex<T>::operator -(const Complex<T>& ob)
{
    Complex temp;
    temp.re = re - ob.re;
    temp.im = im - ob.im;
    return temp;
}

template <class T> Complex<T>Complex<T>::operator -=(const Complex<T>& ob)
{
    re -= ob.re;
    im -= ob.im;
    return *this;
}

template <class T> Complex<T> Complex<T>::operator *(const Complex<T>& ob)
{
    Complex<T> temp;
    temp.re = re * ob.re - im * ob.im;
    temp.im = re * ob.im + im * ob.re;
    return temp;
}

template <class T> Complex<T> Complex<T>::operator *=(const Complex<T>& ob)
{
    re = re * ob.re - im * ob.im;
    im = re * ob.im + im * ob.re;
    return *this;
}

template <class T> Complex<T> Complex<T>::operator /(const Complex<T>& ob)
{
    Complex<T> temp;
    temp.re = re / ob.re;
    temp.im = im / ob.im;
    return temp;
}

template <class T> Complex<T> Complex<T>::operator /=(const Complex<T>& ob)
{
    re /= ob.re;
    im /= ob.im;
    return *this;
}

template <class T> bool Complex<T>::operator ==(const Complex<T>& ob)
{
    return(re == ob.re && im == ob.im);
}

template <class T> bool Complex<T>::operator !=(const Complex<T>& ob)
{
    return(re != ob.re || im != ob.im);
}

template <class T> int Complex<T>::operator >(const Complex<T>& ob)
{
    /* functia returneaza:
       0, daca re < ob.re && im < ob.im
       1, daca re > ob.re && im > ob.im
       2, daca re < ob.re && im > ob.im
       3, daca re > ob.re && im < ob.im
    */
    if(re < ob.re && im < ob.im)
        return 0;
    else if(re > ob.re && im > ob.im)
        return 1;
    if(re < ob.re && im > ob.im)
        return 2;
    else
        return 3;
}

template <class T> void Complex<T>::Eval_cmp(const Complex<T>& ob)
{
    switch(*this > ob)
    {
    case 0:
        cout << "a < b\n";
        break;
    case 1:
        cout << "a > b\n";
        break;
    case 2:
        cout << "a are partea reala mai mica decat b, dar partea imaginara mai mare\n";
        break;
        cout << "a are partea reala mai mare decat b, dar partea imagiara mai mica\n";
    case 3:
        break;
    }
}

template <class T> T Complex<T>::abs()
{
    return sqrt(re * re + im * im);
}

template <class T> Complex<T> Complex<T>::operator ++()
{
    re++;
    im++;
}

template <class T> Complex<T> Complex<T>::operator ++(int x)
{
    Complex temp;
    temp.re = re++;
    temp.im = im++;
    return temp;
}

template <class T> Complex<T> Complex<T>::operator --()
{
    re--;
    im--;
}

template <class T> Complex<T> Complex<T>::operator --(int x)
{
    Complex<T> temp;
    temp.re = re--;
    temp.im = im--;
    return temp;
}
#endif // NR_COMPLEX_H_INCLUDED
