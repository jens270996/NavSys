#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <list>
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
    class Update{
        public:
            Update(int roadId, RoadInformation* roadInformation):_roadInformation(roadInformation){
                try{
                    size_t tmp = roadId;
                    _roadId = tmp;

                }
                catch(std::exception& e){
                    std::cout << "Pointer exception thrown in Update constructor" << e.what() << std::endl;
                    throw;
                }
                catch(...){

                    std::cout << "Unknown Exception thrown in Update constructor" << std::endl;
                }
            }
            Update(const Update& update)=delete;
            Update& operator=(const Update& update) = delete;
            Update(Update&& update) = delete;
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
        private:
            int _roadId;
            RoadInformation* _roadInformation;
    };
class MapUpdater 
{
    typedef boost::signals2::signal<void(Update&)> _signal;

    public:
    MapUpdater(){
    }

    boost::signals2::connection connect(const _signal::slot_type &subscriber)
    {
        return m_sig.connect(subscriber);
    }
    void UpdateSignal( Update&& update){
        std::cout<<"Update on road:"<<update.getRoadId()<<std::endl;
        m_sig(update);
    }

    private:
    _signal m_sig;
}; 


class BusUpdateCenter{
    public:
        typedef boost::signals2::signal<void(const Update&)> _signal;
        BusUpdateCenter(MapUpdater &mapUpdater)
        {
            std::function<void(Update &update)> func([this](Update &update){
                this->UpdateSignals(std::move(update));
            });
            mapUpdater.connect(func);
        }
        void connect(const _signal::slot_type &subscriber, std::vector<size_t> roadId)
        {
            std::for_each(roadId.begin(),roadId.end(),[&](size_t id){
                std::cout<<"Connecting on index:"<<id<<std::endl;
                m_sig[id].connect(subscriber);
            });
        }
        void UpdateSignals(Update&& update){
            std::cout<<"Updating on index:"<<update.getRoadId()<<std::endl;
            m_sig[update.getRoadId()](update);
        }
        
    private:
        std::array <_signal, 1000> m_sig;
    }; 
}