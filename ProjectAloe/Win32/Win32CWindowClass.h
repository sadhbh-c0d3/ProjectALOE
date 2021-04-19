#ifndef ALOE_WIN32_SYSTEM
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'Win32System.cpp'."
#endif

namespace Aloe {
    namespace Win32 {
        struct CWindowClass
            : Detail::Implementation
            < CWindowClass
            , Detail::Interfaces< Win32::IWindowClass >
            , Detail::Bases< Detail::CRefCount >
            , 0x1003 >
        {
            ::HWND m_hWnd;
            
            ThisPtr __init__( ::HWND hWnd )
            {
                m_hWnd = hWnd;
		return Super::__init__();
            }
            
            //
            // Win32::IWindowClass
            //

            aloe__property_imp_put( Win32::IWindowClass, Style, style )
            {
                SetClassLong( m_hWnd, GCL_STYLE, style );
            }

            aloe__property_imp_get( Win32::IWindowClass, Style )
            {
                return GetClassLong( m_hWnd, GCL_STYLE );
            }
           
            aloe__prop_map_imp_put( Win32::IWindowClass, Long, idx, value )
            {
                SetClassLong( m_hWnd, idx, value );
            }
           
            aloe__prop_map_imp_get( Win32::IWindowClass, Long, idx )
            {
                return GetClassLong( m_hWnd, idx );
            }
            
        };//CWindowClass
    };//Win32
};//Aloe

