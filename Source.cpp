#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

class Actor
{
private:
    const int id;
    char* nume;
    char* prenume;
    int nrNote;
    int* noteCasting;
    static int contor;
public:
    Actor() :id(contor++) 
    {
        this->nume = new char[1];
        strcpy(this->nume, "");
        this->prenume = new char[1];
        strcpy(this->prenume, "");
        this->noteCasting = new int[1];
        this->nrNote = 0;
    }
    Actor(const char* nume, const char* prenume, const int* noteCasting, int nrNote) :id(contor++)
    {
        if (nume == nullptr)
            this->nume = nullptr;
        else {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }

        if (prenume == nullptr)
            this->prenume = nullptr;
        else {
            this->prenume = new char[strlen(prenume) + 1];
            strcpy_s(this->prenume, strlen(prenume) + 1, prenume);
        }

        if (noteCasting == nullptr)
            this->noteCasting = nullptr;
        else {
            this->noteCasting = new int[nrNote];
            for (int i = 0; i < nrNote; i++)
                this->noteCasting[i] = noteCasting[i];
        }

        this->nrNote = nrNote;
    }

    Actor(const Actor& a) :id(contor++)
    {
        if (a.nume == nullptr)
            this->nume = nullptr;
        else {
            this->nume = new char[strlen(a.nume) + 1];
            strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
        }

        if (a.prenume == nullptr)
            this->prenume = nullptr;
        else {
            this->prenume = new char[strlen(a.prenume) + 1];
            strcpy_s(this->prenume, strlen(a.prenume) + 1, a.prenume);
        }

        if (a.noteCasting == nullptr)
            this->noteCasting = nullptr;
        else {
            this->noteCasting = new int[a.nrNote];
            for (int i = 0; i < a.nrNote; i++)
                this->noteCasting[i] = a.noteCasting[i];
        }

        this->nrNote = a.nrNote;
    }

    Actor operator =(const Actor& a)
    {
        if (a.nume == nullptr)
            this->nume = nullptr;
        else {
            this->nume = new char[strlen(a.nume) + 1];
            strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
        }

        if (a.prenume == nullptr)
            this->prenume = nullptr;
        else {
            this->prenume = new char[strlen(a.prenume) + 1];
            strcpy_s(this->prenume, strlen(a.prenume) + 1, a.prenume);
        }

        if (a.noteCasting == nullptr)
            this->noteCasting = nullptr;
        else {
            this->noteCasting = new int[a.nrNote];
            for (int i = 0; i < a.nrNote; i++)
                this->noteCasting[i] = a.noteCasting[i];
        }

        return*this;
    }

    void setNume(const char* nume) {
        if (this->nume != nullptr)
            delete[] this->nume;
        this->nume = new char[strlen(nume) + 1];
        strcpy_s(this->nume, strlen(nume) + 1, nume);
    }

    char* getNume() {
        return this->nume;
    }

    void setPrenume(const char* prenume) {
        if (this->prenume != nullptr)
            delete[] this->prenume;
        this->prenume = new char[strlen(prenume) + 1];
        strcpy_s(this->nume, strlen(prenume) + 1, prenume);
    }

    char* getPrenume() {
        return this->prenume;
    }

    void setNoteCasting(const int* noteCasting, int nrNote) {
        if (this->noteCasting != nullptr)
            delete[] this->noteCasting;
        this->noteCasting = new int[nrNote];
        for (int i = 0; i < nrNote; i++)
            this->noteCasting[i] = noteCasting[i];
    }

    int* getNoteCasting() {
        return this->noteCasting;
    }

    void setNrNote(int nrNote) {
        this->nrNote = nrNote;
    }

    int getNrNote() {
        return this->nrNote;
    }


    /* supraincarcarea operatorul index */
    int& operator[](int index)
    {
        if (index > 0 && index < this->nrNote) return this->noteCasting[index];
        else throw new exception("Index invalid");
    }

    /* supraincarcarea operatorul + */
    Actor operator+(Actor a)
    {
        Actor temp = *this;

        temp.nrNote += a.nrNote;

        void* p = realloc(temp.noteCasting, temp.nrNote);

        if (p != nullptr) {
            temp.noteCasting = (int*)p;

            int j = 0;
            for (int i = temp.nrNote - a.nrNote; i < temp.nrNote; i++)
                temp.noteCasting[i] = a.noteCasting[j++];
        }

        return temp;
    }

    /* supraincarcarea operatorul ++ */
    Actor operator++()
    {
        Actor temp = *this;

        temp.nrNote ++;
        
        void* p = realloc(temp.noteCasting, temp.nrNote);

        if (p != nullptr) {
            temp.noteCasting = (int*)p;
            temp.noteCasting[temp.nrNote - 1] = -1;
        }
        return*this;
    }

    /* supraincarcarea operator ++ */
    Actor operator++(int)
    {
        Actor temp = *this;

        temp.nrNote++;
        void* p = realloc(temp.noteCasting, temp.nrNote);

        if (p != nullptr) {
            temp.noteCasting = (int*)p;
            temp.noteCasting[temp.nrNote - 1] = -1;
        }
        return*this;
    }

    /* supraincarcarea operator int() (castare) */
    operator int()
    {
        return this->nrNote;
    }

    /* supraincarcarea operator ! (not) */
    bool operator!()
    {
        return this->nrNote <= 0;
    }

    /* supraincarcarea operator == */
    bool operator ==(Actor a)
    {
        return strcmp(this->nume, a.nume) == 0 &&  strcmp(this->prenume, a.prenume) == 0;
    }

    /* supraincarcarea operator >= */
    bool operator >=(Actor a)
    {
        return this->nrNote >= a.nrNote;
    }

    /* destructor */
    ~Actor()
    {
        if (this->nume != nullptr)
            delete[] this->nume;
        if (this->prenume != nullptr)
            delete[] this->prenume;
        if (this->noteCasting != nullptr)
            delete[] this->noteCasting;
        contor--;
    }

    /* supraincarcarea operator << (afisare stdout) */
    friend void operator <<(ostream& iesire, Actor a);

    /* supraincarcarea operator >> (citire stdin) */
    friend istream& operator >>(istream& intrare, Actor& a);
};
/* initializare camp static contor = 0 */
int Actor::contor = 0;

/* implementare operator << */
void operator <<(ostream& out, Actor a)
{
    out << "Nume: " << a.getNume() << '\n';
    out << "Prenume: " << a.getPrenume() << '\n';
    out << "Note casting: ";
    int* noteCasting = a.getNoteCasting();
    for (int i = 0; i < a.getNrNote(); i++)
        out << noteCasting[i] << ' ';
    out << endl;
}

/* implementare operator >> */
istream& operator >> (istream& in, Actor& a)
{
    char temp[30];
    cout << "Nume actor: ";
    in >> temp;
    a.setNume(temp);

    cout << "Prenume actor: ";
    in >> temp;
    a.setPrenume(temp);

    int nrNote;
    cout << "Numar actori: ";
    in >> nrNote;
    a.setNrNote(nrNote);

    int* noteCasting = new int[nrNote];
    
    cout << "Citeste note: ";
    for (int i = 0; i < nrNote; i++)
    {
        in >> noteCasting[i];
    }

    a.setNoteCasting(noteCasting, nrNote);
    return in;
}

class Recenzie {
private:
    const int id;
    char* text;
    int* aprecieriRaspunsuri;
    int nrRaspunsuri;
    static int contor;
public:
    Recenzie() :id(contor++)
    {
        this->text = new char[1];
        strcpy(this->text, "");
        this->aprecieriRaspunsuri = new int[1];
        this->nrRaspunsuri = 0;
    }
    Recenzie(const char* text, const int* aprecieriRaspunsuri, int nrRaspunsuri) :id(contor++)
    {
        if (text == nullptr)
            this->text = nullptr;
        else {
            this->text = new char[strlen(text) + 1];
            strcpy_s(this->text, strlen(text) + 1, text);
        }

        if (aprecieriRaspunsuri == nullptr)
            this->aprecieriRaspunsuri = nullptr;
        else {
            this->aprecieriRaspunsuri = new int[nrRaspunsuri];
            for (int i = 0; i < nrRaspunsuri; i++)
                this->aprecieriRaspunsuri[i] = aprecieriRaspunsuri[i];
        }

        this->nrRaspunsuri = nrRaspunsuri;
    }

    Recenzie(const Recenzie& r) :id(contor++)
    {
        if (r.text == nullptr)
            this->text = nullptr;
        else {
            this->text = new char[strlen(r.text) + 1];
            strcpy_s(this->text, strlen(r.text) + 1, r.text);
        }

        if (r.aprecieriRaspunsuri == nullptr)
            this->aprecieriRaspunsuri = nullptr;
        else {
            this->aprecieriRaspunsuri = new int[r.nrRaspunsuri];
            for (int i = 0; i < r.nrRaspunsuri; i++)
                this->aprecieriRaspunsuri[i] = r.aprecieriRaspunsuri[i];
        }

        this->nrRaspunsuri = r.nrRaspunsuri;
    }

    Recenzie operator =(const Recenzie& r)
    {
        if (r.text == nullptr)
            this->text = nullptr;
        else {
            this->text = new char[strlen(r.text) + 1];
            strcpy_s(this->text, strlen(r.text) + 1, r.text);
        }

        if (r.aprecieriRaspunsuri == nullptr)
            this->aprecieriRaspunsuri = nullptr;
        else {
            this->aprecieriRaspunsuri = new int[r.nrRaspunsuri];
            for (int i = 0; i < r.nrRaspunsuri; i++)
                this->aprecieriRaspunsuri[i] = r.aprecieriRaspunsuri[i];
        }

        this->nrRaspunsuri = r.nrRaspunsuri;

        return *this;
    }

    void setText(const char* text) {
        if (this->text != nullptr)
            delete[] this->text;
        this->text = new char[strlen(text) + 1];
        strcpy_s(this->text, strlen(text) + 1, text);
    }

    char* getText() {
        return this->text;
    }

    void setAprecieriRaspunsuri(const int* aprecieriRaspunsuri, int nrRaspunsuri) {
        if (this->aprecieriRaspunsuri != nullptr)
            delete[] this->aprecieriRaspunsuri;
        this->aprecieriRaspunsuri = new int[nrRaspunsuri];
        for (int i = 0; i < nrRaspunsuri; i++)
            this->aprecieriRaspunsuri[i] = aprecieriRaspunsuri[i];
    }

    int* getAprecieriRaspunsuri() {
        return this->aprecieriRaspunsuri;
    }

    void setNrRaspunsuri(int nrRaspunsuri) {
        this->nrRaspunsuri = nrRaspunsuri;
    }

    int getNrRaspunsuri() {
        return this->nrRaspunsuri;
    }


    /* supraincarcarea operatorul index */
    int& operator[](int index)
    {
        if (index > 0 && index < this->nrRaspunsuri) return this->aprecieriRaspunsuri[index];
        else throw new exception("Index invalid");
    }

    /* supraincarcarea operatorul + */
    Recenzie operator+(Recenzie r)
    {
        Recenzie temp = *this;

        temp.nrRaspunsuri += r.nrRaspunsuri;

        void* p = realloc(temp.aprecieriRaspunsuri, temp.nrRaspunsuri);

        if (p != nullptr) {
            temp.aprecieriRaspunsuri = (int*)p;

            int j = 0;
            for (int i = temp.nrRaspunsuri - r.nrRaspunsuri; i < temp.nrRaspunsuri; i++)
                temp.aprecieriRaspunsuri[i] = r.aprecieriRaspunsuri[j++];
        }

        return temp;
    }

    /* supraincarcarea operatorul ++ */
    Recenzie operator++()
    {
        Recenzie temp = *this;

        temp.nrRaspunsuri++;

        void* p = realloc(temp.aprecieriRaspunsuri, temp.nrRaspunsuri);

        if (p != nullptr) {
            temp.aprecieriRaspunsuri = (int*)p;
            temp.aprecieriRaspunsuri[temp.nrRaspunsuri - 1] = -1;
        }
        return *this;
    }

    /* supraincarcarea operator ++ */
    Recenzie operator++(int)
    {
        Recenzie temp = *this;

        temp.nrRaspunsuri++;

        void* p = realloc(temp.aprecieriRaspunsuri, temp.nrRaspunsuri);

        if (p != nullptr) {
            temp.aprecieriRaspunsuri = (int*)p;
            temp.aprecieriRaspunsuri[temp.nrRaspunsuri - 1] = -1;
        }
        return *this;
    }

    /* supraincarcarea operator int() (castare) */
    operator int()
    {
        return this->nrRaspunsuri;
    }

    /* supraincarcarea operator ! (not) */
    bool operator!()
    {
        return this->nrRaspunsuri <= 0;
    }

    /* supraincarcarea operator == */
    bool operator ==(Recenzie r)
    {
        return strcmp(this->text, r.text) == 0 && strcmp(this->text, r.text) == 0;
    }

    /* supraincarcarea operator >= */
    bool operator >=(Recenzie r)
    {
        return this->nrRaspunsuri >= r.nrRaspunsuri;
    }

    /* destructor */
    ~Recenzie()
    {
        if (this->text != nullptr)
            delete[] this->text;
        if (this->aprecieriRaspunsuri != nullptr)
            delete[] this->aprecieriRaspunsuri;
        contor--;
    }

    /* supraincarcarea operator << (afisare stdout) */
    friend void operator <<(ostream& iesire, Recenzie f);

    /* supraincarcarea operator >> (citire stdin) */
    friend istream& operator >>(istream& intrare, Recenzie& f);
};
/* initializare camp static contor = 0 */
int Recenzie::contor = 0;

/* implementare operator << */
void operator <<(ostream& out, Recenzie r)
{
    out << "Text: " << r.getText() << '\n';
    out << "Aprecieri raspunsuri: ";
    int* aprecieriRaspunsuri = r.getAprecieriRaspunsuri();
    for (int i = 0; i < r.getNrRaspunsuri(); i++)
        out << aprecieriRaspunsuri[i] << ' ';
    out << endl;
}

/* implementare operator >> */
istream& operator >> (istream& in, Recenzie& r)
{
    char temp[100];
    cout << "Text: ";
    in >> temp;
    r.setText(temp);

    int nrRaspunsuri;
    cout << "Numar raspunsuri: ";
    in >> nrRaspunsuri;
    r.setNrRaspunsuri(nrRaspunsuri);

    int* aprecieriRaspunsuri = new int[nrRaspunsuri];

    cout << "Aprecieri raspunsuri: ";
    for (int i = 0; i < nrRaspunsuri; i++)
    {
        in >> aprecieriRaspunsuri[i];
    }

    r.setAprecieriRaspunsuri(aprecieriRaspunsuri, nrRaspunsuri);
    return in;
}

/* declarare si implementare clasa film */
class Film
{
private:
    const int id;
    char* denumire;
    int* ratingEpisoade;
    int nrEpisoade;
    static int contor;
public:
    /* Constructor fara parametrii */
    Film() :id(contor++)
    {
        this->denumire = new char[1];
        strcpy(this->denumire, "");
        this->ratingEpisoade = new int[1];
        this->nrEpisoade = 0;
    }

    /* Constructor cu parametrii */
    Film(const char* denumire, int* ratingEpisoade, int nrEpisoade) :id(contor++)
    {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
        this->nrEpisoade = nrEpisoade;
        this->ratingEpisoade = new int[this->nrEpisoade];
        for (int i = 0; i < this->nrEpisoade; i++)
            this->ratingEpisoade[i] = ratingEpisoade[i];
    }
    /* contructor de copiere */
    Film(const Film& f) :id(contor++)
    {
        this->denumire = new char[strlen(f.denumire) + 1];
        strcpy_s(this->denumire, strlen(f.denumire) + 1, f.denumire);
        this->nrEpisoade = f.nrEpisoade;
        this->ratingEpisoade = new int[this->nrEpisoade];
        for (int i = 0; i < this->nrEpisoade; i++)
            this->ratingEpisoade[i] = f.ratingEpisoade[i];
    }

    /* operator egal */
    Film operator =(const Film& f)
    {
        if (this->denumire != nullptr)
            delete[] this->denumire;
        if (this->ratingEpisoade != nullptr)
            delete[] this->ratingEpisoade;
        this->denumire = new char[strlen(f.denumire) + 1];
        strcpy_s(denumire, strlen(f.denumire) + 1, f.denumire);
        this->nrEpisoade = f.nrEpisoade;
        this->ratingEpisoade = new int[this->nrEpisoade];
        for (int i = 0; i < this->nrEpisoade; i++)
            this->ratingEpisoade[i] = f.ratingEpisoade[i];
        return*this;
    }

    /* setteri si getteri */
    void setDenumire(const char* denumirenoua)
    {
        this->denumire = new char[strlen(denumirenoua) + 1];
        strcpy_s(this->denumire, strlen(denumirenoua) + 1, denumirenoua);
    }

    /* getter denumire */
    char* getDenumire()
    {
        return this->denumire;
    }

    /* setter nr episoade */
    void setNrEpisoade(int nrEpisoade)
    {
        this->nrEpisoade = nrEpisoade;
    }

    /* getter nr episoade */
    int getNrEpisoade()
    {
        return this->nrEpisoade;
    }

    /* getter ratinguri episoade */
    int* getVarsteActori()
    {
        return this->ratingEpisoade;
    }

    /* setter ratinguri episoade */
    void setVarsteActori(int nrEpisoade, int* ratingEpisoade) {
        if (ratingEpisoade != nullptr) {
            delete[] this->ratingEpisoade;

            this->ratingEpisoade = new int[nrEpisoade];
            for (int i = 0; i < nrEpisoade; i++) {
                this->ratingEpisoade[i] = ratingEpisoade[i];
            }
        }
        else
            this->ratingEpisoade = nullptr;
    }

    /* supraincarcarea operatorul index */
    int& operator[](int index)
    {
        if (index > 0 && index < nrEpisoade) return this->ratingEpisoade[index];
        else throw new exception("Index invalid");
    }

    /* supraincarcarea operatorul + */
    Film operator+(Film f)
    {
        Film temp = *this;

        temp.nrEpisoade += f.nrEpisoade;

        void* p = realloc(temp.ratingEpisoade, temp.nrEpisoade);

        if (p != nullptr)
        {
            temp.ratingEpisoade = (int*)p;
            int j = 0;
            for (int i = temp.nrEpisoade - f.nrEpisoade; i < temp.nrEpisoade; i++)
                temp.ratingEpisoade[i] = f.ratingEpisoade[j++];
        }

        return temp;
    }

    /* supraincarcarea operatorul ++ */
    Film operator++()
    {
        Film temp = *this;

        temp.nrEpisoade++;

        void* p = realloc(temp.ratingEpisoade, temp.nrEpisoade);

        if (p != nullptr)
        {
            temp.ratingEpisoade = (int*)p;
            temp.ratingEpisoade[temp.nrEpisoade - 1] = -1;
        }
        return *this;
    }

    /* supraincarcarea operator ++ */
    Film operator++(int)
    {
        Film temp = *this;

        temp.nrEpisoade++;
        void* p = realloc(temp.ratingEpisoade, temp.nrEpisoade);

        if (p != nullptr)
        {
            temp.ratingEpisoade = (int*)p;
            temp.ratingEpisoade[temp.nrEpisoade - 1] = -1;
        }
        return *this;
    }

    /* supraincarcarea operator int() (castare) */
    operator int()
    {
        return nrEpisoade;
    }

    /* supraincarcarea operator ! (not) */
    bool operator!()
    {
        return nrEpisoade <= 0;
    }

    /* supraincarcarea operator == */
    bool operator ==(Film f)
    {
        return strcmp(this->denumire, f.denumire) == 0;
    }

    /* supraincarcarea operator >= */
    bool operator >=(Film f)
    {
        return this->nrEpisoade >= f.nrEpisoade;
    }

    /* destructor */
    ~Film()
    {

        if (this->denumire != nullptr)
            delete[] this->denumire;
        if (this->ratingEpisoade != nullptr)
            delete[] this->ratingEpisoade;
        contor--;
    }

    /* supraincarcarea operator << (afisare stdout) */
    friend void operator <<(ostream& iesire, Film f);

    /* supraincarcarea operator >> (citire stdin) */
    friend istream& operator >>(istream& intrare, Film& f);

};
/* initializare camp static contor = 0 */
int Film::contor = 0;

/* implementare operator << */
void operator <<(ostream& out, Film f)
{
    out << "Denumire: " <<  f.denumire << '\n';
    out << "Ratinguri episoade: " << '\n';
    for (int i = 0; i < f.nrEpisoade; i++)
        out << f.ratingEpisoade[i] << ' ';
    out << endl;
}

/* implementare operator >> */
istream& operator >> (istream& in, Film& f)
{
    char temp[30];
    cout << "Denumire: ";
    in >> temp;
    f.setDenumire(temp);

    cout << "Numar episoade: ";
    in >> f.nrEpisoade;
    cout << "Ratinguri episoade: ";
    for (int i = 0; i < f.nrEpisoade; i++)
    {
        in >> f.ratingEpisoade[i];
    }
    return in;
}

/* declarare si implementare clasa bilet */
class Bilet
{
private:
    const int id;
    char* metodaPlata;
    float* preturiCategorii;
    int nrCategorii;
    static int contor;
public:
    /* constructor fara parametru */
    Bilet():id(contor++)
    {
        this->metodaPlata = new char[1];
        strcpy(this->metodaPlata, "");
        this->preturiCategorii = new float[1];
        this->nrCategorii = 0;
    }

    /* constructor fara parametru */
    Bilet(const char* metodaPlata, float* preturiCategorii, int nrCategorii):id(contor++)
    {
        this->metodaPlata = new char[strlen(metodaPlata) + 1];
        strcpy_s(this->metodaPlata, strlen(metodaPlata) + 1, metodaPlata);
        this->nrCategorii = nrCategorii;
        this->preturiCategorii = new float[this->nrCategorii];
        for (int i = 0; i < this->nrCategorii; i++)
            this->preturiCategorii[i] = preturiCategorii[i];
    }

    /* constructor de copiere */
    Bilet(const Bilet& b) :id(contor++)
    {
        this->metodaPlata = new char[strlen(b.metodaPlata) + 1];
        strcpy_s(this->metodaPlata, strlen(b.metodaPlata) + 1, b.metodaPlata);
        this->nrCategorii = b.nrCategorii;
        this->preturiCategorii = new float[this->nrCategorii];
        for (int i = 0; i < this->nrCategorii; i++)
            this->preturiCategorii[i] = b.preturiCategorii[i];
    }

    /* suprascriere operator = */
    Bilet operator=(const Bilet& b)
    {
        if (this->metodaPlata != nullptr)
            delete[] this->metodaPlata;
        if (this->preturiCategorii != nullptr)
            delete[] this->preturiCategorii;
        this->metodaPlata = new char[strlen(b.metodaPlata) + 1];
        strcpy_s(this->metodaPlata, strlen(b.metodaPlata) + 1, b.metodaPlata);
        this->nrCategorii = b.nrCategorii;
        this->preturiCategorii = new float[this->nrCategorii];
        for (int i = 0; i < this->nrCategorii; i++)
            this->preturiCategorii[i] = b.preturiCategorii[i];
        return*this;
    }

    /* destructor */
    ~Bilet()
    {
        delete[] this->metodaPlata;
        delete[] this->preturiCategorii;
        contor--;
    }

    /* setter numar categorii*/
    void setNrCategorii(int nrCategorii)
    {
        if (nrCategorii > 0) {
            this->nrCategorii = nrCategorii;
        }
    }

    /* getter nr categorii */
    int getNrCategorii() {
        return this->nrCategorii;
    }

    /* getter metoda plata */
    char* getMetodaPlata()
    {
        return this->metodaPlata;
    }

    /* setter metoda plata */
    void setMetodaPlata(const char* metodaPlata)
    {
        if (this->metodaPlata != nullptr)
            delete[] this->metodaPlata;
        this->metodaPlata = new char[strlen(metodaPlata) + 1];
        strcpy_s(this->metodaPlata, strlen(metodaPlata) + 1, metodaPlata);
    }

    /* getter preturi categorii */
    float* getPreturiCategorii()
    {
        return this->preturiCategorii;
    }

    /* setter preturi categorii */
    void setPreturiCategorii(int nrCategorii, float* preturiCategorii) {
        if (this->preturiCategorii != nullptr)
            delete[] this->preturiCategorii;
        this->preturiCategorii = new float[nrCategorii];
        for (int i = 0; i < nrCategorii; i++)
            this->preturiCategorii[i] = preturiCategorii[i];
    }

    /* supraincarcarea operator [] (index) */
    float& operator[](int index)
    {
        if (index > 0 && index < this->nrCategorii) return this->preturiCategorii[index];
        else throw new exception("Index invalid");
    }

    /* supraincarcarea operator ++ */
    Bilet operator++() {
        Bilet temp = *this;

        temp.nrCategorii++;

        void* p = realloc(temp.preturiCategorii, temp.nrCategorii);

        if (p != nullptr) {
            temp.preturiCategorii = (float*)p;
            temp.preturiCategorii[temp.nrCategorii - 1] = -1;
        }
        return *this;
    }

    /* supraincarcarea operator ++ */
    Bilet operator++(int) {
        Bilet temp = *this;

        temp.nrCategorii++;

        void* p = realloc(temp.preturiCategorii, temp.nrCategorii);

        if (p != nullptr) {
            temp.preturiCategorii = (float*)p;
            temp.preturiCategorii[temp.nrCategorii - 1] = -1;
        }
        return *this;
    }

    /* supraincarcarea operator castare int() */
    explicit operator int() {
        return this->nrCategorii;
    }

    /* supraincarcarea operator + */
    Bilet operator+(Bilet b)
    {
        Bilet temp = *this;

        temp.nrCategorii += b.nrCategorii;

        void* p = realloc(temp.preturiCategorii, temp.nrCategorii);

        if (p != nullptr) {
            temp.preturiCategorii = (float*)p;

            int j = 0;
            for (int i = temp.nrCategorii - b.nrCategorii; i < temp.nrCategorii; i++)
                temp.preturiCategorii[i] = b.preturiCategorii[j++];
        }

        return temp;
    }
    
    /* supraincarcarea operator ! (not) */
    bool operator!()
    {
        if (this->nrCategorii > 0)
            return true;
        else return false;
    }

    /* supraincarcarea operator == ( egalitate ) */
    bool operator == (Bilet& b)
    {
        return strcmp(this->metodaPlata, b.metodaPlata) == 0;
    }

    /* supraincarcarea operator > */
    bool operator >(Bilet b) {
        return this->nrCategorii > b.nrCategorii;
    }

    /* supraincarcarea operator << ( afisare stdout ) */
    friend void operator<< (ostream& out, Bilet b);

    /* supraincarcarea operator >> ( citire stdin ) */
    friend istream& operator >> (istream& in, Bilet& b);

};
/* initializarea campului static TVA cu 0 */
int Bilet::contor = 0;

/* implementare suprascriere operator << */
void operator <<(ostream& out, Bilet b)
{
    out << "Metoda plata: " << b.metodaPlata << '\n';
    out << "Preturi categorii: " << '\n';
    for (int i = 0; i < b.nrCategorii; i++)
        out << b.preturiCategorii[i] << ' ';
    out << endl;
}

/* implementare suprascriere operator >> */
istream& operator >> (istream& in, Bilet& b)
{
    char temp[30];
    cout << "Metoda plata: ";
    in >> temp;
    b.setMetodaPlata(temp);

    cout << "Numar categorii: ";
    in >> b.nrCategorii;
    cout << "Preturi categorii: ";
    for (int i = 0; i < b.nrCategorii; i++)
    {
        in >> b.preturiCategorii[i];
    }
    return in;
}

/* Declarare si implementare clasa cinematograf*/
class Cinematograf
{
private:
    const int id;
    char* denumire;
    int* nrLocuriSali;
    int nrSali;
    static int contor;
public:
    /* constructor fara parametrii */
    Cinematograf() :id(contor++)
    {
        this->denumire = new char[1];
        strcpy(this->denumire, "");
        this->nrLocuriSali = new int[1];
        this->nrSali = 0;
    }

    /* constructor fara parametru */
    Cinematograf(const char* denumire, int* nrLocuriSali, int nrSali) :id(contor++)
    {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
        this->nrSali = nrSali;
        this->nrLocuriSali = new int[this->nrSali];
        for (int i = 0; i < this->nrSali; i++)
            this->nrLocuriSali[i] = nrLocuriSali[i];
    }

    /* constructor de copiere */
    Cinematograf(const Cinematograf& c) :id(contor++)
    {
        this->denumire = new char[strlen(c.denumire) + 1];
        strcpy_s(this->denumire, strlen(c.denumire) + 1, c.denumire);
        this->nrSali = c.nrSali;
        this->nrLocuriSali = new int[this->nrSali];
        for (int i = 0; i < this->nrSali; i++)
            this->nrLocuriSali[i] = c.nrLocuriSali[i];
    }

    /* suprascriere operator = */
    Cinematograf operator=(const Cinematograf& c)
    {
        if (this->denumire != nullptr)
            delete[] this->denumire;
        if (this->nrLocuriSali != nullptr)
            delete[] this->nrLocuriSali;
        this->denumire = new char[strlen(c.denumire) + 1];
        strcpy_s(this->denumire, strlen(c.denumire) + 1, c.denumire);
        this->nrSali = c.nrSali;
        this->nrLocuriSali = new int[this->nrSali];
        for (int i = 0; i < this->nrSali; i++)
            this->nrLocuriSali[i] = c.nrLocuriSali[i];
        return*this;
    }

    /* destructor */
    ~Cinematograf()
    {
        delete[] this->denumire;
        delete[] this->nrLocuriSali;
        contor--;
    }

    /* setter numar sali*/
    void setNrSali(int nrSali)
    {
        if (nrSali > 0) {
            this->nrSali = nrSali;
        }
    }

    /* getter nr sali */
    int getNrSali() {
        return this->nrSali;
    }

    /* getter denumire */
    char* getDenumire()
    {
        return this->denumire;
    }

    /* setter denumire */
    void setDenumire(const char* denumire)
    {
        if (this->denumire != nullptr)
            delete[] this->denumire;
        this->denumire = new char[strlen(denumire) + 1];
        strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
    }

    /* getter nr locuri sali */
    int* getNrLocuriSali()
    {
        return this->nrLocuriSali;
    }

    /* setter nr locuri sali */
    void setPreturiCategorii(int nrSali, float* nrLocuriSali) {
        if (this->nrLocuriSali != nullptr)
            delete[] this->nrLocuriSali;
        this->nrLocuriSali = new int[nrSali];
        for (int i = 0; i < nrSali; i++)
            this->nrLocuriSali[i] = nrLocuriSali[i];
    }

    /* supraincarcarea operator [] (index) */
    int& operator[](int index)
    {
        if (index > 0 && index < this->nrSali) return this->nrLocuriSali[index];
        else throw new exception("Index invalid");
    }

    /* supraincarcarea operator ++ */
    Cinematograf operator++() {
        Cinematograf temp = *this;

        temp.nrSali++;

        void* p = realloc(temp.nrLocuriSali, temp.nrSali);

        if (p != nullptr) {
            temp.nrLocuriSali = (int*)p;
            temp.nrLocuriSali[temp.nrSali - 1] = -1;
        }
        return *this;
    }

    /* supraincarcarea operator ++ */
    Cinematograf operator++(int) {
        Cinematograf temp = *this;

        temp.nrSali++;

        void* p = realloc(temp.nrLocuriSali, temp.nrSali);

        if (p != nullptr) {
            temp.nrLocuriSali = (int*)p;
            temp.nrLocuriSali[temp.nrSali - 1] = -1;
        }
        return *this;
    }

    /* supraincarcarea operator castare int() */
    explicit operator int() {
        return this->nrSali;
    }

    /* supraincarcarea operator + */
    Cinematograf operator+(Cinematograf c)
    {
        Cinematograf temp = *this;

        temp.nrSali += c.nrSali;

        void* p = realloc(temp.nrLocuriSali, temp.nrSali);

        if (p != nullptr) {
            temp.nrLocuriSali = (int*)p;

            int j = 0;
            for (int i = temp.nrSali - c.nrSali; i < temp.nrSali; i++)
                temp.nrLocuriSali[i] = c.nrLocuriSali[j++];
        }

        return temp;
    }

    /* supraincarcarea operator ! (not) */
    bool operator!()
    {
        if (this->nrSali > 0)
            return true;
        else return false;
    }

    /* supraincarcarea operator == ( egalitate ) */
    bool operator == (Cinematograf& c)
    {
        return strcmp(this->denumire, c.denumire) == 0;
    }

    /* supraincarcarea operator > */
    bool operator >(Cinematograf b) {
        return this->nrSali > b.nrSali;
    }

    /* supraincarcarea operator << ( afisare stdout ) */
    friend void operator<< (ostream& out, Cinematograf c);

    /* supraincarcarea operator >> ( citire stdin ) */
    friend istream& operator >> (istream& in, Cinematograf& c);

};
/* initializarea campului static TVA cu 0 */
int Cinematograf::contor = 0;

/* implementare suprascriere operator << */
void operator <<(ostream& out, Cinematograf c)
{
    out << "Denumire: " << c.denumire << '\n';
    out << "Numar locuri per sala: " << '\n';
    for (int i = 0; i < c.nrSali; i++)
        out << c.nrLocuriSali[i] << ' ';
    out << endl;
}

/* implementare suprascriere operator >> */
istream& operator >> (istream& in, Cinematograf& c)
{
    char temp[30];
    cout << "Denumire: ";
    in >> temp;
    c.setDenumire(temp);

    cout << "Numar sali: ";
    in >> c.nrSali;
    cout << "Nr locuri per sala: ";
    for (int i = 0; i < c.nrSali; i++)
    {
        in >> c.nrLocuriSali[i];
    }
    return in;
}

int main()
{
    cout << "========== Test clasa Actor ==========\n";
    Actor a1;
    cout << a1;
    Actor a2("Silvester", "Stallone", new int[3]{ 4,5,6 }, 3);
    cout << '\n';
    cout << a2;
    Actor a3 = a2;
    cout << '\n';
    cout << a3;
    Actor a4;
    a4 = a1;
    cout << '\n';
    cout << a4;
    a2.setNume("Nicolas");
    cout << a2.getNume() << '\n';
    cout << "======================================\n";

    cout << "\n======== Test clasa Recenzie =========\n";
    Recenzie r1;
    cout << r1;
    Recenzie r2("Text recenzie", new int[3]{ 2, 4, 1 }, 3);
    cout << '\n';
    cout << r2;
    Recenzie r3 = r2;
    cout << '\n';
    cout << r3;
    Recenzie r4;
    r4 = r1;
    cout << '\n';
    cout << r4;
    r2.setText("Nou text recenzie");
    cout << r2.getText() << '\n';
    cout << "======================================\n";

    cout << "\n========== Test clasa Film ===========\n";
    Film f1;
    cout << f1;
    Film f2("Prison Break", new int[2]{ 2, 6 }, 2);
    cout << '\n';
    cout << f2;
    Film f3 = f2;
    cout << '\n';
    cout << f3;
    Film f4;
    f4 = f1;
    cout << '\n';
    cout << f4;
    f2.setDenumire("Amintiri din copilarie");
    cout << f2.getDenumire() << '\n';
    cout << "======================================\n";

    cout << "\n========== Test clasa Bilet ==========\n";
    Bilet b1;
    cout << b1;
    Bilet b2("Card", new float[3]{ 2.5f, 3.2f, 6.0f }, 3);
    cout << '\n';
    cout << b2;
    Bilet b3 = b2;
    cout << '\n';
    cout << b3;
    Bilet b4;
    b4 = b1;
    cout << '\n';
    cout << b4;
    b2.setMetodaPlata("Cash");
    cout << b2.getMetodaPlata() << '\n';
    cout << "======================================\n";

    cout << "\n====== Test clasa Cinematograf =======\n";
    Cinematograf c1;
    cout << c1;
    Cinematograf c2("Luceafarul", new int[5]{ 100,50,150,200,75 }, 5);
    cout << '\n';
    cout << c2;
    Cinematograf c3 = c2;
    cout << '\n';
    cout << c3;
    Cinematograf c4;
    c4 = c1;
    cout << '\n';
    cout << c4;
    c2.setDenumire("Lumina soarelui");
    cout << c2.getDenumire() << '\n';
    cout << "======================================\n";

    return 0;
}