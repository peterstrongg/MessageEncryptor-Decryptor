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
void getMessageAndKey(string&, vector<int>&);
void scramble(string&, vector<int>&);
void unscramble(string&, vector<int>);
void storeInfo(string, vector<int>);

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
  string decrypt(string& msg, int decryptKey)
  {
    for (int i = 0; msg[i] != '\0'; i++)
    {
      msg[i] = tolower(msg[i]);
      if(isalpha(msg[i]))
      {
        for(int j = 0; j < decryptKey; j++)
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
  //Scrambles each word in msg vector
  void scramble(string& msg, vector<int>& key)
  {
    srand(time(0));
    for(int j = 0; j < msg.length(); j++)
    {
      int randInt = rand() % msg.length();
      int randInt2 = rand() % msg.length();

      swap(msg[randInt], msg[randInt2]);

      key.push_back(randInt);
      key.push_back(randInt2);
      }
  }

  //Reverses scramble algorithm
  void unscramble(string& msg, vector<int> decryptKey)
  {
    int num1 = decryptKey.size() - 1;
    int num2 = decryptKey.size() - 2;

    for(int j = 0; j < msg.length(); j++)
    {
      swap(msg[decryptKey[num1]], msg[decryptKey[num2]]);

      num1 -= 2;
      num2 -= 2;
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

    scramble.scramble(message, decryptKey);

    storeInfo(message, decryptKey);

    cout << "Check EncryptedMessages.txt for your encrypted message and key\n";
  }

  else if(choice == "d")
  {
    getMessageAndKey(message, decryptKey);

    caesar.decrypt(message, decryptKey[0]);
    decryptKey.erase(decryptKey.begin());

    scramble.unscramble(message, decryptKey);

    cout << message << endl;
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

void getMessageAndKey(string& msg, vector<int>& keyVector)
{
  ofstream messageFileOutput;
  ofstream keyFileOutput;
  ifstream keyFileInput;
  ifstream messageFileInput;
  string tempKey;
  vector<string> tempVector;
  string line;

  cout << "Enter an encrypted message: ";
  getline(cin, msg);

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

  //Converts integers from type string to type int
  for(int i = 0; i < tempVector.size(); i++)
  {
      stringstream num(tempVector[i]);

      int x = 0;
      num >> x;

      keyVector.push_back(x);
  }
}

void storeInfo(string eMsg, vector<int> key)
{
  ofstream file;
  file.open("EncryptedMessages.txt", ios_base::app);

  file << left << setw(20) << "Encrypted Message: " << eMsg << endl;;


  file << left << setw(20) << "Key: ";
  for(int i = 0; i < key.size(); i++)
    file << key[i] << " ";

  file << endl;

  file.close();
}

string encryptDecrypt()
{
  string choice;
  cout << "Enter 'e' to encrypt or 'd' to decrypt: ";
  cin >> choice;

  return choice;
}
