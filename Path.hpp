#pragma once
#include "List.hpp"
#include "City.hpp"
namespace Map{
template<typename T, typename U = void>
struct Path_Impl{};
template<typename T>
struct Path_Impl<T,std::enable_if_t<T::size!=0>>{
    typedef typename T::first::from from;
    typedef typename T::last::to to;
    static const int cost = T::first::cost + Path_Impl<typename T::rest>::cost;
    static const int weight = T::first::weight + Path_Impl<typename T::rest>::weight;
};

template<typename T, typename U>
struct Path_Comparer{
    typedef typename std::conditional_t<T::weight<=U::weight,T,U> shortest;
};

//Empty Path
template<typename T>
struct Path_Impl<T,std::enable_if_t<T::size==0>>{
    static const int cost = 0;
    static const int weight=0;
};




template<typename... Ts>
using Path = Path_Impl<TypeList::List<Ts...>>; //Path is a list of roads in the order they should be transversed.
}