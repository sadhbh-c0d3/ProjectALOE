#ifndef ALOE_WIN32_SYSTEM
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'Win32System.cpp'."
#endif

namespace Aloe {
    namespace Win32 {
        struct CGDIDesign
            : Detail::Implementation
            < CGDIDesign
            , Detail::Interfaces< IGraphicsDesign, IDrawing >
            , Detail::CRefCount
            , 0x7000 >
        {
            
            struct CGDIDesignItem
                : Detail::Implementation
                < CGDIDesignItem
                , Detail::Interfaces< IGraphicsDesignItem >
                , Detail::CRefCount
                , 0x7001 >
            {
                Utils::SmartPtr< CGDIDesign, Utils::WeakPointerPolicy > m_design;
                Types::Recti m_rectBound;

                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design, const Types::Recti &rectBound )
                {
                    m_design = design;
                    m_rectBound = rectBound;
                    return Super::__init__();
                }

                aloe__property_imp_put( IGraphicsDesignItem, Design, design )
                {
                    m_design = design.UseRawPtrCast();
                }

                aloe__property_imp_get( IGraphicsDesignItem, Design )
                {
                    return m_design;
                }
                
                aloe__property_imp_put( IGraphicsDesignItem, Bound, rectBound )
                {
                    m_rectBound;
                }

                aloe__property_imp_get( IGraphicsDesignItem, Bound )
                {
                    return m_rectBound;
                }

                virtual void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect ) = 0;
            };

            struct CGDIShapeDesign
                : Detail::Implementation
                < CGDIShapeDesign
                , Detail::Interfaces< IShapeDesign >
                , CGDIDesignItem
                , 0x7002 >
            {
                Types::SizeType m_iPen;
                
                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design, const Types::Recti &rectBound, Types::SizeType iPen )
                {
                    CGDIDesignItem::__init__( design, rectBound ).AddRef();
                    m_iPen = iPen;
                    return Super::__init__();
                }
                
                aloe__property_imp_put( IShapeDesign, Pen, iPen )
                {
                    m_iPen = iPen;
                }

                aloe__property_imp_get( IShapeDesign, Pen )
                {
                    return m_iPen;
                }
            };
            
            struct CGDIShapeDesign2
                : Detail::Implementation
                < CGDIShapeDesign2
                , Detail::Interfaces< IShapeDesign2 >
                , CGDIShapeDesign
                , 0x7003 >
            {
                Types::SizeType m_iBrush;
                
                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design, const Types::Recti &rectBound, Types::SizeType iPen, Types::SizeType iBrush )
                {
                    CGDIShapeDesign::__init__( design, rectBound, iPen ).AddRef();
                    m_iBrush = iBrush;
                    return Super::__init__();
                }
                
                aloe__property_imp_put( IShapeDesign2, Brush, iBrush )
                {
                    m_iBrush = iBrush;
                }

                aloe__property_imp_get( IShapeDesign2, Brush )
                {
                    return m_iBrush;
                }
            };

            struct CGDISectorDesign
                : Detail::Implementation
                < CGDISectorDesign
                , Detail::Interfaces< ISectorDesign >
                , CGDIShapeDesign
                , 0x7004 >
            {
                Types::Sectori m_sector;
                
                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design
                        , Types::Sectori sector, Types::SizeType iPen )
                {
                    Types::Recti rectBound( sector.start, sector.end );
                    CGDIShapeDesign::__init__( design, rectBound, iPen ).AddRef();
                    m_sector = sector;
                    return Super::__init__();
                }

                aloe__property_imp_put( ISectorDesign, Start, point )
                {
                    m_sector.start = point;
                }
                
                aloe__property_imp_get( ISectorDesign, Start )
                {
                    return m_sector.start;
                }
                
                aloe__property_imp_put( ISectorDesign, End, point )
                {
                    m_sector.end = point;
                }
                
                aloe__property_imp_get( ISectorDesign, End )
                {
                    return m_sector.end;
                }
                
                aloe__property_imp_put( ISectorDesign, From, vect )
                {
                    m_sector.from() = vect;
                }
                
                aloe__property_imp_get( ISectorDesign, From )
                {
                    return m_sector.from();
                }
                
                aloe__property_imp_put( ISectorDesign, To, vect )
                {
                    m_sector.to() = vect;
                }
                
                aloe__property_imp_get( ISectorDesign, To )
                {
                    return m_sector.to();
                }
                
                void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect )
                {
                    device->DrawSector( Utils::makeTuple( m_sector.start, m_sector.end, m_design->m_vPens[ m_iPen ] ));
                }
            };
            
            struct CGDIPolylineDesign
                : Detail::Implementation
                < CGDIPolylineDesign
                , Detail::Interfaces< IPolylineDesign >
                , CGDIShapeDesign
                , 0x7005 >
            {
                Utils::VectorOf< Types::Point2i > m_vPoints;

                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design
                        , const Utils::ArrayOf< Types::Point2i > &vPoints, Types::SizeType iPen )
                {
                    Types::Recti rectBound;
                    if ( !vPoints.empty() )
                    {
                        rectBound.upperLeft()= vPoints[0];
                        rectBound.bottomRight() = vPoints[0];
                        for ( Utils::VectorOf< Types::Point2i >::Iterator iter = vPoints.begin(); iter != vPoints.end(); ++iter )
                        {
                            rectBound.growToFit( *iter );
                        }
                    }
                    CGDIShapeDesign::__init__( design, rectBound, iPen ).AddRef();
                    m_vPoints = vPoints;
                    return Super::__init__();
                }

                aloe__property_imp_put( IPolylineDesign, Points, vPoints )
                {
                    m_vPoints = vPoints;
                }

                aloe__property_imp_get( IPolylineDesign, Points )
                {
                    return IPolylineDesign::Points__valueType( m_vPoints.tight_array() );
                }

                aloe__property_imp_append( IPolylineDesign, Points, point )
                {
                    return m_vPoints.append( point );
                }

                aloe__property_imp_remove( IPolylineDesign, Points, index )
                {
                    return m_vPoints.remove( index );
                }
                
                aloe__property_imp_put( IPolylineDesign, Vectors, vVectors )
                {
                    m_vPoints = Types::None();
                    Types::Point2i ptCurrent(0,0);
                    
                    for ( Utils::ArrayOf< Types::Vector2i >::Iterator iter = vVectors.begin(); iter != vVectors.end(); ++iter )
                    {
                        ptCurrent += *iter;
                        m_vPoints.push_back( ptCurrent );
                    }
                }

                aloe__property_imp_get( IPolylineDesign, Vectors )
                {
                    Utils::VectorOf< Types::Vector2i > vVectors;
                    Types::Point2i ptCurrent(0,0);
                    
                    for ( Utils::ArrayOf< Types::Point2i >::Iterator iter = m_vPoints.begin(); iter != m_vPoints.end(); ++iter )
                    {
                        Types::Vector2i vect = *iter - ptCurrent;
                        vVectors.push_back( vect );
                        ptCurrent = *iter;
                    }

                    return IPolylineDesign::Vectors__valueType( vVectors.tight_array() );
                }

                aloe__property_imp_append( IPolylineDesign, Vectors, vect )
                {
                    throw Errors::Error_Unsupported();
                    return 0;
                }

                aloe__property_imp_remove( IPolylineDesign, Vectors, index )
                {
                    throw Errors::Error_Unsupported();
                    return 0;
                }
                
                void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect )
                {
                    device->DrawPolyline( Utils::makeTuple( m_vPoints.tight_array(), m_design->m_vPens[ m_iPen ] ));
                }
            };
            
            struct CGDIPolygonDesign
                : Detail::Implementation
                < CGDIPolygonDesign
                , Detail::Interfaces< IPolygonDesign >
                , CGDIShapeDesign2
                , 0x7005 >
            {
                Utils::VectorOf< Types::Point2i > m_vPoints;

                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design
                        , const Utils::ArrayOf< Types::Point2i > &vPoints, Types::SizeType iPen, Types::SizeType iBrush )
                {
                    Types::Recti rectBound;
                    if ( !vPoints.empty() )
                    {
                        rectBound.upperLeft()= vPoints[0];
                        rectBound.bottomRight() = vPoints[0];
                        for ( Utils::VectorOf< Types::Point2i >::Iterator iter = vPoints.begin(); iter != vPoints.end(); ++iter )
                        {
                            rectBound.growToFit( *iter );
                        }
                    }
                    CGDIShapeDesign2::__init__( design, rectBound, iPen, iBrush ).AddRef();
                    m_vPoints = vPoints;
                    return Super::__init__();
                }

                aloe__property_imp_put( IPolygonDesign, Points, vPoints )
                {
                    m_vPoints = vPoints;
                }

                aloe__property_imp_get( IPolygonDesign, Points )
                {
                    return IPolygonDesign::Points__valueType( m_vPoints.tight_array() );
                }

                aloe__property_imp_append( IPolygonDesign, Points, point )
                {
                    return m_vPoints.append( point );
                }

                aloe__property_imp_remove( IPolygonDesign, Points, index )
                {
                    return m_vPoints.remove( index );
                }
                
                aloe__property_imp_put( IPolygonDesign, Vectors, vVectors )
                {
                    m_vPoints = Types::None();
                    Types::Point2i ptCurrent(0,0);
                    
                    for ( Utils::ArrayOf< Types::Vector2i >::Iterator iter = vVectors.begin(); iter != vVectors.end(); ++iter )
                    {
                        ptCurrent += *iter;
                        m_vPoints.push_back( ptCurrent );
                    }
                }

                aloe__property_imp_get( IPolygonDesign, Vectors )
                {
                    Utils::VectorOf< Types::Vector2i > vVectors;
                    Types::Point2i ptCurrent(0,0);
                    
                    for ( Utils::ArrayOf< Types::Point2i >::Iterator iter = m_vPoints.begin(); iter != m_vPoints.end(); ++iter )
                    {
                        Types::Vector2i vect = *iter - ptCurrent;
                        vVectors.push_back( vect );
                        ptCurrent = *iter;
                    }

                    return IPolygonDesign::Vectors__valueType( vVectors.tight_array() );
                }

                aloe__property_imp_append( IPolygonDesign, Vectors, vect )
                {
                    throw Errors::Error_Unsupported();
                    return 0;
                }

                aloe__property_imp_remove( IPolygonDesign, Vectors, index )
                {
                    throw Errors::Error_Unsupported();
                    return 0;
                }
                
                void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect )
                {
                    device->DrawPolygon( Utils::makeTuple( m_vPoints.tight_array(), m_design->m_vBrushes[ m_iBrush ], m_design->m_vPens[ m_iPen ] ));
                }
            };
            
            struct CGDIRectangleDesign
                : Detail::Implementation
                < CGDIRectangleDesign
                , Detail::Interfaces< IRectangleDesign >
                , CGDIShapeDesign2
                , 0x7006 >
            {
                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design
                        , const Types::Recti &rectBound, Types::SizeType iPen, Types::SizeType iBrush )
                {
                    CGDIShapeDesign2::__init__( design, rectBound, iPen, iBrush ).AddRef();
                    return Super::__init__();
                }

                void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect )
                {
                    device->DrawRectangle( Utils::makeTuple( m_rectBound, m_design->m_vBrushes[ m_iBrush ], m_design->m_vPens[ m_iPen ] ));
                }
            };
            
            struct CGDITextDesign
                : Detail::Implementation
                < CGDITextDesign
                , Detail::Interfaces< ITextDesign >
                , CGDIDesignItem
                , 0x7007 >
            {
                Types::SizeType m_iFont;
                Types::String m_strText;
                Types::Color32 m_textColor;
                Types::Color32 m_backColor;
                Types::Long m_lFlags;
                Types::SizeType m_iLen;

                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design
                        , const Types::String &strText
                        , const Types::Recti &rectBound
                        , Types::SizeType iFont
                        , const Types::Tuple< Types::Color32, Types::Color32 > &color
                        , Types::Long lFlags )
                {
                    CGDIDesignItem::__init__( design, rectBound ).AddRef();
                    m_strText = strText;
                    m_iFont = iFont;
                    m_textColor = aloe__1( color );
                    m_backColor = aloe__2( color );
                    m_lFlags = lFlags;
                    m_iLen = 0;
                    return Super::__init__();
                }

                aloe__property_imp_put( ITextDesign, Text, strText )
                {
                    m_strText = strText;
                }

                aloe__property_imp_get( ITextDesign, Text )
                {
                    return m_strText;
                }

                aloe__property_imp_put( ITextDesign, Font, iFont )
                {
                    m_iFont = iFont;
                }

                aloe__property_imp_get( ITextDesign, Font )
                {
                    return m_iFont;
                }

                aloe__property_imp_put( ITextDesign, Flags, lFlags )
                {
                    m_lFlags = lFlags;
                }

                aloe__property_imp_get( ITextDesign, Flags )
                {
                    return m_lFlags;
                }

                void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect )
                {
                    m_iLen = device->DrawString(
                            Utils::makeTuple( m_strText, &m_rectBound, m_design->m_vFonts[ m_iFont ]
                                , Utils::makeTuple( m_textColor, m_backColor ), m_lFlags ));
                }
            };
                
            struct CGDIBlitDesign
                : Detail::Implementation
                < CGDIBlitDesign
                , Detail::Interfaces< IBlitDesign >
                , CGDIDesignItem
                , 0x7008 >
            {

                Utils::SmartPtr< Win32::IBitmap > m_ptrRaster;
                Types::Recti m_srcRect;
                Types::Color32 m_color;
                Types::Int m_iRotation;
                Types::Long m_lFlags;

                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design
                        , const Types::Recti &dstRect
                        , const Utils::SmartPtr< Win32::IBitmap > &ptrRaster
                        , const Types::Recti &srcRect
                        , const Types::Color32 &color
                        , Types::Int iRotation
                        , Types::Long lFlags )
                {
                    CGDIDesignItem::__init__( design, dstRect ).AddRef();
                    m_ptrRaster = ptrRaster;
                    m_srcRect = srcRect;
                    m_color = color;
                    m_iRotation = iRotation;
                    m_lFlags = lFlags;
                    return Super::__init__();
                }

                aloe__property_imp_put( IBlitDesign, Raster, ptrRaster )
                {
                    m_ptrRaster = ptrRaster.AutoQ();
                }

                aloe__property_imp_get( IBlitDesign, Raster )
                {
                    return m_ptrRaster.AutoQ();
                }

                aloe__property_imp_put( IBlitDesign, Rect, srcRect )
                {
                    m_srcRect = srcRect;
                }
                
                aloe__property_imp_get( IBlitDesign, Rect )
                {
                    return m_srcRect;
                }

                aloe__property_imp_put( IBlitDesign, Color, color )
                {
                    m_color = color;
                }
                
                aloe__property_imp_get( IBlitDesign, Color )
                {
                    return m_color;
                }
                
                aloe__property_imp_put( IBlitDesign, Rotation, iRotation )
                {
                    m_iRotation = iRotation;
                }
                
                aloe__property_imp_get( IBlitDesign, Rotation )
                {
                    return m_iRotation;
                }
                
                aloe__property_imp_put( IBlitDesign, Flags, lFlags )
                {
                    m_lFlags = lFlags;
                }
                
                aloe__property_imp_get( IBlitDesign, Flags )
                {
                    return m_lFlags;
                }

                void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect )
                {
                    device->DrawBitmap( Utils::makeTuple( m_rectBound, m_ptrRaster, m_srcRect, m_color.Alphaub(), m_lFlags ));
                }
            };
            
            struct CGDISubDesign
                : Detail::Implementation
                < CGDISubDesign
                , Detail::Interfaces< ISubDesign >
                , CGDIDesignItem
                , 0x7009 >
            {
                Types::SizeType m_iSubDesign;

                ThisPtr __init__( const Utils::SmartPtr< CGDIDesign > &design, const Types::Recti &rectBound, Types::SizeType iSubDesign )
                {
                    CGDIDesignItem::__init__( design, rectBound ).AddRef();
                    m_iSubDesign = iSubDesign;
                    return Super::__init__();
                }

                aloe__property_imp_put( ISubDesign, SubDesign, iSubDesign )
                {
                    m_iSubDesign = iSubDesign;
                }

                aloe__property_imp_get( ISubDesign, SubDesign )
                {
                    return m_iSubDesign;
                }
                
                void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect )
                {
                    m_design->m_vSubDesigns[ m_iSubDesign ]->RenderToDevice( device, clipRect );
                }
            };

            Types::Recti m_rectBound;
            Utils::SmartPtr< IGraphicsDesign, Utils::WeakPointerPolicy > m_ptrParent;
            Utils::AssetOf< Utils::SmartPtr< CGDIDesign > > m_vSubDesigns;
            Utils::AssetOf< Utils::SmartPtr< CGDIDesignItem > > m_vItems;
            Utils::AssetOf< Utils::SmartPtr< Win32::IPen > > m_vPens;
            Utils::AssetOf< Utils::SmartPtr< Win32::IBrush > > m_vBrushes;
            Utils::AssetOf< Utils::SmartPtr< Win32::IFont > > m_vFonts;
            
            ThisPtr __init__( const Types::Recti &rectBound )
            {
                m_rectBound = rectBound;
                return Super::__init__();
            }

            aloe__method_imp( IGraphicsDesign, CreateDesign, argv )
            {
                aloe__extract1( IGraphicsDesign, CreateDesign, args, argv, rectBound );

                return (new CGDIDesign)->__init__( rectBound );
            }

            aloe__property_imp_put( IGraphicsDesign, Bound, rectBound )
            {
                m_rectBound = rectBound;
            }

            aloe__property_imp_get( IGraphicsDesign, Bound )
            {
                return m_rectBound;
            }

            aloe__property_imp_put( IGraphicsDesign, Parent, ptrParent )
            {
                m_ptrParent = ptrParent;
            }

            aloe__property_imp_get( IGraphicsDesign, Parent )
            {
                return m_ptrParent;
            }

            //
            //
            // SubDesigns
            //
            //

            aloe__property_imp_put( IGraphicsDesign, SubDesigns, vSubDesigns )
            {
                m_vSubDesigns = vSubDesigns.UseRawPtrCast();
            }

            aloe__property_imp_get( IGraphicsDesign, SubDesigns )
            {
                return IGraphicsDesign::SubDesigns__valueType( m_vSubDesigns.tight_array() );
            }

            aloe__property_imp_append( IGraphicsDesign, SubDesigns, subDesign )
            {
                return m_vSubDesigns.add( subDesign.UseRawPtrCast() );
            }

            aloe__property_imp_remove( IGraphicsDesign, SubDesigns, index )
            {
                return m_vSubDesigns.del( index );
            }

            //
            //
            // Pens
            //
            //

            aloe__prop_map_imp_put( IGraphicsDesign, Pen, index, ptrPen )
            {
                m_vPens[ index ] = ptrPen.AutoQ();
            }
            
            aloe__prop_map_imp_get( IGraphicsDesign, Pen, index )
            {
                return m_vPens[ index ].AutoQ();
            }

            aloe__property_imp_put( IGraphicsDesign, Pens, vPens )
            {
                m_vPens = vPens.AutoQ();
            }
            
            aloe__property_imp_get( IGraphicsDesign, Pens )
            {
                return IGraphicsDesign::Pens__valueType( m_vPens.tight_array().AutoQ() );
            }
            
            aloe__property_imp_append( IGraphicsDesign, Pens, ptrPen )
            {
                return m_vPens.add( ptrPen.AutoQ() );
            }
            
            aloe__property_imp_remove( IGraphicsDesign, Pens, index )
            {
                return m_vPens.del( index );
            }
            
            //
            //
            // Brushes
            //
            //

            aloe__prop_map_imp_put( IGraphicsDesign, Brush, index, ptrBrush )
            {
                m_vBrushes[ index ] = ptrBrush.AutoQ();
            }
            
            aloe__prop_map_imp_get( IGraphicsDesign, Brush, index )
            {
                return m_vBrushes[ index ].AutoQ();
            }

            aloe__property_imp_put( IGraphicsDesign, Brushes, vBrushes )
            {
                m_vBrushes = vBrushes.AutoQ();
            }
            
            aloe__property_imp_get( IGraphicsDesign, Brushes )
            {
                return IGraphicsDesign::Brushes__valueType( m_vBrushes.tight_array().AutoQ() );
            }
            
            aloe__property_imp_append( IGraphicsDesign, Brushes, ptrBrush )
            {
                return m_vBrushes.add( ptrBrush.AutoQ() );
            }
            
            aloe__property_imp_remove( IGraphicsDesign, Brushes, index )
            {
                return m_vBrushes.del( index );
            }
            
            //
            //
            // Fonts
            //
            //

            aloe__prop_map_imp_put( IGraphicsDesign, Font, index, ptrFont )
            {
                m_vFonts[ index ] = ptrFont.AutoQ();
            }

            aloe__prop_map_imp_get( IGraphicsDesign, Font, index )
            {
                return m_vFonts[ index ].AutoQ();
            }

            aloe__property_imp_put( IGraphicsDesign, Fonts, vFonts )
            {
                m_vFonts = vFonts.AutoQ();
            }
            
            aloe__property_imp_get( IGraphicsDesign, Fonts )
            {
                return IGraphicsDesign::Fonts__valueType( m_vFonts.tight_array().AutoQ() );
            }
            
            aloe__property_imp_append( IGraphicsDesign, Fonts, ptrFont )
            {
                return m_vFonts.add( ptrFont.AutoQ() );
            }
            
            aloe__property_imp_remove( IGraphicsDesign, Fonts, index )
            {
                return m_vFonts.del( index );
            }
            
            //
            //
            // Items
            //
            //

            aloe__prop_map_imp_put( IGraphicsDesign, Item, index, ptrItem )
            {
                m_vItems[ index ] = ptrItem.UseRawPtrCast();
            }
            
            aloe__prop_map_imp_get( IGraphicsDesign, Item, index )
            {
                return m_vItems[ index ];
            }

            aloe__property_imp_put( IGraphicsDesign, Items, vItems )
            {
                m_vItems = vItems.UseRawPtrCast();
            }
            
            aloe__property_imp_get( IGraphicsDesign, Items )
            {
                return IGraphicsDesign::Items__valueType( m_vItems.tight_array() );
            }
            
            aloe__property_imp_append( IGraphicsDesign, Items, ptrItem )
            {
                return m_vItems.add( ptrItem.UseRawPtrCast() );
            }
            
            aloe__property_imp_remove( IGraphicsDesign, Items, index )
            {
                return m_vItems.del( index );
            }

            //
            //
            // IDrawing
            //
            //
            
            aloe__method_imp( IDrawing, DrawSector, argv )
            {
                aloe__extract2( IDrawing, DrawSector, args, argv, sector, iPen );

                return m_vItems.add( (new CGDISectorDesign)->__init__( __self__(), sector, iPen ));
            }

            aloe__method_imp( IDrawing, DrawPolyline, argv )
            {
                aloe__extract2( IDrawing, DrawPolyline, args ,argv, vPoints, iPen );

                return m_vItems.add( (new CGDIPolylineDesign)->__init__( __self__(), vPoints, iPen ));
            }

            aloe__method_imp( IDrawing, DrawPolygon, argv )
            {
                aloe__extract3( IDrawing, DrawPolygon, args ,argv, vPoints, iPen, iBrush );

                return m_vItems.add( (new CGDIPolygonDesign)->__init__( __self__(), vPoints, iPen, iBrush ));
            }

            aloe__method_imp( IDrawing, DrawRectangle, argv )
            {
                aloe__extract3( IDrawing, DrawRectangle, args ,argv, rect, iPen, iBrush );

                return m_vItems.add( (new CGDIRectangleDesign)->__init__( __self__(), rect, iPen, iBrush ));
            }

            aloe__method_imp( IDrawing, DrawString, argv )
            {
                aloe__extract5( IDrawing, DrawString, args ,argv, strText, rect, iFont, pairColors, lFlags );

                return m_vItems.add( (new CGDITextDesign)->__init__( __self__(), strText, rect, iFont, pairColors, lFlags ));
            }
            
            aloe__method_imp( IDrawing, DrawRaster, argv )
            {
                aloe__extract6( IDrawing, DrawRaster, args ,argv, dstRect, ptrRaster, srcRect, color, rotation, lFlags );

                return m_vItems.add( (new CGDIBlitDesign)->__init__( __self__(), dstRect, ptrRaster.AutoQ(), srcRect, color, rotation, lFlags ));
            }

            aloe__method_imp( IDrawing, DrawSubDesign, argv )
            {
                aloe__extract2( IDrawing, DrawSubDesign, args, argv, dstRect, subDesign );

                return m_vItems.add( (new CGDISubDesign)->__init__( __self__(), dstRect, subDesign ));
            };

            void RenderToDevice( Win32::IDevContext *device, const Types::Recti &clipRect )
            {
                ::HDC hDc = device->get_HDc();
                ::HRGN hOldRgn = ::CreateRectRgn(0,0,0,0);
                ::GetClipRgn( hDc, hOldRgn );
                
                for ( Utils::AssetOf< Utils::SmartPtr< CGDIDesignItem > >::Iterator iter = m_vItems.begin(); iter != m_vItems.end(); ++iter )
                {
                    Types::Recti itemBound = (*iter)->m_rectBound;
                    if ( itemBound.intersectWith( clipRect ))
                    {
                        ::HRGN hRgn = ::CreateRectRgnIndirect( (LPRECT)&itemBound );
                        ::SelectClipRgn( hDc, hRgn );
                        (*iter)->RenderToDevice( device, itemBound );
                        ::DeleteObject( hRgn );
                    }
                }
            
                ::SelectClipRgn( hDc, hOldRgn );
                ::DeleteObject( hOldRgn );
            }
            
            
        };//CGDIDesign
           
        Utils::SmartPtr< IGraphicsDesign > CDevContext::DoCreateDesign( const Types::Recti &rect )
        {
            return (new CGDIDesign)->__init__( rect );
        }

        Types::Bool CDevContext::DoRenderDesign( const Utils::SmartPtr< IGraphicsDesign > &design, const Types::Recti &rect )
        {
            Utils::SmartPtr< CGDIDesign > gdiDesign = design.UseRawPtrCast();
            gdiDesign->RenderToDevice( this, rect );
            return true;
        }

    };//Win32
};//Aloe

