
#define _WIN32_WINNT 0x0500
#define WINVER 0x0410
#define _UNICODE 1
#define UNICODE 1

#include <windows.h>

#include "Aloe/aloeWin32.h"
#include <set>
#include <map>

#define ALOE_WIN32_SYSTEM
#include "Win32CFile.h"
#include "Win32CGDIObject.h"
#include "Win32CGDIDesign.h"
#include "Win32CWindowClass.h"
#include "Win32CWindow.h"
#include "Win32CFactory.h"

#pragma warning(disable:4250)

namespace Aloe {
	namespace Utils {
		void DebugOut( Types::CStr message )
		{
			::OutputDebugStringA( message );
		}
	};

    namespace Win32 {

        CGDIObject::DictGDIObjects_t CGDIObject::s_dictObjects;
       
        CWindow::DictWindows_t CWindow::s_dictWindows;

        Utils::SmartPtr< IFactory > Initialize( HINSTANCE hInstance )
        {
            return ( new CFactory )->__init__( hInstance )[ &IFactory::This ];
        }

    };//Win32
};//Aloe

