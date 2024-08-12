#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

const int easyWordsSize = 10;
const string wordsEasy[easyWordsSize] = { "apple", "banana", "orange", "mango", "strawberry", "cherry", "apricot", "pineapple", "guava", "pomegranate" };

const int mediumWordsSize = 8;
const string wordsMedium[mediumWordsSize] = { "computer", "keyboard", "mouse", "laptop", "printer", "desktop", "floppydisk", "operatingsystem" };

const int hardWordsSize = 12;
const string wordsHard[hardWordsSize] = { "exquisite", "beekeeper", "abruptly", "absurd", "awkward", "azure", "blizzard", "blitz", "bookwarm", "cobweb", "embezzle", "gossip" };

const int maxGuesses = 6;

class Node
{
public:
    char data;
    Node* next;

    Node(char val) : data(val), next(nullptr) {}
};

class LinkedList
{
public:
    Node* head;
    Node* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    void append(char val)
    {
        Node* newNode = new Node(val);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    bool contains(char val)
    {
        Node* current = head;
        while (current)
        {
            if (current->data == val)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

class Skeleton
{
public:
    void hangmanPrint(int incorrectGuesses)
    {

        //system("Color E4");
        cout << "  -------" << endl;
        cout << "  |     |" << endl;
        switch (incorrectGuesses)
        {
        case 0:
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " =========" << endl;
            break;
        case 1:
            cout << "  |     O" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " =========" << endl;
            break;
        case 2:
            cout << "  |     O" << endl;
            cout << "  |     |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " =========" << endl;
            break;
        case 3:
            cout << "  |     O" << endl;
            cout << "  |    /|" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " =========" << endl;
            break;
        case 4:
            cout << "  |     O" << endl;
            cout << "  |    /|\\" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " =========" << endl;
            break;
        case 5:
            cout << "  |     O" << endl;
            cout << "  |    /|\\" << endl;
            cout << "  |    /" << endl;
            cout << "  |" << endl;
            cout << " ========== " << endl;
            break;
        case 6:
            cout << "  |     O" << endl;
            cout << "  |    /|\\" << endl;
            cout << "  |    / \\" << endl;
            cout << "  |" << endl;
            cout << " =========" << endl;
            break;
        }
    }


};

class RandomAndHiddenWords
{
public:
    string getRandomWord(const string wordList[], int size)
    {
        // Retrieve a random word from the specified word list
        int index = rand() % size;
        return wordList[index];
    }

    string getHiddenWord(const string& word, LinkedList& guessedLetters)
    {
        string hidden = "";
        for (char c : word)
        {
            if (guessedLetters.contains(c))
            {
                hidden += c;
            }
            else
            {
                hidden += '_';
            }
        }
        return hidden;
    }
};

int main()
{

    system("Color 0A");
    srand(static_cast<unsigned int>(time(0)));
    Skeleton sk;
    RandomAndHiddenWords rh;

    cout << "\nWelcome to Hangman!" << endl;
    cout << "Choose difficulty level:" << endl;
    cout << "1. Easy (fruits)" << endl;
    cout << "2. Medium (Computer terminologies)" << endl;
    cout << "3. Hard (English Grammar)" << endl;

    int difficulty;
    cout << "\n";
    cin >> difficulty;

    const string* wordList = nullptr;
    int wordListSize = 0;

    if (difficulty == 1)
    {
        system("Color E4");

        wordList = wordsEasy;
        wordListSize = easyWordsSize;
    }
    else if (difficulty == 2)
    {
        system("Color DE");
        wordList = wordsMedium;
        wordListSize = mediumWordsSize;
    }
    else if (difficulty == 3)
    {
        system("Color 16");
        wordList = wordsHard;
        wordListSize = hardWordsSize;
    }
    else
    {
        cout << "Invalid difficulty level. Exiting the game." << endl;
        return 0;
    }

    string word = rh.getRandomWord(wordList, wordListSize);
    LinkedList guessedLetters;//object of linked list

    int incorrectGuesses = 0;
    while (true)
    {
        sk.hangmanPrint(incorrectGuesses);
        cout << "\nWord: " << rh.getHiddenWord(word, guessedLetters) << endl;

        cout << "Guess a letter: ";
        char guess;
        cin >> guess;

        if (guessedLetters.contains(guess))
        {
            cout << "\nYou already guessed that letter!" << endl;
            continue;
        }

        guessedLetters.append(guess);

        if (word.find(guess) != string::npos)
        {
            cout << "\nCorrect guess!" << endl;
        }
        else
        {
            cout << "\nIncorrect guess!" << endl;
            incorrectGuesses++;
        }

        if (rh.getHiddenWord(word, guessedLetters) == word)
        {
            cout << "\nCongratulations! You won!" << endl;
            break;
        }

        if (incorrectGuesses == maxGuesses)
        {
            cout << "\nSorry, you lost! The word was: " << word << endl;
            cout << "  -------" << endl;
            cout << "  |     |" << endl;
            cout << "  |     O" << endl;
            cout << "  |    /|\\" << endl;
            cout << "  |    / \\" << endl;
            cout << "  |" << endl;
            cout << " =========" << endl;


            break;
        }
    }

    cout << "\nThank you for playing Hangman!" << endl;

    return 0;
}
