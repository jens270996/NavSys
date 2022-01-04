#pragma once
#include <string>
#include <memory>
#include <iostream>

namespace BusRouter{
namespace BusUpdate{
    class RoadInformation{
        public:
            RoadInformation(double traversalTimeImpact, bool isPassable, std::string message)
            {
                _traversalTimeImpact = traversalTimeImpact;
                _isPassable = isPassable;
                _message = message;
            }
            RoadInformation(RoadInformation&& rhs){
                _traversalTimeImpact = std::move(rhs._traversalTimeImpact);
                _isPassable = std::move(rhs._isPassable);
                _message = std::move(rhs._message);
            }
            RoadInformation(const RoadInformation& rhs){
                _traversalTimeImpact = rhs._traversalTimeImpact;
                _isPassable = rhs._isPassable;
                _message = rhs._message;
                
            }
            RoadInformation& operator=(const RoadInformation& rhs){
                if(this!=&rhs){
                    _traversalTimeImpact = rhs._traversalTimeImpact;
                    _isPassable = rhs._isPassable;
                    _message = rhs._message;
                }
                return *this;
            }
            RoadInformation& operator=(RoadInformation&& rhs){
                if(this!=&rhs){
                    _traversalTimeImpact = std::move(rhs._traversalTimeImpact);
                    _isPassable = std::move(rhs._isPassable);
                    _message = std::move(rhs._message);
                }
                return *this;
            }
            double getTraversalTimeImpact()const{
                return _traversalTimeImpact;
            }
            bool getIsPassable()const{
                return _isPassable;
            }
            std::string getMessage()const{
                return _message;
            }
        private:
            double _traversalTimeImpact;
            bool _isPassable;
            std::string _message;

    };
    struct UpdateExpiration{
        UpdateExpiration(int updateId,int roadId):update_id{updateId},road_id{roadId}{}
        const int update_id;
        const int road_id;
    };
    class Update{
        public:
            template<typename... RIs>
            Update(int updateId, int roadId, RIs... ris)
            :_updateId{updateId},_roadId{roadId},
            _roadInformation{std::make_shared<RoadInformation>(std::forward<RIs>(ris)...)}{}

            Update(Update&& update) noexcept
            :_updateId{std::move(update._updateId)},_roadId{std::move(update._roadId)},_roadInformation{update._roadInformation}{
            };
            Update(const Update& update):_updateId{update._updateId},_roadId{update._roadId},_roadInformation{update._roadInformation}{
            };
            Update& operator=(const Update& update) = delete;
            Update& operator=(Update&& update) = delete ;
            ~Update()=default;
            double getTraversalTimeImpact()const{
                try{
                return _roadInformation->getTraversalTimeImpact();
                }
                catch(...){
                    std::cout << "Exception thrown in getTraversalTimeImpact" << std::endl;
                }
            }
            bool getIsPassable() const{
                try{   
                    return _roadInformation->getIsPassable();
                }
                catch(...){
                    std::cout << "Exception thrown in getIsPassable" << std::endl;
                }
            }
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
    template<typename T>
    struct AccumulationTraits{};

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