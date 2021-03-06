# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
create_project -in_memory -part xc7z020clg484-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir U:/Documents/cpre488/Labs/MP-0/project_1/project_1.cache/wt [current_project]
set_property parent.project_path U:/Documents/cpre488/Labs/MP-0/project_1/project_1.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language VHDL [current_project]
set_property board_part em.avnet.com:zed:part0:1.4 [current_project]
set_property ip_repo_paths u:/Documents/cpre488/Labs/MP-0/ip_repo/snes_intf_1.0 [current_project]
update_ip_catalog
set_property ip_output_repo u:/Documents/cpre488/Labs/MP-0/project_1/project_1.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_vhdl -library xil_defaultlib U:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/hdl/zynq_design_1_wrapper.vhd
add_files U:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/zynq_design_1.bd
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_processing_system7_0_0/zynq_design_1_processing_system7_0_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_0_0/zynq_design_1_axi_gpio_0_0_board.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_0_0/zynq_design_1_axi_gpio_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_0_0/zynq_design_1_axi_gpio_0_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_1_0/zynq_design_1_axi_gpio_1_0_board.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_1_0/zynq_design_1_axi_gpio_1_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_1_0/zynq_design_1_axi_gpio_1_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_2_0/zynq_design_1_axi_gpio_2_0_board.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_2_0/zynq_design_1_axi_gpio_2_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_2_0/zynq_design_1_axi_gpio_2_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_xbar_0/zynq_design_1_xbar_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_rst_ps7_0_100M_0/zynq_design_1_rst_ps7_0_100M_0_board.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_rst_ps7_0_100M_0/zynq_design_1_rst_ps7_0_100M_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_rst_ps7_0_100M_0/zynq_design_1_rst_ps7_0_100M_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_vdma_0_0/zynq_design_1_axi_vdma_0_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_vdma_0_0/zynq_design_1_axi_vdma_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_vdma_0_0/zynq_design_1_axi_vdma_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_v_tc_0_0/zynq_design_1_v_tc_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_v_tc_0_0/zynq_design_1_v_tc_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_v_axi4s_vid_out_0_0/zynq_design_1_v_axi4s_vid_out_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_v_axi4s_vid_out_0_0/zynq_design_1_v_axi4s_vid_out_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_proc_sys_reset_0_0/zynq_design_1_proc_sys_reset_0_0_board.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_proc_sys_reset_0_0/zynq_design_1_proc_sys_reset_0_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_proc_sys_reset_0_0/zynq_design_1_proc_sys_reset_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_4_0/zynq_design_1_axi_gpio_4_0_board.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_4_0/zynq_design_1_axi_gpio_4_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_4_0/zynq_design_1_axi_gpio_4_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/edit_snes_intf_v1_0.ip_user_files/zedboard_master.xdc]
set_property used_in_synthesis false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_ila_0_0/ila_v6_2/constraints/ila_impl.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_ila_0_0/ila_v6_2/constraints/ila_impl.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_ila_0_0/ila_v6_2/constraints/ila.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_ila_0_0/zynq_design_1_ila_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_3_0/zynq_design_1_axi_gpio_3_0_board.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_3_0/zynq_design_1_axi_gpio_3_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_axi_gpio_3_0/zynq_design_1_axi_gpio_3_0.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_9/zynq_design_1_auto_pc_9_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_0/zynq_design_1_auto_pc_0_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_1/zynq_design_1_auto_pc_1_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_2/zynq_design_1_auto_pc_2_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_3/zynq_design_1_auto_pc_3_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_4/zynq_design_1_auto_pc_4_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_5/zynq_design_1_auto_pc_5_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_6/zynq_design_1_auto_pc_6_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_7/zynq_design_1_auto_pc_7_ooc.xdc]
set_property used_in_implementation false [get_files -all u:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/ip/zynq_design_1_auto_pc_8/zynq_design_1_auto_pc_8_ooc.xdc]
set_property used_in_implementation false [get_files -all U:/Documents/cpre488/Labs/MP-0/project_1/project_1.srcs/sources_1/bd/zynq_design_1/zynq_design_1_ooc.xdc]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc U:/Documents/cpre488/Labs/MP-0/project_1/mp-0.xdc
set_property used_in_implementation false [get_files U:/Documents/cpre488/Labs/MP-0/project_1/mp-0.xdc]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top zynq_design_1_wrapper -part xc7z020clg484-1


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef zynq_design_1_wrapper.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file zynq_design_1_wrapper_utilization_synth.rpt -pb zynq_design_1_wrapper_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
