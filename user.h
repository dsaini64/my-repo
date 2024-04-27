#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <set>
#include "post.h"


class User {

public:

  //Pre: none
  //Post: User created
  User();

  //Pre: none
  //Post: User created with corresponding id, name, year, zip, friends
  User(int id, std::string name, int year, int zip, std::set<int> friends);

  //Pre: id not part of User's friends
  //Post: id added to User's friends
  void addFriend(std::size_t id);

  //Pre: id part of User's friends
  //Post: id deleted from User's friends
  void deleteFriend(std::size_t id);

  //Pre: none
  //Post: return id of user
  std::size_t getId();

  //Pre: none
  //Post: return name of user
  std::string getName();

  //Pre: none
  //Post: return year of user
  std::size_t getYear();

  //Pre: none
  //Post: return zip of user
  std::size_t getZip();

  //Pre: none
  //Post: return friends of user
  std::set<int> & getFriends();

    int numPosts();
        
    
    void addPost(Post* post_ptr);
    std::vector<Post*> getPosts();
    std::string getPostsString(int howMany, bool showOnlyPublic);
    


private:
  int id_;
  std::string name_;
  int year_;
  int zip_;
  std::set<int> friends_;
  std::vector<Post *> messages_;

};

#endif
