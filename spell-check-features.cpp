#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cctype>

using namespace std;

const int ALPHA_SIZE = 26;

struct TrieNode {
  TrieNode *children[ALPHA_SIZE];
  bool isEndOfWord;

  TrieNode() {
    isEndOfWord = false;
    for (int i = 0; i < ALPHA_SIZE; i++) {
      children[i] = NULL;
    }
  }
};

void insert(TrieNode *root, string word) {
  TrieNode *node = root;
  for (char c : word) {
    int index = c - 'a';
    if (!node->children[index]) {
      node->children[index] = new TrieNode();
    }
    node = node->children[index];
  }
  node->isEndOfWord = true;
}

bool search(TrieNode *root, string word) {
  TrieNode *node = root;
  for (char c : word) {
    int index = c - 'a';
    if (!node->children[index]) {
      return false;
    }
    node = node->children[index];
  }
  return (node != NULL && node->isEndOfWord);
}

void addWord(TrieNode* root, string word) {
  transform(word.begin(), word.end(), word.begin(), ::tolower);
  insert(root, word); 
}

void removeWord(TrieNode* root, string word) {
  TrieNode* node = root;
  for(char c : word) {
    int index = c - 'a';
    if(!node->children[index]) {
      return; 
    }
    node = node->children[index];
  }
  node->isEndOfWord = false;
}

void saveDictionary(TrieNode* root, string filename) {
  ofstream file(filename);
  // logic to save trie nodes to file
} 

TrieNode* loadDictionary(string filename) {
  ifstream file(filename);
  TrieNode* root = new TrieNode();
  // logic to load trie nodes from file
  return root;
}

bool doubleLetter(TrieNode* root, string word) {
  for(int i = 0; i < word.length()-1; i++) {
    if(word[i] == word[i+1]) {
      string newWord = word;
      newWord.erase(newWord.begin() + i);
      if(search(root, newWord)) {
        return true;
      }
    }
  }
  return false;
}

bool transposedLetter(TrieNode* root, string word) {
  for(int i = 0; i < word.length()-1; i++) {
    string newWord = word;
    swap(newWord[i], newWord[i+1]);
    if(search(root, newWord)) {
      return true;
    }
  }
  return false;
}

void rankSuggestions(vector<string> suggestions) {
  unordered_map<string, int> freq;
  // logic to score suggestions

  sort(suggestions.begin(), suggestions.end(), 
    [&](string a, string b) {
      return freq[a] > freq[b];  
  });
}

void interactiveMode() {
  string input;
  while(true) {
    getline(cin, input);
    // spellcheck input
  }
}

void batchMode(string filename) {
  ifstream file(filename);
  string line;
  while(getline(file, line)) {
    // spellcheck line
  }
} 

void printUsage() {
  cout << "Usage: " << endl;
  cout << "-i: Interactive mode" << endl;
  cout << "-f <file>: Batch mode" << endl;
}

int main(int argc, char* argv[]) {

  TrieNode* root = new TrieNode();
  root = loadDictionary("dict.txt");

string word;
  cout << "Enter word to check or 'quit' to exit: ";
  getline(cin, word);
  
  while(word != "quit") {

    transform(word.begin(), word.end(), word.begin(), ::tolower); 

    if(search(root, word)) {
      cout << "Spelling is correct." << endl;  
    }
    else {
      cout << "Spelling is incorrect. Suggestions:" << endl;
      suggestions(root, word);
    }
    
    cout << endl << "Enter word to check or 'quit' to exit: ";  
    getline(cin, word);
  }
  return 0;
}
