/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkPdfUtils_DEFINED
#define SkPdfUtils_DEFINED

#include "SkMatrix.h"
#include "SkRect.h"
#include "SkPdfConfig.h"
#include "SkString.h"

class SkPdfArray;
class SkPdfContext;
class SkCanvas;
class SkPdfNativeObject;

// TODO(edisonn): temporary code, to report how much of the PDF we actually think we rendered.
enum SkPdfResult {
    kOK_SkPdfResult,
    kPartial_SkPdfResult,
    kNYI_SkPdfResult,
    kIgnoreError_SkPdfResult,
    kError_SkPdfResult,
    kUnsupported_SkPdfResult,

    kCount_SkPdfResult
};

struct NotOwnedString {
    const unsigned char* fBuffer;
    size_t fBytes;

    static void init(NotOwnedString* str) {
        str->fBuffer = NULL;
        str->fBytes = 0;
    }

    static void init(NotOwnedString* str, const char* sz) {
        str->fBuffer = (const unsigned char*)sz;
        str->fBytes = strlen(sz);
    }

    bool equals(const char* sz) {
        return strncmp((const char*)fBuffer, sz, fBytes) == 0 && fBytes == strlen(sz);

    }
};

// TODO(edisonn): hack to make code generation simpler. Alternatively we can update the
// generate_code.py not to rely on != operator
bool operator !=(const SkString& first, const char* second);

SkMatrix SkMatrixFromPdfArray(SkPdfArray* pdfArray);

SkPdfResult doType3Char(SkPdfContext* pdfContext, SkCanvas* canvas, const SkPdfNativeObject* skobj, SkRect bBox, SkMatrix matrix, double textSize);

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TRACE functions
//
#ifdef PDF_TRACE
void SkTraceMatrix(const SkMatrix& matrix, const char* sz);
void SkTraceRect(const SkRect& rect, const char* sz);
#else
#define SkTraceMatrix(a,b)
#define SkTraceRect(a,b)
#endif

#endif   // SkPdfUtils_DEFINED
