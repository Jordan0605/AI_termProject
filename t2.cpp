#include <fstream>
#include <string.h>
#include <iostream>
#include <time.h>
#include <vector>
//#include <algorithm>
using namespace std;

struct A{
  int num;
  string s;
};
vector <A> v;
string seq[50];
ifstream genome("genome.data");
string content((istreambuf_iterator<char>(genome)),
  (istreambuf_iterator<char>()));


bool Compare(const A lhs,const A rhs) //vector的sorting用的函式
{
 return lhs.num<rhs.num ;
} 

int DifferentCount(string s1, string s2){ //比較兩個字串的差異數
  int count = 0;
  for(int i=0 ; i<s1.length() ; i++){
    if(s1[i]!=s2[i])
      count++;

  }
  return count;
}

bool CheckGenome(string str){ //如果再Genome出現次數少於2，回傳true
  int count = 0;
  string temp;
  for(int i=0 ; i<content.length()-15 ; i++){
    temp = content.substr(i, 15);
    if(temp == str)
      count++;
    if(count > 1) 
      return false;
  }
  return true;
}

int GetScore(string goal){ //若goal在mutant之後，在一個sequence有找到符合的字串的話，則獲得一分，一共有49個sequence，故最高分為49分

  int sum = 0;
  for(int j = 1 ; j < 50 ; j++){
    int count = 0;

    for(int k = 0 ; k < seq[j].length()-15 ; k++){

      if(DifferentCount(seq[j].substr(k,15),goal)<=5){
        count =1;
        break;
      }
    }
    sum+=count;
  }
  return sum;
}






int main()
{
  int i = 0;
  int sum;
  string str;
  ifstream file;
  file.open("q2.data");
  string goal;
  i = 0;
  while (getline(file, str)) //讀取每個sequence
  {
    seq[i] = str;
    i++;
  }

  for(int n=0; n < seq[0].length()-15 ; n++){ //對第一個sequence的所有985個可能的基因計算Score，並存到vector

    goal =  seq[0].substr(n,15);
    sum =  GetScore(goal);
    A temp;
    temp.num = sum;
    temp.s = goal;
    v.push_back(temp);



  }

  sort(v.begin(), v.end(), Compare); //排列985個基因


  bool find_ans = false;
  string m = "GTAC";
  for (int n=v.size()-1;n>0;n--){ //從分數最多的基因開始mutant
    vector<string> character[15];
    string mutant;

    for(i = 0; i<15;i++){ //依序查看基因的每一個字母
      mutant = v[n].s;//將基因讀入

      for(int j=0;j<4;j++){
        mutant[i] = m[j];//對第字母做G、T、A、C變形

        int score = GetScore(mutant);//取得score
        if (score>=v[n].num){ //若做完mutant的基因，其score>原本的Score，則將其存入character
          if(j==0)
            character[i].push_back("G");
          else if(j==1)
            character[i].push_back("T");
          else if(j==2)
            character[i].push_back("A");
          else 
            character[i].push_back("C");
          }
        }
      }

    for(int n1=0;n1<character[0].size();n1++)
      for(int n2=0;n2<character[1].size();n2++)
        for(int n3=0;n3<character[2].size();n3++)
          for(int n4=0;n4<character[3].size();n4++)
            for(int n5=0;n5<character[4].size();n5++)
              for(int n6=0;n6<character[5].size();n6++)
                for(int n7=0;n7<character[6].size();n7++)
                  for(int n8=0;n8<character[7].size();n8++)
                    for(int n9=0;n9<character[8].size();n9++)
                      for(int n10=0;n10<character[9].size();n10++)
                        for(int n11=0;n11<character[10].size();n11++)
                          for(int n12=0;n12<character[11].size();n12++)
                            for(int n13=0;n13<character[12].size();n13++)
                              for(int n14=0;n14<character[13].size();n14++)
                                for(int n15=0;n15<character[14].size();n15++){
                                  mutant = character[0][n1]+character[1][n2]+character[2][n3]+character[3][n4]+character[4][n5]+character[5][n6]+character[6][n7]+character[7][n8]+character[8][n9]+character[9][n10]+character[10][n11]+character[11][n12]+character[12][n13]+character[13][n14]+character[14][n15];
                                  int score = GetScore(mutant);
                                  if(score==49 && CheckGenome(mutant)) {
                                    cout << "Find：" << mutant <<endl;
                                    find_ans=true;
                                    break;
                                  }
                                }


                                if(find_ans)
                                  break;



                              }


                              return 0;




                            }