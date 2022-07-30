//
// Programskal till inl�mningsuppgift 4 - deluppgift A
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;


// Anv�nd g�rna denna globala konstant i programmet
// i st�llet f�r v�rdet 26
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int A_ASCII_NUMBER = 65;
// Globala variabler �r ej till�tna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Funktionen berakna_histogram_abs
void berakna_histogram_abs(const string text, int &number_of_characters, int freqCounter[ANTAL_BOKSTAVER]);

// Funktionen skriv_histogram_abs
void skriv_histogram_abs(const int &number_of_characters, const int freqCounter[ANTAL_BOKSTAVER]);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
  int freqCounter[ANTAL_BOKSTAVER] = {0};
  int number_of_characters;
  string text;

  // L�s in en rad med text fr�n tangentbordet
  cout << "Ge en rad med text?" << endl;
  getline(cin, text);

  // Anropa funktionen berakna_histogram_abs som ber�knar histogrammet
  // och antalet bokst�ver.  
  berakna_histogram_abs(text, number_of_characters, freqCounter);

  skriv_histogram_abs(number_of_characters, freqCounter); 

  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet

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

//*******************************************************************************************************************************
// Funktion skriv_histogram_abs
// Syfte: Funktionen kommer att visa resultatet av berakna_histogram_abs där den kommer att visa hur många gånger ett karaktär
//        förekommer och hur många giltiga karaktärer som finns.
// Inparametrar: number_of_characters - är mängden av giltiga karaktärer (I denna version är det bara a-z och deras versaller).
//               freqCounter - är arrayen som sparar resultatet av berakna_histogram_abs.
//
//*******************************************************************************************************************************
void skriv_histogram_abs(const int &number_of_characters, const int freqCounter[ANTAL_BOKSTAVER]) {
  cout << endl << "Resultat för bokstäverna A-Z" << endl << endl << "Totala antalet bokstäver: " << number_of_characters << endl;

  cout << endl << "Bokstavfördelning: " << endl << endl;
  for (int i = 0; i < ANTAL_BOKSTAVER; ++i) {
    cout << (char) (i+A_ASCII_NUMBER) << ": " << freqCounter[i] << endl;
  }
}
// ********************************
//
// Redovisning av uppgiften i ord. 
//
// ********************************

// Programmet läser in ett text från användaren där den kommer att beräkna förekomsten av olika bokstäver (dvs. den absoluta histogramet).
// Jag valde att spara förekomsten av de olika bokstäverna i en array of storleken ANTAL_BOKSTAVER, där index 0 innehåller antalet A som finns i texten 
// och index 1 innehåller antalet B som förekommer. Jag itererar över alla karaktärer i strängen och omvandla de till versaler och sen kollar ifall att
// karaktären är giltigt(dvs. A-Z). Om karaktären är giltig så ökar man siffran på ett specifikt index(som karaktären har) i arrayen. Och efter att vi har
// itererat över alla karaktärer borde vi ha förekomsten av alla giltiga karaktärer i arrayen. Senare kommer skriv_histogram_abs att iterera över arrayen
// och skriver ut resultatet. Vi adderar ascii numret för A med indexet i arrayen för att få ut karaktären från arrayen.