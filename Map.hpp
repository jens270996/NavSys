#pragma once
#include <string>
#include <algorithm>
#include "List.hpp"
namespace Map{
    //Traits to determine if road has cost or not?
    template <typename Tfrom, typename Tto, int Weight, int Cost>
    struct Road{
        typedef Tfrom from;
        typedef Tto to;
        static const int weight = Weight;
        static const int cost = Cost;
    };

    template <typename TCities, typename TRoads>
    class Map{
    public:
        typedef TRoads roads;
        typedef TCities cities;
    };
    template<typename City, typename Roads>
    struct GetRoadsFromCity_Impl{
        // typedef typename GetRoadsFromCity<
    };
    //First road in roads springs out from city
    template<typename City,typename Road1To,int Road1Weight,int Road1Cost,typename... Roads>
    struct GetRoadsFromCity_Impl<City,TypeList::List<Road<City,Road1To,Road1Weight,Road1Cost>,Roads...>>{
        typedef typename TypeList::List_Concatenate<Road<City,Road1To,Road1Weight,Road1Cost>,typename GetRoadsFromCity_Impl<City,TypeList::List<Roads...>>::type>::type type;
    };
    //First road in roads doesn't spring out from city
    template<typename City,typename Road1From, typename Road1To,int Road1Weight,int Road1Cost,typename... Roads>
    struct GetRoadsFromCity_Impl<City,TypeList::List<Road<Road1From,Road1To,Road1Weight,Road1Cost>,Roads...>>{
        typedef typename GetRoadsFromCity_Impl<City,TypeList::List<Roads...>>::type type;
    };
    template<typename City>
    struct GetRoadsFromCity_Impl<City,TypeList::List<>>{
        typedef TypeList::List<> type;
        // typedef typename GetRoadsFromCity<
    };

    template<typename City,typename Graph>
    struct GetRoadsFromCity{
        typedef typename GetRoadsFromCity_Impl<City,typename Graph::roads>::type type;
    };

}