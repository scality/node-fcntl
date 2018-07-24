var fs = require('fs');
var posixFadvise = require('../');

fs.open('foo', 'w+', function(err, fd) {
    if (err) {
        throw err;
    }

    ret = posixFadvise(fd, 0, 10, 4);
    console.log('posixFadvise ret: ' + ret);
    fs.close(fd);
});
