#include <dlfcn.h>
#include <ffi.h>
#include <stdio.h>
#include <stdlib.h>

#include "somelib.h"

int main(int argc, const char* argv[]){
    void* libhandle = dlopen("./libsomelib.so", RTLD_LAZY);
    if(!libhandle){
        fprintf(stderr, "dlopen error: %s\n", dlerror());
    }

    printf("dlopen success: handle %p\n", libhandle);

    // Assume we dont know the prototype of add_data at compile 
    // time, we have to save the output of dlsym in a void* and 
    // then prepare the calling sequence using libffi
    void * add_data_fn = dlsym(libhandle, "add_data");
    char* err = dlerror();
    if(err){
        fprintf(stderr, "dlsym failed; %s\n", err);
        exit(1);
    }
    // Describe the function arguments
    // ffi_type_pointer used for any C pointer
    ffi_type* args[] = { &ffi_type_pointer, &ffi_type_uint};

    // Describe the DataPoint struct to libffi,
    // elements described by a NULL-terminated array of pointers
    // to ffi_type
    ffi_type* dp_elements[] = {&ffi_type_sint, 
            &ffi_type_double, NULL};
    ffi_type dp_type = { .size = 0, .alignment = 0,
                        .type = FFI_TYPE_STRUCT,
                        .elements = dp_elements};

    // Describe the interface of add_data to libffi
    ffi_cif cif;
    ffi_status status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, 
        &dp_type, args);
    if(status != FFI_OK){
        fprintf(stderr, "ffi_prep_cif failed: %d\n", status);
        exit(1);
    }

    DataPoint dp[4] = {{2, 2.2}, {3, 3.3}, {4, 4.4}, {5, 5.5}};
    DataPoint *pdp = dp;
    unsigned nelems = sizeof(dp)/sizeof(DataPoint);
    void* values[] = {&pdp, &nelems};

    printf("Calling add_data via libffi\n");
    DataPoint dout;
    ffi_call(&cif, FFI_FN(add_data_fn), &dout, values);

    printf("dout = {%d, %lf}\n", dout.num, dout.dnum);



    return 0;
}

