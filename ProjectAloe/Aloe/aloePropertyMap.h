#ifndef ALOE_INCLUDED_ALOE_PROPERTY_MAP_H
#define ALOE_INCLUDED_ALOE_PROPERTY_MAP_H

#include "Aloe/aloeProperty.h"

namespace Aloe {

    namespace Detail {

        template< typename Interface, typename Type, typename Index > struct PropMapGetter
        {
            typedef Type (Interface::*M)( const Index & );
            M m;

            PropMapGetter( M im ) : m( im ) {}

            Type operator ()( Interface *obj, const Index &i )
            {
                return ((*obj).*m)( i );
            }
        };

        template< class Interface, class Type, typename Index > struct PropMapSetter
        {
            typedef void (Interface::*M)( const Index &i, const Type & );
            M m;

            PropMapSetter( M im ) : m( im ) {}

            void operator ()( Interface *obj, const Index &i, const Type &x )
            {
                ((*obj).*m)( i, x );
            }
        };

        template< class Interface, class Ret, class Type, class Index > struct PropMapAppender
        {
            typedef Ret (Interface::*M)( const Index &, const Type & );
            M m;

            PropMapAppender( M im ) : m( im ) {}

            Ret operator ()( Interface *obj, const Index &i, const Type &x )
            {
                return ((*obj).*m)( i, x );
            }
        };

        template< class Interface, class Ret, class Type, class Index > struct PropMapRemover
        {
            typedef Ret (Interface::*M)( const Index &, const Type & );
            M m;

            PropMapRemover( M im ) : m( im ) {}

            Ret operator ()( Interface *obj, const Index &i, const Type &x )
            {
                return ((*obj).*m)( i, x );
            }
        };
        
        template< typename Interface, typename Ret, typename Arg, class Index > struct PropMapCaller
        {
            typedef Ret (Interface::*M)( const Index &, const Arg & );
            M m;

            PropMapCaller( M im ) : m( im ) {}

            Ret operator ()( Interface *obj, const Index &i, const Arg &arg )
            {
                return ((*obj).*m)( i, arg );
            }
        };


        template< class Interface
            , class ValueType
            , class AppendRet, class AppendArg
            , class RemoveRet, class RemoveArg
            , class CallRet, class CallArg
            , class Index
            , class Getter, class Setter
            , class Appender, class Remover, class Caller > struct PropertyMap
            {
                Getter   g;
                Setter   s;
                Appender a;
                Remover  r;
                Caller   c;

                PropertyMap( const Getter &gt, const Setter &st, const Appender &ap, const Remover &rm, const Caller &cl )
                    : g( gt )
                    , s( st )
                    , a( ap )
                    , r( rm )
                    , c( cl )
                    {}

                struct Proxy : Aloe::Utils::SmartPtr< Interface >
                {
                    mutable PropertyMap        prop;

                    Proxy( PropertyMap *t, const Aloe::Utils::SmartPtr< Interface > &p )
                        : prop( *t )
                        , Aloe::Utils::SmartPtr< Interface >( p )
                    {
                    }

                    struct Proxy2 : Aloe::Utils::SmartPtr< Interface >
                    {
                        mutable PropertyMap prop;
                        Index       index;
                        
                        Proxy2( const Proxy &p, const Index &i )
                            : prop( p.prop )
                            , Aloe::Utils::SmartPtr< Interface >( p )
                            , index( i )
                        {
                        }

                        void operator = ( const ValueType &x )
                        {
                            prop.s( get(), index, x );
                        }

                        operator ValueType () const
                        {
                            return prop.g( get(), index );
                        }

                        ValueType value() const
                        {
                            return prop.g( get(), index );
                        }

                        AppendRet operator += ( const AppendArg &x )
                        {
                            return prop.a( get(), index, x );
                        }

                        RemoveRet operator -= ( const RemoveArg &x )
                        {
                            return prop.r( get(), index, x );
                        }
                        
                        CallRet operator () ( const CallArg &arg )
                        {
                            return prop.c( get(), index, arg );
                        }
                    
                        CallRet operator () ()
                        {
                            return prop.c( get(), index, CallArg() );
                        }

#define ALOE_PP_PropertyMap__Proxy__call( N ) \
                        template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) >  \
                            CallRet operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, ) ) \
                            { \
                                return prop.c( get(), index, \
                                        Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
                                        ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) )); \
                            }
                    
                        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, PropertyMap__Proxy__call );
                        
                        template< class PropertyType >
                            typename Aloe::Detail::PropertyTraits< PropertyType >::PropertyType operator [] ( PropertyType property )
                            {
                                return Detail::make_property( value(), property );
                            }
                    };
                    
                    Proxy2 operator [] ( const Index &i )
                    {
                        return Proxy2( *this, i );
                    }
            
                    
#define ALOE_PP_PropertyMap__Proxy__Proxy2( N ) \
                    template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) > \
                        Proxy2 operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, )) \
                        { \
                            return Proxy2( *this, \
                                Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
                                ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) )); \
                        }
                    
                    ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, PropertyMap__Proxy__Proxy2 );

                };

                Proxy In( const Aloe::Utils::SmartPtr< Interface > &p )
                {
                    return Proxy( this, p );
                }
            };



#define aloe__declare_map_none( N, T, AR, AA, RR, RA, IndexType, Re, Arg )
#define aloe__declare_map_____ aloe__declare_map_none
#define aloe__declare_map_ aloe__declare_map_none
        
#define aloe__declare_map_get( N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        virtual T get_##N( const IndexType & ) = 0;

#define aloe__declare_map_put( N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        virtual void put_##N( const IndexType &, const T & ) = 0;

#define aloe__declare_map_append( N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        virtual AR append_##N( const IndexType &, const AA & ) = 0;

#define aloe__declare_map_remove( N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        virtual RR remove_##N( const IndexType &, const RA & ) = 0;

#define aloe__declare_map_call( N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        virtual Re call_##N( const IndexType &, const Arg & ) = 0;


#define aloe__class_map_none( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropNoAction
#define aloe__class_map_____ aloe__class_map_none
#define aloe__class_map_ aloe__class_map_none

#define aloe__class_map_get( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapGetter< I, T, IndexType >

#define aloe__class_map_put( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapSetter< I, T, IndexType >

#define aloe__class_map_append( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapAppender< I, AR, AA, IndexType >

#define aloe__class_map_remove( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapRemover< I, RR, RA, IndexType >

#define aloe__class_map_call( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapCaller< I, Re, Arg, IndexType >


#define aloe__func_map_none( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropNoAction()
#define aloe__func_map_____ aloe__func_map_none
#define aloe__func_map_ aloe__func_map_none

#define aloe__func_map_get( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapGetter< I, T, IndexType >( &I::get_##N )

#define aloe__func_map_put( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapSetter< I, T, IndexType >( &I::put_##N )

#define aloe__func_map_append( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapAppender< I, AR, AA, IndexType >( &I::append_##N )

#define aloe__func_map_remove( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapRemover< I, RR, RA, IndexType >( &I::remove_##N )

#define aloe__func_map_call( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) \
        Aloe::Detail::PropMapCaller< I, Re, Arg, IndexType >( &I::call_##N )


#define aloe__prop_map__( I, N, T, AR, AA, RR, RA, Re, Arg, IndexType, Gt, St, Ap, Rm, Cl ) \
        aloe__declare_map_##Gt( N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
        aloe__declare_map_##St( N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
        aloe__declare_map_##Ap( N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
        aloe__declare_map_##Rm( N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
        aloe__declare_map_##Cl( N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
        static Aloe::Detail::PropertyMap< I, T, AR, AA, RR, RA, Re, Arg, IndexType, \
            aloe__class_map_##Gt( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ), \
            aloe__class_map_##St( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ), \
            aloe__class_map_##Ap( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ), \
            aloe__class_map_##Rm( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ), \
            aloe__class_map_##Cl( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) >::Proxy N( const Aloe::Utils::SmartPtr< I > &obj ) \
        { \
            aloe__class_map_##Gt( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) gt = aloe__func_map_##Gt( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
            aloe__class_map_##St( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) st = aloe__func_map_##St( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
            aloe__class_map_##Ap( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) ap = aloe__func_map_##Ap( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
            aloe__class_map_##Rm( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) rm = aloe__func_map_##Rm( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
            aloe__class_map_##Cl( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) cl = aloe__func_map_##Cl( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ); \
            Aloe::Detail::PropertyMap< I, T, AR, AA, RR, RA, Re, Arg, IndexType,\
                aloe__class_map_##Gt( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ), \
                aloe__class_map_##St( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ), \
                aloe__class_map_##Ap( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ), \
                aloe__class_map_##Rm( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ), \
                aloe__class_map_##Cl( I, N, T, AR, AA, RR, RA, IndexType, Re, Arg ) > p( gt, st, ap, rm, cl ); \
            return p.In( obj ); \
        }

    }; //Detail
}; //Aloe
#endif//ALOE_INCLUDED_ALOE_PROPERTY_MAP_H
