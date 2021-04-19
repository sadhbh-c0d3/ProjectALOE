
#ifndef ALOE_INCLUDED_ALOE_TYPES_H
#define ALOE_INCLUDED_ALOE_TYPES_H

#include "Aloe/aloePP.h"
#include "Aloe/aloeError.h"

#include <sys/types.h>
#include <stddef.h>
#include <time.h>

namespace Aloe {
    
    // typy podstawowe
    namespace Types {

#ifdef WIN32
        // typy specyficzne
        typedef unsigned __int64 ULongLong;
        typedef unsigned __int64 UInt64;
        typedef unsigned __int32 UInt32;
        typedef unsigned __int16 UInt16;
        typedef unsigned __int8  UInt8;
        
        typedef __int64 Int64;
        typedef __int32 Int32;
        typedef __int16 Int16;
        typedef __int8  Int8;
#else
        // typy specyficzne
        typedef u_int64_t ULongLong;
        typedef u_int64_t UInt64;
        typedef u_int32_t UInt32;
        typedef u_int16_t UInt16;
        typedef u_int8_t  UInt8;
        
        typedef int64_t Int64;
        typedef int32_t Int32;
        typedef int16_t Int16;
        typedef int8_t  Int8;

#define _snprintf snprintf
#endif
        typedef float       Float32;
        typedef double      Float64;
        typedef long double BigFloat;
        
        typedef unsigned long  ULong;
        typedef unsigned int   UInt;
        typedef unsigned short UShort;
        typedef unsigned char  UByte;
        
        // typy ANSI
        typedef size_t    SizeType;
        typedef clock_t   ClockType;
        typedef time_t    TimeType;
        typedef ptrdiff_t PtrDiffType;
        
        // typy standardowe
        typedef Int64  LongLong;
        typedef double Float;
        typedef signed long   Long;
        typedef signed int    Int;
        typedef signed short  Short;
        typedef signed char   Byte;
        typedef bool   Bool;
        
        // typy znakowe
        typedef wchar_t WideChar;
        typedef char    Char;

        // typy buforów tylko do odczytu (C = Const)
        typedef const Char      *CStr;
        typedef const WideChar  *CWideStr;
        typedef const UByte     *CUByteArray;
        typedef const UInt      *CUIntArray;
        typedef const UShort    *CUShortArray;
        typedef const Int       *CIntArray;
        typedef const Short     *CShortArray;
        typedef const Float     *CFloatArray;
        typedef const Float32   *CFloat32Array;
        typedef const BigFloat  *CBigFloatArray;
        
        // typy buforów do odczytu i zapisu (NC = Non-Const)
        typedef Char            *NCStr;
        typedef WideChar        *NCWideStr;
        typedef UByte           *NCUByteArray;
        typedef UInt            *NCUIntArray;
        typedef UShort          *NCUShortArray;
        typedef Int             *NCIntArray;
        typedef Short           *NCShortArray;
        typedef Float           *NCFloatArray;
        typedef Float32         *NCFloat32Array;
        typedef BigFloat        *NCBigFloatArray;

        // wskaŸnik bez typu
        typedef void        *RawPointer;
        typedef void        *NCRawPointer;
        // j.w. tylko do odczytu
        typedef const void  *CRawPointer;
        

        struct None
        {
            template< class T > Bool operator == ( const T & ) { return false; }
            Bool operator == ( const None & ) { return true; }

            operator Bool () const { return false; }
            operator Long () const { return 0L; }
            operator ULong () const { return 0UL; }
            operator Int () const { return 0; }
            operator UInt () const { return 0U; }
            operator Int8 () const { return 0; }
            operator UInt8 () const { return 0U; }
            operator Int16 () const { return 0; }
            operator UInt16 () const { return 0U; }
            operator Int64 () const { return 0LL; }
            operator UInt64 () const { return 0ULL; }
            operator Float () const { return 0; }
            operator CStr () const { return ""; }
            operator CWideStr () const { return L""; }
        };
        
        union LongPointer
        {
            LongPointer() { p = 0; l = 0; }
            LongPointer( Long il ) { p = 0; l = il; }
            LongPointer( RawPointer ip ) { l = 0; p = ip; }
            RawPointer p;
            Long l;
            Bool operator == ( const LongPointer &o ) const { return (p == o.p); }
            Bool operator < ( const LongPointer &o ) const { return (p < o.p); }
            RawPointer & getPointer() { return p; }
            Long       & getLong   () { return l; }
            const RawPointer & getPointer() const { return p; }
            const Long       & getLong   () const { return l; }
        };
    };//Types

    // funkcje uzytkowe
    namespace Utils {
        
        template< class T > Types::None varSwap( T &x, T &y )
        {
            T a( x );
            x = y;
            y = a;
            return Types::None();
        }

        template< class T, class C > const T & varMin( const T &x, const C &y )
        {
            return ( x < y ? x : y );
        }
        
        template< class T, class C > const T & varMax( const T &x, const C &y )
        {
            return ( y < x ? x : y );
        }
        
        template< class _T1, class _T2 > _T1 copyCast( const _T2 &x )
        {
            char b[ sizeof( _T1 ) > sizeof( _T2 ) ? sizeof( _T1 ) : sizeof( _T2 ) ] = {0, };
            (*reinterpret_cast< _T2 *>( b )) = x;
            return (*reinterpret_cast< _T1 *>( b ));
        }

        template< class _T > _T makePositiveCoord( _T coord, _T start, _T end )
        {
            if ( coord < 0 )
                return end + coord + 1;
            else
                return start + coord;
        }
        
        template< class _T > _T makeNegativeCoord( _T coord, _T start, _T end )
        {
            if ( coord < 0 )
                return end + coord + 1;
            else
                return start + coord;
        }
    };//Utils

    // typy wyzsze
    namespace Types {

        struct Color32;
        struct Point2i;
        struct Vector2i;
        struct Recti;

        struct Color32
        {
	    UByte red;
	    UByte green;
	    UByte blue;
	    UByte alpha;

            ULong & longWord()
	    {
		return (*reinterpret_cast< ULong *>( this ));
	    }
	    
            const ULong & longWord() const
	    {
		return (*reinterpret_cast< const ULong *>( this ));
	    }

            Color32( ULong lw )
            {
		longWord() = lw;
	    }

            Color32( UByte r = 0, UByte g = 0, UByte b = 0, UByte a = 255 ) : red(r), green(g), blue(b), alpha(a)
            {}
            
            Color32( Int r, Int g, Int b, Int a ) : red(r), green(g), blue(b), alpha(a)
            {}
            
            Color32( Float r, Float g, Float b, Float a )
                : red  ( static_cast< UByte >( r*255.0 ))
                , green( static_cast< UByte >( g*255.0 ))
                , blue ( static_cast< UByte >( b*255.0 ))
                , alpha( static_cast< UByte >( a*255.0 ))
            {}
            
            UByte Redub() const { return red; }
            UByte Greenub() const { return green; }
            UByte Blueub() const { return blue; }
            UByte Alphaub()const  { return alpha; }

            Int Redi()   const { return static_cast< Int >( red ); }
            Int Greeni() const { return static_cast< Int >( green ); }
            Int Bluei()  const { return static_cast< Int >( blue ); }
            Int Alphai() const { return static_cast< Int >( alpha ); }
            
            Float Redf()   const { return static_cast< Float >( red )/255.0; }
            Float Greenf() const { return static_cast< Float >( green )/255.0; }
            Float Bluef()  const { return static_cast< Float >( blue )/255.0; }
            Float Alphaf() const { return static_cast< Float >( alpha )/255.0; }
            
            Bool operator == ( const Color32 &c ) const
            {
                return (c.longWord() == longWord());
            }
            
            Bool operator != ( const Color32 &c ) const
            {
                return !((*this) == c);
            }
            
            Bool operator ! () const
            {
                return (0 == alpha);
            }
        };

        struct Point2i
        {
            Int x;
            Int y;

            Point2i( Int ix = 0, Int iy = 0 ): x( ix ), y( iy ) {}
            explicit Point2i( const Vector2i &v );

            Point2i & operator += ( const Vector2i &v );
            Point2i & operator -= ( const Vector2i &v );

            Bool operator == ( const Point2i &pt ) const
            {
                return (pt.x==x && pt.y==y);
            }
            
            Bool operator != ( const Point2i &pt ) const
            {
                return !((*this) == pt);
            }
        };

        struct Vector2i
        {
            Int dx;
            Int dy;

            Vector2i( Int idx = 0, Int idy = 0 ): dx( idx ), dy( idy ) {}
            explicit Vector2i( const Point2i &p );

            Vector2i & operator += ( const Vector2i &v );
            Vector2i & operator -= ( const Vector2i &v );
            Vector2i & operator *= ( Float c );
            Vector2i & operator /= ( Float c );
            Vector2i operator - () { return Vector2i( -dx, -dy ); }

            Bool operator == ( const Vector2i &vt ) const
            {
                return (vt.dx==dx && vt.dy==dy);
            }
            
            Bool operator != ( const Vector2i &vt ) const
            {
                return !((*this) == vt);
            }

            Bool operator ! () const
            {
                return (!dx && !dy);
            }
        };

        struct Recti
        {
            Int x1;
            Int y1;
            Int x2;
            Int y2;

            Recti(): x1(0), y1(0), x2(0), y2(0) {}
            Recti( const Point2i &ul, const Point2i &br )
                : x1( ul.x )
                , y1( ul.y )
                , x2( br.x )
                , y2( br.y )
                {}
            Recti( const Point2i &ul, const Vector2i &s )
                : x1( ul.x )
                , y1( ul.y )
                , x2( ul.x + s.dx )
                , y2( ul.y + s.dy )
                {}
            Recti & fixCoords()
            {
                if ( x1 > x2 ) { Aloe::Utils::varSwap( x1, x2 ); }
                if ( y1 > y2 ) { Aloe::Utils::varSwap( y1, y2 ); }
                return (*this);
            }
            
            Bool operator == ( const Recti &r ) const
            {
                return (r.x1==x1 && r.y1==y1 && r.x2==x2 && r.y2==y2);
            }
            
            Bool operator != ( const Recti &r ) const
            {
                return !((*this) == r);
            }

            Bool operator ! () const
            {
                return (0 == width() || 0 == height());
            }

            Recti & operator += ( const Vector2i v ) { x1 += v.dx; x2 += v.dx; y1 += v.dy; y2 += v.dy; return (*this); }
            Recti & operator -= ( const Vector2i v ) { x1 -= v.dx; x2 -= v.dx; y1 -= v.dy; y2 -= v.dy; return (*this); }

            struct corrner
            {
                Int &x;
                Int &y;

                corrner( Int &rx, Int &ry ): x( rx ), y( ry ) {}

                operator Point2i () const { return Point2i( x, y ); }
                corrner & operator = ( const Point2i &p ) { x = p.x; y = p.y; return (*this); }
                corrner & operator += ( const Vector2i &v ) { x += v.dx; y += v.dy; return (*this); }
                corrner & operator -= ( const Vector2i &v ) { x -= v.dx; y -= v.dy; return (*this); }

                Point2i value() const { return Point2i( x, y ); }

            };

            corrner upperLeft  () { return corrner( x1, y1 ); }
            corrner upperRight () { return corrner( x2, y1 ); }
            corrner bottomLeft () { return corrner( x1, y2 ); }
            corrner bottomRight() { return corrner( x2, y2 ); }

            Point2i upperLeft  () const { return Point2i( x1, y1 ); }
            Point2i upperRight () const { return Point2i( x2, y1 ); }
            Point2i bottomLeft () const { return Point2i( x1, y2 ); }
            Point2i bottomRight() const { return Point2i( x2, y2 ); }

            Int width () const { return x2 - x1; }
            Int height() const { return y2 - y1; }

            struct dimension
            {
                Int &x1;
                Int &x2;

                dimension( Int &rx1, Int rx2 ) : x1(rx1), x2(rx2) {}
                
                operator Int () { return x2 - x1; }
                dimension & operator = ( Int d ) { x2 = x1 + d; return *this; }
                dimension & operator += ( Int d ) { x2 += d; return *this; }
                dimension & operator -= ( Int d ) { x2 -= d; return *this; }

                Int value() const { return x2 - x1; }
            };

            dimension width() { return dimension( x1, x2 ); }
            dimension height() { return dimension( y1, y2 ); }

            Vector2i size() const { return Vector2i( width(), height() ); }

            struct dimension2
            {
                Recti &rect;

                dimension2( Recti &rr ) : rect( rr ) {}

                operator Vector2i () { return Vector2i( rect.width(), rect.height() ); }
                dimension2 & operator = ( const Vector2i &s ) { rect.x2 = rect.x1 + s.dx; rect.y2 = rect.y1 + s.dy; return *this; }
                dimension2 & operator += ( const Vector2i &s ) { rect.x2 += s.dx; rect.y2 += s.dy; return *this; }
                dimension2 & operator -= ( const Vector2i &s ) { rect.x2 -= s.dx; rect.y2 -= s.dy; return *this; }

                Vector2i value() const { return Vector2i( rect.width(), rect.height() ); }
            };

            dimension2 size() { return dimension2( *this ); }

            bool empty() const
            {
                return (0 == width() || 0 == height());
            }

            bool intersectWith( const Recti &o )
            {
                if ( o.empty() )
                    return false;

                if ( x1 >= o.x2 || o.x1 >= x2 )
                    return false;

                if ( y1 >= o.y2 || o.y1 >= y2 )
                    return false;

                if ( o.x1 > x1 )
                    x1 = o.x1;
                
                if ( o.x2 < x2 )
                    x2 = o.x2;
                
                if ( o.y1 > y1 )
                    y1 = o.y1;
                
                if ( o.y2 < y2 )
                    y2 = o.y2;

                return true;
            }

            bool isPointInside( const Point2i &pt )
            {
                if ( pt.x < x1 )
                    return false;
                
                if ( pt.y < y1 )
                    return false;

                if ( pt.x < x2 && pt.y < y2 )
                    return true;

                return false;
            }

            Recti & growToFit( const Recti &r )
            {
                if ( r.x1 < x1 )
                    x1 = r.x1;

                if ( r.y1 < y1 )
                    y1 = r.y1;

                if ( r.x2 > x2 )
                    x2 = r.x2;
                
                if ( r.y2 > y2 )
                    y2 = r.y2;

                return (*this);
            }
            
            Recti & growToFit( const Point2i &pt )
            {
                if ( pt.x < x1 )
                    x1 = pt.x;

                if ( pt.y < y1 )
                    y1 = pt.y;
                
                if ( pt.x > x2 )
                    x2 = pt.x;

                if ( pt.y > y2 )
                    y2 = pt.y;

                return (*this);
            }
        };

        inline Point2i::Point2i( const Vector2i &v )
        {
            x = v.dx;
            y = v.dy;
        }

        inline Vector2i::Vector2i( const Point2i &p )
        {
            dx = p.x;
            dy = p.y;
        }

        inline Point2i & Point2i::operator += ( const Vector2i &v )
        {
            x += v.dx;
            y += v.dy;
            return (*this);
        }


        inline Point2i & Point2i::operator -= ( const Vector2i &v )
        {
            x -= v.dx;
            y -= v.dy;
            return (*this);
        }


        inline Vector2i & Vector2i::operator += ( const Vector2i &v )
        {
            dx += v.dx;
            dy += v.dy;
            return (*this);
        }


        inline Vector2i & Vector2i::operator -= ( const Vector2i &v )
        {
            dx -= v.dx;
            dy -= v.dy;
            return (*this);
        }


        inline Vector2i & Vector2i::operator *= ( Float c )
        {
            dx = (Int)((Float)dx * c);
            dy = (Int)((Float)dy * c);
            return (*this);
        }


        inline Vector2i & Vector2i::operator /= ( Float c )
        {
            dx = (Int)((Float)dx / c);
            dy = (Int)((Float)dy / c);
            return (*this);
        }

        inline Vector2i operator - ( const Point2i &p1, const Point2i &p2 )
        {
            return Vector2i( p1.x - p2.x, p1.y - p2.y );
        }

        inline Point2i operator + ( Point2i p, const Vector2i &v ) { return (p += v); }
        inline Point2i operator - ( Point2i p, const Vector2i &v ) { return (p -= v); }

        inline Vector2i operator + ( Vector2i v1, const Vector2i &v2 ) { return (v1 += v2); }
        inline Vector2i operator - ( Vector2i v1, const Vector2i &v2 ) { return (v1 -= v2); }
        inline Vector2i operator * ( Vector2i v, Float c ) { return (v *= c); }
        inline Vector2i operator / ( Vector2i v, Float c ) { return (v /= c); }

        inline Recti operator + ( Recti r, const Vector2i &v ) { return ( r += v ); }
        inline Recti operator - ( Recti r, const Vector2i &v ) { return ( r -= v ); }

        struct Sectori
        {
            Point2i start;
            Point2i end;
            
            Sectori() {}
            Sectori( Point2i s, Point2i e ) : start( s ), end( e ) {}
            Sectori( Point2i s, Vector2i v ) : start( s ), end( s + v ) {}
            Sectori( Vector2i v, Point2i e ) : start( e - v ), end( e ) {}

            struct ProxyFrom
            {
                Sectori &sector;
                ProxyFrom( Sectori &s ) : sector( s ) {}

                ProxyFrom & operator = ( const Vector2i &v )
                {
                    sector.end = sector.start + v;
                    return (*this);
                }
            
                operator Vector2i() const { return value(); }
                Vector2i value() const { return (sector.end - sector.start); }
            };

            struct ProxyTo
            {
                Sectori &sector;
                ProxyTo( Sectori &s ) : sector( s ) {}

                ProxyTo & operator = ( const Vector2i &v )
                {
                    sector.start = sector.end - v;
                    return (*this);
                }
            
                operator Vector2i() const { return value(); }
                Vector2i value() const { return (sector.start - sector.end); }
            };

            ProxyFrom from() { return *this; }
            ProxyFrom to() { return *this; }
            
            Vector2i from() const { return (end - start); }
            Vector2i to() const { return (start - end); }
        };

        struct PixelType
        {
            enum PixelTypes
            {
                F_BITS          = 0x00FF,
                F_FLAG          = 0x0100,
                F_SWAP          = F_FLAG,
                F_ALPHA         = F_FLAG << 1,
                F_LUMI          = F_FLAG << 2,
                F_RED           = F_FLAG << 3,
                F_GREEN         = F_FLAG << 4,
                F_BLUE          = F_FLAG << 5,
                F_PREMUL        = F_FLAG << 6,

                LUMI_8          = 0x08 | F_LUMI,
                ALPHA_8         = 0x08 | F_ALPHA,
                RGB_5_5_5       = 0x0F,
                RGBA_5_5_5_1    = 0x0F | F_ALPHA,
                RGB_5_6_5       = 0x10,
                RGBA_4_4_4_4    = 0x10 | F_ALPHA,
                LUMI_ALPHA_8_8  = 0x10 | F_LUMI | F_ALPHA,
                RGB_8_8_8       = 0x18,
                RGB_8_8_8_8     = 0x20,
                RGBA_8_8_8_8    = 0x20 | F_ALPHA,

                RGB             = RGB_8_8_8,
                RGB16           = RGB_5_6_5,
                RGB24           = RGB_8_8_8,
                RGBA            = RGBA_8_8_8_8,
                RGBA32          = RGBA_8_8_8_8,
                BGR             = RGB | F_SWAP,
                BGRA            = RGBA | F_SWAP
            };

            Int          m_pixelType;
            
#define aloe__pixeltype3( BPP, SWAP, ALPHA ) (BPP | (SWAP << 8) | (ALPHA << 9))

            Bool isSwap()  const { return 0 != (m_pixelType & F_SWAP); }
            Bool isAlpha() const { return 0 != (m_pixelType & F_ALPHA); }
            Bool isLumi()  const { return 0 != (m_pixelType & F_LUMI); }
            Bool isRed()   const { return 0 != (m_pixelType & F_RED); }
            Bool isGreen() const { return 0 != (m_pixelType & F_GREEN); }
            Bool isBlue()  const { return 0 != (m_pixelType & F_BLUE); }
            Bool isPreMul()const { return 0 != (m_pixelType & F_PREMUL); }
            Int  bitsPerPixel() const { return (m_pixelType & F_BITS); }

            PixelType() : m_pixelType(0)
            {
            }
            
            PixelType( Long pixelType ) : m_pixelType( pixelType )
            {
            }
            
            PixelType operator | ( PixelType y ) const
            {
                return PixelType( m_pixelType | y.m_pixelType );
            }

            operator Long () const
            {
                return m_pixelType;
            }
        };
       
        struct PixelRectangle : PixelType
        {
            Int          m_bytesPerRow;
            Int          m_bytesPerPixel;
            Recti        m_rect;
            NCUByteArray m_pixels;
        };


        struct Identifier
        {
            LongPointer lpIdent;            
            Identifier() {}
            Identifier( LongPointer ident ) : lpIdent( ident ) {}
            Bool operator == ( const Identifier &o ) const { return (lpIdent == o.lpIdent); }
            Bool operator < ( const Identifier &o ) const { return (lpIdent < o.lpIdent); }
        };

        template< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, class, A,, = None ) > struct Tuple
        {
            ALOE_PP_TEMPLATE_MAX( NONE, SEMICOLON, typedef, A, T, );
            ALOE_PP_TEMPLATE_MAX( NONE, SEMICOLON, byValue, A, m_, );

#define ALOE_PP_Types__Tuple__ctor( N ) \
            Tuple( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, ) ) \
                : ALOE_PP_TEMPLATE_R( N, NONE, COMMA, initFrom, m_, a, ) \
            {}

            ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, Types__Tuple__ctor );

            Tuple() {}
           
            template< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, class, B,, ) >
                Tuple( const Tuple< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, getClass, B,, ) > &t )
                : ALOE_PP_TEMPLATE_MAX( NONE, COMMA, initFrom, m_, t.m_, )
                {}
        };

    };//Types

    struct IProvider;

    namespace Detail {
        struct CRefCount;
    }
    
    struct IRefCount
    {
        virtual void AddRef() = 0;
        virtual Types::Bool RemRef() = 0;

#ifndef NDEBUG
        Detail::CRefCount *m_countImpl;
#endif
    };
    
    namespace Utils {
        
        typedef void (*PfnPixelSet)( Types::NCUByteArray, const Types::Color32 & );
       
        // BGR (Alpha is ignored)
        inline void pixelSet24( Types::NCUByteArray dst, const Types::Color32 &color )
        {
            dst[0] = color.Blueub();
            dst[1] = color.Greenub();
            dst[2] = color.Redub();
        }
        
        // BGRA
        inline void pixelSet32( Types::NCUByteArray dst, const Types::Color32 &color )
        {
            dst[0] = color.Blueub();
            dst[1] = color.Greenub();
            dst[2] = color.Redub();
            dst[3] = color.Alphaub();
        }
        
        // RGB (Alpha is ignored)
        inline void pixelSet24Swapped( Types::NCUByteArray dst, const Types::Color32 &color )
        {
            dst[0] = color.Redub();
            dst[1] = color.Greenub();
            dst[2] = color.Blueub();
        }
        
        // RGBA
        inline void pixelSet32Swapped( Types::NCUByteArray dst, const Types::Color32 &color )
        {
            dst[0] = color.Redub();
            dst[1] = color.Greenub();
            dst[2] = color.Blueub();
            dst[3] = color.Alphaub();
        }

        inline PfnPixelSet pixelSetFun( Types::Int pixelType )
        {
            if (( pixelType & Types::PixelType::F_BITS ) == 24 )
            {
                if ( pixelType & Types::PixelType::F_SWAP )
                {
                    return pixelSet24Swapped;
                }
                else {
                    return pixelSet24;
                }
            }
            else if ((pixelType & Types::PixelType::F_BITS ) == 32 )
            {
                if ( pixelType & Types::PixelType::F_SWAP )
                {
                    return pixelSet32Swapped;
                }
                else {
                    return pixelSet32;
                }
            }
            return NULL;
        }
        
        typedef void (*PfnPixelGet)( Types::NCUByteArray, Types::Color32 & );
        
        // BGR (Alpha <- 255)
        inline void pixelGet24( Types::NCUByteArray dst, Types::Color32 &color )
        {
            color.blue  = dst[0];
            color.green = dst[1];
            color.red   = dst[2];
            color.alpha = 255;
        }
        
        // BGRA
        inline void pixelGet32( Types::NCUByteArray dst, Types::Color32 &color )
        {
            color.blue  = dst[0];
            color.green = dst[1];
            color.red   = dst[2];
            color.alpha = dst[3];
        }
        
        // RGB (Alpha <- 255)
        inline void pixelGet24Swapped( Types::NCUByteArray dst, Types::Color32 &color )
        {
            color.red   = dst[0];
            color.green = dst[1];
            color.blue  = dst[2];
            color.alpha = 255;
        }
        
        // RGBA
        inline void pixelGet32Swapped( Types::NCUByteArray dst, Types::Color32 &color )
        {
            color.red   = dst[0];
            color.green = dst[1];
            color.blue  = dst[2];
            color.alpha = dst[3];
        }

        inline PfnPixelGet pixelGetFun( Types::Int pixelType )
        {
            if (( pixelType & Types::PixelType::F_BITS ) == 24 )
            {
                if ( pixelType & Types::PixelType::F_SWAP  )
                {
                    return pixelGet24Swapped;
                }
                else {
                    return pixelGet24;
                }
            }
            else if ((pixelType & Types::PixelType::F_BITS ) == 32 )
            {
                if ( pixelType & Types::PixelType::F_SWAP )
                {
                    return pixelGet32Swapped;
                }
                else {
                    return pixelGet32;
                }
            }
            return NULL;
        }
        
        // RGB -> RGB or BGR -> BGR
        inline void copyPixel24( Types::NCUByteArray dst, Types::NCUByteArray src )
        {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
        }
        
        // RGBA -> RGBA or BGRA -> BGRA
        inline void copyPixel32( Types::NCUByteArray dst, Types::NCUByteArray src )
        {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
        }
        
        // RGB -> BGR or BGR -> RGB
        inline void swapPixel24( Types::NCUByteArray dst, Types::NCUByteArray src )
        {
            dst[0] = src[2];
            dst[1] = src[1];
            dst[2] = src[0];
        }
        
        // RGBA -> BGRA or BGRA -> RGBA
        inline void swapPixel32( Types::NCUByteArray dst, Types::NCUByteArray src )
        {
            dst[0] = src[2];
            dst[1] = src[1];
            dst[2] = src[0];
            dst[3] = src[3];
        }

        struct copyPixelGetSet
        {
            PfnPixelGet m_get;
            PfnPixelSet m_set;
	    Types::Color32 m_color;

            copyPixelGetSet( PfnPixelGet rget, PfnPixelSet rset ) : m_get( rget ), m_set( rset ) {}
        
            void operator () ( Types::NCUByteArray dst, Types::NCUByteArray src )
            {
                m_get( src, m_color );
                m_set( dst, m_color );
            }
        };

        template< class _F > struct copyPixelPremulFun
        {
            _F f; copyPixelPremulFun( _F rf ) : f(rf) {}

            Types::UByte PremulChannel( Types::UInt value, Types::UInt alpha )
            {
                value *= alpha;
                value /= 255;
                return value;
            }
            
            void operator () ( Types::NCUByteArray dst, Types::NCUByteArray src )
            {
                f( dst, src );
                dst[0] = PremulChannel( dst[0], dst[3] );
                dst[1] = PremulChannel( dst[1], dst[3] );
                dst[2] = PremulChannel( dst[2], dst[3] );
            }
        };

        template< class _F > copyPixelPremulFun< _F > copyPixelPremul( _F f )
        {
            return copyPixelPremulFun< _F >( f );
        }

        template< class _BlendFunc >
            inline Types::Bool copyPixelsFunc( const Types::PixelRectangle &dst, const Types::PixelRectangle &src, _BlendFunc blendFunc )
            {
                Types::NCUByteArray dstLine = dst.m_pixels;
                Types::NCUByteArray srcLine = src.m_pixels;
                Types::Int width = varMin( dst.m_rect.width(), src.m_rect.width() );
                Types::Int height = varMin( dst.m_rect.height(), src.m_rect.height() );
                for ( int line = 0; line < height; ++line )
                {
                    Types::NCUByteArray dstPixel = dstLine;
                    Types::NCUByteArray srcPixel = srcLine;

                    for ( int pixel = 0; pixel < width; ++pixel )
                    {
                        blendFunc( dstPixel, srcPixel );
                        dstPixel += dst.m_bytesPerPixel;
                        srcPixel += src.m_bytesPerPixel;
                    }

                    dstLine += dst.m_bytesPerRow;
                    srcLine += src.m_bytesPerRow;
                }
                return true;
            }
            
        inline Types::Bool copyPixels( const Types::PixelRectangle &dst, const Types::PixelRectangle &src )
        {
            if ((src.bitsPerPixel() == 24) && (dst.bitsPerPixel() == 24))
            {
                if ( src.isSwap() == dst.isSwap() )
                {
                    return copyPixelsFunc( dst, src, copyPixel24 );
                }
                else {
                    return copyPixelsFunc( dst, src, swapPixel24 );
                }
            }
            else if ((src.bitsPerPixel() == 32) && (dst.bitsPerPixel() == 32))
            {
                if ( src.isSwap() == dst.isSwap() )
                {
                    return copyPixelsFunc( dst, src, copyPixel32 );
                }
                else {
                    return copyPixelsFunc( dst, src, swapPixel32 );
                }
            }
            else if ((src.bitsPerPixel() == 24) && (dst.bitsPerPixel() == 32))
            {
                if ( dst.isPreMul() == src.isPreMul( ) )
                {
                    if ( src.isSwap() == dst.isSwap() )
                    {
                        return copyPixelsFunc( dst, src, copyPixel24 );
                    }
                    else {
                        return copyPixelsFunc( dst, src, swapPixel24 );
                    }
                }
                else
                {
                    if ( src.isSwap() == dst.isSwap() )
                    {
                        return copyPixelsFunc( dst, src, copyPixelPremul( copyPixel24 ));
                    }
                    else {
                        return copyPixelsFunc( dst, src, copyPixelPremul( swapPixel24 ));
                    }
                }
            }
            else if ((src.bitsPerPixel() == 32) && (dst.bitsPerPixel() == 24))
            {
                if ( src.isSwap() == dst.isSwap() )
                {
                    return copyPixelsFunc( dst, src, copyPixel24 );
                }
                else {
                    return copyPixelsFunc( dst, src, swapPixel24 );
                }
            }
            
            PfnPixelGet pfGet = pixelGetFun( src.m_pixelType );
            PfnPixelSet pfSet = pixelSetFun( dst.m_pixelType );
            if ( pfGet && pfSet )
            {
                return copyPixelsFunc( dst, src, copyPixelGetSet( pfGet, pfSet ));
            }
            return false;
        }

        struct StrongPointerPolicy;

        template< class Interface = IProvider, class Policy = StrongPointerPolicy > struct SmartPtr;

#define ALOE_PP_makeTuple__definition( N ) \
        template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) > \
            Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
            makeTuple( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, ) ) \
            { \
                return Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
                    ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) ); \
            }
    
        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, makeTuple__definition );
            
    };
    
    namespace Detail {
        
        template< class Interface, class R, class Meth > struct MethodCaller;

        template< class Ptr, class Interface, class ReferenceType >
            ReferenceType
            make_property( const Ptr &, ReferenceType property( const Utils::SmartPtr< Interface > & ));

#define ALOE_PP_make_property__declaration( N ) \
        template< class Ptr, class Interface, class R ALOE_PP_TEMPLATE_R( N, COMMA, COMMA, class, A,, ) > \
            MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) > \
            make_property( const Ptr &, R (Interface::*property)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) );
        
        ALOE_PP_make_property__declaration( 0 );
        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, make_property__declaration );

        template< class T > struct PropertyTraits;

        template< class Interface, class ReferenceType >
            struct PropertyTraits< ReferenceType (*)( const Utils::SmartPtr< Interface > & ) >
            {
                typedef Interface InterfaceType;
                typedef ReferenceType PropertyType;
            };

#define ALOE_PP_PropertyTraits__MethodCaller( N ) \
        template< class Interface, class R ALOE_PP_TEMPLATE_R( N, COMMA, COMMA, class, A,, ) > \
            struct PropertyTraits< R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) > \
            { \
                typedef Interface InterfaceType; \
                typedef Detail::MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) > PropertyType; \
            };
            
        ALOE_PP_PropertyTraits__MethodCaller( 0 );
        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, PropertyTraits__MethodCaller );

    };//Detail

    namespace Utils {

        struct QueryPointerPolicy
        {
            template< class Interface >
                static void AddRef( Interface *object, IRefCount *count )
                {
                    if ( count )
                    {
                        count->AddRef();
                    }
                }

            template< class Interface >
                static bool RemRef( Interface *object, IRefCount *count )
                {
                    if ( count )
                    {
                        return count->RemRef();
                    }
                    return false;
                }
        };
        
        struct DynamicCastPointerPolicy
        {
            template< class Interface >
                static void AddRef( Interface *object, IRefCount *count )
                {
                    if ( count )
                    {
                        count->AddRef();
                    }
                }

            template< class Interface >
                static bool RemRef( Interface *object, IRefCount *count )
                {
                    if ( count )
                    {
                        return count->RemRef();
                    }
                    return false;
                }
        };
        
        struct RawPtrCastPointerPolicy
        {
            template< class Interface >
                static void AddRef( Interface *object, IRefCount *count )
                {
                    if ( count )
                    {
                        count->AddRef();
                    }
                }

            template< class Interface >
                static bool RemRef( Interface *object, IRefCount *count )
                {
                    if ( count )
                    {
                        return count->RemRef();
                    }
                    return false;
                }
        };

        struct StrongPointerPolicy
        {
            template< class Interface >
                static void AddRef( Interface *object, IRefCount *count )
                {
                    if ( count )
                    {
                        count->AddRef();
                    }
                }

            template< class Interface >
                static bool RemRef( Interface *object, IRefCount *count )
                {
                    if ( count )
                    {
                        return count->RemRef();
                    }
                    return false;
                }
        };

        struct WeakPointerPolicy
        {
            template< class Interface >
                static void AddRef( Interface *object, IRefCount *count )
                {
                }

            template< class Interface >
                static bool RemRef( Interface *object, IRefCount *count )
                {
                    return false;
                }
        };

        template< class Interface, class Policy > struct SmartPtr
        {
            Interface         *m_object;
            Aloe::IRefCount   *m_count;

            SmartPtr() : m_object(0), m_count(0)
            {
            }

            SmartPtr( const Types::None & ) : m_object(0), m_count(0)
            {
            }

            SmartPtr( Interface *p, Aloe::IRefCount *c ) : m_object( p ), m_count( c ) 
            {
            }

            SmartPtr( const SmartPtr &p ) : m_object(p.m_object), m_count(p.m_count)
            {
                AddRef();
            }
           
            template< class Other  >
                SmartPtr( const SmartPtr< Other, QueryPointerPolicy > &p ) : m_object(NULL), m_count(NULL)
                {
                    if ( p.m_object )
                    {
                        p.m_object->Query( Interface::IId(), (Types::RawPointer&)m_object, m_count );
                    }
                }
           
            template< class Other  >
                SmartPtr( const SmartPtr< Other, DynamicCastPointerPolicy > &p ) : m_object(NULL), m_count(NULL)
                {
                    if ( p.m_object )
                        if ( m_object = dynamic_cast< Interface* >( p.m_object ))
                        {
                            m_count = p.m_count; AddRef();
                        }
                }
            
            template< class Other  >
                SmartPtr( const SmartPtr< Other, RawPtrCastPointerPolicy > &p ) : m_object(NULL), m_count(NULL)
                {
                    if ( p.m_object )
                    {
                        p.m_object->QueryRawPtr( Interface::RAWPTR_ID, (Types::RawPointer&)m_object, m_count );
                    }
                }
            
            template< class Other, class OtherPolicy >
                SmartPtr( const SmartPtr< Other, OtherPolicy > &p ) : m_object(p.m_object), m_count(p.m_count)
                {
                    AddRef();
                }
            

            ~SmartPtr()
            {
                RemRef();
            }

            const SmartPtr< Interface, QueryPointerPolicy > & AutoQ() const
            {
                return *reinterpret_cast< const SmartPtr< Interface, QueryPointerPolicy > *>( this );
            }
            
            const SmartPtr< Interface, DynamicCastPointerPolicy > & UseDynamicCast() const
            {
                return *reinterpret_cast< const SmartPtr< Interface, DynamicCastPointerPolicy > *>( this );
            }
            
            const SmartPtr< Interface, RawPtrCastPointerPolicy > & UseRawPtrCast() const
            {
                return *reinterpret_cast< const SmartPtr< Interface, RawPtrCastPointerPolicy > *>( this );
            }

            SmartPtr & operator = ( const SmartPtr &p )
            {
                SmartPtr q( p );
                varSwap( m_object  , q.m_object );
                varSwap( m_count, q.m_count );
                return (*this);
            }

            SmartPtr & AddRef()
            {
                Policy::AddRef( m_object, m_count );
                return (*this);
            }

            SmartPtr & RemRef()
            {   
                if ( Policy::RemRef( m_object, m_count ))
                {
                    m_object = NULL;
                    m_count = NULL;
                }

                return (*this);
            }

            template< class PropertyType >
                typename Aloe::Detail::PropertyTraits< PropertyType >::PropertyType operator [] ( PropertyType property ) const
                {
                    return Detail::make_property( (*this), property );
                }

            template< class Ptr >
                bool QueryFrom( const Ptr &ptr )
                {
                    if ( !ptr )
                        return false;
                    SmartPtr tmp;
                    varSwap( *this, tmp );
                    return ptr->Query( Interface::IId(), (Types::RawPointer&)m_object, m_count );
                }

            template< class InterfaceType >
                bool QueryTo( SmartPtr< InterfaceType > &ptr )
                {
                    if ( !m_object )
                        return false;
                    SmartPtr< InterfaceType > tmp;
                    varSwap( ptr, tmp );
                    return m_object->Query( InterfaceType::IId(), (Types::RawPointer&)ptr.m_object, ptr.m_count );
                }

            Interface * operator -> () const
            {
                return m_object;
            }

            Interface & operator * () const
            {
                return *m_object;
            }

            Interface * get() const
            {
                return m_object;
            }

            bool isNull () const
            {
                return !m_object;
            }

            bool isLess ( const SmartPtr &p ) const
            {
                return m_object < p.m_object;
            }

            bool operator < ( const SmartPtr &p ) const
            {
                return isLess( p );
            }

            bool operator ! () const
            {
                return isNull();
            }
        };
    };
    
    namespace Detail {

        template< class _Tx > struct CArrayDeletter : IRefCount
        {
            Types::Long m_iCount;
            _Tx        *m_vArray;

            CArrayDeletter( _Tx *vArray ) : m_vArray( vArray ), m_iCount(1)
            {}

            ~CArrayDeletter()
            {
                delete [] m_vArray;
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
        };

    };// namespace Detail

    namespace Utils {

        template< class _Tx = Types::UByte > struct ArrayOf
        {
            Types::SizeType      m_size;
            _Tx                 *m_objects;
            Aloe::IRefCount     *m_count;

            typedef _Tx * Iterator;

            ArrayOf() : m_size(0), m_objects(0), m_count(0)
            {}

            ArrayOf( const Types::None & ) : m_size(0), m_objects(0), m_count(0)
            {}

            ArrayOf( Types::SizeType s, _Tx *p, Aloe::IRefCount *d ) : m_size(s), m_objects(p), m_count(d)
            {}

            ArrayOf( const ArrayOf &other ) : m_size( other.m_size ), m_objects( other.m_objects ), m_count( other.m_count )
            {
                AddRef();
            }

            template< class _Ty >
                explicit ArrayOf( const ArrayOf< _Ty >&other ) : m_objects( reinterpret_cast< _Tx *>( other.m_objects ))
                , m_count( other.m_count ), m_size( sizeof( _Tx ) * (other.m_size / sizeof( _Ty )) )
                {
                }

            ArrayOf( Types::SizeType s ) : m_size(s)
            {
                if ( m_size > 0 )
                {
                    m_objects = new _Tx[ s ];
                    m_count = new Aloe::Detail::CArrayDeletter< _Tx >( m_objects );
                }
                else {
                    m_objects = NULL;
                    m_count = NULL;
                }
            }

            ArrayOf( Types::SizeType s, const _Tx &v ) : m_size(s)
            {
                if ( m_size > 0 )
                {
                    m_objects = new _Tx[ s ];
                    m_count = new Aloe::Detail::CArrayDeletter< _Tx >( m_objects );

                    for ( _Tx *p = begin(); p != end(); ++p )
                    {
                        *p = v;
                    }
                }
                else {
                    m_objects = NULL;
                    m_count = NULL;
                }
            }

            ~ArrayOf()
            {
                RemRef();
            }

            ArrayOf< _Tx > & Resize( Types::SizeType s, const _Tx &value )
            {
                ArrayOf< _Tx > other( s );
                _Tx *p = begin();
                _Tx *q = other.begin();
                for ( ; p != end() && q != other.end(); ++p, ++q )
                {
                    *q = *p;
                }
                for ( ; q != other.end(); ++q )
                {
                    *q = value;
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< _Tx > & Resize( Types::SizeType s )
            {
                ArrayOf< _Tx > other( s );
                for ( _Tx *p = begin(), *q = other.begin(); p != end() && q != other.end(); ++p, ++q )
                {
                    *q = *p;
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< _Tx > & AddRef()
            {
                if ( m_count )
                    m_count->AddRef();
                return (*this);
            }

            ArrayOf< _Tx > & RemRef()
            {
                if ( m_count )
                {
                    if ( m_count->RemRef() )
                    {
                        m_objects = NULL;
                        m_count = NULL;
                        m_size = 0;
                    }
                }
                return (*this);
            }

            ArrayOf< _Tx > & operator = ( const ArrayOf< _Tx > &other )
            {
                ArrayOf< _Tx > q( other );
                varSwap( m_objects  , q.m_objects );
                varSwap( m_count, q.m_count );
                varSwap( m_size, q.m_size );
                return (*this);
            }

            _Tx & operator [] ( Types::SizeType index )
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_objects[ index ];
            }

            const _Tx & operator [] ( Types::SizeType index ) const
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_objects[ index ];
            }

            ArrayOf first_n( Types::SizeType n ) const
            {
                ArrayOf a( *this );
                a.m_size = varMin( n, a.m_size );
                return a;
            }
            
            ArrayOf subarr( Types::SizeType first, Types::SizeType count ) const
            {
                ArrayOf a( *this );
                a.m_objects = m_objects + first;
                a.m_size = count;
                return a;
            }

            Iterator begin() const
            {
                return m_objects;
            }

            Iterator end() const
            {
                return (m_objects + m_size);
            }

            Types::SizeType size() const
            {
                return m_size;
            }

            void resize( Types::SizeType s )
            {
                Resize( s );
            }

            bool empty() const
            {
                return !m_objects;
            }

            bool operator ! () const
            {
                return empty();
            }

	    Types::Tuple< _Tx *, Types::SizeType > tuple ()
            {
                return Types::Tuple< _Tx *, Types::SizeType >( m_objects, m_size );
            }
            
            Types::Tuple< const _Tx *, Types::SizeType > tuple () const
            {
                return Types::Tuple< const _Tx *, Types::SizeType >( m_objects, m_size );
            }
        };

        template< class _Tx, class _PolicyX > struct ArrayOf< SmartPtr< _Tx, _PolicyX > >
        {
            Types::SizeType m_size;
            SmartPtr< _Tx, _PolicyX > *m_objects;
            Aloe::IRefCount *m_count;
            
            typedef SmartPtr< _Tx, _PolicyX > * Iterator;

            ArrayOf() : m_size(0), m_objects(0), m_count(0)
            {}

            ArrayOf( const Types::None & ) : m_size(0), m_objects(0), m_count(0)
            {}

            ArrayOf( Types::SizeType s, _Tx *p, Aloe::IRefCount *d ) : m_size(s), m_objects(p), m_count(d)
            {}

            ArrayOf( const ArrayOf &other ) : m_size( other.m_size ), m_objects( other.m_objects ), m_count( other.m_count )
            {
                AddRef();
            }

            template< class _Ty, class _PolicyY >
                ArrayOf( const ArrayOf< SmartPtr< _Ty, _PolicyY > > &other ) : m_size( other.m_size )
                {
                    m_objects = new SmartPtr< _Tx, _PolicyX >[ m_size ];
                    m_count = new Aloe::Detail::CArrayDeletter< SmartPtr< _Tx, _PolicyX > >( m_objects );
                    SmartPtr< _Ty, _PolicyY > *p = other.begin();
                    SmartPtr< _Tx, _PolicyX > *q = begin();
                    for (; p != other.end(); ++p, ++q )
                    {
                        *q = *p;
                    }
                }
            
            const ArrayOf< SmartPtr< _Tx, QueryPointerPolicy > > & AutoQ() const
            {
                return *reinterpret_cast< const ArrayOf< SmartPtr< _Tx, QueryPointerPolicy > > *>( this );
            }
            
            const ArrayOf< SmartPtr< _Tx, DynamicCastPointerPolicy > > & UseDynamicCast() const
            {
                return *reinterpret_cast< const ArrayOf< SmartPtr< _Tx, DynamicCastPointerPolicy > > *>( this );
            }
            
            const ArrayOf< SmartPtr< _Tx, RawPtrCastPointerPolicy > > & UseRawPtrCast() const
            {
                return *reinterpret_cast< const ArrayOf< SmartPtr< _Tx, RawPtrCastPointerPolicy > > *>( this );
            }

            ArrayOf( Types::SizeType s ) : m_size(s)
            {
                if ( m_size > 0 )
                {
                    m_objects = new SmartPtr< _Tx, _PolicyX >[ s ];
                    m_count = new Aloe::Detail::CArrayDeletter< SmartPtr< _Tx, _PolicyX > >( m_objects );
                }
                else {
                    m_objects = NULL;
                    m_count = NULL;
                }
            }

            ArrayOf( Types::SizeType s, const _Tx &v ) : m_size(s)
            {
                if ( m_size > 0 )
                {
                    m_objects = new SmartPtr< _Tx, _PolicyX >[ s ];
                    m_count = new Aloe::Detail::CArrayDeletter< SmartPtr< _Tx, _PolicyX > >( m_objects );

                    for ( _Tx *p = begin(); p != end(); ++p )
                    {
                        *p = v;
                    }
                }
                else {
                    m_objects = NULL;
                    m_count = NULL;
                }
            }

            ~ArrayOf()
            {
                RemRef();
            }

            ArrayOf< SmartPtr< _Tx, _PolicyX > > & Resize( Types::SizeType s, const _Tx &value )
            {
                ArrayOf< SmartPtr< _Tx, _PolicyX > > other( s );
                SmartPtr< _Tx, _PolicyX > *p = begin();
                SmartPtr< _Tx, _PolicyX > *q = other.begin();
                for ( ; p != end() && q != other.end(); ++p, ++q )
                {
                    *q = *p;
                }
                for ( ; q != other.end(); ++q )
                {
                    *q = value;
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx, _PolicyX > > & Resize( Types::SizeType s )
            {
                ArrayOf< SmartPtr< _Tx, _PolicyX > > other( s );
                for ( SmartPtr< _Tx, _PolicyX > *p = begin(), *q = other.begin(); p != end() && q != other.end(); ++p, ++q )
                {
                    *q = *p;
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx, _PolicyX > > & Clean()
            {
                Types::Int iCount = 0;
                for ( SmartPtr< _Tx, _PolicyX > *p = begin(); p != end(); ++p )
                {
                    iCount += !!(*p);
                }
                ArrayOf< SmartPtr< _Tx, _PolicyX > > other( iCount );
                for ( SmartPtr< _Tx, _PolicyX > *p = begin(), *q = other.begin(); p != end(); ++p )
                {
                    if ( !!(*p) )
                    {
                        *q = *p;
                        ++q;
                    }
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx, _PolicyX > > & AddRef()
            {
                if ( m_count )
                    m_count->AddRef();
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx, _PolicyX > > & RemRef()
            {
                if ( m_count )
                {
                    if ( m_count->RemRef() )
                    {
                        m_objects = NULL;
                        m_count = NULL;
                        m_size = 0;
                    }
                }
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx, _PolicyX > > & operator = ( const ArrayOf< SmartPtr< _Tx, _PolicyX > > &other )
            {
                ArrayOf< SmartPtr< _Tx, _PolicyX > > q( other );
                varSwap( m_objects, q.m_objects );
                varSwap( m_count, q.m_count );
                varSwap( m_size, q.m_size );
                return (*this);
            }

            SmartPtr< _Tx, _PolicyX > & operator [] ( Types::SizeType index )
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_objects[ index ];
            }
            
            const SmartPtr< _Tx, _PolicyX > & operator [] ( Types::SizeType index ) const 
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_objects[ index ];
            }
            
            ArrayOf first_n( Types::SizeType n ) const
            {
                ArrayOf a( *this );
                a.m_size = varMin( n, a.m_size );
                return a;
            }
            
            ArrayOf subarr( Types::SizeType first, Types::SizeType count ) const
            {
                ArrayOf a( *this );
                a.m_objects = m_objects + first;
                a.m_size = count;
                return a;
            }

            Iterator begin() const
            {
                return m_objects;
            }

            Iterator end() const
            {
                return (m_objects + m_size);
            }

            Types::SizeType size() const
            {
                return m_size;
            }

            void resize( Types::SizeType s )
            {
                Resize( s );
            }

            bool empty() const
            {
                return !m_objects;
            }

            bool operator ! () const
            {
                return empty();
            }

            Types::Tuple< SmartPtr< _Tx, _PolicyX > *, Types::SizeType > tuple ()
            {
                return Types::Tuple< SmartPtr< _Tx, _PolicyX > *, Types::SizeType >( m_objects, m_size );
            }
            
            Types::Tuple< const SmartPtr< _Tx, _PolicyX > *, Types::SizeType > tuple () const
            {
                return Types::Tuple< const SmartPtr< _Tx, _PolicyX > *, Types::SizeType >( m_objects, m_size );
            }
        };

        template< class _Tx > struct VectorOf
        {
            ArrayOf< _Tx > m_array;
            Types::SizeType m_size;

            typedef typename ArrayOf< _Tx >::Iterator Iterator;

            VectorOf() : m_size(0)
            {
            }
            
            VectorOf( const Types::None & ) : m_size(0)
            {
            }

            VectorOf( Types::SizeType size )
            {
                m_array.Resize( size );
                m_size = size;
            }

            VectorOf( Types::SizeType size, const _Tx &x )
            {
                m_array.Resize( size, x );
                m_size = size;
            }

            VectorOf & operator = ( const ArrayOf< _Tx > &array )
            {
                m_array = array;
                m_size = m_array.size();
                return (*this);
            }
            
            VectorOf & operator = ( const Types::None & )
            {
                clear();
                return (*this);
            }

            VectorOf< _Tx > & clear()
            {
                VectorOf v;
                varSwap( v, *this );
                return (*this);
            }

            VectorOf< _Tx > & push_back( const _Tx &x )
            {
                while ( m_array.size() <= m_size )
                {
                    m_array.resize( m_array.empty() ? 4 : m_array.size() * 2 );
                }
                m_array[ m_size++ ] = x;

                return (*this);
            }

            VectorOf< _Tx > & pop_back( _Tx &x )
            {
                if ( m_size > 0 )
                {
                    x = m_array[ --m_size ];
                    m_array[ m_size ] = _Tx();
                }
                return (*this);
            }
            
            VectorOf< _Tx > & pop_back()
            {
                if ( m_size > 0 )
                {
                    m_array[ --m_size ] = _Tx();
                }
                return (*this);
            }
            
            VectorOf< _Tx > & resize( Types::SizeType s )
            {
                reserve( s );

                while ( s < m_size )
                {
                    m_array[ --m_size ] = _Tx();
                }

                while ( s > m_size )
                {
                    m_array[ m_size++ ] = _Tx();
                }
                return (*this);
            }

            VectorOf< _Tx > & reserve( Types::SizeType s )
            {
                if ( m_array.size() < s )
                {
                    m_array.resize( s );
                }
                return (*this);
            }

            VectorOf & resize_to_fit( Types::SizeType s )
            {
                if ( s < m_array.size() )
                    return (*this);

                Types::SizeType arraySize = m_array.size();
                while ( arraySize < s )
                {
                    arraySize *= 2;
                }
                return resize( arraySize );
            }

            Types::SizeType remove_if_equal( const _Tx &x )
            {
                VectorOf< _Tx > v;
                for ( Iterator iter = m_array.begin(); iter != m_array.end(); ++iter )
                {
                    if ( *iter != x )
                    {
                        v.push_back( *iter );
                    }
                }
                varSwap( v, *this );
                return (v.size() - size());
            }

            Types::SizeType append( const _Tx &x )
            {
                return push_back( x ).size() - 1;
            }

            Types::Bool remove( Types::SizeType index )
            {
                Types::SizeType i = 0;
                VectorOf< _Tx > v;
                for ( Iterator iter = m_array.begin(); iter != m_array.end(); ++iter, ++i )
                {
                    if ( i != index )
                    {
                        v.push_back( *iter );
                    }
                }
                varSwap( v, *this );
                return (v.size() < size());
            }
            
            Types::Bool remove( Iterator where )
            {
                VectorOf< _Tx > v;
                for ( Iterator iter = m_array.begin(); iter != m_array.end(); ++iter )
                {
                    if ( iter != where )
                    {
                        v.push_back( *iter );
                    }
                }
                varSwap( v, *this );
                return (v.size() < size());
            }

            _Tx & back()
            {
                return m_array[ m_size-1 ];
            }

            Iterator begin() const
            {
                return m_array.begin();
            }

            Iterator end() const
            {
                return begin() + m_size;
            }

            Types::Bool empty() const
            {
                return (0 == m_size);
            }

            Types::SizeType size() const
            {
                return m_size;
            }

            Types::SizeType capacity() const
            {
                return m_array.size();
            }

            ArrayOf< _Tx > & array()
            {
                return m_array;
            }

            const ArrayOf< _Tx > & array() const
            {
                return m_array;
            }
            
            ArrayOf< _Tx > tight_array() const
            {
                return m_array.first_n( m_size );
            }
            
            _Tx & operator [] ( Types::SizeType index )
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_array[ index ];
            }

            const _Tx & operator [] ( Types::SizeType index ) const
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_array[ index ];
            }
        };

        template< class _Tx > struct AssetOf : VectorOf< _Tx >
        {
            VectorOf< Types::SizeType > m_free;
            VectorOf< Types::SizeType > m_indices;

            AssetOf()
            {}

            AssetOf( const Types::None & )
            {}
            
            AssetOf & operator = ( const VectorOf< _Tx > &v )
            {
                m_free = Types::None();
                m_indices = Types::None();
                VectorOf< _Tx >::operator = ( v );
                return (*this);
            }
            
            AssetOf & operator = ( const ArrayOf< _Tx > &v )
            {
                m_free = Types::None();
                m_indices = Types::None();
                VectorOf< _Tx >::operator = ( v );
                return (*this);
            }
            
            AssetOf & operator = ( const Types::None &v )
            {
                clear();
                return (*this);
            }

            AssetOf & clear()
            {
                m_free = Types::None();
                m_indices = Types::None();
                VectorOf< _Tx >::clear();
                return (*this);
            }
            
            Types::SizeType add( const _Tx & x )
            {
                if ( m_free.empty() )
                {
                    m_indices.push_back( append( x ));
                    return m_indices.back();
                }
                else
                {
                    Types::SizeType n = m_free.back();
                    m_indices.push_back( n );
                    m_array[ n ] = x;
                    m_free.pop_back();
                    return n;
                }
            }

            Types::Bool del( Types::SizeType index )
            {
                if ( index < m_array.size() )
                {
                    m_array[ index ] = Types::None();
                    m_free.push_back( index );
                    m_indices.remove_if_equal( index );
                    return true;
                }
                else {
                    return false;
                }
            }

            Types::SizeType size() const
            {
                return m_indices.size();
            }

            Types::Bool empty() const
            {
                return m_indices.empty();
            }

            struct Iterator
            {
                VectorOf< Types::SizeType >::Iterator m_iter;
                VectorOf< _Tx > &m_vect;

                Iterator( VectorOf< Types::SizeType >::Iterator iter, VectorOf< _Tx > &vect )
                    : m_iter( iter ), m_vect( vect )
                {}

                Iterator & operator ++ () { ++m_iter; return (*this); }
                Iterator & operator -- () { ++m_iter; return (*this); }
                Types::Bool operator == ( const Iterator &i ) { return i.m_iter == m_iter; }
                Types::Bool operator != ( const Iterator &i ) { return i.m_iter != m_iter; }
                _Tx & operator * () { return m_vect[ *m_iter ]; }
                _Tx * operator -> () { return &(m_vect[ *m_iter ]); }
            };

            Iterator begin() const
            {
                return Iterator( m_indices.begin(), const_cast< AssetOf< _Tx > &>( *this ));
            }

            Iterator end() const
            {
                return Iterator( m_indices.end(), const_cast< AssetOf< _Tx > &>( *this ));
            }

            ArrayOf< _Tx > array() const
            {
                ArrayOf< _Tx > a( size() );
                ArrayOf< _Tx >::Iterator jter = a.begin();
                
                for ( Iterator iter = begin(); iter != end(); ++iter, ++jter )
                {
                    *jter = *iter;
                }

                return a;
            }
        };


    };//Utils

};//Aloe

#endif//ALOE_INCLUDED_ALOE_TYPES_H
