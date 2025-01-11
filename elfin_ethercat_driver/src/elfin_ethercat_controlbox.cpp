#include <elfin_ethercat_driver/elfin_ethercat_controlbox.h>

namespace elfin_ethercat_driver{

ElfinEtherCATControlBoxClient::ElfinEtherCATControlBoxClient(EtherCatManager* manager, int slave_no):
    manager_(manager), slave_no_(slave_no)
    {
        std::string info_tx_name="elfin_controlbox_info_tx_slave";
        std::string info_rx_name="elfin_controlbox_info_rx_slave";
        std::string Simulate_controlbox="elfin_simulate_controlbox_slave";

        std::string slave_num=boost::lexical_cast<std::string>(slave_no);

        info_tx_name.append(slave_num);
        info_rx_name.append(slave_num);
        Simulate_controlbox.append(slave_num);
  
        // init pdo_input and output-txpdo
        std::string name_pdo_input[59]={"Emergency_Stop_Status", "DigitalInput_Feedback",
                                    "Analog_Input", "OutputIO_Feedback",
                                    "SP_OutputIO_Feedback","PowerOnErrorCode",
                                    "SystemControlBoard_Cmd","SafetyOutput",
                                    "sensedTorques_Axis1","disturbanceTorques_Axis1",
                                    "sensedTorques_Axis2","disturbanceTorques_Axis2",
                                    "sensedTorques_Axis3","disturbanceTorques_Axis3",
                                    "sensedTorques_Axis4","disturbanceTorques_Axis4",
                                    "sensedTorques_Axis5","disturbanceTorques_Axis5",
                                    "sensedTorques_Axis6","disturbanceTorques_Axis6",
                                    "Reserved1","Reserved2",
                                    "Reserved3","Reserved4",
                                    "estimatedTorques_Axis1","estimatedTorques_Axis2",
                                    "estimatedTorques_Axis3","estimatedTorques_Axis4",
                                    "estimatedTorques_Axis5","estimatedTorques_Axis6",
                                    "Reserved5","Reserved6",
                                    "Reserved7","Reserved8",
                                    "Reserved9","Reserved10",
                                    "Reserved11","Reserved12",
                                    "Reserved13","Reserved14",
                                    "Reserved15","Reserved16",
                                    "Reserved17","Reserved18",
                                    "Reserved19","Reserved20",
                                    "ExternEconderCount","Axis1_2_STO",
                                    "Axis1_2_Heatbeat","Axis1_2_CRC",
                                    "Axis1_2_reserved1","Axis3_4_STO",
                                    "Axis3_4_Heatbeat","Axis3_4_CRC",
                                    "Axis3_4_reserved1","Axis5_6_STO",
                                    "Axis5_6_Heatbeat","Axis5_6_CRC",
                                    "Axis5_6_reserved1"};
                                
        uint8_t channel_pdo_input[59]={0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40,
                                        44, 48, 52, 56, 60, 64, 68, 72, 76, 80,
                                        84, 88, 92, 96, 100, 104, 108, 112, 116, 120,
                                        124, 128, 132, 136, 140, 144, 148, 152, 156, 160,
                                        164, 168, 172, 176, 180, 184, 188, 192, 196, 200,
                                        204, 208, 212, 216, 220, 224, 228, 232
                                    };
        pdo_input.clear();
        ElfinPDOunit unit_tmp; // old namespace
        for(unsigned i=0; i<59; ++i)
        {
            unit_tmp.name=name_pdo_input[i];
            unit_tmp.channel=channel_pdo_input[i];
            pdo_input.push_back(unit_tmp);
        }
        // rxpdo
        std::string name_pdo_output[133]={"Axis1_PosCmd","Axis1_VelCmd","Axis1_TorqCmd_and_Axis1_Torqfb","Axis1_Posfb",
                                        "Axis1_Velfb","Axis1_Posfb_L","Axis1_Ucurr_safe","Axis1_Ucurr_ctrl",
                                        "Axis1_Vcurr_safe","Axis1_Vcurr_ctrl","Axis1_AccelCmd","Axis1_Pos_filter",
                                        "Axis1_Vel_filter","Axis1_Curr_filter","Axis1_Accel_filter","Axis1_2_Temp_drv",
                                        "Axis1_2_Volt_drv","Axis1_Servo_Status","Axis1_Power","Axis1_Momentum",
                                        "Axis2_PosCmd","Axis2_VelCmd","Axis2_TorqCmd_and_Axis2_Torqfb","Axis2_Posfb",
                                        "Axis2_Velfb","Axis2_Posfb_L","Axis2_Ucurr_safe","Axis2_Ucurr_ctrl",
                                        "Axis2_Vcurr_safe","Axis2_Vcurr_ctrl","Axis2_AccelCmd","Axis2_Pos_filter",
                                        "Axis2_Vel_filter","Axis2_Curr_filter","Axis2_Accel_filter","Axis1_2_HeartbeatCount",
                                        "Axis1_2_CRC","Axis2_Servo_Status","Axis2_Power","Axis2_Momentum",
                                        "Axis3_PosCmd","Axis3_VelCmd","Axis3_TorqCmd_and_Axis3_Torqfb","Axis3_Posfb",
                                        "Axis3_Velfb","Axis3_Posfb_L","Axis3_Ucurr_safe","Axis3_Ucurr_ctrl",
                                        "Axis3_Vcurr_safe","Axis3_Vcurr_ctrl","Axis3_AccelCmd","Axis3_Pos_filter",
                                        "Axis3_Vel_filter","Axis3_Curr_filter","Axis3_Accel_filter","Axis3_4_Temp_drv",
                                        "Axis3_4_Volt_drv","Axis3_Servo_Status","Axis3_Power","Axis3_Momentum",
                                        "Axis4_PosCmd","Axis4_VelCmd","Axis4_TorqCmd_and_Axis4_Torqfb","Axis4_Posfb",
                                        "Axis4_Velfb","Axis4_Posfb_L","Axis4_Ucurr_safe","Axis4_Ucurr_ctrl",
                                        "Axis4_Vcurr_safe","Axis4_Vcurr_ctrl","Axis4_AccelCmd","Axis4_Pos_filter",
                                        "Axis4_Vel_filter","Axis4_Curr_filter","Axis4_Accel_filter","Axis3_4_HeartbeatCount",
                                        "Axis3_4_CRC","Axis4_Servo_Status","Axis4_Power","Axis4_Momentum",
                                        "Axis5_PosCmd","Axis5_VelCmd","Axis5_TorqCmd_and_Axis5_Torqfb","Axis5_Posfb",
                                        "Axis5_Velfb","Axis5_Posfb_L","Axis5_Ucurr_safe","Axis5_Ucurr_ctrl",
                                        "Axis5_Vcurr_safe","Axis5_Vcurr_ctrl","Axis5_AccelCmd","Axis5_Pos_filter",
                                        "Axis5_Vel_filter","Axis5_Curr_filter","Axis5_Accel_filter","Axis5_6_Temp_drv",
                                        "Axis5_6_Volt_drv","Axis5_Servo_Status","Axis5_Power","Axis5_Momentum",
                                        "Axis6_PosCmd","Axis6_VelCmd","Axis6_TorqCmd_and_Axis6_Torqfb","Axis6_Posfb",
                                        "Axis6_Velfb","Axis6_Posfb_L","Axis6_Ucurr_safe","Axis6_Ucurr_ctrl",
                                        "Axis6_Vcurr_safe","Axis6_Vcurr_ctrl","Axis6_AccelCmd","Axis6_Pos_filter",
                                        "Axis6_Vel_filter","Axis6_Curr_filter","Axis6_Accel_filter","Axis5_6_HeartbeatCount",
                                        "Axis5_6_CRC","Axis6_Servo_Status","Axis6_Power","Analog_IO",
                                        "Digital_IO_and_Function_IO","PowerOn_ControlWord_and_Controller_Status","Power_Whole_Machine","Momentum_Whole_Machine",
                                        "Reserved1","Reserved2","Reserved3","Reserved4",
                                        "Reserved5","Reserved6","Reserved7","Reserved8",
                                        "Reserved9"
                                        };
                            
        uint16_t channel_pdo_output[133]={0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40,
                                        44, 48, 52, 56, 60, 64, 66, 70, 74, 78,
                                        82, 86, 90, 94, 98, 102, 106, 110, 114, 118,
                                        122, 126, 130, 134, 138, 142, 144, 148, 152, 156,
                                        160, 164, 168, 172, 176, 180, 184, 188, 192, 196,
                                        200, 204, 208, 212, 216, 220, 222, 226, 230, 234,
                                        238, 242, 246, 250, 254, 258, 262, 266, 270, 274,
                                        278, 282, 286, 290, 294, 298, 300, 304, 308, 312,
                                        316, 320, 324, 328, 332, 336, 340, 344, 348, 352,
                                        356, 360, 364, 368, 372, 376, 378, 382, 386, 390,
                                        394, 398, 402, 406, 410, 414, 418, 422, 426, 430,
                                        434, 438, 442, 446, 450, 454, 456, 460, 464, 468,
                                        472, 476, 480, 484, 488, 492, 496, 500, 504, 508,
                                        512, 516};
        pdo_output.clear();
        for(unsigned i=0; i<133; ++i)
        {
            unit_tmp.name=name_pdo_output[i];
            unit_tmp.channel=channel_pdo_output[i];
            pdo_output.push_back(unit_tmp);
        }

    }

    ElfinEtherCATControlBoxClient::~ElfinEtherCATControlBoxClient()
    {
    }

    bool ElfinEtherCATControlBoxClient::setSimulateControlBox()
    {
        return true;
    }
}
