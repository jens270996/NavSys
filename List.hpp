#pragma once
#include<type_traits>

//inspired by https://www.codeproject.com/Articles/1077852/TypeLists-and-a-TypeList-Toolbox-via-Variadic-Temp

namespace TypeList{

    template <typename T,typename... Ts>
    struct List_impl
    {
        typedef T first;
        typedef typename List_impl<Ts...>::last last;
    };
template <typename T>
    struct List_impl<T>
    {
        typedef T first;
        typedef T last;
    };
    struct Invalid_Type{};

    //should never go here
    template <typename... Ts>
    struct List
    {

    };
    template <typename T,typename... Ts>
    struct List<T,Ts...>
    {
        static const size_t size = sizeof...(Ts)+1;
        typedef typename List_impl<T,Ts...>::last last;
        typedef typename List_impl<T,Ts...>::first first;
        typedef List<Ts...> rest;
    };


    template <>
    struct List<>
    {
        static const size_t size = 0;
        typedef Invalid_Type last;
        typedef Invalid_Type first;
        typedef Invalid_Type rest;
    };

    //Type and type (base)
    template<typename T,typename U>
    struct List_Concatenate{
        typedef List<T,U> type;
    };
    //List and list
    template<typename... Ts,typename... Us>
    struct List_Concatenate<List<Ts...>,List<Us...>>{
        typedef List<Ts...,Us...> type;
    };
    //Type and list
    template<typename T,typename... Us>
    struct List_Concatenate<T,List<Us...>>{
        typedef List<T,Us...> type;
    };
    //Type and empty list
    template<typename T>
    struct List_Concatenate<T,List<>>{
        typedef List<T> type;
    };
    //List and type
    template<typename... Ts,typename U>
    struct List_Concatenate<List<Ts...>,U>{
        typedef List<Ts...,U> type;
    };

    //base templates
    template<typename T, typename U>
    struct List_Contains{};

    template<typename T, typename U, typename... Ts>
    struct List_Contains<T,List<U,Ts...>>
    {
        typedef  typename List_Contains<T,List<Ts...>>::type type;
        static const bool value =  List_Contains<T,List<Ts...>>::value;
    };
    template<typename T, typename... Ts>
    struct List_Contains<T,List<T,Ts...>>
    {
        typedef std::true_type type;
        static const bool value =  true;
    };
    template<typename T>
    struct List_Contains<T,List<>>
    {
        typedef std::false_type type;
        static const bool value =  false;
    };

    // template<typename... Ts, typename T>
    // static constexpr bool contains(List<Ts...>,T);


    // //specializations
    // template<typename... Ts, typename T, typename U>
    // static constexpr bool contains(List<T,Ts...>,U){
    //     //if T and U are the same, the list contains U, otherwise recursively call contains without front element in list.
    //     return std::conditional<std::is_same<T,U>::value,std::false_type,std::integral_constant<bool,contains(List<Ts...>{},U{})>>::type::value;
    // }
    // template<typename T>
    // static constexpr bool contains(List<>,T){
    //     //reached end of list.
    //     return false;
    // }
    // template <typename T,typename... Ts>
    // static constexpr auto unique(List<T,Ts...>){
    //     return std::conditional<contains(List<Ts...>{},T{})
    //         ,decltype(unique(List<Ts...>{}))
    //         ,decltype(T{}+unique(List<Ts...>{}))>{};
    // }
    // template <typename T>
    // static constexpr auto unique(List<T>){
    //     return List<T>{};
    // }



}