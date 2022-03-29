#include "FlightCalculator.hpp"
#include <iostream>
#include "Notification.hpp"
#include "MessageProxy.hpp"
#include "FlightCalculator.hpp"
using namespace std;




int main()
{
    

    MessageProxy server;
    if(!server.init())
    {
            cout<<"socket init failed\n";
    }

    if(!server.startServer())
    {
        cout<<"Start server failed\n";
    }
    else
    {
        cout<<"server started and listening ...";
    }
    return 0;

}