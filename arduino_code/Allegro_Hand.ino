#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

ros::NodeHandle nh;

sensor_msgs::JointState msgJoint;

float analogReading1, analogReading2, analogReading3, analogReading4;

float pos[]=
{
  0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0};

ros::Publisher Joints("/allegroHand_0/joint_states", &msgJoint);

void setup() {
  Serial.begin(57600);
  mySerial.begin(9600);

  nh.initNode();
  nh.advertise(Joints);

  msgJoint.position_length = 16;
}

void loop() {
  if (mySerial.available() >= 27) {
    if (mySerial.read() == 0x7E) {
      for (int i = 1; i < 19; i++) {
        byte discardByte = mySerial.read();
      }
      int analogMSB1      = mySerial.read();
      int analogLSB1      = mySerial.read();
      analogReading1  = analogLSB1 + (analogMSB1 * 256);

      int analogMSB2      = mySerial.read();
      int analogLSB2      = mySerial.read();
      analogReading2  = analogLSB2 + (analogMSB2 * 256);

      int analogMSB3      = mySerial.read();
      int analogLSB3      = mySerial.read();
      analogReading3  = analogLSB3 + (analogMSB3 * 256);

      int analogMSB4      = mySerial.read();
      int analogLSB4      = mySerial.read();
      analogReading4  = analogLSB4 + (analogMSB4 * 256);
    }
  }
  for (int i = 0; i < 16; i++) {
    if(i == 0 || i == 4 || i == 8 ||i == 12){
      pos[i] = 0.0;
    }
    else if (i < 4){
        pos[i] = abs(590 - analogReading2)/250.0;
    }
    else if (i < 8){
        pos[i] = abs(590 - analogReading3)/100.0;
    }
    else if (i < 12){
        pos[i] = abs(495 - analogReading4)/300.0;
    }
    else if (i < 16){
        pos[i] = abs(775 - analogReading1)/350.0;
    }
  }

  msgJoint.position = pos;
  Joints.publish(&msgJoint);

  nh.spinOnce();
}
