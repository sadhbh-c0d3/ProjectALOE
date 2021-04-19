#ifndef ALOE_INCLUDED_ALOE_OBJECT_REF_H
#define ALOE_INCLUDED_ALOE_OBJECT_REF_H

#include "Aloe/aloe.h"

namespace Aloe {

	namespace Utils {

		template< class _T > Types::Int less( _T &a, _T &b )
		{
			return a < b;
		}
		
		template< class _T > Types::Int compare( _T &a, _T &b )
		{
			return ( Utils::less( a, b ) ? -1 : (Utils::less( b, a ) ? 1 : 0));
		}

		template< class _A > Types::Int compareArrays( const _A &a, const _A &b )
		{
			_A::Iterator i = a.begin();
			_A::Iterator j = b.begin();

			for ( ; i < a.end() && j < b.end(); ++i, ++j )
			{
				Types::Int scr = Utils::compare( *i, *j );
				if ( 0 != scr )
					return scr;
			}

			if ( i != a.end() )
				return 1;

			if ( j != b.end() )
				return -1;

			return 0;
		}

	};//Utils

	struct ObjectRef
	{
		typedef Types::Int  (*PfnCompare )( const ObjectRef &, const ObjectRef & );
		typedef Types::Bool (*PfnGetValue)( const ObjectRef &self, ObjectRef &buffer );
		typedef Types::Bool (*PfnSetValue)( ObjectRef &self, const ObjectRef &buffer );
		typedef void		(*PfnDestroy )( ObjectRef &self );

		Types::RawPointer  m_data;
		Types::LongPointer m_typeId;
		IRefCount		  *m_count;
		PfnGetValue pfnGetValue;
		PfnSetValue pfnSetValue;
		PfnCompare  pfnCompare;
		PfnDestroy  pfnDestroy;

		ObjectRef()
		{
			m_data = NULL;
			pfnGetValue = NULL;
			pfnSetValue = NULL;
			pfnCompare = NULL;
			pfnDestroy = NULL;
			m_count = new Detail::CRefCount();
		}

		~ObjectRef()
		{
			if ( m_count )
			{
				if ( m_count->RemRef())
				{
					if ( pfnDestroy )
						(*pfnDestroy)( *this );
				}
			}
		}

		ObjectRef( const ObjectRef &other )
			: m_data( other.m_data )
			, m_typeId( other.m_typeId )
			, m_count( other.m_count )
			, pfnGetValue( other.pfnGetValue )
			, pfnSetValue( other.pfnSetValue )
			, pfnCompare( other.pfnCompare )
			, pfnDestroy( other.pfnDestroy )
		{
			if ( m_count )
			{
				m_count->AddRef();
			}
		}

		void Assign( const ObjectRef &other )
		{
			ObjectRef x( other );
			Utils::varSwap( m_typeId, x.m_typeId );
			Utils::varSwap( m_data, x.m_data );
			Utils::varSwap( m_count, x.m_count );
			Utils::varSwap( pfnGetValue, x.pfnGetValue );
			Utils::varSwap( pfnSetValue, x.pfnSetValue );
			Utils::varSwap( pfnCompare, x.pfnCompare );
			Utils::varSwap( pfnDestroy, x.pfnDestroy );
		}
		
		ObjectRef & operator = ( const ObjectRef &other )
		{
			Assign( other );
			return (*this);
		}


		Types::LongPointer get_Type() const
		{
			return m_typeId;
		}

		Types::Bool get_Value( ObjectRef &other ) const
		{
			if ( pfnGetValue )
				return (*pfnGetValue)( *this, other );
			else
				return false;
		}
		
		Types::Bool put_Value( const ObjectRef &other )
		{
			if ( pfnSetValue )
				return (*pfnSetValue)( *this, other );
			else
				return false;
		}

		Types::Int Compare( const ObjectRef &other ) const
		{
			Types::Int cr = Utils::compare( m_typeId, other.m_typeId );
			if (( 0 == cr ) && ( !!pfnCompare ))
			{
				cr = (*pfnCompare)( *this, other );
			}
			return cr;
		}

		bool operator < ( const ObjectRef &other ) const { return ( Compare( other ) == -1 ); }
		bool operator > ( const ObjectRef &other ) const { return ( Compare( other ) == 1 ); }
		bool operator <= ( const ObjectRef &other ) const { return ( Compare( other ) < 1 ); }
		bool operator >= ( const ObjectRef &other ) const { return ( Compare( other ) > -1 ); }
		bool operator == ( const ObjectRef &other ) const { return ( Compare( other ) == 0 ); }
		bool operator != ( const ObjectRef &other ) const { return ( Compare( other ) != 0 ); }
	};

	template< class _T > struct ObjectCompareTemplate
	{
		static Types::Int Compare( const _T &a, const _T &b )
		{
			return Utils::compare( a, b );
		}
	};
		
	
	template< class _T > struct ObjectCompareTemplate< Utils::ArrayOf< _T > >
	{
		typedef Utils::ArrayOf< _T > Type;

		static Types::Int Compare( const Type &a, const Type &b )
		{
			return Utils::compareArrays( a, b );
		}
	};
	
	template< class _T > struct ObjectCompareTemplate< Utils::VectorOf< _T > >
	{
		typedef Utils::VectorOf< _T > Type;

		static Types::Int Compare( const Type &a, const Type &b )
		{
			return Utils::compareArrays( a, b );
		}
	};
		
	template< class _T > struct ObjectCompareTemplate< Utils::AssetOf< _T > >
	{
		typedef Utils::AssetOf< _T > Type;

		static Types::Int Compare( const Type &a, const Type &b )
		{
			return Utils::compareArrays( a, b );
		}
	};
	
	ALOE_PP_SPECIALIZATION struct ObjectCompareTemplate< Types::Color32 >
	{
		static Types::Int Compare( const Types::Color32 &a, const Types::Color32 &b )
		{
			return 0;
		}
	};
	
	ALOE_PP_SPECIALIZATION struct ObjectCompareTemplate< Types::Recti >
	{
		static Types::Int Compare( const Types::Recti &a, const Types::Recti &b )
		{
			return 0;
		}
	};
	
	ALOE_PP_SPECIALIZATION struct ObjectCompareTemplate< Types::Vector2i >
	{
		static Types::Int Compare( const Types::Vector2i &a, const Types::Vector2i &b )
		{
			return 0;
		}
	};
	
	ALOE_PP_SPECIALIZATION struct ObjectCompareTemplate< Types::Point2i >
	{
		static Types::Int Compare( const Types::Point2i &a, const Types::Point2i &b )
		{
			return 0;
		}
	};



	template< class _T > struct ObjectTemplateWithConvertion
	{
		static Types::Bool SetValue( ObjectRef &self, const ObjectRef &buffer )
		{
			return false;
		}

		static Types::Bool GetValue( const ObjectRef &self, ObjectRef &buffer )
		{
			return false;
		}
	};
	
	template< class _T > struct ObjectTemplateWithConvertion< Utils::SmartPtr< _T > >
	{
		static Types::Bool SetValue( ObjectRef &self, const ObjectRef &buffer )
		{
			Utils::SmartPtr< IProvider > provider;
			if ( buffer.get_Value( make_object_ref( &provider ) ))
			{
				Utils::SmartPtr< _T > *psm = ObjectTemplate< Utils::SmartPtr< _T > >::GetObject( self );
				psm->QueryFrom( provider );
				return true;
			}
			return false;
		}

		static Types::Bool GetValue( const ObjectRef &self, ObjectRef &buffer )
		{
			const Utils::SmartPtr< _T > *psm = ObjectTemplate< Utils::SmartPtr< _T > >::GetObject( self );
			Utils::SmartPtr< IProvider > provider( *psm );
			return buffer.put_Value( make_object_ref( &provider ));
		}
	};

	template< class _T > struct ObjectTemplate
	{
		static Types::LongPointer GetTypeId()
		{
			return Types::LongPointer( (void*)(&GetTypeId) );
		}

		static _T * GetObject( ObjectRef &self )
		{
			return reinterpret_cast< _T *>( self.m_data );
		}

		static const _T * GetObject( const ObjectRef &self )
		{
			return reinterpret_cast< const _T *>( self.m_data );
		}

		static Types::Bool GetValue( const ObjectRef &self, ObjectRef &buffer )
		{
			if ( self.m_typeId == buffer.m_typeId )
			{
				const _T *a = GetObject( self );
				_T *b = GetObject( buffer );
				*b = *a;
				return true;
			}
			else
			{
				return ObjectTemplateWithConvertion< _T >::GetValue( self, buffer );
			}
		}

		static Types::Int Compare( const ObjectRef &self, const ObjectRef &other )
		{
			const _T *a = GetObject( self );
			const _T *b = GetObject( other );
			return ObjectCompareTemplate< _T >::Compare( *a, *b );
		}

		static void Destroy( ObjectRef &self )
		{
			_T *p = GetObject( self );
			delete p;
		}
	};

	namespace Utils {

		template< class _T > ObjectRef make_object_ref( const _T &c )
		{
			ObjectRef ref;
			ref.m_data = reinterpret_cast< Types::RawPointer >( new _T( c ));
			ref.m_typeId = ObjectTemplate< _T >::GetTypeId();
			ref.pfnGetValue = &ObjectTemplate< _T >::GetValue;
			ref.pfnSetValue = &ObjectTemplateWithConvertion< _T >::SetValue;
			ref.pfnCompare  = &ObjectTemplate< _T >::Compare;
			ref.pfnDestroy  = &ObjectTemplate< _T >::Destroy;
			return ref;
		}

		template< class _T > ObjectRef make_object_ref( _T *p )
		{
			ObjectRef ref;
			ref.m_data = reinterpret_cast< Types::RawPointer >( p );
			ref.m_typeId = ObjectTemplate< _T >::GetTypeId();
			ref.pfnGetValue = &ObjectTemplate< _T >::GetValue;
			ref.pfnSetValue = &ObjectTemplateWithConvertion< _T >::SetValue;
			ref.pfnCompare  = &ObjectTemplate< _T >::Compare;
			ref.pfnDestroy  = NULL;
			return ref;
		}

	}; //Utils

	struct AutoObjectRef : ObjectRef
	{
		AutoObjectRef() {}
		template< class _T > AutoObjectRef( const _T &x ) : ObjectRef( Utils::make_object_ref( x )) {}
		template< class _T > AutoObjectRef( _T *x ) : ObjectRef( Utils::make_object_ref( x )) {}
		AutoObjectRef( const ObjectRef &obj ) : ObjectRef( obj ) {}

		template< class _T > operator _T () const
		{
			_T value;
			if ( !get_Value( Utils::make_object_ref( &value ) ))
			{
				throw Errors::Error_Unsupported();
			}
			return value;
		}
		
		template< class _T > Types::Bool get( _T *value ) const
		{
			return get_Value( Utils::make_object_ref( value ) );
		}
		
		AutoObjectRef & operator = ( const AutoObjectRef &other )
		{
			Assign( other );
			return (*this);
		}
	};

	/*! \brief Universal property map
	 *
	 */
	aloe__interface( IPropertyMap )
	{
		aloe__iid__const( IPropertyMap, 0x8 );

		aloe__prop( IPropertyMap, Property
				, map , custom( AutoObjectRef )
				, get , put , custom( AutoObjectRef )
				, ____, ____, ____
				, ____, ____, ____
				, ____, ____, ____ );
	};


};//Aloe

#endif//ALOE_INCLUDED_ALOE_OBJECT_REF_H
