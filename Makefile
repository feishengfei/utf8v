#
# utf8v makefile for openwrt
#

include $(TOPDIR)/rules.mk

PKG_NAME:=utf8v
PKG_RELEASE=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)-$(PKG_RELEASE)
include $(INCLUDE_DIR)/package.mk

define Package/utf8v
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=utf8 validation
endef

define Package/utf8v/description
	utf8v
	This library will validate utf8 format
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR);
	$(CP) ./src/* $(PKG_BUILD_DIR);
	$(CP) ./tests/* $(PKG_BUILD_DIR);
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) -Wall \
		-I . \
		-I $(STAGING_DIR)/usr/include "
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libutf8v.so* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/utf8v.h $(1)/usr/include
endef

define Package/utf8v/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libutf8v.so* $(1)/usr/lib/

#	$(INSTALL_DIR) $(1)/usr/bin
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/test_utf8v $(1)/usr/bin

endef

$(eval $(call BuildPackage,utf8v))
