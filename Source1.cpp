#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
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
    Actor() :id(++contor) 
    {
        this->nume = new char[1];
        strcpy(this->nume, "");
        this->prenume = new char[1];
        strcpy(this->prenume, "");
        this->noteCasting = new int[1];
        this->nrNote = 0;
    }
    Actor(const char* nume, const char* prenume, const int* noteCasting, int nrNote) :id(++contor)
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

    Actor(const Actor& a) :id(++contor)
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

    void scrieInFisier(const char* fileName) {
        ofstream g(fileName, ios::app | ios::out | ios::binary);

        if (!g.is_open()) {
            cout << "Cannot open " << fileName << " file!" << endl;
        }

        int dim;

        dim = strlen(this->nume) + 1;
        g.write((char*)&dim, sizeof(int));
        g.write(this->nume, dim * sizeof(char));

        dim = strlen(this->prenume) + 1;
        g.write((char*)&dim, sizeof(int));
        g.write(this->prenume, dim * sizeof(char));

        g.write((char*)&this->nrNote, sizeof(int));
        g.write((char*)this->noteCasting, this->nrNote * sizeof(int));

        g.close();
    }

    bool citesteDinFisier(ifstream& f) {
        int dim;
        f.read((char*)&dim, sizeof(int));

        if (dim < -1 * pow(2, 15) || dim > pow(2, 15))
            return false;

        this->nume = new char[dim];
        f.read(this->nume, dim * sizeof(char));

        f.read((char*)&dim, sizeof(int));
        this->prenume = new char[dim];
        f.read(this->prenume, dim * sizeof(char));

        f.read((char*)&this->nrNote, sizeof(int));
        this->noteCasting = new int[this->nrNote];
        f.read((char*)this->noteCasting, this->nrNote * sizeof(int));

        return true;
    }
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
    Recenzie() :id(++contor)
    {
        this->text = new char[1];
        strcpy(this->text, "");
        this->aprecieriRaspunsuri = new int[1];
        this->nrRaspunsuri = 0;
    }
    Recenzie(const char* text, const int* aprecieriRaspunsuri, int nrRaspunsuri) :id(++contor)
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

    Recenzie(const Recenzie& r) :id(++contor)
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

    void scrieInFisier(const char* fileName) {
        ofstream g(fileName, ios::app | ios::out | ios::binary);

        if (!g.is_open()) {
            cout << "Cannot open " << fileName << " file!" << endl;
        }

        int dim;

        dim = strlen(this->text) + 1;
        g.write((char*)&dim, sizeof(int));
        g.write(this->text, dim * sizeof(char));

        g.write((char*)&this->nrRaspunsuri, sizeof(int));
        g.write((char*)this->aprecieriRaspunsuri, this->nrRaspunsuri * sizeof(int));

        g.close();
    }

    bool citesteDinFisier(ifstream& f) {
        int dim;
        f.read((char*)&dim, sizeof(int));

        if (dim < -1 * pow(2, 15) || dim > pow(2, 15))
            return false;

        this->text = new char[dim];
        f.read(this->text, dim * sizeof(char));

        f.read((char*)&this->nrRaspunsuri, sizeof(int));
        this->aprecieriRaspunsuri = new int[this->nrRaspunsuri];
        f.read((char*)this->aprecieriRaspunsuri, this->nrRaspunsuri * sizeof(int));

        return true;
    }
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
    Film() :id(++contor)
    {
        this->denumire = new char[1];
        strcpy(this->denumire, "");
        this->ratingEpisoade = new int[1];
        this->nrEpisoade = 0;
    }

    /* Constructor cu parametrii */
    Film(const char* denumire, int* ratingEpisoade, int nrEpisoade) :id(++contor)
    {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
        this->nrEpisoade = nrEpisoade;
        this->ratingEpisoade = new int[this->nrEpisoade];
        for (int i = 0; i < this->nrEpisoade; i++)
            this->ratingEpisoade[i] = ratingEpisoade[i];
    }
    /* contructor de copiere */
    Film(const Film& f) :id(++contor)
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
        
    void scrieInFisier(const char* fileName) {
        ofstream g(fileName, ios::app | ios::out | ios::binary);

        if (!g.is_open()) {
            cout << "Cannot open " << fileName << " file!" << endl;
        }

        int dim;

        dim = strlen(this->denumire) + 1;
        g.write((char*)&dim, sizeof(int));
        g.write(this->denumire, dim * sizeof(char));

        g.write((char*)&this->nrEpisoade, sizeof(int));
        g.write((char*)this->ratingEpisoade, this->nrEpisoade * sizeof(int));

        g.close();
    }

    bool citesteDinFisier(ifstream& f) {
        int dim;
        f.read((char*)&dim, sizeof(int));

        if (dim < -1 * pow(2, 15) || dim > pow(2, 15))
            return false;

        this->denumire = new char[dim];
        f.read(this->denumire, dim * sizeof(char));

        f.read((char*)&this->nrEpisoade, sizeof(int));
        this->ratingEpisoade = new int[this->nrEpisoade];
        f.read((char*)this->ratingEpisoade, this->nrEpisoade * sizeof(int));

        return true;
    }
};
/* initializare camp static contor = 0 */
int Film::contor = 0;

/* implementare operator << */
void operator <<(ostream& out, Film f)
{
    out << "Denumire: " <<  f.denumire << '\n';
    out << "Ratinguri episoade: ";
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
    virtual void afiseaza_metodaPlata()//functie virtuala
    {
        cout << "Metoda de plata este:" << metodaPlata << endl;
    }


public:
    /* constructor fara parametru */
    Bilet():id(++contor)
    {
        this->metodaPlata = new char[1];
        strcpy(this->metodaPlata, "");
        this->preturiCategorii = new float[1];
        this->nrCategorii = 0;
    }

    /* constructor fara parametru */
    Bilet(const char* metodaPlata, float* preturiCategorii, int nrCategorii):id(++contor)
    {
        this->metodaPlata = new char[strlen(metodaPlata) + 1];
        strcpy_s(this->metodaPlata, strlen(metodaPlata) + 1, metodaPlata);
        this->nrCategorii = nrCategorii;
        this->preturiCategorii = new float[this->nrCategorii];
        for (int i = 0; i < this->nrCategorii; i++)
            this->preturiCategorii[i] = preturiCategorii[i];
    }

    /* constructor de copiere */
    Bilet(const Bilet& b) :id(++contor)
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

    void scrieInFisier(const char* fileName) {
        ofstream g(fileName, ios::app | ios::out | ios::binary);

        if (!g.is_open()) {
            cout << "Cannot open " << fileName << " file!" << endl;
        }

        int dim;

        dim = strlen(this->metodaPlata) + 1;
        g.write((char*)&dim, sizeof(int));
        g.write(this->metodaPlata, dim * sizeof(char));

        g.write((char*)&this->nrCategorii, sizeof(int));
        g.write((char*)this->preturiCategorii, this->nrCategorii * sizeof(float));

        g.close();
    }

    bool citesteDinFisier(ifstream& f) {
        int dim;
        f.read((char*)&dim, sizeof(int));

        if (dim < -1 * pow(2, 15) || dim > pow(2, 15))
            return false;

        this->metodaPlata = new char[dim];
        f.read(this->metodaPlata, dim * sizeof(char));

        f.read((char*)&this->nrCategorii, sizeof(int));
        this->preturiCategorii = new float[this->nrCategorii];
        f.read((char*)this->preturiCategorii, this->nrCategorii * sizeof(float));

        return true;
    }

};
/* initializarea campului static TVA cu 0 */
int Bilet::contor = 0;

/* implementare suprascriere operator << */
void operator <<(ostream& out, Bilet b)
{
    out << "Metoda plata: " << b.metodaPlata << '\n';
    out << "Preturi categorii: ";
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
    Cinematograf() :id(++contor)
    {
        this->denumire = new char[1];
        strcpy(this->denumire, "");
        this->nrLocuriSali = new int[1];
        this->nrSali = 0;
    }

    /* constructor fara parametru */
    Cinematograf(const char* denumire, int* nrLocuriSali, int nrSali) :id(++contor)
    {
        this->denumire = new char[strlen(denumire) + 1];
        strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
        this->nrSali = nrSali;
        this->nrLocuriSali = new int[this->nrSali];
        for (int i = 0; i < this->nrSali; i++)
            this->nrLocuriSali[i] = nrLocuriSali[i];
    }

    /* constructor de copiere */
    Cinematograf(const Cinematograf& c) :id(++contor)
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
    void setLocuriSali(int nrSali, int* nrLocuriSali) {
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

    void scrieInFisier(const char* fileName) {
        ofstream g(fileName, ios::app | ios::out | ios::binary);

        if (!g.is_open()) {
            cout << "Cannot open " << fileName << " file!" << endl;
        }

        int dim;

        dim = strlen(this->denumire) + 1;
        g.write((char*)&dim, sizeof(int));
        g.write(this->denumire, dim * sizeof(char));

        g.write((char*)&this->nrSali, sizeof(int));
        g.write((char*)this->nrLocuriSali, this->nrSali * sizeof(int));

        g.close();
    }

    bool citesteDinFisier(ifstream& f) {
        int dim;
        f.read((char*)&dim, sizeof(int));

        if (dim < -1 * pow(2, 15) || dim > pow(2, 15))
            return false;

        this->denumire = new char[dim];
        f.read(this->denumire, dim * sizeof(char));

        f.read((char*)&this->nrSali, sizeof(int));
        this->nrLocuriSali = new int[this->nrSali];
        f.read((char*)this->nrLocuriSali, this->nrSali * sizeof(int));

        return true;
    }
};
/* initializarea campului static TVA cu 0 */
int Cinematograf::contor = 0;

/* implementare suprascriere operator << */
void operator <<(ostream& out, Cinematograf c)
{
    out << "Denumire: " << c.denumire << '\n';
    out << "Numar locuri per sala: ";
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

class Actori {
private:
    char* fileName;
public:
    Actori(const char* fileName) {
        this->fileName = new char[strlen(fileName) + 1];
        strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
    }
    void adaugaActor() {
        int nrNote, noteCasting[10];
        char nume[30], prenume[30];

        cout << "Introdu nume actor: ";
        cin.ignore();
        cin.getline(nume, 30);

        cout << "Introdu prenume actor: ";
        cin.getline(prenume, 30);

        cout << "Introdu nr. note castinguri: ";
        cin >> nrNote;

        cout << "Introdu note casting: ";
        for (int i = 0; i < nrNote; i++)
            cin >> noteCasting[i];

        Actor actor(nume, prenume, noteCasting, nrNote);
        actor.scrieInFisier(this->fileName);
    }
    void modificaActor() {
    }
    void stergeActor() {
        vector<Actor> actori = this->citesteActori();

        char nume[30], prenume[30];

        cout << "Introdu nume actor: ";
        cin.ignore();
        cin.getline(nume, 30);

        cout << "Introdu prenume actor: ";
        cin.getline(prenume, 30);

        int idxToDelete = -1;
        for (int i = 0; i < actori.size(); i++) {
            if (strcmp(actori[i].getNume(), nume) == 0 &&
                strcmp(actori[i].getPrenume(), prenume) == 0)
            {
                idxToDelete = i;
                break;
            }
        }

        if(idxToDelete != -1)
            actori.erase(actori.begin() + idxToDelete);

        this->scrieInFisier(actori);
    }

    void scrieInFisier(vector<Actor> actori) {
        ofstream g(this->fileName, ios::out | ios::binary);

        for (Actor actor : actori) {
            actor.scrieInFisier(this->fileName);
        }
    }

    vector<Actor> citesteActori() {
        ifstream f(this->fileName, ios::in | ios::binary);
        vector<Actor> actori;
        Actor actor;
        int idx = 1;
        while (true) {
            if (!actor.citesteDinFisier(f))
                break;
            actori.push_back(actor);
            idx++;
        }

        f.close();

        return actori;
    }

    void afisareActori() {
        vector<Actor> actori = this->citesteActori();

        cout << "Afisare actori:\n";
        for (int i = 0; i < actori.size(); i++) {
            cout << "Afisare detalii actor nr. " << i + 1 << '\n';
            cout << actori[i];
        }
    }
};

class Recenzii {
private:
    char* fileName;
public:
    Recenzii(const char* fileName) {
        this->fileName = new char[strlen(fileName) + 1];
        strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
    }
    void adaugaRecenzie() {
        int nrRaspunsuri, aprecieriRaspunsuri[10];
        char text[30];

        cin.ignore();

        cout << "Introdu text recenzie: ";
        cin.getline(text, 30);

        cout << "Introdu nr. raspunsuri: ";
        cin >> nrRaspunsuri;

        cout << "Introdu aprecieri raspunsuri: ";
        for (int i = 0; i < nrRaspunsuri; i++)
            cin >> aprecieriRaspunsuri[i];

        Recenzie recenzie(text, aprecieriRaspunsuri, nrRaspunsuri);
        recenzie.scrieInFisier(this->fileName);
    }
    void modificaRecenzie() {
    }
    void stergeRecenzie() {
    }
    void afisareRecenzii() {
        ifstream f(this->fileName, ios::in | ios::binary);
        Recenzie recenzie;
        int idx = 1;
        while (true) {
            if (!recenzie.citesteDinFisier(f))
                break;
            cout << "Afisare detalii recenzie nr. " << idx << '\n';
            cout << recenzie;
            idx++;
        }
        f.close();
    }
};

class Bilete {
private:
    char* fileName;
public:
    Bilete(const char* fileName) {
        this->fileName = new char[strlen(fileName) + 1];
        strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
    }
    void adaugaBilet() {
        int nrCategorii;
        float preturiCategorii[10];
        char metodaPlata[30];

        cin.ignore();

        cout << "Introdu metoda plata: ";
        cin.getline(metodaPlata, 30);

        cout << "Introdu nr. categorii: ";
        cin >> nrCategorii;

        cout << "Introdu preturi categorii: ";
        for (int i = 0; i < nrCategorii; i++)
            cin >> preturiCategorii[i];

        Bilet bilet(metodaPlata, preturiCategorii, nrCategorii);
        bilet.scrieInFisier(this->fileName);
    }
    void modificaBilet() {
    }
    void stergeBilet() {
    }
    void afisareBilete() {
        ifstream f(this->fileName, ios::in | ios::binary);
        Bilet bilet;
        int idx = 1;
        while (true) {
            if (!bilet.citesteDinFisier(f))
                break;
            cout << "Afisare detalii bilet nr. " << idx << '\n';
            cout << bilet;
            idx++;
        }
        f.close();
    }
};

class Filme {
private:
    char* fileName;
public:
    Filme(const char* fileName) {
        this->fileName = new char[strlen(fileName) + 1];
        strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
    }
    void adaugaFilm() {
        int nrEpisoade, ratingEpisoade[10];
        char denumire[30];

        cin.ignore();

        cout << "Introdu denumire: ";
        cin.getline(denumire, 30);

        cout << "Introdu nr. episoade: ";
        cin >> nrEpisoade;

        cout << "Introdu rating episoade: ";
        for (int i = 0; i < nrEpisoade; i++)
            cin >> ratingEpisoade[i];

        Film film(denumire, ratingEpisoade, nrEpisoade);
        film.scrieInFisier(this->fileName);
    }
    void modificaFilm() {
    }
    void stergeFilm() {
    }
    void afisareFilme() {
        ifstream f(this->fileName, ios::in | ios::binary);
        Film film;
        int idx = 1;
        while (true) {
            if (!film.citesteDinFisier(f))
                break;
            cout << "Afisare detalii film nr. " << idx << '\n';
            cout << film;
            idx++;
        }
        f.close();
    }
};

class Cinematografe {
private:
    char* fileName;
public:
    Cinematografe(const char* fileName) {
        this->fileName = new char[strlen(fileName) + 1];
        strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
    }
    void adaugaCinematograf() {
        int nrSali, nrLocuriSala[10];
        char denumire[30];

        cin.ignore();

        cout << "Introdu denumire: ";
        cin.getline(denumire, 30);

        cout << "Introdu nr. sali: ";
        cin >> nrSali;

        cout << "Introdu locuri per sali: ";
        for (int i = 0; i < nrSali; i++)
            cin >> nrLocuriSala[i];

        Cinematograf cinematograf(denumire, nrLocuriSala, nrSali);
        cinematograf.scrieInFisier(this->fileName);
    }
    void modificaCinematograf() {
    }
    void stergeCinematograf() {
    }
    void afisareCinematografe() {
        ifstream f(this->fileName, ios::in | ios::binary);
        Cinematograf cinematograf;
        int idx = 1;
        while (true) {
            if (!cinematograf.citesteDinFisier(f))
                break;
            cout << "Afisare detalii cinematograf nr. " << idx << '\n';
            cout << cinematograf;
            idx++;
        }
        f.close();
    }
};

class UserInterface {
public:
    int citesteOptiune(int min, int max) {
        int optiune;
        cout << "Introdu optiune: ";
        cin >> optiune;

        if (optiune < min || optiune > max)
        {
            cout << "Optiune eronata!\n";
            return -1;
        }
        return optiune;
    }

    void meniuActori() {
        cout << "***** MENIU ACTORI *****\n";
        cout << "1. Adaugare actor\n";
        cout << "2. Actualizare actor\n";
        cout << "3. Stergere actor\n";
        cout << "4. Afisare actori\n";

        int optiune = citesteOptiune(1, 4);

        if (optiune != -1)
        {
            Actori actori("actori.bin");
            switch (optiune)
            {
                case 1:
                    actori.adaugaActor();
                    break;
                case 2:
                    actori.modificaActor();
                    break;
                case 3:
                    actori.stergeActor();
                    break;
                case 4:
                    actori.afisareActori();
                    break;
            }
        }
    }
    void meniuRecenzii() {
        cout << "***** MENIU RECENZII *****\n";
        cout << "1. Adaugare recenzie\n";
        cout << "2. Actualizare recenzie\n";
        cout << "3. Stergere recenzie\n";
        cout << "4. Afisare recenzii\n";

        int optiune = citesteOptiune(1, 4);

        if (optiune != -1)
        {
            Recenzii recenzii("recenzii.bin");
            switch (optiune)
            {
            case 1:
                recenzii.adaugaRecenzie();
                break;
            case 2:
                recenzii.modificaRecenzie();
                break;
            case 3:
                recenzii.stergeRecenzie();
                break;
            case 4:
                recenzii.afisareRecenzii();
                break;
            }
        }
    }
    void meniuBilete() {
        cout << "***** MENIU BILETE *****\n";
        cout << "1. Adaugare bilet\n";
        cout << "2. Actualizare bilet\n";
        cout << "3. Stergere bilet\n";
        cout << "4. Afisare bilete\n";

        int optiune = citesteOptiune(1, 4);

        if (optiune != -1)
        {
            Bilete bilete("bilete.bin");
            switch (optiune)
            {
            case 1:
                bilete.adaugaBilet();
                break;
            case 2:
                bilete.modificaBilet();
                break;
            case 3:
                bilete.stergeBilet();
                break;
            case 4:
                bilete.afisareBilete();
                break;
            }
        }
    }
    void meniuFilme() {
        cout << "***** MENIU FILME *****\n";
        cout << "1. Adaugare film\n";
        cout << "2. Actualizare film\n";
        cout << "3. Stergere film\n";
        cout << "4. Afisare filme\n";

        int optiune = citesteOptiune(1, 4);

        if (optiune != -1)
        {
            Filme filme("filme.bin");
            switch (optiune)
            {
            case 1:
                filme.adaugaFilm();
                break;
            case 2:
                filme.modificaFilm();
                break;
            case 3:
                filme.stergeFilm();
                break;
            case 4:
                filme.afisareFilme();
                break;
            }
        }
    }
    void meniuCinematografe() {
        cout << "***** MENIU CINEMATOGRAFE *****\n";
        cout << "1. Adaugare cinematograf\n";
        cout << "2. Actualizare cinematograf\n";
        cout << "3. Stergere cinematograf\n";
        cout << "4. Afisare cinematografe\n";

        int optiune = citesteOptiune(1, 4);

        if (optiune != -1)
        {
            Cinematografe cinematografe("cinematografe.bin");
            switch (optiune)
            {
            case 1:
                cinematografe.adaugaCinematograf();
                break;
            case 2:
                cinematografe.modificaCinematograf();
                break;
            case 3:
                cinematografe.stergeCinematograf();
                break;
            case 4:
                cinematografe.afisareCinematografe();
                break;
            }
        }
    }
    void meniu() {
        cout << "***** MENIU GENERAL *****\n";
        cout << "1. Meniu actor\n";
        cout << "2. Meniu recenzii\n";
        cout << "3. Meniu bilete\n";
        cout << "4. Meniu filme\n";
        cout << "5. Meniu cinematografe\n";
        cout << "0. Terminare program\n";
    }
    void start() {
        int optiune;
        
        while (true) {
            meniu();

            optiune = citesteOptiune(0, 5);

            if(optiune != -1){
                if (optiune == 0)
                {
                    cout << "Terminare program...\n";
                    break;
                }
                else 
                {
                    switch (optiune)
                    {
                        case 1:
                            meniuActori();
                            break;
                        case 2:
                            meniuRecenzii();
                            break;
                        case 3:
                            meniuBilete();
                            break;
                        case 4:
                            meniuFilme();
                            break;
                        case 5:
                            meniuCinematografe();
                            break;
                    }
                }
            }
        }
    }
};


class Scurtmetraj : public Film //clasa derivate din clasa film 
{
private:
    int nrOre;
public:

    Scurtmetraj() : Film()//contructorul fara paramentrii
    {
        nrOre = 0;
    }

    //constructorul cu parametrii
    Scurtmetraj(const char* denumire, int* ratingEpisoade, int nrEpisoade, int nrOre) : Film(denumire, ratingEpisoade, nrEpisoade)
    {
        this->nrOre = nrOre;
    }

    //getteri setteri
    int getNrOre()

    {
        return nrOre;
    }
    void setNrOre(int valoare)
    {
        if (valoare > 0) {
            nrOre = valoare;
        }
        else throw exception("Valoare incorecta");
    }

    //constructorul de copiere
    Scurtmetraj(const Scurtmetraj& sc) : Film(sc)
    {
        this->nrOre = sc.nrOre;
    }

    //operatorul egal
    Scurtmetraj operator = (const Scurtmetraj sc)
    {
        Film:: operator =(sc);
        this->nrOre = sc.nrOre;
        return *this;
    }

    ~Scurtmetraj()
    {
    }

};
    ostream& operator << (ostream& iesire, Scurtmetraj& sc)
    {
        iesire << (Film)sc;
        iesire << sc.getNrOre() << endl;
        return iesire;

    }


template <class T> //definire clasa template
class adunaBilete
{
public:
    T* numere;
    int cate;
    adunaBilete(int);//constructor cu parametru pentru alocare spatiu
    ~adunaBilete()//destructor
    {
        delete[]numere;
    }
    T& operator[](int i)//operator[] ce returneaza elementele vect
    {
        if (i >= 0 && i < cate)return numere[i];
        else return NULL;
    }
    void afiseaza(); //apel functie de afisare in clasa template
    void adunanumere();//apel functie calcul suma in clasa template
};

template <class T> //constructor cu parametru
adunaBilete<T>::adunaBilete(int n) : cate(n)
{
    numere = new T[n];
    for (int i = 0; i < cate; i++)
    {
        cout << "numarul" << i << " ";
        cin >> numere[i];
        cout << endl;
    }
}
template<class T>// afiseaza elementele vectorului
void adunaBilete<T>::afiseaza()
{
    cout << endl;
    for (int i = 0; i < cate; i++)
    {
        cout << numere[i] << " ";
    }
}
template<class T> //realizeaza o adunare a numerelor
void adunaBilete<T>::adunanumere()
{
    int suma = 0;
    for (int i = 0; i < cate; i++)
        suma = suma + numere[i];
    cout << "suma este:" << suma << endl;
}



int main()
{
    UserInterface ui;
    ui.start();
    /*
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
    */


    /*cout << "\n====== Test clasa Scurtmetraj =======\n";
    Scurtmetraj s1;
    cout << s1;
    Scurtmetraj s2("Captivi in iad", new int[2]{ 9, 7 }, 2, 2);
    cout << '\n';
    cout << s2;
    Scurtmetraj s3 = s2;
    cout << '\n';
    cout << s3;
    Scurtmetraj s4;
    s4 = s1;
    cout << '\n';
    cout << s4;
    s2.setNrOre(1);
    cout << s2.getNrOre() << '\n';
    cout << "======================================\n";*/


    //adunaBilete<int> bi(4);
    //bi.afiseaza();
    //bi.adunanumere();
    //bi.afiseaza();
    //adunaBilete<float> ab(4);
    //ab.afiseaza();
    //ab.adunanumere();
    //ab.afiseaza();
    //adunaBilete <Bilet> ac(1);//apel functie template pentru clasa Bilet
    ////ac.adunanumere();
    ////ac.afiseaza(); // nu merge afisarea elementelor din clasa apelata 


    return 0;
}