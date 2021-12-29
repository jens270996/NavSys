#pragma once
#include "Path.hpp"
#include "Map.hpp"
#include "List.hpp"
namespace Map{

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
    std::enable_if_t<!std::is_same<FROM,TO>::value && !TL::List_Contains<typename ROAD::to, typename Path<PATHS...>::cities>::type::value>
    >{
        //helper defs - should go?
        typedef typename ROAD::to NextCity;
        typedef typename GetRoadsFromCity<NextCity,GRAPH>::type RoadsFromNextCity;
        typedef typename FindPath_Impl<FROM,TO,GRAPH,TL::List<ROADS...>,TL::List<PATHS...>>::type PathWithoutNextRoad;
        typedef typename FindPath_Impl<NextCity,TO,GRAPH,RoadsFromNextCity, TL::List<PATHS...,ROAD>>::type PathWithNextRoad; //må kun evalueres hvis path ikke indeholder dest for road. ellers inf loop
        //Road goes back to previously visited City.
        typedef typename Path_Comparer<PathWithNextRoad, //add road to path, and advance to next city
                                PathWithoutNextRoad> // skip current road and try next.
                                ::shortest type;
    };
    //To and from are different & Next city is in path
    template<typename FROM,typename TO,typename GRAPH,typename ROAD, typename... ROADS, typename... PATHS>
    struct FindPath_Impl<FROM,TO,GRAPH,TL::List<ROAD,ROADS...>,TL::List<PATHS...>,
    std::enable_if_t<!std::is_same<FROM,TO>::value && TL::List_Contains<typename ROAD::to, typename Path<PATHS...>::cities>::type::value>
    >{
        //If next city is already in path, skip to avoid infinite loops.
        typedef typename FindPath_Impl<FROM,TO,GRAPH,TL::List<ROADS...>,TL::List<PATHS...>>::type type;
    };

    template<typename FROM, typename TO,typename GRAPH>
    struct FindPath{
        // std::enable_if_t<(TL::List_Contains<FROM,typename GRAPH::cities>::type::value && TL::List_Contains<TO,typename GRAPH::cities>::type::value)>
        typedef typename FindPath_Impl<FROM,TO,GRAPH,typename GetRoadsFromCity<FROM,GRAPH>::type,TL::List<>>::type type;
    };
}