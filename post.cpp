#include "post.h"

Post::Post(){
    messageId_= 0;
    ownerId_ = 0;
    message_= "";
    likes_= 0;
}

Post::Post(int messageId, int ownerId, std::string message, int likes){
    messageId_ = messageId;
    ownerId_ = ownerId;
    message_ = message;
    likes_ = likes;
}

std::string Post::toString(){
    std::string message =  message_ + " Liked by " + std::to_string(likes_) + " people";
    return message;
}

int Post::getMessageId(){
    return messageId_;
}

int Post::getOwnerId(){
    return ownerId_;
}

std::string Post::getMessage(){
    return message_;
}

int Post::getLikes(){
    return likes_;
}

std::string Post::getAuthor() {
    return "";
}

bool Post::getIsPublic(){
    return true;
}

IncomingPost::IncomingPost(){
    isPublic_ = false;
    
}

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author) : Post(messageId, ownerId,  message, likes){
    author_ = author;
    isPublic_ = isPublic;
}


std::string IncomingPost::toString(){
    std::string message;
    if (isPublic_){
        message = author_ + "wrote: " +  Post::toString();
    }else{
        message = author_ + "wrote(private): " +  Post::toString();
    }
    
    return message;
}

std::string IncomingPost::getAuthor(){
    return author_;
    
}

bool IncomingPost::getIsPublic(){
    return isPublic_;
    
}


