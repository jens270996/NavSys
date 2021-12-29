#include <boost/signals2.hpp>
#include "Update.hpp"
class MapUpdater{
    public:
    MapUpdater();
    template <typename T>
    void connect(T funcToConnect){
        _signal.connect(funcToConnect);
    }


    private:
    boost::signals2::signal<void(MapUpdater)> _signal;

    Update generateUpdate(){
        //return updates.Update attributes
        return Update();
    }

};