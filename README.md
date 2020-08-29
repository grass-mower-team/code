# code
# hello, in this repository me and Nicola Bodei are going to make a grass mower code to implement on an arduino based grassmower. 
# to begin with, the testing board is an arduino mega 2560, with a chinese serial chip(ch340g). 
# the already existing wiring is composed by 4 realys to control the motor direction, pins 4 & 5 for motor sx and 8 & 9 for motor dx (note both has to be in the same #logic state in order to move) and 2 mosfets control the speed by a pwm signal, pins 5 for motor sx and 6 for motor dx
# 2 magnetic sensor with 13 revolution per rotation are places on the whells s encoders, pin A15 for wheel dx and A14 for wheel sx.
# A digial compass will be added with I2C protocol to have a feedback of the robot direction. 
