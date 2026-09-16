const assert = require('assert');
const fs = require('fs');
const os = require('os');
const path = require('path');

const posixFadvise = require('../');

const POSIX_FADV_DONTNEED = 4;

assert.strictEqual(typeof posixFadvise, 'function',
                   'addon did not export posixFadvise');

const file = path.join(os.tmpdir(), `fcntl-smoke-${process.pid}`);
fs.writeFileSync(file, Buffer.alloc(4096));

const fd = fs.openSync(file, 'r');
try {
    assert.strictEqual(posixFadvise(fd, 0, 4096, POSIX_FADV_DONTNEED), 0);
} finally {
    fs.closeSync(fd);
    fs.unlinkSync(file);
}

// Bad input has to surface as a JS throw rather than a crash in native code.
assert.throws(() => posixFadvise(fd), /Wrong number of arguments/);

console.log(`ok - fcntl addon loads and runs on ${process.platform} ${process.version}`);
