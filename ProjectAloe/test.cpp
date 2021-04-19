#include "Aloe/aloeWin32.h"


int main()
{
    aloe__try {

	Root = Win32::Initialize( ::GetModuleHandle( NULL ));

	Utils::SmartPtr<> wnd =
	    Root[ &Win32::IWindowFactory::CreateWindow ](
		    aloe__string("TestClass"), CS_HREDRAW | CS_VREDRAW,
		    aloe__string("TestWindow"), WS_OVERLAPPEDWINDOW, 0,
		    Types::Recti(
			Types::Point2i(10,10),
			Types::Vector2i( 640, 480 )),
		    (HWND)NULL, (HMENU)NULL );

	    Root[ &IFactory::Create ][aloe__string("Font")]();
	

    } aloe__finish;
    
    return 0;
}
