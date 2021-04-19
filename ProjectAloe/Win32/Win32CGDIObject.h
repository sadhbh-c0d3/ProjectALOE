
#ifndef ALOE_WIN32_SYSTEM
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'Win32System.cpp'."
#endif

namespace Aloe {
    namespace Win32 {
        struct CGDIObject
            : Detail::Implementation
            < CGDIObject
            , Detail::Interfaces< Win32::IGDIObject >
            , Detail::CRefCount
            , 0x5000 >
        {
            Types::Bool m_bOwn;
            ::HGDIOBJ   m_hGdiObject;

            typedef std::map< ::HGDIOBJ, CGDIObject * > DictGDIObjects_t;
            static DictGDIObjects_t s_dictObjects;

            template< class Ptr >
                static bool FindObject( Ptr &out, ::HGDIOBJ hGdiObject )
                {
                    DictGDIObjects_t::iterator iter = s_dictObjects.find( hGdiObject );
                    if ( iter != s_dictObjects.end() )
                    {
                        return out.QueryFrom( iter->second );
                    }
                    return false;
                }

            static void Remove( ::HGDIOBJ hGdiObject )
            {
                DictGDIObjects_t::iterator iter = s_dictObjects.find( hGdiObject );
                if ( iter != s_dictObjects.end() )
                {
                    s_dictObjects.erase( iter );
                }
            }

            ~CGDIObject()
            {
                if ( m_bOwn )
                {
                    ::DeleteObject( m_hGdiObject );
                }
                Remove( m_hGdiObject );
            }

            aloe__property_imp_get( Win32::IGDIObject, HGDIObject )
            {
                return m_hGdiObject;
            };

            void __init__( ::HGDIOBJ hGdiObject, Types::Bool bOwn )
            {
                m_bOwn = bOwn;
                m_hGdiObject = hGdiObject;
                s_dictObjects[ hGdiObject ] = this;
            }

        };// CGDIObject
        
        
        struct CGDIBitmap
            : Detail::Implementation
            < CGDIBitmap
            , Detail::Interfaces< Win32::IBitmap >
            , Detail::Bases< CGDIObject >
            , 0x5001 >
        {
            ::HBITMAP m_hBitmap;

            ThisPtr __init__( ::HBITMAP hBitmap, Types::Bool bOwn = false )
            {
                CGDIObject::__init__( (HGDIOBJ)hBitmap, bOwn );

                m_hBitmap = hBitmap;
                return Super::__init__();
            }

            aloe__property_imp_get( Win32::IBitmap, HBitmap )
            {
                return m_hBitmap;
            }
        };// CGDIBitmap
       
        
        struct CGDIFont
            : Detail::Implementation
            < CGDIFont
            , Detail::Interfaces< Win32::IFont >
            , Detail::Bases< CGDIObject >
            , 0x5002 >
        {
            ::HFONT m_hFont;
            
            ThisPtr __init__( ::HFONT hFont, Types::Bool bOwn = false )
            {
                CGDIObject::__init__( (HGDIOBJ)hFont, bOwn );
                
                m_hFont = hFont;
                return Super::__init__();
            }

            aloe__property_imp_get( Win32::IFont, HFont )
            {
                return m_hFont;
            }
        };//CGDIFont
           

        struct CGDIPen
            : Detail::Implementation
            < CGDIPen
            , Detail::Interfaces< Win32::IPen >
            , Detail::Bases< CGDIObject >
            , 0x5003 >
        {
            ::HPEN m_hPen;
            
            ThisPtr __init__( ::HPEN hPen, Types::Bool bOwn = false )
            {
                CGDIObject::__init__( (HGDIOBJ)hPen, bOwn );
                
                m_hPen = hPen;
                return Super::__init__();
            }

            aloe__property_imp_get( Win32::IPen, HPen )
            {
                return m_hPen;
            }
        };// CGDIPen

        
        struct CGDIBrush
            : Detail::Implementation
            < CGDIBrush
            , Detail::Interfaces< Win32::IBrush >
            , Detail::Bases< CGDIObject >
            , 0x5004>
        {
            ::HBRUSH m_hBrush;
            
            ThisPtr __init__( ::HBRUSH hBrush, Types::Bool bOwn = false )
            {
                CGDIObject::__init__( (HGDIOBJ)hBrush, bOwn );
                
                m_hBrush = hBrush;
                return Super::__init__();
            }

            aloe__property_imp_get( Win32::IBrush, HBrush )
            {
                return m_hBrush;
            }
        };// CGDIBrush


        struct CGDICursor
            : Detail::Implementation
            < CGDICursor
            , Detail::Interfaces< Win32::ICursor >
            , Detail::Bases< CGDIObject >
            , 0x5005 >
        {
            ::HCURSOR m_hCursor;

            ~CGDICursor()
            {
                if ( m_bOwn )
                {
                    ::DestroyCursor( m_hCursor );
                    m_hCursor = (::HCURSOR)NULL;
                    m_bOwn = false;
                }
            }

            ThisPtr __init__( ::HCURSOR hCursor, Types::Bool bOwn = false )
            {
                CGDIObject::__init__( (HGDIOBJ)hCursor, bOwn );

                m_hCursor = hCursor;
                return Super::__init__();
            }
            
            aloe__property_imp_get( Win32::ICursor, HCursor )
            {
                return m_hCursor;
            }

        };// CGDICursor
        

        struct CGDIRegion
            : Detail::Implementation
            < CGDIRegion
            , Detail::Interfaces< Win32::IRegion >
            , Detail::Bases< CGDIObject >
            , 0x5006 >
        {
            ::HRGN m_hRgn;
            
            ThisPtr __init__( ::HRGN hRgn, Types::Bool bOwn )
            {
                CGDIObject::__init__( (HGDIOBJ)hRgn, bOwn );

                m_hRgn = hRgn;
                return Super::__init__();
            }

            aloe__property_imp_get( Win32::IRegion, HRgn )
            {
                return m_hRgn;
            }

        };// CGDIRegion
            
        
        struct CDevContext
            : Detail::Implementation
            < CDevContext
            , Detail::Interfaces< IGraphicDevice, Win32::IDevContext >
            , Detail::Bases< Detail::CRefCount >
            , 0x6000 >
        {
            ::HDC m_hDc;
            ::HWND m_hWnd;
            Types::Bool m_bOwn;
            Types::Int m_iState;
            Utils::SmartPtr< IRaster > m_delegateRaster;
            ::HBITMAP m_hDelegateBitmap;
            ::HBITMAP m_hOldBitmap;

            void SetDelegateRaster( const Utils::SmartPtr< IRaster > &raster );
            Utils::SmartPtr< IRaster > GetDelegateRaster();

            ~CDevContext()
            {
                ::RestoreDC( m_hDc, m_iState );
                
                m_delegateRaster = Types::None();
                m_hDelegateBitmap = (::HBITMAP)NULL;

                if ( m_bOwn )
                {
                    if ( m_hWnd )
                    {
                        ::ReleaseDC( m_hWnd, m_hDc );
                    }
                    else
                    {
                        ::DeleteDC( m_hDc );
                    }
                }
            }
            
            ThisPtr __init__( ::HDC hDc, ::HWND hWnd = (::HWND)NULL, Types::Bool bOwn = false )
            {
                m_hDc = hDc;
                m_hWnd = hWnd;
                m_bOwn = bOwn;
                m_hDelegateBitmap = (::HBITMAP)NULL;
                m_iState = SaveDC( m_hDc );
                m_hOldBitmap = (::HBITMAP)::GetCurrentObject( m_hDc, OBJ_BITMAP );
                return Super::__init__();
            }

            Utils::SmartPtr< IGraphicsDesign > DoCreateDesign( const Types::Recti &rect );

            aloe__method_imp( IGraphicDevice, CreateDesign, argv )
            {
                aloe__extract1( IGraphicDevice, CreateDesign, args, argv, rect );

                return DoCreateDesign( rect );
            }

            Types::Bool DoRenderDesign( const Utils::SmartPtr< IGraphicsDesign > &design, const Types::Recti &rect );
            
            aloe__method_imp( IGraphicDevice, RenderDesign, argv )
            {
                aloe__extract2( IGraphicDevice, RenderDesign, args, argv, design, rect );

                return DoRenderDesign( design, rect );
            }

            aloe__property_imp_put( IGraphicDevice, Raster, raster )
            {
                SetDelegateRaster( raster );
            }

            aloe__property_imp_get( IGraphicDevice, Raster )
            {
                return GetDelegateRaster();
            }

            aloe__property_imp_get( Win32::IDevContext, HDc )
            {
                return m_hDc;
            }

            aloe__method_imp( Win32::IDevContext, Save, argv )
            {
                int id = ::SaveDC( m_hDc );
                return id;
            }

            aloe__method_imp( Win32::IDevContext, Restore, argv )
            {
                aloe__extract1( Win32::IDevContext, Restore, args, argv, id );
                
                ::RestoreDC( m_hDc, id );
                m_delegateRaster = Types::None();
                m_hDelegateBitmap = (::HBITMAP)NULL;

                return Types::None();
            }

            aloe__property_imp_put( Win32::IDevContext, Bitmap, bitmap )
            {
                ::SelectObject( m_hDc, bitmap[ &IBitmap::HBitmap ] );
            }

            aloe__property_imp_put( Win32::IDevContext, Font, font )
            {
                ::SelectObject( m_hDc, font[ &IFont::HFont ] );
            }

            aloe__property_imp_put( Win32::IDevContext, Pen, pen )
            {
                ::SelectObject( m_hDc, pen[ &IPen::HPen ] );
            }

            aloe__property_imp_put( Win32::IDevContext, Brush, brush )
            {
                ::SelectObject( m_hDc, brush[ &IBrush::HBrush ] );
            }

            aloe__property_imp_get( Win32::IDevContext, Bitmap )
            {
                ::HGDIOBJ h = ::GetCurrentObject( m_hDc, OBJ_BITMAP );
                
                Utils::SmartPtr< Win32::IBitmap > out;
                if ( !CGDIObject::FindObject( out, h ))
                {
                    out = ( new CGDIBitmap )->__init__( (HBITMAP)h );
                }
                return out;
            }

            aloe__property_imp_get( Win32::IDevContext, Font )
            {
                ::HGDIOBJ h = ::GetCurrentObject( m_hDc, OBJ_FONT );
                
                Utils::SmartPtr< Win32::IFont > out;
                if ( !CGDIObject::FindObject( out, h ))
                {
                    out = ( new CGDIFont )->__init__( (HFONT)h );
                }
                return out;
            }

            aloe__property_imp_get( Win32::IDevContext, Pen )
            {
                ::HGDIOBJ h = ::GetCurrentObject( m_hDc, OBJ_PEN );
                
                Utils::SmartPtr< Win32::IPen > out;
                if ( !CGDIObject::FindObject( out, h ))
                {
                    out = ( new CGDIPen )->__init__( (HPEN)h );
                }
                return out;
            }

            aloe__property_imp_get( Win32::IDevContext, Brush )
            {
                ::HGDIOBJ h = ::GetCurrentObject( m_hDc, OBJ_BRUSH );
                
                Utils::SmartPtr< Win32::IBrush > out;
                if ( !CGDIObject::FindObject( out, h ))
                {
                    out = ( new CGDIBrush )->__init__( (HBRUSH)h );
                }
                return out;
            }

            aloe__method_imp( Win32::IDevContext, DrawRectangle, argv )
            {
                aloe__extract3( Win32::IDevContext, DrawRectangle, args, argv, rect, brush, pen );

                if ( !pen )
                {
                    ::FillRect( m_hDc, (LPRECT)&rect, brush[ &IBrush::HBrush ] );
                }
                else
                {
                    ::HGDIOBJ obj1 = ::SelectObject( m_hDc, brush[ &IBrush::HBrush ] );
                    ::HGDIOBJ obj2 = ::SelectObject( m_hDc, pen[ &IPen::HPen ] );
                    ::Rectangle( m_hDc, rect.x1, rect.y1, rect.x2, rect.y2 );
                    ::SelectObject( m_hDc, obj1 );
                    ::SelectObject( m_hDc, obj2 );
                }

                return Types::None();
            }

            aloe__method_imp( Win32::IDevContext, DrawPolygon, argv )
            {
                aloe__extract3( Win32::IDevContext, DrawPolygon, args, argv, points, brush, pen );
                
                ::HGDIOBJ obj1 = ::SelectObject( m_hDc, brush[ &IBrush::HBrush ] );
                ::HGDIOBJ obj2 = ::SelectObject( m_hDc, pen[ &IPen::HPen ] );
                ::Polygon( m_hDc, (LPPOINT)(points.begin()), (int)points.size() );
                ::SelectObject( m_hDc, obj1 );
                ::SelectObject( m_hDc, obj2 );

                return Types::None();
            }
            
            aloe__method_imp( Win32::IDevContext, DrawPolyline, argv )
            {
                aloe__extract2( Win32::IDevContext, DrawPolyline, args, argv, points, pen );
                
                ::HGDIOBJ obj2 = ::SelectObject( m_hDc, pen[ &IPen::HPen ] );
                ::Polyline( m_hDc, (LPPOINT)(points.begin()), (int)points.size() );
                ::SelectObject( m_hDc, obj2 );

                return Types::None();
            }

            aloe__method_imp( Win32::IDevContext, DrawSector, argv )
            {
                aloe__extract3( Win32::IDevContext, DrawSector, args, argv, point1, point2, pen );
                
                ::HGDIOBJ obj2 = ::SelectObject( m_hDc, pen[ &IPen::HPen ] );
                ::MoveToEx( m_hDc, point1.x, point1.y, NULL );
                ::LineTo( m_hDc, point2.x, point2.y );
                ::SelectObject( m_hDc, obj2 );

                return Types::None();
            }
            
            aloe__method_imp( Win32::IDevContext, DrawString, argv )
            {
                aloe__extract5( Win32::IDevContext, DrawString, args, argv, text, rect, font, color, flags );
                
                ::DRAWTEXTPARAMS dtp;
                ::ZeroMemory( &dtp, sizeof( ::DRAWTEXTPARAMS ));
                dtp.cbSize = sizeof( ::DRAWTEXTPARAMS );
                ::HGDIOBJ obj = ::SelectObject( m_hDc, font[ &IFont::HFont ] );
                ::COLORREF oldTC = CLR_INVALID;
                ::COLORREF oldBC = CLR_INVALID;
                int oldMode = 0;
                if ( aloe__1( color ).alpha > 0 )
                {
                    oldTC = ::SetTextColor( m_hDc, RGB( aloe__1( color ).red, aloe__1( color ).green, aloe__1( color ).blue ));
                }
                if ( aloe__2( color ).alpha > 0 )
                {
                    oldMode = ::SetBkMode( m_hDc, OPAQUE );
                    oldBC = ::SetBkColor( m_hDc, RGB( aloe__2( color ).red, aloe__2( color ).green, aloe__2( color ).blue ));
                }
                else {
                    oldMode = ::SetBkMode( m_hDc, TRANSPARENT );
                }
                ::LONG lFlags = 0L;
                if (( flags & IDrawing::F_MULTILINE ) != IDrawing::F_MULTILINE )
				{
					lFlags |= DT_SINGLELINE;

					if (( flags & IDrawing::F_MIDDLE ) == IDrawing::F_MIDDLE )
					{
						lFlags |= DT_VCENTER;
					}
					else if (( flags & IDrawing::F_TOP ) == IDrawing::F_TOP )
					{
						lFlags |= DT_TOP;
					}
					else if (( flags & IDrawing::F_BOTTOM ) == IDrawing::F_BOTTOM )
					{
						lFlags |= DT_BOTTOM;
					}
				}
				if (( flags & IDrawing::F_CENTER  ) == IDrawing::F_CENTER )
				{
					lFlags |= DT_CENTER;
				}
				else if (( flags & IDrawing::F_LEFT  ) == IDrawing::F_LEFT )
				{
					lFlags |= DT_LEFT;
				}
				else if (( flags & IDrawing::F_RIGHT  ) == IDrawing::F_RIGHT )
				{
					lFlags |= DT_RIGHT;
				}
				else if (( flags & IDrawing::F_JUSTIFY ) == IDrawing::F_JUSTIFY )
				{
					//lFlags |= ?
				}
				if (( flags & IDrawing::F_ELLIPSIS ) == IDrawing::F_ELLIPSIS )
				{
					//lFlags |= ?
				}
				if (( flags & IDrawing::F_BREAKWORD ) == IDrawing::F_BREAKWORD )
				{
					//lFlags |= ?
				}

                ::DrawTextExW( m_hDc, (WCHAR *)( text.c_str() ), Utils::copyCast< int >( text.size()), (LPRECT)rect, lFlags, &dtp );
                ::SelectObject( m_hDc, obj );
                if ( CLR_INVALID != oldTC )
                {
                    ::SetTextColor( m_hDc, oldTC );
                }
                if ( CLR_INVALID != oldBC )
                {
                    ::SetBkColor( m_hDc, oldBC );
                }
                if ( oldMode )
                {
                    ::SetBkMode( m_hDc, oldMode );
                }

                return dtp.uiLengthDrawn;
            }

            aloe__method_imp( Win32::IDevContext, DrawBitmap, argv )
            {
                aloe__extract5( Win32::IDevContext, DrawBitmap, args, argv, rcDest, bitmap, rcSource, opacity, flags );

                ::HBITMAP hBmp = bitmap[ &IBitmap::HBitmap ];
                ::HDC hDc = ::CreateCompatibleDC( m_hDc );
                ::HGDIOBJ obj1 = ::SelectObject( hDc, hBmp );
#ifdef WIN32
                ::BLENDFUNCTION blend;
                blend.BlendOp = AC_SRC_OVER;
                blend.BlendFlags = 0;
                blend.SourceConstantAlpha = opacity;
                blend.AlphaFormat = (flags & 0x1 ? AC_SRC_ALPHA : 0);
                ::AlphaBlend( m_hDc, rcDest.x1, rcDest.y1, rcDest.width(), rcDest.height(),
                        hDc, rcSource.x1, rcSource.y1, rcSource.width(), rcSource.height(),
                        blend );
#endif
                ::SelectObject( hDc, obj1 );
                ::DeleteDC( hDc );

                return Types::None();
            }
            
        };//CDevContext

        
        struct CBrush
            : Detail::Implementation
            < CBrush
            , Detail::Interfaces< Aloe::IBrush, Win32::IBrush >
            , Detail::Bases< Detail::CRefCount >
            , 0x6001 >
        {
            Types::Color32 m_color;
            Types::Long    m_style;
            Types::Long    m_hatch;
            Utils::SmartPtr< Win32::CGDIBrush > m_gdi;
            Utils::SmartPtr< Win32::CGDIBitmap > m_bmp;

            CBrush() : m_color(255,255,255), m_style(BS_SOLID), m_hatch(0)
            {}
            
            aloe__property_imp_put( Aloe::IBrush, Color, color )
            {
                m_color = color;
                m_gdi = Types::None();
            }

            aloe__property_imp_get( Aloe::IBrush, Color )
            {
                return m_color;
            }

            aloe__property_imp_put( Aloe::IBrush, Style, style )
            {
                m_style = style;
                m_gdi = Types::None();
            }
            
            aloe__property_imp_get( Aloe::IBrush, Style )
            {
                return m_style;
            }

            aloe__property_imp_get( Win32::IBrush, HBrush )
            {
                if ( !m_gdi )
                {
                    ::LOGBRUSH logBrush;
                    logBrush.lbStyle = m_style;
                    logBrush.lbColor = RGB( m_color.red, m_color.green, m_color.blue );

                    switch( logBrush.lbStyle )
                    {
                        case BS_DIBPATTERN:
                        case BS_DIBPATTERN8X8:
                        case BS_DIBPATTERNPT:
                            logBrush.lbHatch = Utils::copyCast< ::LONG >( m_bmp->m_hBitmap );
                            break;
                        default:
                            logBrush.lbHatch = m_hatch;
                    };
                    
                    ::HBRUSH hBr = ::CreateBrushIndirect( &logBrush );
                    m_gdi = (new CGDIBrush)->__init__( hBr, true );
                }
                
                return m_gdi->m_hBrush;
            }
            
        };//CBrush

        struct CPen
            : Detail::Implementation
            < CPen
            , Detail::Interfaces< Aloe::IPen, Win32::IPen >
            , Detail::Bases< Detail::CRefCount >
            , 0x6002 >
        {
            Types::Color32 m_color;
            Types::Long    m_style;
            Types::Long    m_width;
            Utils::SmartPtr< Win32::CGDIPen > m_gdi;

            CPen() : m_color(255,255,255), m_style(BS_SOLID), m_width(0)
            {}
            
            aloe__property_imp_put( Aloe::IPen, Color, color )
            {
                m_color = color;
                m_gdi = Types::None();
            }

            aloe__property_imp_get( Aloe::IPen, Color )
            {
                return m_color;
            }

            aloe__property_imp_put( Aloe::IPen, Style, style )
            {
                m_style = style;
                m_gdi = Types::None();
            }
            
            aloe__property_imp_get( Aloe::IPen, Style )
            {
                return m_style;
            }

            aloe__property_imp_put( Aloe::IPen, Width, width )
            {
                m_width = width;
                m_gdi = Types::None();
            }
            
            aloe__property_imp_get( Aloe::IPen, Width )
            {
                return m_width;
            }

            aloe__property_imp_get( Win32::IPen, HPen )
            {
                if ( !m_gdi )
                {
                    ::LOGPEN logPen;
                    logPen.lopnStyle = m_style;
                    logPen.lopnWidth.x = m_width;
                    logPen.lopnWidth.y = m_width;
                    logPen.lopnColor = RGB( m_color.red, m_color.green, m_color.blue );

                    ::HPEN hPen = ::CreatePenIndirect( &logPen );
                    m_gdi = ( new CGDIPen )->__init__( hPen, true );
                }
                return m_gdi->m_hPen;
            }
        };// CPen

        struct CFont
            : Detail::Implementation
            < CFont
            , Detail::Interfaces< Aloe::IFont, Win32::IFont >
            , Detail::Bases< Detail::CRefCount >
            , 0x6003 >
        {
            Types::String m_family;
            Types::Int    m_size;
            Types::Int    m_weight;
            Types::Int    m_slant;
            Types::Int    m_encoding;
            Types::Int    m_rotation;
            Utils::SmartPtr< Win32::CGDIFont > m_gdi;

            CFont() : m_family(aloe__string("Arial")), m_size(10), m_weight(500), m_slant(500), m_encoding(ANSI_CHARSET), m_rotation(0)
            {}

            aloe__property_imp_put( Aloe::IFont, Family, value )
            {
                m_family = value;
            }
            
            aloe__property_imp_get( Aloe::IFont, Family )
            {
                return m_family;
            }
                        
            aloe__property_imp_put( Aloe::IFont, Size, value )
            {
                m_size = value;
            }
            
            aloe__property_imp_get( Aloe::IFont, Size )
            {
                return m_size;
            }
            
            aloe__property_imp_put( Aloe::IFont, Weight, value )
            {
                m_weight = value;
            }
            
            aloe__property_imp_get( Aloe::IFont, Weight )
            {
                return m_weight;
            }
            
            aloe__property_imp_put( Aloe::IFont, Slant, value )
            {
                m_slant = value;
            }
            
            aloe__property_imp_get( Aloe::IFont, Slant )
            {
                return m_slant;
            }
            
            aloe__property_imp_put( Aloe::IFont, Encoding, value )
            {
                m_encoding = value;
            }
            
            aloe__property_imp_get( Aloe::IFont, Encoding )
            {
                return m_encoding;
            }
            
            aloe__property_imp_put( Aloe::IFont, Rotation, value )
            {
                m_rotation = value;
            }
            
            aloe__property_imp_get( Aloe::IFont, Rotation)
            {
                return m_rotation;
            }
            
            aloe__property_imp_get( Win32::IFont, HFont )
            {
                if ( !m_gdi )
                {
                    ::LOGFONTW logFont;
                    ::ZeroMemory( &logFont, sizeof( ::LOGFONT ));
                    logFont.lfHeight = m_size;
                    logFont.lfWeight = m_weight;
                    logFont.lfItalic = (m_slant > 500 ? TRUE : FALSE);
                    logFont.lfEscapement = m_rotation;
                    wprintf( (wchar_t*)(logFont.lfFaceName), m_family.c_str() );
                    logFont.lfCharSet = m_encoding;
                    ::HFONT hFont = ::CreateFontIndirect( &logFont );
                    m_gdi = ( new CGDIFont )->__init__( hFont, true );
                }
                return m_gdi->m_hFont;
            }

        };//CFont
        
        struct CBitmap
            : Detail::Implementation
            < CBitmap
            , Detail::Interfaces< Aloe::IRasterFormat, Aloe::IRaster, Win32::IBitmap >
            , Detail::Bases< Detail::CRefCount, Detail::Delegation< Win32::IGDIObject > >
            , 0x6004 >
        {
            Utils::SmartPtr< Win32::CGDIBitmap > m_gdi;
            ::BITMAP m_bmp;

            void Alloc()
            {
                ::HBITMAP hBitmap = (::HBITMAP)NULL;
                ::HDC hDc = ::GetDC( (::HWND)NULL );
                
                if ( 0 == m_bmp.bmBitsPixel )
                {
                    hBitmap = ::CreateCompatibleBitmap( hDc, m_bmp.bmWidth, m_bmp.bmHeight );
                }
                else
                {
                    ::BITMAPINFO info;
                    ::ZeroMemory( &info, sizeof( ::BITMAPINFO ));
                    info.bmiHeader.biSize = sizeof( ::BITMAPINFOHEADER );
                    info.bmiHeader.biWidth = m_bmp.bmWidth;
                    info.bmiHeader.biHeight = m_bmp.bmHeight;
                    info.bmiHeader.biPlanes = 1;
                    info.bmiHeader.biBitCount = m_bmp.bmBitsPixel;
                    info.bmiHeader.biCompression = BI_RGB;

                    hBitmap = ::CreateDIBSection( hDc, &info, DIB_RGB_COLORS, &m_bmp.bmBits, (::HANDLE)NULL, 0 );
                }
                ::ReleaseDC( (::HWND)NULL, hDc );
                
                m_gdi = ( new CGDIBitmap )->__init__( hBitmap, true );

                // I assume 'm_bmp.bmBits' is equal to 'ppvBits' returned from CreateDIBSection
                ::GetObject( m_gdi->m_hBitmap, sizeof(::BITMAP), &m_bmp );
            }

            Utils::SmartPtr< CBitmap > __init__( Utils::SmartPtr< Win32::CGDIBitmap > gdi )
            {
                m_gdi = gdi;
                if ( !m_gdi )
                {
                    ::ZeroMemory( &m_bmp, sizeof(::BITMAP));
                }
                else
                {
                    ::GetObject( m_gdi->m_hBitmap, sizeof(::BITMAP), &m_bmp );
                }
                return Super::__init__();
            }
            
            aloe__property_imp_put( IRasterFormat, RasterSize, value )
            {
                m_bmp.bmWidth = value.dx;
                m_bmp.bmHeight = value.dy;
                m_gdi = Types::None();
            }
            
            aloe__property_imp_get( IRasterFormat, RasterSize )
            {
                return Types::Vector2i( m_bmp.bmWidth, m_bmp.bmHeight );
            }
            
            aloe__property_imp_put( IRasterFormat, PixelType, value )
            {
                m_bmp.bmBitsPixel = value.bitsPerPixel();
                m_gdi = Types::None();
            }
            
            aloe__property_imp_get( IRasterFormat, PixelType )
            {
                if ( m_bmp.bmBitsPixel == 32 )
                    return Types::PixelType::RGBA32 | Types::PixelType::F_PREMUL;
                else
                    return m_bmp.bmBitsPixel;
            }
            

            void SetPixelRect( const Types::Recti &rect, const Utils::SmartPtr< IRasterRect > &source );
            Utils::SmartPtr< IRasterRect > GetPixelRect( const Types::Recti &rect );

            aloe__prop_map_imp_put( IRaster, PixelRect, rect, source )
            {
                SetPixelRect( rect, source );
            }
            
            aloe__prop_map_imp_get( IRaster, PixelRect, rect )
            {
                return GetPixelRect( rect );
            }

            aloe__method_imp( IRaster, CreateCompat, argv )
            {
                // method should create raster compatibile with this raster
                return Types::None();
            }

            aloe__property_imp_get( Win32::IBitmap, HBitmap )
            {
                if ( !m_gdi )
                {
                    Alloc();
                }
                return m_gdi->m_hBitmap;
            }
            
            Types::Bool /*Detail::Delegation< Win32::IGDIObject >::*/
		QueryDelegate( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                if ( !m_gdi )
                {
                    Alloc();
                }
                return m_gdi->Query( iid, argPtr, argCount );
            }

            Types::Bool /*Detail::Delegation< Win32::IGDIObject >::*/
		QueryDelegateRawPtr( Types::SizeType iRawId, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                if ( !m_gdi )
                {
                    Alloc();
                }
                return m_gdi->QueryRawPtr( iRawId, argPtr, argCount );
            }

        };//CBitmap

        struct CBitmapBits
            : Detail::Implementation
            < CBitmapBits
            , Detail::Interfaces< IRasterRect, IPixelArray >
            , Detail::Bases< Detail::CRefCount, Detail::Delegation< IRasterFormat > >
            , 0x6005 >
        {
            Utils::SmartPtr< CBitmap > m_bitmap;
            Types::Recti m_rect;

            ThisPtr __init__( const Utils::SmartPtr< CBitmap > &bitmap, const Types::Recti &rect )
            {
                m_bitmap = bitmap;
                m_rect = rect;
                return Super::__init__();
            }
            
            aloe__property_imp_put( IRasterRect, Raster, bitmap )
            {
                // ignore
            }

            aloe__property_imp_put( IRasterRect, Rect, rect )
            {
                // ignore
            }
            
            aloe__property_imp_put( IPixelArray, BytesPerRow, bytes )
            {
                // ignore
            }
            
            aloe__property_imp_put( IPixelArray, BytesPerPixel, bytes )
            {
                // ignore
            }
            
            aloe__property_imp_get( IRasterRect, Raster )
            {
                return m_bitmap;
            }
            
            aloe__property_imp_get( IRasterRect, Rect )
            {
                return m_rect;
            }
            
            aloe__property_imp_get( IPixelArray, BytesPerRow )
            {
                return m_bitmap->m_bmp.bmWidthBytes;
            }
            
            aloe__property_imp_get( IPixelArray, BytesPerPixel )
            {
                return m_bitmap->m_bmp.bmBitsPixel / 8;
            }
            
            aloe__method_imp( IPixelArray, Lock, argv )
            {
                aloe__extract1( IPixelArray, Lock, args, argv, info );
                
                if ( !m_bitmap->m_gdi )
                {
                    m_bitmap->Alloc();
                }

                // returning pointer to first pixel in rectangle 'm_rect'
                Types::NCUByteArray data = (Types::NCUByteArray)(m_bitmap->m_bmp.bmBits);
                data += (m_bitmap->m_bmp.bmHeight - m_rect.y2) * get_BytesPerRow();
                data += m_rect.x1 * get_BytesPerPixel();

                if ( info )
                {
                    info->m_pixelType = m_bitmap[ &IRasterFormat::PixelType ].value();
                    info->m_bytesPerRow = get_BytesPerRow();
                    info->m_bytesPerPixel = get_BytesPerPixel();
                    info->m_rect = m_rect;
                    info->m_pixels = data;
                }
                
                return data;
            }
            
            aloe__method_imp( IPixelArray, Unlock, argv )
            {
                // send changes to device resource
                return Types::None();
            }
            

            Types::Bool /*Detail::Delegation< IRasterFormat >::*/
		QueryDelegate( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                return m_bitmap->Query( iid, argPtr, argCount );
            }
            
            Types::Bool /*Detail::Delegation< IRasterFormat >::*/
		QueryDelegateRawPtr( Types::SizeType iRawId, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                return m_bitmap->QueryRawPtr( iRawId, argPtr, argCount );
            }
            
        };// CBitmapBits
        
        void CBitmap::SetPixelRect( const Types::Recti &rect, const Utils::SmartPtr< IRasterRect > &source )
        {
            // copy pixels from source to this(rect)
            Utils::SmartPtr< IRasterRect > dest = GetPixelRect( rect );

            Types::PixelRectangle dataIn, dataOut;
            
            source[ &IPixelArray::Lock ]( &dataIn );
            dest[ &IPixelArray::Lock ]( &dataOut );
            
            Utils::copyPixels( dataOut, dataIn );
            
            source[ &IPixelArray::Unlock ]();
            dest[ &IPixelArray::Unlock ]();
        }
        
        
        Utils::SmartPtr< IRasterRect > CBitmap::GetPixelRect( const Types::Recti &rect )
        {
            // access pixels of this(rect)
            return (new CBitmapBits)->__init__( __self__(), rect );
        }
        
        Utils::SmartPtr< IRaster > CDevContext::GetDelegateRaster()
        {
            ::HGDIOBJ h = ::GetCurrentObject( m_hDc, OBJ_BITMAP );
            
            if ( !m_hDelegateBitmap || m_hDelegateBitmap != (::HBITMAP)h )
            {
                m_delegateRaster = Types::None();

                Utils::SmartPtr< Win32::IBitmap > bitmap;
                if ( !CGDIObject::FindObject( bitmap, h ))
                {
                    bitmap = ( new CGDIBitmap )->__init__( (::HBITMAP)h );
                }

                m_delegateRaster = (new CBitmap)->__init__( bitmap.UseRawPtrCast() );
                m_hDelegateBitmap = (::HBITMAP)h;
            }

            return m_delegateRaster;
        }
            
        void CDevContext::SetDelegateRaster( const Utils::SmartPtr< IRaster > &raster )
        {
            if ( !!raster )
            {
                Utils::SmartPtr< CGDIBitmap > gdiBitmap = raster[ &Win32::IGDIObject::This ].UseRawPtrCast();
                m_delegateRaster = (new CBitmap)->__init__( gdiBitmap );
                ::SelectObject( m_hDc, m_hDelegateBitmap = gdiBitmap->m_hBitmap );
            }
            else
            {
                ::SelectObject( m_hDc, m_hOldBitmap );
                m_delegateRaster = Types::None();
                m_hDelegateBitmap = (::HBITMAP)NULL;
            }
        }
               
        struct CCursorShape
            : Detail::Implementation
            < CCursorShape
            , Detail::Interfaces< Aloe::ICursorShape, Win32::ICursor >
            , Detail::Bases< Detail::CRefCount >
            , 0x6006 >
        {
            Utils::SmartPtr< CGDICursor > m_cursor;
            ::ICONINFO m_info;

            ThisPtr __init__( Utils::SmartPtr< CGDICursor > cursor )
            {
                m_cursor = cursor;
                if ( !m_cursor )
                {
                    ::ZeroMemory( &m_info, sizeof(::ICONINFO));
                }
                else
                {
                    ::GetIconInfo( (::HICON)(m_cursor->m_hCursor), &m_info );
                }
                return Super::__init__();
            }
            
            void Alloc()
            {
                m_info.fIcon = false;
                ::HICON hIcon = ::CreateIconIndirect( &m_info );
                m_cursor = ( new CGDICursor )->__init__( (::HCURSOR)hIcon, true );
            }

            aloe__property_imp_put( ICursorShape, PixelRect, pixels )
            {
                m_cursor = Types::None();
            }

            aloe__property_imp_get( ICursorShape, PixelRect )
            {
                return Types::None();
            }

            aloe__property_imp_put( ICursorShape, HotSpot, hotspot )
            {
                m_info.xHotspot = hotspot.x;
                m_info.yHotspot = hotspot.y;
                m_cursor = Types::None();
            }

            aloe__property_imp_get( ICursorShape, HotSpot )
            {
                return Types::Point2i( m_info.xHotspot, m_info.yHotspot );
            }

            aloe__property_imp_get( Win32::ICursor, HCursor )
            {
                if ( !m_cursor )
                {
                    Alloc();
                }
                return m_cursor->m_hCursor;
            }
        }; //CCursorShape
        
        struct CRegion
            : Detail::Implementation
            < CRegion
            , Detail::Interfaces< Aloe::IRegion, Win32::IRegion >
            , Detail::Bases< Detail::CRefCount >
            , 0x6007 >
        {
            Utils::SmartPtr< CGDIRegion > m_region;

            ThisPtr __init__( Utils::SmartPtr< CGDIRegion > region )
            {
                m_region = region;
                return Super::__init__();
            }
            
            void Alloc()
            {
                m_region = (new CGDIRegion)->__init__( ::CreateRectRgn(0,0,0,0), true );
            }

            aloe__property_imp_get( Win32::IRegion, HRgn )
            {
                if ( !m_region )
                {
                    Alloc();
                }
                return m_region->m_hRgn;
            }

            aloe__property_imp_put( Aloe::IRegion, Rectangles, rects )
            {
                Utils::ArrayOf<> arrayBytes( sizeof( RGNDATAHEADER ) + rects.size() );
                RGNDATA *pRgnData = (RGNDATA*)arrayBytes.begin();
                Types::Recti *pRect = (Types::Recti*)(pRgnData->Buffer);
                std::copy( rects.begin(), rects.end(), pRect );
                if ( ::HRGN hRgn = ::ExtCreateRegion( NULL, (INT)arrayBytes.size(), pRgnData ))
                {
                    m_region = (new CGDIRegion)->__init__( hRgn, true );
                }                
            }
            
            aloe__property_imp_get( Aloe::IRegion, Rectangles )
            {
                ::DWORD dwSizeReq = ::GetRegionData( get_HRgn(), 0, NULL );
                Utils::ArrayOf<> arrayBytes( dwSizeReq );
                RGNDATA *pRgnData = (RGNDATA*)arrayBytes.begin();
                if ( ::GetRegionData( get_HRgn(), dwSizeReq, pRgnData ) == dwSizeReq )
                {
					Utils::ArrayOf< Types::Recti > arrayRects( arrayBytes );
                    arrayRects.m_size = pRgnData->rdh.nCount;
                    arrayRects.m_objects = (Types::Recti*)pRgnData->Buffer;
                    return arrayRects;
                }
                
                return Types::None();
            }

            aloe__property_imp_append( Aloe::IRegion, Rectangles, rect )
            {
                ::HRGN hRgn = ::CreateRectRgnIndirect( (LPRECT)&rect );
                Types::Int result = ::CombineRgn( get_HRgn(), get_HRgn(), hRgn, RGN_OR );
                ::DeleteObject( hRgn );
                return result;
            }
            
            aloe__property_imp_remove( Aloe::IRegion, Rectangles, rect )
            {
                ::HRGN hRgn = ::CreateRectRgnIndirect( (LPRECT)&rect );
                Types::Int result = ::CombineRgn( get_HRgn(), get_HRgn(), hRgn, RGN_DIFF );
                ::DeleteObject( hRgn );
                return result;
            }

            aloe__property_imp_get( Aloe::IRegion, Bound )
            {
                Types::Recti rect;
                Types::Int result = ::GetRgnBox( get_HRgn(), (LPRECT)&rect );
                return rect;
            }

            aloe__method_imp( Aloe::IRegion, And, argv )
            {
                aloe__extract1( Aloe::IRegion, And, args, argv, region );

                ::HRGN hRgn = region[ &Win32::IRegion::HRgn ];
                Types::Int result = ::CombineRgn( get_HRgn(), get_HRgn(), hRgn, RGN_AND );
                return result;
            }

            aloe__method_imp( Aloe::IRegion, Sub, argv )
            {
                aloe__extract1( Aloe::IRegion, Sub, args, argv, region );

                ::HRGN hRgn = region[ &Win32::IRegion::HRgn ];
                Types::Int result = ::CombineRgn( get_HRgn(), get_HRgn(), hRgn, RGN_DIFF );
                return result;
            }

            aloe__method_imp( Aloe::IRegion, Add, argv )
            {
                aloe__extract1( Aloe::IRegion, Add, args, argv, region );

                ::HRGN hRgn = region[ &Win32::IRegion::HRgn ];
                Types::Int result = ::CombineRgn( get_HRgn(), get_HRgn(), hRgn, RGN_OR );
                return result;
            }

            aloe__method_imp( Aloe::IRegion, Xor, argv )
            {
                aloe__extract1( Aloe::IRegion, Xor, args, argv, region );

                ::HRGN hRgn = region[ &Win32::IRegion::HRgn ];
                Types::Int result = ::CombineRgn( get_HRgn(), get_HRgn(), hRgn, RGN_XOR );
                return result;
            }
            
            aloe__method_imp( Aloe::IRegion, Copy, argv )
            {
                aloe__extract1( Aloe::IRegion, Copy, args, argv, region );

                ::HRGN hRgn = region[ &Win32::IRegion::HRgn ];
                Types::Int result = ::CombineRgn( get_HRgn(), hRgn, hRgn, RGN_COPY );
                return result;
            }
            
            aloe__method_imp( Aloe::IRegion, Rect, argv )
            {
                aloe__extract1( Aloe::IRegion, Rect, args, argv, rect );
                
                m_region = (new CGDIRegion)->__init__( ::CreateRectRgnIndirect( (LPRECT)&rect ), true );
                return Types::None();
            }
            
            aloe__method_imp( Aloe::IRegion, RoundRect, argv )
            {
                aloe__extract2( Aloe::IRegion, RoundRect, args, argv, b, r );
                
                m_region = (new CGDIRegion)->__init__( ::CreateRoundRectRgn( b.x1, b.y1, b.x2, b.y2, r.dx, r.dy ), true );
                return Types::None();
            }
            
            aloe__method_imp( Aloe::IRegion, Ellipse, argv )
            {
                aloe__extract1( Aloe::IRegion, Ellipse, args, argv, bound );
                
                m_region = (new CGDIRegion)->__init__( ::CreateEllipticRgnIndirect( (LPRECT)&bound ), true );
                return Types::None();
            }
            
            aloe__method_imp( Aloe::IRegion, Polygon, argv )
            {
                aloe__extract1( Aloe::IRegion, Polygon, args, argv, points );
                
                m_region = (new CGDIRegion)->__init__( ::CreatePolygonRgn( (LPPOINT)points.begin(), (INT)points.size(), 0 ), true );
                return Types::None();
            }
            
            aloe__method_imp( Aloe::IRegion, PolyPolygon, argv )
            {
                aloe__extract2( Aloe::IRegion, PolyPolygon, args, argv, points, sizes );
                
                m_region = (new CGDIRegion)->__init__( ::CreatePolyPolygonRgn( (LPPOINT)points.begin(), (LPINT)sizes.begin(), (INT)sizes.size(), 0 ), true );
                return Types::None();
            }
        };


    };//Win32
};//Aloe
