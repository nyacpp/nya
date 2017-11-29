#include <catch.hpp>
#include <nya/enum.hpp>


#define MyEnumDef(K, V)                 \
	K(One)                              \
	V(Two, 20)                          \
	K(Three)                            \
	V(Four, 40)
nya_enum(MyEnum, MyEnumDef)

#define MyEnumDef2(K, V)                \
	K(One)                              \
	V(Two, 20)                          \
	K(Three)                            \
	V(Four, 40)
nya_enum(MyEnum2, MyEnumDef2)



TEST_CASE( "nya enum", "[nya]" )
{
	// usual init
	MyEnum e1 = MyEnum::One;
	CHECK( e1 == 0 );
	CHECK( strcmp(e1.c_str(), "One") == 0 );

	// init from string
	MyEnum e2 = "Two";
	CHECK( e2 == 20 );
	
	// default value == -1
	MyEnum e3;
	CHECK( e3 == -1 );
	
	// wrong string
	e3 = "Unexpected";
	CHECK( e3 == -1 );
	
	// reassign
	e3 = "Three";
	CHECK( e3 == 21 );
	
	// Second enum
	MyEnum2 ee4 = "Four";
	CHECK( ee4 == 40 );
}