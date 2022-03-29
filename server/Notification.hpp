#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include<string>

//For simplicity of parsing every field as string
struct Notification
{
    public:
    std::string  distance;
    std::string  direction;
    std::string speed;
    std::string time;
    std::string carID;

    void printNotification()
    {
        std::cout<<"Distance :"<<distance<<std::endl;
        std::cout<<"Direction :"<<direction<<std::endl;
        std::cout<<"Speed :"<<speed<<std::endl;
        std::cout<<"Time :"<<time<<std::endl;
        std::cout<<"carID :"<<carID<<std::endl;
    }



};

#endif