#include <bits/stdc++.h>
#include "Nr_Complex.h"
#include "Matrice.h"
#include "Matrice_oarecare.h"
#include "Matrice_patratica.h"

using namespace std;

ifstream in("t.in");
ofstream out("t.out");

int main()
{
    cout << "Se dau N matrice de numere complexe. Deci va trebui sa introduceti ambele componente ale numarului pentru fiecare numar\n";
    cout << "Matricele pot fi oarecare sau patratice.\n";
    cout << "Daca alegeti o matrice oarecare, va trebui sa introduceti N_i * M_i numere\n";
    cout << "Daca alegeti o matrice patratica, va trebui sa introduceti N_i ^ 2 numere\n";
    cout << "1)Adunarea\n";
    cout << "2)Scaderea\n";
    cout << "3)Inmultirea\n";
    cout << '\n';
    cout << "Pentru oricare matrice se pot aplica opeartiile:\n";
    cout << "1)Verificarea diagonalitatii.\n";
    cout << "2)Incrementarea/decrementarea tuturor elementelor matricii cu o unitate.\n";
    cout << "3)Calcularea si afisarea determinantului matricei, impreuna cu matricea, daca este patratica, desgiur.\n";
    cout << '\n';
    int N;
    bool OK;
    cout << "Introduceti numarul de matrice pe care vreti sa operati: ";
    string S;
    do
    {
        OK = 1;
        cin >> S;
        try
        {
            for(int i = 0; i < S.size() && OK; ++i)
                if(!isdigit(S[i]))
                {
                    OK = 0;
                    throw OK;
                }
        }
        catch(bool OK)
        {
            cout << "Nu ati introdus un numar. Incercati din nou: ";
        }
    }
    while(!OK);
    N = stoi(S);
    cout << '\n';
    cout << "Se vor citi cele N matrice, codificand datele in urmatorul fel:\n";
    cout << "x = tipul matricei (1 = oarecare, 2 = patratica)\nN_i, respectiv M_i, dimensiunea, respectiv dimenstiunile matricei i\n2 * N_i * M_i numere, semnificand valorile matricei.\n\n";
    vector<Matrice*> A;
    Matrice_oarecare* obm;
    Matrice_patratica* obp;

    for(int i = 0; i < N; ++i)
    {
        int x;
        cout <<"Introduceti tipul matricei dorite:";
        cin >> x;
        if(x == 1)
        {
            obm = new Matrice_oarecare;
            cin >> *obm;
            A.push_back(obm);
        }
        else
        {
            obp = new Matrice_patratica;
            cin >> *obp;
            A.push_back(obp);
        }
    }
    cout << "Scuzati deranjul, dar trebuie sa afisez cele N elemente de tipuri diferite asa cum se cere in tema\n";
    for(int i = 0; i < N; ++i)
    {
        if(typeid(*A[i]) == typeid(Matrice_oarecare))
        {
            cout << *dynamic_cast<Matrice_oarecare*>(A[i])<< '\n';
        }
        else
        {
            cout << *dynamic_cast<Matrice_patratica*>(A[i]) << '\n';
        }
    }
    cout << '\n';
    cout << "Acum ca am trecut si de asta, va puteti distra cu oricare matrice dintre cele " << N << " create.\n";
    cout << '\n';
    cout << "Numai ca trebuie sa opearati pe matrice de acelasi tip.\n";
    cout << "Va trebui sa dati ca input:\nx = 1 (operatie unara) sau 2 (opeartie binara)\n";
    cout << "Unul, respectiv doua, numere de la 1 la N pe care sa se aplice opeartia dorita pe care o veti introduce.\n";
    cout << '\n';
    cout << "Reamintesc opeartii unare:\n";
    cout << "1)Verificarea diagonalitatii.\n";
    cout << "2)Incrementarea/decrementarea tuturor elementelor matricii cu o unitate.\n";
    cout << "3)Calcularea si afisarea determinantului matricei, impreuna cu matricea, daca este patratica, desgiur.\n";
    cout << '\n';
    cout << "Si pe cele binare binare\n";
    cout << "1)Adunarea\n";
    cout << "2)Scaderea\n";
    cout << "3)Inmultirea\n";
    cout << '\n';
    cout << "De asemenea, trebuie sa introduceti matrice de acelasi tip, patratice sau oarecare, ca sa mearga programul.\n";
    cout << "Ca sa incheiati prorgramul, introduceti numarul 5 pentru x.\n";
    char c;
    string index1, index2;

    do
    {
        int OK;
        cout << "Introduceti categoria operatiei dorite:";
        do
        {
            OK = 1;
            cin >> c;
            if(!isdigit(c))
            {
                cout << "Incercati o valoare corecta:\n";
                OK = 0;
            }
        }
        while(!OK);
        c -= '0';
        if(c == 5)
            break;
        if(c == 1)
        {
            cout << "Introduceti pozitia matricei dorite:";
            do
            {
                OK = 1;
                cin >> index1;
                try
                {
                    for(int i = 0; i < index1.size(); ++i)
                        if(!isdigit(index1[i]))
                        {
                            OK = 0;
                            throw OK;
                        }
                    if(stoi(index1) <= 0 || stoi(index1) > N)
                    {
                        OK = -1;
                    }
                }
                catch(int OK)
                {
                    if(!OK)
                        cout << "Introduceti un numar de data asta:\n";
                    else
                        cout << "Numarul nu face parte din intervalul 1, N. Introduceti altul:\n";
                }

            }
            while(!OK);

            cout << "Introduceti tipul care opeartia dorita:";

            do
            {
                OK = 1;
                cin >> c;
                if(!isdigit(c))
                {
                    cout << "Incercati o valoare corecta:\n";
                    OK = 0;
                }
            }
            while(!OK);
            c -= '0';
            if(c == 1)
            {
                if(typeid(*A[stoi(index1) - 1]) == typeid(Matrice_oarecare))
                {
                    (*dynamic_cast<Matrice_oarecare*>(A[stoi(index1) - 1])).diag();
                }
                else
                {
                    (*dynamic_cast<Matrice_patratica*>(A[stoi(index1) - 1])).diag();
                }
            }
            else if(c == 2)
            {
                cout << "Introduceti 1 daca vreti sa incrementati matricea sau 2 in caz contrat:";
                do
                {
                    OK = 1;
                    cin >> c;
                    try
                    {
                        if(!isdigit(c))
                        {
                            OK = 0;
                            throw OK;
                        }
                        else if(c < '1' || c > '2')
                        {
                            OK = -1;
                            throw OK;
                        }
                    }
                    catch(int OK)
                    {
                        if(!OK)
                        {
                            cout << "Nu ati introdus un numar. Va rog s-o faceti:";
                        }
                        else
                        {
                            cout << "Numarul introdus de dumneavoastra nu este 1 sau 2:";
                        }
                    }
                }
                while(!OK);

                if(typeid(*A[stoi(index1) - 1]) == typeid(Matrice_oarecare))
                {
                    if(c == '1')
                        (*dynamic_cast<Matrice_oarecare*>(A[stoi(index1) - 1]))++;
                    else
                        (*dynamic_cast<Matrice_oarecare*>(A[stoi(index1) - 1]))--;

                }
                else
                {
                    if(c == '1')
                        (*dynamic_cast<Matrice_patratica*>(A[stoi(index1) - 1]))++;
                    else
                        (*dynamic_cast<Matrice_patratica*>(A[stoi(index1) - 1]))--;
                }
            }
            else
            {
                if(typeid(*A[stoi(index1) - 1]) == typeid(Matrice_oarecare))
                {
                    (*dynamic_cast<Matrice_oarecare*>(A[stoi(index1) - 1])).afis();
                }
                else
                {
                    (*dynamic_cast<Matrice_patratica*>(A[stoi(index1) - 1])).afis();
                }
            }
        }
        else
        {
            cout << "Introduceti pozitia primei matrice:";

            do
            {
                OK = 1;
                cin >> index1;
                try
                {
                    for(int i = 0; i < index1.size(); ++i)
                        if(!isdigit(index1[i]))
                        {
                            OK = 0;
                            throw OK;
                        }
                    if(stoi(index1) <= 0 || stoi(index1) > N)
                    {
                        OK = -1;
                    }
                }
                catch(int OK)
                {
                    if(!OK)
                        cout << "Introduceti un numar de data asta:\n";
                    else
                        cout << "Numarul nu face parte din intervalul 1, N. Introduceti altul:\n";
                }

            }
            while(!OK);

            cout << "Introduceti pozitia celei de-a doua matrice:";
            do
            {
                OK = 1;
                cin >> index2;
                try
                {
                    for(int i = 0; i < index2.size(); ++i)
                        if(!isdigit(index2[i]))
                        {
                            OK = 0;
                            throw OK;
                        }
                    if(stoi(index2) <= 0 || stoi(index2) > N)
                    {
                        OK = -1;
                    }
                }
                catch(int OK)
                {
                    if(!OK)
                        cout << "Introduceti un numar de data asta:\n";
                    else
                        cout << "Numarul nu face parte din intervalul 1, N. Introduceti altul:\n";
                }

            }
            while(!OK);

            cout << "Introduceti tipul operatiei dorite:";
            do
            {
                OK = 1;
                cin >> c;
                if(!isdigit(c))
                {
                    cout << "Incercati o valoare corecta:\n";
                    OK = 0;
                }
                else if(c < '1' || c > '3')
                {
                    cout << "Introduceti o valoare din intervalul 1-3:";
                    OK = 0;
                }
            }
            while(!OK);
            c -= '0';

            int i = stoi(index1) - 1;
            int j = stoi(index2) - 1;
            if(typeid(*A[i]) != typeid(*A[j]))
            {
                cout << "Matrice de tip diferit!\n";
            }
            else if(typeid(*A[i]) == typeid(Matrice_oarecare))
            {
                Matrice_oarecare obm, ob1, ob2;

                obm = *dynamic_cast<Matrice_oarecare*>(A[i]);
                ob1 = *dynamic_cast<Matrice_oarecare*>(A[i]);
                ob2 = *dynamic_cast<Matrice_oarecare*>(A[j]);
                if(c == 1)
                {
                    obm = (ob1 + ob2);
                }
                else if(c == 2)
                {
                    obm = A[i] - A[j];
                }
                else
                {
                    obm = ob1 * ob2;
                }
                //cout << *ob1 << " " << *ob2 << '\n';
            }
            else
            {
                Matrice_patratica obp, ob1, ob2;
                obp = *dynamic_cast<Matrice_patratica*>(A[i]);
                ob1 = *dynamic_cast<Matrice_patratica*>(A[i]);
                ob2 = *dynamic_cast<Matrice_patratica*>(A[j]);
                if(c == 1)
                {
                    obp = ob1 + ob2;
                }
                else if(c == 2)
                {
                    obp = ob1 + ob2;
                }
                else
                {
                    obp = ob1 * ob2;
                }
            }
            //cout << ob3 << '\n';
        }
    }
    while(1);

    //A.erase();
    return 0;
}
