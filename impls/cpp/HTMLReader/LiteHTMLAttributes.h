/**
 *	HTML Reader Class Library
 *
 *	LiteHTMLAttributes.h - Defines LiteHTMLAttributes and 
 *	                       LiteHTMLElemAttr
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
#ifndef __LITEHTMLATTRIBUTES_H__
#define __LITEHTMLATTRIBUTES_H__

#include <string>
#include <map>
#include <vector>
#include <ctype.h>
using namespace std;

#define RGB(r,g,b)          ((int)((unsigned char)(r) | ((unsigned char)(g) << 8) | ((unsigned char)(b) << 16)))


/*
 * Conditional Includes
 */
#ifndef __LITEHTMLCOMMON_H__
#	include "LiteHTMLCommon.h"
#endif	// !__LITEHTMLCOMMON_H__

#ifndef __LITEHTMLENTITYRESOLVER_H__
#	include "LiteHTMLEntityResolver.h"
#endif	// !__LITEHTMLENTITYRESOLVER_H__

class LiteHTMLAttributes;	// forward declaration

/**
 * LiteHTMLElemAttr
 *
 * @version 1.0 (Mar 18, 2004)
 * @author Gurmeet S. Kochar
 */
class LiteHTMLElemAttr
{
	// Friends
	friend class LiteHTMLAttributes;

// Constructors
public:
	LiteHTMLElemAttr(char *lpszAttribName = NULL, 
					  char *lpszAttribValue = NULL)
	{
		Init();
		m_strAttrName = lpszAttribName;
		m_strAttrValue = lpszAttribValue;
	}

	LiteHTMLElemAttr(const LiteHTMLElemAttr &rSource)
	{
		Init();
		m_strAttrName = rSource.m_strAttrName;
		m_strAttrValue = rSource.m_strAttrValue;
	}

// Initialization Helpers
private:
	static void Init(void)
	{
		if (_namedColors.size())
			return;

		/** 28 system colors */
		_namedColors["activeborder"]		= (int)0x8000000A;
		_namedColors["activecaption"]		= (int)0x80000002;
		_namedColors["appworkspace"]		= (int)0x8000000C;
		_namedColors["background"]			= (int)0x80000001;
		_namedColors["buttonface"]			= (int)0x8000000F;
		_namedColors["buttonhighlight"]		= (int)0x80000014;
		_namedColors["buttonshadow"]		= (int)0x80000010;
		_namedColors["buttontext"]			= (int)0x80000012;
		_namedColors["captiontext"]			= (int)0x80000009;
		_namedColors["graytext"]			= (int)0x80000011;
		_namedColors["highlight"]			= (int)0x8000000D;
		_namedColors["highlighttext"]		= (int)0x8000000E;
		_namedColors["inactiveborder"]		= (int)0x8000000B;
		_namedColors["inactivecaption"]		= (int)0x80000003;
		_namedColors["inactivecaptiontext"]	= (int)0x80000013;
		_namedColors["infobackground"]		= (int)0x80000018;
		_namedColors["infotext"]			= (int)0x80000017;
		_namedColors["menu"]				= (int)0x80000004;
		_namedColors["menutext"]			= (int)0x80000007;
		_namedColors["scrollbar"]			= (int)0x80000000;
		_namedColors["threeddarkshadow"]	= (int)0x80000015;
		_namedColors["threedface"]			= (int)0x8000000F;
		_namedColors["threedhighlight"]		= (int)0x80000014;
		_namedColors["threedlightshadow"]	= (int)0x80000016;
		_namedColors["threedshadow"]		= (int)0x80000010;
		_namedColors["window"]				= (int)0x80000005;
		_namedColors["windowframe"]			= (int)0x80000006;
		_namedColors["windowtext"]			= (int)0x80000008;

		/** 16 basic colors */
		_namedColors["black"]				= RGB(0x00, 0x00, 0x00);
		_namedColors["gray"]				= RGB(0x80, 0x80, 0x80);
		_namedColors["silver"]				= RGB(0xC0, 0xC0, 0xC0);
		_namedColors["white"]				= RGB(0xFF, 0xFF, 0xFF);
		_namedColors["yellow"]				= RGB(0xFF, 0xFF, 0x00);
		_namedColors["olive"]				= RGB(0x80, 0x80, 0x00);
		_namedColors["red"]					= RGB(0xFF, 0x00, 0x00);
		_namedColors["maroon"]				= RGB(0x80, 0x00, 0x00);
		_namedColors["fuchsia"]				= RGB(0xFF, 0x00, 0xFF);
		_namedColors["purple"]				= RGB(0x80, 0x00, 0x80);
		_namedColors["blue"]				= RGB(0x00, 0x00, 0xFF);
		_namedColors["navy"]				= RGB(0x00, 0x00, 0x80);
		_namedColors["aqua"]				= RGB(0x00, 0xFF, 0xFF);
		_namedColors["teal"]				= RGB(0x00, 0x80, 0x80);
		_namedColors["lime"]				= RGB(0x00, 0xFF, 0x00);
		_namedColors["green"]				= RGB(0x00, 0x80, 0xFF);

		/** additional named colors */
		_namedColors["darkolivegreen"]		= RGB(0x55, 0x6B, 0x2F);
		_namedColors["olivedrab"]			= RGB(0x6B, 0x8E, 0x23);
		_namedColors["yellowgreen"]			= RGB(0x9A, 0xCD, 0x32);
		_namedColors["lawngreen"]			= RGB(0x7C, 0xFC, 0x00);
		_namedColors["chartreuse"]			= RGB(0x7F, 0xFF, 0x00);
		_namedColors["greenyellow"]			= RGB(0xAD, 0xFF, 0x2F);
		_namedColors["palegreen"]			= RGB(0x98, 0xFB, 0x98);
		_namedColors["lightgreen"]			= RGB(0x90, 0xEE, 0x90);
		_namedColors["darkgreen"]			= RGB(0x00, 0x64, 0x00);
		_namedColors["forestgreen"]			= RGB(0x22, 0x8B, 0x22);
		_namedColors["seagreen"]			= RGB(0x2E, 0x8B, 0x57);
		_namedColors["mediumseagreen"]		= RGB(0x3C, 0xB3, 0x71);
		_namedColors["limegreen"]			= RGB(0x32, 0xCD, 0x32);
		_namedColors["darkseagreen"]		= RGB(0x8F, 0xBC, 0x8B);
		_namedColors["springgreen"]			= RGB(0x00, 0xFF, 0x7F);
		_namedColors["mediumspringgreen"]	= RGB(0x00, 0xFA, 0x99);
		_namedColors["darkslategray"]		= RGB(0x2F, 0x4F, 0x4F);
		_namedColors["darkcyan"]			= RGB(0x00, 0x8B, 0x8B);
		_namedColors["cadetblue"]			= RGB(0x5F, 0x9E, 0xA0);
		_namedColors["lightseagreen"]		= RGB(0x20, 0xB2, 0xAA);
		_namedColors["mediumaquamarine"]	= RGB(0x66, 0xCD, 0xAA);
		_namedColors["turquoise"]			= RGB(0x40, 0xE0, 0xD0);
		_namedColors["aquamarine"]			= RGB(0x7F, 0xFF, 0xD4);
		_namedColors["paleturquoise"]		= RGB(0xAF, 0xEE, 0xEE);
		_namedColors["slategray"]			= RGB(0x70, 0x80, 0x90);
		_namedColors["lightslategray"]		= RGB(0x77, 0x88, 0x99);
		_namedColors["steelblue"]			= RGB(0x46, 0x82, 0xB4);
		_namedColors["deepskyblue"]			= RGB(0x00, 0xBF, 0xFF);
		_namedColors["darkturquoise"]		= RGB(0x00, 0xCE, 0xD1);
		_namedColors["mediumturquoise"]		= RGB(0x48, 0xD1, 0xCC);
		_namedColors["powderblue"]			= RGB(0xB0, 0xE0, 0xE6);
		_namedColors["lightcyan"]			= RGB(0xE0, 0xFF, 0xFF);
		_namedColors["darkblue"]			= RGB(0x00, 0x00, 0x8B);
		_namedColors["mediumblue"]			= RGB(0x00, 0x00, 0xCD);
		_namedColors["royalblue"]			= RGB(0x41, 0x69, 0xe1);
		_namedColors["dodgerblue"]			= RGB(0x1E, 0x90, 0xFF);
		_namedColors["cornflowerblue"]		= RGB(0x64, 0x95, 0xED);
		_namedColors["skyblue"]				= RGB(0x87, 0xCE, 0xEB);
		_namedColors["lightskyblue"]		= RGB(0x87, 0xCE, 0xFA);
		_namedColors["lightblue"]			= RGB(0xAD, 0xD8, 0xE6);
		_namedColors["midnightblue"]		= RGB(0x19, 0x19, 0x70);
		_namedColors["darkslateblue"]		= RGB(0x48, 0x3D, 0x8B);
		_namedColors["blueviolet"]			= RGB(0x8A, 0x2B, 0xE2);
		_namedColors["slateblue"]			= RGB(0x6A, 0x5A, 0xCD);
		_namedColors["mediumslateblue"]		= RGB(0x7B, 0x68, 0xEE);
		_namedColors["mediumpurple"]		= RGB(0x93, 0x70, 0xDB);
		_namedColors["lightsteelblue"]		= RGB(0xB0, 0xC4, 0xDE);
		_namedColors["lavender"]			= RGB(0xE6, 0xE6, 0xFA);
		_namedColors["indigo"]				= RGB(0x4B, 0x00, 0x82);
		_namedColors["darkviolet"]			= RGB(0x94, 0x00, 0xD3);
		_namedColors["darkorchid"]			= RGB(0x99, 0x32, 0xCC);
		_namedColors["mediumorchid"]		= RGB(0xBA, 0x55, 0xD3);
		_namedColors["orchid"]				= RGB(0xDA, 0x70, 0xD6);
		_namedColors["violet"]				= RGB(0xEE, 0x82, 0xEE);
		_namedColors["plum"]				= RGB(0xDD, 0xA0, 0xDD);
		_namedColors["thistle"]				= RGB(0xD8, 0xDF, 0xD8);
		_namedColors["darkmagenta"]			= RGB(0x8B, 0x00, 0x8B);
		_namedColors["mediumvioletred"]		= RGB(0xC7, 0x15, 0x85);
		_namedColors["deeppink"]			= RGB(0xFF, 0x14, 0x93);
		_namedColors["palmvioletred"]		= RGB(0xDB, 0x70, 0x93);
		_namedColors["hotpink"]				= RGB(0xFF, 0x69, 0xB4);
		_namedColors["lightpink"]			= RGB(0xFF, 0xB6, 0xC1);
		_namedColors["pink"]				= RGB(0xFF, 0xC0, 0xCB);
		_namedColors["mistyrose"]			= RGB(0xFF, 0xE4, 0xE1);
		_namedColors["brown"]				= RGB(0xA5, 0x2A, 0x2A);
		_namedColors["indianred"]			= RGB(0xCD, 0x5C, 0x5C);
		_namedColors["rosybrown"]			= RGB(0xBC, 0x8F, 0x8F);
		_namedColors["salmon"]				= RGB(0xFA, 0x80, 0x72);
		_namedColors["lightcoral"]			= RGB(0xF0, 0x80, 0x80);
		_namedColors["darksalmon"]			= RGB(0xE9, 0x96, 0x7A);
		_namedColors["lightsalmon"]			= RGB(0xFF, 0xA0, 0x7A);
		_namedColors["peachpuff"]			= RGB(0xFF, 0xDA, 0xB9);
		_namedColors["darkred"]				= RGB(0x8B, 0x00, 0x00);
		_namedColors["firebrick"]			= RGB(0xB2, 0x22, 0x22);
		_namedColors["crimson"]				= RGB(0xDC, 0x14, 0x3C);
		_namedColors["orangered"]			= RGB(0xFF, 0x45, 0x00);
		_namedColors["tomato"]				= RGB(0xFF, 0x63, 0x47);
		_namedColors["coral"]				= RGB(0xFF, 0x7F, 0x50);
		_namedColors["wheat"]				= RGB(0xF5, 0xDE, 0xB3);
		_namedColors["papayawhip"]			= RGB(0xFF, 0xEF, 0xD5);
		_namedColors["sienna"]				= RGB(0xA0, 0x52, 0x2D);
		_namedColors["chocolate"]			= RGB(0xD2, 0x69, 0x1E);
		_namedColors["darkorange"]			= RGB(0xFF, 0x8C, 0x00);
		_namedColors["sandybrown"]			= RGB(0xF4, 0xA4, 0x60);
		_namedColors["orange"]				= RGB(0xFF, 0xA5, 0x00);
		_namedColors["navajowhite"]			= RGB(0xFF, 0xDE, 0xAD);
		_namedColors["moccasin"]			= RGB(0xFF, 0xE4, 0xB5);
		_namedColors["saddlebrown"]			= RGB(0x8B, 0x45, 0x13);
		_namedColors["peru"]				= RGB(0xCD, 0x85, 0x3F);
		_namedColors["burlywood"]			= RGB(0xDE, 0xB8, 0x87);
		_namedColors["tan"]					= RGB(0xD2, 0xB4, 0x8C);
		_namedColors["bisque"]				= RGB(0xFF, 0xE4, 0xC4);
		_namedColors["blanchedalmond"]		= RGB(0xFF, 0xEB, 0xCD);
		_namedColors["antiquewhite"]		= RGB(0xFA, 0xEB, 0xD7);
		_namedColors["darkgoldenrod"]		= RGB(0xB8, 0x86, 0x0B);
		_namedColors["goldenrod"]			= RGB(0xDA, 0xA5, 0x20);
		_namedColors["darkkhaki"]			= RGB(0xBD, 0xB7, 0x6B);
		_namedColors["gold"]				= RGB(0xFF, 0xD7, 0x00);
		_namedColors["khaki"]				= RGB(0xF0, 0xE6, 0x8C);
		_namedColors["palegoldenrod"]		= RGB(0xEE, 0xE8, 0xAA);
		_namedColors["lemonchiffon"]		= RGB(0xFF, 0xFA, 0xCD);
		_namedColors["beige"]				= RGB(0xF5, 0xF5, 0xDC);
		_namedColors["lightgoldenrodyellow"]= RGB(0xFA, 0xFA, 0xD2);
		_namedColors["lightyellow"]			= RGB(0xFF, 0xFF, 0xE0);
		_namedColors["ivory"]				= RGB(0xFF, 0xFF, 0x00);
		_namedColors["cornsilk"]			= RGB(0xFF, 0xF8, 0xDC);
		_namedColors["oldlace"]				= RGB(0xFD, 0xF5, 0xE6);
		_namedColors["florawhite"]			= RGB(0xFF, 0xFA, 0xF0);
		_namedColors["honeydew"]			= RGB(0xF0, 0xFF, 0xF0);
		_namedColors["mintcream"]			= RGB(0xF5, 0xFF, 0xFA);
		_namedColors["azure"]				= RGB(0xF0, 0xFF, 0xFF);
		_namedColors["ghostwhite"]			= RGB(0xF8, 0xF8, 0xFF);
		_namedColors["linen"]				= RGB(0xFA, 0xF0, 0xE6);
		_namedColors["seashell"]			= RGB(0xFF, 0xF5, 0xEE);
		_namedColors["snow"]				= RGB(0xFF, 0xFA, 0xFA);
		_namedColors["dimgray"]				= RGB(0x69, 0x69, 0x69);
		_namedColors["darkgray"]			= RGB(0xA9, 0xA9, 0xA9);
		_namedColors["lightgray"]			= RGB(0xD3, 0xD3, 0xD3);
		_namedColors["gainsboro"]			= RGB(0xDC, 0xDC, 0xDC);
		_namedColors["whitesmoke"]			= RGB(0xF5, 0xF5, 0xF5);
		_namedColors["ghostwhite"]			= RGB(0xF8, 0xF8, 0xFF);
		_namedColors["aliceblue"]			= RGB(0xF0, 0xF8, 0xFF);
	}

// Attributes
public:
	/**
	 * @return name of this LiteHTMLElemAttr
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	string getName(void) const
		{ return (m_strAttrName); }

	/**
	 * @return value of this LiteHTMLElemAttr
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	string getValue(void) const
		{ return (m_strAttrValue); }

	/**
	 * Determines if the attribute value is a named color value
	 * @return true if attribute value is a named color, otherwise, false
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isNamedColorValue(void) const
	{
      if ( (m_strAttrValue.length()) && (isalpha(m_strAttrValue[0])) ) {
        string		strKey(m_strAttrValue);
        
        transform(strKey.begin(), strKey.end(), strKey.begin(), tolower);
        map<string, int>::iterator it = _namedColors.find(m_strAttrValue);
        return (it != _namedColors.end());
      }

      return false;
    }

	/**
	 * Determines if the attribute value is a named system color value
	 * @return true if value is a named system color, false otherwise
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isSysColorValue(void) const
	{
      if ( (m_strAttrValue.length()) && (isalpha(m_strAttrValue[0])) ) {
        string		strKey(m_strAttrValue);

        transform(strKey.begin(), strKey.end(), strKey.begin(), tolower);
        map<string, int>::iterator it = _namedColors.find(m_strAttrValue);
        if (it != _namedColors.end())
          return (it->second >= (int) 0x80000000 && it->second <= (int) 0x80000018);
      }
      return false;
	}

	/**
	 * Determines if the attribute value is a color value in 
	 * hexadecimal format
	 * @return true if attribute value is a color value, otherwise, false
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isHexColorValue(void) const
	{
		// zero-length attribute value?
		if (m_strAttrValue.empty())
			return (false);

		if (m_strAttrValue[0] == '#')
		{
			if (m_strAttrValue.length() > 1)
			{
				for (unsigned i = 1; i < m_strAttrValue.length(); i++)
				{
					if (!isxdigit(m_strAttrValue[i]))
						return (false);
				}
				return (true);
			}
		}

		return (false);
	}

	/**
	 * Determines if the attribute value contains a color reference
	 * @return true, if attribute value is color value, false otherwise.
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isColorValue(void) const
		{ return (isNamedColorValue() || isHexColorValue()); }

	/**
	 * Returns the color value of the attribute
	 * @return a int representing the color
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	int getColorValue(void) const
	{
		int crTemp = _clrInvalid;
		if (isNamedColorValue())
		{
			string	strKey(m_strAttrValue);

            transform(strKey.begin(), strKey.end(), strKey.begin(), tolower);
            map<string, int>::iterator it = _namedColors.find(m_strAttrValue);

            if (it != _namedColors.end()) {
              crTemp = it->second;
              /*// is this a system named color value?
              if (crTemp >= (int) 0x80000000 && crTemp <= (int) 0x80000018)
              crTemp = ::GetSysColor(crTemp & 0x7FFFFFFF);*/
			}
		}
		else if (isHexColorValue())
          crTemp = strtoul(m_strAttrValue.substr(1).c_str(), NULL, 16);
		return (crTemp);
	}
	
	/**
	 * Returns the RGB value of the attribute in hexadecimal format
	 * @return hexadecimal string representing the color value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	string getColorHexValue(void) const
	{
		string	strColorHex;
		if (isHexColorValue())
			strColorHex = m_strAttrValue.substr(1);
		else
		{
			int crTemp = getColorValue();
			if (crTemp != _clrInvalid) {
              char buffer[8];
              sprintf(buffer, "#%06x", crTemp);
              strColorHex = buffer;
            }
		}
		return (strColorHex);
	}

	/**
	 * Checks to see if the attribute contains a percent value
	 * @return true if value is a percent value, otherwise, false
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isPercentValue(void) const
    { return (m_strAttrValue[m_strAttrValue.length()-1] == '%' ? true : false); }

	/**
	 * Returns a percent value of the attribute
	 * @return percentage value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	unsigned short getPercentValue(unsigned short max = _percentMax) const
	{
      if (max <= 0)
        throw "max must be > 0";
      if (!isPercentValue())	return (0);
      unsigned short	percentVal = (unsigned short)((short)*this);
      return ((percentVal > max ? max : percentVal));
	}
	
	/**
	 * Parses a length value from the attribute/value 
	 * and identifies its length unit also
	 *
	 * @param rUnit - this will receive the type of the length unit
	 *
	 * @return an integer value of the attribute 
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	enum LengthUnitsEnum { em, ex, px, per, in, cm, mm, pt, pc };
	short getLengthValue(LengthUnitsEnum &rUnit) const
	{
		static const char _szUnits[][4] = 
		{
			/** relative length units */
			"em", "ex", "px", "%", 
			/** absolute length units */
			"in", "cm", "mm", "pt", "pc"
		};

		if (m_strAttrValue.empty())
			return (0);

        int i;
		for (i = 0; i < (int) (sizeof(_szUnits)/sizeof(_szUnits[0])); i++)
		{
          string part = m_strAttrValue.substr(m_strAttrValue.length() - strlen(_szUnits[i]));
          transform(part.begin(), part.end(), part.begin(), tolower);
			if (part.compare(_szUnits[i]) == 0)
			{
				rUnit = (LengthUnitsEnum)i;
				break;
			}
		}
		if (i == sizeof(_szUnits)/sizeof(_szUnits[0]))
			return (0);
		return (*this);
	}

// Operators
public:
	/**
	 * Converts attribute value to bool
	 * @return true or false
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator bool() const
	{
      string copy = m_strAttrValue;
      transform(copy.begin(), copy.end(), copy.begin(), tolower);

      if (!m_strAttrValue.compare("true"))
        return (true);
      if (!m_strAttrValue.compare("false"))
        return (false);
      return (((short)*this ? true : false));
	}

	/**
	 * Converts attribute value to BYTE (unsigned char)
	 * @return the left-most character of attribute value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator unsigned char() const
		{ return ((unsigned char)(m_strAttrValue.length() ? m_strAttrValue[0] : 0)); }
	
	/**
	 * Converts attribute value to double
	 * @return 0.00 on failure, otherwise, a numeric value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator double() const
    { return (strtod(m_strAttrValue.c_str(), NULL)); }
	
	/**
	 * Converts attribute value to signed short int
	 * @return 0 on failure, otherwise, an integer value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator short() const
    { return ((short)atoi(m_strAttrValue.c_str())); }
	
	/**
	 * @return attribute value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator char*() const
    { return ((char*) m_strAttrValue.c_str()); }

// Private Operations
private:
	/**
	 * Sets the value of an attribute. Takes care of the following:
	 *  1. Ignores leading and trailing white-space characters
	 *  2. Replaces character entities with appropriate characters.
	 *  3. Ignores line feeds (LF).
	 *  4. Replaces each carriage-return (CR) or tab with a single space.
	 *
	 * @param lpszValue - new attribute value
	 * 
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	void putValue(char *lpszValue)
	{
      //ASSERT(AfxIsValidString(lpszValue));

      m_strAttrValue = lpszValue;
      
      // ignore leading white-spaces
      m_strAttrValue.erase(0, m_strAttrValue.find_first_not_of(" \t\r\n"));

      // ignore trailing white-spaces
      size_t i = m_strAttrValue.find_last_not_of(" \t\r\n");
      if (i == string::npos)
        m_strAttrValue = "";
      else
        m_strAttrValue.erase(i + 1);

      // ignore line feeds
      // replace tab and carriage-return with a single space
      size_t found;
      while ((found = m_strAttrValue.find("\n\r\t")) != string::npos) {
        if (m_strAttrValue[found] == '\n')
          m_strAttrValue.erase(found);
        else
          m_strAttrValue[found] = ' ';
      }

		/** resolve entity reference(s) */
		int		iCurPos = -1, iParseLen = 0;
		char	chSubst = 0;
		do
		{
			if ((iCurPos = m_strAttrValue.find_first_of("&", ++iCurPos)) == -1)
				break;
			
			iParseLen = LiteHTMLEntityResolver::resolveEntity((char*) m_strAttrValue.substr(iCurPos).c_str(), chSubst);
			if (iParseLen) {
              string repl;
              repl.push_back(chSubst);
              m_strAttrValue.replace(iCurPos, iParseLen, repl);
            }
		}
		while (true);
	}

// Parsing Helpers
public:
	// parses an attribute/value pair from the given string
	unsigned int parseFromStr(char *lpszString);

// Data Members
public:
	static const int		_clrInvalid;	// an invalid color
	static const unsigned short	_percentMax;	// maximum allowable percentage value
private:
	typedef map<string, int>	CNamedColors;

	static CNamedColors		_namedColors;	// collection of named colors
	string					m_strAttrName,  // attribute name
							m_strAttrValue; // attribute value
};

/**
 * LiteHTMLElemAttr::parseFromStr
 *
 * @param lpszString - string to parse
 *
 * @return number of chars successfully parsed
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
inline unsigned int LiteHTMLElemAttr::parseFromStr(char *lpszString)
{
  //ASSERT(AfxIsValidString(lpszString));

	char*	lpszBegin = lpszString;
	char*	lpszEnd;
	char	ch = 0;

	// skip leading white-space characters
	while (isspace(*lpszBegin))
      lpszBegin++;

	// name doesn't begin with an alphabet?
	if (!isalpha(*lpszBegin))
		return (0U);

	lpszEnd = lpszBegin;
	do
	{
		// attribute name may contain letters (a-z, A-Z), digits (0-9), 
		// underscores '_', hyphen '-', colons ':', and periods '.'
		if ( (!isalnum(*lpszEnd)) && 
			 (*lpszEnd != '-') && (*lpszEnd != ':') && 
			 (*lpszEnd != '_') && (*lpszEnd != '.') )
		{
          if (lpszEnd == lpszBegin)
            throw "end must not equal beginning";

			// only white-space characters, a null-character, an 
			// equal-sign, a greater-than symbol, or a forward-slash 
			// can act as the separator between an attribute and its 
			// value
			if (*lpszEnd == '\0' || isspace(*lpszEnd) || 
				*lpszEnd == '=' || 
				*lpszEnd == '>' || *lpszEnd == '/')
			{
				break;
			}

			return (0U);	// any other character will fail parsing process
		}

		lpszEnd++;
	}
	while (true);

	// extract attribute name
	string	strAttrName(lpszBegin, lpszEnd - lpszBegin);
	
	if (*lpszEnd != '=')
	{
		m_strAttrName = strAttrName;
		m_strAttrValue.clear();
		return (lpszEnd - lpszString);
	}
	else
	{
		// skip white-space characters after equal-sign 
		// and the equal-sign itself
		do {
          lpszEnd++;
		} while (isspace(*lpszEnd));

		lpszBegin = lpszEnd;
		ch = *lpszEnd;
		
		// is attribute value wrapped in quotes?
		if (ch == '\'' || ch == '\"')
		{
			lpszBegin++;	// skip quote symbol
			do
			{
              lpszEnd++;
			}
			// Loop until we find the same quote character that 
			// was used at the starting of the attribute value.
			// Anything within these quotes is considered valid!
			// NOTE that the entity references are resolved later.
			while (*lpszEnd != '\0' && *lpszEnd != ch);
		}

		// open attribute value i.e. not wrapped in quotes?
		else
		{
			do 
			{ 
              lpszEnd++;
			}
			// loop until we find a tag ending delimeter or any 
			// white-space character, or until we reach at the 
			// end of the string buffer
			while (*lpszEnd != '\0' && !isspace(*lpszEnd) && 
				   *lpszEnd != '/' && *lpszEnd != '>');
		}

		m_strAttrName = strAttrName;
		if (lpszEnd == lpszBegin)	// empty attribute value?
			m_strAttrValue.clear();
		else
			// use putValue() instead of direct assignment; 
			// this will automatically normalize data before 
			// assigning according to the specs and will 
			// also resolve entity references!!!
          putValue((char*) string(lpszBegin, lpszEnd - lpszBegin).c_str());

		// calculate and return the count of characters successfully parsed
		return ((lpszEnd - lpszString) + 
				(ch == '\'' || ch == '\"' ? sizeof(char) : 0) );
	}

	return (0U);
}

/**
 * LiteHTMLAttributes
 *
 * @version 1.0 (Mar 18, 2004)
 * @author Gurmeet S. Kochar
 */
class LiteHTMLAttributes
{
// Construction/Destruction
public:
	LiteHTMLAttributes() 
		: m_parrAttrib(NULL)
	{ }

	/**
	 * @param bCopy - if true, this LiteHTMLAttributes makes a copy 
	 * of the encapsulated pointer. if false, this constructor takes 
	 * ownership of the encapsulated pointer.
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
    LiteHTMLAttributes(LiteHTMLAttributes &rSource, bool bCopy = false)
		: m_parrAttrib(NULL)
	{
		if (!bCopy)
		{
			m_parrAttrib = rSource.m_parrAttrib;
			rSource.m_parrAttrib = NULL;
		}
		else
		{
			const int	nElemCount = rSource.getCount();
			if (nElemCount)
			{
				if ((m_parrAttrib = new vector<LiteHTMLElemAttr*>) == NULL)
                  throw "memory error";
				
				LiteHTMLElemAttr	*pItem = NULL;
				m_parrAttrib->resize(nElemCount);
				
				/** DEEP COPY BEGIN */
				for (int iElem = 0; iElem < nElemCount; iElem++)
				{
					if ((pItem = new LiteHTMLElemAttr(rSource[iElem])) == NULL)
					{
						removeAll();
						throw "memory error";
						return;
					}
					
					(*m_parrAttrib)[iElem] = pItem;
					pItem = NULL;
				}
				/** DEEP COPY END */
			}
		}
	}

	virtual ~LiteHTMLAttributes()
		{ removeAll(); }

// Initialization
public:
	// parses attribute/value pairs from the given string
	unsigned int parseFromStr(char *lpszString);

// Attributes
public:
	/**
	 * Returns the count of LiteHTMLElemAttr items in this collection
	 * @return number of items
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	int getCount(void) const
	{
		if (m_parrAttrib != NULL)
          return (m_parrAttrib->size());
		return (0);
	}

	/**
	 * Look up the index of an attribute given its name.
	 * If more than one attribute with the same name exist, 
	 * this will return the index of the first match.
	 *
	 * @param lpszAttributeName - name of the attribute
	 *
	 * @return zero-based index of an attribute, or -1 if not found
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	int getIndexFromName(char *lpszAttributeName) const
	{
      //ASSERT(AfxIsValidString(lpszAttributeName));
		LiteHTMLElemAttr	*pItem = NULL;
		for (int iElem = 0; iElem < getCount(); iElem++)
		{
			if ((pItem = (*m_parrAttrib)[iElem]) == NULL)	// just in case
				continue;
			
			// perform a CASE-INSENSITIVE search
            string copyleft = pItem->m_strAttrName;
            transform(copyleft.begin(), copyleft.end(), copyleft.begin(), tolower);
            string copyright = lpszAttributeName;
            transform(copyright.begin(), copyright.end(), copyright.begin(), tolower);

			if (copyleft.compare(copyright) == 0)
				return (iElem);
		}
		return (-1);
	}

	/**
	 * Returns a LiteHTMLElemAttr object given an attribute's index
	 *
	 * @return LiteHTMLElemAttr co51ntaining the name and value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	LiteHTMLElemAttr operator[](int nIndex) const
	{
		if (!(nIndex >= 0 && nIndex < getCount()))
		{
          throw "out of bounds";
          return (LiteHTMLElemAttr());
		}
		return ( *((*m_parrAttrib)[nIndex]) );
	}

	/**
	 * Returns a LiteHTMLElemAttr object given an attribute name
	 *
	 * @return LiteHTMLElemAttr containing the name and value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	LiteHTMLElemAttr operator[](char *lpszIndex) const
	{
      //ASSERT(AfxIsValidString(lpszIndex));
		return ((*this)[getIndexFromName(lpszIndex)]);
	}

	/**
	 * Returns a LiteHTMLElemAttr object given an attribute's index
	 *
	 * @return LiteHTMLElemAttr containing the name and value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	LiteHTMLElemAttr getAttribute(int nIndex) const
		{ return ((*this)[nIndex]); }

	/**
	 * Returns a LiteHTMLElemAttr object given an attribute name
	 *
	 * @return LiteHTMLElemAttr containing the name and value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	LiteHTMLElemAttr getAttribute(char *lpszIndex) const
	{
      //ASSERT(AfxIsValidString(lpszIndex));
		return ((*this)[getIndexFromName(lpszIndex)]);
	}

	/**
	 * Returns the name of an attribute given its index
	 *
	 * @return name of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	string getName(int nIndex) const
		{ return ((*this)[nIndex].m_strAttrName); }

	/**
	 * Returns the value of an attribute given its index
	 *
	 * @return value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	string getValue(int nIndex) const
		{ return ((*this)[nIndex].m_strAttrValue); }

	/**
	 * Returns the value of an attribute given its name
	 *
	 * @return value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	string getValueFromName(char *lpszAttributeName) const
		{ return ((*this)[lpszAttributeName].m_strAttrValue); }

// Operations
public:
	/**
	 * Adds a new LiteHTMLElemAttr item to the collection
	 *
	 * @param lpszName - attribute name (serves as the key to the item)
	 * @param lpszValue - attribute value
	 * @param bReplaceOld - If an item with the same name as specified 
	 *        by lpszName already exists in the collection, this 
	 *        parameter is used to determine whether to replace the 
	 *        existing item or add a new one
	 *
	 * @return pointer to a LiteHTMLElemAttr
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	LiteHTMLElemAttr* addAttribute(char *lpszName, char *lpszValue)
	{
		//ASSERT(AfxIsValidString(lpszName));
		//ASSERT(AfxIsValidString(lpszValue));

		LiteHTMLElemAttr	*pItem = new LiteHTMLElemAttr(lpszName, lpszValue);
		if (pItem != NULL)
		{
			if (m_parrAttrib == NULL)
			{
				if ((m_parrAttrib = new vector<LiteHTMLElemAttr*>) == NULL)
				{
					SAFE_DELETE_POINTER(pItem);
					throw "(Error) LiteHTMLAttributes::addAttribute: Out of memory.\n";
					return (NULL);
				}
			}
			
			m_parrAttrib->push_back(pItem);
		}
		return (pItem);
	}
	
	/**
	 * Removes an LiteHTMLElemAttr item from the collection
	 *
	 * @param lpszName - attribute to remove
	 *
	 * @return true if successful, false otherwise
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool removeAttribute(int nIndex)
	{
		if (!(nIndex >= 0 && nIndex < getCount()))
			return (false);
		LiteHTMLElemAttr	*pItem = NULL;
        if (((*m_parrAttrib)[nIndex]) == NULL)
          throw "could not find element";

		SAFE_DELETE_POINTER(pItem);
		return (true);
	}
	
	/**
	 * Removes all LiteHTMLElemAttr items from the collection
	 * @return true if successful, false otherwise
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool removeAll(void)
	{
		LiteHTMLElemAttr	*pItem = NULL;
		for (int iElem = 0; iElem < getCount(); iElem++)
		{
          pItem = (*m_parrAttrib)[iElem];
          if (pItem == NULL)
            throw "null element";

          SAFE_DELETE_POINTER(pItem);
		}
		SAFE_DELETE_POINTER(m_parrAttrib);
		return (true);
	}

// Data Members
private:
	vector<LiteHTMLElemAttr*>* m_parrAttrib;	// array of attributes/value pairs
};

/**
 * LiteHTMLAttributes::parseFromStr
 *
 * @param lpszString - string to parse. It can contain pairs such as: 
 *
 *          1. NAME
 *          2. NAME=VALUE
 *          3. NAME='VALUE'
 *          4. NAME="VALUE"
 *
 *        NAME consist of letters, digits, underscores, 
 *        colons, hyphens, and periods
 *
 *        NOTE that white-spaces between NAME and equal-sign AND 
 *        equal-sign and VALUE is allowed.
 *
 * @return number of chars successfully parsed
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
inline unsigned int LiteHTMLAttributes::parseFromStr(char *lpszString)
{
	//ASSERT(AfxIsValidString(lpszString));

	vector<LiteHTMLElemAttr*>		*pcoll = NULL;
	LiteHTMLElemAttr	oElemAttr;
	const unsigned int			nStrLen = strlen(lpszString);
	unsigned int				nRetVal = 0U, 
						nTemp = 0U;

	do
	{
		// try to parse an attribute/value 
		// pair from the rest of the string
		if (!(nTemp = oElemAttr.parseFromStr(&lpszString[nRetVal])))
		{
			if (!nRetVal)
				goto LError;
			break;
		}

		// collection has not been instantiated until now?
		if (pcoll == NULL)
		{
			// instantiate now
			if ((pcoll = new vector<LiteHTMLElemAttr*>) == NULL)
				// out of memory?
			{
				throw "(Error) LiteHTMLAttributes::parseFromStr: Out of memory.\n";
				goto LError;
			}
		}

		// add attribute/value pair to collection
		pcoll->push_back(new LiteHTMLElemAttr(oElemAttr));

		// advance seek pointer
		nRetVal += nTemp;
	}
	
	// do we still have something in the buffer to parse?
	while (nRetVal < nStrLen);

	// collection was never instantiated?
	if (pcoll == NULL)
		goto LError;
	// collection is empty?
	if (pcoll->size() == 0)
		goto LError;
	// current collection could not be emptied?
	if (!removeAll())
		goto LError;

	m_parrAttrib = pcoll;
	pcoll = NULL;
	goto LCleanExit;	// success!

LError:
	SAFE_DELETE_POINTER(pcoll);
	nRetVal = 0U;

LCleanExit:
	return (nRetVal);
}

#endif	// !__LITEHTMLATTRIBUTES_H__
