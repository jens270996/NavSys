#include <iostream>
#include <boost/signals2/signal.hpp>
#include "BusUpdateCenter.hpp"
#include "typeinfo"
    
//main update
using namespace map_updater;

int main(int argc, char* argv[])
{
  RoadInformation* roadInformation = new RoadInformation(40, true, "missing");
  RoadInformation* roadInformation2 = new RoadInformation(30, true, "Not missing");
  Update* update = new Update(0, roadInformation);
  
  // // Update* updates = new Update(1, new RoadInformation(60, true, "missing 2"));
  MapUpdater map;
  BusUpdateCenter Jylland(map);

    //Jylland.m_connection(MapUpdater::Update)
    // std::cout <<map.getText()<< std::endl;
    // std::cout <<map.getText() << std::endl;

    // Jylland.m_connection = Jylland._mapUpdater.connect(boost::bind(&BusUpdateCenter::busUpdateJylland, Jylland));
    
    Jylland._mapUpdater.connect(boost::bind(&BusUpdateCenter::busUpdateJylland, Jylland));
    Jylland._mapUpdater.connect(boost::bind(&BusUpdateCenter::busUpdateFyn, Jylland));

    map.UpdateSignal(" Hej hej", update);

    
    return 0;
}