#include <sys/mount.h>
#include <v8.h>
#include <node.h>

v8::Handle<v8::Value> Mount(const v8::Arguments &args) {
  v8::HandleScope scope;

  if (args.Length() < 3) {
    // TODO: make it raise a proper exception
    return v8::ThrowException(v8::String::New("`mount` needs at least 3 parameters"));
  }
  
  v8::String::Utf8Value device(args[0]->ToString());
  v8::String::Utf8Value path(args[1]->ToString());
  v8::String::Utf8Value type(args[2]->ToString());

  // TODO: expose flag values
  return (mount(*device, *path, *type, 0, NULL) == 0) ? v8::True() : v8::False();
}

v8::Handle<v8::Value> Umount(const v8::Arguments &args) {
  v8::HandleScope scope;

  if (args.Length() < 1) {
    return v8::ThrowException(v8::String::New("`umount` needs at least 1 parameter"));
  }

  v8::String::Utf8Value path(args[0]->ToString());

  return (umount(*path) == 0) ? v8::True() : v8::False();
}

void init (v8::Handle<v8::Object> target) {
  NODE_SET_METHOD(target, "mount", Mount);
  NODE_SET_METHOD(target, "umount", Umount);
}
NODE_MODULE(mount, init)

