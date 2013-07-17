var test = require('./simple_tests.js');

test('first', function() {
    console.log('here I am');
    this('first');
});

test('second', function(first) {
    console.log("second");
    this.assert(first == 'first');
});
