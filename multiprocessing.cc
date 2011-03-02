#include <node.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>

using namespace v8;
using namespace std;
using namespace node;

namespace multiprocessing {
/* fork! */
static Handle<Value> _fork(const Arguments& args) {
    HandleScope scope;
    pid_t pid;

    Local<Function> fn = Local<Function>::Cast(args[0]);
    switch(pid = fork()) {
        case -1: /* Error */
            perror("fork()");
            _exit(256); /* Looking for a unique exit code... */
            return Undefined();
            break;
        case 0: /* Child */
            return Integer::New(pid);
            break;
        default: /* Parent */
            return Integer::New(pid);
    }
}

static Handle<Value> _waitpid(const Arguments& args) {
    HandleScope scope;
    pid_t pid;
    int status, r, v;
    Local<Array> results;
    
    if (args.Length() < 2 ||
        !args[0]->IsInt32() ||
        !args[1]->IsInt32()) {
      return ThrowException(Exception::Error(String::New("Bad argument.")));
    }
    
    pid = args[0]->Int32Value();
    v   = args[1]->Int32Value();
    r = waitpid(pid, &status, v);
    if (r == -1) {
        /* Error handling */
        return ThrowException(ErrnoException(errno, "waitpid"));
    }
    else {
        results = Array::New(2);
        results->Set(0, Integer::New(r));
        results->Set(1, Integer::New(status));
        return results;
    }
}

#ifdef WIFSIGNALED
static Handle<Value> _WIFSIGNALED(const Arguments& args) {
    HandleScope scope;
    if (args.Length() < 1) {
        return ThrowException(Exception::Error(String::New("Bad argument.")));
    }
    int val = args[0]->Int32Value();
    return Boolean::New(WIFSIGNALED(val));
}
#endif
#ifdef WEXITSTATUS
static Handle<Value> _WEXITSTATUS(const Arguments& args) {
    if (args.Length() < 1) {
        return ThrowException(Exception::Error(String::New("Bad argument.")));
    }
    int val = args[0]->Int32Value();
    return Boolean::New(WEXITSTATUS(val));
}
#endif
#ifdef WSTOPSIG
static Handle<Value> _WSTOPSIG(const Arguments& args) {
    if (args.Length() < 1) {
        return ThrowException(Exception::Error(String::New("Bad argument.")));
    }
    int val = args[0]->Int32Value();
    return Boolean::New(WSTOPSIG(val));
}
#endif
#ifdef WIFCONTINUED
static Handle<Value> _WIFCONTINUED(const Arguments& args) {
    if (args.Length() < 1) {
        return ThrowException(Exception::Error(String::New("Bad argument.")));
    }
    int val = args[0]->Int32Value();
    return Boolean::New(WIFCONTINUED(val));
}
#endif
#ifdef WIFEXITED
static Handle<Value> _WIFEXITED(const Arguments& args) {
    if (args.Length() < 1) {
        return ThrowException(Exception::Error(String::New("Bad argument.")));
    }
    int val = args[0]->Int32Value();
    return Boolean::New(WIFEXITED(val));
}
#endif
#ifdef WTERMSIG
static Handle<Value> _WTERMSIG(const Arguments& args) {
    if (args.Length() < 1) {
        return ThrowException(Exception::Error(String::New("Bad argument.")));
    }
    int val = args[0]->Int32Value();
    return Boolean::New(WTERMSIG(val));
}
#endif
#ifdef WCOREDUMP
static Handle<Value> _WCOREDUMP(const Arguments& args) {
    if (args.Length() < 1) {
        return ThrowException(Exception::Error(String::New("Bad argument.")));
    }
    int val = args[0]->Int32Value();
    return Boolean::New(WCOREDUMP(val));
}
#endif

} /* end namespace multiprocessing */

extern "C" void
init (Handle<Object> target) {
    HandleScope scope;
    
    /* Define some constants */
#ifdef WNOHANG
    NODE_DEFINE_CONSTANT(target, WNOHANG);
#endif
#ifdef WUNTRACED
    NODE_DEFINE_CONSTANT(target, WUNTRACED);
#endif

#ifdef WIFSIGNALED
    NODE_SET_METHOD(target, "WIFSIGNALED", multiprocessing::_WIFSIGNALED);
#endif
#ifdef WEXITSTATUS
    NODE_SET_METHOD(target, "WEXITSTATUS", multiprocessing::_WEXITSTATUS);
#endif                       
#ifdef WSTOPSIG              
    NODE_SET_METHOD(target, "WSTOPSIG", multiprocessing::_WSTOPSIG);
#endif                       
#ifdef WIFCONTINUED          
    NODE_SET_METHOD(target, "WIFCONTINUED", multiprocessing::_WIFCONTINUED);
#endif                       
#ifdef WIFEXITED             
    NODE_SET_METHOD(target, "WIFEXITED", multiprocessing::_WIFEXITED);
#endif                       
#ifdef WTERMSIG              
    NODE_SET_METHOD(target, "WTERMSIG", multiprocessing::_WTERMSIG);
#endif                       
#ifdef WCOREDUMP             
    NODE_SET_METHOD(target, "WCOREDUMP", multiprocessing::_WCOREDUMP);
#endif
    
    NODE_SET_METHOD(target, "fork", multiprocessing::_fork);
    NODE_SET_METHOD(target, "waitpid", multiprocessing::_waitpid);
}

