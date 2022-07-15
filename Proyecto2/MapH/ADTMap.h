#ifndef ADTMAP_H
#define ADTMAP_H

#include <bits/stdc++.h>

using namespace std;

//Clase generica para cada mapa
class ADTMap{
  public:
    virtual void insert(std::pair<std::string,int>) = 0;
    virtual void remove(std::string) = 0;
    virtual int at(std::string) = 0;
    virtual int size() = 0;
    virtual bool empty() = 0;
};
#endif