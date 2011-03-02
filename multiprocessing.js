var mp_native = require('./build/default/multiprocessing.node');

function mp(target) {
    this.target = target;
    this.args = arguments.slice(1);
    this.pid = -1;
    this.exitcode = -1; // Has not yet exited
}

mp.prototype.start = function () {
    this.pid = mp._fork();
    if (pid == 0) {
        process.stdin.destroy();
        process.pid = this.pid;
        this.target(this.args);
    }
}

mp.prototype.join = function () {
    
}

mp.prototype.kill = function (sig) {
    return process.kill(this.pid, sig);
}

mp.prototype.exec = function (fn, args) {
    var r = new mp(fn, args);
}

mp.prototype.is_alive = function () {
    
}

exports.multiprocess = mp;
exports.fork = mp_native.fork;
exports.waitpid = mp_native.waitpid;
exports.WNOHANG = mp_native.WNOHANG;
exports.WUNTRACED = mp_native.WUNTRACED;
exports.WIFSIGNALED = mp_native.WIFSIGNALED;
exports.WEXITSTATUS = mp_native.WEXITSTATUS;
exports.WSTOPSIG = mp_native.WSTOPSIG;
exports.WIFCONTINUED = mp_native.WIFCONTINUED;
exports.WIFEXITED = mp_native.WIFEXITED;
exports.WTERMSIG = mp_native.WTERMSIG;
exports.WCOREDUMP = mp_native.WCOREDUMP;
exports.sleep = function () {
    
}
exports.select = function () {
    
}

