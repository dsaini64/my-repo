#include "user.h"

User::User() {
  id_ = -1;
  name_ = "";
  year_ = 0;
  zip_ = 0;
  friends_ = std::set<int>();
}

User::User(int id, std::string name, int year, int zip, std::set<int> friends) {
  id_ = id;
  name_ = name;
  zip_ = zip;
  year_ = year;
  friends_ = friends;
}

void User::addFriend(std::size_t id) {
    friends_.insert(id);
      
}

void User::deleteFriend(std::size_t id) {
  friends_.erase(id);
}

std::size_t User::getId() {
  return id_;
}

std::string User::getName() {
  return name_;
}

std::size_t User::getYear() {
  return year_;
}

std::size_t User::getZip() {
  return zip_;
}

std::set<int> &User::getFriends() {
  return friends_;
}

void User::addPost(Post* post_ptr){
    messages_.push_back(post_ptr);
}

std::vector<Post*> User::getPosts(){
    return messages_;
}


std::string User::getPostsString(int howMany, bool showOnlyPublic){
    
    std::string result;
    if (!showOnlyPublic){
        
        int index = messages_.size() - 1;
        
        for(int i = index; i > (index - howMany); i--){
            result += messages_[i]->toString();
            result += "\n\n";
        }
    }else{
        int count = 0;
        int index = messages_.size() - 1;
        while (count != howMany){
            if (messages_[index]->getIsPublic()){
                result += messages_[index]->toString();
                result += "\n\n";
                count++;
                index--;
            }
        }
    }
    
    return result;
}

int User::numPosts(){
    return messages_.size();
}
