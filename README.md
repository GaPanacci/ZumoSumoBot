# ZumoSumoBot

## Overview
The Zumo32U4 Sumo Bot is a compact, Arduino-compatible robot designed primarily for participation in sumo wrestling competitions. Leveraging the Zumo32U4's line sensors, motors, and a robust set of features, this autonomous robot navigates within the sumo ring, strategically avoiding the ring's edges while seeking and pushing opponents out of the ring.

## Features
- **Edge Detection:** Utilizes line sensors to prevent exiting the sumo ring, enhancing its competitive edge.
- **Randomized Turning:** Incorporates a random turning mechanism to disengage from edges and avoid being trapped in corners.
- **Simple Control Interface:** Starts, pauses, and resumes operation with the press of a button, allowing for easy user interaction.
- **Configurable Speeds and Timings:** Offers adjustable parameters for movement speeds and action durations, providing flexibility in strategy and response.

## Prerequisites
Before starting with the Zumo32U4 Sumo Bot, ensure you have:
- A Zumo32U4 Robot Kit assembled according to the manufacturer's instructions.
- The Arduino IDE installed on your computer.

## Setup and Installation
1. **Assemble the Zumo32U4 Robot:**
   - Follow the assembly instructions provided by Pololu or the kit documentation to build your Zumo32U4 robot.

2. **Install the Arduino IDE and Libraries:**
   - Download and install the Arduino IDE.
   - Install the Zumo32U4 libraries using the Library Manager in the Arduino IDE.

3. **Load the Code:**
   - Connect the Zumo32U4 to your computer via USB.
   - Open the Arduino IDE, and load the provided script.
   - Select the correct board and port from the Tools menu.
   - Upload the script to the Zumo32U4 robot.

## Usage
1. **Prepare the Robot:**
   - Ensure the robot is charged and placed within a sumo ring or a designated practice area.

2. **Start the Robot:**
   - Turn the power switch to ON. The robot will enter a paused state, displaying "Paused" on the OLED screen.

3. **Initiate Sumo Mode:**
   - Press the A button to start the countdown. After the countdown, the robot will actively seek to stay within the ring and engage opponents.

## Important Notes
- The robot's behavior, including movement speeds and reaction times, can be customized within the script to suit different strategies and ring conditions.
- Safety first: Always ensure the area around the sumo ring is clear of obstructions and bystanders are at a safe distance.

## Contribution
Your contributions and suggestions are highly appreciated. Feel free to fork the repository, experiment with different strategies, and share your enhancements by submitting a pull request.

## Disclaimer
The Zumo32U4 Sumo Bot project is provided for educational and entertainment purposes. It's important to use it responsibly and ethically in competitions. The creators assume no responsibility for any damage or loss resulting from its use.

## License
This project is open-source and available under the MIT License. See the LICENSE file for more details.
