#ifndef FLIGHTCALCULATOR_H
#define FLIGHTCALCULATOR_H

#include<thread>
#include<queue>
#include<string>
#include <mutex>
#include <functional>
#include "V2XLogger.hpp"
#include "Notification.hpp"
#include <condition_variable>

class FlightCalculatorService
{
    std::thread thd;
    std::condition_variable m_condVar;
      std::mutex m_mutex;

    std::queue<Notification> Q;
    V2XLogger logger;
    public:
        

    void startService();
    void postMessage( Notification m);
    void processQueue();
  
  bool isQEmpty()
  {
    return Q.empty();
  }
  ~FlightCalculatorService()
  {
    if(thd.joinable())
      thd.join();
  }
    

};

void FlightCalculatorService:: startService()
{
    std::cout<<"starting service thread\n";
    thd= std::thread(&FlightCalculatorService::processQueue,this);
}

void FlightCalculatorService::postMessage( Notification m)
{
  Q.push(m);
}



void FlightCalculatorService:: processQueue()
{
    std::cout<<"In thread func\n";
    while(1)
    {
        if(Q.empty())
        {
            //std::cout<<"waiting since q is empty\n";
            std::unique_lock<std::mutex> mlock(m_mutex);
            m_condVar.wait(mlock, std::bind(&FlightCalculatorService::isQEmpty, this));
        }
        else
          { 
            Notification msg = Q.front();
            Q.pop();
            //TODO
            // process the Notification structure and call warning according to criteria
            logger.printWarningMessage("Warning");
            std::cout<<Q.size()<<" "<<Q.empty()<<std::endl;
        }
    }
}

#endif