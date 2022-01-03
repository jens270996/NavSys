#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <list>
#include <tuple>
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
            RoadInformation(){

            }
            RoadInformation(double traversalTimeImpact, bool isPassable){
                _traversalTimeImpact = traversalTimeImpact;
                _isPassable = isPassable;
            }
            RoadInformation(double traversalTimeImpact){
                _traversalTimeImpact = traversalTimeImpact;
            }
            double getTraversalTimeImpact(){
                return _traversalTimeImpact;
            }
            bool getIsPassable(){
                return _isPassable;
            }
            std::string getMessage(){
                return _message;
            }
        private:
            double _traversalTimeImpact;
            bool _isPassable;
            std::string _message;

    }; 
    class Update{
        public:
            Update(){
            }
            Update(int roadId, RoadInformation* roadInformation){
                _roadId = _roadId;
                _roadInformation = roadInformation;
            }
            double getTraversalTimeImpact(){
                return _roadInformation->getTraversalTimeImpact();
            }
            bool getIsPassable(){
                return _roadInformation->getIsPassable();
            }
            std::string getMessage(){
                return _roadInformation->getMessage();
            }
            int getRoadId(){
                return _roadId;
            }
        private:
            int _roadId;
            RoadInformation* _roadInformation;
    };
class MapUpdater 
{
    typedef boost::signals2::signal<void(Update)> _signal;

    public:
    MapUpdater(){
    }

    boost::signals2::connection connect(const _signal::slot_type &subscriber)
    {
        return m_sig.connect(subscriber);
    }
    
    void UpdateSignal( Update& update){
        m_sig(update);
    }

    private:
    _signal m_sig;
}; 


class BusUpdateCenter{
    public:
        typedef boost::signals2::signal<void(Update)> _signal;
        BusUpdateCenter(MapUpdater &mapUpdater)
        {
            m_sig = std::make_shared<std::array <_signal, 1000>>();
            mapUpdater.connect(boost::bind(&map_updater::BusUpdateCenter::UpdateSignals, this, boost::placeholders::_1));
        }
        // BusUpdateCenter(const BusUpdateCenter& busUpdateCenter){
        //     this->m_sig = m_sig;


        // }
        void connect(const _signal::slot_type &subscriber, std::list<int> roadId)
        {
            auto tuple = std::make_tuple(subscriber, roadId);
            for(int id : roadId){

                (*m_sig)[id].connect(subscriber);
            }

        }
        void UpdateSignals(Update& update){
            (*m_sig)[update.getRoadId()](update);
        }
        
    private:
        std::shared_ptr<std::array <_signal, 1000>> m_sig;

    }; 
    class TestObject{
        public:
            TestObject(BusUpdateCenter& busUpdateCenter)
            :_busUpdateCenter(busUpdateCenter)
            {
            }
                BusUpdateCenter& _busUpdateCenter;
            void TheFunction(){
                    std::cout << "Hello from the function" << std::endl;


            }
    };
}