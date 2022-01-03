#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <list>
#include <deque>
#include <random>
#include <thread>
#include <mutex>
using namespace boost::placeholders;
//template <class T>
namespace map_updater{

    class RoadInformation{
        public:
            RoadInformation(double traversalTimeImpact, bool isPassable, std::string message)
            {
                _traversalTimeImpact = traversalTimeImpact;
                _isPassable = isPassable;
                _message = message;
            }
            double getTraversalTimeImpact()const{
                return _traversalTimeImpact;
            }
            bool getIsPassable()const{
                return _isPassable;
            }
            std::string getMessage()const{
                return _message;
            }
        private:
            double _traversalTimeImpact;
            bool _isPassable;
            std::string _message;

    };
    struct UpdateExpiration{
        UpdateExpiration(int updateId,int roadId):update_id{updateId},road_id{roadId}{}
        const int update_id;
        const int road_id;
    };
    class Update{
        public:
            Update(int updateId, int roadId, RoadInformation* roadInformation):_updateId{updateId},_roadInformation(roadInformation){
                _roadId = roadId;
            }
            Update(Update&& update) noexcept
            :_updateId{std::move(update._updateId)},_roadId{std::move(update._roadId)},_roadInformation{update._roadInformation}{
            };
            Update(const Update& update):_updateId{update._updateId},_roadId{update._roadId},_roadInformation{new RoadInformation(*(update._roadInformation))}{
            };
            Update& operator=(const Update& update) = delete;
            Update& operator=(Update&& update) = delete ;
            ~Update(){
                delete _roadInformation;
            };
            double getTraversalTimeImpact()const{
                try{
                   return _roadInformation->getTraversalTimeImpact();
                }
                catch(...){
                    std::cout << "Exception thrown in getTraversalTimeImpact" << std::endl;
                }
            }
            bool getIsPassable() const{
                try{   
                    return _roadInformation->getIsPassable();
                }
                catch(...){
                    std::cout << "Exception thrown in getIsPassable" << std::endl;
                }
            }
            std::string getMessage() const{
                try{
                    return _roadInformation->getMessage();
                }
                catch(...){
                    std::cout << "Exception thrown in getMessage" << std::endl;
                }
            }
            int getRoadId()const{
                return _roadId;
            }
            int getUpdateId()const{
                return _updateId;
            }
        private:
        const int _updateId;
        int _roadId;
        RoadInformation* _roadInformation;
    };
class MapUpdater 
{
    typedef boost::signals2::signal<void(Update&)> _signal;
    typedef boost::signals2::signal<void(UpdateExpiration&)> _removal_signal;

    public:
    MapUpdater():update_id{0}{
    }
    ~MapUpdater(){
        run=false;
        if(update_thread.joinable())
            update_thread.join();
    }
    void startUpdateGeneration(){

        run=true;
        update_thread=std::thread([&](){
            std::default_random_engine rand_gen;
            std::uniform_int_distribution<int> road_id_generator(0,NO_OF_ROADS-1);
            std::normal_distribution<float> delay_generator(20,10);
            std::bernoulli_distribution blocked_generator(0.1);
            std::string msg = "Default msg.";
            std::uniform_int_distribution<int> sleep_generator(1,15);
            std::bernoulli_distribution add_or_remove_generator(0.5);
            while(run){
                std::this_thread::sleep_for (std::chrono::seconds(sleep_generator(rand_gen)));
                if(add_or_remove_generator(rand_gen)){
                    //generate update
                    int road_id = road_id_generator(rand_gen);
                    UpdateSignal(Update(update_id,road_id
                                ,new RoadInformation((int)delay_generator(rand_gen),blocked_generator(rand_gen),msg)));
                    update_deque.push_front(std::pair<unsigned,int>(update_id++,road_id));
                }
                else if(update_deque.size()>0){
                    std::cout<<"Hi from remove"<<std::endl;
                    //remove update
                    std::uniform_int_distribution<int> removal_id_generator(0,update_deque.size()-1);
                    std::cout<<"Hi from remove"<<std::endl;
                    std::deque<std::pair<unsigned,int>>::iterator it=update_deque.begin()+removal_id_generator(rand_gen);
                    std::cout<<"Hi from remove"<<std::endl;
                    ExpireSignal(UpdateExpiration(it->first,it->second));
                    std::cout<<"Hi from remove"<<std::endl;
                }
            }
        });
    };

    void connect(const _signal::slot_type &subscriber,const _removal_signal::slot_type &removal_subscriber)
    {
        exp_sig.connect(removal_subscriber);
        m_sig.connect(subscriber);
    }
    private:
    void UpdateSignal( Update&& update){
        std::cout<<"Update on road:"<<update.getRoadId()<<std::endl;
        m_sig(update);
    }
    void ExpireSignal( UpdateExpiration&& update){
        std::cout<<"Update expiration on road:"<<update.road_id<<std::endl;
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
                std::cout<<"Connecting on index:"<<id<<std::endl;
                m_sig[id].connect(subscriber);
                exp_sig[id].connect(exp_subscriber);
            });
        }
        void UpdateSignals(Update&& update){
            std::cout<<"Updating on index:"<<update.getRoadId()<<std::endl;
            m_sig[update.getRoadId()](update);
        }
        void UpdateSignals(UpdateExpiration&& update){
            std::cout<<"Updating on index:"<<update.road_id<<std::endl;
            exp_sig[update.road_id](update);
        }
        
    private:
        std::array <_signal, NO_OF_ROADS> m_sig;
        std::array <_removal_signal, NO_OF_ROADS> exp_sig;
    }; 
}