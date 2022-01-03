#include <iostream>
#include "Bus.hpp"
#include "RoadMap.hpp"

int main(void){
    using namespace Map::RoadMap;
    MapUpdater map;
    RoadInformation roadInformation(40, true, "RoadInformation");
    BusUpdateCenter center(map);
    Bus<Aarhus,Odense,Slagelse> bus1(center);
    Update update(37, roadInformation);
    map.UpdateSignal(update);

    bus1.printPath();
    return 1;
}