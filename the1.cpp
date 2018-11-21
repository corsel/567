#include <cstdlib>
#include <cstring>
#include <vector>
#include <set>
#include <fstream>
#include <iostream>

const char* INPUT_FILE = "./the1.inp";
const unsigned int MAX_LINE_SIZE = 20;

struct SkylineElem
{
  unsigned int start;
  mutable unsigned int height;  
  
  SkylineElem(unsigned int start, unsigned int height)
  : start(start), height(height) {}
  bool operator<(SkylineElem const& other) const
  {
    return (other.start > this->start);
  }
};
struct BuildingElem
{
  unsigned int start;
  unsigned int height;
  unsigned int end;

  BuildingElem(unsigned int start, unsigned int height, unsigned int end)
  : start(start), height(height), end(end) {}
};
typedef std::vector<BuildingElem> BuildingVectorType;
typedef std::set<SkylineElem> SkylineSetType;

void cleanDuplicates(SkylineSetType& skylineSet)
{
  for (SkylineSetType::iterator iter = skylineSet.begin(); iter != skylineSet.end();)
  {
    SkylineSetType::iterator next = std::next(iter);
    if (next == skylineSet.end()) break;
    if (next->height == iter->height)
      skylineSet.erase(next);
    else
      iter++;
  }
}

void algo0(BuildingVectorType buildingVector, SkylineSetType& outSkylineSet)
{
  // Insert the first block manually.
  BuildingVectorType::const_iterator first = buildingVector.begin();
  if (first == buildingVector.end()) return;
  outSkylineSet.insert(SkylineElem(first->start, first->height));
  outSkylineSet.insert(SkylineElem(first->end, 0));

  // Iterate through blocks.
  for (BuildingVectorType::iterator bIter = buildingVector.begin() + 1;
    bIter != buildingVector.end();
    bIter++)
  {
    bool flag = false;
    for (SkylineSetType::iterator sIter = outSkylineSet.begin();
      sIter != outSkylineSet.end();
      sIter++)
    {
      SkylineSetType::iterator next = std::next(sIter);

      // Block is past the last critical point.
      if (next == outSkylineSet.end())
      {
        if (!flag)
          outSkylineSet.insert(SkylineElem(bIter->start, bIter->height));
        else
          sIter->height = bIter->height;
        outSkylineSet.insert(SkylineElem(bIter->end, 0));
        break;
      }

      // We have not reached the starting point yet. 
      if (bIter->start >= next->start)
        continue;

      // Starting point of block is after this critical point.
      unsigned int maxHeight = bIter->height > sIter->height ? bIter->height : sIter->height;
      if (!flag)
      {
        if (bIter->start > sIter->start)
        {
          outSkylineSet.insert(SkylineElem(bIter->start, maxHeight));
        }
        if (bIter->start == sIter->start)
        {
          sIter->height = maxHeight;
        }
        flag = true;
      }
      // Block insertion is in progress.
      else
      {
        sIter->height = maxHeight;

        // Block ends after this critical point.
        if (bIter->end < next->start)
        {
          outSkylineSet.insert(SkylineElem(bIter->end, next->height));
          break;
        }
      }

      /*
      if (sIter->start > bIter->start && !flag)
      {
        if (bIter->height > currHeight)
          outSkylineSet.insert(SkylineElem(bIter->start, bIter->height));
        flag = true;
      }
      else if (bIter->end <= sIter->start && flag)
      {
        SkylineSetType::iterator tempIter = sIter;
        tempIter--;
        if (bIter->height > tempIter->height)
          outSkylineSet.insert(SkylineElem(bIter->end, sIter->height));
        flag = false;
      }
      else if (bIter->height > sIter->height && flag)
      {
        sIter->height = bIter->height;
      }
      currHeight = sIter->height;
      */
    }
  }
}

void algo1(BuildingVectorType buildingVector, SkylineSetType& outSkylineSet)
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

  SkylineSetType skylineSet;
  if (algoType == 0)
    algo0(buildingVector, skylineSet);
  else if (algoType == 1)
    algo1(buildingVector, skylineSet);
  else
    abort();

  cleanDuplicates(skylineSet);

  for (SkylineSetType::const_iterator iter = skylineSet.begin(); 
    iter != skylineSet.end();
    iter++)
  {
    std::cout << iter->start << " " << iter->height << std::endl;
  }
  
  return 0;
}
