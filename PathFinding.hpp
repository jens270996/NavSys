#pragma once
#include "Path.hpp"
#include "Map.hpp"
#include "List.hpp"
namespace Map{

    template<typename FROM, typename TO,typename GRAPH>
    static constexpr auto findPath(FROM from, TO to, GRAPH graph){
        GRAPH::getRoadsFromCity(from);

        //list of paths
        
        //take shortest and take next step
    }
}