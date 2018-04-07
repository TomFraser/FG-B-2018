#define DEBUG true

#define ROBOT 1
#define ATTACK_YELLOW true

#define ALT_SCK 14
#define CAM_TRANSFER_NUM 12
#define LIDAR_SS 49
#define IR_TRANSFER_NUM 4

#define FORWARD_SPEED 100

#define angToRad 0.01745329251
#define radToAng 57.2957795131

#define IMU_ADDRESS 0x68
#define MAG_ADDRESS 0x0C
#define GYRO_FULL_SCALE_2000_DPS 0x18
#define ACC_FULL_SCALE_2_G 0x00
#define IMU_CALIBRATION 500
#define IMU_CALIBRATION_NUM 500
#define IMU_MULTI 2.4
#define GOAL_CUTOFF 60
#define ROTATION_CUTOFF 150

#define BACKSPIN_PIN 6

#define LIGHTGATE_PIN 49
#define KICKER_PIN 28
#define LIGHTGATE_THRESHOLD 0
#define MIN_BALL_CONFIDENCE 0
#define BALL_CONFIDENCE 2

/* Xbee */
#define XBEE_PACKAGE 8
#define XBEE_CONST 128
#define XBEE_START_BYTE 255


/* Coord Calc */
#define ATTACK_GOAL_Y 0
#define ATTACK_GOAL_X 0
#define DEFENSE_GOAL_Y 0
#define DEFENSE_GOAL_X 0


/* Orbit */
#define BIG_DISTANCE 0.00
#define MED_DISTANCE 0.00
#define SHORT_DISTANCE 0.00

/* Direction Controller */
#define SLIDE_ANGLE 80
#define ANGLE_CUTOFF 75
#define SPEED_ON_LINE 0
#define STOP_BOUND 150
#define SPEED_SLIDE 60
#define SPEED_OVER_LINE 60
#define DISTANCE_CUTOFF_GOALIE 0
#define DISTANCE_CUTOFF_ATTACK 10
#define DISTANCE_CUTOFF 0
#define CUTOFF_SPEED_SCALE 1
#define COORD_SPEED_SCALE 2.5
#define SPEED_VAL 80
#define SPIRAL_RATE 1
#define SPIRAL_DIRECION_RATE 0.2
#define SPIRAL_SPEED 60
#define SPIRAL_RESET 0.1
#define SPIRAL_CONST 1000
#define SPIRAL_COORD_DIST 10
#define ENABLE_TARGET_SPIRAL true
#define GOALIE_Y -65
#define GOALIE_X_RANGE 15
#define TARGET_X 0
#define TARGET_Y 0

/* Light */
#define LIGHTSENSOR_NUM 20
#define maxNumClusters 20
#define light1x 1.0
#define light1y 0.0
#define light2x 0.9510565162951535
#define light2y 0.3090169943749474
#define light3x 0.8090169943749475
#define light3y 0.5877852522924731
#define light4x 0.587785252292473
#define light4y 0.8090169943749475
#define light5x 0.30901699437494745
#define light5y 0.9510565162951535
#define light6x 0.0
#define light6y 1.0
#define light7x -0.30901699437494756
#define light7y 0.9510565162951535
#define light8x -0.587785252292473
#define light8y 0.8090169943749475
#define light9x -0.8090169943749473
#define light9y 0.5877852522924732
#define light10x -0.9510565162951535
#define light10y 0.3090169943749475
#define light11x -1.0
#define light11y 0.0
#define light12x -0.9510565162951536
#define light12y -0.3090169943749473
#define light13x -0.8090169943749472
#define light13y -0.5877852522924734
#define light14x -0.5877852522924732
#define light14y -0.8090169943749473
#define light15x -0.30901699437494756
#define light15y -0.9510565162951535
#define light16x 0.0
#define light16y -1.0
#define light17x 0.30901699437494723
#define light17y -0.9510565162951536
#define light18x 0.5877852522924737
#define light18y -0.809016994374947
#define light19x 0.8090169943749473
#define light19y -0.5877852522924734
#define light20x 0.9510565162951535
#define light20y -0.3090169943749476
#define LIGHT_1 A1
#define LIGHT_2 A2
#define LIGHT_3 A3
#define LIGHT_4 A4
#define LIGHT_5 A5
#define LIGHT_6 A6
#define LIGHT_7 A7
#define LIGHT_8 A8
#define LIGHT_9 A9
#define LIGHT_10 A10
#define LIGHT_11 A11
#define LIGHT_12 A12
#define LIGHT_13 A13
#define LIGHT_14 A14
#define LIGHT_15 A15
#define LIGHT_16 A16
#define LIGHT_17 A17
#define LIGHT_18 A18
#define LIGHT_19 A19
#define LIGHT_20 A20
#define NUM_COUNTBACK 2
