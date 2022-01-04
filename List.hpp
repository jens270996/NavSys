#pragma once
#include<type_traits>
namespace BusRouter{
namespace Map{
namespace TL{
    struct Invalid_Type{};

    //Primary empty template class
    template <typename... Ts>
    struct List{};
    //Partial for list with items
    template <typename T,typename... Ts>
    struct List<T,Ts...>
    {
        static const size_t size = sizeof...(Ts)+1;
        typedef std::conditional_t<size==1,T,typename List<Ts...>::last> last;
        typedef T first;
        typedef List<Ts...> rest;
    };
    //Fully for empty list
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

    template< typename T,typename U >
    using List_Concatenate_t = typename List_Concatenate<T,U>::type;

    //base template
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

    template< typename T, typename U, typename V = void >
    using List_Contains_t = typename List_Contains<T,U,V>::type;

    template< typename T, typename U, typename V = void >
    inline constexpr bool List_Contains_v = List_Contains<T,U,V>::type::value;

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
}
}