#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<vector>
#include<algorithm>   //swap

using namespace std;

//Function prototypes
string encrypt(string, int);
string decrypt(string, int);
string getMessage();
void splitMessage(vector<string>&);
void scramble(vector<string>&);
void unscramble(vector<string>&, vector<int>);
void storeInfo(vector<string>&, vector<int>&);
void getDecryptKey(vector<int>&);

struct CaesarCipher
{
  //Caesar Cipher encryption algorithm
  string encrypt(string msg, int cipher)
  {
    for(int i = 0; msg[i] != '\0'; i++)
    {
      msg[i] = tolower(msg[i]);
      if(isalpha(msg[i]))
      {
        for(int j = 0; j < cipher; j++)
        {
          if(msg[i] == 'z')
            msg[i] = 'a';
          else
            msg[i]++;
        }
      }
    }
    return msg;
  }

  //Decrypts an already encrypted message
  string decrypt(string msg, int key)
  {
    for (int i = 0; msg[i] != '\0'; i++)
    {
      msg[i] = tolower(msg[i]);
      if(isalpha(msg[i]))
      {
        for(int j = 0; j < key; j++)
        {
          if(msg[i] == 'a')
            msg[i] = 'z';
          else
            msg[i]--;
        }
      }
    }
    return msg;
  }
};

struct Scramble
{
  vector<int> key;

  //Scrambles each word in msg vector
  void scramble(vector<string>& msg)
  {
    srand(time(0));
    for(int i = 0; i < msg.size(); i++)
    {
      for(int j = 0; j < msg[i].length(); j++)
      {
        int randInt = rand() % msg[i].length();
        int randInt2 = rand() % msg[i].length();

        swap(msg[i][randInt], msg[i][randInt2]);

        key.push_back(randInt);
        key.push_back(randInt2);
      }
    }
    for(int i = 0; i < key.size(); i++)
      cout << key[i];
    cout << endl;
  }

  void unscramble(vector<string>& msg, vector<int> decryptKey)
  {
    int num1 = key.size() - 1;
    int num2 = key.size() - 2;

    for(int i = 0; i < msg.size(); i++)
    {
      for(int j = 0; j < msg[i].length(); j++)
      {
        swap(msg[i][decryptKey[num1]], msg[i][decryptKey[num2]]);

        num1 -= 2;
        num2 -= 2;
      }
    }
  }
};

int main()
{
  //Creates random seed for random cipher length
  srand(time(0));
  int randNum = rand() % 35 + 10;    //Gets random number between 10 and 35

  CaesarCipher caesar;
  Scramble scramble;

  string message;
  vector<string> splitMsg;

  vector<int> decryptKey;

  message = getMessage();
  system("SplitMessage.exe");
  splitMessage(splitMsg);

  scramble.scramble(splitMsg);

  cout << "Scrambled message: ";
  for(int i = 0; i < splitMsg.size(); i++)
    cout << splitMsg[i] << " ";
  cout << endl;

  storeInfo(splitMsg, scramble.key);

  // scramble.unscramble(splitMsg, scramble.key);
  //
  // cout << "Unscrambled message: ";
  // for(int i = 0; i < splitMsg.size(); i++)
  //   cout << splitMsg[i] << " ";
  // cout << endl;

  return 0;
}

//Gets a message from the user and stores it in msg
//Stores users message in info.txt file for splitting using SplitMessage.py
string getMessage()
{
  ofstream file;
  string msg;

  file.open("info.txt");

  cout << "Enter a message that you would like to encrypt: ";
  getline(cin, msg);
  file << msg;

  file.close();

  return msg;
}

//Splits ciphered message to prepare for scrambling
void splitMessage(vector<string>& msg)
{
  ifstream file;
  string line;

  file.open("info.txt");

  while(getline(file, line))
    msg.push_back(line);

  file.close();
}

void storeInfo(vector<string>& eMsg, vector<int>& key)
{
  ofstream file;
  file.open("messages.txt");

  file << left << setw(20) << "Encrypted Message: ";
  for(int i = 0; i < eMsg.size(); i++)
    file << eMsg[i] << " ";
  file << endl;

  file << left << setw(20) << "Key: ";
  for(int i = 0; i < key.size(); i++)
    file << key[i] << " ";

  file << endl;

  file.close();
}

void getDecryptKey(vector<int>& key)
{
  Scramble scramble;

}