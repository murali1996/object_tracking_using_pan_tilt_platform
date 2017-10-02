Visual Target Tracking and Shooting

- Mechanism Mounted on Controlled Pan-Tilt

Platform


1 Project Abstract

Target tracking is the process of locating a moving object throughout a sequence

of sequential frames. The project aims to design and realize a tracking system

using a camera mounted on a controlled pan-tilt platform. As the target moves

in the frames of the camera, the pan-tilt platform aligns itself in such a way

that the object being tracked remains at the center of the camera’s frame and

thus in its ﬁeld of vision.

To rotate through a range of 180 degrees for both pan as well as tilt, servo

motors are employed. The power required for the motors and their signalling

is done using Arduino UNO micro-controller. Upon sensing and processing the

images obtained, the communication to Arduino is done through ‘USB Serial

Communication’. And the desired angles are obtained using ‘Proportionality

Control’.

In all, the images obtained from the camera will remain the source of feed-

back for the movement of either motors and the controlled pan-tilt platform

tries to keep the object being tracked at the center of the camera’s frame. While

tracking the object, if the object remains within a bounded range for desired

number of frames, a shooting mechanism is initiated with an LED indicating

the probability of a successful shot at the target.

2 Construction of the platform

A raised platform of size 25 ∗ 25mm2 made out of Acrylic is used as a base

for mounting the pan-tilt platform. Two U shaped brackets of dimensions 13 ∗

9 ∗ 9mm3 and 15 ∗ 9 ∗ 9mm3 respectively are mounted so as to achieve an

independent movement of pan and tilt.

3 Hardware Speciﬁcations and Working

3.1 Servo motors

Servos are controlled by sending an electrical pulse of variable width, or pulse

width modulation (PWM), through the control wire. There is a minimum pulse,

a maximum pulse, and a repetition rate. A servo motor can usually only turn

90 degrees in either direction hence accounting for a total of 180 degree move-

ment. The motor’s neutral position is deﬁned as the position where the servo

has the same amount of potential rotation in both clockwise or counterclockwise

direction.

The PWM sent to the motor determines the position of the shaft. Based on

the duration of the pulse sent via the control wire, the rotor will turn to the

desired position. The servo motor expects to see a pulse every 20 milliseconds

(ms) and the length of the pulse will determine how far the motor turns. For

example, a 1.5ms pulse will make the motor turn to the 90-degree position.

Shorter than 1.5ms moves it to 0 degrees, and any longer than 1.5ms will turn

the servo to 180 degrees.

Figure 1: Controlling Servo motor using PWM.

When these servos are commanded to move, they will move to the position

and hold that position. If an external force pushes against the servo while the

servo is holding a position, the servo will resist from moving out of that position.

The maximum amount of force the servo can exert is called the torque rating of

the servo. Servos will not hold their position forever though; the position pulse

must be repeated to instruct the servo to stay in position.

DC servos, although not designed for high current surges, are usually better

suited for smaller applications. Generally speaking, DC motors are less expen-

sive than their AC counterparts. These are also servo motors that have been

built speciﬁcally for continuous rotation, making it easy to get your robot mov-

ing.

The Speciﬁcations are:

![Im1](images/Im1)

• Operating Speed: 4.8v , 6.0v

• PWM Input Range: Pulse Cycle 202ms

• Std Direction: Counter Clockwise / Pulse Traveling 1500 To 1900 microsec

• Operating Speed: Stall Torque: 15 Kg.cm ( 97.21 Oz .in ) At 4.8v, 19

Kg.cm ( 263.86 Oz .in ) At 6.0v

• Operating Speed: 0.22 Sec / 60 At 4.8v, 0.19 Sec / 60 At 6v

• At No Load, weight: 100g

• Special Feature: Heavy Duty Resin Gears, Ball Bearing, Water Resistance

3.2 Logitech C920 HD Pro Webcam (Black)

Record videos in wide screen Full HD 1080p at 30 frames per second. Smooth

video quality and rich colors in real-world environments are produced by Log-

itech Fluid Crystal technology. C920 uses the same type auto-focus motor used

in smart-phone cameras 15-MP snapshots.

3.3 Arduino UNO

• Microcontroller- ATmega328P

• Operating Voltage- 5V

• DC Current per I/O Pin- 20 mA

• Clock Speed-16 MHz

4 Software and the working principle

Clustering of Static-Adaptive Correspondences for Deformable Object Tracking

(CMT) is an award-winning object tracking algorithm, initially published un-

der the name Consensus-based Tracking and Matching of Key-points for Object

Tracking at the Winter Conference on Applications of Computer Vision 2014,

where it received the Best Paper Award. CMT is able to track a wide variety

of object classes in a multitude of scenes without the need of adapting the algo-

rithm to the concrete scenario in any way. A C++ implementation (CppMT) is

freely available under the BSD license, meaning that you can basically do with

the code whatever you want.

The main idea behind CMT is to break down the ‘object of interest’ into tiny

parts, known as key points. In each frame, we try to again ﬁnd the key points

that were already there in the initial selection of the object of interest. We do

this by employing two diﬀerent kind of methods. First, we track key points from

the previous frame to the current frame by estimating what is known as its optic

ﬂow. Second, we match key-points globally by comparing their descriptors. As

both of these methods are error-prone, we employ a novel way of looking for

consensus within the found key points by letting each key-point vote for the

object center, as shown in the following image:

Figure 2: Correspondence Clustering.

Figure 3: Image showing CMT tracker invariant to rotation.

Based on the remaining key-points, the new bounding box is computed and

the process continues. Using a variant of this algorithm, the coordinates for the

center of the object-box are computed in each iteration and are used for the

controller feedback.

5 Serial Communication

Taking the coordinates of the leftmost bottom pixel of the camera frame as (0,0),

the reference (or the desired) object center is obtained as (320,240). Upon ob-

taining the coordinates of the center of the object-box and comparing it with the

![Im2](images/Im2)

![Im3](images/Im3)

reference coordinates, the ‘error’ is obtained. This error is then scaled using cor-

responding ‘Proportionality Gain’ for the movement of rotation of servo shafts.

Nextly, the obtained angles are coded into 3 digit decimal numbers wherein the

hundred’s place designates clockwise or counterclockwise motion and the rest of

the digits specify the angle to be rotated in that direction.

Here, both the motors are signalled independently and through Arduino

USB serial communication at a baud rate of 9600. The baud rate is the rate

at which information is transferred in a communication channel. In the serial

port context, ”9600 baud” means that the serial port is capable of transferring

a maximum of 9600 bits per second. The Arduino then reads the servos’ current

positions and will write to them an updated position.

6 Shooting Mechanism

A laser diode is employed to serve as a shooting tool and is mounted on top of

the camera. There is also a white coloured LED in this aspect of the project.

The white LED will be signalling the probability of a successful shoot while the

Laser diode turns on when this probability is high. The intensity of the white

LED is proportional to the probability of successful shooting. The inputs to

the White LED and the Laser didode are analog PWM signals with 0-5 Volts

mapped to 0-255 in Arduino UNO.

7 Cost Structure

8 Applications and Future scope

In recent years, we have seen an increase in interest for intelligent and eﬃcient

tracking systems for surveillance applications. Many of the proposed techniques

are designed for static camera environments. When the camera is moving, track-

ing moving objects becomes more diﬃcult and many techniques fail to detect

and track the desired targets. The complexity of the problem increases when we

want to track a speciﬁc object in real-time using a Pan and Tilt camera system

![Im4](images/Im4)

(PTU). Keeping the target within the image frame is important in surveillance

applications. The target under observation must be automatically tracked and

retained within the image frame until an action is taken. Such a system will

ﬁnd applications in security-sensitive areas.

The PTU is also useful in Solar Tracking and Solar Renewable Energy Har-

vesting. By optimizing the power consumption of the pan-tilt platform, an

eﬃcient technique for improving solar energy harvesting can be achieved.

The movement of the platform can be further improvised by implementing I

(Integral) and D (Derivative) control schemes for the servo motors. In addition,

the object tracking algorithm employed on the software front can be improved

for better eﬃciency and accuracy.

References

[1] Nebehay, G., Pugfelder, R.: Clustering of Static-Adaptive correspondences

for deformable object tracking. In: Computer Vision and Pattern Recognition,

IEEE (2015) 2784-2791

