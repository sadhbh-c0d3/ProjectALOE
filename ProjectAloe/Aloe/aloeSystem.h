#ifndef ALOE_INCLUDED_ALOE_SYSTEM_H
#define ALOE_INCLUDED_ALOE_SYSTEM_H

#include "Aloe/aloe.h"
#include "Aloe/aloeObjectRef.h"

namespace Aloe {

    struct IWindow;
    struct IWindowEvents;
    struct IGraphicDevice;
    struct IGraphicsDesign;
    struct IRaster;
    struct IRegion;
    
    aloe__interface( IWindow )
    {
        aloe__iid( IWindow );

        aloe__prop( IWindow, FrameRect
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IWindow, ClientRect
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IWindow, Close
                , ____
                , ____ );

        aloe__prop( IWindow, Region
                , ____, ____
                , get , put , pointer( IRegion )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IWindow, DirtyRects
                , ____, ____
                , ____, ____, ____
                , append, ____, type( Recti )
                , remove, ____, type( Recti )
                , ____, ____, ____ );

        aloe__prop( IWindow, DirtyRegions
                , ____, ____
                , ____, ____, ____
                , append, ____, pointer( IRegion )
                , remove, ____, pointer( IRegion )
                , ____, ____, ____ );

        aloe__method( IWindow, Update
                , ____
                , tuple0());
        
        aloe__method( IWindow, RedrawRect
                , ____
                , tuple2(
                    arg( rect, In, type( Recti )),
                    arg( flags, In, type( Long ))
                    ));
        
        aloe__method( IWindow, RedrawRegion
                , ____
                , tuple2(
                    arg( region, In, pointer( IRegion )),
                    arg( flags, In, type( Long ))
                    ));
    };

    aloe__runtime_prop( IWindow, FrameRect );
    aloe__runtime_prop( IWindow, ClientRect );
    
    aloe__interface( IWindowEvents )
    {
        aloe__iid( IWindowEvents );

        aloe__method( IWindowEvents, Close
                , type( Bool )
                , tuple1(
                    arg( sender, In, pointer( IWindow ))
                    ));
        
        aloe__method( IWindowEvents, Show
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( flags, In, type( Long ))
                    ));
        
        aloe__method( IWindowEvents, Activate
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IWindow )),
                    arg( active, In, type( Bool ))
                    ));
        
        aloe__method( IWindowEvents, Focus
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IWindow )),
                    arg( active, In, type( Bool ))
                    ));
        
        aloe__method( IWindowEvents, LostCapture
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( capture, In, pointer( IProvider ))
                    ));
        
        aloe__method( IWindowEvents, Move
                , type( Bool )
                , tuple3(
                    arg( sender   , In, pointer( IWindow )),
                    arg( frameRect, In, type( Recti )),
                    arg( flags    , In, type( Long ))
                    ));

        aloe__method( IWindowEvents, Key
                , type( Bool )
                , tuple3(
                    arg( sender , In, pointer( IWindow )),
                    arg( virtKey, In, type( Long )),
                    arg( isDown , In, type( Bool ))
                    ));
        
        aloe__method( IWindowEvents, Motion
                , type( Bool )
                , tuple2(
                    arg( sender,   In, pointer( IWindow )),
                    arg( position, In, type( Point2i ))
                    ));
        
        aloe__method( IWindowEvents, Button
                , type( Bool )
                , tuple4(
                    arg( sender,   In, pointer( IWindow )),
                    arg( position, In, type( Point2i )),
                    arg( buttonNo, In, type( Long )),
                    arg( isDown  , In, type( Bool ))
                    ));
        
        aloe__method( IWindowEvents, DoubleClick
                , type( Bool )
                , tuple3(
                    arg( sender,   In, pointer( IWindow )),
                    arg( position, In, type( Point2i )),
                    arg( buttonNo, In, type( Long ))
                    ));

        aloe__method( IWindowEvents, Paint
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IWindow )),
                    arg( device, In, pointer( IGraphicDevice )),
                    arg( rect, In, type( Recti ))
                    ));
    };

    aloe__runtime_method( IWindowEvents, Close );
    aloe__runtime_method( IWindowEvents, Show );
    aloe__runtime_method( IWindowEvents, Activate );
    aloe__runtime_method( IWindowEvents, Focus );
    aloe__runtime_method( IWindowEvents, LostCapture );
    aloe__runtime_method( IWindowEvents, Move );
    aloe__runtime_method( IWindowEvents, Key );
    aloe__runtime_method( IWindowEvents, Motion );
    aloe__runtime_method( IWindowEvents, Button );
    aloe__runtime_method( IWindowEvents, DoubleClick );
    aloe__runtime_method( IWindowEvents, Paint );

    aloe__interface( IGraphicDevice )
    {
        aloe__iid( IGraphicDevice );

        aloe__method( IGraphicDevice, CreateDesign
                , pointer( IGraphicsDesign )
                , tuple1(
                    arg( rect, In, type( Recti ))
                    ));
        
        aloe__method( IGraphicDevice, RenderDesign
                , type( Bool )
                , tuple2(
                    arg( design, In, pointer( IGraphicsDesign )),
                    arg( rect, In, type( Recti ))
                    ));

        aloe__prop( IGraphicDevice, Raster
                , ____, ____
                , get , put , pointer( IRaster )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_method( IGraphicDevice, CreateDesign );
    aloe__runtime_method( IGraphicDevice, RenderDesign );
    aloe__runtime_prop( IGraphicDevice, Raster );

    aloe__interface( IRegion )
    {
        aloe__iid( IRegion );

        aloe__prop( IRegion, Rectangles
                , ____, ____
                , get , put , array_of( type( Recti ))
                , append, type( Int ), type( Recti )
                , remove, type( Int ), type( Recti )
                , ____, ____, ____ );

        aloe__prop( IRegion, Bound
                , ____, ____
                , get , ____, type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IRegion, And
                , type( Int )
                , tuple1(
                    arg( region, In, pointer( IRegion ))
                    ));

        aloe__method( IRegion, Sub
                , type( Int )
                , tuple1(
                    arg( region, In, pointer( IRegion ))
                    ));
        
        aloe__method( IRegion, Add
                , type( Int )
                , tuple1(
                    arg( region, In, pointer( IRegion ))
                    ));
        
        aloe__method( IRegion, Xor
                , type( Int )
                , tuple1(
                    arg( region, In, pointer( IRegion ))
                    ));
        
        aloe__method( IRegion, Copy
                , type( Int )
                , tuple1(
                    arg( region, In, pointer( IRegion ))
                    ));

        aloe__method( IRegion, Rect
                , ____
                , tuple1(
                    arg( rect, In, type( Recti ))
                    ));
        
        aloe__method( IRegion, RoundRect
                , ____
                , tuple2(
                    arg( bound, In, type( Recti )),
                    arg( radi, In, type( Vector2i ))
                    ));
        
        aloe__method( IRegion, Ellipse
                , ____
                , tuple1(
                    arg( bound, In, type( Recti ))
                    ));
        
        aloe__method( IRegion, Polygon
                , ____
                , tuple1(
                    arg( points, In, array_of( type( Point2i )))
                    ));
        
        aloe__method( IRegion, PolyPolygon
                , ____
                , tuple2(
                    arg( points, In, array_of( type( Point2i ))),
                    arg( sizes, In, array_of( type( SizeType )))
                    ));
    };

};//Aloe

#endif//ALOE_INCLUDED_ALOE_SYSTEM_H
