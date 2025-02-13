#include <node_api.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>  // for strerror

napi_value PosixFadvise(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 4;
    napi_value args[4];
    
    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to parse arguments");
        return nullptr;
    }

    // Check argument count
    if (argc < 4) {
        napi_throw_type_error(env, nullptr, "Wrong number of arguments");
        return nullptr;
    }

    // Parse fd
    int32_t fd;
    status = napi_get_value_int32(env, args[0], &fd);
    if (status != napi_ok) {
        napi_throw_type_error(env, nullptr, "Argument 0 must be an integer");
        return nullptr;
    }

    // Parse offset
    double offset_double;
    status = napi_get_value_double(env, args[1], &offset_double);
    if (status != napi_ok) {
        napi_throw_type_error(env, nullptr, "Argument 1 must be a number");
        return nullptr;
    }
    off_t offset = (off_t)offset_double;

    // Parse length
    double len_double;
    status = napi_get_value_double(env, args[2], &len_double);
    if (status != napi_ok) {
        napi_throw_type_error(env, nullptr, "Argument 2 must be a number");
        return nullptr;
    }
    off_t len = (off_t)len_double;

    // Parse advice
    uint32_t advice;
    status = napi_get_value_uint32(env, args[3], &advice);
    if (status != napi_ok) {
        napi_throw_type_error(env, nullptr, "Argument 3 must be an unsigned integer");
        return nullptr;
    }

#ifdef __APPLE__
    // No equivalent on macOS
    int res = 0;
#elif _WIN32
    // Skip on Windows
    int res = 0;
#else
    int res = posix_fadvise(fd, offset, len, advice);
    if (res < 0) {
        napi_throw_error(env, nullptr, strerror(errno));
        return nullptr;
    }
#endif

    napi_value result;
    status = napi_create_int32(env, res, &result);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Unable to create return value");
        return nullptr;
    }

    return result;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, nullptr, 0, PosixFadvise, nullptr, &fn);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Unable to wrap native function");
        return nullptr;
    }

    status = napi_set_named_property(env, exports, "posixFadvise", fn);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Unable to populate exports");
        return nullptr;
    }

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)