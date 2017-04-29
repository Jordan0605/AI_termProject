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

bool goalTest(string str, string* sequence){
  string pattern[50];
  int pos[50];
  bool success;
  string tmp;

  for(int seq=0 ; seq<50 ; seq++){
    success = false;
    for(int j=0 ; j<sequence[seq].length()-15 ; j++){
      tmp = sequence[seq].substr(j, 15);
      if(compare(str, tmp, 5)){
        pattern[seq] = tmp;
        pos[seq] = j;
        success = true;
        break;
      }
    }
    if(!success) break;
    if(seq == 49 && check(str)){
      cout << "Q2= " << str << endl;
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
void Q3(){
  ifstream file("Q2.data");
  string sequence[50];
  string str;
  string origin;
  int i = 0;
  bool success = false;

  while(!file.eof()){
    file >> sequence[i];
    i++;
  }
  str = "CTGTTAGATCAACTG";
  if(goalTest(str, sequence)) cout << "success" << endl;
  else cerr << "error" << endl;

}

int main(){
  Q3();
  return 0;
}
