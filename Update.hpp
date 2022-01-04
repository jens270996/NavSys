#pragma once
#include <string>
#include <memory>
#include <iostream>

namespace BusRouter{
namespace BusUpdate{
    // The class with all the road informations to update the bus' about 
    class RoadInformation{
        public:
            // Parameterized constructor
            RoadInformation(double traversalTimeImpact, bool isPassable, std::string message)
            {
                _traversalTimeImpact = traversalTimeImpact;
                _isPassable = isPassable;
                _message = message;
            }
            // Move constructor
            RoadInformation(RoadInformation&& rhs){
                _traversalTimeImpact = std::move(rhs._traversalTimeImpact);
                _isPassable = std::move(rhs._isPassable);
                _message = std::move(rhs._message);
            }
            // Copy constructor
            RoadInformation(const RoadInformation& rhs){
                _traversalTimeImpact = rhs._traversalTimeImpact;
                _isPassable = rhs._isPassable;
                _message = rhs._message;
                
            }
            // Copy assignment operator 
            RoadInformation& operator=(const RoadInformation& rhs){
                if(this!=&rhs){
                    _traversalTimeImpact = rhs._traversalTimeImpact;
                    _isPassable = rhs._isPassable;
                    _message = rhs._message;
                }
                return *this;
            }
            // Move operator
            RoadInformation& operator=(RoadInformation&& rhs){
                if(this!=&rhs){
                    _traversalTimeImpact = std::move(rhs._traversalTimeImpact);
                    _isPassable = std::move(rhs._isPassable);
                    _message = std::move(rhs._message);
                }
                return *this;
            }
            // return the delayed time
            double getTraversalTimeImpact()const{
                return _traversalTimeImpact;
            }
            // return true if it is passable for the bus
            bool getIsPassable()const{
                return _isPassable;
            }
            // Gives a message to the bus
            std::string getMessage()const{
                return _message;
            }
        private:
            double _traversalTimeImpact;
            bool _isPassable;
            std::string _message;

    };
    // Struct for the UpdateExpiration
    struct UpdateExpiration{
        UpdateExpiration(int updateId,int roadId):update_id{updateId},road_id{roadId}{}
        const int update_id;
        const int road_id;
    };
    //It is the updates which will be send to the bus' 
    class Update{
        public:
            // Varadic template constructor with rvalue reference to perfect forwarding
            template<typename... RIs>
            Update(int updateId, int roadId, RIs... ris)
            :_updateId{updateId},_roadId{roadId},
            _roadInformation{std::make_shared<RoadInformation>(std::forward<RIs>(ris)...)}{}

            // Move constructor
            Update(Update&& update) noexcept
            :_updateId{std::move(update._updateId)},_roadId{std::move(update._roadId)},_roadInformation{update._roadInformation}{
            };
            
            // Copy constructor
            Update(const Update& update):_updateId{update._updateId},_roadId{update._roadId},_roadInformation{update._roadInformation}{
            };
            // Copy assignment operator with default value delete
            Update& operator=(const Update& update) = delete;
            // Move operator 
            Update& operator=(Update&& update) = delete;
            // Destructor
            ~Update()=default;
            
            // Use Simple guarantee
            double getTraversalTimeImpact()const{
                try{
                return _roadInformation->getTraversalTimeImpact();
                }
                catch(...){
                    std::cout << "Exception thrown in getTraversalTimeImpact" << std::endl;
                }
            }
            // Use Simple guarantee
            bool getIsPassable() const{
                try{   
                    return _roadInformation->getIsPassable();
                }
                catch(...){
                    std::cout << "Exception thrown in getIsPassable" << std::endl;
                }
            }
            // Use Simple guarantee
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
            int getUpdateId()const{
                return _updateId;
            }
        private:
        const int _updateId;
        int _roadId;
        std::shared_ptr<const RoadInformation> _roadInformation;
    };

    // Empty class template
    template<typename T>
    struct AccumulationTraits{};

    // Fully specialised template class for Update
    template<>
    struct AccumulationTraits<Update>
    {
        int operator()(int&& sum, const Update & update){
            return sum+=update.getTraversalTimeImpact();
        }
        typedef float AccT;
        static AccT zero(){return 0.0;}
    };
}
}