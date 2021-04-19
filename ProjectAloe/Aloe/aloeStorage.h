
#ifndef ALOE_INCLUDED_ALOE_STORAGE_H
#define ALOE_INCLUDED_ALOE_STORAGE_H

#include "Aloe/aloe.h"

namespace Aloe {

    struct IStreamPos;
    struct IStream;
    struct IStorageEnum;
    struct IStorage;
    
    aloe__interface( IStreamPos )
    {
        aloe__iid( IStreamPos );

        aloe__prop( IStreamPos, BytesFromStart
                , ____, ____
                , get , put , type( LongLong )
                , append, ____, type( LongLong )
                , remove, ____, type( LongLong )
                , ____, ____, ____ );
        
        aloe__prop( IStreamPos, BytesToEnd
                , ____, ____
                , get , put , type( LongLong )
                , append, ____, type( LongLong )
                , remove, ____, type( LongLong )
                , ____, ____, ____ );

        aloe__prop( IStreamPos, Stream
                , ____, ____
                , get , ____, pointer( IStream )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IStreamPos, Write
                , type( SizeType )
                , tuple2(
                    arg( data, In, type( CUByteArray )),
                    arg( size, In, type( SizeType ))
                    ));

        aloe__method( IStreamPos, Read
                , type( SizeType )
                , tuple2(
                    arg( data, In, type( NCUByteArray )),
                    arg( size, In, type( SizeType ))
                    ));

    };

    aloe__runtime_prop( IStreamPos, BytesFromStart );
    aloe__runtime_prop( IStreamPos, BytesToEnd );
    aloe__runtime_prop( IStreamPos, Stream );
    aloe__runtime_method( IStreamPos, Write );
    aloe__runtime_method( IStreamPos, Read );
    
    aloe__interface( IStream )
    {
        aloe__iid( IStream );

        aloe__method( IStream, Open
                , pointer( IStreamPos )
                , tuple0()
                );
        
        aloe__method( IStream, Close
                , ____
                , ____
                );
        
        aloe__method( IStream, Flush
                , ____
                , ____
                );
    };
    
    aloe__runtime_method( IStream, Open );
    aloe__runtime_method( IStream, Close );
    aloe__runtime_method( IStream, Flush );

    aloe__interface( IStorageEnum )
    {
        aloe__iid( IStorageEnum );

        aloe__method( IStorageEnum, Reset
                , type( Bool )
                , tuple0()
                );

        aloe__method( IStorageEnum, Next
                , type( Bool )
                , tuple2( 
                    arg( path, Out, type( String * )),
                    arg( flags, Out, type( Long * ))
                    )
                );
        
        aloe__prop( IStorageEnum, Storage
                , ____, ____
                , get , ____, pointer( IStorage )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IStorageEnum, Path
                , ____, ____
                , get , ____, type( String )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

    };
    
    aloe__runtime_method( IStorageEnum, Reset );
    aloe__runtime_method( IStorageEnum, Next );
    aloe__runtime_method( IStorageEnum, Storage );
    
    aloe__interface( IStorage )
    {
        aloe__iid( IStorage );
        
        enum Flags
        {
            F_STREAM   = 0,
            F_STORAGE  = 1,
            F_EXISTING = 0,
            F_CLEAN    = 2,
            F_APPEND   = 4
        };

        aloe__method( IStorage, Create
                , pointer( IProvider )
                , tuple2(
                    arg( path, In, type( String )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IStorage, Exists
                , type( Bool )
                , tuple2(
                    arg( path, In, type( String )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IStorage, Remove
                , type( Bool )
                , tuple2(
                    arg( path, In, type( String )),
                    arg( flags, In, type( Long ))
                    )
                );

        aloe__method( IStorage, Enumerate
                , pointer( IStorageEnum )
                , tuple1(
                    arg( path, In, type( String ))
                    )
                );
    };
    
    aloe__runtime_method( IStorage, Create );
    aloe__runtime_method( IStorage, Exists );
    aloe__runtime_method( IStorage, Remove );
    aloe__runtime_method( IStorage, Enumerate );


    namespace Utils {
        
        struct NoSwapBytesPolicy
        {
            template< class _T > static Types::UByte * SwapBytes( _T * x )
            {
                return (Types::UByte*)x;
            }
        };
        
        struct SwapBytesPolicy
        {
            template< const int NumBytes > struct Swap
            {
                static Types::UByte * Apply( Types::UByte *p ) {}
            };
            
            ALOE_PP_SPECIALIZATION struct Swap< 2 >
            {
                static Types::UByte * Apply( Types::UByte *p )
                {
                    varSwap( p[0], p[1] );
                    return p;
                }
            };
            
            ALOE_PP_SPECIALIZATION struct Swap< 4 >
            {
                static Types::UByte * Apply( Types::UByte *p )
                {
                    varSwap( p[0], p[3] );
                    varSwap( p[1], p[2] );
                    return p;
                }
            };
            
            ALOE_PP_SPECIALIZATION struct Swap< 8 >
            {
                static Types::UByte * Apply( Types::UByte *p )
                {
                    varSwap( p[0], p[7] );
                    varSwap( p[1], p[6] );
                    varSwap( p[2], p[5] );
                    varSwap( p[3], p[4] );
                    return p;
                }
            };
            
            template< class _T > static Types::UByte * SwapBytes( _T * x )
            {
				return Swap< sizeof( _T ) >::Apply( (Types::UByte *)x );
            }
        };

        template< class _ByteSwapPolicy > struct AutoStream
        {
            SmartPtr< Aloe::IStreamPos > m_stmPos;

            void Write( Types::CUByteArray buffer, Types::SizeType size )
            {
                if ( size != m_stmPos[ Aloe::IStreamPos::Write ]( buffer, size ))
                {
                    throw Errors::Error_BadStream();
                }
            }

            void Read( Types::NCUByteArray buffer, Types::SizeType size )
            {
                if ( size != m_stmPos[ Aloe::IStreamPos::Write ]( buffer, size ))
                {
                    throw Errors::BadStreamSize();
                }
            }

            AutoStream( const SmartPtr< Aloe::IStreamPos > &stmPos ) : m_stmPos( stmPos )
            {}

            //
            // writes
            //
            
            AutoStream & operator << ( Types::UInt8 x )
            {
                Write( &x, sizeof(x) );
                return (*this);
            }
            
            AutoStream & operator << ( Types::UInt16 x )
            {
                Write( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator << ( Types::UInt32 x )
            {
                Write( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator << ( Types::UInt64 x )
            {
                Write( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator << ( Types::Int8 x )
            {
                Write( &x, sizeof(x) );
                return (*this);
            }
            
            AutoStream & operator << ( Types::Int16 x )
            {
                Write( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator << ( Types::Int32 x )
            {
                Write( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator << ( Types::Int64 x )
            {
                Write( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator << ( Types::Float32 x )
            {
                Write( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator << ( Types::Float64 x )
            {
                Write( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            //
            // reads
            //
            
            AutoStream & operator >> ( Types::UInt8 &x )
            {
                Read( &x, sizeof(x) );
                return (*this);
            }
            
            AutoStream & operator >> ( Types::UInt16 &x )
            {
                Read( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator >> ( Types::UInt32 &x )
            {
                Read( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator >> ( Types::UInt64 &x )
            {
                Read( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator >> ( Types::Int8 &x )
            {
                Read( &x, sizeof(x) );
                return (*this);
            }
            
            AutoStream & operator >> ( Types::Int16 &x )
            {
                Read( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator >> ( Types::Int32 &x )
            {
                Read( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator >> ( Types::Int64 &x )
            {
                Read( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator >> ( Types::Float32 &x )
            {
                Read( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }

            AutoStream & operator >> ( Types::Float64 &x )
            {
                Read( _ByteSwapPolicy::SwapBytes( &x ), sizeof(x) );
                return (*this);
            }
        };
//
// if platform is x86
// 
        typedef AutoStream< NoSwapBytesPolicy > LittleEndianStream;
        typedef AutoStream< SwapBytesPolicy >   BigEndianStream;
    };//Utils

};//Aloe

#endif//ALOE_INCLUDED_ALOE_STORAGE_H
