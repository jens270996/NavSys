#include "Map.hpp"
#include "List.hpp"
#include "City.hpp"
#include "Path.hpp"
#include "PathFinding.hpp"
#include <iostream>

int main(void){

    // Map::City_Traits<0>::name="Odense";
    // Map::City_Traits<1>::name="Aarhus";

    //roads in both directions. To allow updates in a single direction
    //also allows for singular interpretation of a path.
    using Odense_Aarhus = Map::Road<City::Odense,City::Aarhus,100,50>;
    using Aarhus_Odense = Map::Road<City::Aarhus,City::Odense,100,50>;

    using MapGraph = Map::Map<TypeList::List<City::Odense,City::Aarhus>,TypeList::List<Odense_Aarhus,Aarhus_Odense>>;

    std::cout<<Map::Path<Odense_Aarhus>::from::id<<std::endl; 
    std::cout<<Map::Path<Odense_Aarhus>::to::id<<std::endl;
    std::cout<<Map::Path<Odense_Aarhus>::cost<<std::endl;
    std::cout<<Map::Path<Odense_Aarhus,Aarhus_Odense>::weight<<std::endl;

    typedef typename Map::FindPath<City::Odense,City::Aarhus,MapGraph>::type path;
}