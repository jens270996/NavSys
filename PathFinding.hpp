#pragma once
#include "Path.hpp"
#include "Map.hpp"
#include "List.hpp"
namespace BusRouter{
namespace Map{

    //Empty primary
    template<typename FROM, typename TO,typename GRAPH, typename ROADS, typename PATHS, typename TOGGLE = void>
    struct FindPath_Impl{};

    //To and from are the same = target reached
    template<typename FROM,typename GRAPH, typename... ROADS, typename... PATHS>
    struct FindPath_Impl<FROM,FROM,GRAPH,TL::List<ROADS...>,TL::List<PATHS...>>{
        typedef Path<PATHS...> type;
    };

    //All edges have been tried unsuccessfully
    template<typename FROM,typename TO,typename GRAPH, typename... PATHS>
    struct FindPath_Impl<FROM,TO,GRAPH,TL::List<>,TL::List<PATHS...>>{
        typedef Path<TL::Invalid_Type> type;
    };
    //To and from are different & Next city is not in path
    template<typename FROM,typename TO,typename GRAPH,typename ROAD, typename... ROADS, typename... PATHS>
    struct FindPath_Impl<FROM,TO,GRAPH,TL::List<ROAD,ROADS...>,TL::List<PATHS...>,
    //!is_same<FROM,TO> is required since equally specialized as target reached.
    std::enable_if_t<!std::is_same<FROM,TO>::value && !TL::List_Contains_v<typename ROAD::to, typename Path<PATHS...>::cities>>
    >{
        //helper defs - should go?
        typedef typename ROAD::to NextCity;
        typedef typename GetRoadsFromCity<NextCity,GRAPH>::type RoadsFromNextCity;
        typedef typename FindPath_Impl<FROM,TO,GRAPH,TL::List<ROADS...>,TL::List<PATHS...>>::type PathWithoutNextRoad;
        //can only be evaluated if path doesn't contain dest for road. otherwise inf loop
        typedef typename FindPath_Impl<NextCity,TO,GRAPH,RoadsFromNextCity, TL::List<PATHS...,ROAD>>::type PathWithNextRoad;

        //Pick shortest path
        typedef typename Path_Comparer<PathWithNextRoad, //add road to path, and advance to next city
                                PathWithoutNextRoad> // skip current road and try next road.
                                ::shortest type;
    };

    //To and from are different & Next city is in path
    template<typename FROM,typename TO,typename GRAPH,typename ROAD, typename... ROADS, typename... PATHS>
    struct FindPath_Impl<FROM,TO,GRAPH,TL::List<ROAD,ROADS...>,TL::List<PATHS...>,
    std::enable_if_t<!std::is_same<FROM,TO>::value && TL::List_Contains_v<typename ROAD::to, typename Path<PATHS...>::cities>>
    >{
        //If next city is already in path, skip to avoid infinite loops.
        typedef typename FindPath_Impl<FROM,TO,GRAPH,TL::List<ROADS...>,TL::List<PATHS...>>::type type;
    };

    template<typename FROM, typename TO,typename GRAPH>
    struct FindPath{
        //Only run algorithm if both FROM and TO are in GRAPH. 
        // std::enable_if_t<(TL::List_Contains<FROM,typename GRAPH::cities>::type::value && TL::List_Contains<TO,typename GRAPH::cities>::type::value)>
        typedef typename FindPath_Impl<FROM,TO,GRAPH,typename GetRoadsFromCity<FROM,GRAPH>::type,TL::List<>>::type type;
    };
    
    //Find path with multiple stops.
    template<typename GRAPH, typename... Points>
    struct FindPaths{
        typedef Path<> type;
    };

    template<typename GRAPH,typename FROM, typename TO,typename... Ts>
    struct FindPaths<GRAPH,FROM,TO,Ts...>{
        typedef Path_Impl<typename TL::List_Concatenate<
        typename FindPath<FROM,TO,GRAPH>::type::list
        ,typename FindPaths<GRAPH,TO,Ts...>::type::list>::type > type;
    };
}
}