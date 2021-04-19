#ifndef ALOE_WIN32_SYSTEM
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'Win32System.cpp'."
#endif

namespace Aloe {
    namespace Win32 {
        struct CWindow
            : Detail::Implementation
            < CWindow
            , Detail::Interfaces< IEventSource, Aloe::IWindow, Win32::IWindow, Win32::ILayeredWindow, IFrame, IContainer >
            , Detail::Bases< Detail::CRefCount >
            , 0x1002 >
        {
            typedef std::map< ::HWND, CWindow * > DictWindows_t;
            static DictWindows_t s_dictWindows;

            ::HWND m_hWnd;
            Types::Bool m_bMouseOver;
            Types::Bool m_bFocussed;
            Types::Point2i m_lastMotionPos;
            Types::Bool m_layerPendingCommit;
            Types::UByte m_layerOpacity;
            Types::Color32 m_layerCK;
            Types::Long m_layerFlags;
            
            typedef std::set< Types::Int > SetOfDragButtons_t;
            SetOfDragButtons_t m_setOfDragButtons;

            CWindow() : m_hWnd(0)
                , m_bMouseOver(0)
                , m_bFocussed(0)
                , m_layerFlags(0)
                , m_layerPendingCommit(0)
            {}
            
            ThisPtr __init__( ::HWND hWnd )
            {
                s_dictWindows[ hWnd ] = this;
                m_hWnd = hWnd;
                return Super::__init__();
            }

            ~CWindow()
            {
                if ( RemoveObject( m_hWnd ))
                {
                    Close( Types::None() );
                }
            }

            CWindow * RemoveObject( ::HWND hWnd )
            {
                DictWindows_t::iterator iter = s_dictWindows.find( hWnd );
                if ( iter != s_dictWindows.end() )
                {
                    CWindow *pWnd = iter->second;
                    s_dictWindows.erase( iter );
                    return pWnd;
                }
                else {
                    return NULL;
                }
            }

            static CWindow * GetObject( ::HWND hWnd )
            {
                DictWindows_t::iterator iter = s_dictWindows.find( hWnd );
                if ( iter != s_dictWindows.end() )
                {
                    return iter->second;
                }
                else {
                    return NULL;
                }
            }

            LRESULT ProcessMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
            {
                __self__()[ &IEventSource::Raise ][ &Win32::IWindowEvents::Event ]( __self__(),
                        Utils::copyCast< Types::Long >( uMsg ),
                        Utils::copyCast< Types::LongPointer >( wParam ),
                        Utils::copyCast< Types::LongPointer >( lParam )
                        );

                Types::Bool isButton = false;
                Types::Bool isDown = false;
                Types::Bool isDblClick = false;
                Types::Bool isSize = false;
                Types::Bool isFocus = false;

                switch( uMsg )
                {
                    case WM_CREATE:
                        {
                        }
                        break;
                    case WM_DESTROY:
                        {
                            if ( RemoveObject( m_hWnd ))
                            {
                                if( s_dictWindows.empty() )
                                {
                                    ::PostQuitMessage(0);
                                }
                            }
                            __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Close ]( __self__() );
                            __self__()[ &IEventSource::Raise ][ &Aloe::IUserInterfaceEvents::Close ]( __self__(), 0 );
                        }
                        break;
                    case WM_ACTIVATE:
                        {
                            Types::Bool bActive = ( LOWORD( wParam ) > 0 );
                            __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Activate ]( __self__(), bActive );
                            __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents::Activate ]( __self__(), bActive );
                        }
                        break;
                    case WM_SETFOCUS:
                        isFocus = true;
                    case WM_KILLFOCUS:
                        {
                            m_bFocussed = isFocus;
                            __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Focus ]( __self__(), isFocus );
                            __self__()[ &IEventSource::Raise ][ &IUserInputEvents::Focus ]( __self__(), isFocus );
                        }
                        break;
                    case WM_SHOWWINDOW:
                        {
                            Types::Long flags = (wParam > 0 ? true : false);
                            // lParam is 0 for call to ShowWindow() or:
                            //  SW_OTHERUNZOOM
                            //  SW_OTHERZOOM
                            //  SW_PARENTCLOSING 
                            //  SW_PARENTOPENING
                            //
                            __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Show ]( __self__(), flags );
                            __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents::Show ]( __self__(), flags );
                        }
                        break;

                    case WM_SIZE:
                        isSize = true;
                    case WM_MOVE:
                        {
                            Types::Recti rect = get_FrameRect();
                            Types::Long flags = ( isSize ? 1 : 0 );
                            __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Move ]( __self__(), rect, flags );
                            __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents::Move ]( __self__(), rect, flags );
                            Types::Recti clientRect = get_ClientRect();
                            for ( SetOfClients_t::iterator iter = m_setOfClients.begin(); iter != m_setOfClients.end(); ++iter )
                            {
                                (*iter)[ &IFrameClient::Move ]( clientRect );
                            }
                        }
                        break;

                    case WM_KEYDOWN:
                        isDown = true;
                    case WM_KEYUP:
                        {
                            __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Key ]( __self__(),
                                    Utils::copyCast< Types::Long >( wParam ), isDown );
                            
                            __self__()[ &IEventSource::Raise ][ &IUserInputEvents::Key ]( __self__(),
                                    Utils::copyCast< Types::Long >( wParam ), isDown );
                        }
                        break;

                    case WM_LBUTTONDBLCLK:
                    case WM_RBUTTONDBLCLK:
                    case WM_MBUTTONDBLCLK:
                        isDblClick = true;
                    case WM_LBUTTONDOWN:
                    case WM_RBUTTONDOWN:
                    case WM_MBUTTONDOWN:
                        isDown = true;
                    case WM_LBUTTONUP:
                    case WM_RBUTTONUP:
                    case WM_MBUTTONUP:
                        isButton = true;
                    case WM_MOUSEMOVE:
                        {
                            ::POINT pt, ptScreen;
                            ::GetCursorPos( &ptScreen );
                            pt = ptScreen;
                            ::ScreenToClient( m_hWnd, &pt );
#if 0                            
                            if ( uMsg == WM_MOUSEMOVE )
                            {
                                wchar_t buffer[100];
                                swprintf( buffer, L"WM_MOUSEMOVE screen=(%i %i) pt=(%i %i)\n", ptScreen.x, ptScreen.y, pt.x, pt.y );
                                ::OutputDebugString( buffer );
                            }
#endif
                            
                            Types::Point2i pos( pt.x, pt.y );

                            if ( !isButton )
                            {
                                __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Motion ]( __self__(), pos );
                            
                                for ( SetOfDragButtons_t::iterator iter = m_setOfDragButtons.begin(); iter != m_setOfDragButtons.end(); ++iter )
                                {
                                    Types::Int iButton = *iter;
                                    __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents4::DragContinue ]( __self__(), iButton, pos );
                                }
                                
                                if ( !m_bMouseOver )
                                {
                                    m_bMouseOver = true;
                                    ::TRACKMOUSEEVENT trackInfo;
                                    std::memset( &trackInfo, 0, sizeof( ::TRACKMOUSEEVENT ));
                                    trackInfo.cbSize = sizeof( ::TRACKMOUSEEVENT );
                                    trackInfo.dwFlags = TME_LEAVE;
                                    trackInfo.hwndTrack = m_hWnd;
                                    trackInfo.dwHoverTime = 0;
                                    ::TrackMouseEvent( &trackInfo );
                                    __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Hover ]( __self__() );
                                }
                                else
                                {
                                    __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Motion ]( __self__(), pos );
                                }

                                m_lastMotionPos = pos;
                                break;
                            }
                            else
                            {
                                Types::Long btnNo = 0;

                                switch( uMsg )
                                {
                                    case WM_RBUTTONDBLCLK:
                                    case WM_RBUTTONDOWN:
                                    case WM_RBUTTONUP: btnNo = 1; break;
                                    case WM_MBUTTONDBLCLK:
                                    case WM_MBUTTONDOWN:
                                    case WM_MBUTTONUP: btnNo = 2; break;
                                };

                                if ( !isDblClick )
                                {
                                    while( true )
                                    {
                                        __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Button ]( __self__(), pos, btnNo, isDown );
                                        if ( isDown )
                                        {
                                            __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Press ]( __self__(), btnNo, pos );
                                            ::UpdateWindow( m_hWnd );
                                            if ( ::DragDetect( m_hWnd, ptScreen ))
                                            {
                                                m_setOfDragButtons.insert( btnNo );
                                                __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents4::DragStart ]( __self__(), btnNo, pos );
                                            }
                                            else
                                            {
                                                isDown = false;
                                                continue;
                                            }
                                            ::SetCapture( m_hWnd );
                                        }
                                        else
                                        {
                                            SetOfDragButtons_t::iterator iterButton = m_setOfDragButtons.find( btnNo );
                                            if ( m_setOfDragButtons.end() != iterButton )
                                            {
                                                m_setOfDragButtons.erase( iterButton );
                                                __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents4::DragEnd ]( __self__(), btnNo, pos );
                                            }
                                            else {
                                                __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Click ]( __self__(), btnNo, pos );
                                            }
                                            
                                            __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Release ]( __self__(), btnNo, pos );
                                                
                                            if ( m_setOfDragButtons.empty() )
                                            {
                                                ::ReleaseCapture();
                                            }
                                        }

                                        break;
                                    };
                                }
                                else {
                                    __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::DoubleClick ]( __self__(), pos, btnNo );
                                    __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents3::DoubleClick ]( __self__(), btnNo, pos );
                                }
                            }
                            
                        };
                        break;
                    case WM_MOUSELEAVE:
                        {
                            if ( m_bMouseOver )
                            {
                                m_bMouseOver = false;
                                ::TRACKMOUSEEVENT trackInfo;
                                std::memset( &trackInfo, 0, sizeof( ::TRACKMOUSEEVENT ));
                                trackInfo.cbSize = sizeof( ::TRACKMOUSEEVENT );
                                trackInfo.dwFlags = TME_CANCEL;
                                trackInfo.hwndTrack = m_hWnd;
                                trackInfo.dwHoverTime = 0;
                                ::TrackMouseEvent( &trackInfo );
                                __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Leave ]( __self__() );
                            }
                        }
                        break;
                    case WM_CAPTURECHANGED:
                        {
                            Utils::SmartPtr<> capture;
                            if ( CWindow *pWnd = GetObject( (::HWND)lParam ))
                            {
                                capture = pWnd->__self__();
                            }
                            __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::LostCapture ]( __self__(), capture );
                            return 1;
                        }
                        break;

                    case WM_ERASEBKGND:
                        {
                            return 1;
                        }
                        break;

                    case WM_PAINT:
                        {
                            PAINTSTRUCT ps;

                            if ( ::HDC hDc = ::BeginPaint( m_hWnd, &ps ))
                            {
                                Utils::SmartPtr< CDevContext > dev = ( new CDevContext )->__init__( hDc );

                                __self__()[ &IEventSource::Raise ][ &Aloe::IWindowEvents::Paint ]( __self__(),
                                        dev, reinterpret_cast< Types::Recti & >( ps.rcPaint ));
                                
                                __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents::Paint ]( __self__(),
                                        dev, reinterpret_cast< Types::Recti & >( ps.rcPaint ));

                                ::EndPaint( m_hWnd, &ps );
                                
                                if ( m_layerPendingCommit )
                                {
                                    CommitLayeredAttributes();
                                }
                            
                                return 0;
                            }
                        }
                        break;
                };

                return ::DefWindowProc( m_hWnd, uMsg, wParam, lParam );
            }
            
            //
            // IEventSource
            //

	    typedef std::set< Utils::SmartPtr<> > SetOfListeners_t;
            SetOfListeners_t m_setOfListeners;

            aloe__property_imp_append( IEventSource, Listeners, listener )
            {
                return m_setOfListeners.insert( listener ).second;
            }
            
            aloe__property_imp_remove( IEventSource, Listeners, listener )
            {
                SetOfListeners_t::iterator found = m_setOfListeners.find( listener );
                if ( found != m_setOfListeners.end() )
                {
                    m_setOfListeners.erase( found );
                    return true;
                }
                else {
                    return false;
                }
            }

            aloe__method_imp( IEventSource, RaiseEvent, event )
            {
                for ( SetOfListeners_t::iterator i = m_setOfListeners.begin(); i != m_setOfListeners.end(); ++i )
                {
                    if ( !event->Invoke( *i ))
                    {
                        break;
                    }
                }
                return Types::None();
            }

            //
            // IWindow
            //

            aloe__property_imp_put( Aloe::IWindow, FrameRect, rect )
            {
                ::MoveWindow( m_hWnd, rect.upperLeft().x, rect.upperLeft().y, rect.width(), rect.height(), TRUE );
            }

            aloe__property_imp_put( Aloe::IWindow, ClientRect, rect )
            {
                ::RECT w32RectClient;
                ::GetClientRect( m_hWnd, &w32RectClient );
                int dx = (w32RectClient.right - w32RectClient.left) - rect.width();
                int dy = (w32RectClient.bottom - w32RectClient.top) - rect.height();
                
                ::RECT w32Rect;
                ::GetWindowRect( m_hWnd, &w32Rect );
                w32Rect.left   += rect.upperLeft().x;
                w32Rect.top    += rect.upperLeft().y;
                w32Rect.right  += rect.upperLeft().x - dx;
                w32Rect.bottom += rect.upperLeft().y - dy;

                ::MoveWindow( m_hWnd, w32Rect.left, w32Rect.top, w32Rect.right - w32Rect.left, w32Rect.bottom - w32Rect.top, TRUE );
            }
            
            aloe__property_imp_get( Aloe::IWindow, FrameRect )
            {
                ::RECT w32Rect;
                ::GetWindowRect( m_hWnd, &w32Rect );
                
                Types::Recti rect;
                rect.upperLeft()   = Types::Point2i( w32Rect.left, w32Rect.top );
                rect.bottomRight() = Types::Point2i( w32Rect.right, w32Rect.bottom );

                return rect;
            }
            
            aloe__property_imp_get( Aloe::IWindow, ClientRect )
            {
                ::RECT w32Rect;
                ::GetClientRect( m_hWnd, &w32Rect );
                
                Types::Recti rect;
                rect.upperLeft()   = Types::Point2i( w32Rect.left, w32Rect.top );
                rect.bottomRight() = Types::Point2i( w32Rect.right, w32Rect.bottom );

                return rect;
            }
            
            aloe__method_imp( Aloe::IWindow, Close, argv )
            {
                ::PostMessage( m_hWnd, WM_CLOSE, 0, 0 );
                return Types::None();
            }

            aloe__property_imp_put( Aloe::IWindow, Region, region )
            {
                if ( !region )
                {
                    ::SetWindowRgn( m_hWnd, (::HRGN)NULL, FALSE );
                }
                else
                {
                    ::SetWindowRgn( m_hWnd, region[ &Win32::IRegion::HRgn ], TRUE );
                }
            }

            aloe__property_imp_get( Aloe::IWindow, Region )
            {
                ::HRGN hRgn = ::CreateRectRgn(0,0,0,0);
                ::GetWindowRgn( m_hWnd, hRgn );
                return (new CRegion)->__init__( (new CGDIRegion)->__init__( hRgn, true ));
            }

            aloe__property_imp_append( Aloe::IWindow, DirtyRects, rect )
            {
                ::InvalidateRect( m_hWnd, (LPRECT)&rect, FALSE );
                return Types::None();
            }
            
            aloe__property_imp_remove( Aloe::IWindow, DirtyRects, rect )
            {
                ::ValidateRect( m_hWnd, (LPRECT)&rect );
                return Types::None();
            }

            aloe__property_imp_append( Aloe::IWindow, DirtyRegions, region )
            {
                ::InvalidateRgn( m_hWnd, region[ &Win32::IRegion::HRgn ], FALSE );
                return Types::None();
            }
            
            aloe__property_imp_remove( Aloe::IWindow, DirtyRegions, region )
            {
                ::ValidateRgn( m_hWnd, region[ &Win32::IRegion::HRgn ] );
                return Types::None();
            }

            aloe__method_imp( Aloe::IWindow, Update, argv )
            {
                ::UpdateWindow( m_hWnd );
                return Types::None();
            }

            aloe__method_imp( Aloe::IWindow, RedrawRect, argv )
            {
                aloe__extract2( Aloe::IWindow, RedrawRect, args, argv, rect, flags );
                
                ::RedrawWindow( m_hWnd, (LPRECT)&rect, (::HRGN)NULL, flags );
                return Types::None();
            }

            aloe__method_imp( Aloe::IWindow, RedrawRegion, argv )
            {
                aloe__extract2( Aloe::IWindow, RedrawRegion, args, argv, region, flags );
                
                ::RedrawWindow( m_hWnd, NULL, region[ &Win32::IRegion::HRgn ], flags );
                return Types::None();
            }

            //
            // Win32::IWindow
            //

            aloe__property_imp_put( Win32::IWindow, Style, style )
            {
                SetWindowLong( m_hWnd, GWL_STYLE, style );
            }
            
            aloe__property_imp_put( Win32::IWindow, ExStyle, exStyle )
            {
                SetWindowLong( m_hWnd, GWL_EXSTYLE, exStyle );
            }
            
            aloe__property_imp_put( Win32::IWindow, UserData, data )
            {
                SetWindowLong( m_hWnd, GWL_USERDATA, data );
            }
           
            aloe__prop_map_imp_put( Win32::IWindow, Long, idx, value )
            {
                SetWindowLong( m_hWnd, idx, value );
            }
            
            aloe__property_imp_get( Win32::IWindow, Class )
            {
                return  ( new CWindowClass )->__init__( m_hWnd );
            }
            
            aloe__property_imp_get( Win32::IWindow, Style )
            {
                return GetWindowLong( m_hWnd, GWL_STYLE );
            }
            
            aloe__property_imp_get( Win32::IWindow, ExStyle )
            {
                return GetWindowLong( m_hWnd, GWL_EXSTYLE );
            }
            
            aloe__property_imp_get( Win32::IWindow, UserData )
            {
                return GetWindowLong( m_hWnd, GWL_USERDATA );
            }
           
            aloe__prop_map_imp_get( Win32::IWindow, Long, idx )
            {
                return GetWindowLong( m_hWnd, idx );
            }
            
            aloe__property_imp_get( Win32::IWindow, HWnd )
            {
                return m_hWnd;
            }

            //
            // Win32::ILayeredWindow
            //

            aloe__property_imp_put( Win32::ILayeredWindow, Opacity, opacity )
            {
                m_layerOpacity = opacity;
                m_layerPendingCommit = true;
            }

            aloe__property_imp_get( Win32::ILayeredWindow, Opacity )
            {
                return m_layerOpacity;
            }

            aloe__property_imp_put( Win32::ILayeredWindow, ColorKey, ck )
            {
                m_layerCK = ck;
                m_layerPendingCommit = true;
            }

            aloe__property_imp_get( Win32::ILayeredWindow, ColorKey )
            {
                return m_layerCK;
            }

            aloe__property_imp_put( Win32::ILayeredWindow, Flags, flags )
            {
                m_layerFlags = flags;
                m_layerPendingCommit = true;
            }

            aloe__property_imp_get( Win32::ILayeredWindow, Flags )
            {
                return m_layerFlags;
            }

            aloe__method_imp( Win32::ILayeredWindow, Commit, argv )
            {
                return CommitLayeredAttributes();
            }

            bool CommitLayeredAttributes()
            {
                ::LONG lExStyle = ::GetWindowLong( m_hWnd, GWL_EXSTYLE );
                m_layerPendingCommit = false;
                
                if ( !m_layerFlags )
                {
                    if ( lExStyle & WS_EX_LAYERED )
                    {
                        ::SetWindowLong( m_hWnd, GWL_EXSTYLE, lExStyle & (~WS_EX_LAYERED) );
                    }
                }
                else
                {
                    if (!( lExStyle & WS_EX_LAYERED ))
                    {
                        ::SetWindowLong( m_hWnd, GWL_EXSTYLE, lExStyle | WS_EX_LAYERED );
                    }
                    
#ifdef WIN32
                    ::BOOL bOk = ::SetLayeredWindowAttributes( m_hWnd,
                            RGB( m_layerCK.Redub(), m_layerCK.Greenub(), m_layerCK.Blueub() ),
                            m_layerOpacity, m_layerFlags );
                    
		    return (bOk == TRUE);
#endif

                }

                return true;
            }

            //
            // IContainer
            //
	    
            typedef std::set< Utils::SmartPtr<> > SetOfObjects_t;
            SetOfObjects_t m_setOfObjects;

            aloe__property_imp_get( IContainer, Objects )
            {
                Utils::VectorOf< Utils::SmartPtr<> > array;
                
                for ( SetOfObjects_t::iterator iter = m_setOfObjects.begin(); iter != m_setOfObjects.end(); ++iter )
                {
                    array.push_back( *iter );
                }

                return array.tight_array();
            }

            aloe__property_imp_put( IContainer, Objects, objects )
            {
                m_setOfObjects.clear();
                
                for ( size_t i = 0, n = objects.size(); i < n; ++i )
                {
                    m_setOfObjects.insert( objects[i] );
                }
            }
            
            aloe__property_imp_append( IContainer, Objects, object )
            {
                return m_setOfObjects.insert( object ).second;
            }
            
            aloe__property_imp_remove( IContainer, Objects, object )
            {
                SetOfObjects_t::iterator iter = m_setOfObjects.find( object );
                if ( iter != m_setOfObjects.end() )
                {
                    m_setOfObjects.erase( iter );
                    return true;
                }
                else {
                    return false;
                }
            }

            aloe__prop_map_imp_get( IContainer, ObjectByName, index )
            {
                for ( SetOfObjects_t::iterator iter = m_setOfObjects.begin(); iter != m_setOfObjects.end(); ++iter )
                {
                    Utils::SmartPtr< IEntity > entity;
                    if ( entity.QueryFrom( *iter ))
                    {
                        Types::String name = entity[ &IEntity::Name ];
                        if ( index == name )
                        {
                            return entity;
                        }
                    }
                }

                return Types::None();
            }
            
            aloe__prop_map_imp_get( IContainer, ObjectByPoint, index )
            {
                for ( SetOfObjects_t::iterator iter = m_setOfObjects.begin(); iter != m_setOfObjects.end(); ++iter )
                {
                    Utils::SmartPtr< IFrameClient > client;
                    if ( client.QueryFrom( *iter ))
                    {
                        Types::Recti bound = client[ &IFrameClient::Frame ][ IFrame::Bound ];
                        if ( bound.isPointInside( index ))
                        {
                            return client;
                        }
                    }
                }
                
                return Types::None();
            }

            //
            // IFrame
            //
            
            typedef std::set< Utils::SmartPtr< IFrameClient > > SetOfClients_t;
            SetOfClients_t m_setOfClients;
            
            aloe__property_imp_put( IFrame, Bound, bound )
            {
                return put_ClientRect( bound );
            }
            
            aloe__property_imp_get( IFrame, Bound )
            {
                return get_ClientRect();
            }
            
            aloe__property_imp_put( IFrame, Parent, parent )
            {
                // not allowed!
            }
            
            aloe__property_imp_get( IFrame, Parent )
            {
                return Types::None();
            }

            aloe__property_imp_get( IFrame, Clients )
            {
                Utils::VectorOf< Utils::SmartPtr< IFrameClient > > array;
                
                for ( SetOfClients_t::iterator iter = m_setOfClients.begin(); iter != m_setOfClients.end(); ++iter )
                {
                    array.push_back( *iter );
                }

                return array.tight_array();
            }

            aloe__property_imp_put( IFrame, Clients, clients )
            {
                m_setOfClients.clear();
                
                for ( size_t i = 0, n = clients.size(); i < n; ++i )
                {
                    m_setOfClients.insert( clients[i] );
                }
            }
            
            aloe__property_imp_append( IFrame, Clients, client )
            {
                return m_setOfClients.insert( client ).second;
            }
            
            aloe__property_imp_remove( IFrame, Clients, client )
            {
                SetOfClients_t::iterator iter = m_setOfClients.find( client );
                if ( iter != m_setOfClients.end() )
                {
                    m_setOfClients.erase( iter );
                    return true;
                }
                else {
                    return false;
                }
            }
            

        };//CWindow
    };//Win32
};//Aloe
