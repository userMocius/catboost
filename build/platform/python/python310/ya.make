RESOURCES_LIBRARY()



INCLUDE(${ARCADIA_ROOT}/build/platform/python/resources.inc)

DECLARE_EXTERNAL_HOST_RESOURCES_BUNDLE(
    PYTHON310
    ${PYTHON310_DARWIN} FOR DARWIN
    ${PYTHON310_DARWIN_ARM64} FOR DARWIN-ARM64
    ${PYTHON310_LINUX} FOR LINUX
    ${PYTHON310_WINDOWS} FOR WIN32
)

IF (OS_LINUX)
    DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON310 ${PYTHON310_LINUX})
ELSEIF (OS_DARWIN)
    IF (ARCH_ARM64)
        DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON310 ${PYTHON310_DARWIN_ARM64})
    ELSEIF(ARCH_X86_64)
        DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON310 ${PYTHON310_DARWIN})
    ENDIF()
ELSEIF (OS_WINDOWS)
    DECLARE_EXTERNAL_RESOURCE(EXTERNAL_PYTHON310 ${PYTHON310_WINDOWS})
ENDIF()

END()
