# Permission
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/android.hardware.camera.xml:system/etc/permissions/android.hardware.camera.xml

# Package
PRODUCT_PACKAGES += \
    Snap

# Configuration
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/camera/camerasize.xml:system/etc/camerasize.xml
    
