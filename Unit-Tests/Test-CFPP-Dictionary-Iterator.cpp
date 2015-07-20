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
 * @file        Test-CFPP-Dictionary-Iterator.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Dictionary::Iterator
 */

#include <CF++.hpp>
#include <GoogleMock/GoogleMock.h>

using namespace testing;

TEST( CFPP_Dictionary_Iterator, DictionaryBegin )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d3;
    
    d3 << CF::Pair( "foo", "hello, world" );
    
    CF::Dictionary::Iterator i;
    
    i = d3.begin();
    
    CFShow( i.GetKey() );
    CFShow( i.GetValue() );
    
    ASSERT_TRUE( d1.begin().GetKey()   == NULL );
    ASSERT_TRUE( d1.begin().GetValue() == NULL );
    ASSERT_TRUE( d2.begin().GetKey()   == NULL );
    ASSERT_TRUE( d2.begin().GetValue() == NULL );
    ASSERT_TRUE( d3.begin().GetKey()   != NULL );
    ASSERT_TRUE( d3.begin().GetValue() != NULL );
    
    ASSERT_TRUE( CF::String( d3.begin().GetKey() )   == "foo" );
    ASSERT_TRUE( CF::String( d3.begin().GetValue() ) == "hello, world" );
    
    ASSERT_TRUE( d1.begin() == d1.end() );
    ASSERT_TRUE( d2.begin() == d2.end() );
    ASSERT_TRUE( d3.begin() != d3.end() );
}

TEST( CFPP_Dictionary_Iterator, DictionaryEnd )
{
    CF::Dictionary d1;
    CF::Dictionary d2( static_cast< CFDictionaryRef >( NULL ) );
    CF::Dictionary d3;
    
    d3 << CF::Pair( "foo", "hello, world" );
    
    ASSERT_TRUE( d1.end().GetKey()   == NULL );
    ASSERT_TRUE( d1.end().GetValue() == NULL );
    ASSERT_TRUE( d2.end().GetKey()   == NULL );
    ASSERT_TRUE( d2.end().GetValue() == NULL );
    ASSERT_TRUE( d3.end().GetKey()   == NULL );
    ASSERT_TRUE( d3.end().GetValue() == NULL );
    
    ASSERT_TRUE( CF::String( d3.begin().GetKey() )   == "foo" );
    ASSERT_TRUE( CF::String( d3.begin().GetValue() ) == "hello, world" );
    
    ASSERT_TRUE( d1.begin() == d1.end() );
    ASSERT_TRUE( d2.begin() == d2.end() );
    ASSERT_TRUE( d3.begin() != d3.end() );
}

TEST( CFPP_Dictionary_Iterator, CTOR )
{
    CF::Dictionary::Iterator i;
    
    ASSERT_TRUE( i.GetKey()   == NULL );
    ASSERT_TRUE( i.GetValue() == NULL );
}

TEST( CFPP_Dictionary_Iterator, CCTOR )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2( i1 );
        CF::Dictionary::Iterator i3( d.begin() );
        CF::Dictionary::Iterator i4( i3 );
        
        ASSERT_TRUE( i1.GetKey()   == NULL );
        ASSERT_TRUE( i1.GetValue() == NULL );
        ASSERT_TRUE( i2.GetKey()   == NULL );
        ASSERT_TRUE( i2.GetValue() == NULL );
        ASSERT_TRUE( i3.GetKey()   != NULL );
        ASSERT_TRUE( i3.GetValue() != NULL );
        ASSERT_TRUE( i4.GetKey()   != NULL );
        ASSERT_TRUE( i4.GetValue() != NULL );
        
        ASSERT_TRUE( CF::String( i3.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i3.GetValue() ) == "hello, world" );
        ASSERT_TRUE( CF::String( i4.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i4.GetValue() ) == "hello, world" );
    }
}

#ifdef CFPP_HAS_CPP11
TEST( CFPP_Dictionary_Iterator, MCTOR )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2( std::move( i1 ) );
        CF::Dictionary::Iterator i3( d.begin() );
        CF::Dictionary::Iterator i4( std::move( i3 ) );
        
        ASSERT_TRUE( i1.GetKey()   == NULL );
        ASSERT_TRUE( i1.GetValue() == NULL );
        ASSERT_TRUE( i2.GetKey()   == NULL );
        ASSERT_TRUE( i2.GetValue() == NULL );
        ASSERT_TRUE( i3.GetKey()   == NULL );
        ASSERT_TRUE( i3.GetValue() == NULL );
        ASSERT_TRUE( i4.GetKey()   != NULL );
        ASSERT_TRUE( i4.GetValue() != NULL );
        
        ASSERT_TRUE( CF::String( i4.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i4.GetValue() ) == "hello, world" );
    }
}
#endif

TEST( CFPP_Dictionary_Iterator, OperatorAssign )
{
    CF::Dictionary d;
    
    d << CF::Pair( "foo", "hello, world" );
    
    {
        CF::Dictionary::Iterator i1;
        CF::Dictionary::Iterator i2;
        CF::Dictionary::Iterator i3( d.begin() );
        CF::Dictionary::Iterator i4;
        
        ASSERT_TRUE( i1.GetKey()   == NULL );
        ASSERT_TRUE( i1.GetValue() == NULL );
        ASSERT_TRUE( i3.GetKey()   != NULL );
        ASSERT_TRUE( i3.GetValue() != NULL );
        
        ASSERT_TRUE( CF::String( i3.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i3.GetValue() ) == "hello, world" );
        
        i2 = i1;
        i4 = i3;
        
        ASSERT_TRUE( i2.GetKey()   == NULL );
        ASSERT_TRUE( i2.GetValue() == NULL );
        ASSERT_TRUE( i4.GetKey()   != NULL );
        ASSERT_TRUE( i4.GetValue() != NULL );
        
        ASSERT_TRUE( CF::String( i4.GetKey() )   == "foo" );
        ASSERT_TRUE( CF::String( i4.GetValue() ) == "hello, world" );
    }
}

TEST( CFPP_Dictionary_Iterator, OperatorPrefixIncrement )
{}

TEST( CFPP_Dictionary_Iterator, OperatorPostfixIncrement )
{}

TEST( CFPP_Dictionary_Iterator, OperatorPrefixDecrement )
{}

TEST( CFPP_Dictionary_Iterator, OperatorPostfixDecrement )
{}

TEST( CFPP_Dictionary_Iterator, OperatorPlusEqual )
{}

TEST( CFPP_Dictionary_Iterator, OperatorMinusEqual )
{}

TEST( CFPP_Dictionary_Iterator, OperatorPlus )
{}

TEST( CFPP_Dictionary_Iterator, OperatorMinus )
{}

TEST( CFPP_Dictionary_Iterator, OperatorEqual )
{}

TEST( CFPP_Dictionary_Iterator, OperatorNotEqual )
{}

TEST( CFPP_Dictionary_Iterator, OperatorDereference )
{}

TEST( CFPP_Dictionary_Iterator, OperatorMemberAccess )
{}

TEST( CFPP_Dictionary_Iterator, OperatorCastToCFType )
{}

TEST( CFPP_Dictionary_Iterator, GetTypeID )
{}

TEST( CFPP_Dictionary_Iterator, GetCFObject )
{}

TEST( CFPP_Dictionary_Iterator, GetKey )
{}

TEST( CFPP_Dictionary_Iterator, GetValue )
{}

TEST( CFPP_Dictionary_Iterator, Swap )
{}
