#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>

const char* INPUT_FILE = "./the1.inp";
const unsigned int MAX_LINE_SIZE = 20;

template<>
bool std::less<SkylineElem>(SkylineElem const& arg0, SkylineElem const& arg1)
{
  return (arg0.start < arg1.start);
}

struct BuildingElem
{
  unsigned int start;
  unsigned int height;
  unsigned int end;

  BuildingElem(unsigned int start, unsigned int height, unsigned int end)
  : start(start), height(height), end(end) {}
};
struct SkylineElem
{
  unsigned int start;
  unsigned int height;  
  
  SkylineElem(unsigned int start, unsigned int height)
  : start(start), height(height) {}
};
typedef std::vector<BuildingElem> BuildingVectorType;
typedef std::set<SkylineElem> SkylineSetType;


void algo0(BuildingVectorType buildingVector, SkylineSetType& outSkylineSet)
{
  BuildingElem firstBuilding = buildingVector.begin();
  outSkylineSet.insert(SkylineElem(firstBuilding.start, firstBuilding.height));
  outSkylineSet.insert(SkylineElem(firstBuilding.start, 0));

  for (BuildingVectorType::iterator bIter = buildingVector.begin() + 1;
    bIter != buildingVector.end();
    bIter++)
  {
    for (SkylineSetType::iterator sIter = outSkylineSet.begin();
      sIter != outSkylineSet.end();
      sIter++)
    {
    }
  }
}

void algo1(BuildingVectorType buildingVector, SkylineVectorType& outSkylineVector)
{
  
}

void readFile(std::string filename, BuildingVectorType& outVector, unsigned int& outAlgo)
{
  std::fstream file(filename, std::ios_base::in);
  if (!file.is_open())
    abort();

  char line[MAX_LINE_SIZE];
  memset(line, 0, MAX_LINE_SIZE);

  // Get algo type
  file.getline(line, MAX_LINE_SIZE);
  outAlgo = std::stoi(line);

  // Get number of entries
  memset(line, 0, MAX_LINE_SIZE);
  file.getline(line, MAX_LINE_SIZE);
  unsigned int numEntries = std::stoi(line);
  
  // Read triplets
  for (int i = 0; i < numEntries; i++)
  {
    memset(line, 0, MAX_LINE_SIZE);
    file.getline(line, MAX_LINE_SIZE);
    unsigned int tmpStart, tmpHeight, tmpEnd;
    sscanf(line, "%u %u %u", &tmpStart, &tmpHeight, &tmpEnd);
    BuildingElem tmpElem = {tmpStart, tmpHeight, tmpEnd};
    outVector.push_back(tmpElem);
  }
}

int main(int argc, char* argv[])
{
  BuildingVectorType buildingVector;
  unsigned int algoType = -1;

  readFile(INPUT_FILE, buildingVector, algoType);

  SkylineVectorType skylineVector;
  if (algoType == 0)
    algo0(buildingVector, skylineVector);
  else if (algoType == 1)
    algo1(buildingVector, skylineVector);
  else
    abort();
  
  return 0;
}
