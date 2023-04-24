#include <iostream>
#include <cstring>
#include <list>

using namespace std;

class CitireAfisare
{
public:
    virtual istream& cit(istream&) = 0;
    virtual ostream& afis(ostream&)const=0;
};

class Persoana:public CitireAfisare
{
    static int contor;
    const int NumarInreg;
    int id;
    char *nume;
public:
    Persoana();
    Persoana(int id, char *nume);
    Persoana( const Persoana&);
    ~Persoana();
    Persoana& operator=(const Persoana&);
    virtual ostream& afis(ostream &) const;
    virtual istream& cit(istream&);
    friend istream& operator>>(istream& in, Persoana& p);
    friend ostream& operator<<(ostream& out, const Persoana& p);

    static void afis_contor()
    {
        cout<<contor<<endl;
    }

    int get_id()
    {
        return id;
    }
    char* get_nume()
    {
        return nume;
    }
    void set_id(int id)
    {
        this->id = id;
    }
    void set_nume(char *nume)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy( this->nume, nume);
    }

};
int Persoana ::contor = 0;

Persoana :: Persoana():NumarInreg(contor++)
{
    id = 0;
    nume = NULL;
}

Persoana :: Persoana(int id, char* nume):NumarInreg(contor++)
{
    this->id = id;
    this->nume=new char[strlen(nume)+1];
    strcpy( this->nume, nume);
}

Persoana :: Persoana(const Persoana& pers):NumarInreg(contor)
{
    this->id = pers.id;
    this->nume=new char[strlen(pers.nume)+1];
    strcpy( this->nume, pers.nume);

}

Persoana &Persoana :: operator = (const Persoana &pers)//operator de atribuire
{
    if(this != &pers)
    {
        this->id = pers.id;
        if(this->nume != NULL)
            delete [] this->nume;
        this->nume = new char[strlen(pers.nume)+1];
        strcpy(this->nume, pers.nume);
    }
    return *this;
}

ostream &Persoana ::afis(ostream &out) const
{
    out << this->id<<endl;
    out << this->nume<<endl;
    return out;
}

void eroare_nume(char* nume)
{
    int ok = 1;
    for(int i = 0; i < strlen(nume); i++)
        if(nume[i] < 'A' || nume[i] > 'Z')
            if(nume[i] != ' ')
                ok = 0;
    if(ok!=1)
        throw 2.5;
}
#include <cstring>
istream& Persoana ::cit(istream &in)
{
    char aux[255];
    int k = 1;
    while(k==1)
    {
        char *prenume = new char[127], *nume = new char[127];
        cout<<"Citit numele: (acesta trebuie sa fie scris cu majuscule) ";
        in >> prenume >> nume;
        strcat(aux, prenume); strcat(aux, " "); strcat(aux, nume);
        delete prenume; delete nume;
        cout<<aux;
        try
        {
            eroare_nume(aux);
            this->nume = new char[strlen(aux)+1];
            strcpy(this->nume , aux);
            k = 0;

        }
        catch (double)
        {
            cout<<"Numele nu este valid! "
                  "Reintroduceti\n";


        }
    }

    cout<<"Citit id-ul: ";
    in >> this->id;
    return in;
}

istream& operator >> (istream &in, Persoana &pers)
{
    return pers.cit(in);
}

ostream& operator << (ostream &out, const Persoana &pers)//afisare persoana
{
    return pers.afis(out);
}

Persoana :: ~Persoana()
{
    if(this->nume != NULL)
        delete[] this->nume;
}

class Abonat : public virtual Persoana
{
    char *nr_telefon;
public:
    Abonat();
    Abonat(int id, char *nume, char *nr_telefon);
    Abonat(const Abonat&);
    ~Abonat();
    Abonat& operator=(const Abonat&);
    ostream &afis(ostream &)const;
    istream &cit(istream &);

    char* get_nr_telefon()
    {
        return nr_telefon;
    }
    void set_nr_telefon(char *nr_telefon)
    {
        this->nr_telefon=new char[strlen(nr_telefon)+1];
        strcpy( this->nr_telefon, nr_telefon);
    }
};

Abonat :: Abonat() : Persoana()
{
    nr_telefon = NULL;
}


Abonat :: Abonat(int id, char* nume, char *nr_telefon):Persoana(id, nume)
{
    this->nr_telefon=new char[strlen(nr_telefon)+1];
    strcpy( this->nr_telefon, nr_telefon);
}

Abonat :: Abonat(const Abonat &ab): Persoana(ab)
{
    this->nr_telefon=new char[strlen(ab.nr_telefon)+1];
    strcpy( this->nr_telefon, ab.nr_telefon);
}

Abonat &Abonat :: operator = (const Abonat &ab)
{
    if(this != &ab)
    {
        Persoana::operator=(ab);
        if(this->nr_telefon != NULL)
            delete [] this->nr_telefon;
        this->nr_telefon = new char[strlen(ab.nr_telefon)+1];
        strcpy(this->nr_telefon, ab.nr_telefon);
    }

    return *this;
}

ostream &Abonat :: afis(ostream &out) const
{
    Persoana::afis(out);
    out << this->nr_telefon << endl;
    return out;
}

void eroare(int x)
{
    if(x!=10)
        throw 11;
}

istream &Abonat :: cit(istream &in)
{
    Persoana ::cit(in);
    int k = 1;
    while(k==1)
    {
        cout<<"Citit nr de telefon: ";
        char aux1[255];
        in >> aux1;
        try
        {
            int nr = strlen(aux1);
            eroare(nr);
            this->nr_telefon = new char[strlen(aux1)+1];
            strcpy(this->nr_telefon , aux1);
            k = 0;
        }
        catch (int)
        {
            cout<<"Nr de telefon nu este valid! "
                  "Reintroduceti\n";
        }
    }

    return in;

}

Abonat :: ~Abonat()
{
    if(this->nr_telefon != NULL)
        delete[] this->nr_telefon;
}

class Abonat_Skype : public virtual Abonat
{
    char *id_skype;
public:
    Abonat_Skype();
    Abonat_Skype(int id, char *nume, char *nr_telefon, char *id_skype);
    Abonat_Skype(const Abonat_Skype&);
    ~Abonat_Skype();
    Abonat_Skype& operator=(const Abonat_Skype&);
    ostream &afis(ostream &) const;
    istream &cit(istream &);

    char* get_id_skype()
    {
        return id_skype;
    }
    void set_id_skype(char *id_skype)
    {
        this->id_skype=new char[strlen(id_skype)+1];
        strcpy( this->id_skype, id_skype);
    }


};

Abonat_Skype :: Abonat_Skype() : Abonat()
{
    id_skype = NULL;
}

Abonat_Skype :: Abonat_Skype(int id, char *nume, char *nr_telefon, char *id_skype) : Abonat(id,nume,nr_telefon)
{
    this->id_skype=new char[strlen(id_skype)+1];
    strcpy( this->id_skype, id_skype);

}

Abonat_Skype :: Abonat_Skype(const Abonat_Skype& abs): Abonat(abs)
{
    this->id_skype=new char[strlen(abs.id_skype)+1];
    strcpy( this->id_skype, abs.id_skype);
}

Abonat_Skype &Abonat_Skype :: operator = (const Abonat_Skype &abs)
{
    if(this != &abs)
    {
        Abonat::operator=(abs);
        if(this->id_skype != NULL)
            delete [] this->id_skype;
        this->id_skype = new char[strlen(abs.id_skype)+1];
        strcpy(this->id_skype, abs.id_skype);
    }

    return *this;
}

ostream &Abonat_Skype :: afis(ostream &out) const
{
    Abonat :: afis(out);
    out << this->id_skype << endl;
    return out;
}

istream &Abonat_Skype :: cit(istream &in)
{
    Abonat :: cit(in);
    cout<<"Citit id-ul skype: ";
    char aux1[255];
    in >> aux1;
    this->id_skype = new char[strlen(aux1)+1];
    strcpy(this->id_skype , aux1);
    return in;

}

Abonat_Skype :: ~Abonat_Skype()
{
    if(this->id_skype != NULL)
        delete[] this->id_skype;
}

class Abonat_Skype_Romania : public virtual Abonat_Skype
{
    char *adresa_mail;
public:
    Abonat_Skype_Romania();
    Abonat_Skype_Romania(int id, char *nume, char *nr_telefon, char *id_skype, char *adresa_mail);
    Abonat_Skype_Romania(const Abonat_Skype_Romania&);
    ~Abonat_Skype_Romania();
    Abonat_Skype_Romania& operator=(const Abonat_Skype_Romania&);
    ostream &afis(ostream &) const;
    istream &cit(istream &);

    char* get_adresa_mail()
    {
        return adresa_mail;
    }
    void set_adresa_mail(char *id_skype)
    {
        this->adresa_mail=new char[strlen(adresa_mail)+1];
        strcpy( this->adresa_mail, adresa_mail);
    }

};

Abonat_Skype_Romania :: Abonat_Skype_Romania()
{
    adresa_mail = NULL;
}

Abonat_Skype_Romania :: Abonat_Skype_Romania(int id, char *nume, char *nr_telefon, char *id_skype, char *adresa_mail) : Abonat_Skype(id,nume,nr_telefon,id_skype)
{
    this->adresa_mail=new char[strlen(adresa_mail)+1];
    strcpy( this->adresa_mail, adresa_mail);
}

Abonat_Skype_Romania :: Abonat_Skype_Romania(const Abonat_Skype_Romania &absr): Abonat_Skype(absr)
{
    this->adresa_mail=new char[strlen(absr.adresa_mail)+1];
    strcpy( this->adresa_mail, absr.adresa_mail);
}

Abonat_Skype_Romania &Abonat_Skype_Romania :: operator = (const Abonat_Skype_Romania &absr)
{
    if(this != &absr)
    {
        Abonat_Skype::operator=(absr);
        if(this->adresa_mail != NULL)
            delete [] this->adresa_mail;
        this->adresa_mail = new char[strlen(absr.adresa_mail)+1];
        strcpy(this->adresa_mail, absr.adresa_mail);
    }

    return *this;
}

ostream &Abonat_Skype_Romania :: afis(ostream &out) const
{
    Abonat_Skype :: afis(out);
    out << this->adresa_mail << endl;
    return out;
}

istream &Abonat_Skype_Romania :: cit(istream &in)
{
    Abonat_Skype :: cit(in);
    cout<<"Citit adresa de mail: ";
    char aux1[255];
    in >> aux1;
    this->adresa_mail = new char[strlen(aux1)+1];
    strcpy(this->adresa_mail , aux1);
    return in;

}

Abonat_Skype_Romania :: ~Abonat_Skype_Romania()
{
    if(this->adresa_mail != NULL)
        delete[] this->adresa_mail;
}

class Abonat_Skype_Extern : public virtual Abonat_Skype
{
    char *tara;
public:
    Abonat_Skype_Extern();
    Abonat_Skype_Extern(int id, char *nume, char *nr_telefon, char *id_skype, char *tara);
    Abonat_Skype_Extern(const Abonat_Skype_Extern&);
    ~Abonat_Skype_Extern();
    Abonat_Skype_Extern& operator=(const Abonat_Skype_Extern&);
    ostream &afis(ostream &) const;
    istream &cit(istream &);

    char* get_tara()
    {
        return tara;
    }
    void set_tara(char *id_skype)
    {
        this->tara=new char[strlen(tara)+1];
        strcpy( this->tara, tara);
    }

};

Abonat_Skype_Extern :: Abonat_Skype_Extern() : Abonat_Skype()
{
    tara = NULL;
}

Abonat_Skype_Extern :: Abonat_Skype_Extern(int id, char *nume, char *nr_telefon, char *id_skype, char *tara) : Abonat_Skype(id,nume,nr_telefon,id_skype)
{
    this->tara=new char[strlen(tara)+1];
    strcpy( this->tara, tara);
}

Abonat_Skype_Extern :: Abonat_Skype_Extern(const Abonat_Skype_Extern &abse): Abonat_Skype(abse)
{
    this->tara=new char[strlen(abse.tara)+1];
    strcpy( this->tara, abse.tara);
}

Abonat_Skype_Extern &Abonat_Skype_Extern :: operator = (const Abonat_Skype_Extern &abse)
{
    if(this != &abse)
    {
        Abonat_Skype::operator=(abse);
        if(this->tara != NULL)
            delete [] this->tara;
        this->tara = new char[strlen(abse.tara)+1];
        strcpy(this->tara, abse.tara);
    }

    return *this;
}

ostream &Abonat_Skype_Extern :: afis(ostream &out) const
{
    Abonat_Skype :: afis(out);
    out << this->tara << endl;
    return out;
}

istream &Abonat_Skype_Extern :: cit(istream &in)
{
    Abonat_Skype :: cit(in);
    cout<<"Cititi tara: ";
    char aux1[255];
    in >> aux1;
    this->tara = new char[strlen(aux1)+1];
    strcpy(this->tara , aux1);
    return in;

}

Abonat_Skype_Extern :: ~Abonat_Skype_Extern()
{
    if(this->tara != NULL)
        delete[] this->tara;
}

class Agenda
{
    list<Abonat>list_ab;
    list<Abonat_Skype>list_abs;
    list<Abonat_Skype_Romania>list_absr;
    list<Abonat_Skype_Extern>list_abse;

public:
    Agenda();
    void citire()
    {
        cout<<"Apasati: 1 pentru a citi un abonat\n"
              "         2 pentru a citi un abonat_skype\n"
              "         3 pentru a citi un abonat_skype_romania\n"
              "         4 pentru a citi un abonat_skype_extern\n";
        int z;
        cin>>z;
        if (z == 1)
        {
            Abonat ab;
            cin>>ab;
            list_ab.push_back(ab);
        }
        if (z == 2)
        {
            Abonat_Skype abs;
            cin>>abs;
            cout<<abs<<endl;
            list_abs.push_back(abs);
        }
        if (z == 3)
        {
            Abonat_Skype_Romania absr;
            cout << "AICI" <<endl;
            cin>>absr;
            list_absr.push_back(absr);
        }
        if (z == 4)
        {
            Abonat_Skype_Extern abse;
            cin>>abse;
            list_abse.push_back(abse);
        }
    }

    void afisare()
    {
        if(list_ab.size() > 0)
        {
            list<Abonat>::iterator it;
            cout<<"-------------------Abonati-------------------\n";
            for(it = list_ab.begin(); it != list_ab.end(); it++)
            {
                cout<<"--------------------------------------\n";
                cout<<*it<<endl;
            }
        }

        if(list_abs.size() > 0)
        {
            list<Abonat_Skype>::iterator it;
            cout<<"-------------------Abonati Skype-------------------\n";
            for(it = list_abs.begin(); it != list_abs.end(); it++)
            {
                cout<<"--------------------------------------\n";
                cout<<*it<<endl;
            }
        }

        if(list_absr.size() > 0)
        {
            cout << list_absr.size() << endl;
            list<Abonat_Skype_Romania>::iterator it;
            cout<<"-------------------Abonati Skype Romania-------------------\n";
            for(it = list_absr.begin(); it != list_absr.end(); it++)
            {
                cout<<"--------------------------------------\n";
                cout<<*it<<endl;
            }
        }

        if(list_abse.size() > 0)
        {
            list<Abonat_Skype_Extern>::iterator it;
            cout<<"-------------------Abonati Skype Extern-------------------\n";
            for(it = list_abse.begin(); it != list_abse.end(); it++)
            {
                cout<<"--------------------------------------\n";
                cout<<*it<<endl;
            }
        }
    }

    void afis_ab(char* nume) {
        int ok = 0;
        Abonat ab;
        Abonat_Skype abs;
        Abonat_Skype_Romania absr;
        Abonat_Skype_Extern abse;
        if (list_ab.size() > 0) {
            list<Abonat>::iterator it;
            for (it = list_ab.begin(); it != list_ab.end(); it++) {
                if (it->get_nume() == nume) {
                    ok = 1;
                    ab = *it;
                    break;

                }
            }
        }

        if(list_abs.size() > 0)
        {
            list<Abonat_Skype>::iterator it;
            for(it = list_abs.begin(); it != list_abs.end(); it++)
            {
                if(it->get_nume() == nume)
                {
                    ok = 2;
                    abs = *it;
                    break;

                }
            }
        }

        if(list_absr.size() > 0)
        {
            list<Abonat_Skype_Romania>::iterator it;
            for(it = list_absr.begin(); it != list_absr.end(); it++)
            {
                if(it->get_nume() == nume)
                {
                    ok = 3;
                    absr = *it;
                    break;

                }
            }
        }

        if(list_abse.size() > 0)
        {
            list<Abonat_Skype_Extern>::iterator it;
            for(it = list_abse.begin(); it != list_abse.end(); it++)
            {
                if(it->get_nume() == nume)
                {
                    ok = 4;
                    abse = *it;
                    break;

                }
            }
        }
        if(ok == 0)
            cout<<"Abonatul nu exista"<<endl;
        if(ok == 1)
            cout<<ab<<endl;
        if(ok == 2)
            cout<<abs<<endl;
        if(ok == 3)
            cout<<absr<<endl;
        if(ok == 4)
            cout<<abse<<endl;
    }


};

Agenda::Agenda()
{
    list_ab = {};
    list_abs = {};
    list_absr = {};
    list_abse = {};
}

int main()
{
    Agenda agenda;
    while(true)
    {
        cout<<"Apasati: 1 pentru a adauga un abonat\n"
              "         2 pentru a afisa toti abonatii\n"
              "         3 pentru a afisa un abonat anume\n"
              "         4 pentru a iesi\n";
        int x;
        cin>>x;
        if(x == 1)
        {
            agenda.citire();
        }

        if(x == 2)
        {
            agenda.afisare();
        }

        if(x == 3)
        {
            cout<<"Cititi numele abonatului: ";
            char *nume;
            cin>>nume;
            agenda.afis_ab(nume);

        }

        if(x == 4)
            break;
    }

    return 0;
}
