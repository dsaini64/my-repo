#include <string>
#include "network.h"
#include "post.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <set>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    
    string userInput;
    bool flag = true;
    
    char inputFileName[256];
    strcpy(inputFileName, argv[1]);
    
    Network myNetwork = Network();
    myNetwork.readUsers(inputFileName);
    
    while (flag) {
        
        cout << "Enter an option number, along with any relevant parameters: ";
        getline(cin, userInput);
        
        if (userInput[0] == '1' && userInput[1] != '0') {
            stringstream inputWords(userInput);
            vector<string> words;
            string token_str;
            while (getline(inputWords, token_str, ' ')) {
                words.push_back(token_str);
            }
            
            string name = words[1] + " " + words[2];
            
            
            User newUser = User(myNetwork.numUsers(), name, stoi(words[3]), stoi(words[4]), set<int>());
            myNetwork.addUser(&newUser);
            
        } else if (userInput[0] == '2') {
            
            stringstream inputWords(userInput);
            vector<string> words;
            string token_str;
            while (getline(inputWords, token_str, ' ')) {
                words.push_back(token_str);
            }
            
            string name1 = words[1] + " " + words[2];
            string name2 = words[3] + " " + words[4];
            
            int result = myNetwork.addConnection(name1, name2);
            
            if (result == -1) {
                cout << "There was an error. Friend connection not added." << endl;
            }
            
        } else if (userInput[0] == '3') {
            
            stringstream inputWords(userInput);
            vector<string> words;
            string token_str;
            while (getline(inputWords, token_str, ' ')) {
                words.push_back(token_str);
            }
            
            string name1 = words[1] + " " + words[2];
            string name2 = words[3] + " " + words[4];
            
            int result = myNetwork.deleteConnection(name1, name2);
            
            if (result == -1) {
                cout << "There was an error. No friend connection deleted." << endl;
            }
            
        } else if (userInput[0] == '4') {
            
            for (int i = 0; i < myNetwork.numUsers(); i++) {
                cout << myNetwork.getUser(i)->getId() << " " << myNetwork.getUser(i)->getName() << " " << endl;
            }
            
        } else if (userInput[0] == '5') {
            
            stringstream inputWords(userInput);
            vector<string> words;
            string token_str;
            while (getline(inputWords, token_str, ' ')) {
                words.push_back(token_str);
            }
            
            string name = words[1] + " " + words[2];
            User* currentUser = myNetwork.getUser(myNetwork.getId(name));
            
            if (currentUser) {
                set<int> userFriends = currentUser->getFriends();
                
                for (const int& friend_id : userFriends) {
                    User* currentFriend = myNetwork.getUser(friend_id);
                    cout << currentFriend->getId() << " " << currentFriend->getName() << endl;
                }
                
            } else {
                cout << "User does not exist in social network." << endl;
            }
            
        } else if (userInput[0] == '6'){
            
            stringstream inputWords(userInput);
            vector<string> words;
            string token_str;
            while (getline(inputWords, token_str, ' ')) {
                words.push_back(token_str);
            }
            
            char* fileName = new char[words[1].length() + 1];
            strcpy(fileName, words[1].c_str());
            
            int result = myNetwork.writeUsers(fileName);
            if(result == -1){
                cout << "Error in writing to the file." << endl;
            }
            else{
                cout<< "# of users written to file = " << result << endl;
            }
            
            
        }
        
        else if (userInput[0] == '7'){
            
            stringstream inputWords(userInput);
            vector<string> words;
            string token_str;
            while (getline(inputWords, token_str, ' ')) {
                words.push_back(token_str);
            }
            
            string name1 = words[1] + " " + words[2];
            string name2 = words[3] + " " + words[4];
            
            
            int from_id = myNetwork.getId(name1);
            int to_id = myNetwork.getId(name2);
            
            vector<int> path = myNetwork.shortestPath(from_id, to_id);
            
            if (path.size() != 0 ) {
                
                cout << "Distance: "<<path.size()-1<<endl;
                
                for(int i = 0; i < path.size(); i++){
                    
                    if (i == path.size() - 1){
                        cout<< myNetwork.getUser(path[i])->getName() << endl;
                    }else{
                        cout<< myNetwork.getUser(path[i])->getName() << " -> ";
                    }
                    
                }
            }else{
                cout << "None"<<endl;
            }
        }
        
        else if (userInput[0] == '8'){
            
            stringstream inputWords(userInput);
            vector<string> words;
            string token_str;
            while (getline(inputWords, token_str, ' ')) {
                words.push_back(token_str);
            }
            
            
            string user = words[1] + " " + words[2];
            
            int distance = stoi(words[3]);
            int from = myNetwork.getId(user);
            int to;
            
            vector<int> result = myNetwork.distanceUser(from, to, distance);
            int result_size = result.size();
            cout << myNetwork.getUser(result[result_size - 1])->getName() << ": ";
            for (int i = 0; i < result_size; i++){
                if (i == result_size - 1){
                    cout << myNetwork.getUser(result[i])->getName()<<endl;
                    
                }else{
                    cout << myNetwork.getUser(result[i])->getName() << " -> ";
                }
                
            }
            
            
        }
        
        else if (userInput[0] == '9'){
            
            stringstream inputWords(userInput);
            vector<string> words;
            string token_str;
            while (getline(inputWords, token_str, ' ')) {
                words.push_back(token_str);
            }
            
            string user = words[1] + " " + words[2];
            
            int user_id = myNetwork.getId(user);
            int score;
            
            vector<int> suggestions = myNetwork.suggestFriends(user_id, score);
            
            if (score != -1){
                cout << "The suggested friend(s) is/are:" <<endl;
                
                for (int i = 0; i < suggestions.size(); i++){
                    cout << myNetwork.getUser(suggestions[i])->getName()<< " Score: "<<score<<endl;
                }
                
            }else{
                cout << "None" <<endl;
            }
            
            
            
        }
        
        
        else if (userInput == "10"){
            vector<vector<int>> mygroups = myNetwork.groups();
            
            for (int i = 0; i < mygroups.size(); ++i) {
                cout << "Set " << i + 1 << " => ";
                
                for (int j = 0; j < mygroups[i].size(); ++j) {
                    cout << myNetwork.getUser(mygroups[i][j])->getName();
                    
                    if (j < mygroups[i].size() - 1) {
                        cout << ", ";
                    }
                }
                
                cout << endl;
            }
        }
        
        else{
            flag = false;
            
        }
        
    }
    
    return 0;
}
    
    
    
