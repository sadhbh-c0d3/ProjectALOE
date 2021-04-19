
#ifndef ALOE_INCLUDED_ALOE_UI_H
#define ALOE_INCLUDED_ALOE_UI_H

#include "Aloe/aloe.h"

namespace Aloe {
        
    // topology
    struct IEntity;
    struct IContainer;

    // positioning in 2D space
    struct IFrame;
    struct IFrameClient;

    // cartesian row/column layout
    struct IMeshCell;
    struct IMeshLine;
    struct IMeshLayout;
    
    // polar distance/angle layout
    struct ITargetCell;
    struct ITargetRadialLine;
    struct ITargetDistanceLine;
    struct ITargetLayout;

    // drawing tools
    struct IFont;
    struct IPen;
    struct IBrush;
    struct ICursorShape;
    struct IDrawing;
    
    // drawing result
    struct IGraphicsDesign;
    struct IGraphicsDesignItem;
    struct IShapeDesign;
    struct IShapeDesign2;
    struct ILineDesign;
    struct IPolylineDesign;
    struct IPolygonDesign;
    struct IRectangleDesign;
    struct IBlitDesign;
    struct ITextDesign;

    // user interface events
    struct IUserInputState;       // state of keyboard and pointer position
    struct IUserInputState2;      // state of joystick/gamepad
    struct IUserInputEvents;      // keyboard events (sent by UI item with focus)
    struct IUserInputEvents2;     // joystick/gamepad events (sent by UI item with focus)
    struct IUserInterfaceState;   // state of an UI item
    struct IUserInterfaceState2;  // focus state of an UI item
    struct IUserInterfaceEvents;  // UI item events
    struct IUserInterfaceEvents1; // UI item events
    struct IUserInterfaceEvents2; // motion events
    struct IUserInterfaceEvents3; // click events
    struct IUserInterfaceEvents4; // drag'n'drop events

    
    /*! \brief Entity interface
     *
     *  This interface extends the unknown object with name.
     *
     *  \code
     *
     *  // assume following
     *  SmartPtr< IEntity > entity;
     *  String name;
     *
     *  // setting and getting object's name
     *  entity[ IEntity::Name ] = name;
     *  name = entity[ IEntity::Name ];
     *  
     *  \endcode
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IEntity < IContainer, IFrameClient, IGraphicsDesignerClient
     *                  ^^^^^^^
     *  \endcode
     */
    aloe__interface( IEntity )
    {
        aloe__iid( IEntity );

        aloe__prop( IEntity, Name
                , ____, ____
                , get , put , type( String )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IEntity, Container
                , ____, ____
                , get , put , pointer( IContainer )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

    };

    aloe__runtime_prop( IEntity, Name );
    aloe__runtime_prop( IEntity, Container );


    /*! \brief Container interface
     *
     *  This interface gives means for managing the set of components.
     *
     *  Allowed operations:
     *  
     *  \code
     *  
     *  // assume following
     *  SmartPtr< IContainer > box;
     *  SmartPtr<> object;
     *  SmartPtr< IEntity > entity;
     *  SmartPtr< IFrameClient > frameClient;
     *  ArrayOf< SmartPtr<> > array;
     *  String name;
     *  Point2i point;
     *  
     *  // setting and getting an array of objects
     *  box[ IContainer::Objects ] = array;
     *  array = box[ IContainer::Objects ];
     *  
     *  // appending and removing single object
     *  box[ IContainer::Objects ] += object;
     *  box[ IContainer::Objects ] -= object;
     *
     *  // finding an object by name
     *  entity = box[ IContainer::ObjectByName ][ name ];
     *
     *  // finding an object by position
     *  frameClient = box[ IContainer::ObjectByPoint ][ point ];
     *  
     *  \endcode
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider, IEntity < IContainer < IFrameClient, IGraphicsDesignerClient
     *                           ^^^^^^^^^^
     *  \endcode
     */
    aloe__interface( IContainer )
    {
        aloe__iid( IContainer );

        aloe__prop( IContainer, Objects
                , ____, ____
                , get , put , array_of_pointer( IProvider )
                , append, type( Bool ), pointer( IProvider )
                , remove, type( Bool ), pointer( IProvider )
                , ____, ____, ____ );

        aloe__prop( IContainer, ObjectByName
                , map, type( String )
                , get , ____, pointer( IEntity )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IContainer, ObjectByPoint
                , map, type( Point2i )
                , get , ____, pointer( IFrameClient )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IContainer, Objects );
    aloe__runtime_prop( IContainer, ObjectByName );
    aloe__runtime_prop( IContainer, ObjectByPoint );


    /*! \brief Frame interface
     *
     *  This interface gives means for object positioning in 2D space.
     *
     *  \code
     *
     *  // assume following
     *  SmartPtr< IFrame > frame;
     *  SmartPtr< IFrame > parent;
     *  SmartPtr< IFrameClient > client;
     *  ArrayOf< SmartPtr< IFrameClient > > array;
     *  Recti rect;
     *
     *  // setting and getting object placement rectangle
     *  frame[ IFrame::Bound ] = rect;
     *  rect = frame[ IFrame::Bound ];
     *
     *  // setting and getting clients
     *  frame[ IFrame::Clients ] = array;
     *  array = frame[ IFrame::Clients ];
     *
     *  // setting and getting parent frame
     *  frame[ IFrame::Parent ] = parent;
     *  parent = frame[ IFrame::Parent ];
     *
     *  // appending and removing single client
     *  frame[ IFrame::Clients ] += client;
     *  frame[ IFrame::Clients ] -= client;
     *
     *  \endcode
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IFrame < IMeshCell, ITargetCell
     *                  ^^^^^^
     *  \endcode
     */
    aloe__interface( IFrame )
    {
        aloe__iid( IFrame );
        
        aloe__prop( IFrame, Bound
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IFrame, Parent
                , ____, ____
                , get , put , pointer( IFrame )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IFrame, Clients
                , ____, ____
                , get , put , array_of_pointer( IFrameClient )
                , append, type( Bool ), pointer( IFrameClient )
                , remove, type( Bool ), pointer( IFrameClient )
                , ____, ____, ____ );
        
    };

    aloe__runtime_prop( IFrame, Bound );
    aloe__runtime_prop( IFrame, Parent );
    aloe__runtime_prop( IFrame, Clients );

    
    /*! \brief FrameClient interface
     *
     *  This interface bind an object to a frame and accepts change notifications.
     *
     *  \code
     *
     *  // assume following
     *  SmartPtr< IFrameClient > client;
     *  SmartPtr< IFrame > frame;
     *  Recti rect;
     *
     *  // setting and getting frame
     *  client[ IFrameClient::Frame ] = frame;
     *  frame = client[ IFrameClient::Frame ];
     *
     *  // notifing about change
     *  client[ IFrameClient::Move ]( rect );
     *
     *  \endcode
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider, IEntity < IFrameClient < IContainer, IGraphicsDesignerClient
     *                           ^^^^^^^^^^^^
     *  \endcode
     */
    aloe__interface( IFrameClient )
    {
        aloe__iid( IFrameClient );

        aloe__prop( IFrameClient, Frame
                , ____, ____
                , get , put , pointer( IFrame )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IFrameClient, Move
                , ____
                , tuple1(
                    arg( rect, In, type( Recti ))
                    ));
    };

    aloe__runtime_prop( IFrameClient, Frame );
    aloe__runtime_method( IFrameClient, Move );


    /*! \brief MeshCell interface
     *
     *  This interface gives means to alter parameters
     *  used by IMeshLayout to calculate IFrame::Bound.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IFrame < IMeshCell
     *                           ^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IMeshCell )
    {
        aloe__iid( IMeshCell );

        aloe__prop( IMeshCell, Mesh
                , ____, ____
                , get , put , pointer( IMeshLayout )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshCell, HLineStart
                , ____, ____
                , get , put , pointer( IMeshLine )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshCell, VLineStart
                , ____, ____
                , get , put , pointer( IMeshLine )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshCell, HLineEnd
                , ____, ____
                , get , put , pointer( IMeshLine )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshCell, VLineEnd
                , ____, ____
                , get , put , pointer( IMeshLine )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshCell, Padding
                , ____, ____
                , get , put , tuple4( type( Int ), type( Int ), type( Int ), type( Int ) )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshCell, Offset
                , ____, ____
                , get , put , type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshCell, MinSize
                , ____, ____
                , get , put , type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshCell, MaxSize
                , ____, ____
                , get , put , type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IMeshCell, Mesh );
    aloe__runtime_prop( IMeshCell, HLineStart );
    aloe__runtime_prop( IMeshCell, VLineStart );
    aloe__runtime_prop( IMeshCell, HLineEnd);
    aloe__runtime_prop( IMeshCell, VLineEnd );
    aloe__runtime_prop( IMeshCell, Padding );
    aloe__runtime_prop( IMeshCell, Offset );
    aloe__runtime_prop( IMeshCell, MinSize );
    aloe__runtime_prop( IMeshCell, MaxSize );


    /*! \brief MeshLine interface
     *
     *  This interface gives means to alter parameters
     *  used by IMeshLayout to calculate IFrame::Bound.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IMeshLine
     *                  ^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IMeshLine )
    {
        aloe__iid( IMeshLine );

        aloe__prop( IMeshLine, Mesh
                , ____, ____
                , get , put , pointer( IMeshLayout )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshLine, Placement
                , ____, ____
                , get , put , tuple2( type( Int ), type( Int ))
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshLine, Offset
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshLine, Cells
                , ____, ____
                , get , put , array_of_pointer( IMeshCell )
                , append, type( Bool ), pointer( IMeshCell )
                , remove, type( Bool ), pointer( IMeshCell )
                , ____, ____, ____ );

        aloe__prop( IMeshLine, CellsFrom
                , ____, ____
                , get , ____, array_of_pointer( IMeshCell )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshLine, CellsTo
                , ____, ____
                , get , ____, array_of_pointer( IMeshCell ) 
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshLine, Position
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IMeshLine, Mesh );
    aloe__runtime_prop( IMeshLine, Placement );
    aloe__runtime_prop( IMeshLine, Offset );
    aloe__runtime_prop( IMeshLine, Cells );
    aloe__runtime_prop( IMeshLine, CellsFrom );
    aloe__runtime_prop( IMeshLine, CellsTo );
    aloe__runtime_prop( IMeshLine, Position );


    /*! \brief MeshLayout interface
     *
     *  This interface gives means to calculate IFrame::Bound.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IMeshLayout
     *                  ^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IMeshLayout )
    {
        aloe__iid( IMeshLayout );

        aloe__prop( IMeshLayout, Frame
                , ____, ____
                , get , put , pointer( IFrame )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IMeshLayout, HLines
                , ____, ____
                , get , put , array_of_pointer( IMeshLine )
                , append, type( Bool ), pointer( IMeshLine )
                , remove, type( Bool ), pointer( IMeshLine )
                , ____, ____, ____ );

        aloe__prop( IMeshLayout, VLines
                , ____, ____
                , get , put , array_of_pointer( IMeshLine )
                , append, type( Bool ), pointer( IMeshLine )
                , remove, type( Bool ), pointer( IMeshLine )
                , ____, ____, ____ );

        aloe__prop( IMeshLayout, Cells
                , ____, ____
                , get , put , array_of_pointer( IMeshCell )
                , append, type( Bool ), pointer( IMeshCell )
                , remove, type( Bool ), pointer( IMeshCell )
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IMeshLayout, Frame );
    aloe__runtime_prop( IMeshLayout, HLines );
    aloe__runtime_prop( IMeshLayout, VLines );
    aloe__runtime_prop( IMeshLayout, Cells );


    /*! \brief TargetCell interface
     *
     *  This interface gives means to alter parameters
     *  used by ITargetLayout to calculate IFrame::Bound.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IFrame < ITargetCell
     *                           ^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( ITargetCell )
    {
        aloe__iid( ITargetCell );

        aloe__prop( ITargetCell, Target
                , ____, ____
                , get , put , pointer( ITargetLayout )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ITargetCell, Radius
                , ____, ____
                , get , put , pointer( ITargetRadialLine )
                , ____, ____, ____ 
                , ____, ____, ____ 
                , ____, ____, ____ );
        
        aloe__prop( ITargetCell, Distance
                , ____, ____
                , get , put , pointer( ITargetDistanceLine )
                , ____, ____, ____ 
                , ____, ____, ____ 
                , ____, ____, ____ );
    };

    aloe__runtime_prop( ITargetCell, Target );
    aloe__runtime_prop( ITargetCell, Radius );
    aloe__runtime_prop( ITargetCell, Distance );


    /*! \brief TargetRadialLine interface
     *
     *  This interface gives means to alter parameters
     *  used by ITargetLayout to calculate IFrame::Bound.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < ITargetRadialLine
     *                  ^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( ITargetRadialLine )
    {
        aloe__iid( ITargetRadialLine );

        aloe__prop( ITargetRadialLine, Target
                , ____, ____
                , get , put , pointer( ITargetLayout )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ITargetRadialLine, Angle
                , ____, ____
                , get , put , type( Float )
                , ____, ____, ____ 
                , ____, ____, ____ 
                , ____, ____, ____ );
    };

    aloe__runtime_prop( ITargetRadialLine, Target );
    aloe__runtime_prop( ITargetRadialLine, Angle );
    aloe__runtime_prop( ITargetRadialLine, Cells );
    
    /*! \brief TargetDistanceLine interface
     *
     *  This interface gives means to alter parameters
     *  used by ITargetLayout to calculate IFrame::Bound.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < ITargetDistanceLine
     *                  ^^^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( ITargetDistanceLine )
    {
        aloe__iid( ITargetDistanceLine );

        aloe__prop( ITargetDistanceLine, Target
                , ____, ____
                , get , put , pointer( ITargetLayout )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ITargetDistanceLine, Distance
                , ____, ____
                , get , put , type( Float )
                , ____, ____, ____ 
                , ____, ____, ____ 
                , ____, ____, ____ );
    };
    
    aloe__runtime_prop( ITargetDistanceLine, Target );
    aloe__runtime_prop( ITargetDistanceLine, Angle );
    aloe__runtime_prop( ITargetDistanceLine, Cells );


    /*! \brief TargetLayout interface
     *
     *  This interface gives means to calculate IFrame::Bound.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < ITargetLayout
     *                  ^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( ITargetLayout )
    {
        aloe__iid( ITargetLayout );

        aloe__prop( ITargetLayout, Frame
                , ____, ____
                , get , put , pointer( IFrame )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( ITargetLayout, RadialLines
                , ____, ____
                , get , put , array_of_pointer( ITargetRadialLine )
                , append, type( Bool ), pointer( ITargetRadialLine )
                , remove, type( Bool ), pointer( ITargetRadialLine )
                , ____, ____, ____ );

        aloe__prop( ITargetLayout, DistanceLines
                , ____, ____
                , get , put , array_of_pointer( ITargetDistanceLine )
                , append, type( Bool ), pointer( ITargetDistanceLine )
                , remove, type( Bool ), pointer( ITargetDistanceLine )
                , ____, ____, ____ );

        aloe__prop( ITargetLayout, Cells
                , ____, ____
                , get , put , array_of_pointer( ITargetCell )
                , append, type( Bool ), pointer( ITargetCell )
                , remove, type( Bool ), pointer( ITargetCell )
                , ____, ____, ____ );

    };
        
    aloe__runtime_prop( ITargetLayout, Frame );
    aloe__runtime_prop( ITargetLayout, RadialLines );
    aloe__runtime_prop( ITargetLayout, DistanceLines );
    aloe__runtime_prop( ITargetLayout, Cells );



    /*! \brief Font interface
     *
     *  This interface gives access to font attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IFont
     *                  ^^^^^
     *  \endcode
     *
     */
    aloe__interface( IFont )
    {
        aloe__iid( IFont );
        
        aloe__prop( IFont, Family
                , ____, ____
                , get , put , type( String )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IFont, Size
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IFont, Weight
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IFont, Slant
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IFont, Encoding
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IFont, Rotation
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    /*! \brief Pen interface
     *
     *  This interface gives access to pen attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IPen
     *                  ^^^^^
     *  \endcode
     *
     */
    aloe__interface( IPen )
    {
        aloe__iid( IPen );
        
        aloe__prop( IPen, Width
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IPen, Color
                , ____, ____
                , get , put , type( Color32 )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IPen, Style
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    /*! \brief Brush interface
     *
     *  This interface gives access to brush attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IBrush
     *                  ^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IBrush )
    {
        aloe__iid( IBrush );
        
        aloe__prop( IBrush, Color
                , ____, ____
                , get , put , type( Color32 )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IBrush, Style
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    /*! \brief CursorShape interface
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < ICursorShape
     *                  ^^^^^^^^^^^^
     *  \endcode
     */
    aloe__interface( ICursorShape )
    {
        aloe__iid( ICursorShape );
        
        aloe__prop( ICursorShape, PixelRect
                , ____, ____
                , get , put , pointer( IRasterRect )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( ICursorShape, HotSpot
                , ____, ____
                , get , put , type( Point2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( ICursorShape, PixelRect );
    aloe__runtime_prop( ICursorShape, HotSpot );
    
    /*! \brief Drawing interface
     *
     *  This interface gives means to insert graphic items into graphics design.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IDrawing
     *                  ^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IDrawing )
    {
        aloe__iid( IDrawing );
        
        enum Flags
        {
            F_FILL      = 0x00000001, //!< filled shape
            F_ROTATE    = 0x00000002, //!< rotate before blit
            F_BLEND     = 0x00000004, //!< use opacity
            F_COLOR     = 0x00000008, //!< use color
            F_MULTILINE = 0x00000010, //!< allow multiple lines (text)
            F_BREAKWORD = 0x00000020, //!< wrap using break word rule
            F_ELLIPSIS  = 0x00000040, //!< add '...' if text doesn't fit in bound
            F_LEFT      = 0x00000100, //!< align to left
            F_RIGHT     = 0x00000200, //!< align to right
            F_CENTER    = 0x00000300, //!< align to center (horizontal)
            F_JUSTIFY   = 0x00000400, //!< justify to full width (if possible)
            F_TOP       = 0x00001000, //!< align to top
            F_BOTTOM    = 0x00002000, //!< align to bottom
            F_MIDDLE    = 0x00003000, //!< align to middle (vertical)
        };

        
        aloe__method( IDrawing, DrawSector
                , type( SizeType )
                , tuple2(
                    arg( sector, In, type( Sectori )),
                    arg( pen, In, type( SizeType ))
                    ));
        
        aloe__method( IDrawing, DrawPolyline
                , type( SizeType )
                , tuple2(
                    arg( points, In, array_of( type( Point2i ))),
                    arg( pen, In, type( SizeType ))
                    ));
        
        aloe__method( IDrawing, DrawPolygon
                , type( SizeType )
                , tuple3(
                    arg( points, In, array_of( type( Point2i ))),
                    arg( pen, In, type( SizeType )),
                    arg( brush, In, type( SizeType ))
                    ));
        
        aloe__method( IDrawing, DrawRectangle
                , type( SizeType )
                , tuple3(
                    arg( rect, In, type( Recti )),
                    arg( pen, In, type( SizeType )),
                    arg( brush, In, type( SizeType ))
                    ));

        aloe__method( IDrawing, DrawString
                , type( SizeType )
                , tuple5(
                    arg( text, In, type( String )),
                    arg( rect, In, type( Recti )),
                    arg( font, In, type( SizeType )),
                    arg( color, In, tuple2( type( Color32 ), type( Color32 ) )),
                    arg( flags, In, type( Long ))
                    ));
        
        aloe__method( IDrawing, DrawRaster
                , type( SizeType )
                , tuple6(
                    arg( dstRect, In, type( Recti )),
                    arg( raster, In, pointer( IRaster )),
                    arg( srcRect, In, type( Recti )),
                    arg( color, In, type( Color32 )),
                    arg( rotation, In, type( Int )),
                    arg( flags, In, type( Long ))
                    ));

        aloe__method( IDrawing, DrawSubDesign
                , type( SizeType )
                , tuple2(
                    arg( dstRect, In, type( Recti )),
                    arg( subDesign, In, type( SizeType ))
                    ));
    };


    /*! \brief GraphicsDesign interface
     *
     *  This interface gives means to manage layout of graphics.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesign
     *                  ^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IGraphicsDesign )
    {
        aloe__iid( IGraphicsDesign );

        aloe__method( IGraphicsDesign, CreateDesign
                , pointer( IGraphicsDesign )
                , tuple1(
                    arg( bound, In, type( Recti ))
                    ));
        
        aloe__prop( IGraphicsDesign, Bound
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IGraphicsDesign, Parent
                , ____, ____
                , get , put , pointer( IGraphicsDesign )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, SubDesigns
                , ____, ____
                , get , put , array_of_pointer( IGraphicsDesign )
                , append, type( SizeType ), pointer( IGraphicsDesign )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, Pen
                , map , type( SizeType )
                , get , put , pointer( IPen )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, Pens
                , ____, ____
                , get , put , array_of_pointer( IPen )
                , append, type( SizeType ), pointer( IPen )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, Brush
                , map , type( SizeType )
                , get , put , pointer( IBrush )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IGraphicsDesign, Brushes
                , ____, ____
                , get , put , array_of_pointer( IBrush )
                , append, type( SizeType ), pointer( IBrush )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, Font
                , map , type( SizeType )
                , get , put , pointer( IFont )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, Fonts
                , ____, ____
                , get , put , array_of_pointer( IFont )
                , append, type( SizeType ), pointer( IFont )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, Item
                , map , type( SizeType )
                , get , put , pointer( IGraphicsDesignItem )
                , ____, ____, ____ 
                , ____, ____, ____ 
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, Items
                , ____, ____
                , get , put , array_of_pointer( IGraphicsDesignItem )
                , append, type( SizeType ), pointer( IGraphicsDesignItem )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
    };


    /*! \brief GraphicsDesignItem interface
     *
     *  This interface gives means to access graphic item attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem
     *                  ^^^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IGraphicsDesignItem )
    {
        aloe__iid( IGraphicsDesignItem );

        aloe__prop( IGraphicsDesignItem, Design
                , ____, ____
                , get , put , pointer( IGraphicsDesign )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesignItem, Bound
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };
    
    /*! \brief ShapeDesign interface
     *
     *  This interface gives means to access shape attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem < IShapeDesign
     *                                        ^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IShapeDesign )
    {
        aloe__iid( IShapeDesign );

        aloe__prop( IShapeDesign, Pen
                , ____, ____
                , get , put , type( SizeType )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };
    
    /*! \brief ShapeDesign2 interface
     *
     *  This interface gives means to access filled shape attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem < IShapeDesign < IShapeDesign2
     *                                                       ^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IShapeDesign2 )
    {
        aloe__iid( IShapeDesign2 );

        aloe__prop( IShapeDesign2, Brush
                , ____, ____
                , get , put , type( SizeType )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    /*! \brief SectorDesign interface
     *
     *  This interface gives means to access sector attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem < IShapeDesign < ISectorDesign
     *                                                       ^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( ISectorDesign )
    {
        aloe__iid( ISectorDesign );
        
        aloe__prop( ISectorDesign, Start
                , ____, ____
                , get , put , type( Point2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ISectorDesign, End
                , ____, ____
                , get , put , type( Point2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ISectorDesign, From
                , ____, ____
                , get , put , type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ISectorDesign, To
                , ____, ____
                , get , put , type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    /*! \brief PolylineDesign interface
     *
     *  This interface gives means to access polyline attributes.
     *
     *  \note The first entry in Vectors array is the distance from origin (0,0).
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem < IShapeDesign < IPolylineDesign
     *                                                       ^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IPolylineDesign )
    {
        aloe__iid( IPolylineDesign );
        
        aloe__prop( IPolylineDesign, Points
                , ____, ____
                , get , put , array_of( type( Point2i ))
                , append, type( SizeType ), type( Point2i )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
        
        aloe__prop( IPolylineDesign, Vectors
                , ____, ____
                , get , put , array_of( type( Vector2i ))
                , append, type( SizeType ), type( Vector2i )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
    };

    /*! \brief PolygonDesign interface
     *
     *  This interface gives means to access polygon attributes.
     *
     *  \note The first entry in Vectors array is the distance from origin (0,0).
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem < IShapeDesign < IShapeDesign2 < IPolygonDesign
     *                                                                       ^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IPolygonDesign )
    {
        aloe__iid( IPolygonDesign );
        
        aloe__prop( IPolygonDesign, Points
                , ____, ____
                , get , put , array_of( type( Point2i ))
                , append, type( SizeType ), type( Point2i )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
        
        aloe__prop( IPolygonDesign, Vectors
                , ____, ____
                , get , put , array_of( type( Vector2i ))
                , append, type( SizeType ), type( Vector2i )
                , remove, type( Bool ), type( SizeType )
                , ____, ____, ____ );
        
    };


    /*! \brief RectangleDesign interface
     *
     *  This interface gives means to access rectangle attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem < IShapeDesign < IShapeDesign2 < IRectangleDesign
     *                                                                       ^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IRectangleDesign )
    {
        aloe__iid( IRectangleDesign );
    };

    /*! \brief BlitDesign interface
     *
     *  This interface gives means to access blit attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem < IBlitDesign
     *                                        ^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IBlitDesign )
    {
        aloe__iid( IBlitDesign );

        aloe__prop( IBlitDesign, Raster
                , ____, ____
                , get , put , pointer( IRaster )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IBlitDesign, Rect
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IBlitDesign, Color
                , ____, ____
                , get , put , type( Color32 )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IBlitDesign, Rotation
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IBlitDesign, Flags
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    /*! \brief TextDesign interface
     *
     *  This interface gives means to access text attributes.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IGraphicsDesignItem < ITextDesign
     *                                        ^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( ITextDesign )
    {
        aloe__iid( ITextDesign );

        aloe__prop( ITextDesign, Text
                , ____, ____
                , get , put , type( String )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ITextDesign, Font
                , ____, ____
                , get , put , type( SizeType )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( ITextDesign, Flags
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };


    /*! \brief SubDesign interface
     */
    aloe__interface( ISubDesign )
    {
        aloe__iid( ISubDesign );

        aloe__prop( ISubDesign, SubDesign
                , ____, ____
                , get , put , type( SizeType )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };


    /*! \brief UserInputState interface
     *
     *  This interface gives means to query the state of input devices such as keyboard/mouse.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInputState
     *                  ^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInputState )
    {
        aloe__iid( IUserInputState );

        aloe__prop( IUserInputState, CursorPos
                , ____, ____
                , get , put , type( Point2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IUserInputState, CursorShape
                , ____, ____
                , get , put , pointer( ICursorShape )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IUserInputState, MouseCapture
                , ____, ____
                , get , put , pointer( IWindow )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IUserInputState, KeyState
                , map , type( Int )
                , get , put , type( UByte )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IUserInputState, KeyboardState
                , ____, ____
                , get , put , array_of( type( UByte ))
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IUserInputState, KeyboardCapture
                , ____, ____
                , get , put , pointer( IWindow )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IUserInputState, CursorPos );
    aloe__runtime_prop( IUserInputState, CursorShape );
    aloe__runtime_prop( IUserInputState, KeyState );
    
    /*! \brief UserInputState2 interface
     *
     *  This interface gives means to query the state of input devices such as joystick/gamepad.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInputState2
     *                  ^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInputState2 )
    {
        aloe__iid( IUserInputState2 );

        aloe__prop( IUserInputState2, AxisState
                , map , type( Int )
                , get , put , type( Float )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IUserInputState2, ButtonState
                , map , type( Int )
                , get , put , type( Bool )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IUserInputState2, AxisState );
    aloe__runtime_prop( IUserInputState2, ButtonState );

    /*! \brief UserInputEvents interface
     *
     *  This interface is used to notify about keyboard input events.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInputEvents
     *                  ^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInputEvents )
    {
        aloe__iid( IUserInputEvents );

        aloe__method( IUserInputEvents, Key
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( index, In, type( Int )),
                    arg( pressed, In, type( Bool ))
                    ));
        
        aloe__method( IUserInputEvents, Focus
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( flags, In, type( Long ))
                    ));
    };
    
    aloe__runtime_method( IUserInputEvents, Key );
    aloe__runtime_method( IUserInputEvents, Focus );
    
    /*! \brief UserInputEvents2 interface
     *
     *  This interface is used to notify about input events from
     *  - joystick/gamepad
     *  - mouse in direct access mode.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInputEvents2
     *                  ^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInputEvents2 )
    {
        aloe__iid( IUserInputEvents );

        aloe__method( IUserInputEvents2, Axis
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( index, In, type( Int )),
                    arg( pos, In, type( Float ))
                    ));

        aloe__method( IUserInputEvents2, Button
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( index, In, type( Int )),
                    arg( pressed, In, type( Bool ))
                    ));
    };
    
    aloe__runtime_method( IUserInputEvents2, Axis );
    aloe__runtime_method( IUserInputEvents2, Button );

    /*! \brief UserInterfaceState interface
     *
     *  This interface gives means to query the state of user interface items.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInterfaceState
     *                  ^^^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInterfaceState )
    {
        aloe__iid( IUserInterfaceState );
        
        aloe__prop( IUserInterfaceState, Visible
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IUserInterfaceState, Enabled
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };
    
    aloe__runtime_prop( IUserInterfaceState, Visible );
    aloe__runtime_prop( IUserInterfaceState, Enabled );
    
    /*! \brief UserInterfaceState2 interface
     *
     *  This interface gives means to query the focus state of user interface items.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInterfaceState2
     *                  ^^^^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInterfaceState2 )
    {
        aloe__iid( IUserInterfaceState2 );
        
        aloe__prop( IUserInterfaceState2, Focussed
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };
    
    aloe__runtime_prop( IUserInterfaceState2, Focussed );

    /*! \brief UserInterfaceEvents interface
     *
     *  This interface is used to notify about changes in user interface.
     *
     *  These events are related to UI item appearance.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInterfaceEvents
     *                  ^^^^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInterfaceEvents )
    {
        aloe__iid( IUserInterfaceEvents );
        
        aloe__method( IUserInterfaceEvents, Close
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( flags, In, type( Long ))
                    ));
        
        aloe__method( IUserInterfaceEvents, Show
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( flags, In, type( Long ))
                    ));
        
        aloe__method( IUserInterfaceEvents, Activate
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( flags, In, type( Long ))
                    ));
        
        aloe__method( IUserInterfaceEvents, Move
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( bound, In, type( Recti )),
                    arg( flags, In, type( Long ))
                    ));
        
        aloe__method( IUserInterfaceEvents, Paint
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( device, In, pointer( IGraphicDevice )),
                    arg( rect, In, type( Recti ))
                    ));
    };
    
    aloe__runtime_method( IUserInterfaceEvents, Close );
    aloe__runtime_method( IUserInterfaceEvents, Show );
    aloe__runtime_method( IUserInterfaceEvents, Activate );
    aloe__runtime_method( IUserInterfaceEvents, Move );
    aloe__runtime_method( IUserInterfaceEvents, Paint );
    
    aloe__interface( IUserInterfaceEvents1 )
    {
        aloe__iid( IUserInterfaceEvents1 );
        
        aloe__method( IUserInterfaceEvents1, Dirty
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( bound, In, type( Recti ))
                    ));
        
        aloe__method( IUserInterfaceEvents1, Design
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( design, In, pointer( IGraphicsDesign ))
                    ));
    };
    
    aloe__runtime_method( IUserInterfaceEvents1, Dirty );
    aloe__runtime_method( IUserInterfaceEvents1, Design );

    /*! \brief UserInterfaceEvents2 interface
     *
     *  This interface is used to notify about mouse in UI items.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInterfaceEvents2
     *                  ^^^^^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInterfaceEvents2 )
    {
        aloe__iid( IUserInterfaceEvents2 );
        
        aloe__method( IUserInterfaceEvents2, Motion
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( pos, In, type( Point2i ))
                    ));
        
        aloe__method( IUserInterfaceEvents2, Hover
                , type( Bool )
                , tuple1(
                    arg( sender, In, pointer( IProvider ))
                    ));
        
        aloe__method( IUserInterfaceEvents2, Leave
                , type( Bool )
                , tuple1(
                    arg( sender, In, pointer( IProvider ))
                    ));
        
    };
    
    aloe__runtime_method( IUserInterfaceEvents2, Motion );
    aloe__runtime_method( IUserInterfaceEvents2, Hover );
    aloe__runtime_method( IUserInterfaceEvents2, Leave );


    /*! \brief UserInterfaceEvents3 interface
     *
     *  This interface is used to notify about clicks on UI items.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInterfaceEvents3
     *                  ^^^^^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInterfaceEvents3 )
    {
        aloe__iid( IUserInterfaceEvents3 );
        
        aloe__method( IUserInterfaceEvents3, Press
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( button, In, type( Int )),
                    arg( pos, In, type( Point2i ))
                    ));
        
        aloe__method( IUserInterfaceEvents3, Release
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( button, In, type( Int )),
                    arg( pos, In, type( Point2i ))
                    ));
        
        aloe__method( IUserInterfaceEvents3, Click
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( button, In, type( Int )),
                    arg( pos, In, type( Point2i ))
                    ));
        
        aloe__method( IUserInterfaceEvents3, DoubleClick
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( button, In, type( Int )),
                    arg( pos, In, type( Point2i ))
                    ));
    };
    
    aloe__runtime_method( IUserInterfaceEvents3, Press );
    aloe__runtime_method( IUserInterfaceEvents3, Release );
    aloe__runtime_method( IUserInterfaceEvents3, Click );
    aloe__runtime_method( IUserInterfaceEvents3, DoubleClick );


    /*! \brief UserInterfaceEvents4 interface
     *
     *  This interface is used to notify about drag'n'drop on UI items.
     *
     *  Run-Time interfaces relation:
     *  \code
     *      IProvider < IUserInterfaceEvents4
     *                  ^^^^^^^^^^^^^^^^^^^^^
     *  \endcode
     *
     */
    aloe__interface( IUserInterfaceEvents4 )
    {
        aloe__iid( IUserInterfaceEvents4 );
        
        aloe__method( IUserInterfaceEvents4, DragStart
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( button, In, type( Int )),
                    arg( pos, In, type( Point2i ))
                    ));
        
        aloe__method( IUserInterfaceEvents4, DragContinue
                , type( Bool )
                , tuple4(
                    arg( sender, In, pointer( IProvider )),
                    arg( button, In, type( Int )),
                    arg( pos, In, type( Point2i )),
                    arg( vector, In, type( Vector2i ))
                    ));
        
        aloe__method( IUserInterfaceEvents4, DragEnd
                , type( Bool )
                , tuple3(
                    arg( sender, In, pointer( IProvider )),
                    arg( button, In, type( Int )),
                    arg( pos, In, type( Point2i ))
                    ));
    };
    
    aloe__runtime_method( IUserInterfaceEvents4, DragStart );
    aloe__runtime_method( IUserInterfaceEvents4, DragContinue );
    aloe__runtime_method( IUserInterfaceEvents4, DragEnd );

	namespace Utils {

		inline Utils::SmartPtr< IWindow > findOwnerWindow( Utils::SmartPtr<> obj )
		{
			while ( !!obj )
				aloe__try {

					return obj[ &IWindow::This ];

				} aloe__retry {

					obj = obj[ &IEntity::Container ].value();

				} aloe__retry {

					obj = Types::None();

				} aloe__finish;

			return Types::None();
		}

	};//Util

};//Aloe

#endif//ALOE_INCLUDED_ALOE_UI_H
