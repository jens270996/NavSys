#pragma once
#include "Path.hpp"
#include "Map.hpp"
#include "List.hpp"
namespace Map{

    template<typename FROM, typename TO,typename GRAPH, typename ROADS, typename PATHS, typename TOGGLE = void>
    struct FindPath_Impl{};

    //To and from are the same = target reached
    template<typename FROM,typename GRAPH, typename... ROADS, typename... PATHS>
    struct FindPath_Impl<FROM,FROM,GRAPH,TypeList::List<ROADS...>,TypeList::List<PATHS...>>{
        typedef Path<PATHS...> type;
    };

    //All edges have been tried unsuccessfully
    template<typename FROM,typename TO,typename GRAPH, typename... PATHS>
    struct FindPath_Impl<FROM,TO,GRAPH,TypeList::List<>,TypeList::List<PATHS...>>{
        typedef Path<TypeList::Invalid_Type> type;
    };
    //To and from are different
    template<typename FROM,typename TO,typename GRAPH,typename ROAD, typename... ROADS, typename... PATHS>
    struct FindPath_Impl<FROM,TO,GRAPH,TypeList::List<ROAD,ROADS...>,TypeList::List<PATHS...>,typename std::enable_if_t<!std::is_same<FROM,TO>::value>>{
        //Road goes back to previously visited City.
        typedef typename std::conditional<TypeList::List_Contains<typename ROAD::to, typename TypeList::List_Concatenate<FROM,TypeList::List<PATHS...>>::type>::type::value,
        typename FindPath_Impl<FROM,TO,GRAPH,TypeList::List<ROADS...>,TypeList::List<PATHS...>>::type,
        typename Path_Comparer<typename FindPath_Impl<typename ROAD::to,TO,GRAPH,typename GetRoadsFromCity<typename ROAD::to,GRAPH>::type,TypeList::List<PATHS...,ROAD>>::type, //add road to path, and advance to next city
                                typename FindPath_Impl<FROM,TO,GRAPH,TypeList::List<ROADS...>,TypeList::List<PATHS...>>::type> // skip current road and try next.
                                ::shortest>
        ::type type;
    };

    template<typename FROM, typename TO,typename GRAPH>
    struct FindPath{
        // std::enable_if_t<(TypeList::List_Contains<FROM,typename GRAPH::cities>::type::value && TypeList::List_Contains<TO,typename GRAPH::cities>::type::value)>
        typedef typename FindPath_Impl<FROM,TO,GRAPH,typename GetRoadsFromCity<FROM,GRAPH>::type,TypeList::List<>>::type type;
    };
}