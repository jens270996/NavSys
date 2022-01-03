#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
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
        private:
            int _roadId;
            RoadInformation* _roadInformation;
    };
class MapUpdater 
{
    typedef boost::signals2::signal<void()> _signal;

    public:
    MapUpdater(){
        _update = nullptr;
    }
    boost::signals2::connection connect(const _signal::slot_type &subscriber)
    {
        return m_sig.connect(subscriber);
    }
    template <typename T, typename M>
    void Updates(T* update){
        _update = update;
    }
    template <class T>
    void UpdateSignal(const char* s, T* update){
        m_text += s;
        _update = update;
        m_sig();
    }
    template <class T>
    void UpdateSignal(const char* s, T& update){
        m_text += s;
        _update = update;
        m_sig();
    }
    Update* getUpdate(){
        return _update;
    }
    const std::string& getText() const{
        return m_text;
    }
    private:
    _signal m_sig;
    std::string m_text;
    Update* _update;
}; 


class BusUpdateCenter{
    public:
        BusUpdateCenter(MapUpdater &mapUpdater)
        :_mapUpdater(mapUpdater)
        {

        }
        #pragma region 
    //     BusUpdateCenter(const T &mapUpdater){
    //         _mapUpdater = mapUpdater;
    //         std::cout << "const &" << std::endl;
    //     }
    //     BusUpdateCenter(const T *mapUpdater){
    //         _mapUpdater = mapUpdater;
    //         std::cout << "const*" << std::endl;
    //     }
    //     BusUpdateCenter(T* mapUpdater){
    //         _mapUpdater = mapUpdater;
    //         std::cout << "**" << std::endl;
    //     };
    //     BusUpdateCenter(){
    //         std::cout << "Nothing" << std::endl;
    //    }
    //    BusUpdateCenter(T mapUpdater){
    //        _mapUpdater = mapUpdater;
    //    }
    #pragma endregion
       ~BusUpdateCenter(){
            m_connection.disconnect();
        }
        void handleUpdates(){
            std::cout << "handleUpdates: " << _mapUpdater.getText() << std::endl;
            
        }
        Update busUpdateJylland(){
            std::cout << "busUpdateJylland: " << _mapUpdater.getText() << std::endl;
            Update *update = _mapUpdater.getUpdate();
            update->getTraversalTimeImpact();
            std::cout << "Update:   TraversalTimeImpact: " << update->getTraversalTimeImpact() << std::endl; 
            std::cout << "  IsPassable: " << update->getIsPassable() << std::endl;
            std::cout << "  Message: " << update->getMessage() << std::endl;
            return *update;
        }
        void busUpdateSjaelland(){
            std::cout << "busUpdateSjaelland: " << _mapUpdater.getText() << std::endl;
        }
        void busUpdateFyn(){
            std::cout << "busUpdateFyn: " << _mapUpdater.getText() << std::endl;
        }

        boost::signals2::connection m_connection;
        MapUpdater& _mapUpdater;
    private:

    };    
}