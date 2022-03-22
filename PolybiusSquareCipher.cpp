/*
 * Author: Mohamed Rady
 * Contact: mails.mail.mm@gmail.com
 * Program Name: PolybiusSquareCipher.cpp
 * Program Description: Polybius square cipher
 * Last Modification Date: 22 Mar 2022
 * Purpose: Handles ciphering/deciphering of an inputted sentence depending on the key given
*/
#include<bits/stdc++.h>

using namespace std;

//Cipher and decipher maps, which will be initialised depending on the key
map<char, string> cipherMap;
map<string, char> decipherMap;

/**
 * Map initialising function using the key sent as a parameter.
 * cipher is a boolen parameter to check if this map is a cipherMap or a decipherMap
 * It loops over every position possible in a 5x5 table (00, 01, etc.) and uses this equation (j + i * 5 + 'a')
 * to determine the character we should map this index to.
 * In the case cipher is true, we insert the characterIndex we calculated mapped to the row+column string value
 * For eg. 'a' : "55" in the case that the row is 5, and column is 5 (first digit in the key is 5).
 * In the case the cipher is false, each row+column string value is mapped to the character.
 * For eg. "55" : "a" in the case that the row is 5, and column is 5 (first digit in the key is 5).
*/
void initMap(string key, bool cipher) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            string row = to_string(key[i]-'0'), column = to_string(key[j]-'0');
            int charIndex = j + i * 5 + 'a';
            if (cipher)
                cipherMap.insert({ (char) (charIndex > 'i' ? charIndex+1 : charIndex),  row + column});
            else
                decipherMap.insert({ row + column, (char) (charIndex > 'i' ? charIndex+1 : charIndex)});
        }
    }
}

/**
 * Function that handles taking the input and deciphering the message.
 * It takes a string from a user, and a key, and calls initMap function with
 * the key and cipher = false. Then it loops over the string and checks for every
 * two consecutive digits and checks for their representation(value) in the decipherMap
 * and adds it to decipheredMessage. If a space is found, it adds the space to the
 * decipheredMessage string and adds one to the iterator value i.
 */
void decipherMessage() {
    string userInput, decipheredMessage, key, decipheredAlpha;
    cout << "Enter a message you would like to decipher:" << endl;
    getline(cin, userInput);

    cout << "Cipher key (5 numbers, eg: 51432):" << endl;
    getline(cin, key);
    while (key.size() != 5 || to_string(stoi(key))!=key) {
        cout << "Cipher key must be 5 digits next to each other.\nCipher key (5 numbers, eg: 51432):" << endl;
        getline(cin, key);
    }

    initMap(key, false);

    for (int i = 0; i < userInput.size(); i+=2) {
        string currTwoDigits = userInput.substr(i, 2);
        if (isdigit(currTwoDigits[0]) && isdigit(currTwoDigits[1]))
            decipheredMessage += decipherMap[currTwoDigits];
        else
            decipheredMessage += currTwoDigits;
        if (userInput[i+2] == ' ') {
            decipheredMessage += ' ';
            i++;
        }
    }

    cout << "The deciphered message is: " + decipheredMessage << endl;
}

/**
 * Function that handles taking the input and ciphering the message.
 * It takes a string from a user, and a key, and calls initMap function with
 * the key and cipher = true. Then it loops over the string and checks for every
 * letter, and checks for their representation(value) in the cipherMap and adds it to cipheredMessage.
 * If the letter is found, it adds value found in the map, else, it adds the character itself.
 */
void cipherMessage() {
    string userInput, cipheredMessage, key;
    cout << "Enter a message you would like to cipher:" << endl;
    getline(cin, userInput);

    cout << "Cipher key (5 numbers, eg: 51432):" << endl;
    getline(cin, key);
    while (key.size() != 5 || to_string(stoi(key))!=key) {
        cout << "Cipher key must be 5 digits next to each other.\nCipher key (5 numbers, eg: 51432):" << endl;
        getline(cin, key);
    }

    initMap(key, true);

    for (char i: userInput)
        if (isalpha(i))
            cipheredMessage += cipherMap[tolower(i == 'j' ? 'i' : i)];
        else
            cipheredMessage += i;

    cout << "Ciphered message: " + cipheredMessage << endl;
}

/**
 * Function that handles taking the operation input from the user
 */
int getInput() {
    int op;
    cout << "\nAhlan ya user ya habibi.\n"
            "What do you like to do today?\n"
            "1- Cipher a message\n"
            "2- Decipher a message\n"
            "3- End\n"
            ">>\n";
    cin >> op;
    return op;
}

/**
 * Main cipher loop where operation input is recieved and
 * the corresponding function is called.
 */
int main() {
    bool running = true;
    while (running) {
        int op = getInput();
        cin.clear();
        cin.sync();
        switch (op) {
            case 1:
                cipherMessage();
                break;
            case 2:
                decipherMessage();
                break;
            case 3:
                cout << "\nSalam Hapipi.";
                running = false;
                break;
            default:
                cout << "Please enter a valid operation..";
        }
    }
    return 0;
}