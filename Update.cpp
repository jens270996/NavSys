#include "Update.hpp"
#include "RoadInformation.hpp"

Update::Update(int roadId, RoadInformation roadInformation)
{
    _road_id = roadId;
    _road_information = roadInformation;
}
