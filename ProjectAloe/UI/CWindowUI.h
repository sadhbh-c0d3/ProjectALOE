#ifndef ALOE_UI
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'UI.cpp'."
#endif

namespace Aloe {

	struct CWindowUI
		: Detail::Implementation
		< CWindowUI
		, Detail::Interfaces
			< Win32::IWindowEvents
			, IWindowEvents
			, IUserInputEvents
			, IUserInterfaceEvents
			, IUserInterfaceEvents1
			, IUserInterfaceEvents2
			, IUserInterfaceEvents3 >
		, Detail::Bases< Detail::CRefCount > >
	{
		Utils::SmartPtr< IWindow, Utils::WeakPointerPolicy > m_window;
		Utils::SmartPtr< IGraphicsDesign > m_design;
		Utils::SmartPtr< IRaster > m_backBitmap;
		Utils::SmartPtr< IRaster > m_bitmapBackImage;
		Types::Point2i m_mouseTouch;
		Types::Recti m_boundTouch;
		Types::Recti m_frameRect;
		Types::Int m_iMouseTouch;
		Types::Vector2i m_resizeLeftUpper;
		Types::Vector2i m_resizeRightBottom;
		Utils::SmartPtr< ICursorShape > m_cursorArrow, m_cursorNWSE, m_cursorNESW, m_cursorNS, m_cursorWE;
		Utils::SmartPtr<> m_objectUnderMouse;
		Utils::SmartPtr<> m_objectPressed;

		enum {
			TOUCH_NONE   = 0,
			TOUCH_LEFT   = 1,
			TOUCH_RIGHT  = 2,
			TOUCH_TOP    = 4,
			TOUCH_BOTTOM = 8
		};

		CWindowUI() : m_iMouseTouch( TOUCH_NONE ), m_resizeLeftUpper( 4, 4 ), m_resizeRightBottom( 4, 4 )
		{
			aloe__try {

				Utils::SmartPtr< IPropertyMap > prop  = Root[ &IFactory::Create ][aloe__string("PropertyMap")]().AutoQ();

				prop[ &IPropertyMap::Property ][ aloe__string("Cursor.SystemResource")] = Utils::copyCast< Types::Int >( IDC_ARROW );
				m_cursorArrow = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();

				prop[ &IPropertyMap::Property ][ aloe__string("Cursor.SystemResource")] = Utils::copyCast< Types::Int >( IDC_SIZENWSE );
				m_cursorNWSE = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();

				prop[ &IPropertyMap::Property ][ aloe__string("Cursor.SystemResource")] = Utils::copyCast< Types::Int >( IDC_SIZENESW );
				m_cursorNESW = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();

				prop[ &IPropertyMap::Property ][ aloe__string("Cursor.SystemResource")] = Utils::copyCast< Types::Int >( IDC_SIZENS );
				m_cursorNS = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();

				prop[ &IPropertyMap::Property ][ aloe__string("Cursor.SystemResource")] = Utils::copyCast< Types::Int >( IDC_SIZEWE );
				m_cursorWE = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();

				prop[ &IPropertyMap::Property ][aloe__string("Bitmap.Filename")] = aloe__string("backImage.bmp");
				m_bitmapBackImage = Root[ &IFactory::Create ][aloe__string("Bitmap")]( prop ).AutoQ();

			} aloe__finish;

		}

		~CWindowUI()
		{
		}

		ThisPtr __init__( Utils::SmartPtr< IWindow > window )
		{
			m_window = window;
			return Super::__init__();
		}

		const Utils::SmartPtr< IRaster > & GetBackBitmap( const Types::Recti &clientRect )
		{
			aloe__try {

				Types::Vector2i bitmapSize;
				//Types::Vector2i screenSize( ::GetSystemMetrics( SM_CXSCREEN ), ::GetSystemMetrics( SM_CYSCREEN ));

				if ( !!m_backBitmap )
				{
					bitmapSize = m_backBitmap[ &IRasterFormat::RasterSize ];
				}

				if ( clientRect.size() != bitmapSize )
					//if ( screenSize != bitmapSize )
				{
					m_backBitmap = Root[ &IFactory::Create ][aloe__string("Bitmap")]().AutoQ();
					m_backBitmap[ &IRasterFormat::RasterSize ] = clientRect.size();
					//m_backBitmap[ &IRasterFormat::RasterSize ] = screenSize;
					m_backBitmap[ &IRasterFormat::PixelType ] = Types::PixelType::RGB;
					//m_backBitmap[ &IRasterFormat::PixelType ] = 0;
				}

			} aloe__finish;

			return m_backBitmap;
		}

		Types::Long DetectResizeAreas( const Types::Recti &bound, const Types::Point2i &mouse )
		{
			Types::Long areas = 0;

			if ( bound.x1 + m_resizeLeftUpper.dx > mouse.x )
			{
				areas |= TOUCH_LEFT;
			}
			if ( bound.x2 - m_resizeRightBottom.dx < mouse.x )
			{
				areas |= TOUCH_RIGHT;
			}
			if ( bound.y1 + m_resizeLeftUpper.dy > mouse.y )
			{
				areas |= TOUCH_TOP;
			}
			if ( bound.y2 - m_resizeRightBottom.dy < mouse.y )
			{
				areas |= TOUCH_BOTTOM;
			}
			if ( 0 == areas )
			{
				areas = TOUCH_LEFT | TOUCH_RIGHT | TOUCH_TOP | TOUCH_BOTTOM;
			}
			return areas;
		}

		void SelectCursorShape( Types::Long areas )
		{
			aloe__try {
				Utils::SmartPtr< ICursorShape > cursor = m_cursorArrow;

				if (( areas == (TOUCH_LEFT | TOUCH_TOP) ) || ( areas == (TOUCH_RIGHT | TOUCH_BOTTOM) ))
				{
					cursor = m_cursorNWSE;
				}
				if (( areas == (TOUCH_RIGHT | TOUCH_TOP )) || ( areas == (TOUCH_LEFT | TOUCH_BOTTOM )))
				{
					cursor = m_cursorNESW;
				}
				if (( areas == ( TOUCH_TOP )) || ( areas == ( TOUCH_BOTTOM )))
				{
					cursor = m_cursorNS;
				}
				if (( areas == ( TOUCH_LEFT )) || ( areas == ( TOUCH_RIGHT )))
				{
					cursor = m_cursorWE;
				}

				Root[ &IUserInputState::CursorShape ] = cursor;
			} aloe__finish;
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

			return false;
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

			aloe__try {

				sender[ &IWindow::DirtyRects ] += rect;

			} aloe__finish;

			return false;
		}

		aloe__method_imp( IUserInterfaceEvents1, Design, argv )
		{
			aloe__try {
				aloe__extract2( IUserInterfaceEvents1, Design, args, argv, sender, design );

				Utils::ArrayOf< Utils::SmartPtr<> > array = sender[ &IContainer::Objects ];
				for ( size_t i = 0, n = array.size(); i < n ; ++i )
				{
					aloe__try {

						Utils::SmartPtr<> widget = array[i];

						widget[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Design ]( widget, design );

					} aloe__finish;
				}
			} aloe__finish;

			return false;
		}

		aloe__method_imp( IUserInterfaceEvents2, Motion, argv )
		{
			aloe__extract2( IUserInterfaceEvents2, Motion, args, argv, sender, pos );

			aloe__try {

				Utils::SmartPtr<> underMouse = sender[ &IContainer::ObjectByPoint ][ pos ].value();

				if ( m_objectUnderMouse.get() != underMouse.get() )
				{
					if ( m_objectUnderMouse.get() )
					{
						m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Leave ]( sender );
					}

					m_objectUnderMouse = underMouse;

					if ( m_objectUnderMouse.get() )
					{
						m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Hover ]( m_objectUnderMouse );
					}
				}

				if ( m_objectUnderMouse.get() )
				{
					m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Motion ]( m_objectUnderMouse, pos );
				}

			} aloe__finish;        


			return true;
		}

		aloe__method_imp( IUserInterfaceEvents2, Hover, argv )
		{
			aloe__extract1( IUserInterfaceEvents2, Hover, args, argv, sender );

			aloe__try {
			} aloe__finish;        

			return true;
		}

		aloe__method_imp( IUserInterfaceEvents2, Leave, argv )
		{
			aloe__extract1( IUserInterfaceEvents2, Leave, args, argv, sender );

			aloe__try {
				if ( m_objectUnderMouse.get() )
				{
					m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Leave ]( m_objectUnderMouse );
				}
			} aloe__finish;        

			return true;
		}

		aloe__method_imp( IUserInterfaceEvents3, Press, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, Press, args, argv, sender, button, pos );

			aloe__try {
				if ( m_objectUnderMouse.get() )
				{
					m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Press ]( m_objectUnderMouse, button, pos );
					m_objectPressed = m_objectUnderMouse;
				}
			} aloe__finish;        

			return true;
		}

		aloe__method_imp( IUserInterfaceEvents3, Release, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, Release, args, argv, sender, button, pos );

			aloe__try {
				if ( m_objectPressed.get() )
				{
					m_objectPressed[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Release ]( m_objectPressed, button, pos );
					m_objectPressed = Types::None();
				}
			} aloe__finish;        

			return true;
		}

		aloe__method_imp( IUserInterfaceEvents3, Click, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, Click, args, argv, sender, button, pos );

			aloe__try {
				if ( m_objectUnderMouse.get() == m_objectPressed.get() )
				{
					m_objectPressed[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Click ]( m_objectPressed, button, pos );
				}
			} aloe__finish;        

			return true;
		}

		aloe__method_imp( IUserInterfaceEvents3, DoubleClick, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, DoubleClick, args, argv, sender, button, pos );

			aloe__try {
				if ( m_objectUnderMouse.get() )
				{
					m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents3::DoubleClick ]( m_objectUnderMouse, button, pos );
				}
			} aloe__finish;        


			return true;
		}

		aloe__method_imp( IUserInputEvents, Key, argv )
		{
			return false;
		}

		aloe__method_imp( IUserInputEvents, Focus, argv )
		{
			return false;
		}


		aloe__method_imp( Aloe::IWindowEvents, Close, argv )
		{
			aloe__extract1( Aloe::IWindowEvents, Close, args, argv, sender );

			return false;
		}

		/*aloe__method_imp( IWindowEvents, Show, argv )
		  {
		  aloe__extract2( IWindowEvents, Show, args, argv, sender, flags );

		  return false;
		  }*/

		aloe__method_imp( Aloe::IWindowEvents, Activate, argv )
		{
			aloe__extract2( Aloe::IWindowEvents, Activate, args, argv, sender, active );

			return false;
		}

		aloe__method_imp( Aloe::IWindowEvents, Focus, argv )
		{
			aloe__extract2( Aloe::IWindowEvents, Focus, args, argv, sender, active );

			return false;
		}

		aloe__method_imp( Aloe::IWindowEvents, LostCapture, argv )
		{
			aloe__extract2( Aloe::IWindowEvents, LostCapture, args, argv, sender, capture );

			return false;
		}

		aloe__method_imp( Aloe::IWindowEvents, Move, argv )
		{
			aloe__extract3( Aloe::IWindowEvents, Move, args, argv, sender, frameRect, flags );

			aloe__try {

				if ( Utils::valueOf( m_frameRect.size() ) != Utils::valueOf( frameRect.size() ))
				{
					m_design = Types::None();

					/*Types::Recti area;
					  area.x2 = frameRect.width();
					  area.y2 = frameRect.height();
					  Utils::SmartPtr< IRegion > region = Root[ &IFactory::Create ][aloe__string("Region")]().AutoQ();
					  region[ &IRegion::RoundRect ]( area, Types::Vector2i(128,128) );
					  sender[ &IWindow::Region ] = region;*/
				}

				m_frameRect = frameRect;

			} aloe__finish;

			return false;
		}

		aloe__method_imp( Aloe::IWindowEvents, Key, argv )
		{
			aloe__extract3( Aloe::IWindowEvents, Key, args, argv, sender, virtKey, isDown );

			return false;
		}

		aloe__method_imp( Aloe::IWindowEvents, Motion, argv )
		{
			aloe__extract2( Aloe::IWindowEvents, Motion, args, argv, sender, position );

			aloe__try {

				if ( m_objectUnderMouse.get() || m_objectPressed.get() )
				{
					return true;
				}

				Types::Recti frame = sender[ &IWindow::FrameRect ];
				Types::Point2i mouse = position;
				mouse.x += frame.x1;
				mouse.y += frame.y1;

				if ( m_iMouseTouch )
				{

					Types::Vector2i distance = mouse - m_mouseTouch;
					Types::Recti bound = m_boundTouch;

					if ( m_iMouseTouch & TOUCH_LEFT )
					{
						bound.x1 += distance.dx;
					}
					if ( m_iMouseTouch & TOUCH_RIGHT )
					{
						bound.x2 += distance.dx;
					}
					if ( m_iMouseTouch & TOUCH_TOP )
					{
						bound.y1 += distance.dy;
					}
					if ( m_iMouseTouch & TOUCH_BOTTOM )
					{
						bound.y2 += distance.dy;
					}

					sender[ &IWindow::FrameRect ] = bound.fixCoords();
				}

				SelectCursorShape( DetectResizeAreas( frame, mouse ));

				m_window[ &IWindow::DirtyRects ] += m_window[ &IWindow::ClientRect ];

			} aloe__finish;

			return true;
		}

		aloe__method_imp( Aloe::IWindowEvents, Button, argv )
		{
			aloe__extract4( Aloe::IWindowEvents, Button, args, argv, sender, position, buttonNo, isDown );
			aloe__try {

				if ( m_objectUnderMouse.get() )
				{
					m_iMouseTouch = TOUCH_NONE;
					return true;
				}

				m_mouseTouch = position;
				m_boundTouch = sender[ &IWindow::FrameRect ];
				m_mouseTouch.x += m_boundTouch.x1;
				m_mouseTouch.y += m_boundTouch.y1;

				Types::Long areas = DetectResizeAreas( m_boundTouch, m_mouseTouch );

				if ( isDown )
				{
					m_iMouseTouch = areas;
				}
				else
				{
					m_iMouseTouch = TOUCH_NONE;
				}

				SelectCursorShape( areas );

			} aloe__finish;
			return false;
		}

		aloe__method_imp( Aloe::IWindowEvents, DoubleClick, argv )
		{
			aloe__extract3( Aloe::IWindowEvents, DoubleClick, args, argv, sender, position, buttonNo );

			return false;
		}

		aloe__method_imp( Aloe::IWindowEvents, Paint, argv )
		{
			aloe__try {

				aloe__extract3( Aloe::IWindowEvents, Paint, args, argv, sender, screen, rect );

				Types::Recti clientRect = sender[ &IFrame::Bound ];

				{
					Utils::SmartPtr<> device = Root[ &IFactory::Create ][aloe__string("GraphicDevice")]();

					device[ &IGraphicDevice::Raster ] = GetBackBitmap( clientRect );

					if ( !m_design )
					{
						m_design = device[ &IGraphicDevice::CreateDesign ]( clientRect );

						Types::Vector2i sizeBackImage = m_bitmapBackImage[ &IRasterFormat::RasterSize ];
						Types::Vector2i sizeBackBuffer = m_backBitmap[ &IRasterFormat::RasterSize ];

						Types::Int xCuts[4] = { 0, 64, -65, -1 };
						Types::Int yCuts[4] = { 0, 64, -65, -1 };

						for ( int row = 0; row < 3; ++row )
						{
							for ( int col = 0; col < 3; ++col )
							{
								Types::Point2i ptSrc1(
										Utils::makePositiveCoord( xCuts[ col + 0 ], 0, sizeBackImage.dx ),
										Utils::makePositiveCoord( yCuts[ row + 0 ], 0, sizeBackImage.dy ));

								Types::Point2i ptSrc2(
										Utils::makePositiveCoord( xCuts[ col + 1 ], 0, sizeBackImage.dx ),
										Utils::makePositiveCoord( yCuts[ row + 1 ], 0, sizeBackImage.dy ));

								Types::Recti rcSrc( ptSrc1, ptSrc2 );

								Types::Point2i ptDst1(
										Utils::makePositiveCoord( xCuts[ col + 0 ], 0, sizeBackBuffer.dx ),
										Utils::makePositiveCoord( yCuts[ row + 0 ], 0, sizeBackBuffer.dy ));

								Types::Point2i ptDst2(
										Utils::makePositiveCoord( xCuts[ col + 1 ], 0, sizeBackBuffer.dx ),
										Utils::makePositiveCoord( yCuts[ row + 1 ], 0, sizeBackBuffer.dy ));

								Types::Recti rcDst( ptDst1, ptDst2 );

								Types::Color32 color(255,255,255);

								m_design[ &IDrawing::DrawRaster ]( rcDst, m_bitmapBackImage, rcSrc, color, 0, 0x0 );
							}
						}

						sender[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Design ]( sender, m_design );
					}

					device[ &IGraphicDevice::RenderDesign ]( m_design, rect );
				}

				screen[ &Win32::IDevContext::DrawBitmap ]( rect, m_backBitmap.AutoQ(), rect, 255, 0 );

			} aloe__finish;

			return true;
		}


		aloe__method_imp( Win32::IWindowEvents, Event, argv )
		{
			aloe__extract4( Win32::IWindowEvents, Event, args, argv, sender, message, wParam, lParam );

			return true;
		};

	};// CWindowUI
};//Aloe

