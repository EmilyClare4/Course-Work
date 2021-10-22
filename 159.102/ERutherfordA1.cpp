//Emily Rutherford ID 21013503
#include<iostream>
#include <string>
using namespace std;

void checkstring (string line, int total);
int stringtoint(string str, int count);
int binarytodecimal(string s, int value);
string decimaltobinary(string b, int t);
string num, newBinary;
int total, decimal;
bool binary = false, valid = false;

int main(){
  cout <<"Enter a number: ";
  cin >>num;
  total = num.length();
  checkstring(num, total);
  if (valid){
    if(binary){
      decimal = binarytodecimal(num, total);
      cout <<"Converting binary to decimal. The result is "<<decimal<<endl;
    } else {
      newBinary = decimaltobinary(num, total);
      cout<<"Converting decimal to binary. The result is ";
      cout<<newBinary<<endl;
    }
  }
}

void checkstring (string line, int total){
//checks if number is binary or decimal, and that it fits the parameters
  int i, value;
  for(i=0;i<total;i++){
    if((line[i] < '0') || (line[i] > '9')){
      cout <<"This is not a valid number"<<endl;
      exit(10);
    }
  }
  if((line[0]=='0') && (total > 1)){
    binary = true;
    for(i=1;i<total;i++){
      if(line[i] <= '1'){
        valid = true;
      }
      else if(line[i] >'1'){
        cout <<"This is not a valid binary number"<<endl;
        exit(10);
      }
    }
  } else {
    binary = false;
  }
  if(total>9){
    if(binary){
      cout <<"This binary number has more than 9 binary digits"<<endl;
      exit(10);
    }
  }
  if(binary == false){
    value = stringtoint(line, total);
    if (value > 255){
      cout <<"This decimal number is outside the range 0 to 255"<<endl;
      exit(10);
    } else {
      valid = true;
    }
  }
}

int stringtoint(string str, int count) {
// function to convert a string to an integer
  int num = 0, i;
  for (i = 0; i < count; i++) {
    num = num * 10 + str[i] - 48;
  }
  return num;
}

int binarytodecimal(string s, int value){
  //Converts a binary number to decimal
  int num = stringtoint(s, value), decimal=0, endDigit, power=1;
  while(num){
    endDigit = num%10; //find the last digit of the binary number
    num = num/10; //remaining number once enddigit has been removed
    decimal += endDigit * power;//multiplying the last digit by the corresponding power
    power = power*2;//incrementing the power for the next loop
  }
  return decimal;
}

string decimaltobinary(string b, int t){
  //Converts a decimal number to binary
  int old = stringtoint(b, t), numBinary;
  string result, temp;
  while(old>0){
    numBinary = old%2;//Finds remainder, which will be a digit in the binary number
    old = old/2;//Finds the next number to be divided by 2
    temp = to_string(numBinary);//Converts numBinary to a string
    result = temp + result;//Adds the new remainder to the existing string of remainders which are creating the binary number
  }
  while(result.length() < 8){
    result = "0"+result;//pads out binary number with zeros to the right
  }
  result = result.insert(4,1,' ');//inserts a space after the fourth digit in the binary number
  return result;
}
