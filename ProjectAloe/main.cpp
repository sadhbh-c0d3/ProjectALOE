#define _WIN32_WINNT 0x0500
#define WINVER 0x0410
#define _CRT_SECURE_NO_DEPRECATE

#include "Aloe/aloeWin32.h"

#include <stdio.h>
#include <set>
#include <map>

#pragma warning(disable:4250)

#define ALOE_UI
#include "UI/CButtonDesigner.h"
#include "UI/CEntity.h"
#include "UI/CRelativeFrame.h"
#include "UI/CWindowUI.h"

namespace Aloe {

    Utils::SmartPtr< IFactory > Root;

};//Aloe


Aloe::Utils::SmartPtr< Aloe::CEntity > CreateButton(
		const Aloe::Utils::SmartPtr< Aloe::IContainer > &container,
		const Aloe::Utils::SmartPtr< Aloe::CRelativeFrame > &frame,
		const Aloe::Types::Vector2i &leftUpper,
		const Aloe::Types::Vector2i &rightBottom,
		const Aloe::Types::String   &strName,
		const Aloe::Types::String	&textLabel,
		const Aloe::Utils::SmartPtr< Aloe::IPropertyMap > &prop )
{
	aloe__try {

		Utils::SmartPtr< CRelativeFrame > frame1;
		Utils::SmartPtr< CEntity > entity;
		Utils::SmartPtr< CButtonDesigner > designer;

		frame1   = ( new CRelativeFrame  )->__init__( leftUpper, rightBottom );
		entity   = ( new CEntity         )->__init__( strName );
		designer = ( new CButtonDesigner )->__init__( entity, textLabel, prop );

		entity[ &IEventSource::Listeners ] += designer;

		entity[ &IFrameClient::Frame     ] = frame1;
		frame1[ &IFrame::Clients         ] += entity;

		frame1[ &IFrameClient::Frame     ] = frame;
		frame [ &IFrame::Clients         ] += frame1;

		container[ &IContainer::Objects	 ] += entity;
		entity	 [ &IEntity::Container   ] = container;

		return entity;

	} aloe__finish;

	return Aloe::Types::None();
}
	
namespace {
	using namespace Aloe;

	struct CButtonListener_Close : CButtonListener
	{
		aloe__method_imp( IUserInterfaceEvents3, Click, argv )
		{
			aloe__extract3( IUserInterfaceEvents3, Click, args, argv, sender, button, pos );

			Utils::SmartPtr< IWindow > window = Utils::findOwnerWindow( sender );
			if ( !!window )
			{
				window[ &IWindow::Close ]();
			}
			
			return false;
		}
	};
};//using Aloe

int main()
{
    aloe__try {
    
		Root = Win32::Initialize( ::GetModuleHandle(NULL) );

		Utils::SmartPtr<> wnd = Root[ &Win32::IWindowFactory::CreateWindow ]
            ( aloe__string("TestClass"), CS_HREDRAW | CS_VREDRAW,
              aloe__string("TestWindow"), WS_POPUP,
#ifdef WIN32
			  WS_EX_LAYERED,
#else
			  0,
#endif
			  Types::Recti( Types::Point2i(10,10), Types::Vector2i( 640, 480 )),
              (HWND)NULL, (HMENU)NULL
            );

        aloe__try {
        
            wnd[ &Win32::IWindow::Class ][ &Win32::IWindowClass::Style ] = 
                wnd[ &Win32::IWindow::Class ][ &Win32::IWindowClass::Style ] | CS_DBLCLKS;
            
            wnd[ &IEventSource::Listeners ] += ( new CWindowUI )->__init__( wnd.AutoQ() );

            aloe__try {
                Utils::SmartPtr< CRelativeFrame > frame;

                frame = ( new CRelativeFrame  )->__init__( Types::Vector2i(10,-201), Types::Vector2i(-11,-11) );
                
                wnd[ &IFrame::Clients ] += frame;
                frame[ &IFrameClient::Frame ] = wnd.AutoQ();

				Utils::SmartPtr< IPropertyMap > prop  = Root[ &IFactory::Create ][ ClsID_PropertyMap ]().AutoQ();
				
				prop[ &IPropertyMap::Property ][ ProID_BitmapFilename ] = aloe__string("buttonNormal.bmp");
				prop[ &IPropertyMap::Property ][ ProID_ButtonBitmapNormal ] = Root[ &IFactory::Create ][ ClsID_Bitmap ]( prop );
				prop[ &IPropertyMap::Property ][ ProID_BitmapFilename ] = aloe__string("buttonHighlight.bmp");
				prop[ &IPropertyMap::Property ][ ProID_ButtonBitmapHighlight ] = Root[ &IFactory::Create ][ ClsID_Bitmap ]( prop );
				prop[ &IPropertyMap::Property ][ ProID_BitmapFilename ] = aloe__string("buttonPressed.bmp");
				prop[ &IPropertyMap::Property ][ ProID_ButtonBitmapPressed ] = Root[ &IFactory::Create ][ ClsID_Bitmap ]( prop );
				
				Utils::SmartPtr< IFont > font = Root[ &IFactory::Create ][aloe__string("Font")]().AutoQ();
				font[ &IFont::Family ] = aloe__string("Arial");
				font[ &IFont::Size ] = 20;
				font[ &IFont::Weight ] = FW_BOLD;
				font[ &IFont::Encoding ] = EASTEUROPE_CHARSET;
				prop[ &IPropertyMap::Property ][ ProID_ButtonFont ] = font;

				Utils::SmartPtr<> button1 =
					CreateButton( wnd.AutoQ(), frame,
						Types::Vector2i(10,10), Types::Vector2i(110,50),
						aloe__string("Button1"), aloe__string("Hello !!!"), prop );

				Utils::SmartPtr<> button2 =
					CreateButton( wnd.AutoQ(), frame,
						Types::Vector2i(-111,10), Types::Vector2i(-11,50),
						aloe__string("Button2"), aloe__string("Goodbye !!!"), prop );

				button2[ &IEventSource::Listeners ] += ( new CButtonListener_Close )->__init__();

            } aloe__finish;
            
            
            wnd[ &IWindow::ClientRect ] = Types::Recti( Types::Point2i(0,0), Types::Vector2i( 300, 480 ));

#ifdef WIN32
            wnd[ &Win32::ILayeredWindow::Opacity ] = 225;
            wnd[ &Win32::ILayeredWindow::ColorKey ] = Types::Color32( 255, 0, 255 );
            wnd[ &Win32::ILayeredWindow::Flags ] = LWA_COLORKEY | LWA_ALPHA;
            wnd[ &Win32::ILayeredWindow::Commit ]();
#endif

        } aloe__finish;

        
        Root[ &Win32::IMessageLoop::Run ]();

    } aloe__finish;

    return 0;
}

int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    return main();
}


