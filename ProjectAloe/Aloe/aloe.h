#ifndef ALOE_INCLUDED_ALOE_H
#define ALOE_INCLUDED_ALOE_H

#pragma warning(disable:4250)

#include "Aloe/aloePropertyMap.h"
#include "Aloe/aloeFormat.h"

#define aloe__method( I, N, Ret, Args ) \
    typedef aloe__##Ret  N##__resultType; \
    typedef aloe__##Args N##__argsType; \
    virtual N##__resultType N ( const N##__argsType & ) = 0;

#define aloe__indexer_none( I, N, IndexType, ValueType, Getter, Setter, AR, AA, RR, RA, Appender, Remover, ResultType, ArgsType, Caller ) \
    typedef aloe__##ValueType N##__valueType;\
    typedef aloe__##AR    N##__appendResultType;\
    typedef aloe__##AA    N##__appendArgType;\
    typedef aloe__##RR    N##__removeResultType;\
    typedef aloe__##RA    N##__removeArgType;\
    typedef aloe__##ResultType N##__resultType;\
    typedef aloe__##ArgsType   N##__argsType;\
    aloe__property__( I, N, N##__valueType, \
            N##__appendResultType, N##__appendArgType, N##__removeResultType, N##__removeArgType, \
            N##__resultType, N##__argsType, Getter, Setter, Appender, Remover, Caller )

#define aloe__indexer_____ aloe__indexer_none
#define aloe__indexer_ aloe__indexer_none

#define aloe__indexer_map( I, N, IndexType, ValueType, Getter, Setter, AR, AA, RR, RA, Appender, Remover, ResultType, ArgsType, Caller ) \
    typedef aloe__##IndexType N##__indexType;\
    typedef aloe__##ValueType N##__valueType;\
    typedef aloe__##AR    N##__appendResultType;\
    typedef aloe__##AA    N##__appendArgType;\
    typedef aloe__##RR    N##__removeResultType;\
    typedef aloe__##RA    N##__removeArgType;\
    typedef aloe__##ResultType N##__resultType;\
    typedef aloe__##ArgsType   N##__argsType;\
    aloe__prop_map__( I, N, N##__valueType, \
            N##__appendResultType, N##__appendArgType, N##__removeResultType, N##__removeArgType, \
            N##__resultType, N##__argsType, N##__indexType, Getter, Setter, Appender, Remover, Caller )
    
#define aloe__prop( I, N, Indexer, IndexType, Getter, Setter, ValueType, Appender, AR, AA, Remover, RR, RA, Caller, ResultType, ArgsType ) \
    aloe__indexer_##Indexer( I, N, IndexType, ValueType, Getter, Setter, AR, AA, RR, RA, Appender, Remover, ResultType, ArgsType, Caller )
    
#define aloe__Query_impl_interfaces_0()
    
#define aloe__Query_impl_interfaces_1( I1 ) \
    if ( iid == aloe__iid_of( I1 )) \
    { \
        reinterpret_cast< I1 *& >( argPtr ) = this; \
        argCount = Aloe::Detail::add_ref( this ); \
        return true; \
    }

#define aloe__Query_impl_interfaces_2( I1, I2 ) \
    aloe__Query_impl_interfaces_1( I1 ) \
    else aloe__Query_impl_interfaces_1( I2 )

#define aloe__Query_impl_interfaces_3( I1, I2, I3 ) \
    aloe__Query_impl_interfaces_2( I1, I2 ) \
    else aloe__Query_impl_interfaces_1( I3 )

#define aloe__Query_impl_interfaces_4( I1, I2, I3, I4 ) \
    aloe__Query_impl_interfaces_3( I1, I2, I3 ) \
    else aloe__Query_impl_interfaces_1( I4 )

#define aloe__Query_impl_interfaces_5( I1, I2, I3, I4, I5 ) \
    aloe__Query_impl_interfaces_4( I1, I2, I3, I4 ) \
    else aloe__Query_impl_interfaces_1( I5 )

#define aloe__Query_impl_interfaces_6( I1, I2, I3, I4, I5, I6 ) \
    aloe__Query_impl_interfaces_5( I1, I2, I3, I4, I5 ) \
    else aloe__Query_impl_interfaces_1( I6 )

#define aloe__Query_impl_interfaces_7( I1, I2, I3, I4, I5, I6, I7 ) \
    aloe__Query_impl_interfaces_6( I1, I2, I3, I4, I5, I6 ) \
    else aloe__Query_impl_interfaces_1( I7 )

#define aloe__Query_impl_interfaces_8( I1, I2, I3, I4, I5, I6, I7, I8 ) \
    aloe__Query_impl_interfaces_8( I1, I2, I3, I4, I5, I6, I7 ) \
    else aloe__Query_impl_interfaces_1( I8 )

#define aloe__Query_impl_interfaces_9( I1, I2, I3, I4, I5, I6, I7, I8, I9 ) \
    aloe__Query_impl_interfaces_8( I1, I2, I3, I4, I5, I6, I7, I8 ) \
    else aloe__Query_impl_interfaces_1( I9 )

#define aloe__Query_impl_bases_0() \
    aloe__Query_impl_interfaces_1( Aloe::IProvider )

#define aloe__Query_impl_bases_1( B1 ) \
    if ( B1::Query( iid, argPtr, argCount )) { return true; }

#define aloe__Query_impl_bases_2( I1, I2 ) \
    aloe__Query_impl_bases_1( I1 ) \
    else aloe__Query_impl_bases_1( I2 )

#define aloe__Query_impl_bases_3( I1, I2, I3 ) \
    aloe__Query_impl_bases_2( I1, I2 ) \
    else aloe__Query_impl_bases_1( I3 )

#define aloe__Query_impl_bases_4( I1, I2, I3, I4 ) \
    aloe__Query_impl_bases_3( I1, I2, I3 ) \
    else aloe__Query_impl_bases_1( I4 )

#define aloe__Query_impl_bases_5( I1, I2, I3, I4, I5 ) \
    aloe__Query_impl_bases_4( I1, I2, I3, I4 ) \
    else aloe__Query_impl_bases_1( I5 )

#define aloe__Query_impl_bases_6( I1, I2, I3, I4, I5, I6 ) \
    aloe__Query_impl_bases_5( I1, I2, I3, I4, I5 ) \
    else aloe__Query_impl_bases_1( I6 )

#define aloe__Query_impl_bases_7( I1, I2, I3, I4, I5, I6, I7 ) \
    aloe__Query_impl_bases_6( I1, I2, I3, I4, I5, I6 ) \
    else aloe__Query_impl_bases_1( I7 )

#define aloe__Query_impl_bases_8( I1, I2, I3, I4, I5, I6, I7, I8 ) \
    aloe__Query_impl_bases_8( I1, I2, I3, I4, I5, I6, I7 ) \
    else aloe__Query_impl_bases_1( I8 )

#define aloe__Query_impl_bases_9( I1, I2, I3, I4, I5, I6, I7, I8, I9 ) \
    aloe__Query_impl_bases_8( I1, I2, I3, I4, I5, I6, I7, I8 ) \
    else aloe__Query_impl_bases_1( I9 )


#define aloe__Query_impl( ICount, INames, BCount, BNames ) \
    Aloe::Types::Bool QueryCounterAddRef( Aloe::IRefCount * &pCount ) \
    { \
        pCount = Aloe::Detail::add_ref( this ); \
        return (0 != pCount);\
    } \
    Aloe::Types::Bool Query( const Aloe::Types::Identifier &iid, Aloe::Types::RawPointer &argPtr, Aloe::IRefCount * &argCount ) \
    { \
        aloe__Query_impl_interfaces_##ICount INames; \
        aloe__Query_impl_bases_##BCount BNames; \
        return false; \
    }
    
#define aloe__interface_common( I ) \
    static Aloe::Utils::SmartPtr< I > This( const Aloe::Utils::SmartPtr< I > &ptr ) \
    { \
        return ptr; \
    } \

#define aloe__interface( I ) struct I : virtual Aloe::IProvider

#define aloe__iid( I ) \
    static const Aloe::Types::Identifier & IId () \
    { \
        static Aloe::Types::Identifier s_IId = Aloe::GetIdOfName( aloe__string( #I )); \
        return s_IId; \
    } \
    aloe__interface_common( I )

#define aloe__iid__const( I, iid ) \
    enum { aloe_IID = iid }; \
    static const Aloe::Types::Identifier & IId () \
    { \
        static Aloe::Types::Identifier s_iid( Aloe::Types::LongPointer( iid )); \
        return s_iid; \
    } \
    aloe__interface_common( I )


#define aloe__property_imp_prefix( I )
//#define aloe__property_imp_prefix( I ) I::

#define aloe__method_imp( I, N, n ) aloe__resultRet( I, N ) aloe__property_imp_prefix( I ) N ( aloe__argsArg( I, N, n ) )

#define aloe__property_imp_get( I, N ) aloe__valueRet( I, N ) aloe__property_imp_prefix( I ) get_##N()
#define aloe__property_imp_put( I, N, n ) void aloe__property_imp_prefix( I ) put_##N( aloe__valueArg( I, N, n ))
#define aloe__property_imp_append( I, N, n ) aloe__appendRet( I, N ) aloe__property_imp_prefix( I ) append_##N( aloe__appendArg( I, N, n ))
#define aloe__property_imp_remove( I, N, n ) aloe__removeRet( I, N ) aloe__property_imp_prefix( I ) remove_##N( aloe__removeArg( I, N, n ))
#define aloe__property_imp_call( I, N, n ) aloe__resultRet( I, N ) aloe__property_imp_prefix( I ) call_##N( aloe__argsArg( I, N, n ))

#define aloe__prop_map_imp_get( I, N, i ) aloe__valueRet( I, N ) aloe__property_imp_prefix( I ) get_##N( aloe__indexArg( I, N, i ))
#define aloe__prop_map_imp_put( I, N, i, n ) void aloe__property_imp_prefix( I ) put_##N( aloe__indexArg( I, N, i ), aloe__valueArg( I, N, n ))
#define aloe__prop_map_imp_append( I, N, i, n ) aloe__appendRet( I, N ) aloe__property_imp_prefix( I ) append_##N( aloe__indexArg( I, N, i ), aloe__appendArg( I, N, n ))
#define aloe__prop_map_imp_remove( I, N, i, n ) aloe__removeRet( I, N ) aloe__property_imp_prefix( I ) remove_##N( aloe__indexArg( I, N, i ), aloe__removeArg( I, N, n ))
#define aloe__prop_map_imp_call( I, N, i, n ) aloe__resultRet( I, N ) aloe__property_imp_prefix( I ) call_##N( aloe__indexArg( I, N, i ), aloe__argsArg( I, N, n ))

    
#ifdef ALOE_DEBUG_RUNTIMEINFO
#include <map>
namespace Aloe {
    namespace Detail {
        template< class Interface > struct RuntimeInfo
        {
            RuntimeInfo( const char *name, void *ptr )
            {
                GetDict()[ ptr ] = name;
            }

            static const char * GetName( void *ptr )
            {
                std::map< void *, const char * >::iterator iter = GetDict().find( ptr );
                if ( GetDict().end() != iter )
                    return iter->second;
                else
                    return NULL;
            }

            static std::map< void *, const char * > & GetDict()
            {
                static std::map< void *, const char * > s_dict;
                return s_dict;
            }
        };
    };
};
    
#define aloe__runtime_method( I, N ) static Aloe::Detail::RuntimeInfo< I > sRM_ ## I ## N( #I "::" #N, Aloe::Utils::copyCast< void *>( &I::N ));
#define aloe__runtime_method_ns( NS, I, N ) static Aloe::Detail::RuntimeInfo< I > sRM_ ## I ## N( #NS "." #I "." #N, Aloe::Utils::copyCast< void *>( &I::N ));
#define aloe__runtime_prop( I, N )
#define aloe__runtime_prop_ns( NS, I, N )
#define aloe__runtime_map( I, N )
#define aloe__runtime_map_ns( NS, I, N )

#else

#define aloe__runtime_method( I, N )
#define aloe__runtime_method_ns( NS, I, N )
#define aloe__runtime_prop( I, N )
#define aloe__runtime_prop_ns( NS, I, N )
#define aloe__runtime_map( I, N )
#define aloe__runtime_map_ns( NS, I, N )
#endif

#define aloe__iid_of( I ) I::IId()
#define aloe__iid_const_of( I ) I::aloe_IID

#define aloe__debugOut( S ) Aloe::Utils::DebugOut( S );

#define aloe__report( S ) { \
    char buffer[1024] = {0,}; \
    _snprintf_s( buffer, 1024, _TRUNCATE, "%s(%i): %s\n", __FILE__, __LINE__, S ); \
    aloe__debugOut( buffer ); }

#define aloe__try \
{ bool aloe__bTrialFailed = false; using namespace Aloe; \
    try {

#define aloe__retry \
    } catch( Errors::Error_InterfaceNotFound & ) { aloe__bTrialFailed = true; \
        aloe__report("interface not found - retrying"); \
    } if ( aloe__bTrialFailed ) try { aloe__bTrialFailed = false; \
        
#define aloe__finish \
    } catch( Errors::Error_InterfaceNotFound & ) { aloe__bTrialFailed = true; \
        aloe__report("interface not found - no trials left"); \
    } }



namespace Aloe {
	namespace Utils {
		extern void DebugOut( Types::CStr message );
	};

    namespace Detail {

        inline IRefCount * add_ref( IRefCount *pCount )
        {
            pCount->AddRef();
            return pCount;
        }
        
        template< class Interface >
            IRefCount * add_ref( const Utils::SmartPtr< Interface > &ptr )
            {
                YOU_CANNOT_ADD_REF_OBJECT_KEPT_VIA_SMART_POINTER;
            }

        inline IRefCount * add_ref( ... )
        {
            return NULL;
        }

        
        template< class Interface, class R, class Meth >
            struct MethodCaller : Aloe::Utils::SmartPtr< Interface > 
            {
                Meth meth;

                MethodCaller( Meth m, const Aloe::Utils::SmartPtr< Interface > &p )
                    : meth( m )
                    , Aloe::Utils::SmartPtr< Interface >( p )
                {
                }

                R operator () ()
                {
                    return ((*(get())).*meth)();
                }
                
#define ALOE_PP_MethodCaller__Generic( N ) \
                template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) > \
                    R operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, )) \
                    {\
                        return ((*(get())).*meth)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) ); \
                    }
                
                ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, MethodCaller__Generic );
            };
        
        template< class Interface, class R ALOE_PP_TEMPLATE_MAX( COMMA, COMMA, class, B,, ) >
            struct MethodCaller< Interface, R
            , R (Interface::*) ( const Aloe::Types::Tuple< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, getClass, B,, ) > & ) >
            : Aloe::Utils::SmartPtr< Interface > 
            {
                typedef R (Interface::*Meth) ( const Aloe::Types::Tuple< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, getClass, B,, ) > & );
                Meth meth;

                MethodCaller( Meth m, const Aloe::Utils::SmartPtr< Interface > &p )
                    : meth( m )
                    , Aloe::Utils::SmartPtr< Interface >( p )
                {
                }
                
                R operator () ()
                {
                    Aloe::Types::Tuple<> t;
                    return ((*(get())).*meth)( t );
                }

                R operator () ( const Aloe::Types::Tuple< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, getClass, B,, ) > &t )
                {
                    return ((*(get())).*meth)( t );
                }

#define ALOE_PP_MethodCaller__Tuple( N ) \
                template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) > \
                    R operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, )) \
                    {\
                        Aloe::Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) >t \
                            ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, )); \
                            return ((*(get())).*meth)( t ); \
                    }

                ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, MethodCaller__Tuple );

            };
        
        
        template< class Interface, class R >
            struct MethodCaller< Interface, R, R (Interface::*)( const Aloe::Types::None & ) > : Aloe::Utils::SmartPtr< Interface > 
            {
                typedef R (Interface::*Meth)( const Aloe::Types::None & );
                Meth meth;

                MethodCaller( Meth m, const Aloe::Utils::SmartPtr< Interface > &p )
                    : meth( m )
                    , Aloe::Utils::SmartPtr< Interface >( p )
                {
                }

                R operator () ()
                {
                    Aloe::Types::None n;
                    return ((*(get())).*meth)( n );
                }
            };

        


        template< class Interface, class ReferenceType >
            ReferenceType
            make_property( const Utils::SmartPtr< Interface > &ptr, ReferenceType property( const Utils::SmartPtr< Interface > & ))
            {
                return property( ptr );
            }
        
        template< class Ptr, class Interface, class ReferenceType >
            ReferenceType
            make_property( const Ptr &ptr, ReferenceType property( const Utils::SmartPtr< Interface > & ))
            {
                Utils::SmartPtr< Interface > p;
                if ( !p.QueryFrom( ptr ))
                {
                    throw Errors::InterfaceNotFound< Interface >();
                }
                    
                return property( p );
            }

#define ALOE_PP_make_property__definition( N ) \
        template< class Interface, class R ALOE_PP_TEMPLATE_R( N, COMMA, COMMA, class, A,, ) > \
            MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) > \
            make_property( const Utils::SmartPtr< Interface > &ptr, R (Interface::*property)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) ) \
            {\
                return Detail::MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) >( property, ptr );\
            } \
        template< class Ptr, class Interface, class R ALOE_PP_TEMPLATE_R( N, COMMA, COMMA, class, A,, ) > \
            MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) > \
            make_property( const Ptr &ptr, R (Interface::*property)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) ) \
            {\
                Utils::SmartPtr< Interface > p; \
                if ( !p.QueryFrom( ptr )) \
                { \
                    throw Errors::InterfaceNotFound< Interface >(); \
                } \
                return Detail::MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) >( property, p ); \
            }
        
        ALOE_PP_make_property__definition( 0 );
        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, make_property__definition );
        
    };//Detail
    
    inline Types::Identifier GetIdOfName( const Types::String &csName );

    struct IProvider;
    struct IFactory;
    struct IEvent;
    struct IEventSource;
    struct IStringsDictionary;
    struct IStringEncoding;
    
    struct IProvider
    {
        aloe__iid__const( IProvider, 0x1 );
        
        virtual Aloe::Types::Bool
            Query(
                    const Aloe::Types::Identifier &iid,
                    Aloe::Types::RawPointer &ptr,
                    Aloe::IRefCount * &pCount
                 ) = 0;

        virtual Aloe::Types::Bool
            QueryCounterAddRef(
                    Aloe::IRefCount * &pCount
                    ) = 0;

        virtual Aloe::Types::Bool
            QueryRawPtr(
                    Types::SizeType iRawId,
                    Aloe::Types::RawPointer &ptr,
                    Aloe::IRefCount * &pCount
                    )
            {
                ptr = NULL; pCount = NULL; return false;
            }

#ifndef NDEBUG
        void *m_impl;
#endif
    };
    
    aloe__interface( IFactory )
    {
        aloe__iid__const( IFactory, 0x2 );

        aloe__prop( IFactory, IdOfName
                , map , type( String )
                , get , ____, type( Identifier )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IFactory, Parent
                , ____, ____
                , get , put , pointer( IFactory )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IFactory, Create
                , map , type( String )
                , get , put , pointer( IFactory )
                , ____, ____, ____
                , ____, ____, ____
                , call, pointer( IProvider ), tuple1(
                    arg( args, In, pointer( IProvider ))
                    ));

        aloe__method( IFactory, Load
                , type( Bool )
                , tuple1(
                    arg( library, In, type( String ))
                    ));

    };
    
    extern Utils::SmartPtr< IFactory > Root;

    inline Types::Identifier GetIdOfName( const Types::String &csName )
    {
        return Root[ IFactory::IdOfName ][ csName ];
    }
    
    
    aloe__interface( IEvent )
    {
        aloe__iid__const( IEvent, 0x3 );
        
        aloe__method( IEvent, Invoke
                , type( Bool )
                , arg( listener, In, pointer( IProvider ))
                );
    };
    
    namespace Detail {
    
        struct Event
        {
            Utils::SmartPtr< IEventSource > obj;

            Event( const Utils::SmartPtr< IEventSource > &o ) : obj ( o )
            {
            }
            
            template< class Interface, class Args >
                struct Proxy : Utils::SmartPtr< IEventSource >
                {
                    typedef Types::Bool (Interface::*Meth)( const Args & );
                    Meth meth;
                    
                    Proxy( const Event &e, Meth m ) : Utils::SmartPtr< IEventSource >( e.obj ), meth( m )
                    {
                    }

                    Types::None Call( const Args &args );

#define ALOE_PP_Event__Proxy__call( N ) \
                    template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) >  \
                        Types::None operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, ) ) \
                        { \
                            return Call( Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
                                    ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) )); \
                        }
                
                    ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, Event__Proxy__call );

                };
            
            template< class Interface, class Args >
                Proxy< Interface, Args >
                operator [] ( Types::Bool (Interface::*event)( const Args & ) )
                {
                    return Proxy< Interface, Args >( *this, event );
                }
        };
    
    };//Detail
    
    
    aloe__interface( IEventSource )
    {
        aloe__iid__const( IEventSource, 0x4 );
    
        aloe__prop( IEventSource, Listeners
                , ____, ____
                , ____, ____, ____
                , append, type( Bool ), pointer( IProvider )
                , remove, type( Bool ), pointer( IProvider )
                , ____, ____, ____ );
    
        aloe__method( IEventSource, RaiseEvent
                , ____
                , arg( event, In, pointer( IEvent ))
                );

        static Detail::Event Raise( const Utils::SmartPtr< IEventSource > &src )
        {
            return Detail::Event( src );
        }

    };

    aloe__interface( IStringsDictionary )
    {
        aloe__iid__const( IStringsDictionary, 0x5 );
        
        aloe__prop( IStringsDictionary, String
                , map , type( String )
                , get , put , type( String )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    
    };
    
    aloe__interface( IStringEncoding )
    {
        aloe__iid__const( IStringEncoding, 0x6 );
    
        aloe__method( IStringEncoding, ReadString
                , type( String )
                , arg( encoded, In, type( CStr ))
                );
    
        aloe__method( IStringEncoding, WriteString
                , type( Long )
                , tuple2( 
                    arg( buffer, Out, type( NCStr )),
                    arg( text, In, type( String ))
                    )
                );
    };

    aloe__interface( IStringBuilder )
    {
        aloe__iid__const( IStringBuilder, 0x7 );
        
        aloe__prop( IStringBuilder, StringsDictionary
                , map , type( CStr )
                , get , put , pointer( IStringsDictionary )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IStringBuilder, StringEncoding
                , map , type( CStr )
                , get , put , pointer( IStringEncoding )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    
    };

    
    namespace Detail {

        struct CRefCount : virtual IRefCount, virtual IProvider
        {
            Types::Long   m_iCount;

            CRefCount() : m_iCount(1)
            {
#ifndef NDEBUG
                m_countImpl = this;
#endif
            }

            virtual ~CRefCount()
            {
            }
            
            Utils::SmartPtr<> __init__()
            {
                return Utils::SmartPtr<>( this, this );
            }

            Utils::SmartPtr<> __self__()
            {
                return Utils::SmartPtr<>( this, this ).AddRef();
            }
            
            void AddRef()
            {
                ++m_iCount;
            }

            Types::Bool RemRef()
            {
                if ( 0 == --m_iCount )
                {
                    delete this;
                    return true;
                }
                return false;
            }

            aloe__Query_impl( 0, (), 0, () );
            
        };
        
        template< class Interface, class Args > struct CMethodCall : IEvent, CRefCount
        {
            typedef Types::Bool (Interface::*Meth)( const Args & );
            Meth meth;
            Args args;

            CMethodCall( Meth m, const Args &a ) : meth( m ), args( a )
            {
            }

            Types::Bool Invoke( const Utils::SmartPtr< IProvider > &ptr )
            {
                Utils::SmartPtr< Interface > listener;
                if ( listener.QueryFrom( ptr ))
                {
                    return ((*listener).*meth)( args );
                }
                return true;
            }
        
            aloe__Query_impl( 1, ( IEvent ), 0, () );
            
        };
        
        template< class Interface, class Args, class B >
            Utils::SmartPtr< IEvent > make_method_call( Types::Bool (Interface::*meth)( const Args & ), const B &args )
            {
                CMethodCall< Interface, Args > *ptr = new CMethodCall< Interface, Args >( meth, args );
                return Utils::SmartPtr< IEvent >( ptr, ptr );
            }

        template< class Interface, class Args >
            Types::None Event::Proxy< Interface, Args >::Call( const Args &args )
            {
#ifdef ALOE_DEBUG_RUNTIMEINFO
                if ( const char *name = Detail::RuntimeInfo< Interface >::GetName( Utils::copyCast< void *>( meth )) )
                {
                    Types::String argString = Utils::Format( args );
                    char buffer[1024] = {0,};
                    _snprintf_s( buffer, 1024, _TRUNCATE, "Event: %s %S\n", name, argString.c_str() );
                    aloe__debugOut( buffer );
                }
#endif
                return get()->RaiseEvent( make_method_call( meth, args ));
            }

        //
        //
        // Automatic implementation of Query and QueryCounterAddRef
        //
        //
        
        template< const int N > struct NoType
        {
            inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                return false;
            }
            
            inline Types::Bool QueryRawPtr( Types::SizeType iRawId, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                return false;
            }
        };

        template< class IType > struct Interface : virtual IType
        {
            inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                if ( aloe__iid_of( IType ) == iid )
                {
                    reinterpret_cast< IType *&>( argPtr ) = this;
                    return true;
                }
                else {
                    return false;
                }
            }
        };

        template< const int N > struct Interface< NoType< N > >
        {
            inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                return false;
            }
        };
        
        template< class IType > struct Delegation
        {
            virtual Types::Bool QueryDelegate( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount ) = 0;
            virtual Types::Bool QueryDelegateRawPtr( Types::SizeType iRawId, Types::RawPointer &argPtr, IRefCount * &argCount ) = 0;
            
            inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                if ( aloe__iid_of( IType ) == iid )
                {
                    return QueryDelegate( iid, argPtr, argCount );
                }
                return false;
            }
                
            inline Types::Bool QueryRawPtr( Types::SizeType iRawId, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                return QueryDelegateRawPtr( iRawId, argPtr, argCount );
            }
        };

        
        template< class A1 = NoType< 1 >, class A2 = NoType< 2 >, class A3 = NoType< 3 >, class A4 = NoType< 4 >
            , class A5 = NoType< 5 >, class A6 = NoType< 6 >, class A7 = NoType< 7 >, class A8 = NoType< 8 >, class A9 = NoType< 9 > >
            struct Bases : A1, A2, A3, A4, A5, A6, A7, A8, A9
            {
                inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
                {
                    return  A1::Query( iid, argPtr, argCount ) ||
                            A2::Query( iid, argPtr, argCount ) ||
                            A3::Query( iid, argPtr, argCount ) ||
                            A4::Query( iid, argPtr, argCount ) ||
                            A5::Query( iid, argPtr, argCount ) ||
                            A6::Query( iid, argPtr, argCount ) ||
                            A7::Query( iid, argPtr, argCount ) ||
                            A8::Query( iid, argPtr, argCount ) ||
                            A9::Query( iid, argPtr, argCount );    
                }

                inline Types::Bool QueryRawPtr( Types::SizeType iRawId, Types::RawPointer &argPtr, IRefCount * &argCount )
                {
                    return  A1::QueryRawPtr( iRawId, argPtr, argCount ) ||
                            A2::QueryRawPtr( iRawId, argPtr, argCount ) ||
                            A3::QueryRawPtr( iRawId, argPtr, argCount ) ||
                            A4::QueryRawPtr( iRawId, argPtr, argCount ) ||
                            A5::QueryRawPtr( iRawId, argPtr, argCount ) ||
                            A6::QueryRawPtr( iRawId, argPtr, argCount ) ||
                            A7::QueryRawPtr( iRawId, argPtr, argCount ) ||
                            A8::QueryRawPtr( iRawId, argPtr, argCount ) ||
                            A9::QueryRawPtr( iRawId, argPtr, argCount );    
                }
            };
        
        template< class A1 = NoType< 1 >, class A2 = NoType< 2 >, class A3 = NoType< 3 >, class A4 = NoType< 4 >
            , class A5 = NoType< 5 >, class A6 = NoType< 6 >, class A7 = NoType< 7 >, class A8 = NoType< 8 >, class A9 = NoType< 9 > >
            struct Interfaces : Interface< IProvider >, Interface< A1 >, Interface< A2 >, Interface< A3 >, Interface< A4 >
				, Interface< A5 >, Interface< A6 >, Interface< A7 >, Interface< A8 >, Interface< A9 >
            {
                inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
                {
                    return  Interface< A1 >::Query( iid, argPtr, argCount ) ||
                            Interface< A2 >::Query( iid, argPtr, argCount ) ||
                            Interface< A3 >::Query( iid, argPtr, argCount ) ||
                            Interface< A4 >::Query( iid, argPtr, argCount ) ||
                            Interface< A5 >::Query( iid, argPtr, argCount ) ||
                            Interface< A6 >::Query( iid, argPtr, argCount ) ||
                            Interface< A7 >::Query( iid, argPtr, argCount ) ||
                            Interface< A8 >::Query( iid, argPtr, argCount ) ||
                            Interface< A9 >::Query( iid, argPtr, argCount ) ||
                            Interface< IProvider >::Query( iid, argPtr, argCount );
                }
            };

        template< class _Type, class _Interfaces, class _Bases, const unsigned int _RawID = 0 >
            struct Implementation : virtual _Interfaces, _Bases
            {
                typedef _Type Type;
                typedef _Interfaces Interfaces ;
                typedef _Bases Bases;
                typedef Implementation Super;
                
                typedef Utils::SmartPtr< Type > ThisPtr;

                enum { RAWPTR_ID = _RawID };
                
                ThisPtr __init__()
                {
#ifndef NDEBUG
                    m_impl = this;
#endif
                    return ThisPtr( reinterpret_cast< Type *>( this ), this );
                }
                
                ThisPtr __self__()
                {
                    return ThisPtr( reinterpret_cast< Type *>( this ), this ).AddRef();
                }
                
                Types::Bool QueryCounterAddRef( IRefCount * &pCount )
                {
                    pCount = add_ref( this );
                    return (0 != pCount);
                }

                inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
                {
                    argCount = NULL;
                    if ( Interfaces::Query( iid, argPtr, argCount ))
                    {
                        argCount = add_ref( this );
                        return true;
                    }
                    else
                    {
                        return Bases::Query( iid, argPtr, argCount );
                    }
                }
            
                inline Types::Bool QueryRawPtr( Types::SizeType iRawId, Types::RawPointer &argPtr, IRefCount * &argCount )
                {
                    argCount = NULL;
                    if ( iRawId == _RawID )
                    {
                        argPtr = this;
                        argCount = add_ref( this );
                        return true;
                    }
                    else
                    {
                        return Bases::QueryRawPtr( iRawId, argPtr, argCount );
                    }
                }
            };

    };//Detail

    namespace Utils {

        //
        // valueOf
        //
       
        inline Types::Point2i valueOf( const Types::Recti::corrner &proxy )
        {
            return proxy.value();
        }
        
        inline Types::Int valueOf( const Types::Recti::dimension &proxy )
        {
            return proxy.value();
        }
        
        inline Types::Vector2i valueOf( const Types::Recti::dimension2 &proxy )
        {
            return proxy.value();
        }
        
        inline Types::Vector2i valueOf( const Types::Sectori::ProxyFrom &proxy )
        {
            return proxy.value();
        }
        
        inline Types::Vector2i valueOf( const Types::Sectori::ProxyTo &proxy )
        {
            return proxy.value();
        }

        template< class Interface
            , class ValueType
            , class AppendRet, class AppendArg
            , class RemoveRet, class RemoveArg
            , class CallRet, class CallArg
            , class Getter, class Setter
            , class Appender, class Remover, class Caller > ValueType valueOf( const typename Detail::Property< Interface, ValueType
                    , AppendRet, AppendArg
                    , RemoveRet, RemoveArg
                    , CallRet, CallArg
                    , Getter, Setter
                    , Appender, Remover, Caller >::Proxy &proxy )
            {
                return proxy.value();
            }
        
        template< class Interface
            , class ValueType
            , class AppendRet, class AppendArg
            , class RemoveRet, class RemoveArg
            , class CallRet, class CallArg
            , class Index
            , class Getter, class Setter
            , class Appender, class Remover, class Caller > ValueType valueOf( const typename Detail::PropertyMap< Interface, ValueType
                    , AppendRet, AppendArg
                    , RemoveRet, RemoveArg
                    , CallRet, CallArg
                    , Index
                    , Getter, Setter
                    , Appender, Remover, Caller >::Proxy::Proxy2 &proxy )
            {
                return proxy.value();
            }

        inline Types::UInt8  valueOf( Types::UInt8  x ) { return x; }
        inline Types::UInt16 valueOf( Types::UInt16 x ) { return x; }
        inline Types::UInt32 valueOf( Types::UInt32 x ) { return x; }
        inline Types::UInt64 valueOf( Types::UInt64 x ) { return x; }
        
        inline Types::Int8  valueOf( Types::Int8  x ) { return x; }
        inline Types::Int16 valueOf( Types::Int16 x ) { return x; }
        inline Types::Int32 valueOf( Types::Int32 x ) { return x; }
        inline Types::Int64 valueOf( Types::Int64 x ) { return x; }
        
        inline Types::Float32 valueOf( Types::Float32 x ) { return x; }
        inline Types::Float64 valueOf( Types::Float64 x ) { return x; }
        
        template< class _T >       _T * valueOf( _T * x ) { return x; }
        template< class _T > const _T * valueOf( const _T * x ) { return x; }
        
        inline Types::Color32   valueOf( const Types::Color32 &x ) { return x; }
        inline Types::Point2i   valueOf( const Types::Point2i &x ) { return x; }
        inline Types::Vector2i  valueOf( const Types::Vector2i &x ) { return x; }
        inline Types::Recti     valueOf( const Types::Recti &x ) { return x; }
        inline Types::Sectori   valueOf( const Types::Sectori &x ) { return x; }
        inline Types::PixelType valueOf( const Types::PixelType &x ) { return x; }
        inline Types::PixelRectangle valueOf( const Types::PixelRectangle &x ) { return x; }

        //
        // bufferFrom{CStr|CWideStr|String}
        //

        inline Types::Tuple< Types::CUByteArray, Types::SizeType > bufferFromCStr( Types::CStr str )
        {
            return Types::Tuple< Types::CUByteArray, Types::SizeType >( (Types::CUByteArray)str, strlen( str ));
        }
        
        inline Types::Tuple< Types::CUByteArray, Types::SizeType > bufferFromCWideStr( Types::CWideStr str )
        {
            return Types::Tuple< Types::CUByteArray, Types::SizeType >( (Types::CUByteArray)str, wcslen( str ) * 2);
        }
        
        inline Types::Tuple< Types::CUByteArray, Types::SizeType > bufferFromString( const Types::String &str )
        {
            return Types::Tuple< Types::CUByteArray, Types::SizeType >( (Types::CUByteArray)str.c_str(), str.size() * 2 );
        }
        
        
    }; //Utils

}; //Aloe

#pragma warning(default:4250)

#endif//ALOE_INCLUDED_ALOE_H

