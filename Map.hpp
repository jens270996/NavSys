#pragma once
#include <string>
#include <algorithm>
#include "List.hpp"
namespace Map{

    template <size_t ID>
    struct City{
        static const size_t id = ID;
    };

    template <size_t ID>
    struct City_Traits{
        static const char* name;
    };

    //Traits to determine if road has cost or not?
    template <typename Tfrom, typename Tto, int Weight, int Cost>
    struct Road{
        typedef Tfrom From;
        typedef Tto To;
        static const int weight = Weight;
        static const int cost = Cost;
    };

    template<typename... Ts>
    using Path = TypeList::List<Ts...>; //Path is a list of roads in the order they should be transversed.


    template <typename TCrossings, typename TRoads>
    class Map{


    };
}