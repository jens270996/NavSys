#pragma once
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <list>
#include "Update.hpp"
#include "MapUpdater.hpp"

//template <class T>
namespace BusRouter{
namespace BusUpdate{
    // It is the class who delegates all the signals out to the bus' and it also acts as a slot to MapUpdater
    class BusUpdateCenter{
        public:
            typedef boost::signals2::signal<void(const Update&)> _signal;
            typedef boost::signals2::signal<void(UpdateExpiration&)> _removal_signal;
            // Constructor using 2 std::function to store 2 lambda expressions. The lambda expression calls BusUpdate->UpdateSignals(std::move(update))
            // std::move is used to make sure it is rvalue reference 
            // Connect to the signal mapUpdater
            BusUpdateCenter(MapUpdater &mapUpdater)
            {
                std::function<void(Update &update)> func([this](Update &update){
                    this->UpdateSignals(std::move(update));
                });
                std::function<void(UpdateExpiration &update)> exp_func([this](UpdateExpiration &update){
                    this->UpdateSignals(std::move(update));
                });
                mapUpdater.connect(func,exp_func);
            }
            // Use STLALgorithms for_each to connect the subscriber and exp_subscriber to each roadId from the vector roadId
            void connect(const _signal::slot_type &subscriber, const _removal_signal::slot_type &exp_subscriber,std::vector<size_t> roadId)
            {
                std::for_each(roadId.begin(),roadId.end(),[&](size_t id){
                    m_sig[id].connect(subscriber);
                    exp_sig[id].connect(exp_subscriber);
                });
            }
            // The method which calls the slots in Bus for updates
            // It gives update as a parameter and the information about update.getRoadId() to the bus' who are connected 
            void UpdateSignals(Update&& update){
                m_sig[update.getRoadId()](update);
            }
            // The method which calls the slots in Bus for updateExpiration
            // It gives updateExpiration as a parameter and the information about update.road_id to the bus' who are connected 
            void UpdateSignals(UpdateExpiration&& update){
                exp_sig[update.road_id](update);
            }
            
        private:
            std::array <_signal, NO_OF_ROADS> m_sig;
            std::array <_removal_signal, NO_OF_ROADS> exp_sig;
        }; 
}
}