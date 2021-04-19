#ifndef ALOE_WIN32_SYSTEM
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'Win32System.cpp'."
#endif

namespace Aloe {
    namespace Win32 {

        struct CFilePos;
        
        struct CFile
            : Detail::Implementation
            < CFile
            , Detail::Interfaces< IStream >
            , Detail::Bases< Detail::CRefCount >
            , 0x4000 >
        {
            Types::String m_fileName;
            Utils::SmartPtr< CFilePos, Utils::WeakPointerPolicy > m_streamPos;
            ::HANDLE m_hFile;
            ::DWORD m_dwAccess;
            ::DWORD m_dwShareMode;
            ::DWORD m_dwCreationDisposition;
            ::DWORD m_dwAttributes;
            ::DWORD m_dwError;
            Types::Long m_lFlags;

            ThisPtr __init__( const Types::String &fileName
                    , ::DWORD dwAccess
                    , ::DWORD dwShareMode
                    , ::DWORD dwCreationDisposition
                    , ::DWORD dwAttributes
                    , Types::Long lFlags )
            {
                m_fileName = fileName;
                m_hFile = INVALID_HANDLE_VALUE;
                m_dwAccess = dwAccess;
                m_dwShareMode = dwShareMode;
                m_dwCreationDisposition = dwCreationDisposition;
                m_dwAttributes = dwAttributes;
                m_dwError = 0;
                m_lFlags = lFlags;
                return Super::__init__();
            }

            Utils::SmartPtr< IStreamPos > CreateStreamPos();

            void CloseStreamPos();
            
            void CloseFile()
            {
                m_streamPos = Types::None();

                if ( INVALID_HANDLE_VALUE != m_hFile )
                {
                    ::CloseHandle( m_hFile );
                    m_hFile = INVALID_HANDLE_VALUE;
                }
            }

            ~CFile()
            {
                Close( Types::None() );
            }

            aloe__method_imp( IStream, Open, argv )
            {
                m_hFile = ::CreateFileW( (WCHAR*)(m_fileName.c_str()), m_dwAccess, m_dwShareMode
			, NULL, m_dwCreationDisposition, m_dwAttributes, NULL );

                if ( INVALID_HANDLE_VALUE == m_hFile )
                {
                    m_dwError = ::GetLastError();
                    return Types::None();
                }
                return CreateStreamPos();
            }

            aloe__method_imp( IStream, Close, argv )
            {
                CloseStreamPos();
                
                return Types::None();
            }

            aloe__method_imp( IStream, Flush, argv )
            {
                if ( INVALID_HANDLE_VALUE != m_hFile )
                {
                    ::FlushFileBuffers( m_hFile );
                }
                
                return Types::None();
            }
        };
        
        struct CFilePos
            : Detail::Implementation
            < CFilePos
            , Detail::Interfaces< IStreamPos >
            , Detail::Bases< Detail::CRefCount >
            , 0x4001 >
        {
            Utils::SmartPtr< CFile > m_file;
            Types::LongLong m_position;

            ~CFilePos()
            {
                if ( !!m_file )
                {
                    m_file->CloseFile();
                }
            }

            Types::LongLong GetSize()
            {
                ::DWORD dwHighSize = 0;
                ::DWORD dwSize = ::GetFileSize( m_file->m_hFile, &dwHighSize );
                return ( Utils::copyCast< Types::LongLong >( dwHighSize ) << 32 |
			 Utils::copyCast< Types::LongLong >( dwSize ));
            }

            ThisPtr __init__( const Utils::SmartPtr< CFile > &file)
            {
                m_file = file;
                return Super::__init__();
            }
            
            aloe__property_imp_put( IStreamPos, BytesFromStart, bytes )
            {
                if ( !m_file )
                    return;

                ::SetFilePointer( m_file->m_hFile, (::LONG)bytes, NULL, FILE_BEGIN );
                m_position = bytes;
            }

            aloe__property_imp_get( IStreamPos, BytesFromStart )
            {
                if ( !m_file )
                    return Types::None();

                return m_position;
            }

            aloe__property_imp_append( IStreamPos, BytesFromStart, bytes )
            {
                if ( !m_file )
                    return Types::None();

                ::SetFilePointer( m_file->m_hFile, (::LONG)bytes, NULL, FILE_CURRENT );
                m_position += bytes;
                return Types::None();
            }
            
            aloe__property_imp_remove( IStreamPos, BytesFromStart, bytes )
            {
                if ( !m_file )
                    return Types::None();

                ::SetFilePointer( m_file->m_hFile, (::LONG)-bytes, NULL, FILE_CURRENT );
                m_position -= bytes;
                return Types::None();
            }
            
            aloe__property_imp_put( IStreamPos, BytesToEnd, bytes )
            {
                if ( !m_file )
                    return;

                ::SetFilePointer( m_file->m_hFile, (::LONG)bytes, NULL, FILE_END );
                m_position = GetSize() - bytes;
            }

            aloe__property_imp_get( IStreamPos, BytesToEnd )
            {
                if ( !m_file )
                    return Types::None();

                return (GetSize() - m_position);
            }

            aloe__property_imp_append( IStreamPos, BytesToEnd, bytes )
            {
                if ( !m_file )
                    return Types::None();

                ::SetFilePointer( m_file->m_hFile, (::LONG)-bytes, NULL, FILE_CURRENT );
                m_position -= bytes;
                return Types::None();
            }
            
            aloe__property_imp_remove( IStreamPos, BytesToEnd, bytes )
            {
                if ( !m_file )
                    return Types::None();

                ::SetFilePointer( m_file->m_hFile, (::LONG)bytes, NULL, FILE_CURRENT );
                m_position += bytes;
                return Types::None();
            }

            aloe__property_imp_get( IStreamPos, Stream )
            {
                return m_file;
            }

            aloe__method_imp( IStreamPos, Write, argv )
            {
                aloe__extract2( IStreamPos, Write, args, argv, data, size );

                if ( !m_file )
                    return Types::None();
                
                ::DWORD bytesWritten = 0;
                ::BOOL bOk = ::WriteFile( m_file->m_hFile, data, (::LONG)size, &bytesWritten, NULL );

                return bytesWritten;
            }

            aloe__method_imp( IStreamPos, Read, argv )
            {
                aloe__extract2( IStreamPos, Read, args, argv, data, size );

                if ( !m_file )
                    return Types::None();
                
                ::DWORD bytesRead = 0;
                ::BOOL bOk = ::ReadFile( m_file->m_hFile, data, (::LONG)size, &bytesRead, NULL );

                return bytesRead;
            }
        };//CFilePos
            
        Utils::SmartPtr< IStreamPos > CFile::CreateStreamPos()
        {
            Utils::SmartPtr< CFilePos > stmPos = (new CFilePos)->__init__( __self__() );
            if ( m_lFlags & IStorage::F_APPEND )
            {
                stmPos->put_BytesToEnd(0);
            }
            m_streamPos = stmPos;
            return stmPos;
        }

        void CFile::CloseStreamPos()
        {
            if ( !!m_streamPos )
            {
                m_streamPos->m_file = Types::None();
                m_streamPos = Types::None();
            }

            if ( INVALID_HANDLE_VALUE != m_hFile )
            {
                ::CloseHandle( m_hFile );
                m_hFile = INVALID_HANDLE_VALUE;
            }
        }
                
        struct CDirectoryEnum
            : Detail::Implementation
            < CDirectoryEnum
            , Detail::Interfaces< Aloe::IStorageEnum >
            , Detail::Bases< Detail::CRefCount >
            , 0x4002 >
        {
            Utils::SmartPtr< Aloe::IStorage > m_storage;
            Types::String m_path;
            ::HANDLE m_hFind;
            ::WIN32_FIND_DATA m_findData;
            ::BOOL m_bNext;

            ThisPtr __init__( const Utils::SmartPtr< IStorage > &storage, const Types::String path )
            {
                m_storage = storage;
                m_path = path;
                if ( m_path[ m_path.size()-1 ] == L'\\' )
                {
                    m_path += aloe__string("*.*");
                }
                m_bNext = FALSE;
                m_hFind = INVALID_HANDLE_VALUE;
                Reset( Types::None() );
                return Super::__init__();
            }

            ~CDirectoryEnum()
            {
                if ( INVALID_HANDLE_VALUE != m_hFind )
                {
                    ::FindClose( m_hFind );
                }
            }
            
            aloe__method_imp( IStorageEnum, Reset, argv )
            {
                if ( INVALID_HANDLE_VALUE != m_hFind )
                {
                    ::FindClose( m_hFind );
                }

                m_hFind = ::FindFirstFile( (WCHAR*)(m_path.c_str()), &m_findData );
                
                if ( INVALID_HANDLE_VALUE != m_hFind )
                {
                    m_bNext = TRUE;
                }
                else {
                    m_bNext = FALSE;
                }

                return (m_bNext > 0);
            }
            
            aloe__method_imp( IStorageEnum, Next, argv )
            {
                aloe__extract2( IStorageEnum, Next, args, argv, outPath, outFlags );

                if ( m_bNext )
                {
                    if ( outPath )
                    {
                        *outPath = Types::String( (Types::CWideStr)( m_findData.cFileName ));
                    }
                    if ( outFlags )
                    {
                        *outFlags = 0;
                        if ( m_findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
                        {
                            *outFlags = IStorage::F_STORAGE;
                        }
                    }
                    m_bNext = ::FindNextFile( m_hFind, &m_findData );
                    return true;
                }
                return false;
            }
            
            aloe__property_imp_get( IStorageEnum, Storage )
            {
                return m_storage;
            }

            aloe__property_imp_get( IStorageEnum, Path )
            {
                Types::SizeType pos = m_path.rfind(L"\\");
                if ( Types::String::npos != pos )
                {
                    return m_path.substr( 0, pos );
                }

                return aloe__string("");
            }
                    
        };//CDirectoryEnum
        
        
    };
};
