#include <node.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace v8;
using namespace std;
using namespace node;

/* fork! */
class Multiprocessing {
  public:
    static Handle<Value> _fork(const Arguments& args) {
        HandleScope scope;
        pid_t pid;
        
        if (args[0]->IsFunction()) {
            Local<Function> fn = Local<Function>::Cast(args[0]);
            switch(pid = fork()) {
                case -1: /* Error */
                    perror("fork()");
                    _exit(256); /* Looking for a unique exit code... */
                    return Undefined();
                    break;
                case 0: /* Child */
                  {
                    /* update PID */
                    Local<Object> global = v8::Context::GetCurrent()->Global();
                    Local<Value> process_v = global->Get(String::NewSymbol("process"));
                    Local<Object> process = process_v->ToObject();
                    process->Set(String::NewSymbol("process"), Integer::New(getpid()));
                    fn->Call(fn, 0, NULL);
                    _exit(0);
                    break;
                  }
                default: /* Parent */
                    return Integer::New(pid);
            }
        }
        else {
            return Undefined();
        }
    }  
};

extern "C" void
init (Handle<Object> target) {
    HandleScope scope;
    
    NODE_SET_METHOD(target, "_fork", Multiprocessing::_fork);
}

