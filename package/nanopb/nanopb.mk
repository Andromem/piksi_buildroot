NANOPB_VERSION = 821747f0b5ef1034335410f5e3e82c87f7678c2a
NANOPB_SITE = $(call github,nanopb,nanopb,$(NANOPB_VERSION))
NANOPB_LICENSE = BSD-3c
NANOPB_LICENSE_FILES = LICENSE.txt
NANOPB_INSTALL_STAGING = YES
$(eval $(cmake-package))