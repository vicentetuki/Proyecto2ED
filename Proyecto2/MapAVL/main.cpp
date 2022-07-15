#include <bits/stdc++.h>
#include "MapAVL.h"
using namespace std;

void string_generator(std::vector<std::string> &v){
  std::string temp;
  static const char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWYXZ"
                               "abcdefghijklmnopqrstuvwxyz"
                               "0123456789";
  srand((unsigned)time(NULL));
  temp.reserve(10);

  for(int i = 0; i < v.size(); ++i){
    for(int j = 0; j < 10; ++j){
      temp += letras[(int)((double)rand()/((double)RAND_MAX+1)*sizeof(letras)-1)];
    }
    v[i] = temp;
    temp.clear();
  }

}



void string_generator2(std::vector<std::string> &v){
  std::string temp;
  static const char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWYXZ"
                               "abcdefghijklmnopqrstuvwxyz"
                               "0123456789";
  srand((unsigned)time(NULL));
  temp.reserve(10);

  for(int i = 0; i < v.size(); ++i){
    for(int j = 0; j < 5; ++j){
      temp += letras[(int)((double)rand()/((double)RAND_MAX+1)*sizeof(letras)-1)];
    }
    v[i] = temp;
    temp.clear();
  }

}





std::vector<std::string> random_strings(int n){
  std::vector<std::string> v1(n);
  string_generator(v1);
  return v1;

}



std::vector<std::string> random_strings2(int n){
  std::vector<std::string> v1(n);
  string_generator2(v1);
  return v1;

}





int main(){

    double nano = 1000;

    MapAVL *m = new MapAVL();

     cout << "n;MapAVL-insert, MapAVL-at; MapAVL-at2;MapAVL-remove"<< endl;

    for(int n=1000;n<=10000;n=n+1000){
      double tiempo_MapAVL_insert=0 , tiempo_MapAVL_at=0, tiempo_MapAVL_remove=0, tiempo_MapAVL_at2=0;

    vector<string> v1 = random_strings(n);
    vector<string> v2 = random_strings2(n);

        //Insert de MapAVL
	      clock_t start = clock();
        for(int i=0; i<v1.size();i++)  m->insert({v1[i],i+1});
        tiempo_MapAVL_insert=((double)clock()-start) / CLOCKS_PER_SEC;

     
	      //At de MapAVL
	      start = clock();
        for(int i=0; i<v1.size();i++)   m->at(v1[i]);
        tiempo_MapAVL_at=((double)clock()-start) / CLOCKS_PER_SEC;

        //at2 de MapAVL
	      start=clock();
	      for(int i=0;i<v1.size();i++) m->at(v2[i]);
        tiempo_MapAVL_at2 = ((double)clock()-start)/ CLOCKS_PER_SEC;

        //Remove de MapAVL
	      start=clock();
        for(int i=0;i<v1.size();i++)   m->remove(v1[i]);
        tiempo_MapAVL_remove = ((double)clock()-start)/ CLOCKS_PER_SEC;

        cout<<n<<";"<<(tiempo_MapAVL_insert/(double)n)*nano<<";"<<(tiempo_MapAVL_at/(double)n)*nano<<";"<<(tiempo_MapAVL_at2/(double)n)*nano<<";"<<(tiempo_MapAVL_remove/(double)n)*nano<<endl;
   
    v1.clear();
    v2.clear();
   
    }
delete m;
return 0;

}
