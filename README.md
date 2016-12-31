# planets

**This is old and buggy! Take a look at [github.com/tmalthouse/trajectory]() instead!**

A SDL-based nbody simulator with timewarp and savefile loading (you can save a system or edit it in a text editor.)

It's still very much a WIP, with a ton of things that still need to be added/changed.

It's only set up for XCode right now, I'll write a makefile once it's a bit more complete. It requires the [`darray.h`](https://github.com/tmalthouse/darray-generic) header and the `libSDL2`, `libSDL2_img`, and `libSDL2_ttf` libraries to compile (the latter of which are all available via homewbrew.)

Use the output `system.sys` as a guide for modifying the solar system. The parser is SUPER finnicky right now, so it needs to be formatted just like the example. There's no limit to the number of bodies though.

