#ifndef ALOE_WIN32_SYSTEM
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'Win32System.cpp'."
#endif

namespace Aloe {
    namespace Win32 {
		struct CPropertyMap
			: Detail::Implementation
			< CPropertyMap
			, Detail::Interfaces< IPropertyMap >
			, Detail::Bases< Detail::CRefCount >
			, 0x1001 >
		{
			typedef std::map< AutoObjectRef, AutoObjectRef > Map_t;
			Map_t m_map;
			
			aloe__prop_map_imp_put( IPropertyMap, Property, index, value )
			{
				m_map[ index ] = value;
			}
			
			aloe__prop_map_imp_get( IPropertyMap, Property, index )
			{
				Map_t::iterator i = m_map.find( index );
				if ( i == m_map.end() )
				{
					//throw Errors::Error_BadArrayIndex();
					return ObjectRef();
				}
				return i->second;
			}
		};// CPropertyMap



        struct CFactory
            : Detail::Implementation
            < CFactory
            , Detail::Interfaces< IFactory, Win32::IWindowFactory, Win32::IMessageLoop, IUserInputState, IStorage >
            , Detail::Bases< Detail::CRefCount >
            , 0x1000 >
        {   
            HINSTANCE m_hInstance;
            DWORD m_lastError;
            typedef std::map< Types::String, Utils::SmartPtr< IFactory > > DictFactory_t;
            DictFactory_t m_dictFactory;

            ThisPtr __init__( HINSTANCE hInstance )
            {
                m_lastError = 0L;
                m_hInstance = hInstance;
                return Super::__init__();
            }

            aloe__prop_map_imp_get( IFactory, IdOfName, csName )
            {
                typedef std::map< Types::String, Types::Identifier > IdMap_t;
                static IdMap_t s_idMap;
                static Types::Long s_next = 0x1000;

                IdMap_t::iterator found = s_idMap.find( csName );
                if ( found != s_idMap.end() )
                {
                    return found->second;
                }
                else {
                    Types::Identifier id( Types::LongPointer( ++s_next ));
                    s_idMap[ csName ] = id;
                    return id;
                }
            }

            aloe__method_imp( IFactory, Load, argv )
            {
                aloe__extract1( IFactory, Load, args, argv, library );

                return false;
            }
            
            aloe__property_imp_put( IFactory, Parent, parent )
            {
            }

            aloe__property_imp_get( IFactory, Parent )
            {
                return Types::None();
            }

            aloe__prop_map_imp_put( IFactory, Create, index, cons )
            {
                m_dictFactory[ index ] = cons;
            };

            aloe__prop_map_imp_get( IFactory, Create, index )
            {
                DictFactory_t::iterator found = m_dictFactory.find( index );
                if ( found != m_dictFactory.end() )
                {
                    return found->second;
                }
                else {
                    return Types::None();
                }
            };

            aloe__prop_map_imp_call( IFactory, Create, index, argv )
            {
                aloe__extract1( IFactory, Create, args, argv, propMap );
                    
                aloe__try {

                    if ( index == aloe__string("PropertyMap") )
                    {
                        return (new CPropertyMap)->__init__();
                    }
                    else if ( index == aloe__string("Pen") )
                    {
                        if ( !propMap )
                        {
                            return (new CPen)->__init__();
                        }
						Types::Color32 color = propMap[ &IPropertyMap::Property ][ aloe__string("Pen.Color") ].value();
						Types::Long style = propMap[ &IPropertyMap::Property ][ aloe__string("Pen.Style") ].value();
						Types::Long width = propMap[ &IPropertyMap::Property ][ aloe__string("Pen.Width") ].value();

                        LOGPEN logPen;
                        logPen.lopnStyle = style;
                        logPen.lopnWidth.x = width;
                        logPen.lopnWidth.y = width;
                        logPen.lopnColor = RGB( color.Redub(), color.Greenub(), color.Blueub() );

                        ::HPEN hPen = ::CreatePenIndirect( &logPen );
                        return ( new CGDIPen )->__init__( hPen, true );
                    }
                    else if ( index == aloe__string("Brush") )
                    {
                        if ( !propMap )
                        {
                            return (new CBrush)->__init__();
                        }
						
						Types::Color32 color = propMap[ &IPropertyMap::Property ][ aloe__string("Brush.Color") ].value();
						Types::Long style = propMap[ &IPropertyMap::Property ][ aloe__string("Brush.Style") ].value();

                        LOGBRUSH logBrush;
                        logBrush.lbStyle = style;
                        logBrush.lbColor = RGB( color.Redub(), color.Greenub(), color.Blueub() );

                        switch( logBrush.lbStyle )
                        {
                            case BS_DIBPATTERN:
                            case BS_DIBPATTERN8X8:
                            case BS_DIBPATTERNPT:
								{
									Utils::SmartPtr< IRaster > bitmap;
									if ( propMap[ &IPropertyMap::Property ][ aloe__string("Brush.Bitmap") ].value().get( &bitmap ))
									{
										logBrush.lbHatch = Utils::copyCast< ::LONG >( bitmap[ &IBitmap::HBitmap ].value() );
									}
								}
                                break;
                            default:
								{
									Types::Long lh;
									if (propMap[ &IPropertyMap::Property ][ aloe__string("Brush.Hatch") ].value().get( &lh ))
									{
										logBrush.lbHatch = lh;
									}
								}
                        };

                        HBRUSH hBr = ::CreateBrushIndirect( &logBrush );
                        return ( new CGDIBrush )->__init__( hBr, true );
                    }
                    else if ( index == aloe__string("Font") )
                    {
                        if ( !propMap )
                        {
                            return (new CFont)->__init__();
                        }
                    }
                    else if ( index == aloe__string("Bitmap") )
                    {
                        if  ( !propMap )
                        {
                            return (new CBitmap)->__init__( Types::None() );
                        }

                        Types::String name;
                        Types::Int res = 0;
                        LPCWSTR lpszName = NULL;
                        int cxDesired = 0;
                        int cyDesired = 0;
                        UINT uType = IMAGE_BITMAP;
                        UINT fuLoad = 0;

                        propMap[ &IPropertyMap::Property ][ aloe__string("Bitmap.Resource") ].value().get( &res );
                        
                        if ( !res )
                        {
                            propMap[ &IPropertyMap::Property ][ aloe__string("Bitmap.Resource") ].value().get( &name );
                            lpszName = (WCHAR*)(name.c_str());
                        }
                        else {
                            lpszName = MAKEINTRESOURCE( res );
                        }

                        if ( !res && name.empty() )
                        {
                            propMap[ &IPropertyMap::Property ][ aloe__string("Bitmap.Filename") ].value().get( &name );
                            lpszName = (WCHAR*)(name.c_str());
                            fuLoad |= LR_LOADFROMFILE;
                            fuLoad |= LR_CREATEDIBSECTION;
                        }

                        ::HBITMAP hBmp = (::HBITMAP)::LoadImageW( m_hInstance, lpszName, uType, cxDesired, cyDesired, fuLoad );

                        return (new CBitmap)->__init__( (new CGDIBitmap)->__init__( hBmp, true ) );
                    }
                    else if ( index == aloe__string("GraphicDevice") )
                    {
                        if  ( !propMap )
                        {
                            ::HDC hRootDc = ::GetDC( (::HWND)NULL );
                            ::HDC hDc = ::CreateCompatibleDC( hRootDc );
                            ::ReleaseDC( (::HWND)NULL, hRootDc );
                            return (new CDevContext)->__init__( hDc, (::HWND)NULL, true );
                        }
                    }
                    else if ( index == aloe__string("Cursor") )
                    {
                        if  ( !propMap )
                        {
                            return (new CCursorShape)->__init__( Types::None() );
                        }

                        Types::String name;
                        Types::Int res = 0;
                        LPCWSTR lpszName = NULL;
                        Types::Bool bFromFile = false;
                        ::HINSTANCE hInstance = (::HINSTANCE)NULL;
                        ::HCURSOR hCursor = (::HCURSOR)NULL;

                        propMap[ &IPropertyMap::Property ][ aloe__string("Cursor.SystemResource") ].value().get( &res );

                        if ( !res )
                        {
                            propMap[ &IPropertyMap::Property ][ aloe__string("Cursor.Resource") ].value().get( &res );
                            
                            if ( !res )
                            {
                                propMap[ &IPropertyMap::Property ][ aloe__string("Cursor.Resource") ].value().get( &name );
                                if ( !name.empty() )
                                {
                                    lpszName = (WCHAR*)(name.c_str());
                                }
                            }
                            else {
                                lpszName = MAKEINTRESOURCE( res );
                            }
                            
                            if ( lpszName )
                            {
                                hInstance = m_hInstance;
                            }
                        }
                        else {
                            lpszName = Utils::copyCast< LPCWSTR >( res );
                        }

                        if ( lpszName )
                        {
                            hCursor = ::LoadCursor( hInstance, lpszName );
                        }
                        else
                        {
                            propMap[ &IPropertyMap::Property ][ aloe__string("Cursor.Filename") ].value().get( &name );
                            lpszName = (WCHAR*)(name.c_str());
                            bFromFile = true;
                       
                            hCursor = ::LoadCursorFromFile( lpszName );
                        }
                            
                        return (new CCursorShape)->__init__( (new CGDICursor)->__init__( hCursor, true ) );
                        
                    }
                    else if ( index == aloe__string("Region") )
                    {
                        return (new CRegion)->__init__( Types::None() );
                    }

                    DictFactory_t::iterator found = m_dictFactory.find( index );
                    if ( found != m_dictFactory.end() )
                    {
                        return found->second[ &IFactory::Create ][ index ]( argv );
                    }
                    else {
                        return Types::None();
                    }
                
                } aloe__finish;
                        
                return Types::None();
            };
            
            aloe__method_imp( Win32::IWindowFactory, CreateWindow, argv )
            {
                aloe__extract8( Win32::IWindowFactory, CreateWindow, args, argv, className, classStyle,
                        windowName, windowStyle, windowStyleEx, windowRect, windowParent, windowMenu );

                ::HWND hWnd = (::HWND)NULL;
                
                ::WNDCLASSEX wcex;
                ::ZeroMemory( &wcex, sizeof( WNDCLASSEX ));
                
                wcex.cbSize         = sizeof( WNDCLASSEX ); 
                wcex.style          = classStyle;
                wcex.lpfnWndProc    = (WNDPROC)MessageProc;
                wcex.cbClsExtra     = 0;
                wcex.cbWndExtra     = 0;
                wcex.hInstance      = m_hInstance;
				wcex.hCursor        = ::LoadCursor((::HINSTANCE)NULL, IDC_ARROW);
                wcex.hbrBackground  = (HBRUSH)(COLOR_BACKGROUND+1);
                wcex.lpszMenuName   = 0;
                wcex.lpszClassName  = (WCHAR*)(className.c_str());
        
                if ( !RegisterClassEx( &wcex ))
                {
                    m_lastError = GetLastError();
		    return Types::None();
                }

                hWnd = ::CreateWindowEx( windowStyleEx, (WCHAR*)(className.c_str()), (WCHAR*)(windowName.c_str()), windowStyle,
                        windowRect.upperLeft().x, windowRect.upperLeft().y, windowRect.width(), windowRect.height(),
                        windowParent, windowMenu, m_hInstance, NULL );

                if ( !hWnd )
                {
                    m_lastError = GetLastError();
		    return Types::None();
                }

                ::ShowWindow( hWnd, SW_SHOW );

                return ( new CWindow )->__init__( hWnd );
            }

            static LRESULT WINAPI MessageProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
            {
                if ( CWindow *pWnd = CWindow::GetObject( hWnd ))
                {
                    return pWnd->ProcessMessage( uMsg, wParam, lParam );
                }
                else {
                    return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
                }
            }

            aloe__method_imp( Win32::IMessageLoop, Run, argv )
            {
                ::MSG msg;

                while ( ::GetMessage( &msg, 0, 0, 0 ))
                {
                    ::TranslateMessage( &msg );
                    ::DispatchMessage( &msg );
                };
                
                return 0L;
            }


            // IUserInputState

            aloe__property_imp_put( IUserInputState, CursorPos, pos )
            {
                ::SetCursorPos( pos.x, pos.y );
            }

            aloe__property_imp_get( IUserInputState, CursorPos )
            {
                Types::Point2i pos;
                ::GetCursorPos( (LPPOINT)&pos );
                return pos;
            }
            
            aloe__property_imp_put( IUserInputState, CursorShape, shape )
            {
                ::SetCursor( shape[ &Win32::ICursor::HCursor ] );
            }
            
            aloe__property_imp_get( IUserInputState, CursorShape )
            {
                ::HCURSOR hCursor = ::GetCursor();
                Utils::SmartPtr< Win32::ICursor > out;
                if ( !CGDIObject::FindObject( out, (::HGDIOBJ)hCursor ))
                {
                    out = ( new CGDICursor )->__init__( hCursor );
                }
                return ( new CCursorShape )->__init__( out.UseRawPtrCast() );
            }

            aloe__property_imp_put( IUserInputState, MouseCapture, capture )
            {
                ::SetCapture( capture[ &Win32::IWindow::HWnd ] );
            }
            
            aloe__property_imp_get( IUserInputState, MouseCapture )
            {
                if ( CWindow *window = CWindow::GetObject( ::GetCapture() ))
                {
                    return window->__self__();
                }

                return Types::None();
            }

            aloe__prop_map_imp_put( IUserInputState, KeyState, index, value )
            {
                // cannot set keyboard state
            }

            aloe__prop_map_imp_get( IUserInputState, KeyState, index )
            {
                DWORD dwState = ::GetKeyState( index );
                if ( dwState & 0x8000 )
                {
                    return true;
                }
                else {
                    return false;
                }
            }
            
            aloe__property_imp_put( IUserInputState, KeyboardState, array )
            {
                if ( array.size() < 256 )
                {
                    Types::SizeType nSize = array.size();
                    Utils::ArrayOf< Types::UByte > current( 256 );
                    ::GetKeyboardState( current.begin() );
                    std::copy( array.begin(), array.begin() + nSize, current.begin() );
                    ::SetKeyboardState( array.begin() );
                }
                else
                {
                    ::SetKeyboardState( array.begin() );
                }
            }
            
            aloe__property_imp_get( IUserInputState, KeyboardState)
            {
                Utils::ArrayOf< Types::UByte > array( 256 );
                ::GetKeyboardState( array.begin() );
                return array;
            }

            aloe__property_imp_put( IUserInputState, KeyboardCapture, capture )
            {
                ::SetFocus( capture[ &Win32::IWindow::HWnd ] );
            }
            
            aloe__property_imp_get( IUserInputState, KeyboardCapture )
            {
                if ( CWindow *window = CWindow::GetObject( ::GetFocus() ))
                {
                    return window->__self__();
                }

                return Types::None();
            }

            //
            //
            // IStorage
            //
            //

            Types::Bool isDirSeparator( Types::WideChar wc )
            {
                return (wc == L'\\' || wc == L'/' );
            }

            Types::NCWideStr FormatPath( Types::NCWideStr buffer, Types::CWideStr path )
            {
                _FormatPath( buffer, path );
                
                for ( int i=0; i < MAX_PATH && buffer[i]; ++i )
                {
                    if ( isDirSeparator( buffer[i] ))
                    {
                        buffer[i] = L'\\';
                    }
                }

                return buffer;
            }
            
            Types::NCWideStr _FormatPath( Types::NCWideStr buffer, Types::CWideStr path )
            {
                // find colon to determine if it's absolute or relative path
                for ( int i=0; path[i]; ++i )
                {
                    if ( L':' == path[i] )
                    {
                        wcscat_s( buffer, MAX_PATH, path );
                        return buffer;
                    }
                }

                int iLevel = 0;

                for ( ;; )
                {
                    if ( *path == L'.' )
                    {
                        ++path;
                        if ( *path == L'.' )
                        {
                            ++iLevel;
                            ++path;
                            if ( isDirSeparator( *path ))
                            {
                                ++path;
                                continue;
                            }
                            buffer[0] = 0; //< error - after '../' was expected
                            return buffer;
                        }
                        if ( isDirSeparator( *path ))
                        {
                            ++path;
                            continue;
                        }
                        buffer[0] = 0; //< error - after './' was expected
                        return buffer;
                    }
                    if ( isDirSeparator( *path ))
                    {
                        ++path;
                        continue;
                    }
                    break;
                }
                
                // append current module path before 'path'
                ::DWORD dwLen = ::GetModuleFileName( m_hInstance, (WCHAR*)buffer, MAX_PATH );
                for ( ::DWORD dwPos = dwLen; dwPos > 0; --dwPos )
                {
                    if ( isDirSeparator( buffer[ dwPos ] ))
                    {
                        buffer[ dwPos + 1 ] = 0x0;
                        if ( 0 == iLevel )
                        {
                            break;
                        }
                        --iLevel;
                    }
                }

                if ( 0 != iLevel )
                {
                    buffer[0] = 0;
                }
                else
                {
                    wcscat_s( buffer, MAX_PATH, path );
                }

                return buffer;
            }
            
            aloe__method_imp( IStorage, Create, argv )
            {
                aloe__extract2( IStorage, Create, args, argv, path, flags );
                    
                Types::WideChar buffer[ MAX_PATH ] = {0,};
                ::BOOL bOk = FALSE;

                if ( flags & F_STORAGE )
                {
                    bOk = ::CreateDirectory( (WCHAR*)FormatPath( buffer, path.c_str()), NULL );
                }
                else
                {
                    ::DWORD dwAccess = 0;
                    ::DWORD dwShareMode = 0;
                    ::DWORD dwCreationDisposition = 0;

                    if ( flags & F_CLEAN )
                    {
                        dwAccess = GENERIC_WRITE;
                        dwShareMode = FILE_SHARE_WRITE;
                        dwCreationDisposition = CREATE_ALWAYS | TRUNCATE_EXISTING;
                    }
                    else if ( flags & F_APPEND )
                    {
                        dwAccess = GENERIC_WRITE;
                        dwShareMode = FILE_SHARE_WRITE;
                        dwCreationDisposition = OPEN_ALWAYS;
                    }
                    else
                    {
                        dwAccess = GENERIC_READ;
                        dwShareMode = FILE_SHARE_READ;
                        dwCreationDisposition = OPEN_EXISTING;
                    }

                    return (new CFile)->__init__( FormatPath( buffer, path.c_str() )
			    , dwAccess, dwShareMode, dwCreationDisposition, 0, flags );
                }

                return Types::None();
            }
        
            aloe__method_imp( IStorage, Exists, argv )
            {
                aloe__extract2( IStorage, Exists, args, argv, path, flags );
                    
                Types::WideChar buffer[ MAX_PATH ] = {0,};
                ::WIN32_FIND_DATA findData;
                ::HANDLE hFind = ::FindFirstFile( (WCHAR*)FormatPath( buffer, path.c_str() ), &findData );
                if ( INVALID_HANDLE_VALUE == hFind )
                {
                    return false;
                }
                do {

                    if (( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == ( flags & F_STORAGE ))
                    {
                        ::FindClose( hFind );
                        return true;
                    }

                } while ( ::FindNextFile( hFind, &findData ));

                ::FindClose( hFind );
                return false;
            }
        
             aloe__method_imp( IStorage, Remove, argv )
             {
                aloe__extract2( IStorage, Remove, args, argv, path, flags );

                ::BOOL bOk = FALSE;
                    
                Types::WideChar buffer[ MAX_PATH ] = {0,};
                
                if ( flags & F_STORAGE )
                {
                    bOk = ::RemoveDirectory( (WCHAR*)FormatPath( buffer, path.c_str() ));
                }
                else
                {
                    bOk = ::DeleteFile( (WCHAR*)FormatPath( buffer, path.c_str() ));
                }

                return Types::None();
             }

            aloe__method_imp( IStorage, Enumerate, argv )
            {
                aloe__extract1( IStorage, Enumerate, args, argv, path );
                
                Types::WideChar buffer[ MAX_PATH ] = {0,};

                return (new CDirectoryEnum)->__init__( __self__(), Types::String( FormatPath( buffer, path.c_str() )));
            }
            
        };//CFactory
    };//Win32
};//Aloe
