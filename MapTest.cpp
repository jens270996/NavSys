#include <iostream>
#include "Map.hpp"
#include "List.hpp"
#include "RoadMap.hpp"
#include "Path.hpp"
#include "PathFinding.hpp"

int main(void){
    using namespace Map::RoadMap;
    // Map::City_Traits<0>::name="Nyborg";
    // Map::City_Traits<1>::name="Odense";

    //roads in both directions. To allow updates in a single direction
    //also allows for singular interpretation of a path.

    using MapGraph = Map::RoadMap::MapGraph;

    std::cout<<Map::Path<Nyborg_Odense>::from::id<<std::endl; 
    std::cout<<Map::Path<Nyborg_Odense>::to::id<<std::endl;
    std::cout<<Map::Path<Nyborg_Odense>::cost<<std::endl;
    std::cout<<Map::Path<Nyborg_Odense,Odense_Nyborg>::weight<<std::endl;

    typedef typename Map::FindPath<Aarhus,Copenhagen,MapGraph>::type path;
    Map::PathFunctions<path>::PrintFull();
    auto array = Map::PathFunctions<path>::getRoadIdArray();
    for(size_t id : array){
        std::cout<<"Id from array: "<<id<<std::endl;
    }
    


    //extract weights from each road:

    //Kunne også være en vector i stedet:
    std::array<int,path::size> weights;
    int i=0;
    Map::PathFunctions<path>::ForEachRoad([&weights,&i](size_t id, int cost, int weight){
        weights[i++]=weight;
    });
    for(int weight : weights){
        std::cout<<"Weight from array: "<<weight<<std::endl;
    }
    return 1;
}