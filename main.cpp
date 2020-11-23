#include<iostream>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<vector>
#include<algorithm>   //swap

using namespace std;

//Function prototypes
string encryptDecrypt();
string encrypt(string&);
string decrypt(string&, int);
string getMessageForEncryption();
void getMessageAndKey(vector<string>&, vector<int>&);
void prepForScramble(string, vector<string>&);
void prepMessage(string);
void splitMessage(vector<string>&);
void scramble(vector<string>&, vector<int>&);
void unscramble(vector<string>&, vector<int>);
void storeInfo(vector<string>, vector<int>);
void getDecryptKey(vector<int>&);


//Container for Caesar Cipher algorithms
struct CaesarCipher
{
  int cipherKey = rand() % 35 + 10;    //Gets random number between 10 and 35

  //Caesar Cipher encryption algorithm
  string encrypt(string& msg)
  {
    cout << cipherKey << endl;
    for(int i = 0; msg[i] != '\0'; i++)
    {
      msg[i] = tolower(msg[i]);
      if(isalpha(msg[i]))
      {
        for(int j = 0; j < cipherKey; j++)
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

  //Reverses caesar cipher
  string decrypt(string& msg, vector<int>decryptKey)
  {
    for (int i = 0; msg[i] != '\0'; i++)
    {
      msg[i] = tolower(msg[i]);
      if(isalpha(msg[i]))
      {
        for(int j = 0; j < decryptKey[0]; j++)
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

//Container for scrambling and unscrambling algorithms
struct Scramble
{
  //vector<int> key;

  //Scrambles each word in msg vector
  void scramble(vector<string>& msg, vector<int>& key)
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
  }

  //Reverses scramble algorithm
  void unscramble(vector<string>& msg, vector<int> decryptKey)
  {
    int num1 = decryptKey.size() - 1;
    int num2 = decryptKey.size() - 2;

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

  CaesarCipher caesar;
  Scramble scramble;

  string choice;
  string message;
  vector<string> splitMsg;

  vector<int> decryptKey;

  cout << "Welcome to my message encryption program\nEnter \"done\" when you are done\n";
  choice = encryptDecrypt();
  cin.ignore(choice.length()+1,'\n');

  if(choice == "e")
  {

    message = getMessageForEncryption();

    caesar.encrypt(message);
    decryptKey.push_back(caesar.cipherKey);

    prepForScramble(message, splitMsg);

    scramble.scramble(splitMsg, decryptKey);

    storeInfo(splitMsg, decryptKey);

    cout << "Check EncryptedMessages.txt for your encrypted message and key\n";
  }

  else if(choice == "d")
  {
    getMessageAndKey(splitMsg, decryptKey);
    for(int i = 0; i < splitMsg.size(); i++)
      cout << splitMsg[i];
    cout << endl;
  }

  return 0;
}

string getMessageForEncryption()
{
  string msg;
  cout << "Enter a message for encryption: ";
  getline(cin, msg);

  return msg;
}

void getMessageAndKey(vector<string>& messageVector, vector<int>& keyVector)
{
  ofstream messageFileOutput;
  ofstream keyFileOutput;
  ifstream keyFileInput;
  ifstream messageFileInput;
  string msg;
  string tempKey;
  vector<string> tempVector;
  string line;

  cout << "Enter an encrypted message: ";
  getline(cin, msg);

  messageFileOutput.open("info.txt");
  messageFileOutput << msg;
  messageFileOutput.close();

  system("SplitMessage.exe");

  messageFileInput.open("info.txt");
  while(getline(messageFileInput, line))
    messageVector.push_back(line);
  messageFileInput.close();

  cout << "Enter the key to decrypt the message: ";
  getline(cin, tempKey);

  keyFileOutput.open("info.txt");
  keyFileOutput << tempKey;
  keyFileOutput.close();

  system("SplitMessage.exe");

  keyFileInput.open("info.txt");
  while(getline(keyFileInput, line))
    tempVector.push_back(line);
  keyFileInput.close();

  for(int i = 0; i < tempVector.size(); i++)
  {
      stringstream num(tempVector[i]);

      int x = 0;
      num >> x;

      keyVector.push_back(x);
  }
}

//Gets a message from the user and stores it in msg
//Stores users message in info.txt file for splitting using SplitMessage.py
void prepForScramble(string msg, vector<string>& msgVector)
{
  ofstream fileOutput;
  ifstream fileInput;
  string line;

  fileOutput.open("info.txt");
  fileOutput << msg;
  fileOutput.close();

  system("SplitMessage.exe");

  fileInput.open("info.txt");

  while(getline(fileInput, line))
    msgVector.push_back(line);

  fileInput.close();
}

void storeInfo(vector<string> eMsg, vector<int> key)
{
  ofstream file;
  file.open("EncryptedMessages.txt", ios_base::app);

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

string encryptDecrypt()
{
  string choice;
  cout << "Enter 'e' to encrypt or 'd' to decrypt: ";
  cin >> choice;

  return choice;
}
