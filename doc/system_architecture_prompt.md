Can you create a markdown document for me that contains a software system architecture.

I see a few high level topics
Summary
Workflow
User Management
Data Collection
Development Environment

A few sections that contain very specific information
Messages
Services
Web Components
Container Hosting

Summary
Discuss that this robotic solution will help workings complete there job in a safer and more efficient manner.  It will include industrial robotic components that are driven by a custom software solution.

In addition to driving the workflow the system software will include user management and data collection.  The data collection will be geared towards reporting on ROI, understanding the performance of the solution (at many customer installations), and could be used for tuning to be included in future software releases.

A diagram showing the system components and how they communicate should be included.
This diagram should only include the following components
System State Machine (runs in Docker Container 1)
System Monitor (runs in Docker Container 1)
User Interface (runs in Docker Container 2)

System State Machine <-> System Monitor : The System Manager will publish DDS Message(s) that the System Monitor will listen for.  The System Monitor will make a service call to the System State Machine.  These two components will be running in the same Docker container.

User Interface <-> System State Machine : The User Interface will communicate with the System State Machine making service calls.

User Interface <-> System Monitor : The User Interface will communicate with the System Monitor by publishing DDS messages.


Workflow
The workflow will mainly be supported by the System State Machine.  This component will be responsible for handling state transitions based on system inputs.  Inputs will be from the user (UI), and the system itself (sensors).  In addition to handle input and driving outpus the System State Machine will be responsible for making sure the System Monitor is up and running.

The System Monitor component will be responsible for making sure that all of the critical system components (ROS2 nodes) are running.  It will do this by monitoring for a Heartbeat message for each of the components in the system.  The System Monitor will have a list of components it expects to be running.  The System Monitor will have access to the Software Estop and will be able to shutdown the system if all of the critical components are not in a safe state.  It will first try and alert the System State Machine of the conern and allow it to safely shut down the system, but if this does not happen in a timeline manner the System Monitor will initiate the Emergency Stop.

The System Controller will send its heartbeat, as all other components will, via a DDS message.  The System Controller will request the System State Machine to initiate an Emergency stop via a service call.
