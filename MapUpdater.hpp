#pragma once
#include<boost/signals2.hpp>
#include <random>
#include <thread>
#include <mutex>
#include <atomic>
#include <deque>
#include "Update.hpp"
#include "RoadMap.hpp"
namespace BusRouter{
namespace BusUpdate{

    // It is the signal to the class BusUpdateCenter. 
    // It delegates all information about incoming roadInformation to the slots who are connected 
    class MapUpdater 
    {
        typedef boost::signals2::signal<void(Update&)> _signal;
        typedef boost::signals2::signal<void(UpdateExpiration&)> _removal_signal;

        public:
        MapUpdater():update_id{0}{
        }
        // Destructor waits to all threads are done with execution
        ~MapUpdater(){
            run=false;
            if(update_thread.joinable())
                update_thread.join();
        }

        //It is the method who Generate randomised roadInformation
        void startUpdateGeneration(){

            run=true;
            update_thread=std::thread([&](){
                std::default_random_engine rand_gen;
                std::uniform_int_distribution<int> road_id_generator(0,NO_OF_ROADS-1);
                std::uniform_int_distribution<int> delay_generator(5,50);
                std::bernoulli_distribution blocked_generator(0.1);
                std::string msg = "Default msg.";
                std::uniform_int_distribution<int> sleep_generator(1,2);
                std::bernoulli_distribution add_or_remove_generator(0.5);
                while(run){
                    std::this_thread::sleep_for (std::chrono::seconds(sleep_generator(rand_gen)));
                    if(add_or_remove_generator(rand_gen)){
                        //generate update
                        int road_id = road_id_generator(rand_gen);
                        UpdateSignal(Update(update_id,road_id,RoadInformation((int)delay_generator(rand_gen),blocked_generator(rand_gen),msg)));
                        update_deque.push_front(std::pair<unsigned,int>(update_id++,road_id));
                    }
                    else if(update_deque.size()>0){
                        //remove update
                        std::uniform_int_distribution<int> removal_id_generator(0,update_deque.size()-1);
                        std::deque<std::pair<unsigned,int>>::iterator it=update_deque.begin()+removal_id_generator(rand_gen);
                        ExpireSignal(UpdateExpiration(it->first,it->second));
                    }
                }
            });
        };
        // Connect the subscribers to the MapUpdaters signals
        void connect(const _signal::slot_type &subscriber,const _removal_signal::slot_type &removal_subscriber)
        {
            exp_sig.connect(removal_subscriber);
            m_sig.connect(subscriber);
        }
        private:
        // Performing the signal 
        void UpdateSignal( Update&& update){
            m_sig(update);
        }
        // Performing the signal
        void ExpireSignal( UpdateExpiration&& update){
            exp_sig(update);
        }
        std::thread update_thread;
        std::atomic_bool run;
        std::mutex mut;
        _removal_signal exp_sig;
        _signal m_sig;
        unsigned update_id;
        std::deque<std::pair<unsigned,int>> update_deque;
    };
}
}