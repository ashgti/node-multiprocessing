var mp = require('../multiprocessing.js');
var r = mp.fork();

if (r == 0) {
    console.log("child process.pid: " + process.pid);
    var finished = false;
    var timer = (function() {
        return setTimeout(function () {
            console.log("callback called!!!?");
            finished = true;
            console.log("Dead... now");
            process.exit(0);
        }, 3500);
    })();
    
    for (var x in timer) {
        console.log("x:" +x+ " :v: " +timer[x]);
    }
    console.log("Timer id: " + timer);
    console.log("started child timer?");
}
else {
    console.log("worked? child is: " + r + " parent is:" + process.pid);

    var timer;
    timer = setInterval(function () {
        console.log('entering timer r: ' + r);
        var got = mp.waitpid(-1, mp.WNOHANG);
    
        console.log("a: " + got[0] + " b:" + got[1]);
        if (got[0] == 0) {
            clearInterval(timer);
            if (mp.WIFSIGNALED(got[1])) {
                console.log("a: " + (-mp.WTERMSIG(got[1])));
                console.log('finished');
            }
            else if (mp.WIFEXITED(got[1])) {
                console.log("b: " + os.WEXITSTATUS(got[1]));
            }
        }
        console.log('exiting timer');
    }, 2000);
}

console.log("Finished if");
