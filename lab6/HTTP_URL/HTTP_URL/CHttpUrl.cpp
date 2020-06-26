#include "CHttpUrl.h"
#include <regex>
#include "URLParsingError.h"

CHttpUrl::CHttpUrl(const std::string& url)
{
    try
    {
        ParseURL(url);
    }
    catch (std::invalid_argument& error)
    {
        throw CUrlParsingError(error.what());
    }
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
    : CHttpUrl(GetDomain(domain), document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
    if (domain.empty())
    {
        throw std::invalid_argument("Domain not found!");
    }
    if (port < 1 || port > 65535)
    {
        throw std::invalid_argument("Port must be in range [1..65535]");
    }
    m_domain = GetDomain(domain);
    m_document = GetDocumentByUrl(document);
    m_protocol = protocol;
    m_port = port;
}

std::string CHttpUrl::GetURL() const
{
    if (m_port != GetDefaultPort(m_protocol))
    {
        return GetProtocolToString(m_protocol) + "://" + m_domain + ":" + std::to_string(m_port) + m_document;
    }
    return GetProtocolToString(m_protocol) + "://" + m_domain + m_document;
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    return m_document;
}
Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

void CHttpUrl::ParseURL(const std::string& url)
{
    std::smatch result;
    std::regex regularExpression("^([[:alpha:]]+)://([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))?$");
    if (!regex_search(url, result, regularExpression))
    {
        throw std::invalid_argument("Incorrect url. protocol://domain[:port][/document]");
    }
    Protocol protocol = GetProtocol(result[1]);
    unsigned short port = GetPort(result[4], protocol);
    m_protocol = protocol;
    m_domain = GetDomain(result[2]);
    m_port = port;
    m_document = "/" + std::string(result[6]);
}

Protocol CHttpUrl::GetProtocol(const std::string& protocol)
{
    if (protocol == "https")
    {
        return Protocol::HTTPS;
    }
    else if (protocol == "http")
    {
        return Protocol::HTTP;
    }
    throw std::invalid_argument("Incorrect protocol name");
}

unsigned short CHttpUrl::GetPort(const std::string& port, const Protocol& protocol)
{
    if (port.empty())
    {
        return GetDefaultPort(protocol);
    }
    int resPort = atoi(port.c_str());
    if (resPort >= 1 && resPort <= 65535)
    {
        return resPort;
    }
    throw std::invalid_argument("Port doesnt exist! Port [1..65535]");
}

unsigned short CHttpUrl::GetDefaultPort(const Protocol& protocol)
{
    auto it = DEFAULT_PORT.find(protocol);
    if (it != DEFAULT_PORT.end())
    {
        return it->second;
    }
    throw std::runtime_error("Port doesnt exist for this protocol");
}

std::string CHttpUrl::GetDomain(const std::string& domain)
{
    if (std::all_of(domain.begin(), domain.end(), [](char symbol) {return symbol != '/'; }))
    {
        return domain;
    }
    throw std::invalid_argument("Domain cannot contain / in it");
}

std::string CHttpUrl::GetDocumentByUrl(const std::string& document)
{
    if (document.empty() || document[0] != '/')
    {
        return '/' + document;
    }
    return document;
}

std::string CHttpUrl::GetProtocolToString(const Protocol& protocol)
{
    if (protocol == Protocol::HTTPS)
    {
        return "https";
    }
    return "http";
}