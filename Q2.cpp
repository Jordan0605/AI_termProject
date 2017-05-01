#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct S{
  int score;
  string s;
};

vector <S> v;
string sequence[50];
ifstream genome("genome.data");
string content((istreambuf_iterator<char>(genome)),
              (istreambuf_iterator<char>()));

bool check(string str){
  int count = 0;
  string tmp;
  for(int i=0 ; i<content.length()-15 ; i++){
    tmp = content.substr(i, 15);
    if(tmp == str)
      count++;
    //randomness > 3
    if(count > 3) return false;
  }
  return true;
}

bool compare(S a, S b){
  return a.score > b.score;
}

int difference(string a, string b){
  int count = 0;
  for(int i=0 ; i<a.length() ; i++){
    if(a[i] != b[i]) count++;
  }
  return count;
}

int getScore(string s){
  int result = 0;
  for(int i=1 ; i<50 ; i++){
    for(int j=0 ; j<sequence[i].length()-15 ; j++){
      if(difference(s, sequence[i].substr(j, 15)) <= 5){
        result++;
        break;
      }
    }
  }
  return result;
}

void printResult(string str){
  string tmp;
  int count;

  cout << "Q2 = " << str << endl;
  for(int i=0 ; i<50 ; i++){
    for(int j=0 ; j<sequence[i].length()-15 ; j++){
      tmp = sequence[i].substr(j, 15);
      count = 0;
      for(int k=0 ; k<15 ; k++){
        if(tmp[k] != str[k])
          count++;
      }
      if(count <= 5){
        cout << "S" << i+1 << "{(" << tmp << "," << j << ")}";
        if(i != 49)
          cout << ", ";
        else
          cout << endl;
        break;
      }
    }
  }
}

void Q2(){
  ifstream file("q2.data");
  int i = 0;
  S tmp;
  string mutate = "ATCG";
  string str;

  while(!file.eof()){
    file >> sequence[i];
    i++;
  }

  for(int j=0 ; j<sequence[0].length()-15 ; j++){
    tmp.s = sequence[0].substr(j, 15);
    tmp.score = getScore(tmp.s);
    v.push_back(tmp);
  }
  sort(v.begin(), v.end(), compare);

  //start from high score
  for(int k=0 ; k<v.size() ; k++){
    vector <char> c[15];
    for(int l=0 ; l<15 ; l++){
      str = v[k].s;
      for(int m=0 ; m<4 ; m++){
        str[l] = mutate[m];
        if(getScore(str) >= v[k].score)
          c[l].push_back(mutate[m]);
      }
    }
    //compose candidate which may be answer
    for(int n1=0;n1<c[0].size();n1++)
      for(int n2=0;n2<c[1].size();n2++)
        for(int n3=0;n3<c[2].size();n3++)
          for(int n4=0;n4<c[3].size();n4++)
            for(int n5=0;n5<c[4].size();n5++)
              for(int n6=0;n6<c[5].size();n6++)
                for(int n7=0;n7<c[6].size();n7++)
                  for(int n8=0;n8<c[7].size();n8++)
                    for(int n9=0;n9<c[8].size();n9++)
                      for(int n10=0;n10<c[9].size();n10++)
                        for(int n11=0;n11<c[10].size();n11++)
                          for(int n12=0;n12<c[11].size();n12++)
                            for(int n13=0;n13<c[12].size();n13++)
                              for(int n14=0;n14<c[13].size();n14++)
                                for(int n15=0;n15<c[14].size();n15++){
                                  str = "";
                                  str += c[0][n1];
                                  str += c[1][n2];
                                  str += c[2][n3];
                                  str += c[3][n4];
                                  str += c[4][n5];
                                  str += c[5][n6];
                                  str += c[6][n7];
                                  str += c[7][n8];
                                  str += c[8][n9];
                                  str += c[9][n10];
                                  str += c[10][n11];
                                  str += c[11][n12];
                                  str += c[12][n13];
                                  str += c[13][n14];
                                  str += c[14][n15];

                                  if(getScore(str) == 49 && check(str)) {
                                    printResult(str);
                                    return;
                                  }
                                }
  }
}

int main(){
  Q2();
  return 0;
}
