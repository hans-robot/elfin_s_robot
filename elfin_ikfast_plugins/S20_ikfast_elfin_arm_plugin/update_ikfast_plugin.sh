search_mode=OPTIMIZE_MAX_JOINT
srdf_filename=S20.srdf
robot_name_in_srdf=S20
moveit_config_pkg=S20_moveit_config
robot_name=S20
planning_group_name=elfin_arm
ikfast_plugin_pkg=S20_ikfast_elfin_arm_plugin
base_link_name=elfin_base
eef_link_name=elfin_end_link
ikfast_output_path=/home/cjw/elfin_s_robot/src/S20_ikfast_elfin_arm_plugin/src/S20_elfin_arm_ikfast_solver.cpp

rosrun moveit_kinematics create_ikfast_moveit_plugin.py\
  --search_mode=$search_mode\
  --srdf_filename=$srdf_filename\
  --robot_name_in_srdf=$robot_name_in_srdf\
  --moveit_config_pkg=$moveit_config_pkg\
  $robot_name\
  $planning_group_name\
  $ikfast_plugin_pkg\
  $base_link_name\
  $eef_link_name\
  $ikfast_output_path
