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
#include "xmlparser.h"


using namespace std;

/**
*  Constructor initializes xerces-C libraries.
*  The XML tags and attributes which we seek are defined.
*  The xerces-C DOM parser infrastructure is initialized.
*/

GetConfig::GetConfig()
{
	try
	{
		XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
	}
	catch( XMLException& e )
	{
		char* message = XMLString::transcode( e.getMessage() );
		cerr << "XML toolkit initialization error: " << message << endl;
		XMLString::release( &message );
		// throw exception here to return ERROR_XERCES_INIT
	}

	// Tags and attributes used in XML file.
	// Can't call transcode till after Xerces Initialize()
	TAG_root        = XMLString::transcode("game");
	
	//ATTR_OptionA = XMLString::transcode("option_a");
	//ATTR_OptionB = XMLString::transcode("option_b");
	m_ConfigFileParser = new XercesDOMParser;

}

/**
*  Class destructor frees memory used to hold the XML tag and 
*  attribute definitions. It als terminates use of the xerces-C
*  framework.
*/

GetConfig::~GetConfig()
{
	// Free memory

	delete m_ConfigFileParser;
	//if(m_OptionA)   XMLString::release( &m_OptionA );
	//if(m_OptionB)   XMLString::release( &m_OptionB );

	//try
	//{
	//	XMLString::release( &TAG_root );

	//	XMLString::release( &TAG_ApplicationSettings );
	//	//XMLString::release( &ATTR_OptionA );
	//	//XMLString::release( &ATTR_OptionB );
	//}
	//catch( ... )
	//{
	//	cerr << "Unknown exception encountered in TagNamesdtor" << endl;
	//}

	// Terminate Xerces

	try
	{
		XMLPlatformUtils::Terminate();  // Terminate after release of memory
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );

		cerr << "XML ttolkit teardown error: " << message << endl;
		XMLString::release( &message );
	}
}




