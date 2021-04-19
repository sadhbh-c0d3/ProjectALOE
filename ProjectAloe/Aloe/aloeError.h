
#ifndef ALOE_INCLUDED_ALOE_ERROR_H
#define ALOE_INCLUDED_ALOE_ERROR_H

namespace Aloe {
    namespace Errors {

        struct Error
        {
        };

        struct Error_InterfaceNotFound : Error
        {
        };

        template< class Interface > struct InterfaceNotFound : Error_InterfaceNotFound
        {
        };

        struct Error_BadArrayIndex : Error
        {
        };

        struct Error_BadStream : Error
        {
        };

        struct BadStreamSize : Error_BadStream
        {
        };
        
        struct Error_InvalidOperation : Error
        {
        };

        struct Error_Unsupported : Error
        {
        };

    };//Errors
};//Aloe

#endif//ALOE_INCLUDED_ALOE_ERROR_H
