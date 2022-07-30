//
// Programskal till inl�mningsuppgift 4 - deluppgift B
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits.h>
#include <float.h>
using namespace std;

// Globala konstanter:

// Tips: Anv�nd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// ist�llet f�r v�rdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;
const int A_ASCII_NUMBER = 65;
const float PLOT_THRESHOLD = 0.5;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska. TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas
// som parameter till den funktion som beh�ver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

const string LANGUAGES[ANTAL_SPRAK] = {"engelska", "franska", "svenska", "tyska"};

// Globala variabler �r ej till�tna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Anv�nd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
void berakna_histogram_abs(const string text, int &number_of_characters, int freqCounter[ANTAL_BOKSTAVER]);

// Funktionen abs_till_rel
void abs_till_rel(float relFreqCounter[ANTAL_BOKSTAVER], const float number_of_characters, const int freqCounter[ANTAL_BOKSTAVER]);

// Funktionen plotta_histogram_rel
void plotta_histogram_rel(const float relFreqCounter[ANTAL_BOKSTAVER]);

// Funktionen tolkning
void tolkning(const int number_of_characters, const float freqCounter[ANTAL_BOKSTAVER]);

// Funktionen namn_pa_fil
void namn_pa_fil(string &file_name);

// Funktionen inlasning
bool inlasning(string &file_name, string &text);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
  int freqCounter[ANTAL_BOKSTAVER] = {0};
  float relFreqCounter[ANTAL_BOKSTAVER]; 
  int number_of_characters;
  string file_name, text;

  // Inläsning
  namn_pa_fil(file_name);

  // A guard clause in case the text is empty.
  if (!inlasning(file_name, text)) {
    return -1;
  }
  // Anropa funktionen berakna_histogram_abs som ber�knar histogrammet
  // och antalet bokst�ver.  
  berakna_histogram_abs(text, number_of_characters, freqCounter);

  //Konvertera ifrån absolut till relativ karaktärförekomst i filen.
  abs_till_rel(relFreqCounter, (float)number_of_characters, freqCounter);

  //Tolka vilket språk filen kan vara med hjälp av den relativa karaktärförekomsten.
  tolkning(number_of_characters, relFreqCounter);

  plotta_histogram_rel(relFreqCounter);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

//***********************************************************************************************************************************
// Funktion berakna_histogram_abs
// Syfte: Funktionen beräknar antalet karaktärer som förekommmer i den givna strängen och mängden av giltiga karaktärer. 
//        Resultatet sparas i ett given array of storleken ANTAL_BOKSTAVER där index 0 representerar A och index 1 respresenterar B.
//        Mängden av giltiga karaktärer kommer att sparas i number_of_characters
// Inparametrar: text - strängen som karaktärmängden kommer att beräknas.
//               number_of_characters - är mängden av giltiga karaktärer (I denna version är det bara a-z och deras versaller).
//               freqCounter - är arrayen där resultatet kommer att sparas.
//
//***********************************************************************************************************************************
void berakna_histogram_abs(const string text, int &number_of_characters, int freqCounter[ANTAL_BOKSTAVER]) {
  // The index for the array.
  int i;
  number_of_characters = 0;
  for (char c : text) {
    //Turn everything to capitalize letter and take minus capital A ascii number so the letter A would be at index 0,
    //While capital B would be at index 1.
    i = toupper(c) - A_ASCII_NUMBER;
    //Check if it was a character from A - Z otherwise skip it.
    //The index must be between 0 and 25 if it was a valid character.
    if (0 <= i && i < ANTAL_BOKSTAVER) {
      ++number_of_characters;
      ++freqCounter[i];
    }
  }
}

//***********************************************************************************************************************************
// Funktion abs_till_rel
// Syfte: Funktionen konverterar den absoluta resultatet från berakna_histogram_abs till ett relativ version av det istället. 
//        Relativ betyder att vi tar förekomsten av det karaktären i filen delat på mängden av giltiga karaktärer i filen.
// Inparametrar: relFreqCounter - Arrayen där de relativa värdena kommer att placeras.
//               number_of_characters - är mängden av giltiga karaktärer (I denna version är det bara a-z och deras versaller).
//               freqCounter - är arrayen med de absoluta värdena.
//
//***********************************************************************************************************************************
void abs_till_rel(float relFreqCounter[ANTAL_BOKSTAVER], const float number_of_characters, const int freqCounter[ANTAL_BOKSTAVER]) {
  for (int i = 0; i < ANTAL_BOKSTAVER; ++i) {
    //Take it times hundred so it is saved in percent.
    relFreqCounter[i] = 100 * (float)freqCounter[i]/number_of_characters;
  }
}

//***********************************************************************************************************************************
// Funktion plotta_histogram_rel
// Syfte: Funktionen ska rita ett bokstavhistogram genom att använda karaktären '*' som betyder 0.5 procent. Det kommer att avrundas
// neråt. Dvs om karaktären A har 1.5 % kommer A att representeras med '***'. Om karaktären B har 0.4 % kommer den att repserenteras med
// '' då den avrundas neråt.
// Inparametrar: relFreqCounter - Arrayen där de relativa värdena kommer att placeras.
//
//***********************************************************************************************************************************
void plotta_histogram_rel(const float relFreqCounter[ANTAL_BOKSTAVER]) {
  float currentFreq;
  
  cout << endl << "Bokstavsfördelning:" << endl << endl;

  //Go through all of the characters.
  for (int c = 0; c < ANTAL_BOKSTAVER; ++c) {
    cout << (char) (c + A_ASCII_NUMBER) << " ";

    currentFreq = relFreqCounter[c];
    //While currentFreq is still larger than PLOT_THRESHOLD (O.5 %) then continue printing out *.
    //This loop will terminate because we are subtracting 0.5 from currentFreq every loop.
    while (currentFreq >= PLOT_THRESHOLD) {
      cout << "*";
      currentFreq -= PLOT_THRESHOLD;
    }
    //After we are done att and endline so we can start doing this for the next character. 
    cout << endl;
  }
}

//***********************************************************************************************************************************
// Funktion tolkning
// Syfte: Funktionen kommer att jämföra ett relativhistogram med fyra fördefinerade språkshistogram. Den kommer att skriva ut resultatet
//        för alla språk och skriva ut vilket språk det troligtviss är.
// Inparametrar: relFreqCounter - Arrayen för den relativevärdena.
//
//***********************************************************************************************************************************
void tolkning(const int number_of_characters, const float freqCounter[ANTAL_BOKSTAVER]) {
  double current_quadsum;

  cout << endl << "Resultatet för bokstäverna A-Z" << endl;
  cout << "Totala antalet bokstäver: " << number_of_characters << endl;

  double best_quadsum = DBL_MAX;
  int best_language = 0;
  //Go though all the languages.
  for (int lan = 0; lan < ANTAL_SPRAK; ++lan) {
    current_quadsum = 0;
    //Go though all the characters and calculate the quadsum.
    for (int c = 0; c < ANTAL_BOKSTAVER; ++c) {
      current_quadsum += pow(TOLK_HJALP[lan][c] - freqCounter[c], 2);
    }
    cout << LANGUAGES[lan] << " har kvadratsumma = " << current_quadsum << endl;
    //If the current_quadsum is smaller than we change that to the new best fit language.

    if (current_quadsum < best_quadsum) {
      best_language = lan;
      best_quadsum = current_quadsum;
    }
  }
  cout << "Det är mest troligt att språket är " << LANGUAGES[best_language] << endl;
}

//***********************************************************************************************************************************
// Funktion namn_pa_fil
// Syfte: Funktionen kommer att be användaren att skriva in ett filnamn. Om användaren inte skrev .txt så kommer den att lägga
//        till det på slutet. 
// Inparametrar: file_name - Strängen där filnamnet kommer att sparas.
//
//***********************************************************************************************************************************
void namn_pa_fil(string &file_name) {
  bool file_exist = false;
  //Ask the user for the file.
  cout << "Ange filnamn?" << endl;
  getline(cin, file_name);

  //Add a '.txt' substring to the end of the string if the user has not added the .txt.
  if (file_name.rfind(".txt") == std::string::npos) {
    file_name.append(".txt");
  }

}

//***********************************************************************************************************************************
// Funktion inlasning
// Syfte: Funktionen läser in filen som har addressen file_name till strängen text och kollar ifall filen existerar.
// Inparametrar: file_name - ett giltig filnamn
//               text - strängen där filen kommer att vara sparad.
// Utparametrar: false om filen inte existerar annars true.
//
//***********************************************************************************************************************************
bool inlasning(string &file_name, string &text) {
  text = "";

  //Open and check if the file exist.
  ifstream file(file_name);
  if (!file.good()) {
    cout << "Det finns inget fil med namnet " << file_name << endl;
    return false;
  }

  // Countinue looping through until we have hit the End Of File character.
  while (file.peek() != EOF) {
    text.push_back(file.get()); 
  }
  return true;
}
// -------------------------------------------------------
// Rapport om uppgiften
// -------------------------------------------------------

// Programmet kommer först att be användaren om ett filnamn där användaren får välja att skriva in .txt eller inte. Därefter kommer programmet att kalla funktionen för att
// läsa in texten. I inläsning funktionen kommer ett kontroll inträffa där den kollar ifall att filen existerar, om den inte existerar kommer funktionen att returnera false
// men om den existerar returnerar funktionen true och läser in texten i filen. Main funktionen kommer sluta programkörningen om inläsning funktionen returnerar ett false
// värde då filen existerar inte.

// Efter inläsning delen av programmet är klar kommer vi ha texten sparad i en sträng och med strängen så räknar vi förekomsten av de olika karaktärerna med samma funktion
// som vi använde i del A av denna uppgift. Efter att vi räknat ut den absoluta histogramet konverterar vi den till ett relativ histogram genom att gå igenom alla giltiga
// karaktärer och sparar resultet när man tar deras förekomst i texten delat på antalet giltiga karaktärer i texten.

// Därefter så tolkar vi resultatet genom att räkna ut kvadratsumman mellan den relativa historgram och fyra fördefinerade språk histogram. Den kommer att skriva ut
// resultatet i terminalen för alla fyra språk och skriva ut vilket språk som är texten är mest troligt.

// På slutet så plottar vi den relative histogrammet med hjälp av tecknet * som representerar 0.5 %. Den gör detta bara genom att gå igenom alla karaktärer och sparar deras
// värde i ett variabel. Med detta variabel så har vi ett while loop som kommer vara sant om värdet är större eller lika med 0.5. Och varje loop så skriver vi ut ett * och
// subtrahera 0.5 på variabeln.
