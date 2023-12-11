#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  uint64_t * frequencies = new uint64_t[257]();
  std::ifstream file(fname);
  int myChar;
  while ((myChar = file.get()) != EOF) {
    frequencies[(size_t)myChar]++;
  }
  frequencies[256]++;
  file.close();
  return frequencies;
}
