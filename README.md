# Rocket-Shop

This is the software design area for Iowa State's Rocketry club, Rocket-Shop. Our rocket must carry a payload to a target altitude of 30,000ft. Score is determined by how close a team's rocket can get to the target altitude, among other things.  It is the job of the Avionics team to control actuation of the airbrakes and locate the rocket after launch.

# Airbrakes

The board that is located above the motor near the mechanical airbrakes, that needs to have the sensors and logic to decide when to actuate the airbrakes.

# Telemetry

The board that is located in the nosecone of the rocket in an RF bay. This board will be used to locate the rocket after launch, so it will need a GPS and radio to receive location data and send it to the base station so the rocket can be recovered.
