#include <iostream>

using namespace std;

void chooseMenu();
void getInput(string, char*);
int str_len(char *);
bool is_alpha(char *);
bool is_num(char *);
bool is_1_2(char *);

int main(){
   chooseMenu();
   return 0;
}

void chooseMenu(){
	char choice[255];
	do{
		getInput("For english to morse code (1); for morse code to english (2): ", choice);
	}while(!(is_num(choice) && is_1_2(choice)));
	//if((int)choice[0]==1)
		//engTOmorse();
    //else if((int)choice[0]==2)
		//morseTOeng();   	
	cout<<choice<<endl;
}

void getInput(string s, char arr[]){
	cout << s;
	cin.getline(arr,255);
}

int str_len(char array[]){
   int i=0;
   while(array[i]!='\0'){
      i++;
      //how do you append the null char?
   }return i;
} 

bool is_alpha(char arr[]){
	for(int i=0; i<str_len(arr); i++){
		if(!((arr[i]>='a'&& arr[i]<='z') || (arr[i]>='A' && arr[i]<='Z')))
			return false;
	}return true;
}

bool is_num(char arr[]){   
	for(int i=0; i<str_len(arr);i++){           //for the length of the string check
		if ((arr[i]>='0' && arr[i]<='9')){  //if the char at i is NOT between 0-9 
			cout<<" a number!!!"<<endl;
    		return true;                       //return false
		}else{
			cout<<"Not a number you fuck!" << endl;
			return false;
		}
		
	}                             //else return true
	//cout<<"yes it is a number"<<endl;
	//return true;
}

bool is_1_2(char arr[]){
	while(str_len(arr)==1){
		if(arr[0]>='1' && arr[0]<='2'){
			cout<<"is 1 or 2" << endl;
			return true;
		}else
			break;
	}
	cout<<"not 1 or 2"<<endl;
	return false;

}
