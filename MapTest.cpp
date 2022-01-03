#include <iostream>
#include "Bus.hpp"
#include "RoadMap.hpp"

int main(void){
    using namespace Map::RoadMap;
    MapUpdater map;
    RoadInformation *roadInformation = new RoadInformation(40, true, "RoadInformation");
    BusUpdateCenter center(map);
    Bus<Aarhus,Odense,Slagelse> bus1(center);
    Bus<Herning,Middelfart,Nyborg> bus2(center);
    Bus<Herning,Aalborg,Grenaa> bus3(center);

    std::cout<<"Hi from main"<<std::endl;
    map.startUpdateGeneration();

    while(1){}
    return 1;
}