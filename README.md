# AppleJPEGDriver-memleak

<!-- Brandon Azad -->

The AppleJPEGDriver kernel extension on iOS can be used to leak kernel memory, leading to local
denial of service.

This issue has been confirmed on iOS 10.1.1 and iOS 11.2 Beta.

## The vulnerability

The AppleJPEGDriverUserClient external methods do not properly handle error conditions resulting
from invalid client data, leading to a kernel memory leak in zone kalloc.512. This can be used to
degrade system performance (iOS 11) or panic the kernel (iOS 10).

All 4 (nontrivial) external methods are vulnerable.

## License

The AppleJPEGDriver-memleak code is released into the public domain. As a courtesy I ask that if
you reference or use any of this code you attribute it to me.
