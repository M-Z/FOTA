const crypto = require('crypto');

function hashFile(options) {
  let hash = "",
    output = "";

  let contents = options.contents.trim();
  // Divide array into n chunks
  contents = contents.match(new RegExp(options.re, "g"));

  for (let i = 0, l = contents.length; i < l; i++) {
    // Add EOF
    if (i + 1 == l) {
      contents[i] += '\r\n';
    }
    hash = crypto.createHash(options.hashType)
      .update(contents[i])
      .digest("hex").toLowerCase();

    output += hash + contents[i]; // Add hash before data in header
  }

  return output;
}

module.exports = hashFile
