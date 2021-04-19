#ifndef ALOE_INCLUDED_ALOE_RASTER_H
#define ALOE_INCLUDED_ALOE_RASTER_H

#include "Aloe/aloe.h"

namespace Aloe {
    
    struct IRasterFormat;
    struct IPixelArray;
    struct IRasterRect;
    struct IRaster;
    

    aloe__interface( IRasterFormat )
    {
        aloe__iid( IRasterFormat );

        aloe__prop( IRasterFormat, RasterSize
                , ____, ____
                , get , put, type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IRasterFormat, PixelType
                , ____, ____
                , get , put, type( PixelType )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IRasterFormat, RasterSize );
    aloe__runtime_prop( IRasterFormat, PixelType );

    aloe__interface( IPixelArray )
    {
        aloe__iid( IPixelArray );

        aloe__prop( IPixelArray, BytesPerRow
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IPixelArray, BytesPerPixel
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__method( IPixelArray, Lock
                , type( NCUByteArray )
                , tuple1(
                    arg( info, In, type( PixelRectangle* ))
                    ));
        
        aloe__method( IPixelArray, Unlock
                , ____
                , tuple0()
                );
    };

    aloe__runtime_prop( IPixelArray, BytesPerRow );
    aloe__runtime_prop( IPixelArray, BytesPerPixel );
    aloe__runtime_method( IPixelArray, Lock );
    aloe__runtime_method( IPixelArray, Unlock );

    aloe__interface( IRasterRect )
    {
        aloe__iid( IRasterRect );

        aloe__prop( IRasterRect, Raster
                , ____, ____
                , get , put , pointer( IRaster )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IRasterRect, Rect
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IRasterRect, Raster );
    aloe__runtime_prop( IRasterRect, Rect );


    aloe__interface( IRaster )
    {
        aloe__iid( IRaster );

        aloe__prop( IRaster, PixelRect
                , map , type( Recti )
                , get , put , pointer( IRasterRect )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IRaster, CreateCompat
                , pointer( IRaster )
                , tuple1(
                    arg( format, In, pointer( IRasterFormat ))
                    )
                );
    };

    aloe__runtime_map( IRaster, PixelRect );
    aloe__runtime_method( IRaster, CreateCompat );
    

};//Aloe

#endif//ALOE_INCLUDED_ALOE_RASTER_H
