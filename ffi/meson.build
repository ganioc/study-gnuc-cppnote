# ffi 

subdir('src')

incdir = ['include']

srcs = ['main.c']




lib1 = library('somelib',
    [sources],
    include_directories: incdir,
    version: '1.0.0',
    soversion: '0')


executable('appffi',
    srcs,
    include_directories: incdir,
    link_with: lib1
    )

