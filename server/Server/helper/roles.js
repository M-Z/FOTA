const AccessControl = require("accesscontrol");
const ac = new AccessControl();

exports.roles = (function() {
  // CRUD actions for each user role

  ac.grant("Developer")
    // Create

    // Read
    .readOwn("team")        // Read his team name, and firmwares
    .readOwn("profile")     // See his own profile

    // Update
    .updateOwn("profile")   // Add own name/image etc
    .updateOwn("team", ['firmware'])   // edit firmware
    // Delete

  ac.grant("Leader")
    .extend("Developer")
    // Create
    .createOwn('team', ['firmware'])  // Add team firmware
    // Read

    // Update

    // Delete
    .deleteOwn("team", ['firmware'])  // Delete team firmware

  ac.grant("Admin")
    .extend("Developer")
    .extend("Leader")

    // Create
    .createAny("profile")   //  Add team member
    .createAny("team")      //  Add team

    // Read
    .readAny("team")
    // Update

    // Delete
    .deleteAny("profile")
    .deleteAny("team")

  return ac;
})();
