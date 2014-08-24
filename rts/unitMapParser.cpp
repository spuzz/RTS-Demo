
#include "unitMapParser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <iterator>

using namespace std;


map<string,map<string,string>> unitMapParser::readConfigFile(string& configFile)
	throw( std::runtime_error )
{
	// Test to see if the file is ok.
	
	struct stat fileStatus;

	//TAG_ApplicationSettings = XMLString::transcode(type.c_str());

	// contains xml values for unit

    typedef map<string,string> StringMap;
	StringMap* unitValues;
	string name;
	map<string,StringMap> spriteMap;
	int iretStat = stat(configFile.c_str(), &fileStatus);
	if( iretStat == ENOENT )
		throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
	else if( iretStat == ENOTDIR )
		throw ( std::runtime_error("A component of the path is not a directory."));
	else if( iretStat == ELOOP )
		throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
	else if( iretStat == EACCES )
		throw ( std::runtime_error("Permission denied."));
	else if( iretStat == ENAMETOOLONG )
		throw ( std::runtime_error("File can not be read\n"));

	// Configure DOM parser.

	m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Never );
	m_ConfigFileParser->setDoNamespaces( false );
	m_ConfigFileParser->setDoSchema( false );
	m_ConfigFileParser->setLoadExternalDTD( false );

	try
	{
		m_ConfigFileParser->parse( configFile.c_str() );

		// no need to free this pointer - owned by the parent parser object
		DOMDocument* xmlDoc = m_ConfigFileParser->getDocument();

		// Get the top-level element: NAme is "root". No attributes for "root"

		DOMElement* elementRoot = xmlDoc->getDocumentElement();
		if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));

		// Parse XML file for tags of interest: "ApplicationSettings"
		// Look one level nested within "root". (child of root)

		DOMNodeList*      children = elementRoot->getChildNodes();
		const  XMLSize_t nodeCount = children->getLength();

		// For all nodes, children of "root" in the XML tree.
		
		for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
		{
			map<string,map<string,string>> spriteAbMap;
			StringMap unitValues;
			DOMNode* currentNode = children->item(xx);
			if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
			{
				
				// Found node which is an Element. Re-cast node as element
				DOMElement* currentElement
					= dynamic_cast< xercesc::DOMElement* >( currentNode );
				//if( XMLString::equals(currentElement->getTagName(), TAG_ApplicationSettings))
				//{
					// Already tested node as type element and of name "ApplicationSettings".
					// Read attributes of element "ApplicationSettings".
					
					DOMNodeList*      children2 = currentElement->getChildNodes();
					const  XMLSize_t nodeCount2 = children2->getLength();
					for( XMLSize_t xx = 0; xx < nodeCount2; ++xx )
					{
						
						DOMNode* currentNode2 = children2->item(xx);
						if( currentNode2->getNodeType() &&  // true is not NULL
							currentNode2->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
						{
							// Found node which is an Element. Re-cast node as element
							DOMElement* currentElement2
								= dynamic_cast< xercesc::DOMElement* >( currentNode2 );
							if(strcmp(XMLString::transcode(currentElement2->getTagName()),"name") == 0) {
								name = XMLString::transcode(currentElement2->getTextContent());
								
							}
							if(strcmp(XMLString::transcode(currentElement2->getTagName()),"ability") == 0) {
								spriteAbMap[abilityName] = addAbility(currentElement2);
							}
							unitValues[XMLString::transcode(currentElement2->getTagName())] = XMLString::transcode(currentElement2->getTextContent());

						}
					}

					spriteMap[name] = unitValues;
					abilityMap[name] = spriteAbMap;
			}
		}
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		//ostringstream errBuf;
		//errBuf << "Error parsing file: " << message << flush;
		//XMLString::release( &message );
	}
	StringMap::iterator pos;
	return spriteMap;
}

map<string,string> unitMapParser::addAbility(DOMElement* ability) {
	map<string,string> tmp;
	DOMNodeList*      children = ability->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();
	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		
		DOMNode* currentNode2 = children->item(xx);
		if( currentNode2->getNodeType() &&  // true is not NULL
			currentNode2->getNodeType() == DOMNode::ELEMENT_NODE ) // is element 
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement2
				= dynamic_cast< xercesc::DOMElement* >( currentNode2 );
			if(strcmp(XMLString::transcode(currentElement2->getTagName()),"name") == 0) {
				abilityName = XMLString::transcode(currentElement2->getTextContent());
			}
			tmp[XMLString::transcode(currentElement2->getTagName())] = XMLString::transcode(currentElement2->getTextContent());
		}
	}
	//spriteAbMap[name] = tmp;
	return tmp;
}