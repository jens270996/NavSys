#include <iostream>
#include "Bus.hpp"
#include "RoadMap.hpp"

int main(void){
    using namespace Map::RoadMap;
    Bus<Aarhus,Odense,Slagelse> bus1;
    bus1.printPath();
    return 1;
}