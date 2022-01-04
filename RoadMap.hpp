#pragma once
#include "Map.hpp"
namespace BusRouter{
namespace Map{
namespace RoadMap{
    //Actual map

    //Cities
    using Copenhagen = City<1301>;
    using Helsingoer = City<3000>;
    using Roskilde = City<4000>;
    using Koege = City<4600>;
    // using Naestved = City<4700>;
    using Slagelse = City<4200>;
    using Kalundborg = City<4400>;
    using Nyborg = City<5800>;
    using Svendborg = City<5700>;
    using Odense = City<5000>;
    using Middelfart = City<5500>;
    using Fredericia = City<7000>;
    // using Haderslev = City<6100>;
    using Esbjerg = City<6700>;
    using Vejle = City<7100>;
    using Horsens = City<8700>;
    using Herning = City<7400>;
    using Silkeborg = City<8600>;
    using Skanderborg = City<8660>;
    using Aarhus = City<8000>;
    using Holstebro = City<7500>;
    using Viborg = City<8800>;
    using Randers = City<8900>;
    using Grenaa = City<8500>;
    using Aalborg = City<9000>;

    //Roads
    //From to weight cost id

    template<size_t road_id>
    struct Road_Information{
        static const char* const from();
        static const char* const to();
    };

    #define CREATE_BIDIRECTIONAL_ROAD(FROM,TO,WEIGHT,COST,ID1,ID2)\
    using FROM ## _ ## TO = Road<FROM,TO,WEIGHT,COST,ID1>;\
    using TO ## _ ## FROM = Road<TO,FROM,WEIGHT,COST,ID2>;\
    namespace{\
        static const char from_ ## ID1 ## ID2 [] = #FROM ;\
        static const char to_ ## ID1 ## ID2 [] = #TO ;\
    }\
    template<>\
    struct Road_Information<ID1>\
    {\
        static const char* const from(){return from_ ## ID1 ## ID2 ;}\
        static const char* const to(){ return to_ ## ID1 ## ID2 ; }\
    };\
    template<>\
    struct Road_Information<ID2>\
    {\
        static const char* const from(){return to_ ## ID1 ## ID2 ;}\
        static const char* const to(){return from_ ## ID1 ## ID2 ;}\
    };\
    

    //Sjælland
    CREATE_BIDIRECTIONAL_ROAD(Copenhagen,Helsingoer,50,0,0,1)
    CREATE_BIDIRECTIONAL_ROAD(Copenhagen,Roskilde,40,0,2,3)
    CREATE_BIDIRECTIONAL_ROAD(Copenhagen,Koege,50,0,4,5)
    CREATE_BIDIRECTIONAL_ROAD(Koege,Slagelse,70,0,6,7)
    CREATE_BIDIRECTIONAL_ROAD(Roskilde,Kalundborg,80,0,8,9)
    CREATE_BIDIRECTIONAL_ROAD(Kalundborg,Slagelse,60,0,10,11)
    CREATE_BIDIRECTIONAL_ROAD(Slagelse,Nyborg,60,400,12,13)

    //Fyn
    CREATE_BIDIRECTIONAL_ROAD(Nyborg,Svendborg,50,0,14,15)
    CREATE_BIDIRECTIONAL_ROAD(Nyborg,Odense,40,0,16,17)
    CREATE_BIDIRECTIONAL_ROAD(Svendborg,Odense,60,0,18,19)
    CREATE_BIDIRECTIONAL_ROAD(Odense,Middelfart,60,0,20,21)
    CREATE_BIDIRECTIONAL_ROAD(Middelfart,Fredericia,10,0,22,23)
    CREATE_BIDIRECTIONAL_ROAD(Fredericia,Vejle,30,0,24,25)
    CREATE_BIDIRECTIONAL_ROAD(Fredericia,Esbjerg,100,0,26,27)
    CREATE_BIDIRECTIONAL_ROAD(Esbjerg,Herning,90,0,28,29)
    CREATE_BIDIRECTIONAL_ROAD(Vejle,Herning,70,0,30,31)
    CREATE_BIDIRECTIONAL_ROAD(Vejle,Horsens,20,0,32,33)
    CREATE_BIDIRECTIONAL_ROAD(Horsens,Herning,20,0,34,35)
    CREATE_BIDIRECTIONAL_ROAD(Horsens,Skanderborg,20,0,36,37)
    CREATE_BIDIRECTIONAL_ROAD(Skanderborg,Aarhus,20,0,38,39)
    CREATE_BIDIRECTIONAL_ROAD(Herning,Silkeborg,30,0,40,41)
    CREATE_BIDIRECTIONAL_ROAD(Silkeborg,Aarhus,30,0,42,43)
    CREATE_BIDIRECTIONAL_ROAD(Herning,Viborg,30,0,44,45)
    CREATE_BIDIRECTIONAL_ROAD(Silkeborg,Viborg,100,0,46,47)
    CREATE_BIDIRECTIONAL_ROAD(Aarhus,Viborg,40,0,48,49)
    CREATE_BIDIRECTIONAL_ROAD(Aarhus,Randers,30,0,50,51)
    CREATE_BIDIRECTIONAL_ROAD(Randers,Viborg,20,0,52,53)
    CREATE_BIDIRECTIONAL_ROAD(Herning,Holstebro,20,0,54,55)
    CREATE_BIDIRECTIONAL_ROAD(Viborg,Holstebro,30,0,56,57)
    CREATE_BIDIRECTIONAL_ROAD(Aarhus,Grenaa,70,0,58,59)
    CREATE_BIDIRECTIONAL_ROAD(Randers,Grenaa,40,0,60,61)
    CREATE_BIDIRECTIONAL_ROAD(Randers,Aalborg,70,0,62,63)


    #define NO_OF_ROADS 64
    using MapGraph = Map::MapGraph<
    TL::List<Copenhagen,Helsingoer,Roskilde,Koege,Slagelse,Kalundborg,Nyborg,Svendborg,Odense,Middelfart,Fredericia
        ,Esbjerg,Vejle,Horsens,Herning,Silkeborg,Skanderborg,Aarhus,Holstebro,Viborg,Randers,Grenaa,Aalborg>

    ,TL::List<Copenhagen_Helsingoer,Copenhagen_Koege,Copenhagen_Roskilde,Helsingoer_Copenhagen,Roskilde_Copenhagen,Roskilde_Kalundborg
        ,Koege_Copenhagen,Koege_Slagelse,Slagelse_Kalundborg,Slagelse_Koege,Slagelse_Nyborg,Kalundborg_Roskilde,Kalundborg_Slagelse
        ,Nyborg_Slagelse,Nyborg_Svendborg,Nyborg_Odense,Svendborg_Nyborg,Svendborg_Odense,Odense_Middelfart,Odense_Nyborg,Odense_Svendborg
        ,Middelfart_Odense,Middelfart_Fredericia,Fredericia_Esbjerg,Fredericia_Middelfart,Fredericia_Vejle,Esbjerg_Fredericia,Esbjerg_Herning
        ,Vejle_Fredericia,Vejle_Herning,Vejle_Horsens,Horsens_Herning,Horsens_Skanderborg,Horsens_Vejle,Herning_Esbjerg,Herning_Holstebro
        ,Herning_Horsens,Herning_Silkeborg,Herning_Vejle,Herning_Viborg,Silkeborg_Aarhus,Silkeborg_Herning,Silkeborg_Viborg,Skanderborg_Aarhus
        ,Skanderborg_Horsens,Aarhus_Grenaa,Aarhus_Randers,Aarhus_Silkeborg,Aarhus_Skanderborg,Aarhus_Viborg,Holstebro_Herning,Holstebro_Viborg
        ,Viborg_Aarhus,Viborg_Herning,Viborg_Holstebro,Viborg_Randers,Viborg_Silkeborg,Randers_Aalborg,Randers_Aarhus,Randers_Grenaa,Randers_Viborg
        ,Grenaa_Aarhus,Grenaa_Randers,Aalborg_Randers>
    >;

    using MapGraphJylland = Map::MapGraph<
    TL::List<Fredericia
        ,Esbjerg,Vejle,Horsens,Silkeborg,Skanderborg,Aarhus,Holstebro,Viborg,Randers,Grenaa,Aalborg>

    ,TL::List<Fredericia_Esbjerg,Fredericia_Vejle,Esbjerg_Fredericia
        ,Vejle_Fredericia,Vejle_Horsens,Horsens_Skanderborg,Horsens_Vejle
        ,Silkeborg_Aarhus,Silkeborg_Viborg,Skanderborg_Aarhus
        ,Skanderborg_Horsens,Aarhus_Grenaa,Aarhus_Randers,Aarhus_Silkeborg,Aarhus_Skanderborg,Aarhus_Viborg,Holstebro_Viborg
        ,Viborg_Aarhus,Viborg_Holstebro,Viborg_Randers,Viborg_Silkeborg,Randers_Aalborg,Randers_Aarhus,Randers_Grenaa,Randers_Viborg
        ,Grenaa_Aarhus,Grenaa_Randers,Aalborg_Randers>
    >;

    using MapGraphThree = Map::MapGraph<
    TL::List<Horsens,Skanderborg,Aarhus>

    ,TL::List<Aarhus_Skanderborg,Skanderborg_Aarhus,Skanderborg_Horsens,Horsens_Skanderborg>
    >;
}
}
}