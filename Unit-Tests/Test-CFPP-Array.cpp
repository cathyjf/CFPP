/*******************************************************************************
 * Copyright (c) 2014, Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        Test-CFPP-Array.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Array
 */

#include <CF++.hpp>
#include <GoogleMock/GoogleMock.h>

using namespace testing;

TEST( CFPP_Array, CTOR )
{
    CF::Array a;
    
    ASSERT_TRUE( a.IsValid() );
    ASSERT_EQ( a.GetCount(), 0 );
}

TEST( CFPP_Array, CTOR_AutoPointer )
{
    CF::Array a1( CF::AutoPointer( CFArrayCreateMutable( NULL, 10, NULL ) ) );
    CF::Array a2( CF::AutoPointer( CFUUIDCreate( NULL ) ) );
    CF::Array a3( CF::AutoPointer( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, CTOR_CFType )
{
    CF::Array d1( static_cast< CFTypeRef >( CF::Array().GetCFObject() ) );
    CF::Array d2( static_cast< CFTypeRef >( NULL ) );
    CF::Array d3( static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Array, CTOR_CFArray )
{
    CF::Array d1( static_cast< CFArrayRef >( CF::Array().GetCFObject() ) );
    CF::Array d2( static_cast< CFArrayRef >( NULL ) );
    CF::Array d3( static_cast< CFArrayRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Array, CCTOR )
{
    CF::Array a1;
    
    a1 << "hello";
    a1 << "world";
    
    ASSERT_TRUE( a1.IsValid() );
    ASSERT_EQ( a1.GetCount(), 2 );
    
    {
        CF::Array a2( a1 );
        
        ASSERT_TRUE( a1.IsValid() );
        ASSERT_TRUE( a2.IsValid() );
        ASSERT_EQ( a1.GetCount(), 2 );
        ASSERT_EQ( a2.GetCount(), 2 );
    }
}

#ifdef CFPP_HAS_CPP11
TEST( CFPP_Array, MCTOR )
{
    CF::Array a1;
    
    a1 << "hello";
    a1 << "world";
    
    ASSERT_TRUE( a1.IsValid() );
    ASSERT_EQ( a1.GetCount(), 2 );
    
    {
        CF::Array a2( std::move( a1 ) );
        
        ASSERT_FALSE( a1.IsValid() );
        ASSERT_TRUE(  a2.IsValid() );
        ASSERT_EQ( a2.GetCount(), 2 );
    }
}
#endif

TEST( CFPP_Array, OperatorAssignArray )
{
    CF::Data a1;
    CF::Data a2( static_cast< CFArrayRef >( NULL ) );
    CF::Data a3( static_cast< CFArrayRef >( NULL ) );
    CF::Data a4;
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    ASSERT_TRUE(  a4.IsValid() );
    
    a3 = a1;
    a4 = a2;
    
    ASSERT_TRUE(  a3.IsValid() );
    ASSERT_FALSE( a4.IsValid() );
}

TEST( CFPP_Array, OperatorAssignAutoPointer )
{
    CF::Array a1( static_cast< CFTypeRef >( NULL ) );
    CF::Array a2;
    CF::Array a3;
    
    ASSERT_FALSE( a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_TRUE(  a3.IsValid() );
    
    a1 = CF::AutoPointer( CFArrayCreateMutable( NULL, 0, NULL ) );
    a2 = CF::AutoPointer( CFUUIDCreate( NULL ) );
    a3 = CF::AutoPointer( NULL );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, OperatorAssignCFType )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    CF::Array a3( static_cast< CFArrayRef >( NULL ) );
    CF::Array a4;
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    ASSERT_TRUE(  a4.IsValid() );
    
    a3 = static_cast< CFTypeRef >( a1 );
    a4 = static_cast< CFTypeRef >( a2 );
    
    ASSERT_TRUE(  a3.IsValid() );
    ASSERT_FALSE( a4.IsValid() );
}

TEST( CFPP_Array, OperatorAssignCFArray )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    CF::Array a3( static_cast< CFArrayRef >( NULL ) );
    CF::Array a4;
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    ASSERT_TRUE(  a4.IsValid() );
    
    a3 = static_cast< CFArrayRef >( a1 );
    a4 = static_cast< CFArrayRef >( a2 );
    
    ASSERT_TRUE(  a3.IsValid() );
    ASSERT_FALSE( a4.IsValid() );
}

TEST( CFPP_Array, OperatorPlusEqualArray )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += a2;
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += a1;
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1 += a3;
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a3 += a1;
    
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, OperatorPlusEqualCFType )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += static_cast< CFTypeRef >( a2.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += static_cast< CFTypeRef >( a1.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1 += static_cast< CFTypeRef >( a3.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a3 += static_cast< CFTypeRef >( a1.GetCFObject() );
    
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, OperatorPlusEqualCFArray )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += static_cast< CFArrayRef >( a2.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 += static_cast< CFArrayRef >( a1.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1 += static_cast< CFArrayRef >( a3.GetCFObject() );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a3 += static_cast< CFArrayRef >( a1.GetCFObject() );
    
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, OperatorLeftShiftCFType )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << static_cast< CFTypeRef >( CF::String( "hello, world" ).GetCFObject() );
    a2 << static_cast< CFTypeRef >( CF::String( "hello, world" ).GetCFObject() );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, OperatorLeftShiftCChar )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << "hello, world";
    a2 << "hello, world";
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, OperatorLeftShiftString )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << CF::String( "hello, world" );
    a2 << CF::String( "hello, world" );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, OperatorLeftShiftNumber )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << CF::Number( 42 );
    a2 << CF::Number( 42 );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, OperatorSubscript )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_TRUE(  a2.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a2[ 0 ] );
    ASSERT_NO_FATAL_FAILURE( a3[ 0 ] );
    ASSERT_NO_THROW( a2[ 0 ] );
    ASSERT_NO_THROW( a3[ 0 ] );
    
    ASSERT_TRUE( a1[ 0 ] != NULL );
    ASSERT_TRUE( a1[ 1 ] == NULL );
    ASSERT_TRUE( a2[ 0 ] == NULL );
    ASSERT_TRUE( a3[ 0 ] == NULL );
    
    ASSERT_EQ( CFGetTypeID( a1[ 0 ] ), CFStringGetTypeID() );
}

TEST( CFPP_Array, GetTypeID )
{
    CF::Array a;
    
    ASSERT_EQ( a.GetTypeID(), CFArrayGetTypeID() );
}

TEST( CFPP_Array, GetCFObject )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE( a1.GetCFObject() != NULL );
    ASSERT_TRUE( a2.GetCFObject() == NULL );
    ASSERT_EQ( CFGetTypeID( a1.GetCFObject() ), CFArrayGetTypeID() );
}

TEST( CFPP_Array, GetCount )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    ASSERT_TRUE( a1.GetCount() == 0 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1 << CF::String( "hello, world" );
    a2 << CF::String( "hello, world" );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1.RemoveAllValues();
    a2.RemoveAllValues();
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    ASSERT_TRUE( a1.GetCount() == 0 );
    ASSERT_TRUE( a2.GetCount() == 0 );
}

TEST( CFPP_Array, ContainsValue )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    a1 << CF::String( "hello, world" );
    a1 << CF::Number( 42 );
    
    ASSERT_TRUE(  a1.ContainsValue( CF::String( "hello, world" ) ) );
    ASSERT_TRUE(  a1.ContainsValue( CF::Number( 42 ) ) );
    ASSERT_FALSE( a2.ContainsValue( CF::String( "hello, world" ) ) );
    ASSERT_FALSE( a2.ContainsValue( CF::Number( 42 ) ) );
    ASSERT_FALSE( a1.ContainsValue( CF::String( "hello, universe" ) ) );
    ASSERT_FALSE( a1.ContainsValue( CF::Number( 43 ) ) );
}

TEST( CFPP_Array, RemoveAllValues )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    
    a1 << CF::String( "hello, world" );
    a1 << CF::Number( 42 );
    a1 << CF::String( "hello, universe" );
    
    a2 << CF::String( "hello, world" );
    a2 << CF::Number( 42 );
    a2 << CF::String( "hello, universe" );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 3 );
    
    a1.RemoveAllValues();
    a2.RemoveAllValues();
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1.RemoveAllValues();
    a2.RemoveAllValues();
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
}

TEST( CFPP_Array, GetValueAtIndex )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_TRUE(  a2.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a2.GetValueAtIndex( 0 ) );
    ASSERT_NO_FATAL_FAILURE( a3.GetValueAtIndex( 0 ) );
    ASSERT_NO_THROW( a2.GetValueAtIndex( 0 ) );
    ASSERT_NO_THROW( a3.GetValueAtIndex( 0 ) );
    
    ASSERT_TRUE( a1.GetValueAtIndex( 0 ) != NULL );
    ASSERT_TRUE( a1.GetValueAtIndex( 1 ) == NULL );
    ASSERT_TRUE( a2.GetValueAtIndex( 0 ) == NULL );
    ASSERT_TRUE( a3.GetValueAtIndex( 0 ) == NULL );
    
    ASSERT_EQ( CFGetTypeID( a1.GetValueAtIndex( 0 ) ), CFStringGetTypeID() );
}

TEST( CFPP_Array, SetValueAtIndex )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a1.SetValueAtIndex( CF::String( "hello, world" ), 1 ) );
    ASSERT_NO_FATAL_FAILURE( a2.SetValueAtIndex( CF::String( "hello, world" ), 0 ) );
    ASSERT_NO_THROW( a1.SetValueAtIndex( CF::String( "hello, world" ), 1 ) );
    ASSERT_NO_THROW( a2.SetValueAtIndex( CF::String( "hello, world" ), 0 ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1.SetValueAtIndex( CF::String( "hello, world" ), 0 );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    
    a1.SetValueAtIndex( CF::String( "hello, universe" ), 0 );
    a1.SetValueAtIndex( CF::String( "hello, world" ), 1 );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, universe" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, world" );
}

TEST( CFPP_Array, InsertValueAtIndex )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a1.InsertValueAtIndex( CF::String( "hello, world" ), 1 ) );
    ASSERT_NO_FATAL_FAILURE( a2.InsertValueAtIndex( CF::String( "hello, world" ), 0 ) );
    ASSERT_NO_THROW( a1.InsertValueAtIndex( CF::String( "hello, world" ), 1 ) );
    ASSERT_NO_THROW( a2.InsertValueAtIndex( CF::String( "hello, world" ), 0 ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1.InsertValueAtIndex( CF::String( "hello, world" ), 0 );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    
    a1.InsertValueAtIndex( CF::String( "hello, universe" ), 0 );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, universe" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, world" );
}

TEST( CFPP_Array, AppendValue )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1.AppendValue( static_cast< CFTypeRef >( CF::String( "hello, world" ).GetCFObject() ) );
    a2.AppendValue( static_cast< CFTypeRef >( CF::String( "hello, world" ).GetCFObject() ) );
    
    ASSERT_TRUE(  a1.GetCount() == 1 );
    ASSERT_FALSE( a2.IsValid() );
}

TEST( CFPP_Array, RemoveValueAtIndex )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << "hello, world";
    a1 << "hello, universe";
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    ASSERT_NO_FATAL_FAILURE( a1.RemoveValueAtIndex( 42 ) );
    ASSERT_NO_FATAL_FAILURE( a2.RemoveValueAtIndex( 0 ) );
    ASSERT_NO_THROW( a1.RemoveValueAtIndex( 42 ) );
    ASSERT_NO_THROW( a2.RemoveValueAtIndex( 0 ) );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1.RemoveValueAtIndex( 1 );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    
    a1.RemoveValueAtIndex( 0 );
    
    ASSERT_TRUE( a1.GetCount() == 0 );
    
    ASSERT_NO_FATAL_FAILURE( a1.RemoveValueAtIndex( 0 ) );
    ASSERT_NO_THROW( a1.RemoveValueAtIndex( 0 ) );
    
    ASSERT_TRUE( a1.GetCount() == 0 );
}

TEST( CFPP_Array, AppendArray )
{
    CF::Array a1;
    CF::Array a2;
    CF::Array a3( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_TRUE(  a2.IsValid() );
    ASSERT_FALSE( a3.IsValid() );
    
    a1 << CF::String( "hello, world" );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1.AppendArray( a2 );
    
    ASSERT_TRUE( a1.GetCount() == 1 );
    ASSERT_TRUE( a2.GetCount() == 0 );
    
    a1.AppendArray( a1 );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a1.AppendArray( a3 );
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    a3.AppendArray( a1 );
    
    ASSERT_FALSE( a3.IsValid() );
}

TEST( CFPP_Array, ExchangeValuesAtIndices )
{
    CF::Array a1;
    CF::Array a2( static_cast< CFArrayRef >( NULL ) );
    
    ASSERT_TRUE(  a1.IsValid() );
    ASSERT_FALSE( a2.IsValid() );
    ASSERT_TRUE(  a1.GetCount() == 0 );
    
    a1 << "hello, world";
    a1 << "hello, universe";
    
    ASSERT_TRUE( a1.GetCount() == 2 );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, world" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, universe" );
    
    a1.ExchangeValuesAtIndices( 0, 1 );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, universe" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, world" );
    
    ASSERT_NO_FATAL_FAILURE( a1.ExchangeValuesAtIndices( 42, 43 ) );
    ASSERT_NO_FATAL_FAILURE( a1.ExchangeValuesAtIndices(  0,  2 ) );
    ASSERT_NO_FATAL_FAILURE( a2.ExchangeValuesAtIndices(  0,  1 ) );
    ASSERT_NO_THROW( a1.ExchangeValuesAtIndices( 42, 43 ) );
    ASSERT_NO_THROW( a1.ExchangeValuesAtIndices(  0,  2 ) );
    ASSERT_NO_THROW( a2.ExchangeValuesAtIndices(  0,  1 ) );
    
    ASSERT_TRUE( CF::String( a1[ 0 ] ) == "hello, universe" );
    ASSERT_TRUE( CF::String( a1[ 1 ] ) == "hello, world" );
}

TEST( CFPP_Array, Swap )
{
    CF::Array a1;
    CF::Array a2;
    
    a1 << "hello";
    a1 << "world";
    
    ASSERT_EQ( a1.GetCount(), 2 );
    ASSERT_EQ( a2.GetCount(), 0 );
    
    swap( a1, a2 );
    
    ASSERT_EQ( a1.GetCount(), 0 );
    ASSERT_EQ( a2.GetCount(), 2 );
}
