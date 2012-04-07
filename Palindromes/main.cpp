#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

void reverse (const char *input, char *output) {
  size_t n = strlen(input);
  for (size_t i = 0; i < n; i++)
    output[i] = input[n - i - 1];
  output[n] = 0;
}

bool mirror (const char *input, char *output) {
  size_t n = strlen(input);
  char c;
  for (size_t i = 0; i < n; i++) {
    c = input[n - i - 1];
    switch (c) {
      case 'A':
      case 'H':
      case 'I':
      case 'M':
      case 'O':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case '1':
      case '8':
        break;
      case 'E':
        c = '3';
        break;
      case '3':
        c = 'E';
        break;
      case 'J':
        c = 'L';
        break;
      case 'L':
        c = 'J';
        break;
      case 'S':
        c = '2';
        break;
      case '2':
        c = 'S';
        break;
      case 'Z':
        c = '5';
        break;
      case '5':
        c = 'Z';
        break;
      default:
        return false;
    }
    output[i] = c;
  }
  output[n] = 0;
  return true;
}

bool iguais (char *str1, char *str2) {
  size_t n = strlen(str1);
  if (strlen(str2) != n)
    return false;
  for (size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i])
      return false;
  }
  return true;
}

int main () {
  char text[256];
  char aux[256];
  bool is_palin = false;
  bool is_mirror = false;
  bool first = true;
  while (cin.getline(text, 256)) {
    if (!first) {
      cout << endl;
    }
    is_palin = false;
    is_mirror = false;
    first = false;
    reverse (text, aux);
    is_palin = iguais(text, aux);
    if (mirror (text, aux))
      is_mirror = iguais(text, aux);;
    cout << text << " -- ";
    if (is_palin && is_mirror)
      cout << "is a mirrored palindrome." << endl;
    else if (is_palin)
      cout << "is a regular palindrome." << endl;
    else if (is_mirror)
      cout << "is a mirrored string." << endl;
    else
      cout << "is not a palindrome." << endl;
  }
  return 0;
}
