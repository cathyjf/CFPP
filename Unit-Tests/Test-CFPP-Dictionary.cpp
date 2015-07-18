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
 * @file        Test-CFPP-Dictionary.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Dictionary
 */

#include <CF++.hpp>
#include <GoogleMock/GoogleMock.h>

using namespace testing;

TEST( CFPP_Dictionary, CTOR )
{
    CF::Dictionary d;
    
    ASSERT_TRUE( d.IsValid() );
    ASSERT_EQ( d.GetCount(), 0 );
}

TEST( CFPP_Dictionary, CTOR_AutoPointer )
{
    CF::Dictionary d1( CF::AutoPointer( CFDictionaryCreateMutable( NULL, 10, NULL, NULL ) ) );
    CF::Dictionary d2( CF::AutoPointer( CFUUIDCreate( NULL ) ) );
    CF::Dictionary d3( CF::AutoPointer( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Dictionary, CTOR_CFType )
{
    CF::Dictionary d1( static_cast< CFTypeRef >( CF::Dictionary().GetCFObject() ) );
    CF::Dictionary d2( static_cast< CFTypeRef >( NULL ) );
    CF::Dictionary d3( static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Dictionary, CTOR_CFDictionary )
{
    CF::Dictionary d1( static_cast< CFDictionaryRef >( CF::Dictionary().GetCFObject() ) );
    CF::Dictionary d2( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d3( static_cast< CFDictionaryRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Dictionary, CCTOR )
{
    CF::Dictionary d1;
    
    d1 << CF::Pair( "foo", "bar" );
    d1 << CF::Pair( "bar", "foo" );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_EQ( d1.GetCount(), 2 );
    
    {
        CF::Dictionary d2( d1 );
        
        ASSERT_TRUE( d1.IsValid() );
        ASSERT_TRUE( d2.IsValid() );
        ASSERT_EQ( d1.GetCount(), 2 );
        ASSERT_EQ( d2.GetCount(), 2 );
    }
}

#ifdef CFPP_HAS_CPP11
TEST( CFPP_Dictionary, MCTOR )
{
    CF::Dictionary d1;
    
    d1 << CF::Pair( "foo", "bar" );
    d1 << CF::Pair( "bar", "foo" );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_EQ( d1.GetCount(), 2 );
    
    {
        CF::Dictionary d2( std::move( d1 ) );
        
        ASSERT_FALSE( d1.IsValid() );
        ASSERT_TRUE(  d2.IsValid() );
        ASSERT_EQ( d2.GetCount(), 2 );
    }
}
#endif

TEST( CFPP_Dictionary, OperatorAssignDictionary )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d3( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d4;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    ASSERT_TRUE(  d4.IsValid() );
    
    d3 = d1;
    d4 = d2;
    
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
}

TEST( CFPP_Dictionary, OperatorAssignAutoPointer )
{
    CF::Dictionary d1( static_cast< CFTypeRef >( NULL ) );
    CF::Dictionary d2;
    CF::Dictionary d3;
    
    ASSERT_FALSE( d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    
    d1 = CF::AutoPointer( CFDictionaryCreateMutable( NULL, 0, NULL, NULL ) );
    d2 = CF::AutoPointer( CFUUIDCreate( NULL ) );
    d3 = CF::AutoPointer( NULL );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Dictionary, OperatorAssignCFType )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d3( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d4;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    ASSERT_TRUE(  d4.IsValid() );
    
    d3 = static_cast< CFTypeRef >( d1 );
    d4 = static_cast< CFTypeRef >( d2 );
    
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
}

TEST( CFPP_Dictionary, OperatorAssignCFDictionary )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d3( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d4;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    ASSERT_TRUE(  d4.IsValid() );
    
    d3 = static_cast< CFDictionaryRef >( d1 );
    d4 = static_cast< CFDictionaryRef >( d2 );
    
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
}

TEST( CFPP_Dictionary, OperatorPlusEqual )
{}

TEST( CFPP_Dictionary, OperatorLeftShiftEqual )
{}

TEST( CFPP_Dictionary, OperatorSubscriptCFType )
{}

TEST( CFPP_Dictionary, OperatorSubscriptCChar )
{}

TEST( CFPP_Dictionary, OperatorSubscriptString )
{}

TEST( CFPP_Dictionary, GetTypeID )
{
    CF::Dictionary d;
    
    ASSERT_EQ( d.GetTypeID(), CFDictionaryGetTypeID() );
}

TEST( CFPP_Dictionary, GetCFObject )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFDictionaryRef >( NULL ) );
    
    ASSERT_TRUE( d1.GetCFObject() != NULL );
    ASSERT_TRUE( d2.GetCFObject() == NULL );
    ASSERT_EQ( CFGetTypeID( d1.GetCFObject() ), CFDictionaryGetTypeID() );
}

TEST( CFPP_Dictionary, ContainsKey )
{}

TEST( CFPP_Dictionary, ContainsValue )
{}

TEST( CFPP_Dictionary, RemoveAllValues )
{}

TEST( CFPP_Dictionary, GetCount )
{}

TEST( CFPP_Dictionary, GetValue )
{}

TEST( CFPP_Dictionary, AddValue )
{}

TEST( CFPP_Dictionary, RemoveValue )
{}

TEST( CFPP_Dictionary, ReplaceValue )
{}

TEST( CFPP_Dictionary, SetValue )
{}

TEST( CFPP_Dictionary, Swap )
{
    CF::Dictionary d1;
    CF::Dictionary d2;
    
    d1 << CF::Pair( "hello", "world" );
    d1 << CF::Pair( "foo",   "bar" );
    
    ASSERT_EQ( d1.GetCount(), 2 );
    ASSERT_EQ( d2.GetCount(), 0 );
    
    swap( d1, d2 );
    
    ASSERT_EQ( d1.GetCount(), 0 );
    ASSERT_EQ( d2.GetCount(), 2 );
}
