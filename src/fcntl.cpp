#include <errno.h>
#include <fcntl.h>
#include "nan.h"

using namespace v8;
using namespace node;

NAN_METHOD(PosixFadvise) {
#ifdef __APPLE__
    // No equivalent on MACOSX
    info.GetReturnValue().Set(0);
#else
    Nan::HandleScope scope;

    Local<Object> buf;
    int length = info.Length();

    assert(length == 4);

    if (!info[0]->IsInt32()) {
        Nan::ThrowTypeError("Argument 0 Must be an Integer");
    }

    if (!info[1]->IsNumber()) {
        Nan::ThrowTypeError("Argument 1 Must be a Number");
    }

    if (!info[2]->IsNumber()) {
      Nan::ThrowTypeError("Argument 1 Must be a Number");
    }

    if (!info[3]->IsUint32()) {
      Nan::ThrowTypeError("Argument 1 Must be an Integer");
    }

    int fd = info[0]->Int32Value(Nan::GetCurrentContext()).FromJust();
    off_t offset = (off_t) info[1]->NumberValue(Nan::GetCurrentContext()).FromJust();
    off_t len = (off_t) info[2]->NumberValue(Nan::GetCurrentContext()).FromJust();
    unsigned long advice = info[3]->IntegerValue(Nan::GetCurrentContext()).FromJust();

    int res = posix_fadvise(fd, offset, len, advice);
    if (res < 0) {
        return Nan::ThrowError(Nan::ErrnoException(errno, "posix_fadvise", nullptr, nullptr));
    }

    info.GetReturnValue().Set(res);
#endif
}

void InitAll(Local<Object> exports) {
  Nan::SetMethod(exports, "posixFadvise", PosixFadvise);
}

NODE_MODULE(fcntl, InitAll)
