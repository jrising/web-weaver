/**
 *	HTML Reader Class Library
 *
 *	LiteHTMLReader.h - Main Header
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
 *	Mar 26, 2004			First release version.
 */
#ifndef __LITEHTMLREADER_H__
#define __LITEHTMLREADER_H__

#ifndef __LITEHTMLTAG_H__
#	include "LiteHTMLTag.h"
#endif	// !__LITEHTMLTAG_H__

class LiteHTMLReader;	// forward declaration

/**
 * ILiteHTMLReaderEvents
 * This class presents an interface that must be implemented 
 * by all those classes that want to handle the notifications 
 * sent by the LiteHTMLReader while parsing an HTML document.
 * The order of events handled by the ILiteHTMLReaderEvents 
 * handler is determined by the order of information within 
 * the document being parsed. It's important to note that the 
 * interface includes a series of methods that the LiteHTMLReader 
 * invokes during the parsing operation. The reader passes the 
 * appropriate information to the method's parameters. To perform 
 * some type of processing for a method, you simply add code to 
 * the method in your own ILiteHTMLReaderEvents implementation.
 *
 * @version 1.0 (Mar 06, 2004)
 * @author Gurmeet S. Kochar
 */
class ILiteHTMLReaderEvents
{
	friend class LiteHTMLReader;

// Events
protected:
	virtual void BeginParse(unsigned long dwAppData, bool &bAbort)
	{
      bAbort = false;
	}

	virtual void StartTag(LiteHTMLTag *pTag, unsigned long dwAppData, bool &bAbort)
	{
		bAbort = false;
	}

	virtual void EndTag(LiteHTMLTag *pTag, unsigned long dwAppData, bool &bAbort)
	{
		bAbort = false;
	}
	
	virtual void Characters(const string &rText, unsigned long dwAppData, bool &bAbort)
	{
		bAbort = false;
	}
	
	virtual void Comment(const string &rComment, unsigned long dwAppData, bool &bAbort)
	{
		bAbort = false;
	}

	virtual void EndParse(unsigned long dwAppData, bool bIsAborted)
	{
	}

public:
	virtual ~ILiteHTMLReaderEvents()
	{
	}
};

/**
 * LiteHTMLReader
 * This class allows you to parse HTML text in a simple, and fast 
 * way by handling events that it generates as it finds specific 
 * symbols in the text. This class is similar to the SAX (Simple 
 * API for XML) implementation, which is an XML DOM parser. Like 
 * SAX, the LiteHTMLReader class reads a section of HTML text, 
 * generates an event, and moves on to the next section. This 
 * results in low memory consumption.
 *
 * @version 1.0 (Mar 26, 2004)
 * @author Gurmeet S. Kochar
 *
 * @todo add support for multiple event handlers.
 * @todo add support for tag validation, a new interface, that 
 *       validator classes must implement, so reader can then 
 *       make a call, such as isValidTag(...), to validate tag 
 *       information and act accordingly.
 * @todo add more reader options (ReaderOptionsEnum). Until now, 
 *       there is only one.
 */
class LiteHTMLReader
{
public:
	enum EventMaskEnum {
		/** @since 1.0 */ 
		notifyStartStop		= 0x00000001L,	// raise BeginParse and EndParse?
		
		/** @since 1.0 */ 
		notifyTagStart		= 0x00000002L,	// raise StartTag?
		
		/** @since 1.0 */ 
		notifyTagEnd		= 0x00000004L,	// raise EndTag?
		
		/** @since 1.0 */ 
		notifyCharacters	= 0x00000008L,	// raise Characters?
		
		/** @since 1.0 */ 
		notifyComment		= 0x00000010L,	// raise Comment?
	};

	enum ReaderOptionsEnum {
		/** @since 1.0 */ 
		resolveEntities,	// determines whether entity references should be resolved

		// TODO: 
		// TODO: add more reader options
		// TODO: 
	};

// Construction/Destruction
public:
	LiteHTMLReader() 
	{
		m_bResolveEntities = true;	// entities are resolved, by default
		m_dwAppData = 0L;	// reasonable default!
		m_dwBufPos = 0L;	// start from the very beginning
		m_dwBufLen = 0L;	// buffer length is unknown yet
		
		// default is to raise all of the events
		m_eventMask = (EventMaskEnum)(notifyStartStop  | 
									  notifyTagStart   | 
									  notifyTagEnd     | 
									  notifyCharacters | 
									  notifyComment    );

		m_pEventHandler = NULL;	// no event handler is associated
		m_lpszBuffer = NULL;
	}

public:
	/**
	 * Returns an event mask which signifies the notification 
	 * messages a LiteHTMLReader will send while parsing HTML 
	 * text.
	 *
	 * @return event mask
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	EventMaskEnum getEventMask(void) const
		{ return (m_eventMask); }

	/**
	 * Sets a new event mask.
	 *
	 * @param dwNewEventMask - new event mask
	 *
	 * @return previous event mask
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	EventMaskEnum setEventMask(unsigned long dwNewEventMask)
	{
		EventMaskEnum	oldMask = m_eventMask;
		m_eventMask = (EventMaskEnum)dwNewEventMask;
		return (oldMask);
	}

	/**
	 * Changes the current event mask by adding and removing 
	 * flags specified by addFlags and removeFlags, respectively.
	 *
	 * @param addFlags - flags to add in the current event mask
	 * @param removeFlags - flags to remove from the current event mask
	 *
	 * @return previous event mask
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	EventMaskEnum setEventMask(unsigned long addFlags, unsigned long removeFlags)
	{
		unsigned long	dwOldMask = (unsigned long)m_eventMask;
		unsigned long	dwNewMask = (dwOldMask | addFlags) & ~removeFlags;
		m_eventMask = (EventMaskEnum)dwNewMask;
		return ((EventMaskEnum)dwOldMask);
	}

	/**
	 * Returns a 32-bit application-specific data 
	 * previously set by a call to setAppData()
	 *
	 * @return 32-bit application-specific data
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	unsigned long getAppData(void) const
		{ return (m_dwAppData); }

	/**
	 * Allows you to store 32-bit application-specific 
	 * data that will be passed to event handlers on each call
	 *
	 * @param dwNewAppData - Application-specific data
	 *
	 * @return previously associated data
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	unsigned long setAppData(unsigned long dwNewAppData)
	{
		unsigned long	dwOldAppData = m_dwAppData;
		m_dwAppData = dwNewAppData;
		return (dwOldAppData);
	}

	/**
	 * Returns a pointer to an event handler registered with 
	 * a LiteHTMLReader by a previous call to setEventHandler().
	 *
	 * @return pointer to a ILiteHTMLReaderEvents
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	ILiteHTMLReaderEvents* getEventHandler(void) const
		{ return (m_pEventHandler); }

	/**
	 * Registers an event handler with a LiteHTMLReader. If no 
	 * event handler is registered with the reader, all events 
	 * raised by the reader will be ignored. An application can 
	 * change the event handler even when the parsing process 
	 * is in progress.
	 *
	 * @param pNewHandler - pointer to an event handler. 
	 *        This parameter can be NULL also.
	 *
	 * @return pointer to the previous event handler
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	ILiteHTMLReaderEvents* setEventHandler(ILiteHTMLReaderEvents* pNewHandler)
	{
		ILiteHTMLReaderEvents *pOldHandler = m_pEventHandler;
		m_pEventHandler = pNewHandler;
		return (pOldHandler);
	}

	// returns the current value for the specified option
	bool getBoolOption(ReaderOptionsEnum option, bool& bCurVal) const;
	// sets a new value for the specified option
	bool setBoolOption(ReaderOptionsEnum option, bool bNewVal);

// Operations
public:
	// parses an HTML document from the specified string
	UINT Read(char *lpszString);
	// parses an HTML document from a file given its HANDLE
	UINT ReadFile(HANDLE hFile);

// Helpers
protected:
	/** Parsing Helpers */

	// parses an HTML document, and returns the 
	// number of characters successfully parsed
	virtual UINT parseDocument(void);

	// parses an HTML comment from the buffer starting from 
	// the current buffer position and returns true on sucess
	virtual bool parseComment(string &rComment);

	// parses an HTML tag from the buffer starting from 
	// the current buffer position and returns true on success
	virtual bool parseTag(LiteHTMLTag &rTag, bool &bIsOpeningTag, bool &bIsClosingTag);

	/**
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	virtual void NormalizeCharacters(string &rCharacters)
	{
		//rCharacters.Replace(_T("\r\n"), _T(""));
		//rCharacters.Remove(_T('\n'));
		//rCharacters.Replace(_T('\r'), _T(' '));
		//rCharacters.Replace(_T('\t'), _T(' '));
	}

	/** Buffer Manipulation Helpers */

	/**
	 * Resets the buffer position back to the beginning
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	void ResetSeekPointer(void)
		{ m_dwBufPos = 0L; }

	/**
	 * Reads the next character and advances the buffer position
	 *
	 * @return character read
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	TCHAR ReadChar(void)
	{
		ASSERT(m_lpszBuffer != NULL);
		if (m_dwBufPos >= m_dwBufLen)
			return (NULL);
		return (m_lpszBuffer[m_dwBufPos++]);
	}

	/**
	 * Moves the buffer back by one TCHAR
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	TCHAR UngetChar(void)
	{
		if (m_lpszBuffer == NULL)
          throw "buffer is NULL";

		if (!m_dwBufPos)
          throw "buffer position is not set";

		return (m_lpszBuffer[--m_dwBufPos]);
	}

	/** Other Helpers */
	
	/**
	 * Determines if the specified event's notification is to be raised
	 *
	 * @return true if notification is to be raised, false otherwise.
	 *         false is returned also when there is no event handler 
	 *         associated with the reader.
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool getEventNotify(unsigned long dwEvent) const 
	{
      if (!(dwEvent == notifyStartStop  || 
            dwEvent == notifyTagStart   || 
            dwEvent == notifyTagEnd     || 
            dwEvent == notifyCharacters || 
            dwEvent == notifyComment))
        throw "event notify invalid";

      if (m_pEventHandler == NULL)
        return (false);
      return ((m_eventMask & dwEvent) == dwEvent);
	}

	/**
	 * Determines if the character specified by ch is 
	 * a white-space character. White-space characters 
	 * are defined as ASCII 0x9-0xD,0x20
	 *
	 * @returns true if character is a white-space, 
	 *          false otherwise
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isWhiteSpace(TCHAR ch) const
		{ return (::_istspace(ch) ? true : false); }

protected:
	/**
	 * Determines if character entities are to be resolved
	 * Default is true.
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool	m_bResolveEntities;

	/**
	 * 32-bit app-specific data (to be passed to callbacks)
	 * Default is 0.
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	unsigned long	m_dwAppData;

	/**
	 * Position of the seek pointer
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	unsigned long	m_dwBufPos;

	/**
	 * size, in TCHARs, of the buffer
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	unsigned long	m_dwBufLen;

	/**
	 * Bit-mask flags to customize events notification(s)
	 * Default is the ORed result of all EventMaskEnum flags.
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	EventMaskEnum	m_eventMask;

	/**
	 * Pointer to an ILiteHTMLReaderEvents based event handling object
	 * Default is NULL
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	ILiteHTMLReaderEvents*	m_pEventHandler;

	/**
	 * Pointer to an array of characters being parsed
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	char	*m_lpszBuffer;
};

/**
 * Returns the current value for the specified option.
 *
 * @param option - option to inquire
 * @param bCurVal - this will receive the current value for the option.
 *
 * @return true if value was retrieved successfully; otherwise false.
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
inline bool LiteHTMLReader::getBoolOption(ReaderOptionsEnum option, bool& bCurVal) const
{
	bool bSuccess = false;

	switch (option)
	{
	case resolveEntities:
		{
			bCurVal = m_bResolveEntities;
			bSuccess = true;
			break;
		}
	default:
		{
			bSuccess = false;
			break;
		}
	}
	return (bSuccess);
}

/**
 * Changes the value of an option and returns 
 * true/false indicating if the specified option 
 * was set successfully.
 *
 * @param option - option to change 
 *                 (one of the ReaderOptionsEnum constants)
 * @param bNewVal - value to set
 *
 * @return true if option was set successfully; otherwise false.
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
inline bool LiteHTMLReader::setBoolOption(ReaderOptionsEnum option, bool bNewVal)
{
	bool bSuccess = false;

	switch (option)
	{
	case resolveEntities:
		{
			m_bResolveEntities = bNewVal;
			bSuccess = true;
			break;
		}
	default:
		{
			bSuccess = false;
			break;
		}
	}
	return (bSuccess);
}

/**
 * Parses an HTML comment starting from the current buffer position.
 *
 * @param rComment - this will receive the comment (without delimeters)
 *
 * @return true if successful, false otherwise
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
inline bool LiteHTMLReader::parseComment(string &rComment)
{
  if (m_lpszBuffer == NULL)
    throw "buffer is NULL";

  if (m_dwBufPos < 0L)
    throw "buffer position invalid";

  if (m_dwBufPos + 4 >= m_dwBufLen)
    throw "buffer position invalid";

	// HTML comments begin with '<!' delimeter and 
	// are immediately followed by two hyphens '--'
	if (::_tcsncmp(&m_lpszBuffer[m_dwBufPos], _T("<!--"), 4))
		return (false);

	char	*lpszBegin = &m_lpszBuffer[m_dwBufPos + 4];	
	// HTML comments end with two hyphen symbols '--'
	char	*lpszEnd = ::_tcsstr(lpszBegin, _T("--"));

	// comment ending delimeter could not be found?
	if (lpszEnd == NULL)
		// consider everything after current buffer position a comment
	{
		rComment = lpszBegin;
		m_dwBufPos += (4 + rComment.GetLength());
		return (true);
	}

	string	strComment(lpszBegin, lpszEnd - lpszBegin);
	
	// end of buffer?
	if (lpszEnd + (sizeof(TCHAR) * 2) >= m_lpszBuffer + m_dwBufLen)
		return (false);

	// skip white-space characters after comment ending delimeter '--'
	lpszEnd += (sizeof(TCHAR) * 2);
	while (::_istspace(*lpszEnd))
		lpszEnd = ::_tcsinc(lpszEnd);

	// comment has not been terminated properly
	if (*lpszEnd != _T('>'))
		return (false);

	lpszEnd = ::_tcsinc(lpszEnd);
	m_dwBufPos += (lpszEnd - &m_lpszBuffer[m_dwBufPos]);
	rComment = strComment;
	return (true);
}

/**
 * Parses an HTML tag starting from the current buffer position.
 *
 * @param rTag - this will receive tag information (along with its attributes)
 * @param bIsOpeningTag - receives true if the tag parsed is a opening tag.
 * @param bIsClosingTag - receives true if the tag parsed is a closing tag.
 *
 * @return true if successful, false otherwise
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
inline bool LiteHTMLReader::parseTag(LiteHTMLTag &rTag, 
									  bool &bIsOpeningTag, 
									  bool &bIsClosingTag)
{
  if (m_lpszBuffer == NULL)
    throw "buffer is null";

  if (m_dwBufPos < 0L)
    throw "buffer position invalid";
  if (m_dwBufPos + 4 >= m_dwBufLen)
    throw "buffer position invalid";

	UINT nRetVal = rTag.parseFromStr(&m_lpszBuffer[m_dwBufPos], 
					bIsOpeningTag, bIsClosingTag);
	if (!nRetVal)
		return (false);

	m_dwBufPos += nRetVal;
	return (true);
}

#endif	// !__LITEHTMLREADER_H__
