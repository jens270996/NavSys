#pragma once
#include<type_traits>

//inspired by https://www.codeproject.com/Articles/1077852/TypeLists-and-a-TypeList-Toolbox-via-Variadic-Temp
namespace TypeList{
    template <typename... Ts>
    struct List
    {
        static const size_t size = sizeof...(Ts);
    };

    template <typename... Ts, typename... Us>
    static constexpr auto operator+ (List<Ts...>,List<Us...>){return List<Ts...,Us...>{};}
    template <typename... Ts,typename T>
    static constexpr auto operator+ (List<Ts...>,T){return List<Ts...>{}+List<T>{};}

    //base templates
    template<typename... Ts, typename T>
    static constexpr bool contains(List<Ts...>,T);


    //specializations
    template<typename... Ts, typename T, typename U>
    static constexpr bool contains(List<T,Ts...>,U){
        //if T and U are the same, the list contains U, otherwise recursively call contains without front element in list.
        return std::conditional<std::is_same<T,U>::value,std::false_type,std::integral_constant<bool,contains(List<Ts...>{},U{})>>::type::value;
    }
    template<typename T>
    static constexpr bool contains(List<>,T){
        //reached end of list.
        return false;
    }
    template <typename T,typename... Ts>
    static constexpr auto unique(List<T,Ts...>){
        return std::conditional<contains(List<Ts...>{},T{})
            ,decltype(unique(List<Ts...>{}))
            ,decltype(T{}+unique(List<Ts...>{}))>{};
    }
    template <typename T>
    static constexpr auto unique(List<T>){
        return List<T>{};
    }



}