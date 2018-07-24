var posixFadvise = require('bindings')('fcntl.node').posixFadvise;

module.exports = posixFadvise;
