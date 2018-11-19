#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>

const unsigned int MAX_LINE_SIZE = 20;
unsigned int algoType = -1;

struct BuildingElem
{
  unsigned int start;
  unsigned int height;
  unsigned int end;
};

typedef std::pair<unsigned int, unsigned int> SkylineElem;

std::vector<SkylineElem> skylineVector;

void readFile(std::string argFilename)
{
  std::fstream file(argFilename, std::ios_base::in);
  if (!file.is_open())
    abort();

  char line[MAX_LINE_SIZE];
  memset(line, 0, MAX_LINE_SIZE);

  // Get algo type
  file.getline(line, MAX_LINE_SIZE);
  unsigned int 
  algoType = std::stoi(line);
  
}

int main(int argc, char* argv[])
{
  
}
