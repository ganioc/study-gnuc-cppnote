
cc = meson.get_compiler('cpp')
boost_dep = cc.find_library('boost_program_options',required: true)

subdir('src')

incdir=['include']

srcs = ['main.cpp', sources]
option_srcs = [option_sources]

executable('boosttest',
    srcs,
    include_directories: incdir,
    )

executable('boostoption',
    option_srcs,
    include_directories: incdir,
    dependencies: boost_dep)

executable('currentfunc',
    currentfunc_srcs,
    include_directories: incdir)

executable('memmanage',
    memmanage_srcs,
    include_directories: incdir)

executable('str',
    string_srcs,
    include_directories: incdir)

executable('move',
    move_srcs,
    include_directories: incdir)

executable('assign',
    assign_srcs,
    include_directories: incdir)

executable('searchtree',
    searchtree_srcs,
    include_directories:incdir)





