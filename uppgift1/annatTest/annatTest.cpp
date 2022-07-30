#include <iostream>
using namespace std;

int main(){

  int a;
  int b = 12;
  a = 0;

  cout << "a = " << a << endl;
  cout << a+b << '\n' << "a-b = " << a-b << endl;

  return 0;
}

//  ###########
//  # Rapport #
//  ###########

/*
Problemet med koden var att det saknades ett semicolon på rad 8 i koden.

Fel meddelanden:

annatTest.cpp: In function ‘int main()’:
annatTest.cpp:8:8: error: expected ‘;’ before ‘cout’
    8 |   a = 0
      |        ^
      |        ;
    9 |
   10 |   cout << "a = " << a << endl;

Det var ganska lätt att hitta felen på grund av att den står i fel meddelandet.
*/
