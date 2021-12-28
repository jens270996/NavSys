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
        template<typename T>
        static constexpr auto getRoadsFromCity(T city){
            return getRoadsFromCity(city,TypeList::List<TRoads>{});
        }
    private:
        //First road in roads springs out from city
        template<typename T,typename Road1To,int Road1Weight,int Road1Cost,typename... Roads>
        static constexpr auto getRoadsFromCity(T city, TypeList::List<Road<T,Road1To,Road1Weight,Road1Cost>,Roads...> roads){
            return Road<T,Road1To,Road1Weight,Road1Cost>{}+getRoadsFromCity(city,TypeList::List<Roads...>{});
        }
        //First road in roads doesn't spring out from city
        template<typename T,typename Road1From,typename Road1To,int Road1Weight,int Road1Cost,typename... Roads>
        static constexpr auto getRoadsFromCity(T city, TypeList::List<Road<Road1From,Road1To,Road1Weight,Road1Cost>,Roads...> roads){
            return getRoadsFromCity(city,TypeList::List<Roads...>{});
        }
        //Base case
        template<typename T>
        static constexpr auto getRoadsFromCity(T city, TypeList::List<> roads){
            return TypeList::List<>{};
        }
    };
    template<typename City, typename Roads>
    struct GetRoadsFromCity_Impl{
        // typedef typename GetRoadsFromCity<
    };
    template<typename City,typename Road1To,int Road1Weight,int Road1Cost,typename... Roads>
    struct GetRoadsFromCity_Impl<City,TypeList::List<Road<City,Road1To,Road1Weight,Road1Cost>,Roads...>{
        typedef typename GetRoadsFromCity<
    }

    template<typename City,typename Graph>
    struct GetRoadsFromCity{
        typedef typename GetRoadsFromCity_Impl<City,Graph::roads>::type type;
    };

}