

RECURSE(
    small
    medium
    large
)

IF (HAVE_CUDA)
    RECURSE(
    medium/gpu
)
ENDIF()
