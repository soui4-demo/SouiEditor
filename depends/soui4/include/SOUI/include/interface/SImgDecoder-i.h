﻿/**
 * Copyright (C) 2014-2050 SOUI group
 * All rights reserved.
 *
 * @file       imgdecoder-i.h
 * @brief
 * @version    v1.0
 * @author     soui group
 * @date       2014-05-28
 *
 * Describe
 */

#ifndef __SIMGDECODER_I__H__
#define __SIMGDECODER_I__H__

#include <interface/obj-ref-i.h>

SNSBEGIN
/**
 * @struct     IImgFrame
 * @brief      a image frame
 *
 * Describe
 */
#undef INTERFACE
#define INTERFACE IImgFrame
DECLARE_INTERFACE_(IImgFrame, IObjRef)
{
    /**
     * GetSize
     * @brief    get image size in pixel
     * @param [out]   UINT * pWid --  image width
     * @param [out]   UINT * pHei --  image height
     * @return   BOOL -- TRUE: succeed; FALSE: failed
     * Describe
     */
    STDMETHOD_(BOOL, GetSize)(THIS_ UINT * pWid, UINT * pHei) PURE;

    /**
     * GetPixels
     * @brief    get pixels buffer
     * @return   const VOID *  pixels buffer ptr
     * Describe
     */
    STDMETHOD_(const VOID *, GetPixels)(CTHIS) SCONST PURE;

    /**
     * GetDelay
     * @brief    get delay for a frame of a gif image
     * @return   int time in MS*10
     * Describe
     */
    STDMETHOD_(int, GetDelay)(THIS) PURE;
};

/**
 * @struct     IImgX
 * @brief      image data
 *
 * Describe
 */
#undef INTERFACE
#define INTERFACE IImgX
DECLARE_INTERFACE_(IImgX, IObjRef)
{
    //!添加引用
    /*!
     */
    STDMETHOD_(long, AddRef)(THIS) PURE;

    //!释放引用
    /*!
     */
    STDMETHOD_(long, Release)(THIS) PURE;

    //!释放对象
    /*!
     */
    STDMETHOD_(void, OnFinalRelease)(THIS) PURE;

    /**
     * LoadFromMemory
     * @brief    load image data from a mememory buffer
     * @param    void * pBuf --  point of buffer
     * @param    size_t bufLen --  size of buffer
     * @return   int
     * Describe
     */
    STDMETHOD_(int, LoadFromMemory)(THIS_ void *pBuf, size_t bufLen) PURE;
    /**
     * LoadFromFile
     * @brief    load image from file
     * @param    LPCWSTR pszFileName --  file name in unicode
     * @return   int
     * Describe
     */
    STDMETHOD_(int, LoadFromFileW)(THIS_ LPCWSTR pszFileName) PURE;

    /**
     * LoadFromFile
     * @brief    load image from file
     * @param    LPCSTR pszFileName --  file name in char
     * @return   int
     * Describe
     */
    STDMETHOD_(int, LoadFromFileA)(THIS_ LPCSTR pszFileName) PURE;

    /**
     * GetFrameCount
     * @brief    get frame count of the image data
     * @return   UINT -- image frame count
     * Describe
     */
    STDMETHOD_(UINT, GetFrameCount)(THIS) PURE;

    /**
     * GetFrame
     * @brief    get frame data
     * @param    UINT iFrame -- the target frame index
     * @return   IImgFrame * -- the associated image frame with the input frame index
     * Describe
     */
    STDMETHOD_(IImgFrame *, GetFrame)(THIS_ UINT iFrame) PURE;
};

typedef enum _ImgFmt
{
    Img_PNG,
    Img_BMP,
    Img_TIFF,
    Img_JPG,
    Img_Webp,
} ImgFmt;

/**
 * @struct     IImgDecoderFactory
 * @brief      image decoder factory
 *
 * Describe
 */
#undef INTERFACE
#define INTERFACE IImgDecoderFactory
DECLARE_INTERFACE_(IImgDecoderFactory, IObjRef)
{
    //!添加引用
    /*!
     */
    STDMETHOD_(long, AddRef)(THIS) PURE;

    //!释放引用
    /*!
     */
    STDMETHOD_(long, Release)(THIS) PURE;

    //!释放对象
    /*!
     */
    STDMETHOD_(void, OnFinalRelease)(THIS) PURE;
    /**
     * CreateImgX
     * @brief    create a IImgX object
     * @param [out] IImgX * * ppImgDecoder --  the created IImgX
     * @return   BOOL
     * Describe
     */
    STDMETHOD_(BOOL, CreateImgX)(THIS_ IImgX * *ppImgDecoder) PURE;

    /**
     * SaveImage
     * @brief    Write a IBitmap Object to File with the specified format
     * @param [in] IBitmap *pImg  --  IBitmap Object
     * @param [in] LPCWSTR pszFileName --  file name
     * @param [in] LPVOID pFormat --  format param
     * @return   HRESULT
     * Describe
     */
    STDMETHOD_(HRESULT, SaveImage)
    (CTHIS_ BYTE * pBits, int nWid, int nHei, LPCWSTR pszFileName, const void *pFormat) SCONST PURE;

    STDMETHOD_(HRESULT, SaveImage2)
    (CTHIS_ BYTE * pBits, int nWid, int nHei, LPCWSTR pszFileName, ImgFmt imgFmt) SCONST PURE;

    /**
     * GetImgDecoderDesc
     * @brief    query image decoder description
     * @return   LPCWSTR
     * Describe
     */
    STDMETHOD_(LPCWSTR, GetDescription)(CTHIS) SCONST PURE;
};

SNSEND
#endif // __SIMGDECODER_I__H__