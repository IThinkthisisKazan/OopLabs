#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../HTTP_URL/HTTP_URL/CHttpUrl.h"

TEST_CASE("constructor check receiving string url")
{
	WHEN("Correct url without port should set default port")
	{
		CHttpUrl url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");

		CHECK(Protocol::HTTP == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(80 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("Correct url with port")
	{
		CHttpUrl url("https://www.mysite.com:325/docs/document1.html?page=30&lang=en#title");

		CHECK(Protocol::HTTPS == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(325 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("url with incorrect protocol")
	{
		CHECK_THROWS(CHttpUrl("h://www.mysite.com:325/docs/document1.html?page=30&lang=en#title"));
	}

	WHEN("url with no domain")
	{
		CHECK_THROWS(CHttpUrl("http://"));
	}

	WHEN("url with incorrect port")
	{
		CHECK_THROWS(CHttpUrl("http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title"));
		CHECK_THROWS(CHttpUrl("http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title"));
	}
}

TEST_CASE("constructor accepts protocol, domain, document")
{
	WHEN("Correct data with defualt protocol")
	{
		CHttpUrl url("www.mysite.com", "/docs/document1.html?page=30&lang=en#title");

		CHECK(Protocol::HTTP == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(80 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("Correct data with protocol")
	{
		CHttpUrl url("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTPS);
		CHECK(Protocol::HTTPS == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(443 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("Correct data with empty document")
	{
		CHttpUrl url("www.mysite.com", "", Protocol::HTTPS);
		CHECK(Protocol::HTTPS == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(443 == url.GetPort());
		CHECK("/" == url.GetDocument());
	}

	WHEN("Incorrect domain")
	{
		CHECK_THROWS(CHttpUrl("www.mys/ite.com", "/docs/document1.html?page=30&lang=en#title"));
	}

	WHEN("Domain is empty")
	{
		CHECK_THROWS(CHttpUrl("", "doc.doc"));
	}
}

TEST_CASE("constructor accepts protocol, domain, document and port")
{
	WHEN("Correct data")
	{
		CHttpUrl url("www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 325);

		CHECK(Protocol::HTTP == url.GetProtocol());
		CHECK("www.mysite.com" == url.GetDomain());
		CHECK(325 == url.GetPort());
		CHECK("/docs/document1.html?page=30&lang=en#title" == url.GetDocument());
	}

	WHEN("Incorrect port value")
	{
		CHECK_THROWS(CHttpUrl("www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, (unsigned short)65536));
	}
}

TEST_CASE("GetUrl tests")
{
	WHEN("url with default port")
	{
		std::string urlLine = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		CHttpUrl url(urlLine);
		CHECK(urlLine == url.GetURL());
	}

	WHEN("url with port")
	{
		std::string urlLine = "http://www.mysite.com:325/docs/document1.html?page=30&lang=en#title";
		CHttpUrl url(urlLine);
		CHECK(urlLine == url.GetURL());
	}

	WHEN("url with default port specified")
	{
		CHttpUrl url("http://www.mysite.com:80/docs/document1.html?page=30&lang=en#title");
		CHECK("http://www.mysite.com/docs/document1.html?page=30&lang=en#title" == url.GetURL());
	}
}