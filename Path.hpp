#pragma once
#include "List.hpp"
#include "Map.hpp"
#include <array>
#include <vector>
namespace BusRouter{
namespace Map{
    template<typename T, typename U = void>
    struct Path_Impl{};
    template<typename T>
    struct Path_Impl<T,std::enable_if_t<(T::size>1)>>{
        typedef T list;
        static const size_t size = T::size;
        typedef typename T::first::from from;
        typedef typename T::last::to to;
        //Start of first road +  cities in path with rest.
        typedef typename TL::List_Concatenate_t<from, typename Path_Impl<typename T::rest>::cities> cities;
        static const int cost = T::first::cost + Path_Impl<typename T::rest>::cost;
        static const int weight = T::first::weight + Path_Impl<typename T::rest>::weight;
    };

    //Path with single road
    template<typename T>
    struct Path_Impl<T,std::enable_if_t<T::size==1>>{
        typedef T list;
        static const size_t size = T::size;
        typedef typename T::first::from from;
        typedef typename T::last::to to;
        //From and to for last road. Since a path goes through number of roads +1 cities.
        typedef TL::List<from,to> cities;
        static const int cost = T::first::cost;
        static const int weight= T::first::weight;
    };

    //Empty Path
    template<typename T>
    struct Path_Impl<T,std::enable_if_t<T::size==0>>{
        typedef T list;
        static const size_t size = T::size;
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

    template<typename T, typename U>
    struct Path_Comparer{
        typedef std::conditional_t<T::weight<=U::weight,T,U> shortest;
    };
    
    //Empty primary
    template<typename T>
    struct PathFunctions{};

    //Non empty path - partial specialization
    template<typename T,typename... Ts>
    struct PathFunctions<Path_Impl<TL::List<T,Ts...>>>{
        //Functor must take a road id (size_t), cost (int) and weight(int) as argument.
        template<typename Functor>
        static constexpr void ForEachRoad(Functor functor){

            functor(T::id,T::cost,T::weight);
            PathFunctions<Path_Impl<TL::List<Ts...>>>::ForEachRoad(functor);
        }
        //Uses ForEachRoad to extract road ids in a vector.
        static std::vector<size_t> getRoadIdVector(){
            std::vector<size_t> vector;
            ForEachRoad([&vector](size_t id, int cost, int weight){
                vector.push_back(id);
            });
            return vector;
        }

        static void PrintFull(){
            std::cout<<"Path goes from: "<<Path<T,Ts...>::from::id<<std::endl;
            std::cout<<"Path goes to: "<<Path<T,Ts...>::to::id<<std::endl;
            std::cout<<"With a total length of: "<<Path<T,Ts...>::weight<<std::endl;
            std::cout<<"And a total cost of: "<<Path<T,Ts...>::cost<<std::endl;
            std::cout<<"Consists of roads:"<<std::endl;
            ForEachRoad([](size_t id, int cost, int weight){
                std::cout<<"Road with ID:"<<id<<" cost: "<<cost<<" weight: "<<weight<<std::endl;
            });
        }
    };
    //Empty path full-specialization
    template<>
    struct PathFunctions<Path_Impl<TL::List<>>>{
        static void PrintFull(){
            std::cout<<"Empty Path..."<<std::endl;
        }
        //base case for ForEachRoad func
        template<typename Functor>
        static void ForEachRoad(Functor functor){
            return;
        }
    };
}
}