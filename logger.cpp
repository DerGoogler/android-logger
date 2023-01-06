#include <android/log.h>
#include <napi.h>

class __native_logger : public Napi::ObjectWrap<__native_logger> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    __native_logger(const Napi::CallbackInfo& info);
    static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);

  private:
    double _value;
    Napi::Value d(const Napi::CallbackInfo& info);
    Napi::Value e(const Napi::CallbackInfo& info);
    Napi::Value i(const Napi::CallbackInfo& info);
    Napi::Value v(const Napi::CallbackInfo& info);
    Napi::Value w(const Napi::CallbackInfo& info);
};

Napi::Object __native_logger::Init(Napi::Env env, Napi::Object exports) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "__native_logger", {
       InstanceMethod<&__native_logger::d>("d", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
       InstanceMethod<&__native_logger::e>("e", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
       InstanceMethod<&__native_logger::i>("i", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
       InstanceMethod<&__native_logger::v>("v", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
       InstanceMethod<&__native_logger::w>("w", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
       StaticMethod<&__native_logger::CreateNewItem>("CreateNewItem", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();

    // Create a persistent reference to the class constructor. This will allow
    // a function called on a class prototype and a function
    // called on instance of a class to be distinguished from each other.
    *constructor = Napi::Persistent(func);
    exports.Set("__native_logger", func);

    // Store the constructor as the add-on instance data. This will allow this
    // add-on to support multiple instances of itself running on multiple worker
    // threads, as well as multiple instances of itself running in different
    // contexts on the same thread.
    //
    // By default, the value set on the environment here will be destroyed when
    // the add-on is unloaded using the `delete` operator, but it is also
    // possible to supply a custom deleter.
    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

__native_logger::__native_logger(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<__native_logger>(info) {
  Napi::Env env = info.Env();
  // ...
  Napi::Number value = info[0].As<Napi::Number>();
  this->_value = value.DoubleValue();
}

Napi::Value __native_logger::d(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    std::string tag = info[0].As<Napi::String>();
    std::string data = info[1].As<Napi::String>();
    __android_log_write(ANDROID_LOG_DEBUG, tag.c_str(), data.c_str());
    return env.Null();
}

Napi::Value __native_logger::e(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    std::string tag = info[0].As<Napi::String>();
    std::string data = info[1].As<Napi::String>();
    __android_log_write(ANDROID_LOG_ERROR, tag.c_str(), data.c_str());
    return env.Null();
}

Napi::Value __native_logger::i(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    std::string tag = info[0].As<Napi::String>();
    std::string data = info[1].As<Napi::String>();
    __android_log_write(ANDROID_LOG_INFO, tag.c_str(), data.c_str());
    return env.Null();
}

Napi::Value __native_logger::v(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    std::string tag = info[0].As<Napi::String>();
    std::string data = info[1].As<Napi::String>();
    __android_log_write(ANDROID_LOG_VERBOSE, tag.c_str(), data.c_str());
    return env.Null();
}

Napi::Value __native_logger::w(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    std::string tag = info[0].As<Napi::String>();
    std::string data = info[1].As<Napi::String>();
    __android_log_write(ANDROID_LOG_WARN, tag.c_str(), data.c_str());
    return env.Null();
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    __native_logger::Init(env, exports);
    return exports;
}

// Create a new item using the constructor stored during Init.
Napi::Value __native_logger::CreateNewItem(const Napi::CallbackInfo& info) {
  // Retrieve the instance data we stored during `Init()`. We only stored the
  // constructor there, so we retrieve it here to create a new instance of the
  // JS class the constructor represents.
  Napi::FunctionReference* constructor =
      info.Env().GetInstanceData<Napi::FunctionReference>();
  return constructor->New({ Napi::Number::New(info.Env(), 42) });
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

/*
#include <assert.h>
#include <node_api.h>
#include <stdio.h>

static napi_value Log(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 3;
	napi_value args[3];
	status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
	assert(status == napi_ok);

	if (argc < 3)
	{
		napi_throw_type_error(env, NULL, "Wrong number of arguments");
		return NULL;
	}

	napi_valuetype valuetype0;
	status = napi_typeof(env, args[2], &valuetype0);
	assert(status == napi_ok);

	napi_valuetype valuetype1;
	status = napi_typeof(env, args[1], &valuetype1);
	assert(status == napi_ok);

	napi_valuetype valuetype2;
	status = napi_typeof(env, args[0], &valuetype2);
	assert(status == napi_ok);


	if (valuetype0 != napi_string || valuetype1 != napi_string || valuetype2 != napi_number)
	{
		napi_throw_type_error(env, NULL, "Wrong arguments");
		return NULL;
	}

	char tag[1024];
	size_t tag_len;
	if (napi_get_value_string_utf8(env, args[1], (char *)&tag, 1024, &tag_len) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "Expected string");
		return NULL;
	}

	char data[1024];
	size_t data_len;
	if (napi_get_value_string_utf8(env, args[2], (char *)&data, 1024, &data_len) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "Expected string");
		return NULL;
	}

	double level;
	if (napi_get_value_double(env, args[0], &level) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "Expected number");
		return NULL;
	}

	switch ((int)level)
	{
	case 0:
		__android_log_write(ANDROID_LOG_DEFAULT, tag, data);
		break;
	case 1:
		__android_log_write(ANDROID_LOG_VERBOSE, tag, data);
		break;
	case 2:
		__android_log_write(ANDROID_LOG_DEBUG, tag, data);
		break;
	case 3:
		__android_log_write(ANDROID_LOG_INFO, tag, data);
		break;
	case 4:
		__android_log_write(ANDROID_LOG_WARN, tag, data);
		break;
	case 5:
		__android_log_write(ANDROID_LOG_ERROR, tag, data);
		break;
	case 6:
		__android_log_write(ANDROID_LOG_FATAL, tag, data);
		break;
	case 7:
		__android_log_write(ANDROID_LOG_SILENT, tag, data);
		break;
	default:
		__android_log_write(ANDROID_LOG_DEFAULT, tag, data);
	}

	return NULL;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("__native_log", Log);
	status = napi_define_properties(env, exports, 1, &addDescriptor);
	assert(status == napi_ok);
	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
 */