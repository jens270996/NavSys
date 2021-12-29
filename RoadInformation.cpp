#include "RoadInformation.hpp"

RoadInformation::RoadInformation(double traversalTimeImpact, bool isPassable,
        std::string message)
{
    _traversalTimeImpact = traversalTimeImpact;
    _is_passable = isPassable;
    _message = message;
}