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
    Bus(BusUpdateCenter& update_center, std::string name):_busStopFunctor(*this),_name(name){

        _path_vector = Map::PathFunctions<path>::getRoadIdVector();

        update_center.connect(std::bind(&Bus::handleUpdate,this,std::placeholders::_1)
                            ,std::bind(&Bus::handleExpire
                            ,this,std::placeholders::_1),_path_vector);
        //get city ids:
        TL::ListFunctions<TL::List<ROUTE_POINTS...>>::ForEach(_busStopFunctor);
        printPath();
    }

    void printPath(){ 
        std::cout<<std::endl<<"===================================================================================="<<std::endl;
        std::cout<<"Bus route for bus with name: "<<_name<<std::endl;
        Map::PathFunctions<path>::PrintFull();
        std::cout<<"===================================================================================="<<std::endl<<std::endl;
    }

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
    } _busStopFunctor;


    void printDelay(int road_number)const{
        typedef std::remove_const_t<std::remove_reference_t<decltype(_updates.front())>> DecltypeShowOff;
        std::cout<<std::endl<<"===================================================================================="<<std::endl;
        std::cout<<"Bus route: "<<_name<<" received update for road with id: "<<road_number<<std::endl;
        std::cout<<"Total delay is now: "<<std::accumulate(_updates.begin(),_updates.end(),AccumulationTraits<DecltypeShowOff>::zero(),AccumulationTraits<DecltypeShowOff>{})<<std::endl;
        std::cout<<"===================================================================================="<<std::endl;
    }

    void handleUpdate(const Update& update){
        _updates.push_back(std::move(update));
        printDelay(update.getRoadId());
    }
    void handleExpire(const UpdateExpiration& update){
        //find matching id and remove
        for(auto it=_updates.begin();it!=_updates.end();it++){
            if(it->getUpdateId()==update.update_id){
                _updates.erase(it);
                break;
            }
        }
        printDelay(update.road_id);

    }
    std::string _name;
    std::list<Update> _updates;
    std::vector<size_t> _path_vector;
    std::vector<int> _route_points;
};