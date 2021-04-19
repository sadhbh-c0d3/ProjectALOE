#ifndef ALOE_UI
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'UI.cpp'."
#endif

namespace Aloe {
	
	const Types::String ClsID_Bitmap( aloe__string("Bitmap") );
	const Types::String ClsID_PropertyMap( aloe__string("PropertyMap") );

	const Types::String ProID_BitmapFilename( aloe__string("Bitmap.Filename") );
	const Types::String ProID_ButtonFont( aloe__string("Button.Font") );
	const Types::String ProID_ButtonBitmapNormal( aloe__string("Button.Bitmap.Normal") );
	const Types::String ProID_ButtonBitmapHighlight( aloe__string("Button.Bitmap.Highlight") );
	const Types::String ProID_ButtonBitmapPressed( aloe__string("Button.Bitmap.Pressed") );

    struct CButtonDesigner
        : Detail::Implementation
        < CButtonDesigner
        , Detail::Interfaces<
			IUserInterfaceEvents,
			IUserInterfaceEvents1,
			IUserInterfaceEvents2,
			IUserInterfaceEvents3 >
        , Detail::Bases< Detail::CRefCount > >
    {
        Utils::SmartPtr< IEntity > m_entity;
        Utils::SmartPtr< IGraphicsDesign > m_design;
        Utils::SmartPtr< IRaster > m_bitmapNormal;
        Utils::SmartPtr< IRaster > m_bitmapHighlight;
        Utils::SmartPtr< IRaster > m_bitmapPressed;
        Utils::SmartPtr< IRaster > m_bitmap;
        Utils::SmartPtr< IFont > m_font;
        Types::String m_label;
		Types::Color32 m_bitmapColor;
		Types::Long m_bitmapOpacity;
		Types::Long m_bitmapFlags;
		Types::Tuple< Types::Color32, Types::Color32 > m_fontColor;
		Types::Long m_fontFlags;


        ThisPtr __init__( const Utils::SmartPtr< IEntity > &entity,
        		const Types::String &label, const Utils::SmartPtr< IPropertyMap > &prop )
        {
            m_entity = entity;
            m_label = label;

			m_font				= prop[ &IPropertyMap::Property ][ ProID_ButtonFont ].value();
			m_bitmapNormal		= prop[ &IPropertyMap::Property ][ ProID_ButtonBitmapNormal ].value();
			m_bitmapHighlight	= prop[ &IPropertyMap::Property ][ ProID_ButtonBitmapHighlight ].value();
			m_bitmapPressed		= prop[ &IPropertyMap::Property ][ ProID_ButtonBitmapPressed ].value();

            m_bitmapColor = Types::Color32(255,255,255);
            m_bitmapOpacity = 255;
            m_bitmapFlags = 0L;

            aloe__1( m_fontColor ) = Types::Color32(0,128,255,255);
            aloe__2( m_fontColor ) = Types::Color32(255,255,255,0);
			
			m_fontFlags = IDrawing::F_CENTER | IDrawing::F_MIDDLE;

            m_bitmap = m_bitmapNormal;
                
            return Super::__init__();
        }

        aloe__method_imp( IUserInterfaceEvents, Close, argv )
        {
            aloe__extract2( IUserInterfaceEvents, Close, args, argv, sender, flags );

            return false;
        }

        aloe__method_imp( IUserInterfaceEvents, Show, argv )
        {
            return false;
        }

        aloe__method_imp( IUserInterfaceEvents, Activate, argv )
        {
            return false;
        }

        aloe__method_imp( IUserInterfaceEvents, Move, argv )
        {
            aloe__extract3( IUserInterfaceEvents, Move, args, argv, sender, frameRect, flags );
            
            m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]
                ( m_entity, m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ].value() );

            return true;
        }

        aloe__method_imp( IUserInterfaceEvents, Paint, argv )
        {
            aloe__extract3( IUserInterfaceEvents, Paint, args, argv, sender, screen, rect );

            return false;
        }

        aloe__method_imp( IUserInterfaceEvents1, Dirty, argv )
        {
            aloe__extract2( IUserInterfaceEvents1, Dirty, args, argv, sender, rect );
            
            m_design = Types::None();

            if ( sender.get() == m_entity.get() )
            {
                Utils::SmartPtr< IContainer > container = m_entity[ &IEntity::Container ].value();
                Types::Recti rect = m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ];
                container[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]( container, rect );
            }
            
            return true;
        }

        aloe__method_imp( IUserInterfaceEvents1, Design, argv )
        {
            aloe__extract2( IUserInterfaceEvents1, Design, args, argv, sender, design );
            
            if ( !m_design )
            {
                Types::Recti rcSrc( Types::Point2i(0,0), m_bitmap[ &IRasterFormat::RasterSize ] );
                Types::Recti rect = m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ];
                
                m_design = design[ &IGraphicsDesign::CreateDesign ]( rect );
                Types::SizeType nFont = ( m_design[ &IGraphicsDesign::Fonts ] += m_font );
                m_design[ &IDrawing::DrawRaster ]( rect, m_bitmap, rcSrc, m_bitmapColor, m_bitmapOpacity, m_bitmapFlags );
                m_design[ &IDrawing::DrawString ]( m_label, rect, nFont, m_fontColor, m_fontFlags );
            }
                
            Types::SizeType nSubDesign = design[ &IGraphicsDesign::SubDesigns ] += m_design;
            design[ &IDrawing::DrawSubDesign ]( m_design[ &IGraphicsDesign::Bound ], nSubDesign );
            
            return true;
        }

        aloe__method_imp( IUserInterfaceEvents2, Motion, argv )
        {
            aloe__extract2( IUserInterfaceEvents2, Motion, args, argv, sender, pos );
            
            return true;
        }

        aloe__method_imp( IUserInterfaceEvents2, Hover, argv )
        {
            aloe__extract1( IUserInterfaceEvents2, Hover, args, argv, sender );
            
            if ( m_bitmap.get() != m_bitmapPressed.get() )
            {
                m_bitmap = m_bitmapHighlight;
                
                m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]
                    ( m_entity, m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ].value() );
            }
            
            return true;
        }
        
        aloe__method_imp( IUserInterfaceEvents2, Leave, argv )
        {
            aloe__extract1( IUserInterfaceEvents2, Hover, args, argv, sender );

            if ( m_bitmap.get() != m_bitmapPressed.get() )
            {
                m_bitmap = m_bitmapNormal;

                m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]
                    ( m_entity, m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ].value() );
            }
            
            return true;
        }

        aloe__method_imp( IUserInterfaceEvents3, Press, argv )
        {
            aloe__extract3( IUserInterfaceEvents3, Press, args, argv, sender, button, pos );

            m_bitmap = m_bitmapPressed;

            m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]
                ( m_entity, m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ].value() );

            return true;
        }

        aloe__method_imp( IUserInterfaceEvents3, Release, argv )
        {
            aloe__extract3( IUserInterfaceEvents3, Release, args, argv, sender, button, pos );
            
            Types::Recti rect = m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ];
            if ( rect.isPointInside( pos ))
            {
                m_bitmap = m_bitmapHighlight;
            }
            else {
                m_bitmap = m_bitmapNormal;
            }

            m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]( m_entity, rect );

            return true;
        }

        aloe__method_imp( IUserInterfaceEvents3, Click, argv )
        {
            aloe__extract3( IUserInterfaceEvents3, Click, args, argv, sender, button, pos );

            return true;
        }

        aloe__method_imp( IUserInterfaceEvents3, DoubleClick, argv )
        {
            aloe__extract3( IUserInterfaceEvents3, DoubleClick, args, argv, sender, button, pos );

            return true;
        }
    
    };//CButtonDesigner
	

	struct CButtonListener
		: Detail::Implementation
		< CButtonListener
		, Detail::Interfaces<
			IUserInterfaceEvents3 >
		, Detail::Bases< Detail::CRefCount > >
	{

		aloe__method_imp( IUserInterfaceEvents3, Press, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, Press, args, argv, sender, button, pos );
			return false;
		}

		aloe__method_imp( IUserInterfaceEvents3, Release, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, Release, args, argv, sender, button, pos );
			return false;
		}

		aloe__method_imp( IUserInterfaceEvents3, Click, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, Click, args, argv, sender, button, pos );
			return false;
		}

		aloe__method_imp( IUserInterfaceEvents3, DoubleClick, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, DoubleClick, args, argv, sender, button, pos );
			return false;
		}

	};//CButtonListener
    
};//Aloe
