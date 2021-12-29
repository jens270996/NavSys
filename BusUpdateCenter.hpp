#include <RoadInformation.hpp>
#include <vector>
#include "MapUpdater.hpp"
#include <boost/signals2.hpp>
#include "Update.hpp"

class BusUpdateCenter{
    public:
        template <typename T>
        void connect(T func_to_connect, int slotToConnect){
            _signals.connect(T, int);
        }
        void handleUpdates(MapUpdater u){
            
        }
    private:
        std::vector<boost::signals2::signal<void(Update)>> _signals;
}; 
