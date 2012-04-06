#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

int getwordintext (char *word, char *text, size_t s) {
  size_t j = 0;
  char c;
  for (; j < 256; j++) {
    if (s + j == 256)
      break;
    c = text[s+j];
    if ((c == ' ') || (c == 0))
      break;
    word[j] = c;
  }
  word[j] = 0;
  return s + j + 1;
}

bool isword (char *word) {
  size_t L = strlen(word);
  for (size_t i = 0; i < L; i++) {
    char c = word[i];
    if ( ( (c >= 65) && (c <= 90) ) || ( (c >= 97) && (c <= 122) ) )
      return true;
  }
  return false;
}

int main () {
  char text[256];
  char word[256];
  while (cin.getline(text, 256)) {
    size_t WC = 0;
    size_t textSize = strlen(text);
    int s = 0;
    while (s < textSize) {
      s = getwordintext (word, text, s);
      if (isword(word))
        WC++;
    }
    cout << WC << endl;
  }
  return 0;
}
