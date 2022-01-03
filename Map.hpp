#pragma once
#include <string>
#include <algorithm>
#include "List.hpp"
namespace Map{
    //Traits to determine if road has cost or not?
    template <typename Tfrom, typename Tto, int Weight, int Cost,size_t ID>
    struct Road{
        typedef Tfrom from;
        typedef Tto to;
        // add extra weight, to allow for updated path_finding.
        static const int weight = Weight;
        static const int cost = Cost;
        static const size_t id = ID;
    };
        template <size_t ID>
    struct City{
        static const size_t id = ID;
    };

    //Trait with city names?? Specific names must be defined in global scope?
    // template <typename T>
    // struct City_Traits{
    //     static const char name* = "Unknown";
    // };

    // Template aliases

    template <typename TCities, typename TRoads>
    class MapGraph{
    public:
        typedef TRoads roads;
        typedef TCities cities;
    };
    template<typename City, typename Roads>
    struct GetRoadsFromCity_Impl{
        // typedef typename GetRoadsFromCity<
    };
    //First road in roads springs out from city
    template<typename City,typename Road1To,int R1W,int R1C, size_t R1ID,typename... Roads>
    struct GetRoadsFromCity_Impl<City,TL::List<Road<City,Road1To,R1W,R1C,R1ID>,Roads...>>{
        typedef typename TL::List_Concatenate<
                            Road<City,Road1To,R1W,R1C,R1ID>,
                            typename GetRoadsFromCity_Impl<City,TL::List<Roads...>>::type
                >::type type;
    };
    //First road in roads doesn't spring out from city
    template<typename City,typename Road1From, typename Road1To,int R1W,int R1C, size_t R1ID,typename... Roads>
    struct GetRoadsFromCity_Impl<City,TL::List<Road<Road1From,Road1To,R1W,R1C,R1ID>,Roads...>>{
        typedef typename GetRoadsFromCity_Impl<City,TL::List<Roads...>>::type type;
    };
    template<typename City>
    struct GetRoadsFromCity_Impl<City,TL::List<>>{
        typedef TL::List<> type;
        // typedef typename GetRoadsFromCity<
    };

    template<typename City,typename Graph>
    struct GetRoadsFromCity{
        typedef typename GetRoadsFromCity_Impl<City,typename Graph::roads>::type type;
    };
}