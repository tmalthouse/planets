//
//  debug.h
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef debug_h
#define debug_h

#ifdef DEBUG
#define dprintf(...) printf(__VA_ARGS__);
#else
#define dprintf(...)
#endif

#undef VERBOSE_DEBUG

#ifdef VERBOSE_DEBUG
#define vdprintf(...) dprintf(__VA_ARGS__)
#else
#define vdprintf(...)
#endif

#endif /* debug_h */
