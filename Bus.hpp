#pragma once
#include <vector>
#include "RoadMap.hpp"
#include "PathFinding.hpp"
#include "List.hpp"
#include "BusUpdateCenter.hpp"
#include <functional>
using namespace map_updater;
template<typename... ROUTE_POINTS>
class Bus{
    typedef typename Map::FindPaths<Map::RoadMap::MapGraph,ROUTE_POINTS...>::type path;
public:
    Bus(BusUpdateCenter& update_center):_busstop_functor(*this){

        _path_vector = Map::PathFunctions<path>::getRoadIdVector();

        update_center.connect(std::bind(&Bus::handleUpdate,this,std::placeholders::_1)
                            ,std::bind(&Bus::handleExpire
                            ,this,std::placeholders::_1),_path_vector);
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
    void handleUpdate(const Update& update){
        _updates.push_back(std::move(update));
        std::cout<<_updates.back().getMessage()<<std::endl;
    }
    void handleExpire(const UpdateExpiration& update){
        //find matching id and remove
        std::cout<<"Update with id expired: "<<update.road_id<<std::endl;
        for(auto it=_updates.begin();it!=_updates.end();it++){
            if(it->getUpdateId()==update.update_id){
                std::cout<<"Removing"<<std::endl;
                _updates.erase(it);
                break;
            }
        }
    }
    std::list<Update> _updates;
    std::vector<size_t> _path_vector;
    std::vector<int> _route_points;
};