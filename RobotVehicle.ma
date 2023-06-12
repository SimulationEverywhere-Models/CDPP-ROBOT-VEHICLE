[top]
components : RadarSystem MovingSystem

out : Out1
out : Out2
out : Out3
in : In1  
in : In2
in : In3
in : In4 
in : In5 

Link : In1 MS_In1@MovingSystem
Link : In2 RS_In2@RadarSystem
Link : In3 RS_In3@RadarSystem
Link : In4 MS_In3@MovingSystem 
link : In5 MS_In4@MovingSystem 
Link : RS_Out1@RadarSystem Out1
Link : MS_Out2@MovingSystem Out2
Link : MS_Out3@MovingSystem Out3

Link : RS_Out2@RadarSystem MS_In2@MovingSystem
Link : MS_Out1@MovingSystem RS_In1@RadarSystem 

[RadarSystem]
components : sonar1@Sonar1 compass1@Compass1 motor1@Motor1 radarcontroller@RadarController

in : RS_In1 
in : RS_In2
in : RS_In3
out : RS_Out1 
out : RS_Out2 

Link : RS_In1 radar_in1@radarcontroller
Link : RS_In2 sonar1_in1@sonar1
Link : RS_In3 compass1_in2@compass1
Link : motor1_out1@motor1 RS_Out1
Link : radar_out2@radarcontroller RS_Out2

Link : sonar1_out1@sonar1 radar_in2@radarcontroller
Link : compass1_out1@compass1 radar_in3@radarcontroller
Link : radar_out1@radarcontroller motor1_in1@motor1
Link : radar_out3@radarcontroller compass1_in1@compass1
 
[Sonar1]
sonar1Processingtime : 00:00:00:010


[compass1]
compass1processingTime : 00:00:00:010


[Motor1]
stoppreparationtime : 00:00:00:010

[RadarController]
radarprocessingTime : 00:00:00:010
turnprocessingTime : 00:00:06:00

[MovingSystem]
components : motor2@Motor2 motor3@Motor3 movementController@MovementController compass2@Compass2 sonar2@Sonar2

in : MS_In1 
in : MS_In2
in : MS_In3
in : MS_In4
out : MS_Out1
out : MS_Out2 
out : MS_Out3 

Link : MS_In1 move_in1@movementController
Link : MS_In2 move_in2@movementController
Link : MS_In3 compass2_in1@compass2
Link : MS_In4 sonar2_in2@sonar2
Link : move_out1@movementController MS_Out1
Link : motor2_out1@motor2 MS_Out2
Link : motor3_out1@motor3 MS_Out3

Link : compass2_out1@compass2 move_in3@movementController
Link : sonar2_out1@sonar2 move_in4@movementController
Link : move_out2@movementController motor2_in1@motor2
Link : move_out3@movementController motor3_in1@motor3
Link : move_out4@movementController compass2_in2@compass2
Link : move_out5@movementController sonar2_in1@sonar2

[Motor2]
motor2processingtime : 00:00:00:010

[Sonar2]
sonar2processingtime : 00:00:00:010
sonar2objectTime : 00:00:00:200

[Motor3]
motor3processingtime : 00:00:00:010

[compass2]
compass2processingTime : 00:00:00:010

[MovementController]
mcprocessingTime : 00:00:00:010

