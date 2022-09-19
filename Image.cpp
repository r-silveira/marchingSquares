//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-- includes -----------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include "Image.h"
//-----------------------------------------------------------------------------
#define ILBOOL(b) (b==IL_TRUE)?true:false
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-- Class: CImage ------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int CImage::m_nRefCount (0);
//-----------------------------------------------------------------------------
CImage::CImage()
{
  if (m_nRefCount == 0)
    ilInit();
  m_nRefCount++;

  ilGenImages(1, &m_idImage);
}
//-----------------------------------------------------------------------------
CImage::CImage(const string& strFilename)
{
  // ESSE CONSTRUTOR DÁ PROBLEMA NO GCC !!!
  if (m_nRefCount == 0)
    ilInit();
  m_nRefCount++;

  ilGenImages(1, &m_idImage);
  LoadFromFilename(strFilename);
}
//-----------------------------------------------------------------------------
CImage::~CImage()
{
  ilDeleteImages(1, &m_idImage);

  m_nRefCount--;
  if (m_nRefCount == 0)
    ilShutDown();
}
//-----------------------------------------------------------------------------
const bool CImage::LoadFromFilename(const string& strFilename)
{
  ilBindImage(m_idImage);
  const ILboolean boLoaded = ilLoadImage((char*) strFilename.c_str());
  return(ILBOOL(boLoaded));
}
//-----------------------------------------------------------------------------
const int CImage::GetWidth()
{
  ilBindImage(m_idImage);
  const int nWidth = ilGetInteger(IL_IMAGE_WIDTH);
  return(nWidth);
}
//-----------------------------------------------------------------------------
const int CImage::GetHeight()
{
  ilBindImage(m_idImage);
  const int nHeight = ilGetInteger(IL_IMAGE_HEIGHT);
  return(nHeight);
}
//-----------------------------------------------------------------------------
const int CImage::GetPixelDepth()
{
  ilBindImage(m_idImage);
  const int nHeight = ilGetInteger(IL_IMAGE_BPP);
  return(nHeight);
}
//-----------------------------------------------------------------------------
const unsigned char* CImage::GetData()
{
  ilBindImage(m_idImage);
  const unsigned char* pPixels = ilGetData();
  return(pPixels);
}
//-----------------------------------------------------------------------------
