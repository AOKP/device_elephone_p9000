# Package
PRODUCT_PACKAGES += \
    libfmjni \
	FMRadio

# Configuration
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/configs/fmr/mt6627_fm_cust.cfg:system/etc/fmr/mt6627_fm_cust.cfg
