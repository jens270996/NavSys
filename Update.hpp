#include <RoadInformation.hpp>

class Update{
    public:
        Update(int road_id, RoadInformation road_information);
        Update();
        int _road_id;
        RoadInformation _road_information;
};