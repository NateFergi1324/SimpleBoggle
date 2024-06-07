#include <map>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <random>
#include <cmath>
#include <string>
using namespace std;

// Global variables
std::unordered_map<unsigned int, string>* wordHashMap = new std::unordered_map<unsigned int, string>(); // create an array that will hold a map
int n;
vector<string> wordArray;
static unsigned int hashStr(string key)
{
    const string Keystring = key;
    const hash<string> hasher;
    const unsigned int result = hasher(Keystring);
    return result;

}
string findWordinHashmap(string str){
    unsigned int tempHash = (hashStr(str));
    //cout << "Checking for word: " << str << endl;
    auto it = wordHashMap->find(tempHash);
    if (it != wordHashMap->end()) {
        it = wordHashMap->find(tempHash);
        return wordHashMap->at(tempHash);
    }
    return "";
}

// BST Node struct
struct Node {
    char* value;
    int sumIndex;
    Node* parent;
    Node* left;
    Node* right;

    Node(char* v, int sumIndex) : value(v), left(nullptr), right(nullptr) {}
};
// BST class
class BinarySearch{
    private:
        Node* root;

        Node* insert(Node* node, char* value, int sumIndexV) {
            if (node == nullptr) {
                node = new Node(value, sumIndexV);
                return node;
            }
            if (sumIndexV < node->sumIndex) {
                return insert(node->left, value, sumIndexV);
            } else {
                return insert(node->right, value, sumIndexV);
            }
        }

        void recursiveIteration(Node* node){
            if(node == nullptr){
                return;
            }
            if(node != nullptr){
                string word = findWordinHashmap(node->value);
                if(word != ""){
                    wordArray.push_back(word);
                }

            }
            recursiveIteration(node->left);
            recursiveIteration(node->right);
            
        }

        void deleteTree(Node* node){
            if(node == nullptr){
                return;
            }
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    public:
        BinarySearch() : root(nullptr) {}

        Node* insert(char* value, int sumIndexV) {
            root = insert(root, value, sumIndexV);
        }

        void iteratorR(Node* node) {
            return recursiveIteration(root);
        }

        void deleteTreeR() {
            deleteTree(root);
            root = nullptr;
        }
};
void setN(){
    cout << "Set size of array: ";
    cin >> n;
    cout << "Size set to: " << n << endl;
}
string reverseString(string s) {
    std::reverse(s.begin(), s.end());
    return s;
}
char genRandLetter() {
    const char letters[] = "abcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, sizeof(letters) - 2);
    return letters[dist(rng)];
}
char** generateRandomCharArray(int size) {
    if (size <= 0) {
        throw invalid_argument("Array size must be greater than 0");
    }

    char** array = new char*[size];
    assert(array != nullptr);

    for (int i = 0; i < size; i++) {
        array[i] = new char[size + 1];
        assert(array[i] != nullptr);

        for (int j = 0; j < size; j++) {
            array[i][j] = genRandLetter();
        }
        array[i][size] = '\0';  // add /0 at the end of the row
    }

    cout << "Array generated successfully" << endl;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << array[i][j] << "    ";
        }
        cout << endl;
    }
    cout << endl;
    return array;
}
unordered_map<unsigned int, string>* readFile(string fileName){
    fstream file(fileName);
    string line; 
    if(file.is_open()){
        //cout << "File opened successfully!" << endl;
        while(getline(file, line)){
            if(line.length() <= n){
                //cout << "Adding word: " << line << " with hash: " << hashStr(line) << endl;
                wordHashMap->insert(make_pair(hashStr(line), line));
            }
            else{
                //cout << "Skipping line: " << line << " (line length: " << line.length() << ")" << endl;
            }
        }   
    }
    else{
        cout << "Failed to open file: " << fileName << endl;
    }
    return wordHashMap;
}
string constructWord(char** arr, pair<int, int> startPos, pair<int, int> endPos){
    string word = "";
    int Startrow = startPos.first;
    int Startcol = startPos.second;
    int Endrow = endPos.first;
    int Endcol = endPos.second;
    for(int i = Startrow; i <= Endrow; i++){
        for(int j = Startcol; j <= Endcol; j++){
            word += arr[i][j];
        }
    }
    return word;
}
char* findSingleLine(const string& tmpStr){
    char* arr = new char[tmpStr.size() + 1];
    std::copy(tmpStr.begin(), tmpStr.end(), arr);
    arr[tmpStr.size()] = '\0';
    return arr;
}
void buildTree(Node*& parent, string arr){
    if(arr.c_str() == nullptr || arr.c_str() == '\0'){ return; }
    int sumIndex = 0;
    for(int i = 0; i < arr.length(); i++){
        sumIndex += i;
    }
    const char* charArr = arr.c_str();
    Node* node = new Node(charArr, sumIndex);
    node->parent = parent;
    if (parent != nullptr) {
        if (sumIndex < ceil((parent->sumIndex) / 2)) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    }
    int Initmiddle = strlen(arr.c_str())/2;
    Initmiddle = ceil(Initmiddle);
    std::string s(arr);
    buildTree(node, s.substr(0, Initmiddle));
    buildTree(node, s.substr(Initmiddle, strlen(arr.c_str())));
}

char* getRow(char** arr, int row){
    if(0 <= row && row < n){
        return arr[row];
    }else{
        return nullptr;
    }
}

char* getCol(char** arr, int col){
    char* column = new char[n + 1];
    for(int i = 0; i < n; i++){
        if(col < strlen(arr[i])){
            column[i] = arr[i][col];
        } else {
            column[i] = '\0';
        }
    }
    return column;
}

void iterate2DArr(char** arr){
    int i = 0;
    int j = 0;
    while(i < n && j < n){
        char* row = getRow(arr, i);
        Node rowTree = buildTree(nullptr, row);
        rowTree.deleteTreeR();
        i++;
        char* col = getCol(arr, j);
        Node colTree = buildTree(nullptr, col);
        colTree.deleteTreeR();
        j++;
    }

}

/**vector<string> findWords(char** arr, unordered_map<unsigned int, string>* wordHashMap){
    // Old Algorithm holding for reference
    /**if(arr == nullptr || wordHashMap == nullptr) {
        throw invalid_argument("Array or wordHashMap is NULL");
    }
    vector<string> wordArray;

    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n ; j++) {
            string temp = constructWord(arr,make_pair(i, j), make_pair(i , j));
            string f = findWordinHashmap(temp);
            if(f != ""){
                wordArray.push_back(f);
            }
        

            for(int k = j+1; k < n ; k++){
                temp = constructWord(arr, make_pair(i, j), make_pair(i, k));
                string f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
                temp = reverseString(temp);
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
            }
        }
    }

    for(int j = 0; j < n; j++){
        for(int i = 0; i < n; i++){
            for(int k = i+1; k < n; k++){
                string temp = constructWord(arr, make_pair(i,j), make_pair(k, j));
                string f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
                temp = reverseString(temp);
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
            }
        }
    }

    return wordArray;
    if(arr == nullptr || wordHashMap == nullptr) {
        throw invalid_argument("Array or wordHashMap is NULL");
    }
    vector<string> wordArray;
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n;j++) {
            string temp = constructWord(arr,make_pair(i, j), make_pair(i , j));
            string f = findWordinHashmap(temp);
            if(f != ""){
                wordArray.push_back(f);
            }
            // These first two for loops are for back tracking 

            for(int k = i-1; k >= 0 ; k--){
                temp = constructWord(arr, make_pair(i, j), make_pair(i, k));
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
                temp = reverseString(temp);
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
            }
            
            for(int k = j-1; k >= 0 ; k--){
                temp = constructWord(arr, make_pair(i, j), make_pair(i, k));
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
                temp = reverseString(temp);
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
            }
            // these two for loops are for forward tracking
            for(int k = i+1; k < n ; k++){
                temp = constructWord(arr, make_pair(i, j), make_pair(k, j));
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
                temp = reverseString(temp);
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
            }
            
            for(int k = j+1; k < n ; k++){
                temp = constructWord(arr, make_pair(i, j), make_pair(i, k));
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
                temp = reverseString(temp);
                f = findWordinHashmap(temp);
                if(f != ""){
                    wordArray.push_back(f);
                }
            }
        }
    }
    return wordArray;
}*/
int calcPoints(vector<string> wordArray){
    int totalPoints = 0;
    for(int i = 0; i < wordArray.size(); i++){
        string tmpWrd = wordArray[i];
        for(int j = 0; j < tmpWrd.length(); j++){
            int tmpScore = 0;
            tmpScore += (((int)tmpWrd[j]) - 96) * 2;
            totalPoints += tmpScore;
        }
    }
    return totalPoints;
}
void timeIt(function<void()> func){
    auto start = chrono::steady_clock::now();
    func();
    auto end = chrono::steady_clock::now();
    auto diff = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken: " << diff << " milliseconds" << endl;
}
int main(){
    setN();
    //cout << "Generating random char array of size " << n << endl;
    char** charArray = generateRandomCharArray(n);
    //cout << "Reading file for words" << endl;
    unordered_map<unsigned int, string>* wordHashmap = readFile("word-list.txt");
    iterate2DArr(charArray);
    vector<string> finalWordArray = wordArray;
    
    // remove duplicates
    sort(finalWordArray.begin(), finalWordArray.end());
    finalWordArray.erase(unique(finalWordArray.begin(), finalWordArray.end()), finalWordArray.end());
    
    timeIt([&](){findWords(charArray, wordHashmap);});

    cout << "Found " << finalWordArray.size() << " words in the grid" << endl;
    for(int i = 0; i < finalWordArray.size(); i++){
        cout << finalWordArray[i] << endl;
    }
    cout << "Total points: " << calcPoints(finalWordArray) << endl;
    return 0;
}