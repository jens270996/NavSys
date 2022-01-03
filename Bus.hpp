#pragma once
#include <vector>
#include "RoadMap.hpp"
#include "PathFinding.hpp"
#include "List.hpp"

template<typename... ROUTE_POINTS>
class Bus{
    typedef typename Map::FindPaths<Map::RoadMap::MapGraph,ROUTE_POINTS...>::type path;
public:
    Bus():_busstop_functor(*this){
        _path_vector = Map::PathFunctions<path>::getRoadIdVector();
        //get city ids:
        TL::ListFunctions<TL::List<ROUTE_POINTS...>>::ForEach(_busstop_functor);
    } //also BusUpdateCenter, to connect to slots
    void printPath(){ Map::PathFunctions<path>::PrintFull();}
    std::vector<size_t> getPath() { return _path_vector; }
    std::vector<int>    getStops(){ return _route_points;}
private:
    struct BusstopsFunctor{
        BusstopsFunctor(Bus& parent):_parent(parent){
        }
        template<typename T>
        void operator() (T t){
            _parent._route_points.push_back(t.id);
        }
        private:
        Bus& _parent;
    } _busstop_functor;
    // void handleUpdate(Update update){
    //     typedef typename Map::FindPath<ROUTE_POINTS...,MapGraph>::type path;
    //     _path_vector = Map::PathFunctions<path>::getRoadIdVector();
    // }
    std::vector<size_t> _path_vector;
    std::vector<int> _route_points;
};