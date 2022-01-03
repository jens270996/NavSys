#include <iostream>
#include "Bus.hpp"
#include "RoadMap.hpp"

int main(void){
    using namespace Map::RoadMap;
    MapUpdater map;
    RoadInformation *roadInformation = new RoadInformation(40, true, "RoadInformation");
    BusUpdateCenter center(map);
    Bus<Aarhus,Odense,Slagelse> bus1(center);
    Bus<Aarhus,Odense,Slagelse> bus2(center);
    Bus<Aarhus,Odense,Slagelse> bus3(center);
    Bus<Aarhus,Odense,Slagelse> bus4(center);
    map.UpdateSignal(Update(37, roadInformation));

    bus1.printPath();
    return 1;
}