/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkLruImageCache_DEFINED
#define SkLruImageCache_DEFINED

#include "SkImageCache.h"
#include "SkThread.h"
#include "SkTInternalLList.h"

class CachedPixels;

/**
 *  SkImageCache implementation that uses an LRU cache to age out old images.
 */
class SkLruImageCache : public SkImageCache {

public:
    SkLruImageCache(size_t budget);

    virtual ~SkLruImageCache();

#ifdef SK_DEBUG
    CacheStatus getCacheStatus(intptr_t ID) const SK_OVERRIDE;
#endif

    void setBudget(size_t newBudget);

    virtual void* allocAndPinCache(size_t bytes, intptr_t* ID) SK_OVERRIDE;
    virtual void* pinCache(intptr_t ID) SK_OVERRIDE;
    virtual void releaseCache(intptr_t ID) SK_OVERRIDE;
    virtual void throwAwayCache(intptr_t ID) SK_OVERRIDE;

private:
    // Linked list of recently used. Head is the most recently used, and tail is the least.
    SkTInternalLList<CachedPixels> fLRU;
    typedef SkTInternalLList<CachedPixels>::Iter Iter;

#ifdef SK_DEBUG
    // fMutex is mutable so that getCacheStatus can be const
    mutable
#endif
    SkMutex fMutex;
    size_t  fRamBudget;
    size_t  fRamUsed;

    /**
     *  Find the CachedPixels represented by ID, or NULL if not in the cache. Mutex must be locked
     *  before calling.
     */
    CachedPixels* findByID(intptr_t ID) const;

    /**
     *  If over budget, throw away pixels which are not currently in use until below budget or there
     *  are no more pixels eligible to be thrown away. Mutex must be locked before calling.
     */
    void purgeIfNeeded();

    /**
     *  Purge until below limit. Mutex must be locked before calling.
     */
    void purgeTilAtOrBelow(size_t limit);

    /**
     *  Remove a set of CachedPixels. Mutex must be locked before calling.
     */
    void removePixels(CachedPixels*);
};

#endif // SkLruImageCache_DEFINED
