/**
 *	HTML Reader Class Library
 *
 *	LiteHTMLEntityResolver.h - Defines LiteHTMLEntityResolver
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
 *	Mar 21, 2004			First release version.
 *  May 13, 2011            Translation to STL (James Rising)
 */
#ifndef __LITEHTMLENTITYRESOLVER_H__
#define __LITEHTMLENTITYRESOLVER_H__

/*
 * Conditional Includes
 */
#ifndef __LITEHTMLCOMMON_H__
#	include "LiteHTMLCommon.h"
#endif

#include <string>
#include <map>
#include <assert.h>
#include <strings.h>
using namespace std;

/**
 * LiteHTMLEntityResolver
 * This is a utility class that helps in resolving the character 
 * and numeric entity references.
 *
 * @version 1.0 (Mar 17, 2004)
 * @author Gurmeet S. Kochar
 */
class LiteHTMLEntityResolver
{
private:
  class CharEntityRefs : public map<string, char>
	{
	public:
		CharEntityRefs()
		{
			/** C0 Controls and Basic Latin */
			(*this)["quot"]		= '\x22';
			(*this)["amp"]		= '\x26';
			(*this)["apos"]		= '\x27';
			(*this)["lt"]		= '\x3C';
			(*this)["gt"]		= '\x3E';
			/** ISO 8859-1 (Latin-1) characters */
			(*this)["nbsp"]		= '\xA0';
			(*this)["iexcl"]	= '\xA1';
			(*this)["cent"]		= '\xA2';
			(*this)["pound"]	= '\xA3';
			(*this)["current"]	= '\xA4';
			(*this)["yen"]		= '\xA5';
			(*this)["brvbar"]	= '\xA6';
			(*this)["sect"]		= '\xA7';
			(*this)["uml"]		= '\xA8';
			(*this)["copy"]		= '\xA9';
			(*this)["ordf"]		= '\xAA';
			(*this)["laquo"]	= '\xAB';
			(*this)["not"]		= '\xAC';
			(*this)["shy"]		= '\xAD';
			(*this)["reg"]		= '\xAE';
			(*this)["macr"]		= '\xAF';
			(*this)["deg"]		= '\xB0';
			(*this)["plusmn"]	= '\xB1';
			(*this)["sup2"]		= '\xB2';
			(*this)["sup3"]		= '\xB3';
			(*this)["acute"]	= '\xB4';
			(*this)["micro"]	= '\xB5';
			(*this)["para"]		= '\xB6';
			(*this)["middot"]	= '\xB7';
			(*this)["cedil"]	= '\xB8';
			(*this)["sup1"]		= '\xB9';
			(*this)["ordm"]		= '\xBA';
			(*this)["raquo"]	= '\xBB';
			(*this)["frac14"]	= '\xBC';
			(*this)["frac12"]	= '\xBD';
			(*this)["frac34"]	= '\xBE';
			(*this)["iquest"]	= '\xBF';
			(*this)["Agrave"]	= '\xC0';
			(*this)["Aacute"]	= '\xC1';
			(*this)["Acirc"]	= '\xC2';
			(*this)["Atilde"]	= '\xC3';
			(*this)["Auml"]		= '\xC4';
			(*this)["Aring"]	= '\xC5';
			(*this)["AElig"]	= '\xC6';
			(*this)["Ccedil"]	= '\xC7';
			(*this)["Egrave"]	= '\xC8';
			(*this)["Eacute"]	= '\xC9';
			(*this)["Ecirc"]	= '\xCA';
			(*this)["Euml"]		= '\xCB';
			(*this)["Igrave"]	= '\xCC';
			(*this)["Iacute"]	= '\xCD';
			(*this)["Icirc"]	= '\xCE';
			(*this)["Iuml"]		= '\xCF';
			(*this)["ETH"]		= '\xD0';
			(*this)["Ntilde"]	= '\xD1';
			(*this)["Ograve"]	= '\xD2';
			(*this)["Oacute"]	= '\xD3';
			(*this)["Ocirc"]	= '\xD4';
			(*this)["Otilde"]	= '\xD5';
			(*this)["Ouml"]		= '\xD6';
			(*this)["times"]	= '\xD7';
			(*this)["Oslash"]	= '\xD8';
			(*this)["Ugrave"]	= '\xD9';
			(*this)["Uacute"]	= '\xDA';
			(*this)["Ucirc"]	= '\xDB';
			(*this)["Uuml"]		= '\xDC';
			(*this)["Yacute"]	= '\xDD';
			(*this)["THORN"]	= '\xDE';
			(*this)["szlig"]	= '\xDF';
			(*this)["agrave"]	= '\xE0';
			(*this)["aacute"]	= '\xE1';
			(*this)["acirc"]	= '\xE2';
			(*this)["atilde"]	= '\xE3';
			(*this)["auml"]		= '\xE4';
			(*this)["aring"]	= '\xE5';
			(*this)["aelig"]	= '\xE6';
			(*this)["ccedil"]	= '\xE7';
			(*this)["egrave"]	= '\xE8';
			(*this)["eacute"]	= '\xE9';
			(*this)["ecirc"]	= '\xEA';
			(*this)["euml"]		= '\xEB';
			(*this)["igrave"]	= '\xEC';
			(*this)["iacute"]	= '\xED';
			(*this)["icirc"]	= '\xEE';
			(*this)["iuml"]		= '\xEF';
			(*this)["eth"]		= '\xF0';
			(*this)["ntilde"]	= '\xF1';
			(*this)["ograve"]	= '\xF2';
			(*this)["oacute"]	= '\xF3';
			(*this)["ocirc"]	= '\xF4';
			(*this)["otilde"]	= '\xF5';
			(*this)["ouml"]		= '\xF6';
			(*this)["divide"]	= '\xF7';
			(*this)["oslash"]	= '\xF8';
			(*this)["ugrave"]	= '\xF9';
			(*this)["uacute"]	= '\xFA';
			(*this)["ucirc"]	= '\xFB';
			(*this)["uuml"]		= '\xFC';
			(*this)["yacute"]	= '\xFD';
			(*this)["thorn"]	= '\xFE';
			(*this)["yuml"]		= '\xFF';
		}
	};

// Constructors
public:
	LiteHTMLEntityResolver()	{ }

// Operations
public:
	/**
	 * Resolves a character or numeric entity reference.
	 *
	 * @param rStr - entity to resolve
	 * @param ch - variable that will receive the result
	 *
	 * @return number of TCHARs used to resolve entity reference
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	static unsigned int resolveEntity(char* entity, char& subst)
	{
		assert(charEntityRefs.size());
		assert(entity);

		char	*begin = entity, 
				*end = strchr(entity, ';');
		char	chTemp = 0;
		
		// entity references always end with a semi-colon ';'
		if (end == NULL)
			return (0);

		// skip leading white-space characters
		while (isspace(*begin))
			begin++;
		
		// remaining string (including semi-colon) 
		// must be at least 4 characters in length
		if (end - begin < 3)
			return (0U);

		// entity references always begin with an ampersand '&' symbol
		if (*begin != '&')
			return (0U);
		begin++;

		// numeric (decimal or hexadecimal) entity reference?
		if (*begin == '#')
		{
		  begin++;
		  chTemp = *begin;
		  int radix = (isdigit(chTemp) ? 10 : 
					   (chTemp == 'x' || 
						chTemp == 'X' ? 16 : 0));
		  if (radix) {
			if (radix == 16)
			  begin++;
				
			unsigned long	ulNum = strtoul(begin, NULL, radix);
			subst = ulNum;
			end++;
			return (end - entity);
		  }
		}

		// character entity reference?
		else
		{
			string strKey(begin, end - begin);

			// because some character entity references are 
			// case-sensitive, we must fix them manually
			if (!strcasecmp(strKey.c_str(), "eth") || 
				!strcasecmp(strKey.c_str(), "thorn"))
			  {
				if (isupper(strKey[0]))
				  std::transform(strKey.begin(), strKey.end(), strKey.begin(), ::toupper);
				else
				  std::transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
			  }
			else if (!strcasecmp(strKey.c_str(), "Oslash"))
			{
			  std::transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
			  strKey[0] = 'O';
			}
			else if (!strcasecmp(strKey.c_str(), "AElig"))
			{
			  std::transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
			  strKey[0] = 'A';
			  strKey[1] = 'E';
			}
			else
			{
				string	strT = strKey.substr(1);
				std::transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
				if (strcasecmp(strT.c_str(), "grave") == 0 || 
					strcasecmp(strT.c_str(), "acute") == 0 || 
					strcasecmp(strT.c_str(), "circ")  == 0 || 
					strcasecmp(strT.c_str(), "uml")   == 0 || 
					strcasecmp(strT.c_str(), "tilde") == 0 || 
					strcasecmp(strT.c_str(), "cedil") == 0 || 
					strcasecmp(strT.c_str(), "ring")  == 0)
				{
					strKey[0] = strT[0];
				}
			}
			
			// is this a known entity reference?
			map<string, char>::iterator it = charEntityRefs.find(strKey);
			if (it != charEntityRefs.end())
			{
				subst = it->second;
				end++;
				return (end - entity);
			}
		}

		return (0U);
	}

// Data Members
private:
	static CharEntityRefs	charEntityRefs;
};

#endif
