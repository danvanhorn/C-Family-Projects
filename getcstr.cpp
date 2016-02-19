#include <iostream>
#include <cstdlib>

using namespace std;

void getInput(string s, char array[]);
int str_len(char array[]);

int main(){
   char *cstr;
   int x;
   cstr=new char; 
   getInput("Enter a string", cstr);
   cout << cstr << endl;
   x = str_len(cstr);
   cout << x << endl;   
//cout << cstr[0] << endl;
   //cout << cstr[1] << endl;
   //cout << (cstr-1) << endl;
   return 0;
}

void getInput(string s, char array[]){
   cout<< s << endl;
   cin.get(array, '\n');
   //*(array-1)+='\0';
}

int str_len(char array[]){
   int i=0;
   while(array[i]!='\0'){
      cout << i << " ";
      cout << array[i] << endl;
      i++;
   }return i;
} 

