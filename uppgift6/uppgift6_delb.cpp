#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

#define MAX_PERSONER 10
#define MAX_TRANSAKTIONER 30

class Transaktion 
{
private:
    string datum;
    string typ;
    string namn;
    double beloop;
    int antal_kompisar;
    string *kompisar;
public:
    Transaktion();
    ~Transaktion();
    Transaktion& operator=( const Transaktion& t);
    string hamtaNamn() const;
    double hamtaBelopp() const;
    int hamtaAntalKompisar() const;
    bool finnsKompis(const string &namnet) const;
    bool lasIn(istream &is);
    void skrivUt(ostream &os) const;
    void skrivTitel(ostream &os) const;
};

class Person 
{
private:
    string namn;
    double betalat_andras;
    double skyldig;
public:
    Person();
    Person(const string &namn, double betalat_andras, double skyldig);
    string hamtaNamn();
    double hamtaBetalat();
    double hamtaSkyldig();
    void skrivUt(ostream &os);
};

class PersonLista
{
private:
  int antal_personer;
  Person *personer;
public:
  PersonLista();
  ~PersonLista();
  void laggTill(Person ny_person);
  void skrivUtOchFixa(ostream &os); 
  double summaSkyldig() const;
  double summaBetalat() const;
  bool finnsPerson(const string& namn);
};

class TransaktionsLista
{
private:
  int antal_transaktioner;
  Transaktion *transaktioner;
public:
  TransaktionsLista();
  ~TransaktionsLista();
  void lasIn(istream &is);
  void skrivUt(ostream &os);
  void laggTill(Transaktion &t);
  double totalKostnad();
  double liggerUteMed(const string &namnet);
  double arSkyldig(const string &namnet);
  PersonLista fixaPersoner();
};

int main()
{
  cout << "Startar med att läsa från en fil." << endl;

  TransaktionsLista transaktioner;
  std::ifstream     is("resa2.txt");
  transaktioner.lasIn(is);

  int operation = 1;
  while (operation != 0)
    {
      cout << endl;
      cout << "Välj i menyn nedan:" << endl;
      cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
      cout << "1. Skriv ut information om alla transaktioner." << endl;
      cout << "2. Läs in en transaktion från tangentbordet." << endl;
      cout << "3. Beräkna totala kostnaden." << endl;
      cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
      cout << "5. Hur mycket ligger en viss person ute med?" << endl;
      cout << "6. Lista alla personer mm och FIXA" << endl;

      cin >> operation;
      cout << endl;

      switch (operation)
        {
          case 1:
            {
              transaktioner.skrivUt(cout);
              break;
            }
          case 2:
            {
              Transaktion transaktion;
              cout << "Ange transaktion i följande format" << endl;
              transaktion.skrivTitel(cout);
              transaktion.lasIn(cin);
              transaktioner.laggTill(transaktion);
              break;
            }
          case 3:
            {
              cout << "Den totala kostnanden för resan var "
                   << transaktioner.totalKostnad() << endl;
              break;
            }
          case 4:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ar_skyldig = transaktioner.arSkyldig(namn);
              if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " är skyldig " << ar_skyldig << endl;
              break;
            }
          case 5:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ligger_ute_med = transaktioner.liggerUteMed(namn);
              if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
              break;
            }
          case 6:
            {
              cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
              PersonLista lista = transaktioner.fixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}

//********************************************************************************
// Konstruktorn till Transaktion
// Syfte: Skapar objektet och sätter default-värde till sina variabler. 
//********************************************************************************
Transaktion::Transaktion() 
{
  datum = typ = namn = "";
  beloop = 0;
  antal_kompisar = 0;
  kompisar = nullptr;
}

//********************************************************************************
// Destruktorn till Transaktion
// Syfte: Den frigör minnet från arrayen kompisar.
//********************************************************************************
Transaktion::~Transaktion() 
{
  delete[] kompisar;
}


//********************************************************************************
// Copy assignmnet till Transaktion
// Syfte: Den kopierar den givna objektets variabler till detta objekt.
// Inparametrar: t - ett reference till trasaktionen som kommer att kopieras.
//********************************************************************************
Transaktion& Transaktion::operator=( const Transaktion& t)
{
  if (this != &t)
  {
    delete[] kompisar;
    datum = t.datum;
    typ = t.typ;
    namn = t.namn;
    beloop = t.beloop;
    antal_kompisar = t.antal_kompisar;
    kompisar = new string[antal_kompisar];
    for (int i = 0; i < antal_kompisar; ++i)
      kompisar[i] = t.kompisar[i];
  }
  return *this;
}

//********************************************************************************
// Metoden Transaktion::hamtaNamn
// Syfte:  Getter för att hämta betalarens namn.
//********************************************************************************
string Transaktion::hamtaNamn() const { return namn; }

//********************************************************************************
// Metoden Transaktion::hamtaBelopp
// Syfte:  Getter för att hämta beloppet på transaktionen.
//********************************************************************************
double Transaktion::hamtaBelopp() const { return beloop; }

//********************************************************************************
// Metoden Transaktion::hamtaAntalKompisar
// Syfte:  Getter för att hämta antalet personer i transaktionen.
//********************************************************************************
int Transaktion::hamtaAntalKompisar() const { return antal_kompisar; }

//********************************************************************************
// Metoden Transaktion::finnsKompis
// Syfte: Returnera true om den givna namnet är en av kompisen.
// Inparametrar: namnet - namnet of kompisen.
//********************************************************************************
bool Transaktion::finnsKompis(const string &namnet) const
{
  // Look through the entire array and if the name is found than we return true...
  for (int i = 0; i < antal_kompisar; ++i)
  {
      if (kompisar[i] == namnet) return true;
  }
  //... otherwise false.
  return false;
}

//********************************************************************************
// Metoden Transaktion::lasIn
// Syfte: Läser in en trasaktion från en given istream och returnerar true
// om det lyckades annars false.
// Inparametrar: is - ett istream som funktionen kommer att läsa ifrån.
//********************************************************************************
bool Transaktion::lasIn(istream &is)
{
    //If the datum is still an empty string than we have reached the end of the file
    //Because we did not manage to read anything.
    //Tried using is.eof() but the file has a couple of enter before the real end of the file.
    //which made it not work.
    datum = "";
    is >> datum;
    if (datum == "") return false;

    is >> typ >> namn >> beloop >> antal_kompisar;

    //Deleting the old one in case it exist and creating a new array with the size of antal_kompisar.
    delete[] kompisar;
    kompisar = new string[antal_kompisar];

    //Read in all the friends because we know how many there are.
    for (int i = 0; i < antal_kompisar; ++i) 
    {
        is >> kompisar[i];
    }

    return true;
}

//********************************************************************************
// Metoden Transaktion::skrivUt
// Syfte: Skriver information till ett given ostream os.
// Inparametrar: os - ett ostream som funktionen kommer att skriva till.
//********************************************************************************
void Transaktion::skrivUt(ostream &os) const
{
    os << datum << '\t' << typ << '\t' << namn << '\t';
    os << beloop << '\t' << antal_kompisar << '\t';

    for (int i = 0; i < antal_kompisar; ++i) 
    {
        os << kompisar[i] << '\t';
    }
    //flushing the buffer.
    os << endl;
}

//********************************************************************************
// Metoden Transaktion::skrivTitel
// Syfte: Skriver ett titel för informationen till den givna ostream.
// Inparametrar: os - ett ostream som funktionen kommer att skriva till.
//********************************************************************************
void Transaktion::skrivTitel(ostream &os) const
{
    os << "Datum\tTyp\tNamn\tBeloop\tAntal\toch lista av kompisar" << endl;
}

//********************************************************************************
// Konstruktorn till Person
// Syfte: Skapar objektet och sätter default-värde till sina variabler. 
//********************************************************************************
Person::Person()
{
  namn = "";
  betalat_andras = 0; 
  skyldig = 0;
}

//********************************************************************************
// Konstruktorn till Person
// Syfte: Skapar objektet och sätter den variablarna till de givna värdena
//********************************************************************************
Person::Person(const string &namn, double betalat_andras, double skyldig)
{
    this->namn = namn;
    this->betalat_andras = betalat_andras;
    this->skyldig = skyldig;
}

//********************************************************************************
// Metoden Person::hamtaNamn
// Syfte:  Getter för att hämta personens namn.
//********************************************************************************
string Person::hamtaNamn() { return namn; }

//********************************************************************************
// Metoden Person::hamtaBetalat
// Syfte:  Getter för att hämta mängden person har betalat för andras.
//********************************************************************************
double Person::hamtaBetalat() { return betalat_andras; }

//********************************************************************************
// Metoden Person::hamtaSkyldig
// Syfte:  Getter för att hämta mängden person är skyldig andra.
//********************************************************************************
double Person::hamtaSkyldig() { return skyldig; }

//********************************************************************************
// Metoden Person::skrivUt
// Syfte: Skriver information till ett given ostream os.
// Inparametrar: os - ett ostream som funktionen kommer att skriva till.
//********************************************************************************
void Person::skrivUt(ostream &os)
{
    os << hamtaNamn() << " ligger ute med " << hamtaBetalat();
    os << " och är skyldig " << hamtaSkyldig() << ". ";

    // different text when they need to pay, they need to take or they do not did
    // to do anything.
    if (hamtaBetalat() > hamtaSkyldig())
    {
        os << "Skall ha " << hamtaBetalat() - hamtaSkyldig();
    }
    else if (hamtaBetalat() < hamtaSkyldig())
    {
        os << "Skall betala " << hamtaSkyldig() - hamtaBetalat();
    }
    else
    {
        os << "Skall inte ha något";
    }

    // flushing the buffer.
    os << " från potten" << endl;
}


//********************************************************************************
// Konstruktorn till PersonLista
// Syfte: Skapar objektet och sätter default-värde till sina variabler. 
//********************************************************************************
PersonLista::PersonLista() 
{
  antal_personer = 0;
  personer = nullptr;
}

//********************************************************************************
// Destruktorn till PersonLista
// Syfte: Det gör ingenting just nu men tror att det ska användas för del b.
//********************************************************************************
PersonLista::~PersonLista()
{
  delete[] personer;
}

//********************************************************************************
// Metoden PersonLista::laggTill
// Syfte:  lägger in den ny personen back i listan.
// Inparametrar: ny_person - den nya personen.
//********************************************************************************
void PersonLista::laggTill(Person ny_person)
{
  Person *ny_arr = new Person[++antal_personer];
  for (int i = 0; i < antal_personer - 1; ++i)
  {
    ny_arr[i] = personer[i];
  }
  delete[] personer;
  ny_arr[antal_personer - 1]  = ny_person;
  personer = ny_arr;
}

//********************************************************************************
// Metoden PersonLista::skrivUtOchFixa
// Syfte:  skriver ut information of varje person.
// Inparametrar: os - ostream som funktionen ska skriva till. 
//********************************************************************************
void PersonLista::skrivUtOchFixa(ostream &os)
{
  for (int i = 0; i < antal_personer; ++i) personer[i].skrivUt(os);
}

//********************************************************************************
// Metoden PersonLista::summaSkyldig
// Syfte:  returnerar summan hur mycket alla är skyldig.
//********************************************************************************
double PersonLista::summaSkyldig() const
{
  double skyldig = 0;
  for (int i = 0; i < antal_personer; ++i) skyldig += personer[i].hamtaSkyldig();
  return skyldig;
}

//********************************************************************************
// Metoden PersonLista::summaBetalat
// Syfte:  returnerar summan hur mycket alla har betalat.
//********************************************************************************
double PersonLista::summaBetalat() const
{
  double betalat = 0;
  for (int i = 0; i < antal_personer; ++i) betalat += personer[i].hamtaBetalat();
  return betalat;
}

//********************************************************************************
// Metoden PersonLista::finnsPerson
// Syfte:  returnerar true om personen finns in listan.
// Inparametrar: namn - namnet of personen.
//********************************************************************************
bool PersonLista::finnsPerson(const string& namn)
{
  // Just doing a simple linear search.
  for (int i = 0; i < antal_personer; ++i)
  {
    if (personer[i].hamtaNamn() == namn) return true;
  }
  return false;
}

//********************************************************************************
// Konstruktorn till TransaktionLista
// Syfte: Skapar objektet och sätter default-värde till sina variabler. 
//********************************************************************************
TransaktionsLista::TransaktionsLista()
{
  antal_transaktioner = 0;
  transaktioner = nullptr;
}

//********************************************************************************
// Destruktorn till PersonLista
// Syfte: Det gör ingenting just nu men tror att det ska användas för del b.
//********************************************************************************
TransaktionsLista::~TransaktionsLista()
{
  delete[] transaktioner;
}

//********************************************************************************
// Metoden TransaktionsLista::lasIn
// Syfte: Läser in en trasaktion från en given istream och lägger transaktion till
// listan.
// Inparametrar: is - ett istream som funktionen kommer att läsa ifrån.
//********************************************************************************
void TransaktionsLista::lasIn(istream &is)
{
  Transaktion t;
  //While it is not at the end of the file keep reading from the file.
  while (t.lasIn(is)) laggTill(t);
}

//********************************************************************************
// Metoden TransaktionsLista::skrivUt
// Syfte: Läser in en trasaktion från en given istream och lägger transaktion till
// listan.
// Inparametrar: os - ett ostream där funktione kommer att skriva till. 
//********************************************************************************
void TransaktionsLista::skrivUt(ostream &os)
{
  os << "Antal trans = " << antal_transaktioner << endl;
  transaktioner[0].skrivTitel(os);
  for (int i = 0; i < antal_transaktioner; ++i) transaktioner[i].skrivUt(os);
}

//********************************************************************************
// Metoden TransaktionsLista::laggTill
// Syfte: Läger in den givna transaktion i listan.
// Inparametrar: t - transaktionen som ska läggas in. 
//********************************************************************************
void TransaktionsLista::laggTill(Transaktion &t)
{
  // Skapar ett array som är +1 storlek för att göra plats för en extra transaktion.
  Transaktion *ny_arr = new Transaktion[++antal_transaktioner];
  // Kopierar de gamla transaktionerna till den nya lista.
  for (int i = 0; i < antal_transaktioner - 1; ++i)
  {
    ny_arr[i] = transaktioner[i];
  }
  ny_arr[antal_transaktioner - 1] = t;
  delete[] transaktioner;
  transaktioner = ny_arr;
}

//********************************************************************************
// Metoden TransaktionsLista::totalKostnad
// Syfte: Räknar ut den totala kostnad av alla transaktioner.
//********************************************************************************
double TransaktionsLista::totalKostnad()
{
  double total = 0;
  for (int i = 0; i < antal_transaktioner; ++i) total += transaktioner[i].hamtaBelopp();
  return total;
}

//********************************************************************************
// Metoden TransaktionsLista::liggerUteMed
// Syfte: Räknar ut hur mycket en given person namn har lagt ute med. 
// Inparametrar: namnet - namnet på personen. 
//********************************************************************************
double TransaktionsLista::liggerUteMed(const string &namnet)
{
  double belopp;
  double total = 0; 
  for (int i = 0; i < antal_transaktioner; ++i)
  {
    if (transaktioner[i].hamtaNamn() == namnet) {
      belopp = transaktioner[i].hamtaBelopp();
      // +1 because the payer is also in the transaktion.
      total += belopp - belopp/(transaktioner[i].hamtaAntalKompisar() + 1);
    }
  }
  return total;
}

//********************************************************************************
// Metoden TransaktionsLista::arSkyldig
// Syfte: Räknar ut hur mycket en given person är skyldig. 
// Inparametrar: namnet - namnet på personen. 
//********************************************************************************
double TransaktionsLista::arSkyldig(const string &namnet)
{
  double total = 0; 
  for (int i = 0; i < antal_transaktioner; ++i)
  {
    if (transaktioner[i].finnsKompis(namnet))
    {
      // +1 för att räkna in den som betalar.
      total += transaktioner[i].hamtaBelopp()/(transaktioner[i].hamtaAntalKompisar() + 1);
    }
  }
  return total;
}

//********************************************************************************
// Metoden TransaktionsLista::fixaPersoner
// Syfte: Räknar ut hur mycket alla personer ligger ute med och skyldig och därefter
// lägger de i en lista och returnerar listan.
//********************************************************************************
PersonLista TransaktionsLista::fixaPersoner()
{
  PersonLista personer;
  //Go through all the transaction...
  for (int i = 0; i < antal_transaktioner; ++i)
  {
    // Check if the person is paying for the transaction is a new person.
    // Note: Everyone has atleast payed once. this why this works otherwise
    // we will need to look through everyone in the transaction too.
    if (!personer.finnsPerson(transaktioner[i].hamtaNamn()))
    {
      // If it is a new person than we need to find out how much he payed and how much he owed
      // and add it to the list.
      string namn = transaktioner[i].hamtaNamn();
      personer.laggTill(Person(namn, liggerUteMed(namn), arSkyldig(namn)));
    }
  }
  return personer;
}


