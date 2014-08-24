#pragma once

#include "xmlparser.h"
#include "spriteInfo.h"
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <string>
#include <stdexcept>
#include <map>

using namespace xercesc;
using namespace std;


class tileMapParser : public GetConfig
{
public:
	void readSpriteConfigFile(std::string&) throw(std::runtime_error);
	map<string,spriteInfo*> getSpriteMap() { return spriteMap; }
private:
	map<string,spriteInfo*> spriteMap;
};