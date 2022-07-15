#include "MapSV.h"
#include <bits/stdc++.h>

using namespace std;

/* Como en el ppt 9SearchTrees, binary-search, 
 minimo para left maximo para right r. 
  O(log n) pasos. */
int MapSV::binary_search(int l, int r, string s){
    while(l<=r){
        int mitad = (l+r)/2; 
        if(this->v[mitad].first < s){
            r = mitad-1;
        }if(this->v[mitad].first > s){
            l = mitad+1;
        }else{
            return mitad;
        }
    }
    return -1;
}

MapSV::MapSV(){}

MapSV::~MapSV(){
    this->v.clear();
}


void MapSV::insert(pair<string,int> p){
    int aux = binary_search(0,v.size()-1,p.first);
    if(aux>-1){
        return;
    }
    this->v.push_back(p);
    this->tamano+=1;
    sort(v.begin(),v.end());
}

int MapSV::at(string s){
    int aux = binary_search(0,this->v.size()-1,s);
    if(aux<v.size() && aux>=0){
        return this->v[aux].second;
    }else{
        return INT_MIN;
    }
}

void MapSV::remove(string s){
    if(!this->v.empty()){
        int aux = binary_search(0,this->v.size()-1,s);
        if(aux >= 0){
           v.erase(v.begin()+aux);
        }
    }
}

int MapSV::size(){
    return this->v.size();
}

bool MapSV::empty(){
    return this->v.empty();
}