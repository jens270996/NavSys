#pragma once
#include "List.hpp"
#include "Map.hpp"
namespace Map{
    template<typename T, typename U = void>
    struct Path_Impl{};
    template<typename T>
    struct Path_Impl<T,std::enable_if_t<(T::size>1)>>{
        typedef typename T::first::from from;
        typedef typename T::last::to to;
        //Start of each road + 
        typedef typename TL::List_Concatenate<from, typename Path_Impl<typename T::rest>::cities>::type cities;
        static const int cost = T::first::cost + Path_Impl<typename T::rest>::cost;
        static const int weight = T::first::weight + Path_Impl<typename T::rest>::weight;
    };

    template<typename T, typename U>
    struct Path_Comparer{
        typedef std::conditional_t<T::weight<=U::weight,T,U> shortest;
    };

    //Path with single road
    template<typename T>
    struct Path_Impl<T,std::enable_if_t<T::size==1>>{
        typedef typename T::first::from from;
        typedef typename T::last::to to;
        typedef TL::List<from,to> cities;
        static const int cost = T::first::cost;
        static const int weight= T::first::weight;
    };


    //Empty Path
    template<typename T>
    struct Path_Impl<T,std::enable_if_t<T::size==0>>{
        typedef TL::List<> cities;
        static const int cost = 0;
        static const int weight=0;
    };

    //Invalid Path
    template<>
    struct Path_Impl<TL::List<TL::Invalid_Type>>{
        typedef TL::List<TL::Invalid_Type> cities;
        static const int cost = INT32_MAX;
        static const int weight=INT32_MAX;
    };




    template<typename... Ts>
    using Path = Path_Impl<TL::List<Ts...>>; //Path is a list of roads in the order they should be transversed.
}