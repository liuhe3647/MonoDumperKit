//
//  Mono.cpp
//
//  Created by MJ (Ruit) on 2/3/19.
//

#include "Mono.h"


using Mono::MonoImage;
using Mono::MonoAssembly;
using Mono::MonoFunc;


MonoImage *(*Mono::mono_assembly_get_image)(MonoAssembly *) = NULL;
const char *(*Mono::mono_image_get_name)(MonoImage *) = NULL;
void (*Mono::mono_assembly_foreach)(MonoFunc, void *) = NULL;


#define InitMonoFunc(x, y) *(void **)(&y) = (void *)dlsym(x, #y)
#define GetMonoFunc(x, y) (void *)dlsym(x, #y)


void Mono::initialize_exports() {
    void *mono = dlopen("libmono.so", RTLD_LAZY);
    if (!mono) {
        LOGD("%s", dlerror());
        return;
    }

    LOGD("Mono handle: %p", mono);

    InitMonoFunc(mono, mono_assembly_get_image);
    InitMonoFunc(mono, mono_image_get_name);
    InitMonoFunc(mono, mono_assembly_foreach);
}