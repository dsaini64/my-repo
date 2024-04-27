
#include "network.h"
#include "user.h"
#include "post.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

//NOTE: pre and post conditions in corresponding header file

Network::Network(){
    std::vector<User*> users;
    users_ = users;
    
}


void Network::addUser(User* user){
    users_.push_back(user);
    
}
int Network::addConnection(std::string s1, std::string s2){
    int id1 = getId(s1);
    int id2 = getId(s2);
    
    if(id1 == -1 || id2 == -1 || id1 == id2){
        return -1;
    }
    
    
    User *user1 = getUser(id1);
    User *user2 = getUser(id2);
    
    
    user1->addFriend(id2);
    user2->addFriend(id1);
    return 0;
}
int Network::deleteConnection(std::string s1, std::string s2){
    
    int id1 = getId(s1);
    int id2 = getId(s2);
    
    if(id1 == -1 || id2 == -1 || id1 == id2){
        return -1;
    }
    
    
    User *user1 = getUser(id1);
    User *user2 = getUser(id2);
    
    
    user1->deleteFriend(id2);
    user2->deleteFriend(id1);
    return 0;
    
}
int Network::getId(std::string name){
    for(int i = 0; i < users_.size(); i++){
        if (name == users_[i]->getName()){
            return users_[i]->getId();
        }
    }
    
    std::cout << "Did not find user ID" <<std::endl;
    return -1;
    
}
int Network::readUsers(char* fname){
    
    //read the file
    std::ifstream networkFile;
    networkFile.open(fname);
    
    
    try{
        //read the lines from the file
        
        std::string line;
        int numUsers;
        
        //read the number of users in the network
        std::getline (networkFile, line);
        numUsers = stoi(line);
        
        for(int i = 0; i < numUsers; i++){
            int id;
            std::string name;
            int year;
            int zip;
            std::set<int> friends;
            
            
            //get user id
            std::getline(networkFile, line);
            id = stoi(line);
            
            //get user name
            std::getline(networkFile, line);
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            name = line;
            
            
            //get user birth year
            std::getline(networkFile, line);
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            year = stoi(line);
            
            //get user zip code
            std::getline(networkFile, line);
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            zip = stoi(line);
            
            //get user friends
            std::getline(networkFile, line);
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            std::stringstream friend_stream(line);
            std::string friend_str;
            
            while (getline(friend_stream, friend_str, ' ')) {
                int friend_id = stoi(friend_str);
                friends.insert(friend_id);
                
            }
            
            
            //add the new user to the users_ vector
            User * newUser = new User(id, name, year, zip, friends);
            addUser(newUser);
            
        }
        
        
        
    } catch(...){
        return -1;
    }
    
    return 0;
    
}

int Network::writeUsers(char* fname) {
    
    std::ofstream outputFile(fname);
    if (!outputFile.is_open()) {
        return -1;
    }
    
    try {
        std::size_t num_users = users_.size();
        outputFile << num_users << std::endl;
        
        for (int i = 0; i < users_.size(); ++i) {
            std::size_t id = users_[i]->getId();
            outputFile << id << std::endl;
            
            if (i == users_.size() - 1) {
                outputFile << '\t' << users_[i]->getName() << std::endl;
            } else {
                outputFile << '\t' << users_[i]->getName() << '\r' << std::endl;
            }
            
            outputFile << '\t' << users_[i]->getYear() << std::endl;
            
            int zipCode = users_[i]->getZip();
            if (zipCode < 10){
                outputFile << '\t'<< "0000" << users_[i]->getZip() << std::endl;
            }
            else if (zipCode < 100){
                outputFile << '\t'<< "000" << users_[i]->getZip() << std::endl;
            }
            if (zipCode < 1000){
                outputFile << '\t'<< "00" << users_[i]->getZip() << std::endl;
                
            }
            else if (zipCode < 10000){
                outputFile << '\t'<<'0' << users_[i]->getZip() << std::endl;
            }
            else{
                outputFile << '\t'<< users_[i]->getZip() << std::endl;
                
            }
            
            
            
            outputFile << '\t';
            std::set<int> friends = users_[i]->getFriends(); // Get friends as a set
            std::vector<int> friends_vec(friends.begin(), friends.end()); // Create a vector copy
            
            for (int j = 0; j < friends_vec.size(); ++j) {
                if (j == friends_vec.size() - 1) {
                    outputFile << friends_vec[j] << " " << std::endl;
                } else {
                    outputFile << friends_vec[j] << " ";
                }
            }
        }
        
    } catch (...) {
        return -1;
    }
    
    return users_.size();
}


std::size_t Network::numUsers(){
    return users_.size();
    
}


User* Network::getUser(int id){
    for(int i = 0; i < users_.size(); i++){
        if(users_[i]->getId() == id){
            return users_[i];
        }
    }
    
    return NULL;
    
}

std::vector<int> Network::shortestPath(int from, int to) {
    std::vector<int> shortestPath;
    std::vector<std::vector<int> > allPaths;
    std::queue<std::vector<int> > q;
    std::unordered_map<int, bool> visited;
    
    q.push({from});
    
    while (!q.empty()) {
        std::vector<int> currentPath = q.front();
        q.pop();
        int currentId = currentPath.back();
        
        if (currentId == to) {
            allPaths.push_back(currentPath);
        }
        
        visited[currentId] = true;
        
        for (int friendId : getUser(currentId)->getFriends()) {
            if (!visited[friendId]) {
                std::vector<int> newPath = currentPath;
                newPath.push_back(friendId);
                q.push(newPath);
            }
        }
    }
    
    if (!allPaths.empty()) {
        shortestPath = allPaths[0];
        for (std::vector<int>& path : allPaths) {
            if (path.size() < shortestPath.size()) {
                shortestPath = path;
            }
        }
    }
    
    return shortestPath;
}


std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    std::vector<int> path;
    std::queue<std::vector<int> > q;
    std::unordered_map<int, bool> visited;
    
    q.push({from});
    
    while (!q.empty()) {
        std::vector<int> currentPath = q.front();
        q.pop();
        int currentId = currentPath.back();
        
        if (currentPath.size() - 1 == distance) {
            to = currentId;
            path = currentPath;
            break;
        }
        
        visited[currentId] = true;
        
        for (int friendId : getUser(currentId)->getFriends()) {
            if (!visited[friendId]) {
                std::vector<int> newPath = currentPath;
                newPath.push_back(friendId);
                q.push(newPath);
            }
        }
    }
    
    return path;
}


std::vector<int> Network::suggestFriends(int who, int& score){
    
    std::vector<int> suggestions;
    score = -1;
    
    
    std::set<int> userFriends = getUser(who)->getFriends();
    
    std::unordered_map<int, int> commonFriendsTracker;
    
    for (int friendId : userFriends) {
        
        std::set<int> friendsOfFriends = getUser(friendId)->getFriends();
        
        for (int id : friendsOfFriends) {
            if (id == who || std::find(userFriends.begin(), userFriends.end(), id) != userFriends.end()) {
                continue;
            }
            
            commonFriendsTracker[id]++;
        }
    }
    
    std::size_t maxCount = 0;
    for(const auto &element : commonFriendsTracker){
        if(element.second > maxCount){
            suggestions.clear();
            suggestions.push_back(element.first);
            maxCount += element.second;
        } else if (element.second == maxCount) {
            suggestions.push_back(element.first);
        }
    }
    
    if (maxCount == 0){
        score = -1;
    }
    
    else{
        score = maxCount;
    }
    
    
    return suggestions;
}
std::vector<std::vector<int> > Network::groups() {
    std::vector<std::vector<int>> result;
    std::unordered_set<int> visited;
    
    for (int userId = 0; userId < numUsers(); ++userId) {
        if (visited.find(userId) == visited.end()) {
            std::vector<int> group;
            std::stack<int> stack;
            stack.push(userId);
            
            while (!stack.empty()) {
                std::size_t currentUserId = stack.top();
                stack.pop();
                
                if (visited.find(currentUserId) == visited.end()) {
                    visited.insert(currentUserId);
                    group.push_back(currentUserId);
                    
                    for (int friendId : getUser(currentUserId)->getFriends()) {
                        if (visited.find(friendId) == visited.end()) {
                            stack.push(friendId);
                        }
                    }
                }
            }
            
            result.push_back(group);
        }
    }
    
    return result;
}


void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic){
    
    Post * post_ptr;
    int messageId = getUser(ownerId)->numPosts() + 1;
    if(isIncoming){
        post_ptr = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
    }else{
        post_ptr = new Post(messageId, ownerId, message, likes);
    }
       
       getUser(ownerId)->addPost(post_ptr);
    
}

std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic){
    
    std::string result;
    for(int i = 0; i < users_.size(); i++){
        if (users_[i]->getId() == ownerId){
            result = users_[i]->getPostsString(howMany, showOnlyPublic);
            break;
        }
    }
        
    return result;
    
}

int Network::readPosts(char* fname){
    std::ifstream networkFile;
    networkFile.open(fname);
       
       try{
           //read the lines from the file
           
           std::string line;
           int numPosts;
           int postsRemaining;
           
           //read the number of posts in the file
           std::getline (networkFile, line);
           numPosts = stoi(line);
           
           postsRemaining = numPosts;
           
           while (postsRemaining > 0){
               
               int message_id;
               std::string message;
               int owner_user_id;
               int num_likes;
               std::string public_private;
               
               //get post id
               std::getline(networkFile, line);
               message_id = stoi(line);
               
               
               //get message
               std::getline(networkFile, line);
               line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
               line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
               message = line;
               
               
               //get owner user id
               std::getline(networkFile, line);
               line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
               owner_user_id = stoi(line);
               
               
               //get number of likes
               std::getline(networkFile, line);
               line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
               num_likes = stoi(line);
               
               
               //get public private (or blank line)
               std::getline(networkFile, line);
               line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
               line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
               public_private = line;
               
               
               if(public_private == ""){
                   Post * post_ptr = new Post(message_id, owner_user_id, message, num_likes);
                   getUser(owner_user_id)->addPost(post_ptr);
                   postsRemaining --;
               }else{
                   
                   bool isPublic;
                   if (public_private == "public"){
                       isPublic = true;
                   }else{
                       isPublic = false;
                   }
                   
                   //get author name
                   std::string author_name;
                   std::getline(networkFile, line);
                   line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
                   line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
                   author_name = line;
                   
                   IncomingPost * incoming_post_ptr = new IncomingPost(message_id, owner_user_id, message, num_likes, isPublic, author_name);
                   getUser(owner_user_id)->addPost(incoming_post_ptr);
                   postsRemaining--;
                   
                   
               }
               
           }
           
           
           
           
       } catch(...){
           return -1;
       }
       
       return 0;
       
    
}
int Network::writePosts(char* fname){
    return 0;
    
}
