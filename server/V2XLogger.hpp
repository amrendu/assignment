#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include<iostream>
class V2XLogger
{
  public:
  void printWarningMessage(std::string msg)
  {
      std::cout<<"Log :"<<msg<<"\n";
  }
};

#endif