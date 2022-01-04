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

    class BusUpdateCenter{
        public:
            typedef boost::signals2::signal<void(const Update&)> _signal;
            typedef boost::signals2::signal<void(UpdateExpiration&)> _removal_signal;
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
            void connect(const _signal::slot_type &subscriber, const _removal_signal::slot_type &exp_subscriber,std::vector<size_t> roadId)
            {
                std::for_each(roadId.begin(),roadId.end(),[&](size_t id){
                    m_sig[id].connect(subscriber);
                    exp_sig[id].connect(exp_subscriber);
                });
            }
            void UpdateSignals(Update&& update){
                m_sig[update.getRoadId()](update);
            }
            void UpdateSignals(UpdateExpiration&& update){
                exp_sig[update.road_id](update);
            }
            
        private:
            std::array <_signal, NO_OF_ROADS> m_sig;
            std::array <_removal_signal, NO_OF_ROADS> exp_sig;
        }; 
}
}