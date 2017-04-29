#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool check(string str){
  ifstream genome("genome.data");
  int count = 0;
  string tmp;
  string content((istreambuf_iterator<char>(genome)),
                (istreambuf_iterator<char>()));
  for(int i=0 ; i<content.length()-15 ; i++){
    tmp = content.substr(i, 15);
    if(tmp == str)
      count++;
    //randomness > 3
    if(count > 3) return false;
  }
  return true;
}

bool compare(string str1, string str2, int mutation){
  int count = 0;
  for(int i=0 ; i<15 ; i++){
    if(str1[i] != str2[i]){
      count++;
      if(count > mutation) return false;
    }
  }
  return true;
}

bool goalTest(string str, int p, string* sequence){
  string pattern[50];
  int pos[50];
  bool success;
  string tmp;

  pattern[0] = sequence[0].substr(p, 15);
  pos[0] = p;

  for(int seq=1 ; seq<50 ; seq++){
    success = false;
    for(int j=0 ; j<sequence[seq].length()-15 ; j++){
      tmp = sequence[seq].substr(j, 15);
      if(compare(str, tmp, 7)){
        pattern[seq] = tmp;
        pos[seq] = j;
        success = true;
        break;
      }
    }
    if(!success) break;
    if(seq == 49 && check(str)){
      cout << "Q3= " << str << endl;
      for(int m=0 ; m<50 ; m++){
        cout << "S" << m+1 << ":{(" << pattern[m] << "," << pos[m] << ")}";
        if(m != 49) cout << ", ";
      }
      cout << endl;
      return true;
    }
  }
  return false;
}

char change(char a){
  string s = "ATCG";
  return s[(s.find(a) + 1) % 4];
}

bool mutate(string origin, int pos, string* sequence){
  string str = origin;

  for(int i=0 ; i<15-4 ; i++){
    for(int j=i+1 ; j<15-3 ; j++){
      for(int k=j+1 ; k<15-2 ; k++){
        for(int l=k+1 ; l<15-1 ; l++){
          for(int m=l+1 ; m<15 ; m++){
            //change 4 times each
            for(int a=0 ; a<4 ; a++){
              str[i] = change(str[i]);
              for(int b=0 ; b<4 ; b++){
                str[j] = change(str[j]);
                for(int c=0 ; c<4 ; c++){
                  str[k] = change(str[k]);
                  for(int d=0 ; d<4 ; d++){
                    str[l] = change(str[l]);
                    for(int e=0 ; e<4 ; e++){
                      str[m] = change(str[m]);
                      if(goalTest(str, pos, sequence)) return true;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  /*debug*/
  if(str != origin){
    cerr << "error." << endl;
    exit(-1);
  }
  return false;
}

void Q3(){
  ifstream file("Q3.data");
  string sequence[50];
  string str;
  string origin;
  int i = 0;
  int turn = -1;
  int part[4] = {249, 499, -1, 749};
  bool success = false;

  while(!file.eof()){
    file >> sequence[i];
    i++;
  }
  do{
    turn++;
    turn = turn % 4;
    part[turn]++;
    origin = sequence[0].substr(part[turn], 15);
    success = mutate(origin, part[turn], sequence);
    /*debug*/
    if(part[2] > 250){
      cerr << "error 2." << endl;
      break;
    }
  }while(!success);

}

int main(){
  Q3();
  return 0;
}
