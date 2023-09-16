
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

executable('matrix_mul',
    matrix_mult_srcs,
    include_directories:incdir)

executable('matrix_mul_thread',
    matrix_mult_thread_srcs,
    include_directories: incdir)

executable('llist',
    llist_srcs,
    include_directories: incdir)


executable('process_mutex',
    process_shared_mutex_srcs,
    include_directories: incdir)

executable('cvsimple',
    cvsimple_srcs,
    include_directories:incdir)

    