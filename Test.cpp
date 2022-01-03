#include <iostream>
#include <functional>
#include <boost/signals2/signal.hpp>
#include <boost/bind/bind.hpp>
#include "BusUpdateCenter.hpp"
#include "typeinfo"
#include "list"
//main update
using namespace map_updater;

void helloWorld(){
  std::cout << "  Message: " << std::endl;
            
}
namespace bs2 = boost::signals2;

void single_shot_slot(const bs2::connection &conn, const std::string &message)
{
  conn.disconnect();
  std::cout << message;
}
int main(int argc, char* argv[])
{
  RoadInformation* roadInformation = new RoadInformation(40, true, "RoadInformation");
  RoadInformation* roadInformation2 = new RoadInformation(30, true, "RoadInformation2");
  RoadInformation* roadInformation3 = new RoadInformation(50, true, "RoadInformation3");
  Update update(0, roadInformation);
  Update* update1 = new Update(1, roadInformation2);
  Update* update2 = new Update(2, roadInformation3);
  MapUpdater map;
  BusUpdateCenter Jylland(map);
  BusUpdateCenter Fyn(map);


  //Jylland._mapUpdater.connect(boost::bind(&BusUpdateCenter::update, roadInformation));
  
  // Jylland->_mapUpdater->connect(boost::bind(&BusUpdateCenter::busUpdateFyn, Jylland));
  // bus->_busUpdateCenter->connect(boost::bind(&Bus::hello, bus));


  std::list <int> routes = {0,1,2,3,4};

  TestObject* testObject = new TestObject(Jylland);
  
  testObject->_busUpdateCenter.connect(boost::bind(&TestObject::TheFunction, testObject),routes);

   map.UpdateSignal(update);


  return 0;
}