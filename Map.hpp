#pragma once
#include <string>
#include <algorithm>
#include "List.hpp"
namespace BusRouter{
namespace Map{
    template <typename Tfrom, typename Tto, int Weight, int Cost,size_t ID>
    struct Road{
        typedef Tfrom from;
        typedef Tto to;
        static const int weight = Weight;
        static const int cost = Cost;
        static const size_t id = ID;
    };
        template <size_t ID>
    struct City{
        static const size_t id = ID;
    };

    template <typename TCities, typename TRoads>
    class MapGraph{
    public:
        typedef TRoads roads;
        typedef TCities cities;
    };
    //Empty primary
    template<typename City, typename Roads>
    struct GetRoadsFromCity_Impl{};

    //First road in roads springs out from city
    template<typename City,typename Road1To,int R1W,int R1C, size_t R1ID,typename... Roads>
    struct GetRoadsFromCity_Impl<City,TL::List<Road<City,Road1To,R1W,R1C,R1ID>,Roads...>>{
        //Concatenate Road which springs out from city with return from recursive call to GetRoadsFromCity_Impl
        typedef typename TL::List_Concatenate<
                            Road<City,Road1To,R1W,R1C,R1ID>,
                            typename GetRoadsFromCity_Impl<City,TL::List<Roads...>>::type
                >::type type;
    };
    //First road in roads doesn't spring out from city, make recursive call without first road.
    template<typename City,typename Road1From, typename Road1To,int R1W,int R1C, size_t R1ID,typename... Roads>
    struct GetRoadsFromCity_Impl<City,TL::List<Road<Road1From,Road1To,R1W,R1C,R1ID>,Roads...>>{
        typedef typename GetRoadsFromCity_Impl<City,TL::List<Roads...>>::type type;
    };
    //Went through all roads in graph. Return empty list.
    template<typename City>
    struct GetRoadsFromCity_Impl<City,TL::List<>>{
        typedef TL::List<> type;
    };

    template<typename City,typename Graph>
    struct GetRoadsFromCity{
        typedef typename GetRoadsFromCity_Impl<City,typename Graph::roads>::type type;
    };
}
}