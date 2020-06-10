#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../TVSet/TVSet/CTVSet.h"

TEST_CASE("The first time tv is turned on it should be on 1st channel")
{
	CTVSet tv;
	tv.TurnOn();
	REQUIRE(tv.GetChannel() == 1);
}

TEST_CASE("channel in turned off tv should be 0")
{
	CTVSet tv;
	tv.TurnOff();
	REQUIRE(tv.GetChannel() == 0);
}

TEST_CASE("select channel")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SelectChannel(5);
	REQUIRE(tv.GetChannel() == 5);
}

TEST_CASE("tv turn on at previous channel")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SelectChannel(5);
	tv.TurnOff();
	tv.TurnOn();
	REQUIRE(tv.GetChannel() == 5);
}

TEST_CASE("select chanel on turned off tv")
{
	CTVSet tv;
	tv.TurnOff();
	tv.SelectChannel(5);
	REQUIRE(tv.GetChannel() == 0);
}

TEST_CASE("select channel that is out of range")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SelectChannel(5);
	tv.SelectChannel(100);
	REQUIRE(tv.GetChannel() == 5);
	tv.SelectChannel(0);
	REQUIRE(tv.GetChannel() == 5);
}

TEST_CASE("select channel that is within range")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SelectChannel(5);
	tv.SelectChannel(99);
	REQUIRE(tv.GetChannel() == 99);
	tv.SelectChannel(5);
	tv.SelectChannel(1);
	REQUIRE(tv.GetChannel() == 1);
}

TEST_CASE("Select previous channel should cycle between 2  last channels")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SelectChannel(5);
	tv.SelectChannel(6);
	tv.SelectChannel(9);
	tv.SelectPreviousChannel();
	int firstChannel = tv.GetChannel();
	tv.SelectPreviousChannel();
	int secondChannel = tv.GetChannel();
	REQUIRE(firstChannel == 6);
	REQUIRE(secondChannel == 9);
}