/*************************************************************************/
/*	File : CKSoundReader.h												 */
/*	Author :  Nicolas Galinotti											 */	
/*																		 */	
/*	Virtools SDK 															 */	 
/*	Copyright (c) Virtools 2000, All Rights Reserved.						 */	
/*************************************************************************/
#ifndef CKSOUNDREADER_H

#define CKSOUNDREADER_H


#include "CKDataReader.h"
#include "CKSoundManager.h"

// Summary: To Document.
// 
typedef enum CK_SOUNDREADER_ERROR {
	CKSOUND_READER_OK			=	0,
	CKSOUND_READER_GENERICERR	=	-1,
	CKSOUND_READER_EOF			=	-2,
	CKSOUND_READER_NO_DATA_READY=	-3
} CK_SOUNDREADER_ERROR;

// Summary: To Document.
// 
class CKSoundReader: public CKDataReader  
{
protected:
	CK_DATAREADER_FLAGS m_Flags;
public:
	void* m_SubFileMem;			//Used to keep data in memory when read from VxBigfile files when sound is streamed
public:
	
	virtual ~CKSoundReader(){}
	
	virtual CK_DATAREADER_FLAGS GetFlags() {return m_Flags; }

	// Opens a file
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR OpenFile(char *file) = NULL;

	// Decodes next chunk of data, use get data buffer to get decoded data
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR Decode() = NULL;

	// Gets the last decoded buffer
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR GetDataBuffer(BYTE **buf, int *size) = NULL;
	
	// Gets the wave format of decoded datas
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR GetWaveFormat(CKWaveFormat *wfe) = NULL;

	// Gets whole decoded data size
	/************************************************
	Summary: To Document.
	************************************************/
	virtual int GetDataSize() = NULL;
	
	// Gets the play time length
	/************************************************
	Summary: To Document.
	************************************************/
	virtual int GetDuration() = NULL;

	
	// Play
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR Play() = NULL;

	// Stop
	/************************************************
	Summary: To Document.
	************************************************/	
	virtual CKERROR Stop() = NULL;

	// Play
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR Pause() = NULL;

	// Resume
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR Resume() = NULL;
	
	// Seek
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR Seek(int pos) = NULL;
	
	// Opens a from memory
	/************************************************
	Summary: To Document.
	************************************************/
	virtual CKERROR ReadMemory(void* memory, int size){return CK_OK;};
	
	
};

#endif 
