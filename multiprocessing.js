var mp = require('./build/default/multiprocessing.node');

function fork(target, args) {
}

fork.prototype.start = function () {
    
}

fork.prototype.join = function () {
    
}

/* SIGINT ... etc. as well as 'exit' */
fork.prototype.on = function (name, fn) {
    
}

r = mp.fork(function () {
    console.log("process.pid: " + process.pid)
});

console.log("worked? parent " + r + ":" + process.pid);
exports.fork = fork;
