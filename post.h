#ifndef POST_H
#define POST_H
#include <string>


class Post{

public:
    Post();
    Post(int messageId, int ownerId, std::string message, int likes);
    int getMessageId();
    int getOwnerId();
    std::string getMessage();
    int getLikes();
    std::string virtual toString();
    std::string virtual getAuthor();
    bool virtual getIsPublic();
    
    
private:
    int messageId_;
    std::string message_;
    int likes_;
    int ownerId_;
    
};


class IncomingPost : public Post{
    public:
        IncomingPost();
        IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);
        
    private:
        std::string author_;
        bool isPublic_;
    
};

#endif
