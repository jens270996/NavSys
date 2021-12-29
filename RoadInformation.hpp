#include <string>

class RoadInformation{
    public:
        RoadInformation(double traversalTimeImpact, bool isPassable,
        std::string message);
        RoadInformation();
    private:
        double _traversalTimeImpact;
        bool _is_passable;
        std::string _message;

};