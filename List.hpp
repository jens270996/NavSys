#pragma once
#include<type_traits>

//inspired by https://www.codeproject.com/Articles/1077852/TypeLists-and-a-TypeList-Toolbox-via-Variadic-Temp

namespace TL{

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

    template <typename... Ts>
    struct List{};

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
        typedef List<> rest;
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
    //List and empty list
    template<typename... Ts>
    struct List_Concatenate<List<Ts...>,List<>>{
        typedef List<Ts...> type;
    };
    //List and type
    template<typename... Ts,typename U>
    struct List_Concatenate<List<Ts...>,U>{
        typedef List<Ts...,U> type;
    };

    //base templates
    template<typename T, typename U, typename = void>
    struct List_Contains{};

    template<typename T, typename U, typename... Ts>
    struct List_Contains<T,List<U,Ts...>, std::enable_if_t<!std::is_same<T,U>::value>>
    {
        typedef  typename List_Contains<T,List<Ts...>>::type type;
    };
    template<typename T, typename... Ts>
    struct List_Contains<T,List<T,Ts...>>
    {
        typedef std::true_type type;
    };
    template<typename T>
    struct List_Contains<T,List<>>
    {
        typedef std::false_type type;
    };

    template<typename T>
    struct ListFunctions{};

    template<typename T,typename... Ts>
    struct ListFunctions<List<T,Ts...>>
    {
        template<typename Functor>
        static constexpr void ForEach(Functor functor){
            functor(T{});
            ListFunctions<List<Ts...>>::ForEach(functor);
        }
    };

    template<>
    struct ListFunctions<List<>>
    {
        template<typename Functor>
        static constexpr void ForEach(Functor functor){
            return;
        }
    };

}