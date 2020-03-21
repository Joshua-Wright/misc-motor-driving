# misc-motor-driving
messing around with various ways to drive motors

## reference information
* [Arduino programming reference](https://www.arduino.cc/reference/en/#structure)
* [arduino pro micro sparkfun info page](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/hardware-overview-pro-micro)

# encoders

## quadrature encoders
or, rather, incremental encoders with quadrature signal output.

Wikipedia has some useful information for implementing a decoder:
* https://en.wikipedia.org/wiki/Incremental_encoder#Quadrature_outputs
* https://en.wikipedia.org/wiki/Incremental_encoder#State_transitions

hybrid disk encoder https://github.com/JamesNewton/HybridDiskEncoder
used on dexter robot arm https://github.com/HaddingtonDynamics/Dexter/wiki/Encoders
* https://hackaday.com/2018/11/15/an-in-depth-look-at-dexter-the-robotic-arm/





# Brushed DC motors

there's some good looking encoder gearmotors on amazon for relatively cheap:
https://www.amazon.com/gp/product/B07BRLW82M






# Brushless DC Motors

these are now super cheap, thanks to hobby drones. But can such motors do decent torque? and can they be driven with an arduino, or do I need to buy an odrive?

resources:
* https://www.instructables.com/id/Make-Your-Own-ESC/
* http://www.electronoobs.com/eng_circuitos_tut4.php
* https://hackaday.io/project/160585-motor-as-encoder
* https://www.youtube.com/watch?v=8LXPcJD6hEA
* https://www.youtube.com/watch?v=erppWLMzw8I

## BLDC servo controllers
* https://hackaday.io/project/169905-esp-32-bldc-robot-actuator-controller
* https://hackaday.io/project/19370-akarin-servo
* https://hackaday.io/project/157586-powerful-brushless-dc-motor-drivercontroller
* odrive https://odriverobotics.com/
* https://hackaday.com/2016/02/04/adding-position-control-to-an-open-source-brushless-motor-driver/ https://github.com/vedderb?tab=repositories

## BLDC non-servo drivers
* https://hackaday.io/project/7171-tiny-bldc
* https://hackaday.io/project/168324-sdrive-small-bldc-driver
* https://hackaday.io/project/167173-custom-bldc-motor-board-using-fpga



# PID
https://platformio.org/lib/show/2/PID
https://platformio.org/lib/show/3/PID-AutoTune
