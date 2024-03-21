/*
 * Program:     Encryption and Decryption program
 * Course:      CS112 - Structured Programming
 * Authors:     Hady Mohammed Meawad Mohammed       20230455        meawad.hady@gmail.com
 *              Marwan Hussein Mohamed Mohamed      20230382        marawanlabana649@gmail.com
 *
 * Lab No.:     S19, S20
 * TA:          Eng. Yomna Fathy
 * Work:        Hady Mohammed --> Simple Substitution Cipher and Decipher
 *              Mahmoud --> Viagenere Cipher and decipher
 *              Marwan --> Atabsh Cipher and Decipher
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

void atbash_cipher()
{
    string sentence;
    string ciphersentence;
    getline(cin, sentence);
    for (int i = 0; i < sentence.length(); i++)
    {
        if (isalpha(sentence[i]))
        {
            char newchar = tolower(sentence[i]);
            char cipherchar = char(int('z') - (int(newchar) - int('a')));
            if (isupper(sentence[i]))
                cipherchar = toupper(cipherchar);
            ciphersentence += cipherchar;
        }
        else
            ciphersentence += sentence[i];
    }
    cout << ciphersentence << endl;
}

void atbash_cipher_v2()
{
    string sentence;
    string Ciphersentence = "";
    getline(cin, sentence);
    for (int i = 0; i < sentence.length(); i++)
    {
        if (isalpha(sentence[i]))
        {
            if (int(toupper(sentence[i])) <= int('M'))
            {
                char newchar = tolower(sentence[i]);
                char CipherChar = char(int('m') - (int(newchar) - int('a')));
                if (isupper(sentence[i]))
                    CipherChar = toupper(CipherChar);
                Ciphersentence += CipherChar;
            }
            else
            {
                char newchar = tolower(sentence[i]);
                char CipherChar = char(int('z') - (int(newchar) - int('n')));
                if (isupper(sentence[i]))
                    CipherChar = toupper(CipherChar);
                Ciphersentence += CipherChar;
            }
        }
        else
            Ciphersentence += sentence[i];
    }
    cout << Ciphersentence << endl;
}

string Vignere_Cipher(string message, string repeated_keyword)
{
    transform(message.begin(), message.end(), message.begin(), ::toupper);
    transform(repeated_keyword.begin(), repeated_keyword.end(), repeated_keyword.begin(), ::toupper);
    string encrypted_message{};

    int index{};

    string final;

    for (size_t i = 0; i < message.size(); i++)
    {
        if (index == repeated_keyword.size())
        {
            index = 0;
        }

        final.push_back(repeated_keyword[index]);
        index++;
    }

    for (size_t i = 0; i < message.size(); i++)
    {
        if (message[i] == 32 || (message[i] - '0' <= 9 && message[i] - '0' >= 0))
        {
            encrypted_message.push_back(message[i]);
        }
        else
            encrypted_message.push_back(((message[i] + final[i]) % 26) + 65);
    }
    return encrypted_message;
}

string Vignere_Cipher_Encoding(string encrypted_message, string repeated_keyword)
{
    string message{};
    int index{};
    string final;

    // Convert encrypted_message and repeated_keyword to uppercase
    transform(encrypted_message.begin(), encrypted_message.end(), encrypted_message.begin(), ::toupper);
    transform(repeated_keyword.begin(), repeated_keyword.end(), repeated_keyword.begin(), ::toupper);

    for (size_t i = 0; i < encrypted_message.size(); i++)
    {
        if (index == repeated_keyword.size())
        {
            index = 0;
        }

        final.push_back(repeated_keyword[index]);
        index++;
    }

    for (size_t i = 0; i < encrypted_message.size(); i++)
    {
        int result{};
        if (encrypted_message[i] == 32 || (encrypted_message[i] - '0' <= 9))
        {
            message.push_back(encrypted_message[i]);
        }
        else
        {
            result = encrypted_message[i] - 65;
            for (size_t j = 65; j <= 90; j++)
            {
                if ((final[i] + j) % 26 == result)
                {
                    message.push_back(j);
                }
            }
        }
    }
    return message;
}

// initializing alphabets string
string alpha = "abcdefghijklmnopqrstuvwxyz";

// function to check uniqueness of a given string
bool is_string_unique(string input)
{
    // initialize boolean variable as true
    bool is_unique = true;

    for (int i = 0; i < input.length(); i++)
    {
        for (int j = i + 1; j < input.length(); j++)
        {
            // if a character is repeated
            if (input[i] == input[j])
            {
                // set boolean variable to false
                is_unique = false;
                return is_unique;
            }
        }
    }

    return is_unique;
}

// function that creates the new alphabet using the entered key
string create_key()
{
    string ciphering, key; // initializing 2 string: ciphering is the new alphabet, key
    bool is_unique = true;

    // Keep prompting until a unique key is entered
    do
    {
        cout << "Enter a unique Key:"; // prompt user to enter the key
        getline(cin, key);             // get the entered key by user

        // switch every character to lowercase
        for (auto &x : key)
        {
            x = tolower(x);
        }

        // Check if the key is unique
        is_unique = true;
        for (int i = 0; i < key.length(); ++i)
        {
            for (int j = i + 1; j < key.length(); ++j)
            {
                if (key[i] == key[j])
                {
                    is_unique = false;
                    break;
                }
            }
            if (!is_unique)
            {
                break;
            }
        }
        // check if key is 5 letters
        if (key.length() != 5)
        {
            cout << "Key must have exactly 5 characters." << endl;
            continue;
        }

        if (!is_unique)
        {
            cout << "Key is not unique. Please enter a key with distinct characters." << endl;
        }
    } while (!is_unique || key.length() != 5);

    // initialize the first part of new alphabet
    ciphering = key;

    // adding the rest of the alphabets
    for (int i = 0; i < 26; i++)
    {
        if (not key.contains(alpha[i]))
        {                          // using .contains to return whether the letter is in the key or not
            ciphering += alpha[i]; // the letter isn't in the key, add it
        }
    }
    return ciphering; // return new alphabet (encrypted)
}

// simple substitution ciphering function
void simple_sub_cipher()
{
    // initializing ciphering alphabet, str (used to enter line), newline (string of encrypted line)
    string ciphering = create_key(), str, newline;

    // prompt user to enter a line tto cipher
    cout << "Enter A Sentence to Cipher:";
    getline(cin, str);

    // iterating through every character and switch
    for (char j : str)
    {
        j = tolower(j); // convert character to lower
        if (isalpha(j))
        { // check if the character is a letter
            // if character is a letter --> switch
            // using .find to find the real index of the letter and use it in encrypted alphabet
            newline += ciphering[alpha.find(j)];
        }
        else
        { // if not a letter --> symbol or number --> add it as it is
            newline += j;
        }
    }
    // print the encrypted text
    cout << "Encrypted Text: " << newline << endl;
}

// simple substitution deciphering function
void simple_sub_decipher()
{
    // initializing ciphering alphabet, str (used to enter line), newline (string of encrypted line)
    string ciphering = create_key(), str, newline;

    // prompt user to enter a line tto cipher
    cout << "Enter A Sentence to Cipher:";
    getline(cin, str);

    // iterating through every character and switch
    for (char j : str)
    {
        // convert character to lower
        if (isalpha(j))
        { // check if the character is a letter
            // if character is a letter --> switch
            // using .find to find the  index of the letter in the ciphered alphabet and use it in real alphabet
            newline += alpha[ciphering.find(j)];
        }
        else
        { // if not a letter --> symbol or number --> add it as it is
            newline += j;
        }
    }
    // print the encrypted text
    cout << "Decrypted Text: " << newline << endl;
}

int main()
{
    // creating choice variable
    char choice;

    // main program loop
    do
    {
        // Program instructions
        cout << "This is a program  to encrypt and decrypt text strings" << endl;
        cout << "Menu:" << endl;
        cout << "Encription:" << endl;
        cout << "   1. Atbash Cipher" << endl;
        cout << "   2. Atbash Cipher (two halves)" << endl;
        cout << "   3. Vigenere Cipher" << endl;
        cout << "    4. simple sub Cipher" << endl;

        cout << "Decryption:" << endl;
        cout << "   5. Atbash Decipher" << endl;
        cout << "   6. Atbash Decipher (two halves)" << endl;
        cout << "   7. Vigenere DeCipher " << endl;
        cout << "    8. simple sub Decipher" << endl;
        cout << "9. Exit" << endl;

        // prompt user choice
        cout << "Enter your choice:";
        cin >> choice;
        cin.ignore(); // ignore the rest of text

        // check if entered character is a digit
        if (not isdigit(choice))
        { // if not --> prompt user to enter an integer
            cout << "Enter an integer from 1-7" << endl;
            continue; // skip the next part of the loop
        }

        // switching over the different encrypting techniques
        switch (choice)
        {
        case '1':
            cout << "Enter a message to cipher:";
            atbash_cipher();
            break;

        case '2':
            cout << "Enter a message to cipher:";
            atbash_cipher_v2();
            break;

        case '3':
        {
            string message, repeated_keyword;
            cout << "Please enter a message for Vigenere Cipher (up to 80 characters): ";
            getline(cin, message);
            if (message.length() > 80)
            {
                cout << "Message exceeds 80 characters." << endl;
                break;
            }
            if (!all_of(message.begin(), message.end(), ::isalpha))
            {
                cout << "Massage should only contain alphabetic characters." << endl;
                break;
            }
            cout << "Please enter the keyword (up to 8 characters): ";
            getline(cin, repeated_keyword);
            if (repeated_keyword.length() > 8)
            {
                cout << "Keyword exceeds 8 character." << endl;
                break;
            }
            if (!all_of(repeated_keyword.begin(), repeated_keyword.end(), ::isalpha))
            {
                cout << "Keyword should only contain alphabetic characters." << endl;
                break;
            }
            cout << "Ciphered message: " << Vignere_Cipher(message, repeated_keyword) << endl;
            break;
        }
        case '4':
            simple_sub_cipher();
            break;
        case '5':
            cout << "Enter a message to deipher:";
            atbash_cipher_v2();
            break;

        case '6':
            cout << "Enter a message to decipher:";
            atbash_cipher_v2();
            break;

        case '7':
        {
            string encrypted_message, repeated_keyword;
            cout << "Please enter a message for Vigenere Cipher (up to 80 characters): ";
            getline(cin, encrypted_message);
            if (encrypted_message.length() > 80)
            {
                cout << "Message exceeds 80 characters." << endl;
                break;
            }
            if (!all_of(encrypted_message.begin(), encrypted_message.end(), ::isalpha))
            {
                cout << "Massage should only contain alphabetic characters." << endl;
                break;
            }
            cout << "Please enter the keyword (up to 8 characters): ";
            getline(cin, repeated_keyword);
            if (repeated_keyword.length() > 8)
            {
                cout << "Keyword exceeds 8 character." << endl;
                break;
            }
            if (!all_of(repeated_keyword.begin(), repeated_keyword.end(), ::isalpha))
            {
                cout << "Keyword should only contain alphabetic characters." << endl;
                break;
            }
            cout << "Deciphered message: " << Vignere_Cipher_Encoding(encrypted_message, repeated_keyword) << endl;
            break;
        }

        case '8':
            simple_sub_decipher();
            break;
        }

    } while (choice != '9');

    cout << "Thanks for using the Program" << endl;

    return 0;
}
