#ifndef ALOE_UI
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'UI.cpp'."
#endif

namespace Aloe {

    struct CRelativeFrame
        : Detail::Implementation
        < CRelativeFrame
        , Detail::Interfaces< IFrame, IFrameClient >
        , Detail::Bases< Detail::CRefCount > >
    {
        Types::Vector2i m_distP1;
        Types::Vector2i m_distP2;
        Types::Recti m_bound;
        Utils::SmartPtr< IFrame, Utils::WeakPointerPolicy > m_frame;
        
        typedef std::set< Utils::SmartPtr< IFrameClient > > SetOfClients_t;
        SetOfClients_t m_setOfClients;

        void CalcBound( const Types::Recti &rect )
        {
            m_bound.x1 = Utils::makePositiveCoord( m_distP1.dx, rect.x1, rect.x2 );
            m_bound.y1 = Utils::makePositiveCoord( m_distP1.dy, rect.y1, rect.y2 );
            m_bound.x2 = Utils::makePositiveCoord( m_distP2.dx, rect.x1, rect.x2 );
            m_bound.y2 = Utils::makePositiveCoord( m_distP2.dy, rect.y1, rect.y2 );
        }

        ThisPtr __init__( const Types::Vector2i &distP1, const Types::Vector2i &distP2 )
        {
            m_distP1 = distP1;
            m_distP2 = distP2;
            return Super::__init__();
        }
        
        aloe__property_imp_put( IFrame, Bound, bound )
        {
            m_bound = bound;
        }

        aloe__property_imp_get( IFrame, Bound )
        {
            return m_bound;
        }

        aloe__property_imp_put( IFrame, Parent, frame )
        {
            m_frame = frame;
        }

        aloe__property_imp_get( IFrame, Parent )
        {
            return m_frame;
        }

        aloe__property_imp_put( IFrame, Clients, clients )
        {
            m_setOfClients.clear();

            for ( size_t i = 0, n = clients.size(); i < n; ++i )
            {
                m_setOfClients.insert( clients[i] );
            }
        }

        aloe__property_imp_get( IFrame, Clients )
        {
            Utils::VectorOf< Utils::SmartPtr< IFrameClient > > array;

            for ( SetOfClients_t::iterator iter = m_setOfClients.begin(); iter != m_setOfClients.end(); ++iter )
            {
                array.push_back( *iter );
            }

            return array.m_array;
        }

        aloe__property_imp_append( IFrame, Clients, client )
        {
            return m_setOfClients.insert( client ).second;
        }

        aloe__property_imp_remove( IFrame, Clients, client )
        {
            SetOfClients_t::iterator iter = m_setOfClients.find( client );
            if ( iter != m_setOfClients.end() )
            {
                m_setOfClients.erase( iter );
                return true;
            }
            else {
                return false;
            }
        }

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

            CalcBound( rect );
            
            for ( SetOfClients_t::iterator iter = m_setOfClients.begin(); iter != m_setOfClients.end(); ++iter )
            {
                (*iter)[ &IFrameClient::Move ]( m_bound );
            }

	    return Types::None();
        }
    };//CRelativeFrame

    
};//Aloe
