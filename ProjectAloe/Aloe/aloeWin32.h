#ifndef ALOE_INCLUDED_ALOE_WIN32_H
#define ALOE_INCLUDED_ALOE_WIN32_H

#include "Aloe/aloeSystem.h"
#include "Aloe/aloeStorage.h"
#include "Aloe/aloeRaster.h"
#include "Aloe/aloeUI.h"

#define _UNICODE 1
#define UNICODE 1
#define MEAN_AND_LEAN
#include <windows.h>
#ifndef UNICODE
#   define WIN32__CreateWindow CreateWindowA
#else
#   define WIN32__CreateWindow CreateWindowW
#endif
#undef CreateWindow
#undef Sleep


namespace Aloe {
    namespace Win32 {

        struct IMessageLoop;
        struct IWindowFactory;
        struct IWindowClass;
        struct IWindow;
        struct IWindowEvents;

        extern Utils::SmartPtr< IFactory > Initialize( HINSTANCE hInstance );

        aloe__interface( IMessageLoop )
        {
            aloe__iid( Win32::IMessageLoop );

            aloe__method( IMessageLoop, Run, type( Long ) ,____ );
        };
        
        aloe__runtime_method_ns( Win32, IMessageLoop, Run );

        aloe__interface( IWindowFactory )
        {
            aloe__iid( Win32::IWindowFactory );

            aloe__method( IWindowFactory, CreateWindow
                    , pointer( Win32::IWindow )
                    , tuple8(
                        arg( className,     In, type( String )),
                        arg( classStyle,    In, type( Long )),
                        arg( windowName,    In, type( String )),
                        arg( windowStyle,   In, type( Long )),
                        arg( windowStyleEx, In, type( Long )),
                        arg( windowRect,    In, type( Recti )),
                        arg( windowParent,  In, custom( ::HWND )),
                        arg( windowMenu,    In, custom( ::HMENU ))
                        ));
        };

        aloe__runtime_method_ns( Win32, IWindowFactory, CreateWindow );

        aloe__interface( IWindowClass )
        {
            aloe__iid( Win32::IWindowClass );

            aloe__prop( IWindowClass, Style
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindowClass, Long
                    , map , type( Long )
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };

        aloe__runtime_prop_ns( Win32, IWindowClass, Style );
        aloe__runtime_prop_ns( Win32, IWindowClass, Long );

        aloe__interface( IWindow )
        {
            aloe__iid( Win32::IWindow );

            aloe__prop( IWindow, Class
                    , ____, ____
                    , get , ____, pointer( Win32::IWindowClass )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindow, Style
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindow, ExStyle
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindow, UserData
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindow, Long
                    , map , type( Long )
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

            aloe__prop( IWindow, HWnd
                    , ____, ____
                    , get , ____, custom( ::HWND )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };

        aloe__runtime_prop_ns( Win32, IWindow, Class );
        aloe__runtime_prop_ns( Win32, IWindow, Style );
        aloe__runtime_prop_ns( Win32, IWindow, ExStyle );
        aloe__runtime_prop_ns( Win32, IWindow, UserData );
        aloe__runtime_map ( Win32::IWindow, Long );
        aloe__runtime_prop_ns( Win32, IWindow, HWnd );
        
        aloe__interface( IWindowEvents )
        {
            aloe__iid( Win32::IWindowEvents );

            aloe__method( IWindowEvents, Event
                    , type( Bool )
                    , tuple4(
                        arg( sender,   In, pointer( Win32::IWindow )),
                        arg( message,  In, type( Long )),
                        arg( wParam,   In, type( LongPointer )),
                        arg( lParam,   In, type( LongPointer ))
                        ));
        };

        aloe__runtime_method_ns( Win32, IWindowEvents, Event );

        aloe__interface( ILayeredWindow )
        {
            aloe__iid( Win32::ILayeredWindow );

            aloe__prop( ILayeredWindow, Opacity
                    , ____, ____
                    , get , put , type( UByte )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( ILayeredWindow, ColorKey
                    , ____, ____
                    , get , put , type( Color32 )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( ILayeredWindow, Flags
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

            aloe__method( ILayeredWindow, Commit
                    , type( Bool )
                    , tuple0());
        };

        aloe__runtime_prop_ns( Win32, ILayeredWindow, Opacity );
        aloe__runtime_prop_ns( Win32, ILayeredWindow, ColorKey );
        aloe__runtime_prop_ns( Win32, ILayeredWindow, Flags );
        aloe__runtime_method_ns( Win32, ILayeredWindow, Commit );

        aloe__interface( IGDIObject )
        {
            aloe__iid( Win32::IGDIObject );

            aloe__prop( IGDIObject, HGDIObject
                    , ____, ____
                    , get , ____, custom( ::HGDIOBJ )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };

        aloe__runtime_prop( IGDIObject, HGDIObject );
        
        aloe__interface( IBitmap )
        {
            aloe__iid( Win32::IBitmap );

            aloe__prop( IBitmap, HBitmap
                    , ____, ____
                    , get , ____, custom( ::HBITMAP )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };
        
        aloe__runtime_prop_ns( Win32, IBitmap, HBitmap );

        aloe__interface( IFont )
        {
            aloe__iid( Win32::IFont );

            aloe__prop( IFont, HFont
                    , ____, ____
                    , get , ____, custom( ::HFONT )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };
        
        aloe__runtime_prop_ns( Win32, IFont, HFont );

        aloe__interface( IPen )
        {
            aloe__iid( Win32::IPen );

            aloe__prop( IPen, HPen
                    , ____, ____
                    , get , ____, custom( ::HPEN )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };
        
        aloe__runtime_prop_ns( Win32, IPen, HPen );

        aloe__interface( IBrush )
        {
            aloe__iid( Win32::IBrush );

            aloe__prop( IBrush, HBrush
                    , ____, ____
                    , get , ____, custom( ::HBRUSH )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };
        
        aloe__runtime_prop_ns( Win32, IBrush, HBrush );

        aloe__interface( ICursor )
        {
            aloe__iid( Win32::ICursor );

            aloe__prop( ICursor, HCursor
                    , ____, ____
                    , get , ____, custom( ::HCURSOR )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

        };

        aloe__runtime_prop_ns( Win32, ICursor, HCursor );

        aloe__interface( IRegion )
        {
            aloe__iid( Win32::IRegion );

            aloe__prop( IRegion, HRgn
                    , ____, ____
                    , get , ____, custom( ::HRGN )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

        };

        aloe__runtime_prop_ns( Win32, IRegion, HRgn );

        aloe__interface( IDevContext )
        {
            aloe__iid( Win32::IDevContext );

            aloe__prop( IDevContext, HDc
                    , ____, ____
                    , get , ____, custom( ::HDC )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

            aloe__prop( IDevContext, Bitmap
                    , ____, ____
                    , get , put , pointer( Win32::IBitmap )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

            aloe__prop( IDevContext, Font
                    , ____, ____
                    , get , put , pointer( Win32::IFont )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

            aloe__prop( IDevContext, Pen
                    , ____, ____
                    , get , put , pointer( Win32::IPen )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

            aloe__prop( IDevContext, Brush
                    , ____, ____
                    , get , put , pointer( Win32::IBrush )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

            aloe__method( IDevContext, Save
                    , type( Int )
                    , tuple0(
                        ));
            
            aloe__method( IDevContext, Restore
                    , ____
                    , tuple1(
                        arg( id, In, type( Int ))
                        ));

            aloe__method( IDevContext, DrawRectangle
                    , ____
                    , tuple3(
                        arg( rect, In, type( Recti )),
                        arg( brush, In, pointer( Win32::IBrush )),
                        arg( pen, In, pointer( Win32::IPen ))
                        ));
            
            aloe__method( IDevContext, DrawPolygon
                    , ____
                    , tuple3(
                        arg( points, In, array_of( type( Point2i ))),
                        arg( brush, In, pointer( Win32::IBrush )),
                        arg( pen, In, pointer( Win32::IPen ))
                        ));
            
            aloe__method( IDevContext, DrawSector
                    , ____
                    , tuple3(
                        arg( point1, In, type( Point2i )),
                        arg( point2, In, type( Point2i )),
                        arg( pen, In, pointer( Win32::IPen ))
                        ));
            
            aloe__method( IDevContext, DrawPolyline
                    , ____
                    , tuple2(
                        arg( points, In, array_of( type( Point2i ))),
                        arg( pen, In, pointer( Win32::IPen ))
                        ));

            aloe__method( IDevContext, DrawString
                    , type( Int )
                    , tuple5(
                        arg( text, In, type( String )),
                        arg( rect, In, type( Recti* )),
                        arg( font, In, pointer( Win32::IFont )),
                        arg( color, In, tuple2( type( Color32 ), type( Color32 ) )),
                        arg( flags,In, type( Long ))
                        ));

            aloe__method( IDevContext, DrawBitmap
                    , ____
                    , tuple5(
                        arg( rcDest, In, type( Recti )),
                        arg( bitmap, In, pointer( Win32::IBitmap )),
                        arg( rcSource, In, type( Recti )),
                        arg( opacity, In, type( Int )),
                        arg( flags, In, type( Long ))
                        ));
        };
        
        aloe__runtime_prop_ns( Win32, IDevContext, HDc );
        aloe__runtime_prop_ns( Win32, IDevContext, Bitmap );
        aloe__runtime_prop_ns( Win32, IDevContext, Font );
        aloe__runtime_prop_ns( Win32, IDevContext, Pen );
        aloe__runtime_prop_ns( Win32, IDevContext, Brush );
        aloe__runtime_method_ns( Win32, IDevContext, Save );
        aloe__runtime_method_ns( Win32, IDevContext, Restore );
        aloe__runtime_method_ns( Win32, IDevContext, DrawRectangle );
        aloe__runtime_method_ns( Win32, IDevContext, DrawPolygon );
        aloe__runtime_method_ns( Win32, IDevContext, DrawSector );
        aloe__runtime_method_ns( Win32, IDevContext, DrawString );
        aloe__runtime_method_ns( Win32, IDevContext, DrawBitmap );
        
    };//Win32
};//Aloe

#endif//ALOE_INCLUDED_ALOE_WIN32_H

