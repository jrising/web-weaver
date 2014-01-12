/**
 *	HTML Reader Class Library
 *
 *	LiteHTMLTag.h - Defines LiteHTMLTag
 *
 *	Written By Gurmeet S. Kochar <gomzygotit@hotmail.com>
 *	Copyright (c) 2004. All rights reserved.
 *
 *	This code may be used in compiled form in any way you desire 
 *	(including commercial use). The code may be redistributed 
 *	unmodified by any means PROVIDING it is not sold for profit 
 *	without the authors written consent, and providing that this 
 *	notice and the authors name and all copyright notices remains 
 *	intact. However, this file and the accompanying source code may 
 *	not be hosted on a website or bulletin board without the authors 
 *	written permission.
 *
 *	This file is provided "AS IS" with no expressed or implied warranty.
 *	The author accepts no liability for any damage/loss of business that
 *	this product may cause.
 *
 *	Although it is not necessary, but if you use this code in any of 
 *	your application (commercial or non-commercial), please INFORM me 
 *	so that I may know how useful this library is. This will encourage 
 *	me to keep updating it.
 *
 *	HISTORY:
 *
 *	Version 1.0				Gurmeet S. Kochar (GSK)
 *	Mar 18, 2004			First release version.
 */
#ifndef __LITEHTMLTAG_H__
#define __LITEHTMLTAG_H__

/*
 * Conditional Includes
 */
#ifndef __LITEHTMLCOMMON_H__
#	include "LiteHTMLCommon.h"
#endif	// !__LITEHTMLCOMMON_H__

#ifndef __LITEHTMLATTRIBUTES_H__
#	include "LiteHTMLAttributes.h"
#endif	// !__LITEHTMLATTRIBUTES_H__

/**
 * LiteHTMLTag
 *
 * @version 1.0 (March 18, 2004)
 * @author Gurmeet S. Kochar
 */
class LiteHTMLTag
{
// Construction/Destruction
public:
	LiteHTMLTag()
		: m_pcollAttr(NULL)
	{ }

	/**
	 * @param bCopy - if true, this LiteHTMLTag makes a copy of the 
	 * LiteHTMLAttributes pointer. if false, this constructor takes 
	 * ownership of the encapsulated LiteHTMLAttributes pointer.
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	LiteHTMLTag(LiteHTMLTag &rSource, bool bCopy = false)
		:m_pcollAttr(NULL)
	{
		m_strTagName = rSource.m_strTagName;
		if (!bCopy)
		{
			m_pcollAttr = rSource.m_pcollAttr;
			rSource.m_pcollAttr = NULL;
		}
		else if (rSource.m_pcollAttr != NULL)
		{
          m_pcollAttr = new LiteHTMLAttributes(*(rSource.m_pcollAttr), true);
		}
	}

	virtual ~LiteHTMLTag()
		{ SAFE_DELETE_POINTER(m_pcollAttr); }

// Attributes
public:
	/**
	 * @return name of the tag
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	string getTagName(void) const
		{ return (m_strTagName); }

	/**
	 * @return pointer to the attribute collection
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	const LiteHTMLAttributes* getAttributes(void) const
		{ return (m_pcollAttr);  }

// Parsing Helpers
public:
	// parses tag information from the given string
	unsigned parseFromStr(char *str, 
					  bool &bIsOpeningTag, 
					  bool &bIsClosingTag, 
					  bool bParseAttrib = true);

// Data Members
private:
	/**
	 * collection of LiteHTMLElemAttr objects
	 * @since 1.0
	 */
	LiteHTMLAttributes	*m_pcollAttr;

	/**
	 * tag name of the element
	 * @since 1.0
	 */
	string				m_strTagName;
};

/**
 * LiteHTMLTag::parseFromStr
 * 
 * @param rStr - string to parse
 * @param bIsOpeningTag - receives true if the tag parsed 
 *        is a opening tag, false otherwise.
 * @param bIsClosingTag - receives true if the tag parsed 
 *        is a closing tag, false otherwise.
 * @param bParseAttrib - determines whether attribute/value 
 *        pairs should be parsed. Default is true.
 *
 * @return number of characters successfully parsed
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
inline unsigned LiteHTMLTag::parseFromStr(char *str, 
									   bool &bIsOpeningTag, 
									   bool &bIsClosingTag, 
									   bool bParseAttrib /* = true */)
{
  //ASSERT(AfxIsValidString(str));

	bool				bClosingTag = false;
	bool				bOpeningTag = false;
	LiteHTMLAttributes	*pcollAttr = NULL;
	string				strTagName;
	unsigned				nRetVal = 0U, 
						nTemp = 0U;
	char*				begin = str;
	char*				end = NULL;

	// skip leading white-space characters
	while (isspace(*begin))
      begin++;

	// HTML tags always begin with a less-than symbol
	if (*begin != '<')
		return (0U);
	
	// skip tag's opening delimeter '<'
	begin++;

	// optimization for empty opening tags
	if (*begin == '>')
	{
      if (!strTagName.empty())
        throw "strTagName not empty";
      if (pcollAttr != NULL)
        throw "pcollAttr not NULL";
      if (bClosingTag)
        throw "closing tag set";
      nRetVal = begin - str;
      goto LUpdateAndExit;
	}

	// tag names always begin with an alphabet
	if (!isalpha(*begin))
	{
		bClosingTag = (*begin == '/');
		if (bClosingTag)
          begin++;
		else
			return (0U);
	}

	bOpeningTag = !bClosingTag;
	end = begin;
	do
	{
		// tag name may contain letters (a-z, A-Z), digits (0-9), 
		// underscores '_', hyphen '-', colons ':', and periods '.'
		if ( (!isalnum(*end)) && 
			 (*end != '-') && (*end != ':') && 
			 (*end != '_') && (*end != '.') )
		{
          if (end == begin)
            throw "end == beginning";
          
          // only white-space characters, a null-character, a 
          // greater-than symbol, or a forward-slash can break 
          // a tag name
          if (*end == '\0' || isspace(*end) || 
              *end == '>' || 
              (*end == '/' && (!bClosingTag)) )
			{
              break;
			}

          return (0U);	// any other character will fail parsing process
		}

		end++;
	}
	while(true);

	// store tag name for later use
	strTagName = string(begin, end - begin);

	// is this a closing tag?
	if (bClosingTag)
	{
		// in a closing tag, there can be only one symbol after 
		// tag name, i.e., the tag end delimeter '>'. Anything 
		// else will result in parsing failure
		if (*end != '>')
			return (0U);

		// skip tag's ending delimeter
		end++;

        if (!strTagName.length())
          throw "empty tag length";
		if (pcollAttr != NULL)
          throw "non NULL pcollAttr";
		nRetVal = end - str;
		goto LUpdateAndExit;
	}

	// tag contains attribute/value pairs?
	if (*end != '>')
	{
		begin = end;
		end = NULL;

		// skip white-space characters after tag name
		while (isspace(*begin))
          begin++;

		nTemp = 0U;
		if (bParseAttrib)	// parse attribute/value pairs?
		{
          if (pcollAttr != NULL)
            throw "non NULL pcollAttr";
          // instantiate collection ...
          if ((pcollAttr = new LiteHTMLAttributes) == NULL)
			{
              throw "(Error) LiteHTMLTag::parseFromStr: Out of memory.\n";
			}
          
          // ... and delegate parsing process
          nTemp = pcollAttr->parseFromStr(begin);
		}

		if (nTemp == 0)	// attribute/value pair parsing is disabled? 
						//	- OR - 
						// attribute/value pairs could not be parsed?
		{
			SAFE_DELETE_POINTER(pcollAttr);
			if ((end = strstr(begin, "/>")) == NULL)
			{
				if ((end = strchr(begin, '>')) == NULL)
					return (0U);
			}
		}
		else
		{
			end = begin + nTemp;

			// skip white-space after attribute/value pairs
			while (isspace(*end))
              end++;
			
			// tag's ending delimeter could not be found?
			if (*end == '\0')
			{
				SAFE_DELETE_POINTER(pcollAttr);
				return (0U);
			}
		}

		// a tag like this one: <BR/>
		if (*end == '/')
		{
          if (!bOpeningTag)
            throw "no openning tag";
          bClosingTag = true;
          end++;
		}
	}

	// HTML tags always end with a greater-than '>' symbol
	if (*end != '>')
	{
		SAFE_DELETE_POINTER(pcollAttr);
		return (0U);
	}
	else
      end++;

	nRetVal = end - str;
	goto LUpdateAndExit;	// just to show the flow-of-control

LUpdateAndExit:
	bIsClosingTag = bClosingTag;
	bIsOpeningTag = bOpeningTag;
	m_strTagName = strTagName;
    
    // ignore leading white-spaces
    m_strTagName.erase(0, m_strTagName.find_first_not_of(" \t\r\n"));

    // ignore trailing white-spaces
    size_t i = m_strTagName.find_last_not_of(" \t\r\n");
    if (i == string::npos)
      m_strTagName = "";
    else
      m_strTagName.erase(i + 1);

	SAFE_DELETE_POINTER(m_pcollAttr);
	m_pcollAttr = pcollAttr;
	pcollAttr = NULL;

	return (nRetVal);
}

#endif	// !__LITEHTMLTAG_H__
