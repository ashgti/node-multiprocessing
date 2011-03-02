var mp = require('../multiprocessing.js');
var r = mp.fork(); 

if (r == 0) {
    console.log("process.pid: " + process.pid);
    
    setTimeout(function () {
        process.exit(0);
    }, 3500);
    
    while(1) { }
}

console.log("worked? parent " + r + ":" + process.pid);

var timer;

timer = setInterval(function () {
    console.log('entering timer r: ' + r);
    var got = mp.waitpid(r, mp.WNOHANG);
    
    console.log("a: " + got[0] + " b:" + got[1]);
    if (got[0] == process.pid) {
        clearInterval(timer);
        if (mp.WIFSIGNALED(got[1])) {
            console.log("a: " + (-mp.WTERMSIG(got[1])));
            console.log('finished');
        }
        else {
            console.log("b: " + os.WEXITSTATUS(got[1]));
        }
    }
    console.log('exiting timer');
}, 2000);
