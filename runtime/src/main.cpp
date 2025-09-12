#include <coreclr/nethost.h>

#include <coreclr/hostfxr.h>
#include <coreclr/coreclr_delegates.h>

#ifdef _WIN32
#include <Windows.h>
#endif

hostfxr_initialize_for_runtime_config_fn init_for_config_fptr;

bool load_hostfxr(const char_t *assembly_path) {
    get_hostfxr_parameters params{ sizeof(get_hostfxr_parameters), assembly_path, nullptr };
    
    char_t buffer[260];
    size_t buffer_size = sizeof(buffer) / sizeof(char_t);

    int rc = get_hostfxr_path(buffer, &buffer_size, &params);

    if (rc != 0) {
        return false;
    }

    #ifdef _WIN32
    void *lib = (void*)LoadLibraryW(buffer);
    init_for_config_fptr = (hostfxr_initialize_for_runtime_config_fn)GetProcAddress((HMODULE)lib, "hostfxr_initialize_for_runtime_config");
    #endif

    return init_for_config_fptr;
}