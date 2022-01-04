#pragma once
#include <vector>
#include "RoadMap.hpp"
#include "PathFinding.hpp"
#include "List.hpp"
#include "BusUpdateCenter.hpp"
#include <functional>
namespace BusRouter{
    using namespace BusUpdate;
    using namespace Map;
    template<typename... ROUTE_POINTS>
    class Bus{
        //Path found through cities passed as template parameters
        typedef typename Map::FindPaths<Map::RoadMap::MapGraph,ROUTE_POINTS...>::type path;
    public:
        Bus(BusUpdateCenter& update_center, std::string name):_busStopFunctor(*this),_name(name){
            //save ids from roads in path, in vector.
            _path_vector = Map::PathFunctions<path>::getRoadIdVector();

            //connect to BusUpdateCenter on slots for road ids in path.
            update_center.connect(std::bind(&Bus::handleUpdate,this,std::placeholders::_1)
                                ,std::bind(&Bus::handleExpire
                                ,this,std::placeholders::_1),_path_vector);
            //Get city ids:
            TL::ListFunctions<TL::List<ROUTE_POINTS...>>::ForEach(_busStopFunctor);
            printPath();
        }
        //Prints path for bus.
        void printPath(){ 
            std::cout<<std::endl<<"===================================================================================="<<std::endl;
            std::cout<<"Bus route for bus with name: "<<_name<<std::endl;
            Map::PathFunctions<path>::PrintFull();

            std::cout<<"Stops in cities with postal codes:"<<std::endl;
            for(auto city : _route_points){std::cout<<city<<std::endl;}
            std::cout<<"===================================================================================="<<std::endl<<std::endl;
        }
        //returns road-ids on path
        std::vector<size_t> getPath() { return _path_vector; }
        //returns postal codes for cities on path
        std::vector<int>    getStops(){ return _route_points;}
    private:
        //Functor to extract all cities the bus visits.
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

        //Prints the total delay on the route
        void printDelay(int road_number)const{
            typedef std::remove_const_t<std::remove_reference_t<decltype(_updates.front())>> DecltypeShowOff;
            std::cout<<std::endl<<"===================================================================================="<<std::endl;
            std::cout<<"Bus route: "<<_name<<" received update for road with id: "<<road_number<<std::endl;
            std::cout<<"Total delay is now: "<<std::accumulate(_updates.begin(),_updates.end(),AccumulationTraits<DecltypeShowOff>::zero(),AccumulationTraits<DecltypeShowOff>{})<<std::endl;
            std::cout<<"===================================================================================="<<std::endl;
        }
        //Handles a new update
        void handleUpdate(const Update& update){
            _updates.push_back(std::move(update));
            printDelay(update.getRoadId());
        }
        //handles an expired update
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
}