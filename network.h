#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <queue>
#include <stack>


class Network{
    
public:
    //Pre: none
    //Post: network created
    Network();
    
    //Pre: none
    //Post: user added to network
    void addUser(User* user);
    
    //Pre: s1 and s2 names of people in network who do not have a friendship
    //Post: friendship between user s1 and s2 is added
    int addConnection(std::string s1, std::string s2);
    
    //Pre: s1 and s2 names of people in network who have a friendship
    //Post: friendship between user s1 and s2 is deleted
    int deleteConnection(std::string s1, std::string s2);
    
    //Pre: name is represented in network
    //Post: corresponding id returned
    int getId(std::string name);
    
    //Pre: fname has users in the correct format
    //Post: network contains users in fname
    int readUsers(char* fname);
    
    //Pre: some users in network
    //Post: all users in network with details written to fname
    int writeUsers(char *fname);
    
    //Pre: none
    //Post: number of users in network returned
    std::size_t numUsers();
    
    //Pre: id in network
    //Post: User with corresponding id returned
    User* getUser(int id);
    
    //Pre: ids 'from' and 'to' in network
    //Post: shortest path between 'from' and 'to' returned
    std::vector<int> shortestPath(int from, int to);
    
    //Pre: id 'from' in network
    //Post: path to user 'distance' connections away returned (user stored in 'to')
    std::vector<int> distanceUser(int from, int& to, int distance);
    
    //Pre: id in network
    //Post: suggested friends returned (along with score in 'score')
    std::vector<int> suggestFriends(int who, int& score);
    
    //Pre: none
    //Post: groups of users (dijointed sets) returned
    std::vector<std::vector<int> > groups();
    
    
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);
    
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);
    
    int readPosts(char* fname);
    int writePosts(char* fname);
    
    
private:
    std::vector<User*> users_;
    
};

#endif
