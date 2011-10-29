var binding;

try {
  binding = require('../build/default/mount');
}
catch (e) {
  binding = require('../build/Release/mount');
}

module.exports = binding;

