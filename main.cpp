#include<iostream>
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
void getMessageForEncryption(string&);
void splitMessage(vector<string>&);
void scramble(vector<string>&, vector<int>&);
void unscramble(vector<string>&, vector<int>);
void storeInfo(vector<string>&, vector<int>&);
void getDecryptKey(vector<int>&);


//Container for Caesar Cipher algorithms
struct CaesarCipher
{
  int cipherKey = rand() % 35 + 10;    //Gets random number between 10 and 35

  //Caesar Cipher encryption algorithm
  string encrypt(string& msg)
  {
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
  string decrypt(string& msg)
  {
    for (int i = 0; msg[i] != '\0'; i++)
    {
      msg[i] = tolower(msg[i]);
      if(isalpha(msg[i]))
      {
        for(int j = 0; j < cipherKey; j++)
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
    for(int i = 0; i < key.size(); i++)
      cout << key[i];
    cout << endl;
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

  cin.ignore(choice.length() + 1,'\n');
  getMessageForEncryption(message);

  if(choice == "e")
  {
    caesar.encrypt(message);
    cout << message << endl;
    decryptKey.push_back(caesar.cipherKey);
    cout << decryptKey[0] << endl;

    //Runs python script that splits message in info.txt onto separate lines
    system("SplitMessage.exe");
    //Appends each line of info.txt into splitMsg vector
    splitMessage(splitMsg);

    for(int i = 0; i < splitMsg.size(); i++)
      cout << splitMsg[i] << " ";
    cout << endl;

    scramble.scramble(splitMsg, decryptKey);
  }



  // scramble.scramble(splitMsg);

  // cout << "Scrambled message: ";
  // for(int i = 0; i < splitMsg.size(); i++)
  //   cout << splitMsg[i] << " ";
  // cout << endl;
  //
  // storeInfo(splitMsg, scramble.key);

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
void getMessageForEncryption(string& msg)
{
  ofstream file;

  cout << "Enter a message to be encrypted: ";
  getline(cin, msg);

  file.open("info.txt");
  file << msg;
  file.close();
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
