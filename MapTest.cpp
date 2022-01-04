#include <iostream>
#include "Bus.hpp"
#include "RoadMap.hpp"

int main(void){
    using namespace Map::RoadMap;
    MapUpdater map;
    RoadInformation *roadInformation = new RoadInformation(40, true, "RoadInformation");
    BusUpdateCenter center(map);
    Bus<Aarhus,Odense,Slagelse> bus1(center,"Aarhus-Odense-Slagelse-Route-404");
    Bus<Herning,Middelfart,Nyborg> bus2(center,"Herning-Middelfart-Nyborg-Route-42");
    Bus<Herning,Aalborg,Grenaa> bus3(center,"Herning-Aalborg-Grenaa-Route-1337");

    map.startUpdateGeneration();

    while(1){}
    return 1;
}