// entire file as of now

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;
const int MAX_ATTEMPTS = 6;
const string WORDS_FILE = "words.txt";
const string ALLOWED_WORDS_FILE = "allowed.txt";

struct GameRecord{
    string word;
    int attempts;
    bool win;
};

// Function to read word list and store them in a vector
vector<string> readWordList(const string& filename){
    vector<string> wordList;
    ifstream file(filename);

    if (!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    string word;
    while (getline(file, word)){
        wordList.push_back(word);
    }
    file.close();
    return wordList;
}
// function to select random word from vector
string getRandomWord(const vector<string>& wordList){
    srand(time(0));
    int randomIndex = rand() % wordList.size(); // get random index within word list
    return wordList[randomIndex];
}

bool isGameOver(const string&guess, const string&secretWord){
    return guess == secretWord;
}

//function to check if guess is allowed
bool isValidGuess(const string& guess, const vector<string>& allowedWords){
    if (guess.length() != 5){
        cout << "Invalid guess. Please enter a 5 letter word.";
    }

    ifstream file(ALLOWED_WORDS_FILE);

    string word;

    while (file >> word){
        if (word == guess){
            file.close();
            return true;
        }
    }

    file.close();
    cout << "The word ' " << guess << " ' is not allowed." << endl;
    return false;
}

void printBoard(const string& guess, const string& secretWord){
    // more to come
}

string getGuess(){
        string guess;
        cout << "Enter your guess (5 letters): ";
        cin >> guess;
        return guess;
    }
// function to show feedback for guess( correct, misplaced, and missing letters)
void displayGuessResult(const string& word, const string& guess){
    for (int i = 0; i < 5; ++i){
        if (word[i] == guess[i]){
            cout << guess[i] << " "; //print correct in green
        } else if (word.find(guess[i]) != string::npos){
            cout << "? "; // print misplaced in yellow
        } else{
            cout << "X "; // print missing in gray
        }
    }
    cout << endl;
}
void playWordle(vector<GameRecord>& records){
    const int maxTries = 6;
    int tries = 0;

    srand(static_cast<unsigned int>(time(nullptr)));

    vector<string> wordList;
    ifstream allowedWords(ALLOWED_WORDS_FILE);
    string word;
    while (allowedWords >> word){
    wordList.push_back(word);
    }

    allowedWords.close();
    
    string secretWord = wordList[rand() % wordList.size()];

    string guess;
    
    while (tries < maxTries){
        cout << "Enter your guess (5 letters): ";
        cin >> guess;

        if (isValidGuess(guess, wordList)){
            // provideFeedback
            printBoard(guess, secretWord);
    
                if (isGameOver(guess, secretWord)){
                    cout << "Congratulations! You guessed the word.\n";
                    records.push_back({secretWord, tries + 1, true});
                    break;
        }
        ++tries;
    } else {
        // if not valid do not increment tries
    }
    }

    if (tries == maxTries){
        cout << "Sorry, you ran out of tries. The word was: " << secretWord << "\n";
        records.push_back({secretWord, maxTries, false});

    }
}
void displayStatsSummary(const vector<GameRecord>& records){
    int timesPlayed = records.size();
    int totalAttempts = 0;
    int wins = 0;
    int currentStreak = 0;
    int longestStreak = 0;

    for (const auto& record : records){
        totalAttempts += record.attempts;
        if (record.win){
            wins++;
            currentStreak++;
        } else{
            currentStreak = 0;
        }
        longestStreak = max(longestStreak, currentStreak);
    }
    double winPercentage = (timesPlayed > 0) ? (static_cast<double>(wins) / timesPlayed) * 100.0 : 0.0;
    double averageAttempts = (timesPlayed > 0) ? static_cast<double>(totalAttempts) / timesPlayed : 0.0;

    cout << "==========================\n";
    cout << "    STATISTICS SUMMARY\n";
    cout << "==========================\n";
    cout << "Times Played:        " << timesPlayed << "\n";
    cout << "Average Attempts:    " << averageAttempts << "\n";
    cout << "Win Percentage:      " << winPercentage << "%\n";
    cout << "Current Streak:      " << currentStreak << "\n";
    cout << "Longest Streak:      " << longestStreak << "\n\n";

    cout << "--------------------------\n";
    cout << "WORD     ATTEMPTS      WIN\n";
    cout << "--------------------------\n";

    for (const auto& record : records){
        cout << setw(8) << record.word << setw(10) << record.attempts;
        cout << setw(8) << (record.win ? "Yes" : "No") << "\n";
    }
    cout << "\nPress [enter] to continue";
    cin.ignore();
    cin.get();
}
void saveStatsToFile(const vector<GameRecord>& records, const string& filename){
    ofstream file(filename);

    for (const auto& record : records){
        file << record.word << " " << record.attempts << " " << record.win << "\n";
    }
}

void loadStatsFromFile(vector<GameRecord>& records, const string& filename){
    ifstream file(filename);

    if (file.is_open()){
        records.clear();

        string word;
        int attempts;
        bool win;

        while (file >> word >> attempts >> win){
            records.push_back({word, attempts, win});
        }
        file.close();
    }
}
void displayHowToPlay(){
    cout << "=============================================\n";
    cout << "                 HOW TO PLAY\n";
    cout << "=============================================\n";
    cout << "Guess the Wordle in 6 tries.\n\n";
    cout << "HOW TO PLAY:\n";
    cout << "- Each guess must be a valid 5 letter word.\n";
    cout << "- The color of the tiles will change to show\n";
    cout << "  you how close your guess was to the word.\n\n";
    cout << " --- --- --- --- ---\n";
    cout << "| W | | E || A || R || Y |\n";
    cout << " --- --- --- --- ---\n";
    cout << "W is in the word and in the correct spot.\n\n"; //(make the 'W' and dashes around it green)
    cout << " --- --- --- --- --- ---\n";
    cout << "| P || I || L || L || S |\n";
    cout << "--- --- --- --- --- ---\n";
    cout << "I is in the word but in the wrong spot.\n\n"; // (make the 'I' and dashes around it yellow)
    cout << "--- --- --- --- --- --- ---\n";
    cout << "| V || A || G || U || E |\n";
    cout << "--- --- --- --- --- --- ---\n";
    cout << "U is not in the word in any spot.\n\n"; // (make the 'U' and dashes around it a dark gray)
    cout << "\nPress [enter] to continue";
    cin.ignore();
    cin.get();
}
int main() {
    vector<GameRecord> gameRecords;
    loadStatsFromFile(gameRecords, "statistics.txt");

    vector<string> allowedWords = readWordList(ALLOWED_WORDS_FILE);

    while (true){
        cout << "=========================\n";
        cout << "    WELCOME TO WORDLE\n";
        cout << "=========================\n\n";
        cout << "1. Play Wordle\n";
        cout << "2. How to Play\n";
        cout << "3. Statistics Summary\n";
        cout << "4. Reset Statistics\n";
        cout << "5. Exit\n\n";
        cout << "Select an option: ";
    
        int option;
        cin >> option;

        switch (option){
            case 1:
                playWordle(gameRecords);
                break;
            case 2:
                displayHowToPlay();
                break;
            case 3:
                displayStatsSummary(gameRecords);
                break;
            case 4:
                // reset stats
                gameRecords.clear();
                cout << "Statistics have been reset.\n";
                break;
            case 5:
                // save stats before exit
                saveStatsToFile(gameRecords, "statistics.txt");
                cout << "Exiting the program. \n";
                return 0;
        default:
            // invalid
            cout << "Invalid option. Please select a valid option. \n";
            break;
        }
    }
    return 0;
}
