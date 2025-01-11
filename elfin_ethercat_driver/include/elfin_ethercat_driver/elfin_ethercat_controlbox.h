#ifndef ELFIN_ETHERCAT_CONTROLBOX_CLIENT_H
#define ELFIN_ETHERCAT_CONTROLBOX_CLIENT_H

#include <ros/ros.h>
#include <vector>
#include <elfin_ethercat_driver/elfin_ethercat_manager.h>
#include <std_srvs/SetBool.h>

#include <pthread.h>
#include <time.h>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

namespace elfin_controlbox_txpdo {

const int Emergency_Stop_Status=0;
const int DigitalInput_Feedback=1;
const int Analog_Input=2;
const int OutputIO_Feedback=3;
const int SP_OutputIO_Feedback=4;
const int PowerOnErrorCode=5;
const int SystemControlBoard_Cmd=6;
const int SafetyOutput=7;
const int sensedTorques_Axis1=8;
const int disturbanceTorques_Axis1=9;
const int sensedTorques_Axis2=10;
const int disturbanceTorques_Axis2=11;
const int sensedTorques_Axis3=12;
const int disturbanceTorques_Axis3=13;
const int sensedTorques_Axis4=14;
const int disturbanceTorques_Axis4=15;
const int sensedTorques_Axis5=16;
const int disturbanceTorques_Axis5=17;
const int sensedTorques_Axis6=18;
const int disturbanceTorques_Axis6=19;
const int Reserved1=20;
const int Reserved2=21;
const int Reserved3=22;
const int Reserved4=23;
const int estimatedTorques_Axis1=24;
const int estimatedTorques_Axis2=25;
const int estimatedTorques_Axis3=26;
const int estimatedTorques_Axis4=27;
const int estimatedTorques_Axis5=28;
const int estimatedTorques_Axis6=29;
const int Reserved5=30;
const int Reserved6=31;
const int Reserved7=32;
const int Reserved8=33;
const int Reserved9=34;
const int Reserved10=35;
const int Reserved11=36;
const int Reserved12=37;
const int Reserved13=38;
const int Reserved14=39;
const int Reserved15=40;
const int Reserved16=41;
const int Reserved17=42;
const int Reserved18=43;
const int Reserved19=44;
const int Reserved20=45;
const int ExternEconderCount=46;
const int Axis1_2_STO=47;
const int Axis1_2_Heatbeat=48;
const int Axis1_2_CRC=49;
const int Axis1_2_reserved1=50;
const int Axis3_4_STO=51;
const int Axis3_4_Heatbeat=52;
const int Axis3_4_CRC=53;
const int Axis3_4_reserved1=54;
const int Axis5_6_STO=55;
const int Axis5_6_Heatbeat=56;
const int Axis5_6_CRC=57;
const int Axis5_6_reserved1=58;
}

namespace elfin_io_rxpdo {

const int Axis1_PosCmd=0;
const int Axis1_VelCmd=1;
// 16
const int Axis1_TorqCmd=2;
const int Axis1_Torqfb=2;
// 32
const int Axis1_Posfb=3;
const int Axis1_Velfb=4;
const int Axis1_Posfb_L=5;
const int Axis1_Ucurr_safe=6;
const int Axis1_Ucurr_ctrl=7;
const int Axis1_Vcurr_safe=8;
const int Axis1_Vcurr_ctrl=9;
const int Axis1_AccelCmd=10;
const int Axis1_Pos_filter=11;
const int Axis1_Vel_filter=12;
const int Axis1_Curr_filter=13;
const int Axis1_Accel_filter=14;
const int Axis1_2_Temp_drv=15;
const int Axis1_2_Volt_drv=16;
// 16
const int Axis1_Servo_Status=17;
// 32
const int Axis1_Power=18;
const int Axis1_Momentum=19;
const int Axis2_PosCmd=20;
const int Axis2_VelCmd=21;
// 16
const int Axis2_TorqCmd=22;
const int Axis2_Torqfb=22;
// 32
const int Axis2_Posfb=23;
const int Axis2_Velfb=24;
const int Axis2_Posfb_L=25;
const int Axis2_Ucurr_safe=26;
const int Axis2_Ucurr_ctrl=27;
const int Axis2_Vcurr_safe=28;
const int Axis2_Vcurr_ctrl=29;
const int Axis2_AccelCmd=30;
const int Axis2_Pos_filter=31;
const int Axis2_Vel_filter=32;
const int Axis2_Curr_filter=33;
const int Axis2_Accel_filter=34;
const int Axis1_2_HeartbeatCount=35;
const int Axis1_2_CRC=36;
// 16
const int Axis2_Servo_Status=37;
// 32
const int Axis2_Power=38;
const int Axis2_Momentum=39;
const int Axis3_PosCmd=40;
const int Axis3_VelCmd=41;
// 16
const int Axis3_TorqCmd=42;
const int Axis3_Torqfb=42;
// 32
const int Axis3_Posfb=43;
const int Axis3_Velfb=44;
const int Axis3_Posfb_L=45;
const int Axis3_Ucurr_safe=46;
const int Axis3_Ucurr_ctrl=47;
const int Axis3_Vcurr_safe=48;
const int Axis3_Vcurr_ctrl=49;
const int Axis3_AccelCmd=50;
const int Axis3_Pos_filter=51;
const int Axis3_Vel_filter=52;
const int Axis3_Curr_filter=53;
const int Axis3_Accel_filter=54;
const int Axis3_4_Temp_drv=55;
const int Axis3_4_Volt_drv=56;
// 16
const int Axis3_Servo_Status=57;
// 32
const int Axis3_Power=58;
const int Axis3_Momentum=59;
const int Axis4_PosCmd=60;
const int Axis4_VelCmd=61;
// 16
const int Axis4_TorqCmd=62;
const int Axis4_Torqfb=62;
// 32
const int Axis4_Posfb=63;
const int Axis4_Velfb=64;
const int Axis4_Posfb_L=65;
const int Axis4_Ucurr_safe=66;
const int Axis4_Ucurr_ctrl=67;
const int Axis4_Vcurr_safe=68;
const int Axis4_Vcurr_ctrl=69;
const int Axis4_AccelCmd=70;
const int Axis4_Pos_filter=71;
const int Axis4_Vel_filter=72;
const int Axis4_Curr_filter=73;
const int Axis4_Accel_filter=74;
const int Axis3_4_HeartbeatCount=75;
const int Axis3_4_CRC=76;
// 16
const int Axis4_Servo_Status=77;
// 32
const int Axis4_Power=78;
const int Axis4_Momentum=79;
const int Axis5_PosCmd=80;
const int Axis5_VelCmd=81;
// 16
const int Axis5_TorqCmd=82;
const int Axis5_Torqfb=82;
// 
const int Axis5_Posfb=83;
const int Axis5_Velfb=84;
const int Axis5_Posfb_L=85;
const int Axis5_Ucurr_safe=86;
const int Axis5_Ucurr_ctrl=87;
const int Axis5_Vcurr_safe=88;
const int Axis5_Vcurr_ctrl=89;
const int Axis5_AccelCmd=90;
const int Axis5_Pos_filter=91;
const int Axis5_Vel_filter=92;
const int Axis5_Curr_filter=93;
const int Axis5_Accel_filter=94;
const int Axis5_6_Temp_drv=95;
const int Axis5_6_Volt_drv=96;
// 16
const int Axis5_Servo_Status=97;
// 32
const int Axis5_Power=98;
const int Axis5_Momentum=99;
const int Axis6_PosCmd=100;
const int Axis6_VelCmd=101;
// 16
const int Axis6_TorqCmd=102;
const int Axis6_Torqfb=102;
// 32
const int Axis6_Posfb=103;
const int Axis6_Velfb=104;
const int Axis6_Posfb_L=105;
const int Axis6_Ucurr_safe=106;
const int Axis6_Ucurr_ctrl=107;
const int Axis6_Vcurr_safe=108;
const int Axis6_Vcurr_ctrl=109;
const int Axis6_AccelCmd=110;
const int Axis6_Pos_filter=111;
const int Axis6_Vel_filter=112;
const int Axis6_Curr_filter=113;
const int Axis6_Accel_filter=114;
const int Axis5_6_HeartbeatCount=115;
const int Axis5_6_CRC=116;
// 16
const int Axis6_Servo_Status=117;
// 32
const int Axis6_Power=118;
const int Analog_IO=119;
// 16
const int Digital_IO=120;
const int Function_IO=120;
// 16
const int PowerOn_ControlWord=121;
const int Controller_Status=121;
// 32
const int Power_Whole_Machine=122;
const int Momentum_Whole_Machine=123;
const int Reserved1=124;
const int Reserved2=125;
const int Reserved3=126;
const int Reserved4=127;
const int Reserved5=128;
const int Reserved6=129;
const int Reserved7=130;
const int Reserved8=131;
const int Reserved9=132;
}

namespace  elfin_ethercat_driver {

class ElfinEtherCATControlBoxClient{

private:
    EtherCatManager* manager_;
    ros::NodeHandle n_;
    ros::NodeHandle box_nh_;
    std::vector<ElfinPDOunit> pdo_input; // txpdo
    std::vector<ElfinPDOunit> pdo_output; //rxpdo
    int slave_no_;
public:
    ElfinEtherCATControlBoxClient(EtherCatManager* manager, int slave_no);
    ~ElfinEtherCATControlBoxClient();

    std::string getTxSDO();
    std::string getRxSDO();

    bool setSimulateControlBox();
};

}

#endif
