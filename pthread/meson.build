
# language('c')

subdir('src')

incdir = ['include']

srcs = ['main.c', sources]




executable('pthread',
    srcs,
    include_directories: incdir,
    )

executable('exit_status',
    exit_srcs,
    include_directories: incdir
    )

executable('atm_srv_serial',
    atm_svr_srcs,
    include_directories: incdir
    )

executable('atm_svr',
    atm_svr_thread,
    include_directories:incdir)
    