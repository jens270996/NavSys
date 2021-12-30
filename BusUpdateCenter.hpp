#include <RoadInformation.hpp>
#include <vector>
#include "MapUpdater.hpp"
#include <boost/signals2.hpp>
#include "Update.hpp"

class BusUpdateCenter{
    public:
        BusUpdateCenter(){

        };
        template <typename T>
        void connect(T funcToConnect, int slotToConnect){
            _signals.connect(funcToConnect, int);
        }
        void handleUpdates(MapUpdater u){
            
        }
    private:
        std::vector<boost::signals2::signal<void(Update)>> _signals;
}; 
