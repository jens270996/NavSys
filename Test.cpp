#include "BusUpdateCenter.hpp"
#include <iostream>
#include <boost/signals2.hpp>
#include "MapUpdater.hpp"
    int f()
    {
        std::cout << "Hello" << std::endl;
        return 2;
    }
    struct HelloWorld
    {
        void operator() () const{
            std::cout << "hello, world!" << std::endl;

        }
    };
int main()
{


    BusUpdateCenter rute1;
    MapUpdater map;
    rute1.connect(&map.jyllandUpdate, 0);
    boost::signals2::signal<void ()> sig;


    HelloWorld hello;
    sig.connect(1,&f);
    sig.connect(0,hello);
    sig();
    return 0;
}