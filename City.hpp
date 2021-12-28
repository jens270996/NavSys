#pragma once
#include <string>

namespace City{

    template <size_t ID>
    struct City{
        static const size_t id = ID;
    };

    //Trait with city names?? Specific names must be defined in global scope?
    // template <typename T>
    // struct City_Traits{
    //     static const char name* = "Unknown";
    // };

    // Template aliases
    using Odense = City<0>;
    using Aarhus = City<1>;
    
}