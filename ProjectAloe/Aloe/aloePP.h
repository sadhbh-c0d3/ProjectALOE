#ifndef ALOE_INCLUDED_ALOE_PP_H
#define ALOE_INCLUDED_ALOE_PP_H

#ifdef WIN32
#   define ALOE_PP_SPECIALIZATION template<>
#else
#   define ALOE_PP_SPECIALIZATION 
#endif

#define ALOE_PP_NONE()
#define ALOE_PP_COMMA() ,
#define ALOE_PP_SEMICOLON() ;

#define ALOE_PP_class( A, a, b ) class A b
#define ALOE_PP_typedef( A, a, b ) typedef A a
#define ALOE_PP_byConstReference( A, a, b ) const A & a
#define ALOE_PP_byReference( A, a, b ) A & a
#define ALOE_PP_byValue( A, a, b ) A a
#define ALOE_PP_getValue( A, a, b ) a
#define ALOE_PP_getClass( A, a, b ) A
#define ALOE_PP_initFrom( A, a, b ) A( a )

#define ALOE_PP_TEMPLATE_0( C, D, G, A, a, b )
#define ALOE_PP_TEMPLATE_1( C, D, G, A, a, b ) ALOE_PP_##C() ALOE_PP_##G( A##1, a##1, b )
#define ALOE_PP_TEMPLATE_2( C, D, G, A, a, b ) ALOE_PP_TEMPLATE_1( C, D, G, A, a, b ) ALOE_PP_##D() ALOE_PP_##G( A##2, a##2, b )
#define ALOE_PP_TEMPLATE_3( C, D, G, A, a, b ) ALOE_PP_TEMPLATE_2( C, D, G, A, a, b ) ALOE_PP_##D() ALOE_PP_##G( A##3, a##3, b )
#define ALOE_PP_TEMPLATE_4( C, D, G, A, a, b ) ALOE_PP_TEMPLATE_3( C, D, G, A, a, b ) ALOE_PP_##D() ALOE_PP_##G( A##4, a##4, b )
#define ALOE_PP_TEMPLATE_5( C, D, G, A, a, b ) ALOE_PP_TEMPLATE_4( C, D, G, A, a, b ) ALOE_PP_##D() ALOE_PP_##G( A##5, a##5, b )
#define ALOE_PP_TEMPLATE_6( C, D, G, A, a, b ) ALOE_PP_TEMPLATE_5( C, D, G, A, a, b ) ALOE_PP_##D() ALOE_PP_##G( A##6, a##6, b )
#define ALOE_PP_TEMPLATE_7( C, D, G, A, a, b ) ALOE_PP_TEMPLATE_6( C, D, G, A, a, b ) ALOE_PP_##D() ALOE_PP_##G( A##7, a##7, b )
#define ALOE_PP_TEMPLATE_8( C, D, G, A, a, b ) ALOE_PP_TEMPLATE_7( C, D, G, A, a, b ) ALOE_PP_##D() ALOE_PP_##G( A##8, a##8, b )
#define ALOE_PP_TEMPLATE_9( C, D, G, A, a, b ) ALOE_PP_TEMPLATE_8( C, D, G, A, a, b ) ALOE_PP_##D() ALOE_PP_##G( A##9, a##9, b )

#define ALOE_PP_TEMPLATE_R( n, C, D, G, A, a, b ) ALOE_PP_TEMPLATE_##n( C, D, G, A, a, b )

#define ALOE_PP_TEMPLATE_MAX ALOE_PP_TEMPLATE_9

#define ALOE_PP_GENERATE_0( C, D, G ) 
#define ALOE_PP_GENERATE_1( C, D, G ) ALOE_PP_##C() ALOE_PP_##G(1)
#define ALOE_PP_GENERATE_2( C, D, G ) ALOE_PP_GENERATE_1( C, D, G ) ALOE_PP_##D() ALOE_PP_##G(2)
#define ALOE_PP_GENERATE_3( C, D, G ) ALOE_PP_GENERATE_2( C, D, G ) ALOE_PP_##D() ALOE_PP_##G(3)
#define ALOE_PP_GENERATE_4( C, D, G ) ALOE_PP_GENERATE_3( C, D, G ) ALOE_PP_##D() ALOE_PP_##G(4)
#define ALOE_PP_GENERATE_5( C, D, G ) ALOE_PP_GENERATE_4( C, D, G ) ALOE_PP_##D() ALOE_PP_##G(5)
#define ALOE_PP_GENERATE_6( C, D, G ) ALOE_PP_GENERATE_5( C, D, G ) ALOE_PP_##D() ALOE_PP_##G(6)
#define ALOE_PP_GENERATE_7( C, D, G ) ALOE_PP_GENERATE_6( C, D, G ) ALOE_PP_##D() ALOE_PP_##G(7)
#define ALOE_PP_GENERATE_8( C, D, G ) ALOE_PP_GENERATE_7( C, D, G ) ALOE_PP_##D() ALOE_PP_##G(8)
#define ALOE_PP_GENERATE_9( C, D, G ) ALOE_PP_GENERATE_8( C, D, G ) ALOE_PP_##D() ALOE_PP_##G(9)

#define ALOE_PP_GENERATE_MAX ALOE_PP_GENERATE_9


#endif//ALOE_INCLUDED_ALOE_PP_H
