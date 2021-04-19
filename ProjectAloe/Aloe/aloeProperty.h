#ifndef ALOE_INCLUDED_ALOE_PROPERTY_H
#define ALOE_INCLUDED_ALOE_PROPERTY_H

#include "Aloe/aloeTypes.h"

namespace Aloe {

    namespace Detail {

        struct PropNoAction
        {
        };

        template< typename Interface, typename Type > struct PropGetter
        {
            typedef Type (Interface::*M)();
            M m;

            PropGetter( M im ) : m( im ) {}

            Type operator ()( Interface *obj )
            {
                return ((*obj).*m)();
            }
        };

        template< class Interface, class Type > struct PropSetter
        {
            typedef void (Interface::*M)( const Type & );
            M m;

            PropSetter( M im ) : m( im ) {}

            void operator ()( Interface *obj, const Type &x )
            {
                ((*obj).*m)( x );
            }
        };

        template< class Interface, class Ret, class Type > struct PropAppender
        {
            typedef Ret (Interface::*M)( const Type & );
            M m;

            PropAppender( M im ) : m( im ) {}

            Ret operator ()( Interface *obj, const Type &x )
            {
                return ((*obj).*m)( x );
            }
        };

        template< class Interface, class Ret, class Type > struct PropRemover
        {
            typedef Ret (Interface::*M)( const Type & );
            M m;

            PropRemover( M im ) : m( im ) {}

            Ret operator ()( Interface *obj, const Type &x )
            {
                return ((*obj).*m)( x );
            }
        };
        
        template< typename Interface, typename Ret, typename Arg > struct PropCaller
        {
            typedef Ret (Interface::*M)( const Arg & );
            M m;

            PropCaller( M im ) : m( im ) {}

            Ret operator ()( Interface *obj, const Arg &arg )
            {
                return ((*obj).*m)( arg );
            }
        };


        template< class Interface
            , class ValueType
            , class AppendRet, class AppendArg
            , class RemoveRet, class RemoveArg
            , class CallRet, class CallArg
            , class Getter, class Setter
            , class Appender, class Remover, class Caller > struct Property
            {
                Getter   g;
                Setter   s;
                Appender a;
                Remover  r;
                Caller   c;

                Property( const Getter &gt, const Setter &st,
                          const Appender &ap, const Remover &rm, const Caller &cl )
                    : g( gt )
                    , s( st )
                    , a( ap )
                    , r( rm )
                    , c( cl )
                    {}

                struct Proxy : Aloe::Utils::SmartPtr< Interface >
                {
                    mutable Property prop;

                    Proxy( Property *t, const Aloe::Utils::SmartPtr< Interface > &p )
                        : prop( *t )
                        , Aloe::Utils::SmartPtr< Interface >( p )    
                    {
                    }

                    void operator = ( const ValueType &x )
                    {
                        prop.s( get(), x );
                    }

                    operator ValueType () const
                    {
                        return value();
                    }

                    ValueType value() const
                    {
                        return prop.g( get() );
                    }

                    AppendRet operator += ( const AppendArg &x )
                    {
                        return prop.a( get(), x );
                    }

                    RemoveRet operator -= ( const RemoveArg &id )
                    {
                        return prop.r( get(), id );
                    }

                    CallRet operator () ( const CallArg &arg )
                    {
                        return prop.c( get(), arg );
                    }
                    
                    CallRet operator () ()
                    {
                        return prop.c( get(), Types::None() );
                    }

#define ALOE_PP_Property__Proxy__call( N ) \
                    template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) >  \
                        CallRet operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, ) ) \
                        { \
                            return prop.c( get(), \
                                    Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
                                    ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) )); \
                        }
                
                    ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, Property__Proxy__call );

                    template< class PropertyType >
                        typename Aloe::Detail::PropertyTraits< PropertyType >::PropertyType operator [] ( PropertyType property )
                        {
                            return Detail::make_property( value(), property );
                        }

                };

                Proxy In( const Aloe::Utils::SmartPtr< Interface > &p )
                {
                    return Proxy( this, p );
                }
            };

#define aloe__none Aloe::Types::None

#define aloe______ aloe__none
#define aloe__ aloe__none
        
#define aloe__util( F ) Aloe::Utils::F

#define aloe__type( T ) Aloe::Types::T

#define aloe__custom( X ) X

#define aloe__pointer( T ) Aloe::Utils::SmartPtr< Aloe::T >

#define aloe__array_of( T ) Aloe::Utils::ArrayOf< aloe__##T >

#define aloe__array_of_pointer( T ) Aloe::Utils::ArrayOf< Aloe::Utils::SmartPtr< Aloe::T > >

#define aloe__arg( Name, Kind, Type ) aloe__##Type

#define aloe__tuple0() Aloe::Types::Tuple<>
#define aloe__tuple1( A1 ) Aloe::Types::Tuple< aloe__##A1 >
#define aloe__tuple2( A1, A2 ) Aloe::Types::Tuple< aloe__##A1, aloe__##A2 >
#define aloe__tuple3( A1, A2, A3 ) Aloe::Types::Tuple< aloe__##A1, aloe__##A2, aloe__##A3 >
#define aloe__tuple4( A1, A2, A3, A4 ) Aloe::Types::Tuple< aloe__##A1, aloe__##A2, aloe__##A3, aloe__##A4 >
#define aloe__tuple5( A1, A2, A3, A4, A5 ) Aloe::Types::Tuple< aloe__##A1, aloe__##A2, aloe__##A3, aloe__##A4, aloe__##A5 >
#define aloe__tuple6( A1, A2, A3, A4, A5, A6 ) Aloe::Types::Tuple< aloe__##A1, aloe__##A2, aloe__##A3, aloe__##A4, aloe__##A5, aloe__##A6 >
#define aloe__tuple7( A1, A2, A3, A4, A5, A6, A7 ) Aloe::Types::Tuple< aloe__##A1, aloe__##A2, aloe__##A3, aloe__##A4, aloe__##A5, aloe__##A6, aloe__##A7 >
#define aloe__tuple8( A1, A2, A3, A4, A5, A6, A7, A8 ) Aloe::Types::Tuple< aloe__##A1, aloe__##A2, aloe__##A3, aloe__##A4, aloe__##A5, aloe__##A6, aloe__##A7, aloe__##A8 >
#define aloe__tuple9( A1, A2, A3, A4, A5, A6, A7, A8, A9 ) Aloe::Types::Tuple< aloe__##A1, aloe__##A2, aloe__##A3, aloe__##A4, aloe__##A5, aloe__##A6, aloe__##A7, aloe__##A8, aloe__##A9 >

#define aloe__1( t ) t.m_1
#define aloe__2( t ) t.m_2
#define aloe__3( t ) t.m_3
#define aloe__4( t ) t.m_4
#define aloe__5( t ) t.m_5
#define aloe__6( t ) t.m_6
#define aloe__7( t ) t.m_7
#define aloe__8( t ) t.m_8
#define aloe__9( t ) t.m_9

#define aloe__extract0( I, N, M, t )

#define aloe__extract1( I, N, M, t, a1 ) \
        const I::N##__##M##Type::T1 a1( aloe__1( t )); \

#define aloe__extract2( I, N, M, t, a1, a2 ) \
        aloe__extract1( I, N, M, t, a1 ); \
        const I::N##__##M##Type::T2 a2( aloe__2( t ));

#define aloe__extract3( I, N, M, t, a1, a2, a3 ) \
        aloe__extract2( I, N, M, t, a1, a2 ); \
        const I::N##__##M##Type::T3 a3( aloe__3( t ));

#define aloe__extract4( I, N, M, t, a1, a2, a3, a4 ) \
        aloe__extract3( I, N, M, t, a1, a2, a3 ); \
        const I::N##__##M##Type::T4 a4( aloe__4( t ));

#define aloe__extract5( I, N, M, t, a1, a2, a3, a4, a5 ) \
        aloe__extract4( I, N, M, t, a1, a2, a3, a4 ); \
        const I::N##__##M##Type::T5 a5( aloe__5( t ));

#define aloe__extract6( I, N, M, t, a1, a2, a3, a4, a5, a6 ) \
        aloe__extract5( I, N, M, t, a1, a2, a3, a4, a5 ); \
        const I::N##__##M##Type::T6 a6( aloe__6( t ));

#define aloe__extract7( I, N, M, t, a1, a2, a3, a4, a5, a6, a7 ) \
        aloe__extract6( I, N, M, t, a1, a2, a3, a4, a5, a6 ); \
        const I::N##__##M##Type::T7 a7( aloe__7( t ));

#define aloe__extract8( I, N, M, t, a1, a2, a3, a4, a5, a6, a7, a8 ) \
        aloe__extract7( I, N, M, t, a1, a2, a3, a4, a5, a6, a7 ); \
        const I::N##__##M##Type::T8 a8( aloe__8( t ));

#define aloe__extract9( I, N, M, t, a1, a2, a3, a4, a5, a6, a7, a8, a9 ) \
        aloe__extract8( I, N, M, t, a1, a2, a3, a4, a5, a6, a7, a8 ); \
        const I::N##__##M##Type::T9 a9( aloe__9( t ));


#define aloe__indexArg( I, N, n ) const I::N##__indexType & n
#define aloe__valueArg( I, N, n ) const I::N##__valueType & n
#define aloe__argsArg( I, N, n ) const I::N##__argsType & n
#define aloe__appendArg( I, N, n ) const I::N##__appendArgType & n
#define aloe__removeArg( I, N, n ) const I::N##__removeArgType & n
#define aloe__valueRet( I, N ) I::N##__valueType
#define aloe__appendRet( I, N ) I::N##__appendResultType
#define aloe__removeRet( I, N ) I::N##__removeResultType
#define aloe__resultRet( I, N ) I::N##__resultType

#define aloe__pointerArg( T, n ) const Aloe::Utils::SmartPtr< T > &n
#define aloe__pointerRet( T ) Aloe::Utils::SmartPtr< T >
        
#define aloe__declare_none( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg )
#define aloe__declare_____ aloe__declare_none
#define aloe__declare_ aloe__declare_none

#define aloe__declare_get( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        virtual T get_##N() = 0;

#define aloe__declare_put( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        virtual void put_##N( const T & ) = 0;

#define aloe__declare_append( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        virtual ApRet append_##N( const ApArg & ) = 0;

#define aloe__declare_remove( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        virtual RmRet remove_##N( const RmArg & ) = 0;

#define aloe__declare_call( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        virtual Re call_##N( const Arg & ) = 0;


#define aloe__class_none( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropNoAction

#define aloe__class_____ aloe__class_none
#define aloe__class_ aloe__class_none

#define aloe__class_get( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropGetter< I, T >

#define aloe__class_put( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropSetter< I, T >

#define aloe__class_append( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropAppender< I, ApRet, ApArg >

#define aloe__class_remove( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropRemover< I, RmRet, RmArg >

#define aloe__class_call( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropCaller< I, Re, Arg >


#define aloe__func_none( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropNoAction()

#define aloe__func_____ aloe__func_none
#define aloe__func_ aloe__func_none

#define aloe__func_get( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropGetter< I, T >( &I::get_##N )

#define aloe__func_put( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropSetter< I, T >( &I::put_##N )

#define aloe__func_append( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropAppender< I, ApRet, ApArg >( &I::append_##N )

#define aloe__func_remove( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropRemover< I, RmRet, RmArg >( &I::remove_##N )

#define aloe__func_call( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) \
        Aloe::Detail::PropCaller< I, Re, Arg >( &I::call_##N )


#define aloe__property__( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg, Gt, St, Ap, Rm, Cl ) \
        aloe__declare_##Gt( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
        aloe__declare_##St( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
        aloe__declare_##Ap( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
        aloe__declare_##Rm( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
        aloe__declare_##Cl( N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
        static Aloe::Detail::Property< I, T, ApRet, ApArg, RmRet, RmArg, Re, Arg,\
        aloe__class_##Gt( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ), \
        aloe__class_##St( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ), \
        aloe__class_##Ap( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ), \
        aloe__class_##Rm( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ), \
        aloe__class_##Cl( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) >::Proxy N( const Aloe::Utils::SmartPtr< I > &obj ) \
        { \
            aloe__class_##Gt( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) gt = aloe__func_##Gt( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
            aloe__class_##St( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) st = aloe__func_##St( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
            aloe__class_##Ap( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) ap = aloe__func_##Ap( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
            aloe__class_##Rm( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) rm = aloe__func_##Rm( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
            aloe__class_##Cl( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) cl = aloe__func_##Cl( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ); \
            Aloe::Detail::Property< I, T, ApRet, ApArg, RmRet, RmArg, Re, Arg,\
            aloe__class_##Gt( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ), \
            aloe__class_##St( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ), \
            aloe__class_##Ap( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ), \
            aloe__class_##Rm( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ), \
            aloe__class_##Cl( I, N, T, ApRet, ApArg, RmRet, RmArg, Re, Arg ) > p( gt, st, ap, rm, cl ); \
            return p.In( obj ); \
        }

    }; //Detail
}; //Aloe
#endif//ALOE_INCLUDED_ALOE_PROPERTY_H

