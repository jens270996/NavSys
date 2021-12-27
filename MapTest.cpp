#include "Map.hpp"
#include "List.hpp"

int main(void){

    // Template aliases
    using Odense = Map::City<0>;
    using Aarhus = Map::City<1>;
    // Map::City_Traits<0>::name="Odense";
    // Map::City_Traits<1>::name="Aarhus";

    //roads in both directions. To allow updates in a single direction
    //also allows for singular interpretation of a path.
    using Odense_Aarhus = Map::Road<Odense,Aarhus,100,0>;
    using Aarhus_Odense = Map::Road<Aarhus,Odense,100,0>;

    using Map = Map::Map<TypeList::List<Odense,Aarhus>,TypeList::List<Odense_Aarhus,Aarhus_Odense>>;
}