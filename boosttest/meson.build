
cc = meson.get_compiler('cpp')
boost_dep = cc.find_library('boost_program_options',required: true)
boost_dep_chrono = cc.find_library('boost_chrono',
required: true)
boost_dep_timer = cc.find_library('boost_timer', required:true)
boost_dep_files = cc.find_library('boost_filesystem', required:true)
boost_dep_system = cc.find_library('boost_system', required:true)
boost_dep_iostreams = cc.find_library('boost_iostreams',required:true)
boost_dep_regex = cc.find_library('boost_regex',required:true)

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

executable('multicriteria',
    multicriteria_srcs,
    include_directories:incdir)

executable('highorder',
    highorder_srcs,
    include_directories: incdir)

executable('phoenix',
    phoenix_srcs,
    include_directories: incdir)

executable('posixtime',
    posixtime_srcs,
    include_directories: incdir,
    dependencies: [boost_dep_chrono, boost_dep_timer])

executable('files',
    files_srcs,
    dependencies:[boost_dep_files, boost_dep_system, boost_dep_iostreams, boost_dep_regex]
    )

executable('compression',
    compression_srcs,
    dependencies:[boost_dep_iostreams])