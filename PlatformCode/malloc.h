//
//  malloc.h
//  PlatformCode
//
//  Created by Bill on 8/8/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef PlatformCode_malloc_h
#define PlatformCode_malloc_h


struct MallocInfo {

        uint16_t uordblks;
};


MallocInfo mallinfo();
#endif
