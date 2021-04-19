#ifndef ALOE_UI
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'UI.cpp'."
#endif

namespace Aloe {

    struct CEntity
        : Detail::Implementation
        < CEntity
        , Detail::Interfaces< IEntity, IEventSource, IFrameClient >
        , Detail::Bases< Detail::CRefCount > >
    {
        ThisPtr __init__( const Types::String &name )
        {
            m_name = name;

            return Super::__init__();
        }
            
        //
        // IEntity
        //

        Types::String m_name;
        Utils::SmartPtr< IContainer, Utils::WeakPointerPolicy > m_container;
        
        aloe__property_imp_put( IEntity, Name, name )
        {
            m_name = name;
        }
        
        aloe__property_imp_get( IEntity, Name )
        {
            return m_name;
        }
        
        aloe__property_imp_put( IEntity, Container, container)
        {
            m_container = container;
        }
        
        aloe__property_imp_get( IEntity, Container )
        {
            return m_container;
        }
       
        //
        // IFrameClient
        //
        
        Utils::SmartPtr< IFrame, Utils::WeakPointerPolicy > m_frame;
        
        aloe__property_imp_put( IFrameClient, Frame, frame )
        {
            m_frame = frame;
        }
        
        aloe__property_imp_get( IFrameClient, Frame )
        {
            return m_frame;
        }

        aloe__method_imp( IFrameClient, Move, argv )
        {
            aloe__extract1( IFrameClient, Move, args, argv, rect );

            Types::Long flags = 1;

            __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents::Move ]( __self__(), rect, flags );

            return Types::None();
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
    };//CEntity
    
    
};//Aloe
