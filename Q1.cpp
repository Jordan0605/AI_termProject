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

void Q1(){
  ifstream file("Q1.data");
  string sequence[50];
  int pos[50];
  int i = 0;
  bool valid;
  string str;

  while (!file.eof()) {
    file >> sequence[i];
    i++;
  }
  for(int j=0 ; j<sequence[0].length()-15 ; j++){
    valid = true;
    pos[0] = j;
    str = sequence[0].substr(j, 15);
    //check if it appears in all squence
    for(int k=1 ; k<50 ; k++){
      pos[k] = sequence[k].find(str);
      if(pos[k] == -1){
        valid = false;
        break;
      }
    }
    if(valid){
      if(check(str)){
        cout << "Q1= " << str << endl;
        for(int l=0 ; l<50 ; l++){
          cout << "S" << l+1 << ":{(" << str << "," << pos[l] << ")}";
          if(l != 49) cout << ", ";
        }
        cout << endl;
        return;
      }
    }
  }
  cout << "Q1 doesn't have significant pattern." << endl;
}
 int main(){
   Q1();
   return 0;
 }
