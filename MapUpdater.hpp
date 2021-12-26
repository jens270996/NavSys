#include <boost/signals2.hpp>
#include "MapUpdate.hpp"
class MapUpdater{
    public:
    template <typename T>
    void connect( T func_to_connect){
        _signal.connect(T);
    }


    private:
    boost::signals2::signal<void(MapUpdate)> _signal;

    MapUpdate generateUpdate(){
        return MapUpdate();
    }

};